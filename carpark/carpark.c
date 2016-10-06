#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define F_CPU 16000000uL
#define sbi(sfr,bit) (_SFR_BYTE(sfr)|=_BV(bit))

int main (void)
{
	unsigned int ADCResult;
	char data;
	char arr[4] = "000";
	
	//pin setting

	DDRB = (DDRB |= (1<<PB0));
	DDRC = (DDRC |= (1<<PC5));
	PORTB = (PORTB | (1<<PORTB0));
	_delay_ms(1000);
	PORTB = (PORTB & ~(1<<PORTB0));
	PORTC = (PORTC | (1<<PORTC5));
	
	//sleep setting
	
	MCUCR = (1<<SE) | (1<<SM1);


	//ADC

	ADMUX = 0b01000001; //((0<<REFS1) | (0<<REFS0)) | ((0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (1<<MUX0)) <-- AVcc with external capacitor at AREFpin & ADC1;
	ADCSRA = 0b10100111; //ADC Enable, Free Running Mode, Prescaler 128
	sbi(ADCSRA, ADSC); // ADC START

	while(1) {
		sleep_disable();
		ADCResult = ADC;
		if (ADCResult > 300) {
			PORTB = 0x01;
		}
		else if (ADCResult < 300) {
			PORTB = 0x00;
		}
		
		_delay_ms(2000);
		sleep_cpu();
	}
	return 0;
}
