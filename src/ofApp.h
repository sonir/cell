#pragma once

#define SCREEN_WIDTH  768//1024
#define SCREEN_HEIGHT 768
#define FONT_SIZE_MODIFY 7. //For dispray on center of Square

//Define for OSC to Receive
#define PORT 58137
#define NUM_MSG_STRINGS 20
//Define for OSC to Send
//#define SENDER_HOST "49.212.138.54"
//#define SENDER_PORT 57122
#define SENDER_HOST "127.0.0.1"
#define SENDER_PORT 58137


#include "ofMain.h"
#include "ofxOsc.h"
#include "slCircular.h"
#include "slEuclid.h"
//#include "slMetro.h"
#include "gismodel.h"
#include "tools.h"
#include "DigitalFis.h"



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

    
//        slMetro *metro;
    
    	//OSC Receive
		ofxOscReceiver receiver;
		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];
        void sendData();
    

    private:
    	Gismodel gismodel;
        ofxOscSender server;
    
    	ToolKit toolKit;
    	DigitalFis digitalFis;
        slCircular* circle1;
        slCircular* circle2;
        slCircular* circle3;
        slCircular* circle4;
        float pirad_circle1;
       	float pirad_circle2;
       	float pirad_circle3;
       	float pirad_circle4;

        slEuclid* space;
		float pirad;
    
		//System
	    int reset_flg; //Init reset flag
	    int stop_flg; // Init stop flag
	    int agent_count;
        //Font
        ofTrueTypeFont	dekar;
    

	    //Agent
         unsigned long seeds[SEED_ARRAY_MAX];
	     string seed_names[SEED_ARRAY_MAX];
	     float 	counter;

		bool checkIntersect(slCircular *target);
		void setupSeeds();
		void displayAgents();
		void listenOsc();
    
};
