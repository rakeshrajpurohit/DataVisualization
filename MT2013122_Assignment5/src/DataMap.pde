class DataMap extends SimpleMapModel {
  MapLayout algorithm = new SquarifiedLayout();//PivotBySplitSize();
  Mappable[] items;
  
  HashMap words;
  
  DataMap()
  {
    words = new HashMap();
  }
  
  void addData(DataItem item){
    words.put(item.id, item);
  }
  
  public void finishAdd() {
    items = new DataItem[words.size()];
    words.values().toArray(items);
  }
  
  Mappable[] getItems() {
    return items;
  }
  
  int getItemCount() {
    return items.length;
  }
}
