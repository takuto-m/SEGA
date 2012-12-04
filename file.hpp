#ifndef _FILE_H_
#define _FILE_H_ 

namespace file_image{
typedef class IMAGE_CLASS{
public:
		IMAGE_CLASS(const char *filename);
		~IMAGE_CLASS();
		int width() const;
		int height() const;
		unsigned *data() const;
private:
	int mWidth;
	int mHeight;
	unsigned *mData;
}*IMAGE;
} 
#endif