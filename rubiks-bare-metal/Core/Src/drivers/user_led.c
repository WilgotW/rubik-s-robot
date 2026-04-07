#include "led_blink.h"

void blink_user_led(void){
  GPIOA->ODR ^= (1 << 5);
  //toggle PA5 pin between 1 and 0 to blink the LED
}

void blink_loop(void){
  //let's first blink the user LED. I can see in in the Pinout configuration tab in the
  //STM32CubeMX program that the user LED is connected to PA5, which stands for: Port A Pin 5.
  
  //The first thing we need to do is giving clock access to this pin. Without it, the pin won't work.  
  //In the datasheet i found the memory map. By scrolling down we can see that the GPIOA port
  //is inside the AHB1 bus. In the refernce manual there's and dedicated section for enabling clock
  //access to AHB1 peripherals. In the diagram, we can se that we need to set bit 0 to the value 1.
  RCC->AHB1ENR |= (1 << 0);
  //OR operation between the AHB1EN register and the number 1 shiften 0 times to the left.  
  
  GPIOA->MODER &= ~(3 << 10);
  //clear mods register. 3 = 11 in binary

  GPIOA->MODER |= (1 << 10); 
  //set mode to output for PA5

  while (1){
    for(volatile int i = 0; i < 1000000; i++){} //delay between blinks
    blink_user_led();
  }
}
