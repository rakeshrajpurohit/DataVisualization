class Widget
{
  public float w_x, w_y, w_w, w_h;
  
  public Widget(float x, float y, float w, float h){
    w_x = x;
    w_y = y;
    w_w = w;
    w_h = h;
  }
  
  public boolean isInside(float X, float Y){
    return ((X >= w_x) && (Y >= w_y) && (X <= w_x + w_w) && (Y <= w_y +w_h));
  }
}
