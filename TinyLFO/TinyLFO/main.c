#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t phase_accumulator =0;
volatile uint8_t tuning_word =70;

int main(void)
{
	//setup output led
	DDRA =0xff;
	//PORTA |= (1<<PORTA0);
	//PORTA |= (1<<PORTA1);
	//PORTA |= (1<<PORTA2);
	//PORTA |= (1<<PORTA3);
	//PORTA |= (1<<PORTA4);
	//PORTA |= (1<<PORTA5);
	//PORTA |= (1<<PORTA6);
	//PORTA |= (1<<PORTA7);


	//enable timer interrupt
	TIMSK0 |= (1 << TOIE0);
	TCCR0B |=(1<< CS00);

	//enable interrupts
	sei(); 
    
    while (1) 
    {
    }
}

//isr
SIGNAL (TIM0_OVF_vect)
{

 	phase_accumulator+=tuning_word;
 	PORTA = phase_accumulator >>8 ;
	
}
