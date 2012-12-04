#include "title.h"
#include "GameLib\Framework.h"
#include "file.hpp"
#include "drawStrings.h"

using namespace draw_strings;
using namespace GameLib;
using namespace title_class;


TITLE_CLASS::TITLE_CLASS(){
	title_image = new IMAGE_CLASS("dummy.dds");
	cursor = 1;
	input = '\0';
	g_previous_input_w = false;
	g_previous_input_z = false;
	cout << "hoge" << endl;
	//title_image = new IMAGE_CLASS("title.dds");
}

TITLE_CLASS::~TITLE_CLASS(){
	delete title_image;
}

void TITLE_CLASS::draw(){

	if (getInput()){
		if (input == 'w'){
			cursor--;
			if (cursor == 0) cursor = 1;
		}else if (input == 'z'){
			cursor++;
			if (cursor == 5) cursor = 4;
		}
	}
	
	draw_screen(title_image->data(),title_image->width() * title_image->height(),0);
	DRAW_STRINGS_CLASS *ds = DRAW_STRINGS_CLASS::instance();
	ds->draw_string(0,0,"[MENU]",0x0000FF);
	ds->draw_string(20,20,"RETRY",0xFFFFFF);
	ds->draw_string(20,40,"GO TO STAGE SELECTION",0xFFFFFF);
	ds->draw_string(20,60,"GO TO TITLE",0xFFFFFF);
	ds->draw_string(20,80,"CONTINUE",0xFFFFFF);
	ds->draw_string(8,cursor*20,">",0xFFFFFF);
	return;
}

int TITLE_CLASS::get_transition(){
	return cursor;
}

bool TITLE_CLASS::getInput(){
	bool flag = true;
	bool input_w = Framework::instance().isKeyOn('w');
	bool input_z = Framework::instance().isKeyOn('z');

	if (!g_previous_input_w && input_w) input = 'w';
	else if (!g_previous_input_z && input_z) input = 'z';
	else flag = false;

	g_previous_input_w = input_w;
	g_previous_input_z = input_z;

	return(flag);
};
