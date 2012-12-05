#include"./soukoban.hpp"
#include"GameLib\Framework.h"
#include"defs.h"
#include "function.h"
#include <algorithm>
#include<string>
#include<fstream>
#include<iostream>




//using namespace std;
using namespace GameLib;
using namespace soukoban;


SOUKOBAN_CLASS::SOUKOBAN_CLASS(char* filename){
    /*char input_data[] ="\
###.######\
#     ####\
# .   ##p#\
##      o \
## ##     \
#.      # \
##.###  # ";*/
	char *input_data = read_map(filename);
	GameLib::cout << input_data << endl;
	printf("%s\n",input_data);				
	//initialize
	clearFlag = false;
	input = '\0';
	g_previous_input_a = false;
    g_previous_input_w = false;
    g_previous_input_s = false;
    g_previous_input_z = false;
	animation_flag = 0;
	itnum = 0;
	//Initialize previous screen
	unsigned *vram = Framework::instance().videoMemory();
	int windowWidth = Framework::instance().width();
	int windowHeight = Framework::instance().height();
	for (int i = 0; i < windowWidth * windowHeight; i++){
		vram[i] = 0x000000;
	}

	//Read map data
	image = new IMAGE_CLASS("nimotsuKunImage2.dds");
	object[VOID] = getObject(IMAGE_ID_VOID);
	object[WALL] = getObject(IMAGE_ID_WALL);
	object[GOAL] = getObject(IMAGE_ID_GOAL);
	object[LOAD] = getObject(IMAGE_ID_LOAD);
	object[PLAY] = getObject(IMAGE_ID_PLAY);
	delete image;

    //Memory allocation for map
	for(int i=0; i < W_SIZE * H_SIZE;i++){
		map.push_back(VOID);
		//map[i].set_move_xy(0,0);
		for (int j = 0; j < BLOCK_SIZE*BLOCK_SIZE;j++)
			background.push_back(0);
	}
	int k = 0;
    for(int i = 0; i < H_SIZE;i++){
        for(int j = 0; j < W_SIZE; j++){
            //while(input_data[k] == '\t') k++;
            switch(input_data[k]){
                case '#': map[i*W_SIZE+j].set_id(WALL); break;
                case ' ': map[i*W_SIZE+j].set_id(VOID); break;
                case 'o': map[i*W_SIZE+j].set_id(LOAD); break;
				case '.': map[i*W_SIZE+j].set_id(GOAL); break;
                case 'O': map[i*W_SIZE+j].set_id(D_GOAL); break;
                case 'c': map[i*W_SIZE+j].set_id(COMP); break;
                case 'p': 
					map[i*W_SIZE+j].set_id(PLAY);
					x=j;
					y=i;
					set_player(j,i);
					break;
				case '\n': j--; break;
                default :
					GameLib::cout << input_data[k] << endl;
					break;
            }	
			
			k++;
        }
    }
    if (x < 0|| x >= W_SIZE || y < 0 || y >= H_SIZE){
        GameLib::cout << "Error:Bad location of player!" << endl;
        finish();
        exit(1);
    }

    //draw initial graphics
    draw(0);
	delete[] input_data;
    return;
}

char *SOUKOBAN_CLASS::read_map(char *filename){
	std::ifstream ifs(filename);
	std::string str;

	ifs.seekg(0,std::fstream::end);//ファイルの末尾へ
	int eofPos = ifs.tellg();
	ifs.seekg(0,std::fstream::beg);//ファイルの先頭へ
	int begPos = ifs.tellg();
	int size = eofPos - begPos; //ファイルサイズ取得
	char* buf = new char [size]; 
	memset(buf, 0, size);//メモリを0で初期化
	ifs.read(buf, size);//読み込み
	ifs.close();
	GameLib::cout << size << endl;
	return buf;
}

SOUKOBAN_CLASS::~SOUKOBAN_CLASS(){
	//delete image;
	for (int i = 0; i < 7;i++) {
		switch(i){
		case VOID:
		case WALL:
		case GOAL:
		case LOAD:
		case PLAY:
			delete[] object[i];
		default:
			break;
		}
	}
}

bool SOUKOBAN_CLASS::getClearFlag(){
	return(clearFlag);
}

void SOUKOBAN_CLASS::animation(){
	const int ITERATION = BLOCK_SIZE;
	animation_flag = 1;
	itnum ++;

	if (itnum == BLOCK_SIZE){
		if (ifclear()){
			clearFlag = true;
			return;
		}
		animation_flag = 0;
		itnum = 0;
		for (int i = 0; i < W_SIZE * H_SIZE;i++)
			map[i].set_move_xy(0,0);

	}
	draw(itnum);
	return;
}

int SOUKOBAN_CLASS::getInput(){
	if (animation_flag){
		return(1);
	}
	bool flag = true;
	bool input_a = Framework::instance().isKeyOn('a');
	bool input_w = Framework::instance().isKeyOn('w');
	bool input_s = Framework::instance().isKeyOn('s');
	bool input_z = Framework::instance().isKeyOn('z');
	bool input_q = Framework::instance().isKeyOn('q');

	if (!g_previous_input_a && input_a) input = 'a';
	else if (!g_previous_input_w && input_w) input = 'w';
	else if (!g_previous_input_s && input_s) input = 's';
	else if (!g_previous_input_z && input_z) input = 'z';
	else if (input_q) input = 'q';
	else flag = false;

	g_previous_input_a = input_a;
	g_previous_input_w = input_w;
	g_previous_input_s = input_s;
	g_previous_input_z = input_z;

	if (flag) return(1);
	else return(0);
};

void SOUKOBAN_CLASS::updateGame(){
	if (animation_flag) return;

    int next_x = x;
    int next_y = y;
    int vec_x = 0;
    int vec_y = 0;
    switch(input){
        case 'a':
            vec_x = -1;
            break;
        case 's':
            vec_x = 1;
            break;
        case 'z':
            vec_y = 1;
            break;
        case 'w':
            vec_y = -1;
            break;
        case 'q':
            GameLib::cout <<"Game over!!"<<endl; 
            finish();
            exit(0);
        default:
            break;
    }
    next_x += vec_x;
    next_y += vec_y;
    if (next_x < 0 || next_x >= W_SIZE || next_y < 0 || next_y >= H_SIZE){
        GameLib::cout << "Can't move!" << endl;
        return ;
    }
	
	switch (map[next_y*W_SIZE+next_x].get_id()){
        case GOAL:
        case VOID:
            set_player(next_x,next_y);
            break;
        case WALL:
            GameLib::cout << "Can't move" << endl;
            break;
        case COMP:
            if (judge(vec_x,vec_y)){
				map[next_y*W_SIZE+next_x].set_id(GOAL);
				set_player(next_x,next_y);
				map[next_y*W_SIZE+next_x].set_move_xy(-vec_x,-vec_y);
            }
            break;
        case LOAD:
            judge(vec_x,vec_y);
            break;
        case PLAY:
            GameLib::cout <<"Plaese input key from [a,w,s,z]" << endl;
            break;
        default:
            break;
    }
        
};

int SOUKOBAN_CLASS::judge(int a,int b){
	int next_x = x + a;
	int next_y = y + b;
	int next_load_x = next_x + a;
	int next_load_y = next_y + b;
	switch(map[next_load_y*W_SIZE+next_load_x].get_id()){
		case VOID:
			map[next_load_y*W_SIZE+next_load_x].set_id(LOAD);
			map[next_load_y*W_SIZE+next_load_x].set_move_xy(-a,-b);
			set_player(next_x,next_y);
			break;
		case WALL:
		case LOAD:
		case COMP:
			GameLib::cout << "Can't move" << endl;
			return 0;
			break;
		case GOAL:
			map[next_load_y*W_SIZE+next_load_x].set_id(COMP);
			map[next_load_y*W_SIZE+next_load_x].set_move_xy(-a,-b);
			set_player(next_x,next_y);
			if (!ifclear())
				GameLib::cout << "Good job" << endl;
			break;
		case PLAY:
			GameLib::cout << "Incredible!" << endl;
			break;
		default:
			break;
	}
	return 1;
}

int SOUKOBAN_CLASS::ifclear(){
	int i,j;
	for (i = 0;i < H_SIZE; i++){
		for (j = 0;j < W_SIZE;j++){
			if (map[i*W_SIZE+j].get_id() == LOAD)
				return 0;	
		}
	}
	GameLib::cout << "Congraturations!" << endl;
	return 1;
}

unsigned *SOUKOBAN_CLASS::getObject(enum ImageID id){
	const int IMAGE_WIDTH = image->width();
	int k = 0;
	unsigned *obj_memory = image->data();
	unsigned *maptip = new unsigned[BLOCK_SIZE * BLOCK_SIZE];
	int prelude = 0;
	//GameLib::cout << image.width() << endl;
	switch(id){
		case IMAGE_ID_PLAY: prelude = 0 * BLOCK_SIZE; break; 
		case IMAGE_ID_WALL: prelude = 1 * BLOCK_SIZE; break;
		case IMAGE_ID_GOAL: prelude = 2 * BLOCK_SIZE; break;
		//case IMAGE_ID_COMP: prelude = 3 * BLOCK_SIZE; break;
		case IMAGE_ID_LOAD: prelude = 3 * BLOCK_SIZE; break;
		case IMAGE_ID_VOID: prelude = 4 * BLOCK_SIZE; break;
		default: break;
	}
	for (int i = 0; i < BLOCK_SIZE; i++){
		for (int j = 0; j < BLOCK_SIZE;j++){
			maptip[k++] = obj_memory[i * IMAGE_WIDTH + j + prelude];
		}
	}
	return(maptip);
}

void SOUKOBAN_CLASS::draw(int a){
	unsigned *vram =  Framework::instance().videoMemory();
	int windowWidth = Framework::instance().width();
	//Draw WALL and VOID
	for(int i = 0; i < H_SIZE;i++){
		for(int j = 0; j < W_SIZE; j++){
			switch(map[i*W_SIZE+j].get_id()){
				case WALL:
					for (int k = 0;k < BLOCK_SIZE;k++){
						for (int l = 0; l < BLOCK_SIZE; l++){
							background[(i*BLOCK_SIZE+k)*windowWidth + (j * BLOCK_SIZE+l)] = object[WALL][k*BLOCK_SIZE+l];
						}
					}
					break;
				case PLAY:
				case VOID:
				case LOAD:
				case GOAL:
				case D_GOAL:
				case COMP:
					for (int k = 0;k < BLOCK_SIZE;k++){
						for (int l = 0; l < BLOCK_SIZE; l++){
							background[(i*BLOCK_SIZE+k)*windowWidth + (j * BLOCK_SIZE+l)] = object[VOID][k*BLOCK_SIZE+l];
						}
					}
					break;
				default:break;
			}
        }
    }
	int vec_x=0,vec_y=0;
	//Draw Load and Player (Mover)
	for(int i = 0; i < H_SIZE;i++){
		for(int j = 0; j < W_SIZE; j++){
			switch(map[i*W_SIZE+j].get_id()){
				case COMP:	
				case LOAD:
					vec_x = map[i*W_SIZE+j].get_move_x();
					vec_y = map[i*W_SIZE+j].get_move_y();
					for (int k = 0;k < BLOCK_SIZE;k++){
						for (int l = 0; l < BLOCK_SIZE; l++){
							blend(background[(i*BLOCK_SIZE+k+vec_y*(BLOCK_SIZE-a))*windowWidth + 
								(j * BLOCK_SIZE+l)+vec_x*(BLOCK_SIZE-a)],object[LOAD][k*BLOCK_SIZE+l]);
						}
					}
					break;
				case D_GOAL:
				case PLAY:
					vec_x = map[i*W_SIZE+j].get_move_x();
					vec_y = map[i*W_SIZE+j].get_move_y();
					for (int k = 0;k < BLOCK_SIZE;k++){
						for (int l = 0; l < BLOCK_SIZE; l++){
							blend(background[(i*BLOCK_SIZE+k+vec_y*(BLOCK_SIZE-a))*windowWidth +
								(j * BLOCK_SIZE+l)+vec_x*(BLOCK_SIZE-a)],object[PLAY][k*BLOCK_SIZE+l]);
						}
					}
					break;
				case WALL:
				case VOID:
				case GOAL:
				default:break;
			}
        }
    }
	//Draw GOAL
	for(int i = 0; i < H_SIZE;i++){
		for(int j = 0; j < W_SIZE; j++){
			switch(map[i*W_SIZE+j].get_id()){
				case GOAL:
				case D_GOAL:
				case COMP:
					for (int k = 0;k < BLOCK_SIZE;k++){
						for (int l = 0; l < BLOCK_SIZE; l++){
							blend(background[(i*BLOCK_SIZE+k)*windowWidth + (j * BLOCK_SIZE+l)],object[GOAL][k*BLOCK_SIZE+l]);
						}
					}
					break;
				case WALL:
				case VOID:
				case LOAD:
				default:break;
			}
        }
    }
	draw_v_screen(background,0);
	return;
}

void SOUKOBAN_CLASS::set_player(int a,int b){
    if (a < 0 || a >= W_SIZE || b < 0|| b >= H_SIZE ){
        GameLib::cout << "Can't move!" << endl;
        return;
    }else if (map[y*W_SIZE+x].get_id() == PLAY)
		map[y*W_SIZE+x].set_id(VOID);
	else if (map[y*W_SIZE+x].get_id() == D_GOAL)
		map[y*W_SIZE+x].set_id(GOAL);
	map[b*W_SIZE+a].set_move_xy(x-a,y-b);
	if (map[b*W_SIZE+a].get_id() == GOAL){
		map[b*W_SIZE+a].set_id(D_GOAL);
	}else{
		map[b*W_SIZE+a].set_id(PLAY);
		
	}
    x = a;
    y = b;
    return;
}

void SOUKOBAN_CLASS::finish(){
	//image.~Image();
    return;
}