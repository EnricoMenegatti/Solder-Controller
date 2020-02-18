void initADC()
{
//The voltage reference for the ADC from VCC
	ADMUX &= (0 << REFS2) & (0 << REFS1) & (0 << REFS0);
//Do not left shift result (for 10-bit values)
	ADMUX &= (0 << ADLAR);
//Set prescaler to 128
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
//ADC Enable
	ADCSRA |= (1 << ADEN);
}

int readADC(int pin)
{
	int ADC_low, ADC_raw;

//Reset MUX bit
	ADMUX &= (0 << MUX3) & (0 << MUX2) & (0 << MUX1) & (0 << MUX0);
//Set MUX bit
	ADMUX |= pin;
//Start Conversion
	ADCSRA |= (1 << ADSC);
	
//Wait conversion end
	while(ADSC);

//Get the sample value from ADCL
	ADC_low = ADCL;
//Add lower byte and higher byte
	ADC_raw = (ADCH << 8) | ADC_low;

	return(ADC_raw);
}
