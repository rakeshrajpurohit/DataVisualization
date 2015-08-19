class Axis extends Widget 
{  
  Axis(float X, float Y, float W, float H){
    super(X, Y, W, H);
  }
  
  void drawAxis()
  {
    float Y1 = w_y;
    float Y2 = w_y + w_h;
    
    stroke(0);
    fill(255);
    rectMode(CORNERS);
    rect(w_x, Y1, w_x+w_w, Y2 );
  }
}
