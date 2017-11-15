#ifndef MUSIC_H
#define MUSIC_H
#include "common.h"
#define MARIO_MULTIPLIER_FREQUENCY 4
#define MARIO_MULTIPLIER_LENGTH (2.0f/3.0f)
const uint16_t music_frequency[] = {
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*164,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*246,
	MARIO_MULTIPLIER_FREQUENCY*233,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*440,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*247,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*164,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*246,
	MARIO_MULTIPLIER_FREQUENCY*233,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*440,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*247,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*370,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*311,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*207,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*370,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*311,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*523,
	MARIO_MULTIPLIER_FREQUENCY*523,
	MARIO_MULTIPLIER_FREQUENCY*523,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*370,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*311,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*207,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*311,
	MARIO_MULTIPLIER_FREQUENCY*296,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*440,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*220,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*196,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*330,
	MARIO_MULTIPLIER_FREQUENCY*392,
	MARIO_MULTIPLIER_FREQUENCY*523,
	MARIO_MULTIPLIER_FREQUENCY*660,
	MARIO_MULTIPLIER_FREQUENCY*784,
	MARIO_MULTIPLIER_FREQUENCY*660,
	MARIO_MULTIPLIER_FREQUENCY*207,
	MARIO_MULTIPLIER_FREQUENCY*262,
	MARIO_MULTIPLIER_FREQUENCY*311,
	MARIO_MULTIPLIER_FREQUENCY*415,
	MARIO_MULTIPLIER_FREQUENCY*523,
	MARIO_MULTIPLIER_FREQUENCY*622,
	MARIO_MULTIPLIER_FREQUENCY*830,
	MARIO_MULTIPLIER_FREQUENCY*622,
	MARIO_MULTIPLIER_FREQUENCY*233,
	MARIO_MULTIPLIER_FREQUENCY*294,
	MARIO_MULTIPLIER_FREQUENCY*349,
	MARIO_MULTIPLIER_FREQUENCY*466,
	MARIO_MULTIPLIER_FREQUENCY*587,
	MARIO_MULTIPLIER_FREQUENCY*698,
	MARIO_MULTIPLIER_FREQUENCY*932,
	MARIO_MULTIPLIER_FREQUENCY*932,
	MARIO_MULTIPLIER_FREQUENCY*932,
	MARIO_MULTIPLIER_FREQUENCY*932,
	MARIO_MULTIPLIER_FREQUENCY*1046
};

const uint16_t music_length[] = {
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*200,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*60
};

const uint16_t music_delay[] = {
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*0,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*500,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*0,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*150,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*900,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*500,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*1100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*500,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*1300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*500,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*50,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*100,
	MARIO_MULTIPLIER_LENGTH*300,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*700,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*580,
	MARIO_MULTIPLIER_LENGTH*580,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*580,
	MARIO_MULTIPLIER_LENGTH*580,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*580,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*130,
	MARIO_MULTIPLIER_LENGTH*5000,
};

#define LOST_MULTIPLIER_FREQUENCY 2
const uint16_t music_lost_frequency[] = {
	LOST_MULTIPLIER_FREQUENCY*1046, 
	LOST_MULTIPLIER_FREQUENCY*784, 
	LOST_MULTIPLIER_FREQUENCY*659, 
	LOST_MULTIPLIER_FREQUENCY*880, 
	LOST_MULTIPLIER_FREQUENCY*988, 
	LOST_MULTIPLIER_FREQUENCY*880, 
	LOST_MULTIPLIER_FREQUENCY*831, 
	LOST_MULTIPLIER_FREQUENCY*932, 
	LOST_MULTIPLIER_FREQUENCY*831, 
	LOST_MULTIPLIER_FREQUENCY*784, 
	LOST_MULTIPLIER_FREQUENCY*740, 
	LOST_MULTIPLIER_FREQUENCY*784
};

const uint16_t music_lost_length[] = {
	100, 100, 100, 50, 50, 50, 50, 50, 50, 50, 50, 200
};

const uint16_t music_lost_delay[] = {
	50, 50, 50, 50, 50, 50, 50, 50, 50, 20, 20, 1000
};
void wave_frequency(uint32_t frequency);
#endif