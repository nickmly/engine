#include "SOIL.h"
#include "SOILImage.h"


SOILImage::SOILImage(const char * fname, int _width, int _height)
{
	width = _width;
	height = _height;
	image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
}

unsigned char * SOILImage::getImage() 
{
	return image;
}

int SOILImage::getWidth() 
{
	return width;
}

int SOILImage::getHeight()
{
	return height;
}

SOILImage::~SOILImage()
{
	SOIL_free_image_data(image);
}
