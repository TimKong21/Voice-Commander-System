/*
  blind close data bits, stop will be recognized right away
  If stop is not recognized = error / time out --> ask if next instruction needed
  No delay, to recognize "stop" instantly
*/

void blind_close ()
{
  /* #1 sound: blind's closing*/
  easyvr.playSound(1, EasyVR::VOL_FULL);
  Serial.println("Sound #1: Blind's closing");

  /*Set address and data bits*/
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);

  /* go to group 1 during the next recognition*/
  group = GROUP_1;
  x="error";
}
