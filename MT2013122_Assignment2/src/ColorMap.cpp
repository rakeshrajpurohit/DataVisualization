#include "ColorMap.h"

cMap colorMap[10] ={{0.0,{0.0, 0.0, 1.0}},
					{0.1,{0.0, 0.0, 1.0}},
					{0.2,{0.0, 0.0, 1.0}},
					{0.3,{0.0, 0.2, 0.8}},
					{0.4,{0.0, 1.0, 0.2}},
					{0.5,{0.0, 1.0, 0.0}},
					{0.6,{0.2, 0.8, 0.0}},
					{0.7,{0.8, 0.2, 0.0}},
					{0.8,{1.0, 0.0, 0.0}},
					{0.9,{1.0, 0.0, 0.0}},	
				   };


Color interpol(Color C1, Color C2, float fraction)
{
	Color C;
	C.red =  (C2.red-C1.red) * fraction + C1.red;
	C.green =  (C2.green-C1.green) * fraction + C1.green;
	C.blue =  (C2.blue-C1.blue) * fraction + C1.blue;
	return C;
}

Color getColor(float S)
{
	if(S < 0.0)
		return colorMap[0].col;
	else if(S >= 1.0)
		return colorMap[9].col;
	else
	{
		int i = 8;
		Color C;
		while(colorMap[i].val > S && i > 0)
			i--;
		float S1 = colorMap[i].val;
		float S2 = colorMap[i+1].val;
		if(S1 == S)
			C = colorMap[i].col;
		else
		{
			int t = (S - S1)/(S2 - S1);
			C = interpol(colorMap[i].col, colorMap[i+1].col, t);
		}
		return C;
	}
}
