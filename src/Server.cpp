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
    
    //Write here sender init and receiver init
    
//    cout << "listening for osc messages on port " << PORT << "\n";
//    receiver.setup(PORT);
    
    
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
    
}

void Server::send(sending_message_t getParams){

    sending_param = getParams;
    this->send();
    
}


//To Receive
//--------------------------------------------------------------
void Server::getMessages(){
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // check for mouse moved message
        if(m.getAddress() == "/mouse/position"){
            // both the arguments are int32's
            cout << m.getArgAsInt32(0) << endl;
            cout << m.getArgAsFloat(1) << endl;
        }
        // check for mouse button message
        else if(m.getAddress() == "/mouse/button"){

            cout << "/mouse/button received" << endl;
        }
        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        
    }
}
