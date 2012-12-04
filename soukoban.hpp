#ifndef _Soukoban_hpp
#define _Soukoban_hpp
#include "status.h"
#include<vector>
#include "file.hpp"

using namespace cell_status;
using namespace file_image;
namespace soukoban{
	typedef class SOUKOBAN_CLASS{
		private:
			enum ImageID{
				IMAGE_ID_VOID,	
				IMAGE_ID_WALL,
				IMAGE_ID_GOAL,
				IMAGE_ID_LOAD,
				IMAGE_ID_COMP,
				IMAGE_ID_PLAY,
				IMAGE_ID_D_GOAL
			};
			IMAGE image;
			std::vector<STATUS_CLASS> map;
			std::vector<unsigned> background;
			unsigned *object[7];
			char input;
			bool g_previous_input_a;
			bool g_previous_input_w;
			bool g_previous_input_s;
			bool g_previous_input_z;
			int x,y,itnum;
			char* read_map(char *filename);
			int animation_flag;
			int judge(int a,int b);
			void draw(int a);
			void set_player(int a,int b);
			int ifclear();
			bool clearFlag;
			void finish();
			unsigned *getObject(enum ImageID id);
		public:
			void animation();
			int getInput();
			void updateGame();
			bool getClearFlag();
			SOUKOBAN_CLASS();
			SOUKOBAN_CLASS(char* filename);
			~SOUKOBAN_CLASS();
	}*SOUKOBAN;
}
#endif
