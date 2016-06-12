#define STM32F103xE
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "UART.h"

int32_t UARTWrite(uint8_t hello) {
  /**/
  UNUSED(hello);
  return 114514;
}
