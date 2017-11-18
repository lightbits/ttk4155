#ifndef SHARED_H
#define SHARED_H
const uint8_t MODE_PLAY = 0;
const uint8_t MODE_MUSIC = 1;
const uint8_t MODE_CONTROLS = 2;
const uint8_t MODE_MENU = 3;
const uint8_t MODE_LOST = 4;
typedef struct 
{
	uint8_t angle; // joystick or remote controller angle
	uint8_t position; // position of slider or (nothing at all!)
	uint8_t shoot; // 1 (active) or 0 (inactive) joystick button or remote button
	uint8_t mode; // game mode
} can_msg_node1_to_node2;
typedef struct 
{
	uint8_t light_blocked; // 1 (blocked) or 0 (not blocked)
} can_msg_node2_to_node1;
#endif