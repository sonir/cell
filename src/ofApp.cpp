#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){    

    //Instanciate Model
    model = new slCellModel(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //System Setup
    system.fps = 60;
    timerAgentStep = new slMetro(STEP_INTERVAL);
    timerSendingParameters = new slMetro(SENDING_INTERVAL);
    
    //Font Setup
    ofTrueTypeFont::setGlobalDpi(72);
    h1.loadFont("Dekar.otf", 30, true, true);
    h2.loadFont("Dekar.otf", 18, true, true);
    body.loadFont("frabk.ttf", 12, false, true);
    // body.loadFont("Dekar.otf", 16, true, true);
    
	//APP Setup
    system.reset_flg = 0; //Init reset flag
    system.stop_flg = 1; // Init stop flag
    system.step_count = 0;
    system.sent_drone = 0;
    int ofSetFrameRate(system.fps); //Setup Frame Rate
    if(false)toolKit.dice(6); //No meaning code to avoid "Unused" warning.
    
	//OSC Setup
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
	current_msg_string = 0;
    // open an outgoing connection to HOST:PORT
    server.setup(SENDER_HOST, SENDER_PORT);


    //Set Corner
	arm[0] = new slCircular(-0.7,0.7,1.1, -0.75);
	arm[1] = new slCircular(0.7,0.7,1.1,0.75);
	arm[2] = new slCircular(0.7,-0.7, 1.1, .25);
	arm[3] = new slCircular(-0.7,-0.7,1.1, -.25);
	space = new slEuclid(SCREEN_WIDTH , SCREEN_HEIGHT);                   

	pirad = 0.;

    //Add Agents
    this->addAgents();

    
    
}

//--------------------------------------------------------------
void ofApp::update(){



    //Reset check for Mutex
    if(system.reset_flg){
        system.reset_flg = 0;
    }        
    //Do Agent Cycle
    if(!system.stop_flg){
        
        if(timerAgentStep->alart())model->stroke(system.step_count);
        system.step_count++;
        if(system.step_count>=ARM_NUM)system.step_count=0;
//        model->cycle();
    }

    if(timerSendingParameters->alart()){
        //Send Now Agents States
        snap.ag0 = model->getAgent(0);
        snap.ag1 = model->getAgent(1);
        snap.ag2 = model->getAgent(2);
        snap.ag3 = model->getAgent(3);
        sound.update(snap);
        system.sent_drone = true;
    }
    
    sendData();
	listenOsc();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    

	sl_screen_position center;
	sl_screen_position node;
    
    ofBackground(0, 0, 0);

    
    //Draw ARM1
    syncPosition(0);
    center = space->getScreenPosition(arm[0]->center.x,arm[0]->center.y);
    node = space->getScreenPosition(arm[0]->arc_position.x,arm[0]->arc_position.y);
    ofSetHexColor(0xFF0000);
    if(checkIntersect(arm[0])){ //If the lines are crossing
        digitalFis.flash(PF,(fis_color)toolKit.dice(3));
         // digitalFis.flash(PF,(fis_color)getAgent.condition);
    }
    ofLine(center.x,center.y,node.x,node.y); //Change Line Color

    //Draw ARM2
    syncPosition(1);
     center = space->getScreenPosition(arm[1]->center.x,arm[1]->center.y);
     node = space->getScreenPosition(arm[1]->arc_position.x,arm[1]->arc_position.y);
     ofSetHexColor(0x00FF77);
     if(checkIntersect(arm[1])){ //If the lines are crossing
         digitalFis.flash(TB,(fis_color)toolKit.dice(3));
     }
     ofLine(center.x,center.y,node.x,node.y);                

    //Draw ARM3
    syncPosition(2);
     center = space->getScreenPosition(arm[2]->center.x,arm[2]->center.y);
     node = space->getScreenPosition(arm[2]->arc_position.x,arm[2]->arc_position.y);
     ofSetHexColor(0x0000FF);
     if(checkIntersect(arm[2])){ //If the lines are crossing
         digitalFis.flash(GT,(fis_color)toolKit.dice(3));
     }
     ofLine(center.x,center.y,node.x,node.y);                

    //Draw ARM4
    syncPosition(3);
     center = space->getScreenPosition(arm[3]->center.x,arm[3]->center.y);
     node = space->getScreenPosition(arm[3]->arc_position.x,arm[3]->arc_position.y);
     ofSetHexColor(0xFFFF00);
     if(checkIntersect(arm[3])){ //If the lines are crossing
         digitalFis.flash(BS,(fis_color)toolKit.dice(3));
     }
     ofLine(center.x,center.y,node.x,node.y);

    //Draw Fonts
    float top_offset = TOP_OFFSET;
    ofSetColor(225);
    h1.drawString(DISP_TITLE, LEFT_OFFSET, TOP_OFFSET);
    h2.drawString(MESSAGE1, LEFT_OFFSET, top_offset+=LINE_HEIGHT);
    top_offset = this->dispAgentParam(top_offset,0);
    top_offset = this->dispAgentParam(top_offset,1);
    top_offset = this->dispAgentParam(top_offset,2);
    top_offset = this->dispAgentParam(top_offset,3);
    ofSetColor(255);
    //OSC Status
    ofSetColor(80);
    body.drawString(SENDIG_MES, LEFT_OFFSET+15., SCREEN_HEIGHT-20.f);
    ofSetColor(255);
    if(system.sent_drone){
        system.sent_drone = false;
        //ofRect(LEFT_OFFSET, SCREEN_HEIGHT-30.f, 10.f, 10.f);
        body.drawString(SENDIG_MES, LEFT_OFFSET+15., SCREEN_HEIGHT-20.f);

    }
    ofSetColor(200);

}

float ofApp::dispAgentParam(float top_offset, int ag_id){

    float ag_top;
    char str_val[40]; //Create Label Str
    agent ag = model->getAgent(ag_id); //Get Agent Param
    
    //Agent
    ofSetColor(0,205,0);
    sprintf(str_val, LB_AGENT_ID, ag.ag_id);
    body.drawString(str_val, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT);
    ag_top = top_offset;
    ofSetColor(0,180,0);
    body.drawString(LB_VIEW, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_STRENGTH, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_DEXTERYTY, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_HP, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    ofSetColor(0,100,0);
    body.drawString(LB_INTERTIA, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_C_POSI, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_CONTACT, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    body.drawString(LB_ACTION, LEFT_OFFSET_FOR_PRAM,top_offset+=LINE_HEIGHT_BODY);
    //Param
    ofSetColor(0, 205, 0);
    body.drawString(LB_SPACER, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset=ag_top);
    sprintf(str_val, "%.3f", ag.view);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%d", ag.strength);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%d", ag.dexterity);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%.3f", ag.hp);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    ofSetColor(0,150,0);
    sprintf(str_val, "%d", ag.inertia);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%.3f", ag.circumference_posi);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%d", ag.contact_flg);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    sprintf(str_val, "%d", ag.action_flg);
    body.drawString(str_val, (LEFT_OFFSET_FOR_PRAM+PARAMETER_SPC),top_offset+=LINE_HEIGHT_BODY);
    
    return top_offset;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == OF_KEY_RETURN){
    	system.stop_flg = ( (system.stop_flg-1)*(-1) ); //Invert the value
    } else if (key == 0x20){
    	system.stop_flg = ( (system.stop_flg-1)*(-1) ); //Invert the value
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
bool ofApp::checkIntersect(slCircular *target){

	// if(target == arm[1])ofSetHexColor(0xFFFFFF);

	slCircular* another;

	for(int i = 0; i<4; i++){

		switch (i){

			case 0:
				another = arm[0];
				break;

			case 1:
				another = arm[1];
				break;

			case 2:
				another = arm[2];			
				break;

			case 3:
				another = arm[3];			
				break;

			default:
				cout << "unknown agent" << endl;
				break;

		}

		if(target == another) continue;

	    sl_scaled_position *a_st = (struct sl_scaled_position *)&target->center;
	    sl_scaled_position *a_ed = (struct sl_scaled_position *)&target->arc_position;
	    sl_scaled_position *b_st = (struct sl_scaled_position *)&another->center;
	    sl_scaled_position *b_ed = (struct sl_scaled_position *)&another->arc_position;

		if( space->intersect(*a_st, *a_ed, *b_st, *b_ed) ){

			ofSetHexColor(0xFFFFFF);
			return true;			
		}

	}

	return false;

}



//--------------------------------------------------------------
void ofApp::addAgents(){
    
    //SetUp Agents
    agent ag1;
    ag1.view = 0.3;
    ag1.strength = 50;
    ag1.dexterity = 50;
    ag1.hp = 0.5;
    ag1.circumference_posi = -1.0f;
    ag1.posi.x = 0.138;
    ag1.posi.y = 0.139;
    model->addAgent(&ag1);
    
    agent ag2;
    ag2.view = 0.3;
    ag2.strength = 50;
    ag2.dexterity = 50;
    ag2.hp = 0.5;
    ag2.circumference_posi = -1.0f;
    ag2.posi.x = 0.138;
    ag2.posi.y = 0.139;
    model->addAgent(&ag2);
    
    agent ag3;
    ag3.view = 0.3;
    ag3.strength = 50;
    ag3.dexterity = 50;
    ag3.hp = 0.5;
    ag3.circumference_posi = -1.0f;
    ag3.posi.x = 0.;
    ag3.posi.y = 0.;
    model->addAgent(&ag3);
    
    agent ag4;
    ag4.view = 0.3;
    ag4.strength = 50;
    ag4.dexterity = 50;
    ag4.hp = 0.5;
    ag4.circumference_posi = -1.0f;
    ag4.posi.x = 1.;
    ag4.posi.y = 1.;
    model->addAgent(&ag4);
    
 
    //Sync ag position and arm position
    this->syncPositions();
    
}



//--------------------------------------------------------------

void ofApp::sendData(){

    ofxOscMessage m;
    m.setAddress("/message");
    m.addFloatArg(0.9f);
    server.sendMessage(m);

}
//--------------------------------------------------------------

void ofApp::listenOsc(){

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
        

		//Message for arm[0]
		if(m.getAddress() == "/circleControl"){
            
            slCircular* circle;
            agent ag;
            
			string target = m.getArgAsString(0); //Get the 2nd address
            int target_id;
            if(target=="/circle1") target_id = 0;
			else if (target =="/circle2")target_id = 1;
            else if (target =="/circle3")target_id = 2;
            else if (target =="/circle4")target_id = 3;

            //Set target arm and agent
            circle = arm[target_id];
            ag = model->getAgent(target_id);

            //Set agent position
            ag.circumference_posi = (float)scale(m.getArgAsFloat(1), 1., 0., 1., -1.);
            model->setAgent(target_id, &ag);
            cout << ag.circumference_posi << endl;
			if( m.getArgAsFloat(2) != 0.) circle->radius = m.getArgAsFloat(2);

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



void ofApp::syncPosition(int ag_id){
    
    agent ag = model->getAgent(ag_id);
    
    //Scale Agent position into pirad
    double pirad = scale(ag.circumference_posi, 1., -1., 1., 0.);
    //Set the arm position with piRad, then, set the eucrid arm position to agent
    ag.posi = arm[ag_id]->piradToPosition( (float)pirad );
    model->setAgent(ag_id, &ag);
    
}

void ofApp::syncPositions(){
    
    //Sync the agent position into arm position
    for(int i; i<ARM_NUM; i++) this->syncPosition(i);

    
}
