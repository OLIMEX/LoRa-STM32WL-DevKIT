#ifndef	_AHT20_H_
#define	_AHT20_H_

#include "stm32wlxx_hal.h"

#define AHT20_ADDR (0x38<<1)
#define MAX_BUFFER 20

extern I2C_HandleTypeDef hi2c1;

void AHT20_Begin();
void AHT20_Start(void);
double AHT20_ReadData(float *h, float *t);

#endif
