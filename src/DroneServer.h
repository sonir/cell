//
//  DroneServer.h
//  cell
//
//  Created by sonir on 10/28/14.
//
//

#ifndef __cell__DroneServer__
#define __cell__DroneServer__

#define SERVER_IP "49.212.138.54"
#define SERVER_PORT 57122

#include <stdio.h>
#include "ofxOsc.h"

typedef struct drone_mes_t {
    
    int twitter_announce;
    int twitter_log;
    float synth_pitch1_vol;
    float synth_pitch2_vol;
    float synth_pitch3_vol;
    float synth_pitch4_vol;
    float synth_pitch5_vol;
    float synth_pitch6_vol;
    float synth_pitch7_vol;
    float synth_pitch8_vol;
    float synth_pitch9_vol;
    float synth_pitch10_vol;
    float synth_pitch11_vol;
    float synth_pitch12_vol;
    float synth_pitch13_vol;
    int degrade_on;
    float degrade_sample_rate;
    int vocoder_on;
    float vocoder_dry;
    int reverb_on;
    float reverb_dry;
    int autopan_on;
    float autopan_rate;
    float autopan_ammount;
    float autopan_randomness;
    int autofilter_on;
    float auto_filter_ammount;
    float auto_filter_rate;
    float auto_filter_cutoff;

} drone_mes_t;

class DroneServer{
    
	public:
        DroneServer();
        ofxOscSender server;
		drone_mes_t drone_param;
        void initParam();
        void send();
        void test();
        int foo;
    
};

#endif /* defined(__cell__DroneServer__) */
