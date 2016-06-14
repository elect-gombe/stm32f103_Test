/*
 * A skeleton main.c
 * Add your own code!
 */
/* Load CMSIS and peripheral library and configuration */

#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "message.h"

/* Peripheral configuration functions */
void GPIO_Config();

/* A simple busy wait loop */
void Delay(volatile unsigned long delay);

uint32_t SystemCoreClock = 72000000;

UART_HandleTypeDef U2handle = {
  .Instance = USART2,
  .Init = {
    .BaudRate = 115200,
    .WordLength = UART_WORDLENGTH_8B,
    .StopBits = UART_STOPBITS_2,
    .Parity = UART_PARITY_NONE,
    .Mode = UART_MODE_TX_RX,
    .HwFlowCtl = UART_HWCONTROL_NONE,
    .OverSampling = UART_OVERSAMPLING_16,
  }
};

void SystemInit(void) {
  volatile int i[1000] = { 0 };
  i[1000 - 1] = 1 << 16;
  i[2] = i[1];

  /* Reset the RCC clock configuration to the default reset state*/

  /*Set HSEBYP bit */
  /*  RCC->CR &= (uint32_t)0x1<<18; */

  /* Set HSEON bit */
  RCC->CR |= (uint32_t)0x1 << 16;

  /*set 9x8MHz*/
  RCC->CFGR |= RCC_CFGR_PLLMULL9;

  /*use HSE*/
  RCC->CFGR |= RCC_CFGR_PLLSRC;

  /*set AHB prescaler 1:2*/
  RCC->CFGR |= 0x10 << 10;

  FLASH->ACR = 0;
  /*flash prefetch buffer*/
  FLASH->ACR |= FLASH_ACR_PRFTBE;
  /*flash latency*/
  FLASH->ACR |= FLASH_ACR_LATENCY_2;

  /*wait get ready*/
  while( !( RCC->CR & ( 0x01 << 17 ))){
  }

  Delay(10);
  /*PLL enable*/
  RCC->CR |= 0x01 << 24;
  Delay(10);

  while( !( RCC->CR & ( 0x01 << 25 ))){
  }

  RCC->CFGR |= 0x02;

  /*select PLL clock*/
  RCC->CR &= ~(uint32_t)( 0x01 << 16 );

  /*set interrupt vector base*/
  SCB->VTOR = FLASH_BASE;

  /*other clock settings*/
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();
} /* SystemInit */

int __io_putchar(int ch) {
  HAL_UART_Transmit(&U2handle, (uint8_t*)&ch, 1, 0xFFFF);
  return ch;
}

int main(void) {
  int i = 0;
  SystemInit();
  /* Setup the GPIOs */
  GPIO_Config();

  HAL_Init();
  {
    if( HAL_UART_Init(&U2handle) != HAL_OK ){
      while( 1 ){
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

        for( uint32_t i = 0; i < 200000; i++ ){
        }
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

        for( uint32_t i = 0; i < 500000; i++ ){
        }
      }
    } else {
      xdev_out(__io_putchar);

      while( 1 ){
        MW_printf("HelloWorld\n");
        MW_printf("Hello%d:%b\n", 114514, 114514);

        message("msg", "in infinity loop%d", i++);
        MW_flush();
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

        for( int i = 0; i < 500000; i++ ){
        }

        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

        for( int i = 0; i < 500000; i++ ){
        }
      }
    }
  }
} /* main */

void Delay(volatile unsigned long delay) {
  for(; delay; --delay ){
  }
}

void GPIO_Config() {
  RCC->APB2ENR |= ( 0x01 << 4 ) | ( 0x01 << 5 );

  GPIOD->CRL = 0x42444444;
  GPIOD->CRH = 0x44244444;

  /* GPIO_InitStruct.Pin = GPIO_PIN_2; */
  /* GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; */
  /* GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; */
  {
    GPIO_InitTypeDef gpio = {
      GPIO_PIN_2,
      GPIO_MODE_AF_PP,
      GPIO_NOPULL,
      GPIO_SPEED_FREQ_HIGH,
    };
    HAL_GPIO_Init(GPIOA, &gpio);
  }

  {
    GPIO_InitTypeDef gpio = {
      GPIO_PIN_3,
      GPIO_MODE_INPUT,
      GPIO_NOPULL,
      GPIO_SPEED_FREQ_HIGH
    };
    HAL_GPIO_Init(GPIOA, &gpio);
  }
} /* GPIO_Config */
