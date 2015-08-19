#ifndef COLORMAP_H_
#define COLORMAP_H_

struct Color
{
	float red;
	float green;
	float blue;
};

struct cMap
{
	float val;
	Color col;
};

Color interpol(Color C1, Color C2, float fraction);

Color getColor(float S);

#endif
