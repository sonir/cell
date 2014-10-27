#pragma once

#define SCREEN_WIDTH  768//1024
#define SCREEN_HEIGHT 768
#define FONT_SIZE_MODIFY 7. //For dispray on center of Square

//System
#define ARM_NUM 4
#define STEP_INTERVAL 0.2f
#define SENDING_INTERVAL 5.0f

//Define for OSC to Receive
#define PORT 58137
#define NUM_MSG_STRINGS 20
//Define for OSC to Send
//#define SENDER_HOST "49.212.138.54"
//#define SENDER_PORT 57122

//For FIS
#define SENDER_HOST "127.0.0.1"
#define SENDER_PORT 58137


#include "ofMain.h"
#include "ofxOsc.h"
#include "slCircular.h"
#include "slEuclid.h"
#include "slCellModel.h"
#include "slMetro.h"
#include "DigitalFis.h"


typedef struct system_t {

    int fps;
    int reset_flg;
    int stop_flg;
    int step_count;
    
}system_t;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        system_t system;
        slCellModel *model;
    
    	//OSC Receive
		ofxOscReceiver receiver;
		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];
        void sendData();
    

    private:

        //OSC
        ofxOscSender server;
    
        //Utilities
        slMetro *timerAgentStep;
        slMetro *timerSendingParameters;
        //Fis
    	DigitalFis digitalFis;
    
        //Drawing Arm
        slEuclid* space;
        float pirad;
        slCircular* arm[ARM_NUM];
        float pirad_circle1;
       	float pirad_circle2;
       	float pirad_circle3;
       	float pirad_circle4;
    
		//System Variables
	    int agent_count;
        ToolKit toolKit;
        //Font
        ofTrueTypeFont	dekar;
    
        //Agent (model level)
        void addAgents();
    
	    //Agent (drawing level)
        float counter;
		bool checkIntersect(slCircular *target);
		void setupSeeds();
		void displayAgents();
		void listenOsc();
    
        //Bridge Graphic and Model
        void syncPosition(int ag_id);
        void syncPositions();
    
};
