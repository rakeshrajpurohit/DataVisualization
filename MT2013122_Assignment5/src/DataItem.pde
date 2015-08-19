class DataItem extends SimpleMapItem {
  int id;
  String name;
  String parent;
  int number;
  float rate;
 
  color c;
  
  float textPadding = 10;
  float boxLeft, boxTop;
  float boxRight, boxBottom;
  
  DataItem item;
  DataItem(int id, String name, int number, float rate, String parent){
    this.id     = id;
    this.name   = name;
    this.number = number;
    this.rate   = rate;
    this.parent = parent;
    this.size = this.number;
    this.setDepth(1);
  }
  
  void calcBox(){
    boxLeft = x;
    boxTop  = y;
    boxRight = x+w;
    boxBottom = y+h;
  }
  
  void draw(){
    updateColors();
    calcBox();
    fill(c);
    rect(boxLeft, boxTop, boxRight, boxBottom);
    
    if( textFits()) {
      drawTitle();
    }
    
    if(mouseInside())
    {
      rollOverData = this;
    }
  }
  
  void highlight(){
    fill(255, 40);
    stroke(0);
    strokeWeight(2f);
    rect(x, y, w, h);
  }
  
  void drawInfo(){
    String s = "\""+this.name+" "+this.number+"\"";
    textSize(20);
    textAlign(LEFT, CENTER);
    fill(255);
    text(s, mouseX, mouseY);
    textSize(10);
    rollOverData.highlight();
  }
  
  void drawTitle(){
    fill(0);
    textAlign(LEFT, CENTER);
    text(name, boxLeft+4 , boxTop+h/2);
    textAlign(LEFT, CENTER);
    text(number, boxLeft+4 , boxTop+h/2 + textPadding);

  }
  
  boolean textFits(){
    float wide = textWidth(name) + textPadding*2;
    float high = textAscent() + textDescent() + textPadding*2;
    return (boxRight - boxLeft > wide) && (boxBottom - boxTop > high);
  }
  
 void updateColors(){
    c = getPartColor();
  }
  
  boolean mouseInside() {
    return(x < mouseX && mouseX < x+w && y < mouseY && mouseY < y+h);
  }
  
  color getPartColor(){
    color c = color(30, 114, 45);
    if(this.rate < 0)
        c = color(100, 50 , 50);
  else if(this.rate > 5)
      c = color(50, 52, 100);  
     
    return c;
  }
}
