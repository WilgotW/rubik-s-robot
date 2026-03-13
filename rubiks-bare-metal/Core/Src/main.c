#include "stm32f4xx.h"

int blink_user_led(void){
  //let's first blink the user LED. I can see in in the Pinout configuration tab in the
  //STM32CubeMX program that the user LED is connected to PA5, which stands for: Port A Pin 5.
  
  //The first thing we need to do is giving clock access to this pin. Without it, the pin won't work.  
  //In the datasheet i found the memory map. By scrolling down we can see that the GPIOA port
  //is inside the AHB1 bus. In the refernce manual there's and dedicated section for enabling clock
  //access to AHB1 peripherals. In the diagram, we can se that we need to set bit 0 to the value 1.
  RCC->AHB1ENR |= (1 << 0);
  //OR operation with the current register and a 1 shiften 0 times to the left.  
}
int main(void){
  
  while (1){

  }
}