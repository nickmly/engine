#pragma once
#include "Image.h"
class SOILImage : public Image
{
private:
	unsigned char* image;
	int width, height;
public:
	SOILImage(const char * fname, int width, int height);
	~SOILImage();
	virtual int getBitsPerPixel();
	virtual GLenum getFormat();
	virtual int getHeight();
	virtual int getWidth();
	virtual unsigned char * getImage();
	virtual int getPixelStorageParameter();
	virtual GLenum getPixelStorageType();
	virtual GLenum getPixelType();
	virtual void Init(int _width, int _height);
	virtual void Init(std::string fname);
	virtual void setPixel(int x, int y, float r, float g, float b);
};

