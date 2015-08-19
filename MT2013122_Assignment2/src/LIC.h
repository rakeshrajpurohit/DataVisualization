#include "floatData.h"
#ifndef LIC_H_
#define LIC_H_

class LIC{	
	public:
		int  discrete_filter_size;	
		float  line_square_clip_max;
		float vector_component_min;  
		floatData FD; 
	
		LIC();
		void  	vectorField(int  xSize,  int     ySize,  float*   vectr);
		void	NormalizVectrs(int  xSize,  int     ySize,  float*   vectr);
		void    GenBoxFiltrLUT(int  LUTsiz,  float*  lut0,  float*  lut1);
		void    MakeNoise(int  xSize,  int     ySize,  unsigned char*  pNoise);
		void	FlowImagingLIC(int  xSize,  int     ySize,  float*   vectr,   unsigned char*  noise,  unsigned char*  outDraw,  float*  lut0,  float*  lut1,  float  kernel);
		void 	displayLIC(int  xSize,  int  ySize,  unsigned char*  outDraw);
};
#endif
