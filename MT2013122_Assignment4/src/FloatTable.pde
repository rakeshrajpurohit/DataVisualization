class FloatTable{
  int rowCount;
  int columnCount = 5;
  float[][] data;
  
  FloatTable(String filename){
    String[] rows = loadStrings(filename);
    
    data = new float[rows.length][];
    for(int i = 0; i< rows.length; i++){
      String[] pieces = split(rows[i], ',');
      data[rowCount] = parseFloat(pieces);
      rowCount++;
    }
  }

  int getRowCountData() {
    return rowCount;
  }
  
  float getFloatData(int row, int col){
    return data[row][col];
  }
  
  float getColumnMin(int col){
    float m = Float.MAX_VALUE;
    for(int i = 0; i< rowCount; i++){
      if(!Float.isNaN(data[i][col])){
        if(data[i][col] < m) {
          m = data[i][col];
        }
      }
    }
    return m;
  }
  
  float getColumnMax(int col){
    float m = -Float.MAX_VALUE;
    for(int i = 0; i<rowCount; i++){
      if(data[i][col] > m){
        m = data[i][col];
      }
    }
  return m;
  }
}
