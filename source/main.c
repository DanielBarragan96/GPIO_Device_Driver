
#include "MK64F12.h"
#include "GPIO.h"
#include "GlobalFunctions.h"

#define GPIOB_OFF_CONST (0xFFFFFFFFU)
#define GPIOB_ON_CONST (0U)
#define DELAY_CONST 65000

GPIO_pinControlRegisterType pinControlRegisterGPIOBpin21 = GPIO_MUX1;
GPIO_pinControlRegisterType pinControlRegisterGPIOBpin22 = GPIO_MUX1;
GPIO_pinControlRegisterType pinControlRegisterGPIOCpin6 = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;


int main(void) {


	GPIO_clockGating(GPIO_B);
	GPIO_clockGating(GPIO_C);

	GPIO_pinControlRegister(GPIO_B,BIT21,&pinControlRegisterGPIOBpin21);
	GPIO_pinControlRegister(GPIO_B,BIT22,&pinControlRegisterGPIOBpin22);
	GPIO_pinControlRegister(GPIO_C,BIT6,&pinControlRegisterGPIOCpin6);


	GPIO_writePORT(GPIO_B, GPIOB_OFF_CONST);

	GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT21);
	GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT22);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT6);

	GPIO_writePORT(GPIO_B, GPIOB_ON_CONST);
	delay(DELAY_CONST);
	GPIO_writePORT(GPIO_B, GPIOB_OFF_CONST);


	for (;;) {

		if(!GPIO_readPIN(GPIO_C, BIT6))
		{
			GPIO_clearPIN(GPIO_B, BIT21);
			delay(DELAY_CONST);
			GPIO_setPIN(GPIO_B, BIT21);
			delay(DELAY_CONST);
			GPIO_clearPIN(GPIO_B, BIT22);
			delay(DELAY_CONST);
			GPIO_setPIN(GPIO_B, BIT22);
		}

		}

    return 0 ;
}
