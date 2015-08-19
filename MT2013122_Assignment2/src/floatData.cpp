#include <iostream>
#include <stdio.h>
#include "floatData.h"
using namespace std;

floatData::floatData(void)
{
	XDIM = 500;
	YDIM = 500;
	ZDIM = 100;
	XMIN = -79.47297;
	XMAX = 85.17703;
	YMAX = 82.95293;
	YMIN = -76.03391;
}
floatData::~floatData(void)
{
	
}

float floatData::getDataX(int x, int y,int z)
{
	int index = x+XDIM*(y+YDIM*z);
	return dataX[index];
}

float floatData::getDataY(int x, int y,int z)
{
	int index = x+XDIM*(y+YDIM*z);
	return dataY[index];
}

Vector floatData:: findLine(float X, float Y)
{
	Vector v;
	v.x = X/(XMAX-XMIN);
	v.y = Y/(YMAX-YMIN);
	return v;
}

void floatData::loadFiles()
{
	FILE *file1 = NULL;
	FILE *file2 = NULL;

	if(((file1 = fopen("../bin/Uf02.bin","rb")) == NULL) || ((file2 = fopen("../bin/Vf02.bin","rb")) == NULL))
		cout<<"Couldn't open specified file"<<endl;

	fread((float *)dataX, XDIM*YDIM*ZDIM*sizeof(float), 1, file1);
	fread((float *)dataY, XDIM*YDIM*ZDIM*sizeof(float), 1, file2);
		
	fclose(file1);	
	fclose(file2);		
}

float floatData::ReverseFloat( const float inFloat )
{
	float retVal;
	char *floatToConvert = ( char* ) & inFloat;
	char *returnFloat = ( char* ) & retVal;

	// swap the bytes into a temporary buffer
	returnFloat[0] = floatToConvert[3];
	returnFloat[1] = floatToConvert[2];
	returnFloat[2] = floatToConvert[1];
	returnFloat[3] = floatToConvert[0];

	return retVal;
}

void floatData::convertEndian(){
	for(int i=0;i<XDIM*YDIM*ZDIM; i++){
		dataX[i] = ReverseFloat(dataX[i]);
		dataY[i] = ReverseFloat(dataY[i]);
	}
}
