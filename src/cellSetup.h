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
#define SENDING_INTERVAL 8.0f //5.0f
#define ARDUINO_UPDATE_INTERVAL 0.1f
#define CLIP_EVENT_INTERVAL 4500.0f
#define MODE_INTERVAL 5.0f

#define INTERVAL_OF_REPORT_IN_MINUTES 75
#define TWEET_RATE ( ( INTERVAL_OF_REPORT_IN_MINUTES*60 )/ SENDING_INTERVAL ) // 900 // ( INTERVAL_OF_REPORT_IN_MINUTES*60 )/ SENDING_INTERVAL


//Modes
#define DEFAULT_STOP_FLG 1

//For Presets

//PS_DEFAULT
#define DEFAULT_SYSTWM_FPS 60
#define DEFAULT_STEP_INTERVAL 1.0f //0.2f
#define DEFAULT_STEP_INTERVAL_NORMAL_MODE 0.15f
#define DEFAULT_MOV_FIX ( BASIC_MOV_FIX * 10.0f)
#define DEFAULT_RANDOM_WALK_FIX ( BASIC_RANDOM_WALK_FIX * 3.0 )
#define DEFAULT_CLOCK_MODE 1

//PS_MICRO
#define PS_MICRO_SYSTWM_FPS DEFAULT_SYSTWM_FPS
#define PS_MICRO_STEP_INTERVAL 0.01f
#define PS_MICRO_STEP_INTERVAL_NORMAL_MODE 0.01f
#define PS_MICRO_MOV_FIX 0.05f
#define PS_MICRO_RANDOM_WALK_FIX 0.005f
#define PS_MICRO_CLOCK_MODE 0

//PS_CATHARSIS
#define PS_CATHARSIS_SYSTWM_FPS DEFAULT_SYSTWM_FPS
#define PS_CATHARSIS_STEP_INTERVAL 0.15f
#define PS_CATHARSIS_STEP_INTERVAL_NORMAL_MODE 0.15f
#define PS_CATHARSIS_MOV_FIX 0.8f
#define PS_CATHARSIS_RANDOM_WALK_FIX 0.5f
#define PS_CATHARSIS_CLOCK_MODE 1

//PS_VIBE
#define PS_VIBE_SYSTWM_FPS DEFAULT_SYSTWM_FPS
#define PS_VIBE_STEP_INTERVAL 0.2f
#define PS_VIBE_STEP_INTERVAL_NORMAL_MODE 0.15f
#define PS_VIBE_MOV_FIX 0.02f
#define PS_VIBE_RANDOM_WALK_FIX 0.01f
#define PS_VIBE_CLOCK_MODE 1

//PS_SYNC
#define PS_SYNC_SYSTWM_FPS DEFAULT_SYSTWM_FPS
#define PS_SYNC_STEP_INTERVAL 0.2f
#define PS_SYNC_STEP_INTERVAL_NORMAL_MODE 0.15f
#define PS_SYNC_MOV_FIX 0.02f
#define PS_SYNC_RANDOM_WALK_FIX 0.01f
#define PS_SYNC_CLOCK_MODE 1



//Define for OSC to Receive
#define PORT 58137
#define NUM_MSG_STRINGS 20

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
#define LINE_HEIGHT_BODY 15.0f
#define DISP_TITLE "CELL Operation System Ver0.95"
#define MESSAGE1 "SPC : START SIMULATOR"
#define SENDIG_MES "connect with drone server"
#define LB_MOVE_MODE1 "clock mode"
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

//Preset Mode
typedef enum preset_mode { PS_DEFAULT, PS_MICRO, PS_CATHARSIS, PS_VIBE, PS_SYNC } preset_mode_t;


#endif
