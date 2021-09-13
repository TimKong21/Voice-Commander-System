/*
  stop data bits,if recognized -->ask for next instruction
  if stop is not recognized = error / time out --> ask if next instruction needed
*/

void blind_stop()
{
  /*set data bits*/
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  
  delay (500);
}
