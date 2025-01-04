#include "msp.h"

int main(void) {
	int currentLedIsRed = 1;
	int currentLedIsRGB = 0;
	
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; 
	
	P1SEL0 &= (uint8_t)(~((1<<4)|(1<<1)|(1<<0))); 
	P1SEL1 &= (uint8_t)(~((1<<4)|(1<<1)|(1<<0)));
	
	P2SEL0 &= (uint8_t)(~((1<<2)|(1<<1)|(1<<0)));
	P2SEL1 &= (uint8_t)(~((1<<2)|(1<<1)|(1<<0)));
	
	P1DIR &= (uint8_t)((~((1<<4)|(1<<1))));
	P1DIR |= (uint8_t)((1<<0));
	
	P2DIR |= (uint8_t)(((1<<2)|(1<<1)|(1<<0)));
	
	P1REN |= (uint8_t)((((1<<4)|(1<<1))));
	
	P1OUT |= (uint8_t)((((1<<4)|(1<<1))));
	P1OUT &= ~(uint8_t)(1<<0);
	
	P2OUT &= ~(uint8_t)((1<<2)|(1<<1)|(1<<0));
	
	
	// For RGB
	TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); 
	TA0CTL &= (uint16_t)(~(1<<0)); 
	TA0CCR0 = (uint16_t)(32767); // init for Red
	TA0CTL |= (uint16_t)((1<<1)); 
	TA0CTL |= (uint16_t)((1<<8)); 
	
	
	//P1.1 configured as falling edge event (active low switches)
	P1IES |= (uint8_t)((1<<4)|(1<<1));
	// clear flag1 (so we don’t interrupt prematurely)
	P1IFG &= (uint8_t)~((1<<4)|(1<<1));
	//arm (enable) interrupt on P1.1
	P1IE |= (uint8_t)((1<<4)|(1<<1));
	
	// Config NVIC
	NVIC_SetPriority(PORT1_IRQn, 2);
	NVIC_ClearPendingIRQ(PORT1_IRQn);
	NVIC_EnableIRQ(PORT1_IRQn);
	
	NVIC_SetPriority(TA0_N_IRQn, 3);
	NVIC_ClearPendingIRQ(TA0_N_IRQn);
	NVIC_EnableIRQ(TA0_N_IRQn);
	


	
	
	//Enable interrupts globally
	__ASM("CPSIE I");

	while(1){
	
	}
}


void PORT1_IRQHandler(void)  {
	static int currentLedIsRed = 1;


	//Test for pin 1 interrupt flag
	if (((P1IFG & (uint8_t)(1<<1)) != 0))
	{
		// clear RED and RGB LED
		P1OUT &= ~(uint8_t)(1<<0);
		P2OUT &= ~(uint8_t)((1<<2)|(1<<1)|(1<<0));
		TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); // stop timer
		
		//Yes, pin 1: clear flag (ack)
		P1IFG &= (uint8_t)~(1<<1);
		//do stuff
		if (currentLedIsRed == 1) {
			currentLedIsRed = 0;
		} else {
			currentLedIsRed = 1;
		}
	}
	//pin 4
	else if ((P1IFG & (uint8_t)(1<<4)) != 0){
		//Yes, pin 4: clear flag (ack)
		P1IFG &= (uint8_t)~(1<<4);
		
		if (currentLedIsRed == 0) {
			TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); // stop timer
			TA0CCR0 = (uint16_t)(65535);
			TA0CTL |= (uint16_t)(1<<4); // start timer
		}
		else {
			TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); // stop timer
			TA0CCR0 = (uint16_t)(32767);
			TA0CTL |= (uint16_t)(1<<4); // start timer
		}
	}
}

// RGB
void TA0_N_IRQHandler(void) {
	// count to 5 and reset and continue	
	static uint8_t state;
	//clear interrupt flag
	TA0CTL &= (uint16_t)(~BIT0);
	
	if (TA0CCR0 == (uint16_t) (32767)) {
		// Toggle RED
		P1OUT ^= (uint8_t) (1<<0); 
	}
	else {
		// Increment state
		state = P2->OUT;
		state++;
		P2->OUT = state;
	}
}





