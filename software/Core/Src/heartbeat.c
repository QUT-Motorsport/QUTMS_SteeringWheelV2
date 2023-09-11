/*
 * heartbeat.c
 *
 *  Created on: Nov 22, 2022
 *      Author: n9996095
 */

#include "heartbeat.h"

VCU_HeartbeatState_t VCU_hbState_CTRL;
VCU_HeartbeatState_t VCU_hbState_DASH;
VCU_HeartbeatState_t VCU_hbState_EBS;
DVL_HeartbeatState_t DVL_hbState;
BMU_HeartbeatState_t BMU_hbState;

void setup_heartbeat() {
//	// send heartbeat every 100ms
//	timer_heartbeat = timer_init(100, true, heartbeat_timer_cb);
//
//	// setup constants
//	heartbeats.heartbeat_timeout = HEARTBEAT_TIMEOUT;
//
//	// reset heartbeat timers to default
//	heartbeat_timeout_reset();
//
//	// start timer
//	timer_start(&timer_heartbeat);
//
//	heartbeat_print_timer_start = HAL_GetTick();
}

// call every time checking CAN message queue to update heartbeat status of boards
bool check_heartbeat_msg(CAN_MSG_Generic_t *msg) {
	bool hb_message = false;

	uint8_t idx = (msg->ID & 0xF);
	uint32_t masked_id = (msg->ID & ~0xF);

	if (masked_id == BMU_Heartbeat_ID) {
		hb_message = true;

		Parse_BMU_Heartbeat(msg->data, &BMU_hbState);
	} else if (masked_id == VCU_Heartbeat_ID) {
		hb_message = true;

		if (idx < MAX_VCU) {
			// update heartbeat structs
			if (idx == VCU_ID_CTRL) {
				Parse_VCU_Heartbeat(msg->data, &VCU_hbState_CTRL);
			} else if (idx == VCU_ID_DASH) {
				Parse_VCU_Heartbeat(msg->data, &VCU_hbState_DASH);

			} else if (idx == VCU_ID_EBS) {
				Parse_VCU_Heartbeat(msg->data, &VCU_hbState_EBS);
			}
		}
	} else if (masked_id == DVL_Heartbeat_ID) {
		hb_message = true;
		Parse_DVL_Heartbeat(msg->data, &DVL_hbState);
	}

	return hb_message;
}
