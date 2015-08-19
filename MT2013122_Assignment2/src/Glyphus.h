#include "ColorMap.h"
#ifndef GLYPHUS_H_
#define GLYPHUS_H_

class Glyphus{
	private:
		float startX;
		float startY;
		float magnitude;
		float angle;
		float endX;
		float endY;
		Color color;

	public:
		Glyphus(float startX, float startY);
		~Glyphus(void);
		void findDirection(float X, float Y);
		float getAngle();
		void DrawGlyphus();
		void DrawArrow(void);
};
#endif
