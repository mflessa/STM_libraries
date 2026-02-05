/* 
 * Function prototypes for the DRV8424/25 stepper motor driver. Defined here are the functions
 * I would expect to be available for a programmer to call to interface with the driver. T
 *
 *
 */
#pragma once
#include <stdint.h>
#include "stm32g4xx_hal.h" // i think this is the correct file but check when you initialize a project

typedef struct {
	TIM_HandleTypeDef *htim_step;
	uint32_t tim_step_channel;
	GPIO_TypeDef *IN1_port;
	uint16_t IN1_pin;
    GPIO_TypeDef *IN2_port;
	uint16_t IN2_pin;
    GPIO_TypeDef *IN3_port;
	uint16_t IN3_pin;
    GPIO_TypeDef *IN4_port;
	uint16_t IN4_pin;

	volatile int32_t steps_remaining;
	uint8_t current_step_index;
	uint8_t direction;
} ULN2003_Handle;


// Initializes handle for the driver that holds  all hardware details (pwm channel, pin assignments).
void ULN2003_Init(ULN2003_Handle *hdrv);

// Drive the motor a given number of steps with the direction indicated by the sign of param steps, at the given frequency. 
uint8_t ULN2003_DriveSteps(ULN2003_Handle *hdrv, int32_t steps, uint32_t freq); 

// Stop motor regardless of steps remaining.
uint8_t ULN2003_Stop(ULN2003_Handle *hdrv);

// Those are the most important. After that is implemented and tested, consider adding more like sleep mode, microstepping modes, current limiting, and more.
