void initADC()
{
  	ADMUX = (0 << REFS1) | //VCC used as Voltage Reference
  			(0 << REFS0) | //VCC used as Voltage Reference
  			(0 << ADLAR) | //ADC Right Adjust Result
  			(0 << REFS2) | //VCC used as Voltage Reference
  			(0 << MUX3) | //Analog Channel
  			(0 << MUX2) | //Analog Channel
  			(0 << MUX1) | //Analog Channel
  			(0 << MUX0);  //Analog Channel

  	ADCSRA = (1 << ADEN) | //ADC Enable
  			 (0 << ADSC) | //ADC Start Conversion
  			 (0 << ADATE) | //ADC Auto Trigger Enable
  			 (0 << ADIF) | //ADC Interrupt Flag
  			 (1 << ADIE) | //ADC Interrupt Enable
  			 (0 << ADPS2) | //ADC Prescale 128
  			 (0 << ADPS1) | //ADC Prescale 128
  			 (0 << ADPS0);  //ADC Prescale 128

  	ADCSRB = (0 << BIN) | //Bipolar Input Mode
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


void readADC()
{
//Set MUX bit ADC2 PB4
  ADMUX = (0 << MUX3) |
          (0 << MUX2) |
          (1 << MUX1) |
          (0 << MUX0);

//Start Conversion
  ADCSRA |= (1 << ADSC);
}


ISR(ADC_vect)
{
    int temp;
    switch (ADMUX)
    {
      case 0x02:
        temp = ADCL;
      	pot = (ADCH << 8) | temp;

  //Set MUX bit ADC3 PB3
        ADMUX = (0 << MUX3) |
                (0 << MUX2) |
                (1 << MUX1) |
                (1 << MUX0);
  //Start Conversion
        ADCSRA |= (1 << ADSC);
        break;

      case 0x03:
        temp = ADCL;
      	sol = (ADCH << 8) | temp;
        break;

      default:
        temp = ADCL;
        ADC_raw = (ADCH << 8) | temp;
        break;
    }
}
