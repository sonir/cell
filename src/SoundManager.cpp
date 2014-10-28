//
//  SoundManager.cpp
//  cell
//
//  Created by sonir on 10/28/14.
//
//

#include "SoundManager.h"

SoundManager::SoundManager(){
    
//    intervalTimer = new slMetro(SENDING_INTERVAL);
    droneServer = new DroneServer;
    
}

bool SoundManager::degradeCheck(){
    

    
}

void SoundManager::mappingToDrone(){
    
    drone_params.twitter_announce = 0;
    drone_params.twitter_log = 0;
    drone_params.synth_pitch1_vol = model.ag[0].hp;
    drone_params.synth_pitch2_vol = model.ag0.hp;
    drone_params.synth_pitch3_vol = model.ag0.hp;
    drone_params.synth_pitch4_vol = model.ag1.hp;
    drone_params.synth_pitch5_vol = model.ag1.hp;
    drone_params.synth_pitch6_vol = model.ag1.hp;
    drone_params.synth_pitch7_vol = model.ag2.hp;
    drone_params.synth_pitch8_vol = model.ag2.hp;
    drone_params.synth_pitch9_vol = model.ag2.hp;
    drone_params.synth_pitch10_vol = model.ag3.hp;
    drone_params.synth_pitch11_vol = model.ag3.hp;
    drone_params.synth_pitch12_vol = model.ag3.hp;
    drone_params.synth_pitch13_vol = model.ag3.hp;

    //Mk degrade Param
    degradeCheck();
    drone_params.degrade_on= 0;
    drone_params.degrade_sample_rate = 1.0f;
    drone_params.vocoder_on = 0;
    drone_params.vocoder_dry = 0.0f;
    drone_params.reverb_on = 0;
    drone_params.reverb_dry = 0.0f;
    drone_params.autopan_on = 0;
    drone_params.autopan_rate = 0.0f;
    drone_params.autopan_ammount = 0.7f;
    drone_params.autopan_randomness = 1.0f;
    drone_params.autofilter_on = 0;
    drone_params.auto_filter_ammount = 0.7f;
    drone_params.auto_filter_rate = 0.7f;
    drone_params.auto_filter_cutoff = 0.7f;
    
    
}


void SoundManager::update(agent_snap_t snap){
    
    model.ag0 = snap.ag0;
    model.ag1 = snap.ag1;
    model.ag2 = snap.ag2;
    model.ag3 = snap.ag3;
    
    droneServer->send();
    
}