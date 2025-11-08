/*
 * PCA_9685.h
 *
 *  Created on: Nov 1, 2025
 *      Author: aadithyamanoj
 */

#ifndef INC_PCA_9685_H_
#define INC_PCA_9685_H_

#include <stdint.h>
#include "main.h"


#define PCA9685ADDY (0x40)

/* Transfer statuses */
#define TRANSFER_CMPLT (0x00u)
#define TRANSFER_ERROR      (0xFFu)

#define DELAYTIME 1

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
#define bufferSize 2

 /*Prototype*/
    void setPWMFromDutyCycle(int Ledn, int dutyCycle);
    void setPWMFromBytes(int pinN, uint8_t onTimeL, uint8_t onTimeH, uint8_t offTimeL, uint8_t offTimeH);
    uint8_t TurnOnTimeL();
    uint8_t TurnOnTimeH();
    uint8_t TurnOffTimeH(int dutyCycle);
    uint8_t TurnOffTimeL(int dutyCycle);
    uint32_t writeBuffer(uint8_t buff[],uint32_t PCA9685Address);
    void writeByte(uint8_t chip_register, uint8_t value);

    // Init function, pass handle to which I2C peripheral you are using in your project (&hi2c1)
    void pca_init(I2C_HandleTypeDef* I2C_Handle);

#endif /* INC_PCA_9685_H_ */
