/*
 * machine_learning.c
 *
 *  Created on: 11. 6. 2025
 *      Author: jvmreis
 */

#include "TimeSeries.h"
#include "TimeSeries_freqModel.h"
#include "machine_learning.h"
#include "peripherals.h"
#include "sai.h"
#include "MPU6050.h"
#include "fsl_fxos.h"
#include <stdio.h>
#include "stdio.h"

float acc_data_input[TSS_INPUT_DATA_LEN * TSS_INPUT_DATA_DIM];
float mic_data_input[512];

extern volatile bool i2c_new_data;
extern fxos_handle_t g_fxosHandle;


extern sai_edma_handle_t txHandle;
extern sai_edma_handle_t rxHandle;
extern uint8_t audioBuff[BUFFER_SIZE * BUFFER_NUM];
extern volatile bool istxFinished;
extern volatile bool isrxFinished;
extern volatile uint32_t beginCount;
extern volatile uint32_t sendCount;
extern volatile uint32_t receiveCount;
extern bool sdcard;
extern volatile uint32_t fullBlock;
extern volatile uint32_t emptyBlock;

/*
 * @brief Collects one full line of acceleration samples for ML input
 *        Each line has SAMPLES_PER_LINE vectors of (X,Y,Z) data
 */
void acc_sample_data(float data_buffer[])
{
    uint32_t sample_idx = 0;  // Conta amostras completas (x,y,z)
    uint8_t fifo_buffer[6];

    while (sample_idx < TSS_INPUT_DATA_LEN)
    {
        if (i2c_new_data)
        {
            MPU6050_getRAWAcceleration(fifo_buffer, 6);

            data_buffer[sample_idx * 3 + 0] = (float)(int16_t)((fifo_buffer[0] << 8) | fifo_buffer[1]); // X
            data_buffer[sample_idx * 3 + 1] = (float)(int16_t)((fifo_buffer[2] << 8) | fifo_buffer[3]); // Y
            data_buffer[sample_idx * 3 + 2] = (float)(int16_t)((fifo_buffer[4] << 8) | fifo_buffer[5]); // Z

            sample_idx++;
            i2c_new_data = false;
        }

        /***** on board accelrometer *******
        fxos_data_t fxos_data;

        if (FXOS_ReadSensorData(&g_fxosHandle, &fxos_data) != kStatus_Success)
        {
            PRINTF("Failed to read acceleration data!\r\n");
        }else{
        	data_buffer[sample_idx * 3 + 0] = (int16_t)((uint16_t)((uint16_t)fxos_data.accelXMSB << 8) | (uint16_t)fxos_data.accelXLSB) / 4U;
        	data_buffer[sample_idx * 3 + 1] = (int16_t)((uint16_t)((uint16_t)fxos_data.accelYMSB << 8) | (uint16_t)fxos_data.accelYLSB) / 4U;
        	data_buffer[sample_idx * 3 + 2] = (int16_t)((uint16_t)((uint16_t)fxos_data.accelZMSB << 8) | (uint16_t)fxos_data.accelZLSB) / 4U;
        }
        /********************************************************/
    }
}

void mic_sample_data(float data_buffer[])
{
    uint32_t txindex      = 0;
    uint32_t rxindex      = 0;
    sai_transfer_t xfer   = {0};
    uint32_t collected_samples = 0;

    // Reset flags e buffers
    isrxFinished = false;
    istxFinished = false;
    receiveCount = 0;
    sendCount    = 0;
    emptyBlock   = 0;
    fullBlock    = 0;
    memset(audioBuff, 0, BUFFER_SIZE * BUFFER_NUM);

    // Inicia os primeiros buffers
    xfer.dataSize = BUFFER_SIZE;
    for (int i = 0; i < BUFFER_NUM; i++) {
        xfer.data = audioBuff + i * BUFFER_SIZE;
        SAI_TransferReceiveEDMA(DEMO_SAI_PERIPHERAL, &rxHandle, &xfer);
    }
    beginCount = (512 + BUFFER_SIZE - 1) / BUFFER_SIZE;    // Loop até atingir 512 amostras
    while (collected_samples < 512)
    {
        if (fullBlock > 0)
        {
            // Calcula quantas amostras podemos copiar neste bloco
            uint32_t samples_to_copy = BUFFER_SIZE;
            if (collected_samples + samples_to_copy > 512)
            {
                samples_to_copy = 512 - collected_samples;
            }

            for (uint32_t i = 0; i < samples_to_copy; i += 2)
            {
                uint32_t pos = txindex * BUFFER_SIZE + i;
                int16_t sample = (int16_t)((audioBuff[pos+1] << 8) | audioBuff[pos]);
                data_buffer[collected_samples++] = (float)sample;
            }

            collected_samples += samples_to_copy;

            // Atualiza índices
            txindex = (txindex + 1U) % BUFFER_NUM;
            fullBlock--;
            emptyBlock++;
        }

        // Reenche buffer se ainda estiver recebendo
        if ((emptyBlock > 0) && (!isrxFinished))
        {
            xfer.data = audioBuff + rxindex * BUFFER_SIZE;
            rxindex   = (rxindex + 1U) % BUFFER_NUM;
            SAI_TransferReceiveEDMA(DEMO_SAI_PERIPHERAL, &rxHandle, &xfer);
            emptyBlock--;
        }
    }
}


/*
 * @brief Runs eIQ Time Series anomaly detection
 *        Trains model (if ODL enabled), then continuously predicts
 */
int ml_anmaly_detection(void)
{
    tss_status status;
    float probability;
    uint32_t cycleCnt;

#ifdef SUPPORT_ODL
    status = tss_ad_init(NULL);
    if (status != TSS_SUCCESS)
    {
        /* Handle the initialization failure cases */
    }

    /*The learning number is customizable, but we recommend the number greater than TSS_RECOMMEND_LEARNING_SAMPLE_NUM to get better results.*/
    int learning_num = TSS_RECOMMEND_LEARNING_SAMPLE_NUM;
    for (int i = 0; i < learning_num; i++)
    {
        sample_data(data_input);
        status = tss_ad_learn(data_input);
        if (status != TSS_LEARNING_NOT_ENOUGH && status != TSS_RECOMMEND_LEARNING_DONE)
        {
            /* Handle the learning failure cases */
        }
    }
#else
    status = tss_ad_init();
    if (status != TSS_SUCCESS)
    {
        /* Handle the initialization failure cases */
        PRINTF("[DEBUG] ML init error %d\r\n", status);

    }
#endif

    while (1)
    {
    	acc_sample_data(acc_data_input);
        DWT->CYCCNT=0;
        status = tss_ad_predict(acc_data_input, &probability);
        cycleCnt = DWT->CYCCNT;

        if (status != TSS_SUCCESS)
        {
            /* Handle the prediction failure cases */
            PRINTF("error %d\r\n");

        }else{
            PRINTF("anomaly detection %f %d\r\n", probability,cycleCnt);
        }

        /* Handle the prediction result */
    }

    return 0;
}
int ml_classification(void)
{
    tss_status status;
    float probabilities[TSS_CLASS_NUMBER_freqModel];
    int class_index;
    uint32_t cycleCnt;

    status = tss_cls_init_freqModel();
    if (status != TSS_SUCCESS)
    {
        /* Handle the initialization failure cases */
        PRINTF("start error %d\r\n",status);

    }

    while (1)
    {

    	DWT->CYCCNT=0;
    	mic_sample_data(mic_data_input);

        status = tss_cls_predict_freqModel(mic_data_input, probabilities, &class_index);
		cycleCnt = DWT->CYCCNT;
        if (status != TSS_SUCCESS)
        {
            /* Handle the prediction failure cases */
          PRINTF("error %d\r\n",status);

        }else{

        	for(int i=0;i<TSS_CLASS_NUMBER_freqModel;i++){
                PRINTF("class[%d] %.1f ", i,probabilities[i]*100);

        	}
            PRINTF("cycles %d \r\n", cycleCnt);

           // ...PRINTF("classification %f %d\r\n", probabilities[0],0);
        }

        /* Handle the prediction result */
    }

    return 0;
}
