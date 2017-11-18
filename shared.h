#ifndef SHARED_H
#define SHARED_H
const uint8_t MODE_PLAY = 0;
const uint8_t MODE_MUSIC = 1;
const uint8_t MODE_CONTROLS = 2;
const uint8_t MODE_MENU = 3;
const uint8_t MODE_LOST = 4;
typedef struct 
{
	uint8_t angle;
	uint8_t position;
	uint8_t shoot;
	uint8_t mode;
} can_msg_node1_to_node2;
typedef struct 
{
	uint8_t light_blocked;
} can_msg_node2_to_node1;
#endif