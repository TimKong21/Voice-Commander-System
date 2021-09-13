/*
  define pin configuration
*/

void default_pin_configuration()
{
  /* OUTPUT pins*/
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT); // for powering bar LED for testing, can be removed
  pinMode(LED_RED, OUTPUT); // for light indicator (on / off)
  pinMode(LED_GREEN, OUTPUT); // for light indicator (low battery)

  /*addresses and bits - everything low, transmitter is not transmitting */
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  /* for powering bar LED (can be removed)*/
  digitalWrite(8, LOW);

  /*1st LED indicator: (power on/off)& low battery */
  digitalWrite(LED_RED, LOW);

  /*2nd LED indicator (listening & flashes if command is recognized)*/
  digitalWrite(LED_GREEN, LOW);

  delay (250);
}
