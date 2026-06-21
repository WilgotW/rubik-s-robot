


void Driver_Init(){
    //The NEMA17 has 


    //DRIVER 1, arm driver
    //clear bits
    GPIOA->MODER &= ~((3U << (5 * 2)) | (3U << (6 * 2)) | (3U << (7 * 2))); 
    //Set to Output
    GPIOA->MODER |=  ((1U << (5 * 2)) | (1U << (6 * 2)) | (1U << (7 * 2))); 

    //DRIVER 2, platform driver
    //clear bits



    //Initialize static pins
    GPIOA->ODR &= ~(1U << 7);  //Pull EN (PA7) LOW to energize the motor coils
    GPIOA->ODR |=  (1U << 6);  //Set DIR (PA6) HIGH (change to LOW to reverse direction)

}
