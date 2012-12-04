#include "status.h"
using namespace cell_status;



STATUS_CLASS::STATUS_CLASS(int a){
	set_id(a);
	set_move_xy(0,0);
}

STATUS_CLASS::~STATUS_CLASS(){

}

int STATUS_CLASS::get_id(){
	return id;
}

int STATUS_CLASS::get_move_x(){
	return move_x;
}

int STATUS_CLASS::get_move_y(){
	return move_y;
}

void STATUS_CLASS::set_id(int a){
	id = a;
}

void STATUS_CLASS::set_move_xy(int x, int y){
	move_x = x;
	move_y = y;
}