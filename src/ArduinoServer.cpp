//
//  ArduinoServer.cpp
//  cell
//
//  Created by sonir on 10/30/14.
//
//

#include "ArduinoServer.h"

ArduinoServer::ArduinoServer(){
    
    server.setup(ARDUINO_SERVER_IP, ARDUINO_SERVER_PORT);
    this->initPram(&arduino_param);
    
}


void ArduinoServer::send(){

    ofxOscMessage m;
    m.setAddress("/ardControl");
    m.addFloatArg(arduino_param.servo1);
	m.addFloatArg(arduino_param.servo2);
	m.addFloatArg(arduino_param.servo3);
	m.addFloatArg(arduino_param.servo4);
	server.sendMessage(m);

}


void ArduinoServer::send(arduino_param_t getParams){

	arduino_param = getParams;
	this->send();

}


void ArduinoServer::initPram(arduino_param_t *pArduino){

	pArduino->servo1 = 0.0f;
	pArduino->servo2 = 0.0f;
	pArduino->servo3 = 0.0f;
	pArduino->servo4 = 0.0f;

}