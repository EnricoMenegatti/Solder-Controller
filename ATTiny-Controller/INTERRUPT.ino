void initINTERRUPT()
{
/*  single time[s] = 1 / (clock[hz] / prescaler)
    single time = 1 / (16000000 / 8192) = 0.512ms
    prescaler = clock[hz] * single time[s]
    final time = OCR1C * (1 / (clock[hz] / prescaler))
    final time = 10 * 0.512 = 5.12ms
*/
  TCCR1 |= (1 << CTC1);  // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) & (0 << CS10); //clock prescaler 1024
  OCR1C = 10; // compare match value 
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}


ISR(TIMER1_COMPA_vect)
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

  analogWrite(PWM_pin, Output);
  print_output = Output;
}
