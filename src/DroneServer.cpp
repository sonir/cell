//
//  DroneServer.cpp
//  cell
//
//  Created by sonir on 10/28/14.
//
//

#include "DroneServer.h"

DroneServer::DroneServer(){
    
    server.setup(SERVER_IP, SERVER_PORT);
    this->initParam();
    foo = 0;
    
}

void DroneServer::test(){
    
    ofxOscMessage m;
    m.setAddress("/droneTest");
    m.addFloatArg(0.137f);
    m.addIntArg(foo);
    server.sendMessage(m);
    
    foo++;
    
}

void DroneServer::send(){
    
    ofxOscMessage m;
    m.setAddress("/drone");
    m.addIntArg(drone_param.twitter_announce);
    m.addIntArg(drone_param.twitter_log);
    m.addFloatArg(drone_param.synth_pitch1_vol);
    m.addFloatArg(drone_param.synth_pitch2_vol);
    m.addFloatArg(drone_param.synth_pitch3_vol);
    m.addFloatArg(drone_param.synth_pitch4_vol);
    m.addFloatArg(drone_param.synth_pitch5_vol);
    m.addFloatArg(drone_param.synth_pitch6_vol);
    m.addFloatArg(drone_param.synth_pitch7_vol);
    m.addFloatArg(drone_param.synth_pitch8_vol);
    m.addFloatArg(drone_param.synth_pitch9_vol);
    m.addFloatArg(drone_param.synth_pitch10_vol);
    m.addFloatArg(drone_param.synth_pitch11_vol);
    m.addFloatArg(drone_param.synth_pitch12_vol);
    m.addFloatArg(drone_param.synth_pitch13_vol);
    m.addIntArg(drone_param.degrade_on);
    m.addFloatArg(drone_param.degrade_sample_rate);
    m.addIntArg(drone_param.vocoder_on);
    m.addFloatArg(drone_param.vocoder_dry);
    m.addIntArg(drone_param.reverb_on);
    m.addFloatArg(drone_param.reverb_dry);
    m.addIntArg(drone_param.autopan_on);
    m.addFloatArg(drone_param.autopan_rate);
    m.addFloatArg(drone_param.autopan_ammount);
    m.addFloatArg(drone_param.autopan_randomness);
	m.addIntArg(drone_param.autofilter_on);
    m.addFloatArg(drone_param.auto_filter_ammount);
    m.addFloatArg(drone_param.auto_filter_rate);
    m.addFloatArg(drone_param.auto_filter_cutoff);
    server.sendMessage(m);
    
    
}

void DroneServer::initParam(){

    drone_param.twitter_announce = 0;
    drone_param.twitter_log = 0;
    drone_param.synth_pitch1_vol = 1.0f;
    drone_param.synth_pitch2_vol = 1.0f;
    drone_param.synth_pitch3_vol = 1.0f;
    drone_param.synth_pitch4_vol = 1.0f;
    drone_param.synth_pitch5_vol = 1.0f;
    drone_param.synth_pitch6_vol = 1.0f;
    drone_param.synth_pitch7_vol = 1.0f;
    drone_param.synth_pitch8_vol = 1.0f;
    drone_param.synth_pitch9_vol = 1.0f;
    drone_param.synth_pitch10_vol = 1.0f;
    drone_param.synth_pitch11_vol = 1.0f;
    drone_param.synth_pitch12_vol = 1.0f;
    drone_param.synth_pitch13_vol = 1.0f;
    drone_param.degrade_on= 0;
    drone_param.degrade_sample_rate = 1.0f;
    drone_param.vocoder_on = 0;
    drone_param.vocoder_dry = 0.0f;
    drone_param.reverb_on = 0;
    drone_param.reverb_dry = 0.0f;
    drone_param.autopan_on = 0;
    drone_param.autopan_rate = 0.0f;
    drone_param.autopan_ammount = 0.7f;
    drone_param.autopan_randomness = 1.0f;
    drone_param.autofilter_on = 0;
    drone_param.auto_filter_ammount = 0.7f;
    drone_param.auto_filter_rate = 0.7f;
    drone_param.auto_filter_cutoff = 0.7f;

}