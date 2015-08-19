#ifndef FLOATDATA_H_
#define FLOATDATA_H_

struct Vector{
	float x;
	float y;
};

class floatData{
	private:
		int XDIM;
		int YDIM;
		int ZDIM;
		float dataX[500*500*100];
		float dataY[500*500*100];
		float XMIN, XMAX, YMAX, YMIN;

	public:
		floatData(void);
		~floatData(void);
		float getDataX(int x, int y,int z);
		float getDataY(int x, int y,int z);
		Vector findLine(float X, float Y);
		void loadFiles();
		float ReverseFloat( const float inFloat );
		void convertEndian();	
};
#endif
