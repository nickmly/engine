#pragma once
#include <string>
#include <GL\glew.h>
class Image
{
protected:
	Image();
	Image(int width, int height);
	Image(std::string & fname);
	virtual int getBitsPerPixel() = 0;
	virtual GLenum getFormat() = 0;
	virtual int getHeight() = 0;
	virtual int getWidth() = 0;
	virtual unsigned char * getImage() = 0;
	virtual int getPixelStorageParameter() = 0;
	virtual GLenum getPixelStorageType() = 0;
	virtual GLenum getPixelType() = 0;
	virtual void Init(int _width, int _height) = 0;
	virtual void Init(std::string fname) = 0;
	virtual void setPixel(int x, int y, float r, float g, float b) = 0;
	~Image();
};

