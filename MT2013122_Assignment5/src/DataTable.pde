class DataTable{
  int rowCount;
  String[] name;
  int[]  values;
  int[]  valuesX;
  float[]  rateChange;
  float[] rateChangeX;
  
  DataTable(String fileName){
    String[] rows = loadStrings(fileName);
    
    values     = new int[rows.length];
    name       = new String[rows.length];
    rateChange = new float[rows.length];
    valuesX     = new int[rows.length];
    rateChangeX = new float[rows.length];


    for(int i =1; i<rows.length; i++){
      String[] pieces = split(rows[i], ',');
      name[i] = pieces[0];
      values[i] = parseInt(pieces[1]);
      valuesX[i] = parseInt(pieces[2]);
      rateChange[i] = parseFloat(pieces[4]);      
      rateChangeX[i] = parseFloat(pieces[5]);
      rowCount++;
    }
 }
  
  int getRowCount() {
    return rowCount;
  }
  
  String getName(int row){
    return name[row];
  }
  
  int getValue(int row){
    return values[row];
  }
  
  float getRateChange(int row){
    return rateChange[row];
  }
}
