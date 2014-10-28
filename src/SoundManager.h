//
//  SoundManager.h
//  cell
//
//  Created by sonir on 10/28/14.
//
//

#ifndef __cell__SoundManager__
#define __cell__SoundManager__

//Sound Setup
#define JUDGE_DEGRADER 0.7
#define JUDGE_AUTOPAN 0.3

#include <stdio.h>
#include "DroneServer.h"
#include "cellSetup.h"
#include "slCellModel.h"
#include "slEuclid.h"

typedef struct agent_snap_t {
    
    agent ag[4];
    
} agent_snap_t;


class SoundManager {
    
    public:
        SoundManager();
        int degradeCheck();
        int autoPanCheck();
        void mappingToDrone();
        void update(agent_snap_t snap);
        DroneServer *droneServer;
    
    private:
        agent_snap_t model;
        drone_mes_t drone_params;
    
};

#endif /* defined(__cell__SoundManager__) */
