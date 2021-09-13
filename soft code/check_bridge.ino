/*
  check bridge mode
*/

void check_bridge_mode()
{
  int mode = easyvr.bridgeRequested(pcSerial);
  switch (mode)
  {
    case EasyVR::BRIDGE_NONE:
      /*setup EasyVR serial port*/
      port.begin(9600);

      /*run normally*/
      pcSerial.println(F("---"));
      pcSerial.println(F("Bridge not started!"));
      Serial.println("*** case EasyVR::BRIDGE_NONE: ***");
      break;

    case EasyVR::BRIDGE_NORMAL:
      /*setup EasyVR serial port (low speed)*/
      port.begin(9600);

      /*soft-connect the two serial ports (PC and EasyVR)*/
      easyvr.bridgeLoop(pcSerial);

      /*resume normally if aborted*/
      pcSerial.println(F("---"));
      pcSerial.println(F("Bridge connection aborted!"));
      Serial.println("*** case EasyVR::BRIDGE_NORMAL: ***");
      break;

    case EasyVR::BRIDGE_BOOT:
      /*setup EasyVR serial port (high speed)*/
      port.begin(115200);

      /*soft-connect the two serial ports (PC and EasyVR)*/
      easyvr.bridgeLoop(pcSerial);

      /*resume normally if aborted*/
      pcSerial.println(F("---"));
      pcSerial.println(F("Bridge connection aborted!"));
      Serial.println("*** case EasyVR::BRIDGE_BOOT: ***");
      break;
  } //end case.

}
