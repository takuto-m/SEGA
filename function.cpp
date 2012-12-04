#include "function.h"
#include "GameLib\Framework.h"
#include "defs.h"
using namespace GameLib;


//配列とその長さを受け取ってインデックスの位置から描画を行う
void draw_screen(unsigned *data, int size, int index){
	unsigned *vram =  Framework::instance().videoMemory();
	int windowWidth = Framework::instance().width();
	for (int i = 0;i < size;i++){
		vram[i + index] = data[i];
	}
	return;
};

//上記のvector版
void draw_v_screen(std::vector<unsigned> &data, int index){
	unsigned *vram =  Framework::instance().videoMemory();
	int windowWidth = Framework::instance().width();
	for (unsigned i = 0;i < data.size();i++){
		vram[i + index] = data[i];
	}
	return;
};

void blend(unsigned &a, unsigned b){
	union_data x,y;
	y.data = a;	
	x.data = b;
		
	y.argb.red = x.argb.alpha * (x.argb.red - y.argb.red) / 255 + y.argb.red;
	y.argb.blue = x.argb.alpha * (x.argb.blue - y.argb.blue) / 255 + y.argb.blue;
	y.argb.green = x.argb.alpha * (x.argb.green - y.argb.green) / 255  + y.argb.green; 
	y.argb.alpha = std::max(x.argb.alpha,y.argb.alpha);
	a = y.data;
	return;
}

void over_draw_screen(unsigned *data, int size, int width, int index){
	unsigned *vram =  Framework::instance().videoMemory();
	int windowWidth = Framework::instance().width();
	for (int i = 0;i < size;i++){
		blend(vram[i+index],data[i]);
	}
	return;
}