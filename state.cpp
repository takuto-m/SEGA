#include "state.h"
#include "GameLib\Framework.h"

using namespace state;
using namespace GameLib;
STATE_CLASS::STATE_CLASS(){
	state = TITLE_STATE;
	previous_state = INITIALIZE_STATE;
	DRAW_STRINGS_CLASS::create("font.dds");
	title_data = NULL;
	game = NULL;
}

STATE_CLASS::~STATE_CLASS(){
	DRAW_STRINGS_CLASS::destroy();	
}

void STATE_CLASS::update(){
	using namespace soukoban;
	using namespace title_class;
	using namespace draw_strings;

	switch(state){
	case TITLE_STATE:
		if (previous_state != state) title_data = new TITLE_CLASS();
		title_data->draw();
		if ( Framework::instance().isKeyOn(' ')){
			get_state(title_data->get_transition());
			delete title_data;
			previous_state = INITIALIZE_STATE;
			return;
		}
		break;
	case STAGE_STATE:
		if (previous_state != state) game = new SOUKOBAN_CLASS("Stage_1.txt");
		//Game-Update
		if (game->getInput()){
			game->updateGame();
			game->animation();
		}else return;
		//Transition to title
		if (game->getClearFlag()){
			delete game;
			state = TITLE_STATE;
			return;
		}
		break;
	case INITIALIZE_STATE:
		break;
	default:
		break;
	}
	previous_state = state;
	return;
}

void STATE_CLASS::get_state(int a){
	switch (a){
		case 1: state = TITLE_STATE; break;
		case 2: state = STAGE_STATE; break;
		case 3: state = CLEAR_STATE; break;
		case 4: state = INITIALIZE_STATE; break;
		default: break;
	}
	return; 
}