/*
  check bridge connection
*/
void check_bridge_connection()
{
  /*if bridge is not connected, keep looping*/
  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    delay(1000);
  } //end while

  /*if bridge is detected, 1st LED on*/
  digitalWrite(LED_RED, HIGH);
  digitalWrite(8, HIGH); // power bar LED (for testing)

  /*if bridge is detected, power on sound + power on feedback messsage */
  easyvr.playSound(10, EasyVR::VOL_FULL); //#10th sound
  Serial.println("Sound #10: Power on");
}
