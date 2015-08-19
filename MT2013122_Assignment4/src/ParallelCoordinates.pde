Axis a[];
PFont font;

int NC = 5,NR;
int W = 1200;
int H = 600;
String s[] = {"Variance","Skewness","Curtosis","Entropy","class"};
  
// a color palet
float[][] col_pal;

//Data Source  
String dataSource ="data_banknote_authentication.txt";
FloatTable data;

void setup()
{
  size(W, H);
  background(0,0,0);
  
  // build the color pallet
 col_pal = new float[3][3];
 col_pal[0][0] = 255; col_pal[0][1] =   0; col_pal[0][2] =   0;
 col_pal[1][0] =   0; col_pal[1][1] = 255; col_pal[1][2] =   0;
 col_pal[2][0] =   0; col_pal[2][1] =   0; col_pal[2][2] = 255;
 
  //load data
  data = new FloatTable(dataSource);
  NR = 1372;
  a = new Axis[NC];
  font = createFont("AvdiraItalic", 20);
  textFont(font);
  textSize(10); 
}

void draw()
{
  float X1 = 50.0;
  float gap = 200.0;
  for(int i = 0; i<NC; i++){
    drawAxis(X1, i);
    X1 = X1 +gap;
  }
  for(int i = 0; i<NR-1; i++){
    drawLines(i);
  }
}

void drawAxis(float X1, int i){
    a[i] = new Axis(X1, 46.0, 10.0, 360.0);
    a[i].drawAxis();
    textAlign(CENTER);
    text(s[i],X1, 470.0);
    text(data.getColumnMax(i), X1, 40.0);
    text(data.getColumnMin(i), X1, 440.0);
}

void drawLines(int i){
  float dmin = data.getColumnMin(0);
  float dmax = data.getColumnMax(0);
  float caseA = dmin+(dmax - dmin)*0.34;
  float caseB = caseA + (dmax - dmin)*0.26;
  float caseC = caseB + (dmax - dmin)*0.41;
  float dmin1, dmax1, dmin2, dmax2, vi, vn, yi, yn;
  
  strokeWeight(1);
  if((data.getFloatData(i,0))<=caseA)
     stroke(col_pal[0][0],col_pal[0][1],col_pal[0][2], 10);
  else if((data.getFloatData(i,0))<=caseB)
     stroke(col_pal[1][0],col_pal[1][1],col_pal[1][2], 10);
  else
     stroke(col_pal[2][0],col_pal[2][1],col_pal[2][2], 10);
  
  for (int j =0;j<NC-1;j++){   
    dmin1 = data.getColumnMin(j);
    dmax1 = data.getColumnMax(j);
    dmin2 = data.getColumnMin(j+1);
    dmax2 = data.getColumnMax(j+1);

    vi = data.getFloatData(i, j);
    yi = map(vi, dmin1, dmax1, 400.0, 50.0);
    vn = data.getFloatData(i, j+1);
    yn = map(vn, dmin2, dmax2, 400.0, 50.0);
    line(a[j].w_x, yi, a[j+1].w_x, yn); 
  }
}
