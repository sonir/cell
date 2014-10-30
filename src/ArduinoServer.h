//
//  ArduinoServer.h
//  cell
//
//  Created by sonir on 10/30/14.
//
//

#ifndef __cell__ArduinoServer__
#define __cell__ArduinoServer__

#define ARDUINO_SERVER_IP "127.0.0.1"
#define ARDUINO_SERVER_PORT 57137

#include <stdio.h>
#include "ofxOsc.h"
#include "Server.h"


typedef struct arduino_param_t {

	float servo1;
	float servo2;
	float servo3;
	float servo4;

} arduino_param_t;

class ArduinoServer : Server {
    
    public:
	    ArduinoServer();
	    arduino_param_t arduino_param;
	    void initPram(arduino_param_t *pArduino);
	    void send();
	    void send(arduino_param_t getParams);
        
};

#endif /* defined(__cell__ArduinoServer__) */
