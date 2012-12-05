#include "GameLib\Framework.h"
#include <cstdlib>
#include <fstream>
#include "state.h"


namespace GameLib{
	using namespace state;
	const int MEAN_FRAME = 10;
	const int SKIP_FRAME = 16;
	unsigned g_previous_time[MEAN_FRAME];
	STATE_CLASS *state = 0;
	void Framework::update(){
		if (!state){
			state = new STATE_CLASS();
		}
		//Frame rate
		unsigned current_time = time();
		unsigned frame_time = current_time - g_previous_time[0];
		for (int i = 0; i < MEAN_FRAME - 1; i++){
			g_previous_time[i] = g_previous_time[i + 1];
		}
		while ((time() - g_previous_time[MEAN_FRAME - 1]) < SKIP_FRAME){
			sleep(1);
		}
		g_previous_time[MEAN_FRAME - 1] = current_time;
		unsigned frame_rate = 1000 * MEAN_FRAME / frame_time;
		//cout << frame_rate << endl;
		if (Framework::instance().isKeyOn('q')){
			delete state;
      Framework::instance().requestEnd();
		}else{
			state->update();
		}
	}
}