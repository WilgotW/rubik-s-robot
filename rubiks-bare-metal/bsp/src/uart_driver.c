#include "stm32f401xe.h"
#include "stm32f4xx.h"

//UART works by setting up 2 pins for recieving(Rx) and sending(Tx) data

//STM pins: PB6: TX.  PB7: RX
//Enable clock for Rx and Tx pin 

void setup(void) {
    RCC->APB1ENR
}