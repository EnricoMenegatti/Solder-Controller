void initADC()
{
  	ADMUX = (0 << REFS1) | //VCC used as Voltage Reference
  			(0 << REFS0) | //VCC used as Voltage Reference
  			(1 << ADLAR) | //ADC Left Adjust Result
  			(0 << REFS2) | //VCC used as Voltage Reference
  			(0 << MUX3) | //Analog Channel
  			(0 << MUX2) | //Analog Channel
  			(0 << MUX1) | //Analog Channel
  			(0 << MUX0);  //Analog Channel

  	ADCSRA = (1 << ADEN) | //ADC Enable
  			 (0 << ADSC) | //ADC Start Conversion
  			 (0 << ADATE) | //ADC Auto Trigger Enable
  			 (0 << ADIF) | //ADC Interrupt Flag
  			 (0 << ADIE) | //ADC Interrupt Enable
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
  			(1 << ADC3D) | //Digital Input Disable
  			(0 << ADC1D) | //Digital Input Disable
  			(0 << AIN1D) |
  			(0 << AIN0D);

    sei();

    ADCSRA |= (1 << ADSC);
}


void readADC()
{
  if (!(ADCSRA & (1<<ADSC)))
  {
    switch (ADMUX & (1<<MUX0))
    {
      case 0: //ADC2 PB4
        ADC_CMD = ADCH;

  //Set MUX bit ADC3 PB3
        ADMUX |= (1 << MUX0);
        for(int i=0;i>=1000;i++)
        {
          
        }
        
  //Start Conversion
        ADCSRA |= (1 << ADSC);
        break;

      case 1: //ADC3 PB3
        ADC_TEMP = ADCH;

        //Set MUX bit ADC2 PB4
        ADMUX |= (1 << MUX1);
        ADMUX &=~ (1 << MUX0);
        for(int i=0;i>=1000;i++)
        {
          
        }

      //Start Conversion
        ADCSRA |= (1 << ADSC);
        break;

      default:
        ADC_raw = ADCH;
        //Set MUX bit ADC2 PB4
        ADMUX |= (1 << MUX1);
        ADMUX &=~ (1 << MUX0);
        for(int i=0;i>=1000;i++)
        {
          
        }

      //Start Conversion
        ADCSRA |= (1 << ADSC);
        break;
    }
  }
}
