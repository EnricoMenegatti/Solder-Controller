void initADC()
{
//The voltage reference for the ADC from VCC
//	ADMUX &= (0 << REFS2) & (0 << REFS1) & (0 << REFS0);
//Do not left shift result (for 10-bit values)
//	ADMUX |= (1 << ADLAR);
//Set prescaler to 128
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

 ADMUX |= (1 << MUX1);
//ADC Enable
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
  sei();
//  ADCSRB |= (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0);

  ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect)
{
  ADC_raw = (ADCH << 8) | ADCL;
}

int readADC(int pin)
{
//Reset MUX bit
//	ADMUX &= (0 << MUX3) & (0 << MUX2) & (0 << MUX1) & (0 << MUX0);
//Set MUX bit
	
//Start Conversion
	ADCSRA |= (1 << ADSC);
	
//Wait conversion end
//delay(10);
	while(ADCSRA & (1 << ADSC));

//Get value
	ADC_raw = (ADCH << 8) | ADCL;

	return(ADC_raw);
}
