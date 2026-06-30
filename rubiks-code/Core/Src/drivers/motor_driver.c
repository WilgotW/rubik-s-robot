#include "stm32f401xe.h"

void Driver_Init(void){
    //driver 2
    //clear bits for PA5 (STEP), PA6 (DIR), PA7 (EN)
    GPIOA->MODER &= ~((3U << (5 * 2)) | (3U << (6 * 2)) | (3U << (7 * 2))); 
    //Set to output
    GPIOA->MODER |=  ((1U << (5 * 2)) | (1U << (6 * 2)) | (1U << (7 * 2))); 

    //driver 1
    //Clear bits 
    GPIOB->MODER &= ~((3U << (6 * 2)) | (3U << (7 * 2)) | (3U << (8 * 2)));
    // Set to output
    GPIOB->MODER |=  ((1U << (6 * 2)) | (1U << (7 * 2)) | (1U << (8 * 2)));
    
    //Driver 1
    GPIOA->ODR &= ~(1U << 7);  //Pull EN (PA7) LOW
    GPIOA->ODR |=  (1U << 6);  //Set DIR (PA6) HIGH 

    //driver 2 
    GPIOB->ODR &= ~(1U << 8);  //Pull (PB8) LOW
    GPIOB->ODR |=  (1U << 7);  //Set DIR (PB7) HIGH 
}