#include "PCA_9685.h"
/* ========================================
 *
 * Driver for PCA9685
 *
 * Name I2C Block in Top Design "I2C"
 *
 * Written by Dupri Chipman and Davis Sauer
 *
 *
 * Ported to STM32 by Aadithya Manoj
 * ========================================
*/


static I2C_HandleTypeDef* PCA_I2C_Handle;

void pca_init(I2C_HandleTypeDef* I2C_Handle){
//    I2C_Start(); called in main in an stm32 project
//    I2C_Enable();
	PCA_I2C_Handle = I2C_Handle;
    uint8_t mode_buf[2] = {0,0b10010000};  // set sleep mode
    writeBuffer(mode_buf, PCA9685ADDY);

    uint8_t freq_buf[2] = {254, 121};      // set frequency to 50Hz
    writeBuffer(freq_buf, PCA9685ADDY);

    uint8_t mode_buf1[2] = {0,0b10000000}; // set to unsleep
    writeBuffer(mode_buf1, PCA9685ADDY);
}

/*Writes a single byte over i2c*/
void writeByte(uint8_t chip_register, uint8_t value){
     uint8_t buf[2] = {chip_register, value};
     writeBuffer(buf, PCA9685ADDY);
}

/*Casting delayTime as uint8_t gets rid of the four left most significant bits*/
uint8_t TurnOnTimeL(){
           int delayTime = DELAYTIME; /*This ammounts to 41 ticks before turn on*/
           //dutyCycle = (4095*dutyCycle)/100;
            delayTime = (4095*delayTime)/100 - 1;
        return delayTime;
}

/*Shifting to the right keeps the four most signifcant bits but gets rid of 8 least significant digits */
uint8_t TurnOnTimeH(){
    int delayTime = DELAYTIME;
    delayTime = (4095*delayTime)/100 - 1;
    delayTime = delayTime >> 8;
        return delayTime;
}

uint8_t TurnOffTimeL(int dutyCycle){
    int delayTime = DELAYTIME;
    int offTime=0;
    if(delayTime+dutyCycle<=100){
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle;
    } else {
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle - 4096;
    offTime = offTime;
    }
       return offTime;}

uint8_t TurnOffTimeH(int dutyCycle){
    int delayTime = DELAYTIME;
    int offTime = 0; //initialized because program giving a warning
    if(delayTime+dutyCycle<=100){
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle;
    } else {
    delayTime = (4095*delayTime)/100 - 1;
    dutyCycle = (4095*dutyCycle)/100;
    offTime = delayTime + dutyCycle - offTime;
    }
       return offTime >> 8;}

uint32_t writeBuffer(uint8_t *buff, uint32_t PCA9685Address){
     HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(PCA_I2C_Handle, PCA9685Address <<1 , buff, bufferSize, HAL_MAX_DELAY);

    return (status == HAL_OK) ? TRANSFER_CMPLT : TRANSFER_ERROR;
}

void setPWMFromBytes(int pinN, uint8_t onTimeL, uint8_t onTimeH, uint8_t offTimeL, uint8_t offTimeH){
    uint8_t registerNum = 0;
    registerNum = 0x06 + pinN * 4;
    writeByte(registerNum, onTimeL);
    writeByte(registerNum+1, onTimeH);
    writeByte(registerNum+2, offTimeL);
    writeByte(registerNum+3, offTimeH);
}

void setPWMFromDutyCycle(int pinN, int dutyCycle){
    uint8_t registerNum = 0;
    registerNum = 0x06 + pinN * 4;

    writeByte(registerNum, TurnOnTimeL());
    writeByte(registerNum+1, TurnOnTimeH());
    writeByte(registerNum+2, TurnOffTimeL(dutyCycle));
    writeByte(registerNum+3, TurnOffTimeH(dutyCycle));
}







