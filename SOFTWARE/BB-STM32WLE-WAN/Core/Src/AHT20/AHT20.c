#include "AHT20.h"

void AHT20_Begin()
{
	unsigned char status=0x71;
	unsigned char cmd=0xBE;
	unsigned char rcv_data[2];

	HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDR, &status, 1, 200);
	HAL_Delay(1);

	HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDR | 1, &rcv_data[0], 1, 500);

	if ((rcv_data[0] & 0x8) != 0x8)
		HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDR, &cmd, 1, 200);
}

void AHT20_Start(void)
{

	unsigned char snd_data[] = { 0xac,0x33,0x00 };
	unsigned char rcv_data[10];

	/* HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout) */
	HAL_I2C_Master_Transmit(&hi2c1, AHT20_ADDR, &snd_data[0], sizeof(snd_data)/sizeof(snd_data[0]), 500);

	do
	{
		HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDR | 1, &rcv_data[0], 1, 500);
		HAL_Delay(10);
	}
	while((rcv_data[0] & 0x80) != 0);

}

double AHT20_ReadData(float *h, float *t)
{
	unsigned char str[10];

	AHT20_Start();

	HAL_I2C_Master_Receive(&hi2c1, AHT20_ADDR | 1, &str[0], 6, 500);

	if (str[0] & 0x80)
		return 0;

	unsigned long __humi = 0;
	unsigned long __temp = 0;

	__humi = str[1];
	__humi <<= 8;
	__humi += str[2];
	__humi <<= 4;
	__humi += str[3] >> 4;

	*h = ((float)__humi/1048576.0) * 100;

	__temp = str[3]&0x0f;
	__temp <<=8;
	__temp += str[4];
	__temp <<=8;
	__temp += str[5];

	*t = (float)__temp/1048576.0*200.0-50.0;

	return 1;
}
