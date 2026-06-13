
#include "uart.h"
#include "stm32f401xe.h"

void UART2_Init(void){
    //UART drivers
    //The user manual tells that the TX and RX pins are connected to PA2 and PA3
    //enable clock access to UART2:
    RCC->APB1ENR |= (1<<17);
    //set moder to alternative function
    //pin 2 (TX)
    GPIOA->MODER &= ~(3<<4); //clear bits 4 and 5, 3 = 11 in binary
    GPIOA->MODER |= (2<<4); //set to 10, 2 = 10 in binary
    //pin 3 (RX)
    GPIOA->MODER &= ~(3<<6); //clear bits
    GPIOA->MODER |= (2<<6); //set to 10
    //looking at the alternative function diagram in the datasheet: We need to take the UART function AF07
    //writing to the AFLR (Alternative Function Low Register) register the UART function:  AF07 = 0111 
    GPIOA->AFR[0] |= ((1<<8) | (1<<9) | (1<<10)); //pin 2 (TX) 111
    GPIOA->AFR[0] |= ((1<<12) | (1<<13) | (1<<14)); //pin 3 (RX) 111
    GPIOA->AFR[0] &= ~((1<<11) | (1<<15)); //0
    //next we need to setup the BRR (Baud Rate Register). The Baud rate is calculated with the formula in the image "baud rate formula.png"
    //We'll decide that the baud rate will be 9600 and that OVER8 = 0 for simplicity. f_ck is the frequency of the bus connecting to USART2 (the APB1 bus) which is 16MHz
    //Now we need to calculate the USARTDIV with the now known variables:
    //USARTDIV = f_ck / 16*Baud = 16 000 000 / 16 * 9600 = 104,1666..
    //USART2->BRR |= (104<<4) | 3; //the integer nums
    USART2->BRR = 42000000 / 9600;

    //Enable USART, Transmitter and Reciever
    USART2->CR1 |= ((1<<13) | (1<<3) | (1<<2));

}

void UART2_WriteChar(char ch){
    while ((USART2->SR & (1<<7) == 0));
    USART2->DR = ch;
}