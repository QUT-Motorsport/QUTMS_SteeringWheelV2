/*
 * heartbeat.h
 *
 *  Created on: Nov 22, 2022
 *      Author: n9996095
 */

#ifndef INC_HEARTBEAT_H_
#define INC_HEARTBEAT_H_

#define MAX_VCU 16

#include <stdbool.h>
#include <CAN_VCU.h>
#include <CAN_BMU.h>
#include <CAN_DVL.h>

extern VCU_HeartbeatState_t VCU_hbState_CTRL;
extern VCU_HeartbeatState_t VCU_hbState_DASH;
extern VCU_HeartbeatState_t VCU_hbState_EBS;
extern DVL_HeartbeatState_t DVL_hbState;
extern BMU_HeartbeatState_t BMU_hbState;

void setup_heartbeat();

// call every time checking CAN message queue to update heartbeat status of boards
bool check_heartbeat_msg(CAN_MSG_Generic_t *msg);

#endif /* INC_HEARTBEAT_H_ */
