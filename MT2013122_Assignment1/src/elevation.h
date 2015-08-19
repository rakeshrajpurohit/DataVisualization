#ifndef ELEVATION_H
#define ELEVATION_H

struct Color{
		float red;
		float green;
		float blue;
};

class Elevation {
	private:
		int w; //Width of Image
		int l; //Length of Image
		float** hs; //Height value for elevation
		Color** colorMap;//ColorMap for elevation
		Vec3f** normals;
		bool computedNormals; //bool variable to check whether normals is updated
	public:
		Elevation(int w, int l);
		~Elevation();
		int width(void);
		int length(void);
		
		//Sets the height at the position (x, z) to y
		void setHeight(int x, int z, float y);
		
		//Get the height at postion (x, z)
		float getHeight(int x, int z);
		
		//set the color value at position (x,z)
		void setColor(int x, int z, float value);
		
		//Get the color value at position (x,z)
		Color getColor(int x, int z);
		
		//Computes the normals, if not yet computed
		void computeNormals(void);

		//Returns the normal at (x, z)
		Vec3f getNormal(int x, int z);
};

#endif
