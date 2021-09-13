/*
  blind open data bits, stop will be recognized right away,
  If stop is not recognized = error / time out --> ask if next instruction needed
  No delay, to recognize "stop" instantly
*/

void blind_open()
{
  /* #2 sound: blind's opening*/
  easyvr.playSound(2, EasyVR::VOL_FULL);
  Serial.println("Sound #2: Blind's opening");

  /*Set address and bits*/
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  
  /* go to group 1 during the next recognition*/
  group = GROUP_1;
  x= "error";
}
