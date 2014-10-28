//
//  cellSetup.h
//  cell
//
//  Created by sonir on 10/28/14.
//
//

#ifndef cell_cellSetup_h
#define cell_cellSetup_h


//System
#define ARM_NUM 4
//System Timers
#define STEP_INTERVAL 0.01f
#define SENDING_INTERVAL 5.0f

//Define for OSC to Receive
#define PORT 58137
#define NUM_MSG_STRINGS 20

//Define for OSC to Send
//#define SENDER_HOST "49.212.138.54"
//#define SENDER_PORT 57122

//ScreenSetup
#define SCREEN_WIDTH  768//1024
#define SCREEN_HEIGHT 768
#define FONT_SIZE_MODIFY 7. //For dispray on center of Square


//For FIS
#define SENDER_HOST "127.0.0.1"
#define SENDER_PORT 58137

// LayOut and Display
#define TOP_OFFSET 35
#define LEFT_OFFSET 15
#define LEFT_OFFSET_FOR_PRAM 620
#define PARAMETER_SPC 70
#define LINE_HEIGHT 30
#define LINE_HEIGHT_BODY 15
#define DISP_TITLE "CELL Operation Sytem Ver0.3"
#define MESSAGE1 "SPC : START SIMULATOR"
#define SENDIG_MES "connect with drone server"
#define SENDIG_BLINK "OSC SENDING"
//Label
#define LB_AGENT_ID "AGENT-%d"
#define LB_VIEW "VIEW"
#define LB_STRENGTH "STRENGTH"
#define LB_DEXTERYTY "DEXTERITY"
#define LB_HP "LIFE"
#define LB_INTERTIA "INTERTIA"
#define LB_C_POSI "C_POSI"
#define LB_CONTACT "CONTACT"
#define LB_ACTION "ACTION"
#define LB_SPACER "////"


#endif