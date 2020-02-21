void initTIMER0() //Timer to set Output value
{
    /*  single time[s] = (1 / (clock[hz] / prescaler)) * 2
    single time = (1 / (16000000 / 1024)) * 2 = 0,000128ms
    prescaler = clock[hz] * single time[s]
    final time = OCR1C * ((1 / (clock[hz] / prescaler)) * 2 )
    final time = 156 * 0,000128 = 0,019968ms
    REQUEST TIME = final time * counter
    REQUEST TIME = 0,019968 * 501 = 10,003968ms
    */
    GTCCR = (0 << TSM) |
            (0 << PSR0); //Prescaler Reset Timer/Counter0

    TCCR0A = (0 << COM0A1) | //Set normal mode
             (0 << COM0A0) | //Set normal mode
             (0 << COM0B1) | //Set normal mode
             (0 << COM0B0) | //Set normal mode
             (0 << WGM01) | //Set normal mode
             (0 << WGM00);  //Set normal mode

    TCCR0B = (0 << FOC0A) | //Force Output Compare A
             (0 << FOC0B) | //Force Output Compare B
             (0 << WGM02) | //Set normal mode
             (1 << CS02) | //Set clocl prescale to 1024
             (0 << CS01) | //Set clocl prescale to 1024
             (1 << CS00);  //Set clocl prescale to 1024

    OCR0A = 156; //Compare match value 

    TIMSK = (1 << OCIE0A) | //Compare Match A Interrupt Enable
            (0 << OCIE0B) | //Compare Match B Interrupt Enable
            (0 << TOIE0); //Overflow Interrupt Enable
}

void initTIMER1()
{
    //Set PWM fast mode
    PLLCSR |= (1 << PLLE);               //Enable PLL (64 MHz)
    _delay_us(100);                      //Wait for a steady state
    while (!(PLLCSR & (1 << PLOCK)));    //Ensure PLL lock
    PLLCSR |= (1 << PCKE);               //Enable PLL as clock source for timer 1

    //Set PWM register
    TCCR1 = (0 << CTC1) | //Clear Timer/Counter on Compare Match
            (1 << PWM1A) | //Pulse Width Modulator A Enable PB1
            (1 << COM1A1) | //OC1A cleared on compare match. Set when TCNT1 = $00
            (0 << COM1A0) | //OC1A cleared on compare match. Set when TCNT1 = $00
            (0 << CS13) | //No clock prescale
            (0 << CS12) | //No clock prescale
            (0 << CS11) | //No clock prescale
            (1 << CS10);  //No clock prescale

    GTCCR = (0 << PWM1B) | //Pulse Width Modulator B Enable
            (0 << COM1A1) | //OC1A not connected
            (0 << COM1A0) | //OC1A not connected
            (0 << FOC1B) | //Force Output Compare Match 1B
            (0 << FOC1A) | //Force Output Compare Match 1B
            (0 << PSR1); //Prescaler Reset Timer/Counter1

    OCR1C = 0xFF; //Set compare match value

    TIMSK = (0 << OCIE1A) | //Timer/Counter1 Output Compare Interrupt Enable
            (0 << OCIE1B) | //Timer/Counter1 Output Compare Interrupt Enable
            (0 << TOIE1); //Timer/Counter1 Overflow Interrupt Enable
}


ISR(TIMER0_COMPA_vect)
{
    cli();
    if (Timer0_cont >= 500)
    {
        OCR1A = Output; //Write PWM value
        Timer0_cont = 0;
    }

    Timer0_cont ++;
    TCNT1 = 2; //preset timer register
    sei();
}
