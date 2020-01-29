int PID(int val_SET, int val_IN)
{
  /*La funzione PID è richiamata dall’interrupt del timer di sistema; la chiamata avviene ogni 10 msec., pertanto z-1 = 10 msec. La
  funzione PID riceve un valore intero che rappresenta il valore di consegna “val_SET “, la funzione restituisce un valore intero
  “val_OUT” che rappresenta il valore di riferimento per l’attuatore.
   Le variabili:
   float Upper_P_limit, Upper_I_limit, Upper_D_limit, Upper_Total_limit
   float Lower_P_limit, Lower _I_limit, Lower _D_limit, Lower _Total_limit
   float Kp, Ki, Kd
  sono globali; sono introdotte e modificate tramite interfaccia HMI
  */
  static int val_OUT = 0; /*Scrittura convertitore D/A: scrive la variabile di uscita*/
  static int error = 0; /*differenza tra valore di consegna e valore reale */
  static int old_error = 0; /*differenza tra valore di consegna e valore reale @ z-1 */

  float P = 0; /* componente proporzionale */
  float I = 0; /* componente integrale */
  float D = 0; /* componente differenziale */
  float I_inst = 0; /* parte istantanea del processo di integrazione*/
  float Out = 0; /* Totale regolazione */

  error = val_SET - val_IN;
  P = error * Kp;

  if (P > Upper_P_limit) P = Upper_P_limit;
  if (P < Lower_P_limit) P = Lower_P_limit;

  if (Ki > 0)
  {
    I_inst = error * Ki;
    I = I + I_inst;
    if (I > Upper_I_limit) I = Upper_I_limit;
    if (I < Lower_I_limit) I = Lower_I_limit; 
  }

  else
    I = 0;

  if (Kd > 0)
  {
    D = Kd * (error - old_error);
    old_error = error;
    if (D > Upper_D_limit) D = Upper_D_limit;
    if (D < Lower_D_limit) D = Lower_D_limit;
  }

  else
    D = 0;

  Out = P + I + D;

  if ( Out > Upper_Total_limit) Out = Upper_Total_limit;
  if (Out < Lower_Total_limit) Out = Lower_Total_limit;

  val_OUT = Out;
  return(val_OUT);
} 
