
#include "MK64F12.h"
#include "GPIO.h"
#include "GPIO.c"
#include "GlobalFunctions.h"

#define GPIOB_OFF_CONST (0xFFFFFFFFU)
#define GPIOB_ON_CONST (0U)
#define DELAY_CONST 65000

GPIO_pinControlRegisterType pinControlRegisterGPIOBpin21 = GPIO_MUX1; //Se usa para activar los pines del MUX1
GPIO_pinControlRegisterType pinControlRegisterGPIOBpin22 = GPIO_MUX1;
GPIO_pinControlRegisterType pinControlRegisterGPIOCpin6 = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;


int main(void) {

//Configuración de la K64
	GPIO_clockGating(GPIO_B); //Inicia reloj del puerto B
	GPIO_clockGating(GPIO_C); //Inicia reloj del puerto C

	//// Activa los pins para lios LEDs (PCR)
	GPIO_pinControlRegister(GPIO_B,BIT21,&pinControlRegisterGPIOBpin21);
	GPIO_pinControlRegister(GPIO_B,BIT22,&pinControlRegisterGPIOBpin22);
	GPIO_pinControlRegister(GPIO_C,BIT6,&pinControlRegisterGPIOCpin6);


	GPIO_writePORT(GPIO_B, GPIOB_OFF_CONST);//Escribe 32 unos en el puerto B, apaga tod el puerto (TODO Falta implementar?)

	GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT21);// El pin 21 del puerto B se configura como salida (PDDR) (TODO Falta implementar?)
	GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT22);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_INPUT,BIT6);

	GPIO_writePORT(GPIO_B, GPIOB_ON_CONST);//Escribe 32 ceros en el puerto B, apaga tod el puerto
	delay(DELAY_CONST); // Delay
	GPIO_writePORT(GPIO_B, GPIOB_OFF_CONST);//Escribe 32 unos  en el puerto B, apaga tod el puerto


	for (;;) {//TODO faltan condiciones

		if(!GPIO_readPIN(GPIO_C, BIT6))
		{
			//Creo que lo que intenta hacer es si está prendido el LED verde (Puerto C) prende el LED pin 21, lo apaga, y luego prende y apaga el LED del pin 22
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
