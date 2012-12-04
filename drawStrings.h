#ifndef __DRAW_STRINGS__
#define __DRAW_STRINGS__
#include "file.hpp"
using namespace file_image;

namespace draw_strings{
	typedef class DRAW_STRINGS_CLASS{
	public:
		static DRAW_STRINGS_CLASS *instance();
		static void create(const char *font_file_name);
		static void destroy();
		void draw_string(int x, int y, const char *string, unsigned color = 0xffffff) const;
	private:
		DRAW_STRINGS_CLASS(const char *font_file_name);
		~DRAW_STRINGS_CLASS();
		IMAGE string_image;
		void draw(int dstX, int dstY, int srcX, int srcY,int char_width,int char_height, unsigned color);
		static DRAW_STRINGS_CLASS *m_instance;
	} *DRAW_STRINGS;
}

#endif