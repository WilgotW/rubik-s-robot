#include "stm32f401xe.h"
#include "stm32f4xx.h"

//UART works by setting up 2 pins for recieving(Rx) and sending(Tx) data

//STM pins: PB6: TX.  PB7: RX
//Enable clock for Rx and Tx pin 

//by viewing the block diagram, we can see that PORT B is connected to the AHB1 bus.
//In the refrence manual, we can see that GPIOB has a offset of 1
void setup(void) {
    RCC->AHB1ENR |= (1 << 1); //GPIOB now has clock access


}