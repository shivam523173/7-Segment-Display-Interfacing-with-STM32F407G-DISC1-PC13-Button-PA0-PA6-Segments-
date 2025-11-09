/* USER CODE BEGIN Header */
 /** ******************************************************************************
 * @file
 main.c
 * @brief STM32F407 Discovery: 7-Segment Display with User Button
 ******************************************************************************
 */
 /* USER CODE END Header */
 #include "main.h"
 /* Private variables---------------------------------------------------------*/
 volatile int led_number = 0;
 // 0-9 counter
 volatile uint8_t button_pressed = 0; // Button flag
 // 7-segment pattern for 0-9 (a-g, common-cathode)
 // bit order: PA0->a, PA1->b, PA2->c, PA3->d, PA4->e, PA5->f, PA6->g
 uint8_t segmentNumber[10] = {
 0x3F, //0
 0x06, //1
 0x5B, //2
 0x4F, //3
 0x66, //4
 0x6D, //5
 0x7D, //6
 0x07, //7
 0x7F, //8
 0x6F //9
 };
 /* Function Prototypes */
 void SystemClock_Config(void);
 static void MX_GPIO_Init(void);
 void SevenSegment_Update(uint8_t number);
 /* USER CODE BEGIN 0 */
 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
if(GPIO_Pin == GPIO_PIN_13){ // User button on PC13
 button_pressed = 1;
 }
 }
 void SevenSegment_Update(uint8_t num)
 {
// Using PA0-PA6 for 7-segment a-g
 for(uint8_t i=0; i<7; i++){
 HAL_GPIO_WritePin(GPIOA, (1<<i), (num>>i)&0x01);
 }
 }
 /* USER CODE END 0 */
 int main(void)
 {
HAL_Init();
 SystemClock_Config();
 MX_GPIO_Init();
 while (1)
 {
if(button_pressed) // increment
 { led_number++;
 if(led_number > 9) led_number = 0;
 button_pressed = 0;
 }
 SevenSegment_Update(segmentNumber[led_number]);
}
 HAL_Delay(500); // display delay
 }
 /* System Clock Configuration */
 void SystemClock_Config(void)
 {
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
 RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
 __HAL_RCC_PWR_CLK_ENABLE();
 __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
 RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
 RCC_OscInitStruct.HSIState = RCC_HSI_ON;
 RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
 RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
 RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
 RCC_OscInitStruct.PLL.PLLM = 16;
 RCC_OscInitStruct.PLL.PLLN = 336;
 RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
 RCC_OscInitStruct.PLL.PLLQ = 7;
 if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();
 RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
 |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
 RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
 RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
 RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
 RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
 if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
 Error_Handler();
 }
 /* GPIO Initialization */
 static void MX_GPIO_Init(void)
 {
GPIO_InitTypeDef GPIO_InitStruct = {0};
 __HAL_RCC_GPIOA_CLK_ENABLE();
 __HAL_RCC_GPIOC_CLK_ENABLE();
 // Configure 7-segment pins PA0-PA6
 GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
 |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 // Configure User Button PC13
 GPIO_InitStruct.Pin = GPIO_PIN_13;
 GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
 // Enable EXTI interrupt
 HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
 HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
 }
 /* Error Handler */
 void Error_Handler(void)
 {
__disable_irq();
 while(1) {}
 }
