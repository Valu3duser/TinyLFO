#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

volatile uint16_t phase_accumulator =0;
volatile uint8_t tuning_word =70;
volatile uint8_t table_index = 0;
volatile uint8_t temp =0;
const uint8_t sin_table[256] PROGMEM= {128,131,134,137,140,143,146,149,
	152,155,158,162,165,167,170,173,
	176,179,182,185,188,190,193,196,
	198,201,203,206,208,211,213,215,
	218,220,222,224,226,228,230,232,
	234,235,237,238,240,241,243,244,
	245,246,248,249,250,250,251,252,
	253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,254,253,
	253,252,251,250,250,249,248,246,
	245,244,243,241,240,238,237,235,
	234,232,230,228,226,224,222,220,
	218,215,213,211,208,206,203,201,
	198,196,193,190,188,185,182,179,
	176,173,170,167,165,162,158,155,
	152,149,146,143,140,137,134,131,
	128,124,121,118,115,112,109,106,
	103,100,97,93,90,88,85,82,
	79,76,73,70,67,65,62,59,
	57,54,52,49,47,44,42,40,
	37,35,33,31,29,27,25,23,
	21,20,18,17,15,14,12,11,
	10,9,7,6,5,5,4,3,
	2,2,1,1,1,0,0,0,
	0,0,0,0,1,1,1,2,
	2,3,4,5,5,6,7,9,
	10,11,12,14,15,17,18,20,
	21,23,25,27,29,31,33,35,
	37,40,42,44,47,49,52,54,
	57,59,62,65,67,70,73,76,
	79,82,85,88,90,93,97,100,
	103,106,109,112,115,118,121,124};

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


	//enable timer0 interrupt
	TIMSK0 |= (1 << TOIE0);
	TCCR0B |=(1<< CS00);

	//timer1 pwm
	//TCCR1A =(1<<WGM10)|(1<<COM1A0);
	//TCCR1B = (1<<WGM12)|(1<<CS10);
	TCCR1A |= (1<<COM0A1) | (1<<WGM10) ;
	TCCR1B |= (1<<CS10) | (1<<WGM12);
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
	table_index = phase_accumulator >>8;
	temp = sin_table[table_index] ;
	temp = &(sin_table[table_index]) ;
	temp = pgm_read_byte(&(sin_table[table_index]));
	OCR1A = temp;
 	//PORTA = temp;
}
