/*
 * machine_learning.c
 *
 *  Created on: 11. 6. 2025
 *      Author: xmartij01
 */

#include "TimeSeries.h"
#include "machine_learning.h"
#include "sai.h"
#include "MPU6050.h"
#include "fsl_fxos.h"
#include <stdio.h>
#include "stdio.h"

float data_input[TSS_INPUT_DATA_LEN * TSS_INPUT_DATA_DIM];
extern volatile bool i2c_new_data;
extern fxos_handle_t g_fxosHandle;

/*
 * @brief Collects one full line of acceleration samples for ML input
 *        Each line has SAMPLES_PER_LINE vectors of (X,Y,Z) data
 */
void sample_data(float data_buffer[])
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
        sample_data(data_input);
        DWT->CYCCNT=0;
        status = tss_ad_predict(data_input, &probability);
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
//int ml_classification(void)
//{
//    tss_status status;
//    float probabilities[TSS_CLASS_NUMBER];
//    int class_index;
//
//    status = tss_cls_init();
//    if (status != TSS_SUCCESS)
//    {
//        /* Handle the initialization failure cases */
//    }
//
//    while (1)
//    {
//        sample_data(data_input);
//        status = tss_cls_predict(data_input, probabilities, &class_index);
//        if (status != TSS_SUCCESS)
//        {
//            /* Handle the prediction failure cases */
//            PRINTF("error %d\r\n");
//
//        }else{
//            PRINTF("classification %f %d\r\n", probabilities[0],0);
//            ...PRINTF("classification %f %d\r\n", probabilities[0],0);
//        }
//
//        /* Handle the prediction result */
//    }
//
//    return 0;
//}
