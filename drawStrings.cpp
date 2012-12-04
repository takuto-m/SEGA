#include "drawStrings.h"
#include "defs.h"
#include "function.h"

#include"GameLib\Framework.h"

using namespace GameLib;
using namespace draw_strings;
/*
DRAW_STRINGS_CLASS::DRAW_STRINGS_CLASS(){
	string_image = new IMAGE_CLASS("font.dds");
	return;
}*/

DRAW_STRINGS_CLASS* DRAW_STRINGS_CLASS::m_instance = 0;

DRAW_STRINGS_CLASS::DRAW_STRINGS_CLASS(const char *font_file_name){
	string_image = new IMAGE_CLASS(font_file_name);
	return;
}


DRAW_STRINGS_CLASS::~DRAW_STRINGS_CLASS(){
	SAFE_DELETE(string_image);
	return;
}

void DRAW_STRINGS_CLASS::create(const char *font_file_name){
	STRONG_ASSERT(!m_instance && "ìÒå¬çÏÇÈÇÃÇÕÉ_ÉÅÇÊÅH");
	m_instance = new DRAW_STRINGS_CLASS(font_file_name);
	return;
}

void DRAW_STRINGS_CLASS::destroy(){
	SAFE_DELETE(m_instance);
	return;
}

DRAW_STRINGS_CLASS * DRAW_STRINGS_CLASS::instance(){
	return m_instance;
}

void DRAW_STRINGS_CLASS::draw_string(int x,int y,const char * string,unsigned color)const{
	int dstX = x;
	int dstY = y;

	const int CHAR_WIDTH = 8;
	const int CHAR_HEIGHT = 16;

	for (int i = 0; string[i] != '\0';i++){
		int t = string[i];
		//cout << t << endl; 
		if (t < 32 || t >= 128){
			t = 127;
		}
		t -= 32;//
		int srcX = t % 16;
		int srcY = t / 16;
		
		m_instance->draw(dstX,dstY,srcX,srcY,CHAR_WIDTH,CHAR_HEIGHT,color);
		dstX += CHAR_WIDTH;
	}
	return;
}

void DRAW_STRINGS_CLASS::draw(int dstX, int dstY, int srcX, int srcY, int char_width, int char_height, unsigned color){
	int windowWidth = Framework::instance().width();
	unsigned *vram =  Framework::instance().videoMemory();
	unsigned *data = string_image->data();
	union_data a,b;
	b.data = color;
	for (int i = 0; i < char_height; i++){
		for (int j = 0; j < char_width; j++){
			a.data = data[(srcY*char_height+i)*string_image->width() + (srcX*char_width + j)];
			a.argb.blue = b.argb.blue;
			a.argb.green = b.argb.green;
			a.argb.red = b.argb.red;
			blend(vram[(dstY + i)*windowWidth + (dstX + j)],a.data);
				//data[(srcY*char_height+i)*string_image->width() + (srcX*char_width + j)]);
		}
	}
	return;
}
