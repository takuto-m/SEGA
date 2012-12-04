#ifndef __STATUS_H__
#define __STATUS_H__
namespace cell_status{
	class STATUS_CLASS{
	public:
		int get_id();
		int get_move_x();
		int get_move_y();
		void set_id(int a);
		void set_move_xy(int x, int y);
		STATUS_CLASS(int a);
		~STATUS_CLASS();
	private:
		int move_x;
		int move_y;
		int id;
	};
}
#endif