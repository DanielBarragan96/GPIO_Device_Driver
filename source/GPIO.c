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

//TODO Las que tiene USED si las usamos
void GPIO_writePORT(GPIO_portNameType portName, uint32 Data ){
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				PORTA = Data;
				break;
			case GPIO_B:/** GPIO B is selected*/
				PORTB = Data;
				break;
			case GPIO_C:/** GPIO C is selected*/
				PORTC = Data;
				break;
			case GPIO_D:/** GPIO D is selected*/
				PORTD = Data;
				break;
			case GPIO_E: /** GPIO E is selected*/
				PORTE = Data;
			default:/**If doesn't exist the option*/
				return(FALSE);
			break;
			}
}//USED
uint32 GPIO_readPORT(GPIO_portNameType portName){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						return PORTA;
						break;
					case GPIO_B:/** GPIO B is selected*/
						return PORTB;
						break;
					case GPIO_C:/** GPIO C is selected*/
						return PORTC;
						break;
					case GPIO_D:/** GPIO D is selected*/
						return PORTD;
						break;
					case GPIO_E: /** GPIO E is selected*/
						return PORTE;
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
					return PORTA[PIN];
					break;
				case GPIO_B:/** GPIO B is selected*/
					return PORTB[PIN];
					break;
				case GPIO_C:/** GPIO C is selected*/
					return PORTC[PIN];
					break;
				case GPIO_D:/** GPIO D is selected*/
					return PORTD[PIN];
					break;
				case GPIO_E: /** GPIO E is selected*/
					return PORTE[PIN];
				default:/**If doesn't exist the option*/
					return(FALSE);
				break;
				}
}//USED
void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){

}//USED
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){

}//USED
void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin);
void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						return PORTA->PDDR = direction;
						break;
					case GPIO_B:/** GPIO B is selected*/
						return PORTA->PDDR = direction;
						break;
					case GPIO_C:/** GPIO C is selected*/
						return PORTA->PDDR = direction;
						break;
					case GPIO_D:/** GPIO D is selected*/
						return PORTA->PDDR = direction;
						break;
					case GPIO_E: /** GPIO E is selected*/
						return PORTA->PDDR = direction;
					default:/**If doesn't exist the option*/
						return(FALSE);
					break;
					}
}
void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	switch(portName)
					{
					case GPIO_A:/** GPIO A is selected*/
						PORTA->PDDR[PIN] = State;
						break;
					case GPIO_B:/** GPIO B is selected*/
						PORTB->PDDR[PIN] = State;
						break;
					case GPIO_C:/** GPIO C is selected*/
						PORTC->PDDR[PIN] = State;
						break;
					case GPIO_D:/** GPIO D is selected*/
						PORTD->PDDR[PIN] = State;
						break;
					case GPIO_E: /** GPIO E is selected*/
						PORTE->PDDR[PIN] = State;
					default:/**If doesn't exist the option*/
						return(FALSE);
					break;
					}
}//USED




