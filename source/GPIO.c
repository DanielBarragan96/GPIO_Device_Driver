/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"

	GPIO_interruptFlags_t portName;

uint8 GPIO_getIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			return(portName.flagPortA);
			break;
		case GPIO_B:
			return(portName.flagPortB);
			break;
		case GPIO_C:
			return(portName.flagPortC);
			break;
		case GPIO_D:
			return(portName.flagPortD);
			break;
		case GPIO_E:
			return(portName.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}
	return(ERROR);
}

uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			portName.flagPortA = FALSE;
			break;
		case GPIO_B:
			portName.flagPortB = FALSE;
			break;
		case GPIO_C:
			portName.flagPortC = FALSE;
			break;
		case GPIO_D:
			portName.flagPortD = FALSE;
			break;
		case GPIO_E:
			portName.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{

	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}


void GPIO_writePORT(GPIO_portNameType portName, uint32 Data ){
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PSOR = Data;
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PSOR = Data;
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PSOR = Data;
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PSOR = Data;
				break;
			default: /** GPIO E is selected*/
				GPIOE->PSOR = Data;
			}
}//USED
uint32 GPIO_readPORT(GPIO_portNameType portName){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						return *(PORTA->PCR);
						break;
					case GPIO_B:/** GPIO B is selected*/
						return *(PORTB->PCR);
						break;
					case GPIO_C:/** GPIO C is selected*/
						return *(PORTC->PCR);
						break;
					case GPIO_D:/** GPIO D is selected*/
						return *(PORTD->PCR);
						break;
					case GPIO_E: /** GPIO E is selected*/
						return *(PORTE->PCR);
					default:/**If doesn't exist the option*/
						return(FALSE);
					break;
					}
			return(FALSE);
}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					return (PORTA->PCR[pin]);
					break;
				case GPIO_B:/** GPIO B is selected*/
					return (PORTB->PCR[pin]);
					break;
				case GPIO_C:/** GPIO C is selected*/
					return (PORTC->PCR[pin]);
					break;
				case GPIO_D:/** GPIO D is selected*/
					return (PORTD->PCR[pin]);
					break;
				case GPIO_E: /** GPIO E is selected*/
					return (PORTE->PCR[pin]);
				default:/**If doesn't exist the option*/
					return(FALSE);
				break;
				}
	return FALSE;
}//USED

void GPIO_setPIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				PORTA->PCR[pin] = BIT_ON;
				break;
			case GPIO_B:/** GPIO B is selected*/
				PORTB->PCR[pin] = BIT_ON;
				break;
			case GPIO_C:/** GPIO C is selected*/
				PORTC->PCR[pin] = BIT_ON;
				break;
			case GPIO_D:/** GPIO D is selected*/
				PORTD->PCR[pin] = BIT_ON;
				break;
			default: /** GPIO E is selected*/
				PORTE->PCR[pin]= BIT_ON;
			break;
			}
}

void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				PORTA->PCR[pin] = BIT_OFF;
				break;
			case GPIO_B:/** GPIO B is selected*/
				PORTB->PCR[pin] = BIT_OFF;
				break;
			case GPIO_C:/** GPIO C is selected*/
				PORTC->PCR[pin] = BIT_OFF;
				break;
			case GPIO_D:/** GPIO D is selected*/
				PORTD->PCR[pin] = BIT_OFF;
				break;
			default: /** GPIO E is selected*/
				PORTE->PCR[pin]= BIT_OFF;
			break;
			}
}

void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				if(PORTA->PCR[pin] == BIT_ON)
					PORTA->PCR[pin]= BIT_OFF;
				else PORTA->PCR[pin]= BIT_ON;
				break;
			case GPIO_B:/** GPIO B is selected*/
				if(PORTB->PCR[pin] == BIT_ON)
					PORTB->PCR[pin]= BIT_OFF;
				else PORTB->PCR[pin]= BIT_ON;
				break;
			case GPIO_C:/** GPIO C is selected*/
				if(PORTC->PCR[pin] == BIT_ON)
					PORTC->PCR[pin]= BIT_OFF;
				else PORTC->PCR[pin]= BIT_ON;
				break;
			case GPIO_D:/** GPIO D is selected*/
				if(PORTD->PCR[pin] == BIT_ON)
					PORTD->PCR[pin]= BIT_OFF;
				else PORTD->PCR[pin]= BIT_ON;
				break;
			default: /** GPIO E is selected*/
				if(PORTE->PCR[pin] == BIT_ON)
					PORTE->PCR[pin]= BIT_OFF;
				else PORTE->PCR[pin]= BIT_ON;
			break;
			}
}

void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						return GPIOA->PDDR = direction;
						break;
					case GPIO_B:/** GPIO B is selected*/
						return GPIOB->PDDR = direction;
						break;
					case GPIO_C:/** GPIO C is selected*/
						return GPIOC->PDDR = direction;
						break;
					case GPIO_D:/** GPIO D is selected*/
						return GPIOD->PDDR = direction;
						break;
					default:
						return GPIOE->PDDR = direction;
					break;
					}
}

void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						PORTA->PCR[pin] = State;
						break;
					case GPIO_B:/** GPIO B is selected*/
						PORTB->PCR[pin] = State;
						break;
					case GPIO_C:/** GPIO C is selected*/
						PORTC->PCR[pin] = State;
						break;
					case GPIO_D:/** GPIO D is selected*/
						PORTD->PCR[pin] = State;
						break;
					default:
						PORTE->PCR[pin] = State;
					break;
					}
}//USED



