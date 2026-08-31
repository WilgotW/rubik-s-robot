#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>

void Driver_Init(void);
void execute_motor_move(uint8_t move, uint8_t motor); 

#endif