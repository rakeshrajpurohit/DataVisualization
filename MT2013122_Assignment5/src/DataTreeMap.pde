import treemap.*;

Treemap tmap;
DataTable data;

PFont font;
DataItem rollOverData;

void setup(){
  size(1300, 700);
  
  cursor(CROSS);
  smooth();
  strokeWeight(0.25f);  
  
  font = createFont("Serif", 10);
  textFont(font);
  String fileName = "export_import_tradebalance_2012_13_dec_crore_1.csv";
  data = new DataTable(fileName);  
  DataMap mapData   = new DataMap();
  
  for(int i = 1; i< data.rowCount-1; i++){
     DataItem d1 = new DataItem(i, data.name[i], data.values[i], data.rateChange[i], "import");
     mapData.addData(d1);
   } 
   
   mapData.finishAdd();
   
   tmap = new Treemap(mapData, 0, 0, width, height);
   MapLayout algorithm = new SquarifiedLayout();
   tmap.setLayout(algorithm);
}

void draw() {
  background(162);
  tmap.draw();  
  frameRate(30);
  
  textAlign(LEFT, CENTER);  
  textAlign(RIGHT, CENTER);
  text("Import acccording to area and With color coded RateOF change",width-20, height-20);
  
  if(mouseX < 1 || width -1 < mouseX || mouseY < 1 || height - 10 < mouseY)
  {
    rollOverData = null;
  }
  
  if(rollOverData != null){
    rollOverData.drawInfo();
  }
}

