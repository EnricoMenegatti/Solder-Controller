void initADC()
{
	ADMUX = (0 << REFS1) | //VCC used as Voltage Reference 
			(0 << REFS0) | //VCC used as Voltage Reference
			(0 << ADLAR) | //ADC Right Adjust Result
			(0 << REFS2) | //VCC used as Voltage Reference
			(0 << MUX3) | //Analog Channel adc2 - PB4
			(0 << MUX2) | //Analog Channel adc2 - PB4
			(1 << MUX1) | //Analog Channel adc2 - PB4
			(0 << MUX0);  //Analog Channel adc2 - PB4

	ADCSRA = (1 << ADEN) | //ADC Enable
			 (0 << ADSC) | //ADC Start Conversion
			 (1 << ADATE) | //ADC Auto Trigger Enable
			 (0 << ADIF) | //ADC Interrupt Flag
			 (1 << ADIE) | //ADC Interrupt Enable
			 (1 << ADPS2) | //ADC Prescale 128
			 (1 << ADPS1) | //ADC Prescale 128 
			 (1 << ADPS0);  //ADC Prescale 128

	ADCSRA = (0 << BIN) | //Bipolar Input Mode
			 (0 << ACME) |
			 (0 << IPR) | //Input Polarity Reversal
			 (0 << ADTS2) | //ADC Auto Trigger Source - Free Running mode
			 (0 << ADTS1) | //ADC Auto Trigger Source - Free Running mode
			 (0 << ADTS0);  //ADC Auto Trigger Source - Free Running mode

	DIDR0 = (0 << ADC0D) | //Digital Input Disable 
			(1 << ADC2D) | //Digital Input Disable
			(0 << ADC3D) | //Digital Input Disable
			(0 << ADC1D) | //Digital Input Disable
			(0 << AIN1D) |
			(0 << AIN0D);

	sei();

	ADCSRA |= (1 << ADSC);
}


ISR(ADC_vect)
{
	int temp = ADCL;
  	ADC_raw = (ADCH << 8) | temp;
}