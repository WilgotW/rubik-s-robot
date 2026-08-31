#include <stdint.h>
#include <sys/types.h>
#include "uart.h"
#include "cmsis_gcc.h"
#include "stm32f401xe.h"
#include "motor_driver.h"

void UART2_SendByte(uint8_t data);
uint8_t UART2_ReceiveByte(void);
void UART2_SendFace(uint8_t face[9]);
// void read_cube_face(uint8_t *face_buffer);
void receive_solution(void);
void UART2_protocol(void);

void delay_(volatile uint32_t count) {
    while(count--) {
        __NOP(); 
    }
}

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

//THE SETUP
//STM (slave) recieves command from computer (master) to start scaning cube
//STM sends an ACK and starts scanning the first side of the cube 
//STM sends the data and waits for an ACK from computer
//repeat until all faces are scanned sucessfully. 


//example:    cube = 'DRLUUBFBRBLURRLRUBLRDDFDLFUFUFFDBRDUBRUFLLFDDBFLUBLRBD'

void receive_solution(void) {
    // 1. Acknowledge the 'S' (Start) command so Python begins sending moves
    UART2_SendByte('A');

    while (1) {
        // 2. Wait for the next character from Python
        uint8_t move = UART2_ReceiveByte();

        // 3. Check if it is the end of the sequence
        if (move == '-') {
            UART2_SendByte('A'); // ACK the end command
            break;               // Break out of the while loop, solution complete!
        }

        // 4. Interpret the move and physically turn the motor
        // NOTE: This function needs to block until the physical motor stops moving!
        // execute_motor_move(move);

        // 5. Send ACK to tell Python "Motor finished, send the next move"
        UART2_SendByte('A');
    }
}

// void read_cube_face(){
//     //TO DO 

//     return {1, 2, 3, 4, 5, 6, 7, 8, 9}
// }

void UART2_protocol(void){
    uint8_t command = UART2_ReceiveByte();
    if (command == 'R'){
        // UART2_SendByte('A'); //Send ACK
        
        // uint8_t face_data[9] = read_cube_face();

        // UART2_SendFace(face_data);

        // //wait for ACK
        // uint8_t status = UART2_ReceiveByte();
        // if (status == 'A'){
        //     //rotate cube to next face
        // }else if (status == 'N'){
        //     //redo face scan
        // }
    }else if (command == 'S'){
        receive_solution();
    }else if (command == 'A'){
        execute_motor_move('R', 0);
    }else if (command == 'B'){
        execute_motor_move('R', 1);
    }
}

uint8_t UART2_ReceiveByte(void) {
    while ((USART2->SR & (1 << 5)) == 0); //Wait for RXNE (Bit 5)
    return USART2->DR;
}

void UART2_SendByte(uint8_t data){
    while ((USART2->SR & (1<<7)) == 0);
    USART2->DR = data;
}

void UART2_WriteChar(char ch){
    while ((USART2->SR & (1<<7)) == 0);
    USART2->DR = ch;
}

// void UART2_SendFace(uint8_t face[9]){
//     int sent[9] = {};

//     for(int i = 0; i < 9; i++;){
//         while((USART2->SR & (1<<7)) != 0){
//             //wait for register to be ready
//         }
//         USART2->DR = face[i];   
//     }
// }