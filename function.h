#ifndef _FUNCTION_H_
#define _FUNCTION_H_ 
#include <vector>
void draw_screen(unsigned *data, int size, int index = 0);
void draw_v_screen(std::vector<unsigned> &data,int index = 0);
void blend(unsigned &a, unsigned b);
void over_draw_screen(unsigned *data, int size, int width, int index = 0);
#endif