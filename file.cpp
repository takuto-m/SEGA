#include"file.hpp"
#include"GameLib\Framework.h"
#include <fstream>
using namespace file_image;
using namespace GameLib;

IMAGE_CLASS::IMAGE_CLASS(const char *filename){
	const int FORMAT_SIZE = 4;
	std::ifstream fin(filename,std::ios::in|std::ios::binary);
	if (!fin){
		cout << "ERROR : Can not open " <<  filename << endl;
	}
	/*
	char *extention;
	extention = new char[FORMAT_SIZE];
	fin.seekg(0);
	fin.read((char *)extention,FORMAT_SIZE);
	cout << extention << endl;
	delete[] extention;
	*/
	fin.seekg(FORMAT_SIZE*4);
	fin.read((char*)&mWidth,FORMAT_SIZE);
	fin.seekg(FORMAT_SIZE*3);
	fin.read((char *)&mHeight,FORMAT_SIZE);
	fin.seekg(128);
	mData = new unsigned[mWidth * mHeight];
	fin.read((char *)mData,mWidth * mHeight*8);
	fin.close();//
	cout << filename << endl;
	cout << "width :\t" << mWidth << endl;
	cout << "Height :\t" << mHeight << endl;
	cout << "*************************************"<< endl;
}

IMAGE_CLASS::~IMAGE_CLASS(){
	delete[] mData;
}

 
int IMAGE_CLASS::width() const{
	return(mWidth);
}

int IMAGE_CLASS::height() const {
	return(mHeight);
}

unsigned *IMAGE_CLASS::data()const{
	return(mData);
}

