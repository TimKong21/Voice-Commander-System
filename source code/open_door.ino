/*
  set open_door data bits, if recognized -->ask for next instruction
  if not recognized = error / time out --> ask if next instruction needed
*/

void open_door()
{
  /* #3 sound: blind's opening*/
  easyvr.playSound(3, EasyVR::VOL_FULL);
  Serial.println("Sound #3: Door's opening");

  /*Set address and bits*/
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);

  delay(1000);
  
  /* clear off address and bit*/
  digitalWrite(2, HIGH);  // set the LED on
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  
  delay(350);
}
