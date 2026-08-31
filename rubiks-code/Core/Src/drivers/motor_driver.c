#include "stm32f401xe.h"
#include <stdint.h>

//NOTE: Update this to Hardware timers instead
void step_delay(volatile uint32_t count) {
    while(count--) {
        __NOP(); 
    }
}

void execute_motor_move(uint8_t move, uint8_t motor){
    
    //ensure enable pin is LOW
    //GPIOA->ODR &= ~(1U << 7);
    
    step_delay(5000);

    //set direction. R = clockwise, r = counter-clockwise
    // if(move == 'R'){
    //     GPIOA->ODR |= (1U << 6); //HIGH
    // }else if (move = 'r'){
    //     GPIOA->ODR &= ~(1U << 6); //LOW
    // }
    
    //Generate steps
    int steps_90_deg = 400;
    for (int i = 0; i < steps_90_deg; i++){
        if(motor == 0){
            GPIOA->ODR |= (1U<< 5);
            step_delay(3000);

            GPIOA->ODR &= ~(1U << 5);
            step_delay(3000);
        }else if (motor == 1){
            GPIOB->ODR |= (1U << 6);
            step_delay(3000);

            GPIOB->ODR &= ~(1U << 6);
            step_delay(3000);
        }
    }

    // if(motor == 1){
    //     for (int y = 0; y < 50; y++){
    //         GPIOB->ODR |= (1U << 6);
    //         step_delay(3000);

    //         GPIOB->ODR &= ~(1U << 6);
    //         step_delay(3000);
    //     }
    // }
}



void Driver_Init(void){
    //driver 1
    //clear bits for PA5 (STEP), PA6 (DIR), PA7 (EN)
    GPIOA->MODER &= ~((3U << (5 * 2)) | (3U << (6 * 2)) | (3U << (7 * 2))); 
    //Set to output
    GPIOA->MODER |=  ((1U << (5 * 2)) | (1U << (6 * 2)) | (1U << (7 * 2))); 

    //driver 2
    //Clear bits 
    GPIOB->MODER &= ~((3U << (6 * 2)) | (3U << (7 * 2)) | (3U << (8 * 2)));
    //Set to output
    GPIOB->MODER |=  ((1U << (6 * 2)) | (1U << (7 * 2)) | (1U << (8 * 2)));
    
    //Driver 1
    GPIOA->ODR &= ~(1U << 7);  //Pull EN (PA7) LOW
    GPIOA->ODR |=  (1U << 6);  //Set DIR (PA6) HIGH 

    //driver 2 
    GPIOB->ODR &= ~(1U << 8);  //Pull (PB8) LOW
    GPIOB->ODR |=  (1U << 7);  //Set DIR (PB7) HIGH 
}