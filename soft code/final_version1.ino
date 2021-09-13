/*include libraries*/
#include "Arduino.h"
#include "EasyVR.h"
#pragma once //Stops multiple opening of same .h files.

/*check available port*/
#if !defined(SERIAL_PORT_MONITOR)
#error "Arduino version not supported. Please update your IDE to the latest version."
#endif

#if defined(SERIAL_PORT_USBVIRTUAL)
/*Shield Jumper on HW (using pin 0/1 as Rx/Tx)*/
#define port SERIAL_PORT_HARDWARE
#define pcSerial SERIAL_PORT_USBVIRTUAL
#else
/*Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)*/
#include "SoftwareSerial.h"
SoftwareSerial port(12, 13); //define pin 12/13
#define pcSerial SERIAL_PORT_MONITOR
#endif

/*declare functions*/
EasyVR easyvr(port);
void default_pin_configuration();
void action();
void easyVR_settings();
void check_bridge_mode();
void check_bridge_connection();
void open_door();
void blind_open();
void blind_close();
void blind_stop();
void check_battery();
bool checkSleepMode();

/* global variables */
int8_t group, idx;
int16_t err;
String x;
int y =0;
bool isSleeping = false;

/*define LED pins*/
#define LED_RED 9
#define LED_GREEN 10

/*declare Groups in easyVR commander*/
enum Groups
{
  GROUP_1  = 1,
  GROUP_2  = 2,
};

enum Group_1
{
  G1_BLIND_OPEN  = 0,
  G1_BLIND_CLOSE = 1,
  G1_OPEN_DOOR   = 2,
  G1_BLIND_STOP  = 3,
};
enum Group_2
{
  G2_YES = 0,
  G2_NO  = 1,
};

/* arduino board Setup*/
void setup ()
{
  /*define configuration of pins (reserve 0,1,12,13 for serial transmission)*/
  default_pin_configuration();

  /*check bridge mode*/
  check_bridge_mode();

  /*setup PC serial port*/
  pcSerial.begin(9600);

  /*check bridge connection*/
  check_bridge_connection();

  /*adjust easyvr setting,initialize group to begin*/
  easyVR_settings();

  /* end setup*/
  Serial.println("Now exit setup...");

  easyvr.playSound(15, EasyVR::VOL_FULL); // #15 sound
  easyvr.playSound(0, EasyVR::VOL_FULL); // #0 sound
  Serial.println("Sound #15: Say a command in group 1");
  Serial.println("Sound #0: Beep - listening ");
} // end setup

bool checkSleepMode()
{
  /* if "no" being recognized*/
  if ((group == GROUP_2) && (idx == 1 ))
  {
    int8_t mode = 0;

    mode = EasyVR::WAKE_ON_LOUDSOUND;

    pcSerial.print(F("Sleep mode "));
    pcSerial.println(mode);

    digitalWrite(LED_RED, LOW);

    easyvr.stop();
    isSleeping = easyvr.sleep(mode);
    return true;
  }
} // end checkSleepMode

void loop()
{
  checkSleepMode();
  //check_battery();

  if (!isSleeping)
  {
    /* EasyVR ready to listen command*/
    Serial.println("Now in loop...");

    /* 1.For group 2 , beep ,then say (yes / no)*/
    if ((group == GROUP_2))
    {
      easyvr.playSound(0, EasyVR::VOL_FULL); // #0 sound
      Serial.println("Sound #0: Beep");
    }


    /* 2. For group 1 except for blind (open/close) command, "say a command in group 1"  + beep ,then say a command(GROUP_1)*/
    else if (group == GROUP_1)
      if (x == "SayCommand") //&& (x != "good")&& (x!= "error"))
      {
        easyvr.playSound(10, EasyVR::VOL_FULL); // #10 sound
        Serial.println("Sound #15: Power on");

        digitalWrite(LED_RED, HIGH);

        easyvr.playSound(15, EasyVR::VOL_FULL); // #15 sound
        easyvr.playSound(0, EasyVR::VOL_FULL); // #0 sound
        Serial.println("Sound #15: Say a command in group 1");
        Serial.println("Sound #0: Beep");
      }
      else if (x == "good")
      {
        easyvr.playSound(15, EasyVR::VOL_FULL); // #15 sound
        easyvr.playSound(0, EasyVR::VOL_FULL); // #0 sound
        Serial.println("Sound #15: Say a command in group 1");
        Serial.println("Sound #0: Beep");
      }
      else if (idx != 0 && idx != 1) // for user to stop the blind after the beep if recognitiom failure/ did not say the stop command
      {
        easyvr.playSound(0, EasyVR::VOL_FULL); // #0 sound
        Serial.println("Sound #0: Beep");
      }




    /*2nd LED on: listening*/
    digitalWrite(LED_GREEN, HIGH); // 2ND LED: easy vr listening

    /* Start recognizing a command*/
    //Serial.print("Say a command in Group ");
    delay(200);
    //Serial.println(group);
    easyvr.recognizeCommand(group); //Recognition of a custom command from a group
  } // end if (!isSleeping)

  /* recognizing a command, check sleep mode too*/
  do
  {

  }
  while (!easyvr.hasFinished()); // break loop if finisih recognizing

  isSleeping = false; // set isSleeping to be false

  /*awake on wake up indicator*/
  if (easyvr.isAwakened())
  {
    pcSerial.println("Audio wake-up!");

    group = GROUP_1;
    x = "SayCommand";
    y =0;
    return;
  }

  /* easyvr done listening, 2nd LED off*/
  digitalWrite(LED_GREEN, LOW);

  /* Get the recognised SD command index*/
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    uint8_t train = 0;
    char name[32];

    Serial.print("Command: ");
    Serial.print(idx);

    /* print recognized command's group and index*/
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      Serial.print(" = ");
      Serial.println(name);
    } //end if.
    else
      Serial.println();

    /* Command recognized - two beeps and 2nd LED flashes*/
    digitalWrite(LED_GREEN, HIGH);
    easyvr.playSound(0, EasyVR::VOL_FULL);
    digitalWrite(LED_GREEN, LOW);

    easyvr.playSound(0, EasyVR::VOL_FULL);
    digitalWrite(LED_GREEN, HIGH);
    delay(100);
    digitalWrite(LED_GREEN, LOW); // turn of 2nd LED
    Serial.println("Sound #0 : Beep (2 beeps = recognized)");

    /*set addresses and bits accordingly*/
    action();

    /* if open door and stop, ask for next instruction and go to GROUP_2(yes / no)*/
    if (group == GROUP_1)
      if (idx != 0 && idx != 1)
      {
        easyvr.playSound(11, EasyVR::VOL_FULL); // #11th sound
        Serial.println("Sound #11: Do you have another task to perform?");
        group = GROUP_2;
        delay(250);
      }
  } //end if(get recognized command).

  /*time out or error*/
  else
  {
    /* time out*/
    if (easyvr.isTimeout())
    {
      Serial.println("Sound #8: Time out ");
      easyvr.playSound(8, EasyVR::VOL_FULL); //#8th sound

      delay(250);
    }

    /* Error*/
    err = easyvr.getError(); //Gets last error code. 0-255. (16 bits)
    if (err >= 0)
    {
      Serial.print("Sound #7: Error ");
      Serial.println(err, HEX);
      easyvr.playSound(7, EasyVR::VOL_FULL); // #7th sound
      delay (250);
    }

    /* ask for next instruction*/
    if (group == GROUP_1)
    {
      if (idx == 2 || idx == 3)
      {
        easyvr.playSound(11, EasyVR::VOL_FULL); // #11th sound
        Serial.println("Sound #11: Do you have another task to perform?");
        group = GROUP_2;
        delay(250);
      }
      else if ( x == "error" )
      {
        easyvr.playSound(16, EasyVR::VOL_FULL); // #16th sound
        Serial.println("Sound #16: Please stop the blind after the beep");
        group = GROUP_1;
        delay(250);
      }
      else
      {
        easyvr.playSound(11, EasyVR::VOL_FULL); // #11th sound
        Serial.println("Sound #11: Do you have another task to perform?");
        group = GROUP_2;
        delay(250);
      }

    }
    /*else if group 2*/
    else
    {
      easyvr.playSound(11, EasyVR::VOL_FULL); // #11th sound
      Serial.println("Sound #11: Do you have another task to perform?");
      group = GROUP_2;
      delay(250);
    }

  } //end else (time out / error)

} //end loop.


void action()
{

  Serial.println("Now in action function...");

  switch (group)
  {
    case GROUP_1:
      switch (idx)
      {
        case G1_OPEN_DOOR:
          open_door();
          break;

        case G1_BLIND_OPEN:
          blind_open();
          break;

        case G1_BLIND_CLOSE:
          blind_close();
          break;

        case G1_BLIND_STOP:
          blind_stop();
          break;
      } //end case GROUP_1.
      break;

    case GROUP_2:
      switch (idx)
      {
        case G2_YES:
          group = GROUP_1;
          x = "good";

          /*clear off bits*/
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);

          delay(350);
          
          break;

        case G2_NO:

          /*check  battery percentage*/
          check_battery();

          /*clear off bits*/
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);

          delay (350);

          /*enter sleep mode*/
          easyvr.playSound(4, EasyVR::VOL_FULL); // #4th sound
          Serial.println("Sound #4: Entering Sleeping Mode");
          delay(250);
          break;
      }// end case GROUP_2.
      break;

  } //end group case stmt.

} //end action.
