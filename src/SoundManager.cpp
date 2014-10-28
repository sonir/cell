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

int SoundManager::degradeCheck(){
    
    for(int i=0; i<ARM_NUM; i++){
        
        if(model.ag[i].hp >= JUDGE_DEGRADER) return i; //Return the ag_id
        
    }

    return -1;
    
}

int SoundManager::autoPanCheck(){
    
    for(int i=0; i<ARM_NUM; i++){
        
        if(model.ag[i].hp <= JUDGE_AUTOPAN) return i; //Return the ag_id
        
    }
    
    return -1;
    
}

void SoundManager::mappingToDrone(){
    
    drone_params.twitter_announce = 0;
    drone_params.twitter_log = 0;
    drone_params.synth_pitch1_vol = model.ag[0].hp;
    drone_params.synth_pitch2_vol = model.ag[0].hp;
    drone_params.synth_pitch3_vol = model.ag[0].hp;
    drone_params.synth_pitch4_vol = model.ag[1].hp;
    drone_params.synth_pitch5_vol = model.ag[1].hp;
    drone_params.synth_pitch6_vol = model.ag[1].hp;
    drone_params.synth_pitch7_vol = model.ag[2].hp;
    drone_params.synth_pitch8_vol = model.ag[2].hp;
    drone_params.synth_pitch9_vol = model.ag[2].hp;
    drone_params.synth_pitch10_vol = model.ag[3].hp;
    drone_params.synth_pitch11_vol = model.ag[3].hp;
    drone_params.synth_pitch12_vol = model.ag[3].hp;
    drone_params.synth_pitch13_vol = model.ag[3].hp;

    //Mk degrade Param
    int checked_deg = degradeCheck();
    if(checked_deg!=-1){
        drone_params.degrade_on= 1;
        drone_params.degrade_sample_rate = (float)scale(model.ag[checked_deg].hp, 1.0, 0.7, 0.0, 1.0);
    } else{
        drone_params.degrade_on= 0;
        drone_params.degrade_sample_rate = 1.0f;
    }
    //Mk autoPan param
    int checked_pan = autoPanCheck();
    if(checked_deg!=-1){
        drone_params.autopan_on = 1;
        drone_params.autopan_rate = (float)scale(model.ag[checked_deg].hp, 0.4, 0.0, 0.0, 1.0);
        drone_params.autopan_ammount = 0.7f;
        drone_params.autopan_randomness = 1.0f;
    
    } else{
        drone_params.autopan_on = 0;
        drone_params.autopan_rate = 0.0f;
        drone_params.autopan_ammount = 0.7f;
        drone_params.autopan_randomness = 1.0f;
    }
    
    drone_params.vocoder_on = 0;
    drone_params.vocoder_dry = 0.0f;
    
    //Reverb
    drone_params.reverb_on = 1;
    drone_params.reverb_dry = (float)scale(model.ag[1].circumference_posi, 1.0, -1.0, 1.0, 0.0);
    //AutoFilter
//    drone_params.autofilter_on = 0;
    drone_params.autofilter_on = 0;
//    drone_params.auto_filter_ammount = 0.7f;
    drone_params.auto_filter_ammount = (float)scale(model.ag[0].circumference_posi, 1.0, -1.0, 1.0, 0.0);
    drone_params.auto_filter_rate = 0.7f;
//    drone_params.auto_filter_cutoff = 0.7f;
    drone_params.auto_filter_cutoff = 0.5f;
    
}


void SoundManager::update(agent_snap_t snap){
    
    model.ag[0] = snap.ag[0];
    model.ag[1] = snap.ag[1];
    model.ag[2] = snap.ag[2];
    model.ag[3] = snap.ag[3];
    this->mappingToDrone();
    droneServer->send(drone_params);
    
}