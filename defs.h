#ifndef __DEFS_H__
#define __DEFS_H__

const int VOID = 0;
const int WALL = 1;
const int GOAL = 2;
const int LOAD = 3;
const int COMP = 4;
const int PLAY = 5;
const int D_GOAL = 6;
const int W_SIZE = 10;
const int H_SIZE = 7;
const int BLOCK_SIZE = 32;

typedef struct{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
}aRGB;

typedef union{
	unsigned data;
	aRGB argb;
}union_data;

#endif