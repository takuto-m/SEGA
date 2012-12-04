#ifndef _title_h_
#define _title_h_
#include "file.hpp"
#include "function.h"
using namespace file_image;
namespace title_class{
	typedef class TITLE_CLASS{
		private:
			IMAGE title_image;
			int cursor;
			bool getInput();
			char input;
			bool g_previous_input_w,g_previous_input_z;
		public:
			int get_transition();
			TITLE_CLASS();
			~TITLE_CLASS();
			void draw();
	}*TITLE;
}
#endif