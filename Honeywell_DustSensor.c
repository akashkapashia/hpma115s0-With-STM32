/**
	******************************************************************************
	* File Name          : Honeywell_DustSensor.c
	* Description        : This file contains the common defines of the application
	******************************************************************************
	*
	* COPYRIGHT(c) 2017 Akash kapashia
        * Created by Akash kapashia
	******************************************************************************
*/
 

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "Honeywell_DustSensor.h"
UART_HandleTypeDef huart1_DustSensor;

uint8_t Particle_Measure_Data[8];
uint16_t PM2_5=0;;
uint16_t PM10 =0;


/**
  * @brief MX_USART_DUSTSENSOR_UART_Init.
  * @param NONE.
  * @retval None
  */
 void MX_USART_DUSTSENSOR_UART_Init(void)
{

  huart1_DustSensor.Instance = USART_DUSTSENSOR;
  huart1_DustSensor.Init.BaudRate = 9600;
  huart1_DustSensor.Init.WordLength = UART_WORDLENGTH_8B;
  huart1_DustSensor.Init.StopBits = UART_STOPBITS_1;
  huart1_DustSensor.Init.Parity = UART_PARITY_NONE;
  huart1_DustSensor.Init.Mode = UART_MODE_TX_RX;
  huart1_DustSensor.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1_DustSensor.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1_DustSensor.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1_DustSensor.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1_DustSensor) != HAL_OK)
  {
  while(1);		
	}

}


/**
  * @brief start_Particle_Measure.
  * @param NONE.
  * @retval None.
  */
void start_Particle_Measure(void){
	uint8_t meas_start_data[]={0x68,0x01,0x01,0x96};
 while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if( HAL_UART_Transmit(&huart1_DustSensor, meas_start_data, 4,500)!= HAL_OK)
 {
	 while(1);
 }
	 uint8_t ackn[2];
 if(HAL_UART_Receive(&huart1_DustSensor,ackn,2,500)!=HAL_OK)
 {
	 while(1);
 }
}


/**
  * @brief Read_Particle_Measuring.
  * @param NONE.
  * @retval None.
  */
void Read_Particle_Measuring(){
uint8_t Particle_Measure[]={0x68,0x01,0x4,0x93};
 while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if( HAL_UART_Transmit(&huart1_DustSensor, Particle_Measure, 4,500)!= HAL_OK)
 {
	 while(1);
 }
	  while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if(HAL_UART_Receive(&huart1_DustSensor,Particle_Measure_Data,8,1000)!=HAL_OK)
 {
	 while(1);
 }
 
PM2_5 = Particle_Measure_Data[3] * 256 + Particle_Measure_Data[4];
PM10 = Particle_Measure_Data[5] * 256 + Particle_Measure_Data[6];
}



/**
  * @brief Stop_Particle_Measurement.
  * @param NONE.
  * @retval None.
  */
void Stop_Particle_Measurement(){
	uint8_t meas_start_data[]={0x68,0x01,0x02,0x95};
 while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if( HAL_UART_Transmit(&huart1_DustSensor, meas_start_data, 4,500)!= HAL_OK)
 {
	 while(1);
 }
	 uint8_t ackn[2];
 if(HAL_UART_Receive(&huart1_DustSensor,ackn,2,500)!=HAL_OK)
 {
	 while(1);
 }
	
}

/**
  * @brief Stop_Auto_Send.
  * @param NONE.
  * @retval None.
  */
void Stop_Auto_Send()
{
		uint8_t meas_start_data[]={0x68,0x01,0x20,0x77};
 while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if( HAL_UART_Transmit(&huart1_DustSensor, meas_start_data, 4,500)!= HAL_OK)
 {
	 while(1);
 }
	 uint8_t ackn[2];
 if(HAL_UART_Receive(&huart1_DustSensor,ackn,2,500)!=HAL_OK)
 {
	 while(1);
 }
}


/**
  * @brief Enable_Auto_Send.
  * @param NONE.
  * @retval None.
  */
void Enable_Auto_Send()
{
		uint8_t meas_start_data[]={0x68,0x01,0x40,0x77};
 while(HAL_UART_GetState(&huart1_DustSensor)!= HAL_UART_STATE_READY);
 if( HAL_UART_Transmit(&huart1_DustSensor, meas_start_data, 4,500)!= HAL_OK)
 {
	 while(1);
 }
	 uint8_t ackn[2];
 if(HAL_UART_Receive(&huart1_DustSensor,ackn,2,500)!=HAL_OK)
 {
	 while(1);
 }
	
}
