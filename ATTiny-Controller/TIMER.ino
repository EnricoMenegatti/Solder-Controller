void initTIMER0()
{
/*  single time[s] = (1 / (clock[hz] / prescaler)) * 2
    single time = (1 / (16000000 / 1024)) * 2 = 0,000128ms
    prescaler = clock[hz] * single time[s]
    final time = OCR1C * ((1 / (clock[hz] / prescaler)) * 2 )
    final time = 156 * 0,000128 = 0,019968ms
    REQUEST TIME = final time * counter
    REQUEST TIME = 0,019968 * 501 = 10,003968ms
*/
  TCCR0A = 0x00; //Set normal mode
  TCCR0B |= (1 << CS02) | (1 << CS00); //Set clocl prescale to 1024
  OCR0A = 156; //Compare match value 
  TIMSK |= (1 << OCIE0A); //Enable compare match A interrupt
}

void initTIMER1()
{
//Set PWM fast mode
  PLLCSR |= (1 << PLLE);               //Enable PLL (64 MHz)
  _delay_us(100);                      //Wait for a steady state
  while (!(PLLCSR & (1 << PLOCK)));    //Ensure PLL lock
  PLLCSR |= (1 << PCKE);               //Enable PLL as clock source for timer 1

//Set PWM register
  TCCR1 |= (1 << PWM1A); //Pulse Width Modulator A Enable PB1
  TCCR1 |= (1 << COM1A1); //Clear on match with OCR1C
  TCCR1 |= (1 << CS10); //No clock prescale
  OCR1C = 0xFF; //Set compare match value
}


ISR(TIMER0_COMPA_vect)
{
//utilizzo il PID solo all'interno del range impostato  
  if (Setpoint < Input - TEMPERATURE_GAP)
  {
    Output = 0;
  }
  
  else if (Setpoint > Input + TEMPERATURE_GAP)
  {
    Output = 255;
  }

  else
  {
    Output = PID(Setpoint, Input);
  }

  OCR1A = Output; //Write PWM value
  print_output = Output;

  TCNT1 = 2; //preset timer register
}
