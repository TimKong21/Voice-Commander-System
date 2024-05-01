; external declaration of sound table:

    .EXTRN (const) SNDTBL_SOUND_TABLE



; external declarations of addresses of sounds for direct access:

    .EXTRN (const) SX_Blinds_closing
    .EXTRN (const) SX_Blinds_opening
    .EXTRN (const) SX_Doors_opening
    .EXTRN (const) SX_Entering_Sleeping_Mode
    .EXTRN (const) SX_Error__please_try_again
    .EXTRN (const) SX_Listening
    .EXTRN (const) SX_Error
    .EXTRN (const) SX_Time_out
    .EXTRN (const) SX_Low_battery
    .EXTRN (const) SX_Power_on
    .EXTRN (const) SX_Do_you_want_to_perform_another_task
    .EXTRN (const) SX_low_battery__please_get_a_new_replacement
    .EXTRN (const) SX_Battery_percentage_good
    .EXTRN (const) SX_Say_the_trigger_command
    .EXTRN (const) SX_Say_a_command_in_group_1
    .EXTRN (const) SX_Please_stop_the_blind_after_the_beep
    .EXTRN (const) SX_The_blind_has_stopped


; equates defining sounds as entries in the sound table:

SND_Blinds_closing      .EQU 1
SND_Blinds_opening      .EQU 2
SND_Doors_opening       .EQU 3
SND_Entering_Sleeping_Mode .EQU 4
SND_Error__please_try_again .EQU 5
SND_Listening           .EQU 6
SND_Error               .EQU 7
SND_Time_out            .EQU 8
SND_Low_battery         .EQU 9
SND_Power_on            .EQU 10
SND_Do_you_want_to_perform_another_task .EQU 11
SND_low_battery__please_get_a_new_replacement .EQU 12
SND_Battery_percentage_good .EQU 13
SND_Say_the_trigger_command .EQU 14
SND_Say_a_command_in_group_1 .EQU 15
SND_Please_stop_the_blind_after_the_beep .EQU 16
SND_The_blind_has_stopped .EQU 17

