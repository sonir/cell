//
//  Server.h
//  cell
//
//  Created by sonir on 10/30/14.
//
//

#ifndef __cell__Server__
#define __cell__Server__

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 57122

#include <stdio.h>
#include "ofxOsc.h"



typedef struct sending_message_t {

	int ival;
	float fval;

} sending_message_t;

class Server{
    
    public:
        Server(); //CONSTRUCTOR
        ofxOscSender server;
        sending_message_t sending_param;
        virtual void initParam(sending_message_t *pMessage);
        virtual void send();
        virtual void send(sending_message_t getParams);
    
    
};

#endif /* defined(__cell__Server__) */
