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
  int val_OUT = 0; /*Scrittura convertitore D/A: scrive la variabile di uscita*/
  int error = 0; /*differenza tra valore di consegna e valore reale */

  float I_inst = 0; /* parte istantanea del processo di integrazione*/
  float Out = 0; /* Totale regolazione */

  error = val_SET - val_IN;
  P = error * Kp;

  if (Ki > 0)
  {
    I_inst = error * Ki;
    I = I + I_inst;
  }

  else
    I = 0;

  if (Kd > 0)
  {
    D = Kd * (error - old_error);
    old_error = error;
  }

  else
    D = 0;

  Out = P + I + D;

  if (Out > Upper_Total_limit) Out = Upper_Total_limit;
  if (Out < Lower_Total_limit) Out = Lower_Total_limit;

  val_OUT = int(Out);
  return(val_OUT);
}
