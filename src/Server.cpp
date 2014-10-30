//
//  Server.cpp
//  cell
//
//  Created by sonir on 10/30/14.
//
//

#include "Server.h"

Server::Server(){ //CONSTRUCTOR
 
//    server.setup(SND_SERVER_IP, SND_SERVER_PORT);
//    this->initParam(&sending_param);

    cout << "foo" << endl;
    
}


void Server::initParam(sending_message_t *pMessage){

	pMessage->ival = 137;
	pMessage->fval = 0.137f;

}

void Server::send(){
    
    ofxOscMessage m;
    m.setAddress("/test");
    m.addIntArg(sending_param.ival);
    m.addFloatArg(sending_param.fval);
    server.sendMessage(m);

    cout << "foo2" << endl;
    
    
}

void Server::send(sending_message_t getParams){

    sending_param = getParams;
    this->send();
    
}