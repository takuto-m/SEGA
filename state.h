#ifndef __STATE_H__
#define __STATE_H__
#include "GameLib\Framework.h"
#include "./soukoban.hpp"
#include "./title.h"
#include "drawStrings.h"

using namespace soukoban;
using namespace draw_strings;
enum STATE_INDEX{
	TITLE_STATE,
	STAGE_STATE,
	CLEAR_STATE,
	INITIALIZE_STATE,
	EXIT_STATE
};
namespace state{
	typedef class STATE_CLASS{
	public:
		void update();
		STATE_CLASS();
		~STATE_CLASS();
	private:
		void get_state(int a);
		SOUKOBAN game;
		enum STATE_INDEX state, previous_state;
		title_class::TITLE title_data;
	} *STATE;
}
#endif