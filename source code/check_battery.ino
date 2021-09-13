/*
  check battery and inform user if low battery
*/

void check_battery()
{
  /* variables for input voltages*/
  float analogValue;
  float inputVoltage;

  analogValue = analogRead (A4);
  inputVoltage = analogValue * (5.00 / 1024.00) * 2;

  if (y == 1)
  {
    /* 1st LED flashes*/
    for (int m = 0; m <= 2; m++)
    {
      digitalWrite(9, LOW);
      delay (200);
      digitalWrite(9, HIGH);
      delay (200);
    }
    
    easyvr.playSound(12, EasyVR::VOL_FULL); //#12TH sound
    Serial.print("Sound #12: low battery, at ");
    Serial.println(inputVoltage);
  }
  
  else if (y == 0)
  {
    /* check battery */
    if (inputVoltage <= 6.50)
    {
      /* 1st LED flashes*/
      for (int m = 0; m <= 2; m++)
      {
        digitalWrite(9, LOW);
        delay (200);
        digitalWrite(9, HIGH);
        delay (200);
      }

      easyvr.playSound(12, EasyVR::VOL_FULL); //#12TH sound
      Serial.print("Sound #12: low battery, at ");
      Serial.println(inputVoltage);
      y = 1;
    }
    else
    {
      easyvr.playSound(13, EasyVR::VOL_FULL); //#13th sound
      Serial.print("Sound #13:Battery percentage good, at ");
      Serial.println(inputVoltage);
      y = 0;
    }

  }// end else if (y =0)



}// end function
