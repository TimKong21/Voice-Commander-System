/*
  adjust easyvr setting,initialize group to begin
*/

void easyVR_settings()
{
  /*operation setting*/
  easyvr.setMicDistance(1);//Set mic operating distance. 1 nearest - 3 farthest.
  easyvr.setLevel(3);//Set strictness level for recognition of custom commands.
  easyvr.setKnob(2);//Set confidence threshold for recognition of built-in words.
  easyvr.setTimeout(8); //Set the number of seconds to listen for each command.
  easyvr.setLanguage(0); //Set language to English

  /*set group to group 0 to begin*/
  group = GROUP_1; // start with group 0(trigger)
}
