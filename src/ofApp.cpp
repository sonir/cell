#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){    
    
    //Font Setup
    ofTrueTypeFont::setGlobalDpi(72);
    dekar.loadFont("Dekar.otf", 20, true, true);

    
	//APP Setup
    reset_flg = 0; //Init reset flag
    stop_flg = 1; // Init stop flag
    gismodel.setFps(60);
    ofSetFrameRate(gismodel.getFps()); //Setup Frame Rate
    if(false)toolKit.dice(6); //No meaning code to avoid "Unused" warning.
//    metro = new slMetro(1.);
    
	//OSC Setup
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
	current_msg_string = 0;
    // open an outgoing connection to HOST:PORT
    server.setup(SENDER_HOST, SENDER_PORT);


	//Agent Seed Setup
	setupSeeds();
	//Put Agents
	gismodel.addAgent(seeds[8], 0);
	gismodel.addAgent(seeds[8], 0);
	gismodel.addAgent(seeds[8], 0);
	gismodel.addAgent(seeds[8], 0);


    //Set Corner
	circle1 = new slCircular(-0.7,0.7,1.1, -0.75);
	circle2 = new slCircular(0.7,0.7,1.1,0.75);
	circle3 = new slCircular(0.7,-0.7, 1.1, .25);
	circle4 = new slCircular(-0.7,-0.7,1.1, -.25);
	space = new slEuclid(SCREEN_WIDTH , SCREEN_HEIGHT);                   

	pirad = 0.;

	//Init Position
	circle1->piradToPosition(0.);
	circle2->piradToPosition(0.);
	circle3->piradToPosition(0.);
	circle4->piradToPosition(0.);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){


//     if(metro->alart())cout << "foo" << endl;
    
    //Reset check for Mutex
    if(reset_flg){
        gismodel.reset();
        reset_flg = 0;
    }        
    //Do Agent Cycle
    if(!stop_flg) gismodel.cycle();

    sendData();
	listenOsc();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    

	sl_screen_position center;
	sl_screen_position node;
    
    ofBackground(0, 0, 0);


    //Agent Processing

    //Get now agent numbers
    int agent_count = gismodel.getAgentCount();
    
    //If there are agents
    if(!stop_flg)
     {
     	if(agent_count) displayAgents();
 	     if(agent_count){
 
 	    	//Draw them
 	         for(int i=0 ; i <agent_count; i++)
 	         {
 	             if( reset_flg )continue; //If reset is invoked by other thread, do nothing (mutex).
 	             Agent getAgent;
 	             gismodel.getAnAgent(i, &getAgent);
 	            
 	             getAgent.posi.y = 0.;
 	             //Ignore dead agent
 	             if(gismodel.isAgentActive(getAgent)==false)continue;
 	            
 	             //Convert the position to pixel
 	             // screen_position posi = convertPositionForScreen(getAgent.posi.x,getAgent.posi.y);
 	             sl_scaled_position tmp_posi;
 	             tmp_posi.x = getAgent.posi.x;   tmp_posi.y = getAgent.posi.y;
 	             sl_screen_position posi = space->getScreenPosition(tmp_posi);
 	            
 	             //Draw
 	             switch(getAgent.layer)
 	             {
 	                 case 0:
 	                     ofSetColor(255,255,255); //Set White
 	                     //ofNoFill();
 	                     break;
 	  
 	                 case 1:
 	                     ofSetColor(255,0,0); //Set Red
 	                     //ofFill();
 	                     break;
 	  
 	                 case 2:
 	                     ofSetColor(0,255,0); //Set Green
 	                     //ofFill();
 	                     break;
 	  
 	                 case 3:
 	                     ofSetColor(0,0,255); //Set Blue
 	                     //ofFill();
 	                     break;
 	    
 	                 default:
 	                     ofSetColor(255,255,0); //else is white
 	                     //ofNoFill();
 	                     break;
 	                    
 	             }
 	  
 	             //ofFill();     // draw "filled shapes"
 	             float size = (float)space->getLengthForScreen(getAgent.size);
 	             //Draw Square
 	             ofRect(posi.x-(size*0.5),posi.y-(size*0.5), size, size);
 	             //Draw View
 	             ofNoFill();
 	             ofCircle(posi.x, posi.y,(float)space->getLengthForScreen(getAgent.view));
 	             //Draw Number
 	             ofPushMatrix();
 	             //Create drawing String
 	             char num_str[10];
 	             sprintf(num_str, "%d", getAgent.ag_id); //Create
 	             ofTranslate( posi.x , posi.y ); // Now, display it on center
 	             //Scale it
 	             ofScale( ( getAgent.size * FONT_SIZE_MODIFY ), ( getAgent.size * FONT_SIZE_MODIFY ) );
 	             //Set Color
 	             ofSetColor(255);
 	             ofPopMatrix();
 
 
 	             switch (i) {
 
 	                 case 0:
 	                     circle1->piradToPosition( ofMap(getAgent.posi.x, -1.,1.,0.,1.));     
 	                     center = space->getScreenPosition(circle1->center.x,circle1->center.y);
 	                     // node = space->getScreenPosition(circle1->arc_position.x,circle1->arc_position.y);
 	                     node = space->getScreenPosition(circle1->arc_position.x,circle1->arc_position.y);
 	                     ofSetHexColor(0xFF0000);
 	                     if(checkIntersect(circle1)){ //If the lines are crossing
 	                         digitalFis.flash(PF,(fis_color)toolKit.dice(3));
 	                         // digitalFis.flash(PF,(fis_color)getAgent.condition);
 	                     }
 
 	                     ofLine(center.x,center.y,node.x,node.y); //Change Line Color
 	                 break;
 
 	                 case 1:
 	                     circle2->piradToPosition( ofMap(getAgent.posi.x, -1.,1.,0.,1.));     
 	                     center = space->getScreenPosition(circle2->center.x,circle2->center.y);
 	                     node = space->getScreenPosition(circle2->arc_position.x,circle2->arc_position.y);
 	                     ofSetHexColor(0x00FF77);
 	                     if(checkIntersect(circle2)){ //If the lines are crossing
 	                         digitalFis.flash(TB,(fis_color)toolKit.dice(3));
 	                     }
 	                     ofLine(center.x,center.y,node.x,node.y);                
 	                 break;
 
 	                 case 2:
 	                     circle3->piradToPosition( ofMap(getAgent.posi.x, -1.,1.,0.,1.));     
 	                     center = space->getScreenPosition(circle3->center.x,circle3->center.y);
 	                     node = space->getScreenPosition(circle3->arc_position.x,circle3->arc_position.y);
 	                     ofSetHexColor(0x0000FF);
 	                     if(checkIntersect(circle3)){ //If the lines are crossing
 	                         digitalFis.flash(GT,(fis_color)toolKit.dice(3));
 	                     }
 	                     ofLine(center.x,center.y,node.x,node.y);                
 	                 break;
 
 	                 case 3:
 	                     circle4->piradToPosition( ofMap(getAgent.posi.x, -1.,1.,0.,1.));     
 	                     center = space->getScreenPosition(circle4->center.x,circle4->center.y);
 	                     node = space->getScreenPosition(circle4->arc_position.x,circle4->arc_position.y);
 	                     ofSetHexColor(0xFFFF00);
 	                     if(checkIntersect(circle4)){ //If the lines are crossing
 	                         digitalFis.flash(BS,(fis_color)toolKit.dice(3));
 	                     }
 	                     ofLine(center.x,center.y,node.x,node.y);
 	                 break;
 
 	                 default:
 	                 break;
 
 	             }
 	             
 	//             getAgent.posi.x = node.x;  getAgent.posi.y = node.y;
 	                getAgent.posi.x = 0.;  getAgent.posi.y = 0.;
 	             	            
 	         } // end of for
 
 	     } // end of if
     }else { // end of if (stop_flg)

			//For Servo1
             circle1->piradToPosition( pirad_circle1 );     
             center = space->getScreenPosition(circle1->center.x,circle1->center.y);
             // node = space->getScreenPosition(circle1->arc_position.x,circle1->arc_position.y);
             node = space->getScreenPosition(circle1->arc_position.x,circle1->arc_position.y);
             ofSetHexColor(0xFF0000);
             if(checkIntersect(circle1)){ //If the lines are crossing
                 digitalFis.flash(PF,(fis_color)toolKit.dice(3));
                 // digitalFis.flash(PF,(fis_color)getAgent.condition);
             }
             ofLine(center.x,center.y,node.x,node.y); //Change Line Color

			//For Servo2
             circle2->piradToPosition( pirad_circle2 );     
             center = space->getScreenPosition(circle2->center.x,circle2->center.y);
             node = space->getScreenPosition(circle2->arc_position.x,circle2->arc_position.y);
             ofSetHexColor(0x00FF77);
             if(checkIntersect(circle2)){ //If the lines are crossing
                 digitalFis.flash(TB,(fis_color)toolKit.dice(3));
             }
             ofLine(center.x,center.y,node.x,node.y);                

             //For Servo3
             circle3->piradToPosition( pirad_circle3 );     
             center = space->getScreenPosition(circle3->center.x,circle3->center.y);
             node = space->getScreenPosition(circle3->arc_position.x,circle3->arc_position.y);
             ofSetHexColor(0x0000FF);
             if(checkIntersect(circle3)){ //If the lines are crossing
                 digitalFis.flash(GT,(fis_color)toolKit.dice(3));
             }
             ofLine(center.x,center.y,node.x,node.y);                

             //For Servo4
             circle4->piradToPosition( pirad_circle4 );     
             center = space->getScreenPosition(circle4->center.x,circle4->center.y);
             node = space->getScreenPosition(circle4->arc_position.x,circle4->arc_position.y);
             ofSetHexColor(0xFFFF00);
             if(checkIntersect(circle4)){ //If the lines are crossing
                 digitalFis.flash(BS,(fis_color)toolKit.dice(3));
             }
             ofLine(center.x,center.y,node.x,node.y);

     }
    
    
    
    ofSetColor(225);
    dekar.drawString("SPC : START SIMULATOR", 30, 35);
    
//    // circle1->piradToPosition( abs(sin(nxt)) );
//    circle1->piradToPosition( pirad_circle1 );     
//	center = space->getScreenPosition(circle1->center.x,circle1->center.y);
//	node = space->getScreenPosition(circle1->arc_position.x,circle1->arc_position.y);
//    ofSetHexColor(0xFF0000);
//    checkIntersect(circle1);
//    ofLine(center.x,center.y,node.x,node.y);
//
//    // circle2->piradToPosition( abs(sin(nxt)) );
//    circle2->piradToPosition( pirad_circle2 );     
//	center = space->getScreenPosition(circle2->center.x,circle2->center.y);
//	node = space->getScreenPosition(circle2->arc_position.x,circle2->arc_position.y);
//    ofSetHexColor(0x00FF77);
//    checkIntersect(circle2);
//    ofLine(center.x,center.y,node.x,node.y);
//
//    // circle3->piradToPosition( abs(sin(nxt)) );
//    circle3->piradToPosition( pirad_circle3 );     
//    center = space->getScreenPosition(circle3->center.x,circle3->center.y);
//    node = space->getScreenPosition(circle3->arc_position.x,circle3->arc_position.y);
//    ofSetHexColor(0x0000FF);
//    checkIntersect(circle3);
//    ofLine(center.x,center.y,node.x,node.y);
//
//    // circle4->piradToPosition( abs(sin(nxt)) );
//    circle4->piradToPosition( pirad_circle4 );     
//    center = space->getScreenPosition(circle4->center.x,circle4->center.y);
//    node = space->getScreenPosition(circle4->arc_position.x,circle4->arc_position.y);
//    ofSetHexColor(0xFFFF00);
//    checkIntersect(circle4);
//    ofLine(center.x,center.y,node.x,node.y);
//   
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == OF_KEY_RETURN){
    	stop_flg = ( (stop_flg-1)*(-1) ); //Invert the value
    } else if (key == 0x20){
    	stop_flg = ( (stop_flg-1)*(-1) ); //Invert the value
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

bool ofApp::checkIntersect(slCircular *target){

	// if(target == circle2)ofSetHexColor(0xFFFFFF);

	slCircular* another;

	for(int i = 0; i<4; i++){

		switch (i){

			case 0:
				another = circle1;
				break;

			case 1:
				another = circle2;
				break;

			case 2:
				another = circle3;			
				break;

			case 3:
				another = circle4;			
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


void ofApp::displayAgents(){

        //Draw them
        for(int i=0 ; i <agent_count; i++)
        {
            if( reset_flg )continue; //If reset is invoked by other thread, do nothing (mutex).
            Agent getAgent;
            gismodel.getAnAgent(i, &getAgent);
            
            //Ignore dead agent
            if(gismodel.isAgentActive(getAgent)==false)continue;
            
            //Convert the position to pixel
            // screen_position posi = convertPositionForScreen(getAgent.posi.x,getAgent.posi.y);
            sl_scaled_position tmp_posi;
            tmp_posi.x = getAgent.posi.x;	tmp_posi.y = getAgent.posi.y;
            sl_screen_position posi = space->getScreenPosition(tmp_posi);
            
            //Draw
            switch(getAgent.layer)
            {
                case 0:
                    ofSetColor(255,255,255); //Set White
                    //ofNoFill();
                    break;
  
                case 1:
                    ofSetColor(255,0,0); //Set Red
                    //ofFill();
                    break;
  
                case 2:
                    ofSetColor(0,255,0); //Set Green
                    //ofFill();
                    break;
  
                case 3:
                    ofSetColor(0,0,255); //Set Blue
                    //ofFill();
                    break;
    
                default:
                    ofSetColor(255,255,0); //else is white
                    //ofNoFill();
                    break;
                    
            }
  
            //ofFill();		// draw "filled shapes"
            float size = (float)space->getLengthForScreen(getAgent.size);
            //Draw Square
            ofRect(posi.x-(size*0.5),posi.y-(size*0.5), size, size);
            //Draw View
            ofNoFill();
            ofCircle(posi.x, posi.y,(float)space->getLengthForScreen(getAgent.view));
            //Draw Number
            ofPushMatrix();
            //Create drawing String
            char num_str[10];
            sprintf(num_str, "%d", getAgent.ag_id); //Create
            ofTranslate( posi.x , posi.y ); // Now, display it on center
            //Scale it
            ofScale( ( getAgent.size * FONT_SIZE_MODIFY ), ( getAgent.size * FONT_SIZE_MODIFY ) );
            //Set Color
            ofSetColor(255);
            ofPopMatrix();
            
            
        } // end of for


}

void ofApp::setupSeeds(){

	    //Initialize seedArray
    for(int i=0; i<SEED_ARRAY_MAX;i++)
    {
        seeds[i] = 0;
    }

    //--------------------------------------------------------//
    
    //Add Default seeds
    
    int tmp_count; //To Storage count for treating  id and name at same time
    
    //Add a Seed 0
    //AgentSeed aSeed0(0, "voidAgent", .22, .03, .3); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    AgentSeed aSeed0(0, "voidAgent", .22, .1, 2.); //Create seed data. when init, sometimes same id is generated. add 1 to avoid
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed0);//Add it to gismodel
    seed_names[tmp_count] = aSeed0.getName(); // Take the name
    
    //Add a Seed 1
    AgentSeed aSeed1(1,"voryoQ" , .3, .5, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed1);//Add it to gismodel
    seed_names[tmp_count] = aSeed1.getName(); // Take the name
    
    //Add a Seed 2
    AgentSeed aSeed2(2, "biotope", .2, .4, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed2);//Add it to gismodel
    seed_names[tmp_count] = aSeed2.getName(); // Take the name
    
    //Add a Seed 3
    AgentSeed aSeed3(3, "snd", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed3);//Add it to gismodel
    seed_names[tmp_count] = aSeed3.getName(); // Take the name
    
    //Add a Seed 4
    AgentSeed aSeed4(4,"LS", .5, .14, .5); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed4);//Add it to gismodel
    seed_names[tmp_count] = aSeed4.getName(); // Take the name
    
    //Add a Seed 5
    AgentSeed aSeed5(5,"brossum", .2, .4, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed5);//Add it to gismodel
    seed_names[tmp_count] = aSeed5.getName(); // Take the name
    
    //Add a Seed 6
    AgentSeed aSeed6(6,"film", .2, .4, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed6);//Add it to gismodel
    seed_names[tmp_count] = aSeed6.getName(); // Take the name

    //Add a Seed 7
    AgentSeed aSeed7(7, "KICKd", .2, .4, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed7);//Add it to gismodel
    seed_names[tmp_count] = aSeed7.getName(); // Take the name
    
    //Add a Seed 8
    AgentSeed aSeed8(8, "sonir-hat", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed8);//Add it to gismodel
    seed_names[tmp_count] = aSeed8.getName(); // Take the name

    //Add a Seed 9
    AgentSeed aSeed9(9,"Robots" , .3, .5, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed9);//Add it to gismodel
    seed_names[tmp_count] = aSeed9.getName(); // Take the name

    //Add a Seed 10
    AgentSeed aSeed10(10,"137beats" , .3, .5, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed10);//Add it to gismodel
    seed_names[tmp_count] = aSeed10.getName(); // Take the name

    //Add a Seed 11
    AgentSeed aSeed11(11,"Laura" , .3, .5, .2); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed11);//Add it to gismodel
    seed_names[tmp_count] = aSeed11.getName(); // Take the name
    
    //Add a Seed 12
    AgentSeed aSeed12(12, "smoky", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed12);//Add it to gismodel
    seed_names[tmp_count] = aSeed12.getName(); // Take the name

    //Add a Seed 13
    AgentSeed aSeed13(13,"ePH", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed13);//Add it to gismodel
    seed_names[tmp_count] = aSeed13.getName(); // Take the name

    //Add a Seed 14
    AgentSeed aSeed14(14,"minimal", .2, .47, .3); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed14);//Add it to gismodel
    seed_names[tmp_count] = aSeed14.getName(); // Take the name

    
    //Add a Seed 15
    AgentSeed aSeed15(15,"*Piano", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed15);//Add it to gismodel
    seed_names[tmp_count] = aSeed15.getName(); // Take the name

    //Add a Seed 16
    AgentSeed aSeed16(16,"*Gismo", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed16);//Add it to gismodel
    seed_names[tmp_count] = aSeed16.getName(); // Take the name

    //Add a Seed 17
    AgentSeed aSeed17(17,"*Guitar", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed17);//Add it to gismodel
    seed_names[tmp_count] = aSeed17.getName(); // Take the name

    //Add a Seed 18
    AgentSeed aSeed18(18,"*Trombone", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed18);//Add it to gismodel
    seed_names[tmp_count] = aSeed18.getName(); // Take the name
    
    //Add a Seed 19
    AgentSeed aSeed19(19,"*Bass", .2, .47, .05); //Create seed data. when init, sometimes same id is generated. add 1 to avoid it.
    tmp_count = gismodel.getSeedCount();
    seeds[tmp_count] = gismodel.addSeed(&aSeed19);//Add it to gismodel
    seed_names[tmp_count] = aSeed19.getName(); // Take the name
    

}


void ofApp::sendData(){

    ofxOscMessage m;
    m.setAddress("/message");
    m.addFloatArg(0.9f);
    server.sendMessage(m);

}

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
        

		//Message for circle1
		if(m.getAddress() == "/circleControl"){
            
            
            float *length;
            slCircular* circle;
            
			string target = m.getArgAsString(0); //Get the 2nd address
			if(target=="/circle1"){
				length = &pirad_circle1;
				circle = circle1;
			}
			else if (target =="/circle2"){
				length = &pirad_circle2;
				circle = circle2;
			}
            else if (target =="/circle3"){
                length = &pirad_circle3;
                circle = circle3;
            }
            else if (target =="/circle4"){
                length = &pirad_circle4;
                circle = circle4;
            }
            
			*length = m.getArgAsFloat(1);
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
