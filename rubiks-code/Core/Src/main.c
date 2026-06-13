#include "main.h"
#include "uart.h"
#include "stm32f401xe.h"

void SystemClock_Config(void);
void Error_Handler(void);




int main(void)
{
  HAL_Init();
  SystemClock_Config();
  UART2_Init();


  //SETUP USER BTN
  //user btn: PC13 - port C, pin 13
  //in the block diagram: Port C is connected to the AHB1 buss.
  RCC->AHB1ENR |= ((1<<0) | (1<<2)); //enable both user btn and user led 
  GPIOC->MODER &= ~((1<<26) | (1<<27)); //set moder13 to input state (00)

  //SETUP USER LED
  //The user LED is connected is located at Port A, Pin 5. as seen in the user guide. 
  //in the datasheet, at the block diagram: we can see that PORT A is connected to the AHB1 bus
  //the base address for GPIO Port A is 0x4002 0000.
  GPIOA->MODER |= (1<<10);
  GPIOA->MODER &= ~(1<<11);

  while (1)
  {
    int btn_pressed = ((GPIOC->IDR & (1<<13)) == 0);

    if(btn_pressed){
      GPIOA->ODR &= ~(1<<5);
      if((USART2->SR & (1<<7)) != 0){
        UART2_WriteChar('A');
      } 
    }else{
      GPIOA->ODR |= (1<<5);
    }
    
    btn_pressed = 0;
    
  }
}


//HAL code for configuring the clock signal
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | 
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif