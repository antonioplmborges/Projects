import hw.sudoku._

object Solution extends SudokuLike {
  type T = Board
 
 // Your first task is to parse strings that represent Sudoku boards. You may 
 // assume that all strings represent solvable boards and that the string has 
 // exactly 81 characters. This part of the assignment should be trivial.
 
 // The latter, I think. Parse is placing values at coordinates. 11/11/14. AG.
 
  def parse(str: String): Board = {
    var theMap: Map[(Int, Int), List[Int]] = Map() 
    var newMap: Map[(Int, Int), List[Int]] = Map()
    if(str.length != 81)  new Board(theMap) 
    val iter = str.toCharArray().iterator //mk to char array
 
    while(iter.hasNext) {
      for( i <- 0 to 8) 
        for(j <- 0 to 8){    
          val nextVal = iter.next 
          
            if(nextVal.isDigit) {
             theMap = theMap + ((i, j) -> List[Int](nextVal.toString.toInt) ) 
                               
            } else if(nextVal == '.') {
              theMap = theMap + ((i, j) -> List[Int](0) ) }
      } /** overview: substitutes '.' for 0 as placeholder for None. **/
    }
     
 
    /** overview: for all Lists in the original map that equal a List of 0 (which is an empty slot), call peers. 
        create new map with all possible playable numbers mapped to each blank space on the board. **/
 
    for(map_object: ((Int, Int), List[Int])  <-theMap){ 
      if(map_object._2 == List(0)) { 
        /** overview: for each peer, GRAB the sudoku number played if there is one, 
        set it into a list of numbers that can no longer be played. **/     
        /** note: (map_object._1._1, map_object._1._2) <====  gets the first and second element of map_object's tuple:(Int, Int) **/
 
        var impossible_values = List[Int]() 
        for(littlePeer: (Int, Int)  <-peers(map_object._1._1, map_object._1._2)) { 
          if(theMap.get(littlePeer).get != List(0)) 
          impossible_values = (impossible_values union theMap.get(littlePeer).get).toSet.toList  
        } /** eliminates duplicate Ints by converting to set**/
 
        var lst1 = List[Int]() 
        for(i<- 1 to 9) if(!impossible_values.contains(i)) { lst1 = lst1 :+ i}
 
        newMap = newMap + ((map_object._1: (Int, Int) ) -> lst1 ) 
      }
    }
 
    /** overview: Reformatting with for expression, merge maps. **/
    for(map_object: ((Int, Int), List[Int])  <-theMap){
      if((map_object._2).length == 1){  // takes care of singleton cases, makes sure that if Some(List(k)), we eliminate k from its peer rows, cols, and cube.
        for(singletons_peer: (Int, Int)  <-peers(map_object._1._1, map_object._1._2)) {
            var theOption = newMap.get(singletons_peer._1, singletons_peer._2)
            if(theOption != None) {// theOption.get 
            newMap = newMap + (singletons_peer -> (theOption.get.toSet-(map_object._2.head)).toList.sortWith (_ < _)) }
        }
      }
 
      if(map_object._2 != List(0)) {
        newMap = newMap + ((map_object._1._1: Int, map_object._1._2: Int) -> map_object._2 )  
 
 
      }
    }
     
     new Board(newMap)
  }
 
  // You can use a Set instead of a List (or, any Iterable)
  def peers(row: Int, col: Int): List[(Int, Int)] = {
    var lst: List[(Int, Int)] = List[(Int, Int)]()
    for(x <- 0 to 8) { if(x != row) /* println("printing (x, col) " + (x, col)) ;*/lst = lst :+ (x, col) }
    for(y <- 0 to 8) { if(y != col) lst = lst :+ (row, y) }
 
    val lowerRowIndex:Int = (row / 3) * 3;
    val lowerColumnIndex:Int =  (col / 3) * 3;
 
    /** overview: Calculate cube coordinates for (row, col). **/
    for (i <- lowerRowIndex to lowerRowIndex + 3 - 1) 
        for (j <- lowerColumnIndex to lowerColumnIndex + 3 - 1 ) 
          if((i, j) != (row, col)) lst = lst :+ (i, j)
             
 
    lst
  }
 
}
 
// Top-left corner is (0,0). Bottom-right corner is (8,8).
// You don't have to have a field called available. Feel free to change it.
class Board(val available: Map[(Int, Int), List[Int]]) extends BoardLike[Board] {
 
  def availableValuesAt(row: Int, col: Int): List[Int] = {
    // Assumes that a missing value means all values are available. Feel
    // free to change this.
    available.getOrElse((row, col), 1.to(9).toList)
  }
 
  def valueAt(row: Int, col: Int): Option[Int] = {
    if(available.get((row, col)).get.length != 1){ None} else Some (available.get((row, col)).get(0))
  }
 
  def isSolved(): Boolean = {
    // for(s<- available){ if(s._2.length != 1) {return false} }
    // true
    var truth:Boolean = false
    val cubes: List[(Int, Int)] = List[(Int, Int)]((0,0), (0,3), (0,6),
                                                   (3,0), (3,3), (3,6),
                                                   (6,0), (6,3), (6,6))
    for(square <- cubes){
      val lowerRowIndex:Int = (square._1 / 3) * 3;
      val lowerColumnIndex:Int =  (square._2 / 3) * 3;
      var lst: Set[Int] = Set()
 
      for (i <- lowerRowIndex to lowerRowIndex + 3 - 1)
          for (j <- lowerColumnIndex to lowerColumnIndex + 3 - 1 ){
          val Some(contents) = available.get(i, j)
          if(contents.length == 1) lst = lst union contents.toSet  
        }
       
 
      // println("printing inside square: " + lst.toList.sortWith(_ < _))
      if(lst == 1.to(9).toSet ) truth = true else false
    }
 
    truth
  }
 
  def isUnsolvable(): Boolean = {
    for(s<- available.values){ if(s == List()){ true} }
    false
    // throw new UnsupportedOperationException("not implemented")
  }
 
 
  def place(row: Int, col: Int, value: Int): Board = {
    require(availableValuesAt(row, col).contains(value))
    var newMap:Map[(Int, Int), List[Int]] = available
    if(newMap.get(row, col).get != List()) {
      /**overview: grab first element in list structure and set into map**/ // available.get(row, col).get(0)
      newMap = newMap + ((row, col) -> List(value)) 
 
      for(littlePeer: (Int, Int)  <- Solution.peers(row, col)) { 
 
        if(newMap.get(littlePeer._1, littlePeer._2).get.length > 1){
          var lst1 = (newMap.get(littlePeer._1, littlePeer._2).get.toSet-(value)).toList.sortWith (_ < _)
          newMap = newMap + (littlePeer -> lst1) 
        } 
 
        else if (newMap.get(littlePeer._1, littlePeer._2).get.length == 1) { 
          for(singletons_peer: (Int, Int)  <-Solution.peers(littlePeer._1, littlePeer._2)) {
            var theOption = newMap.get(singletons_peer._1, singletons_peer._2)
            if(theOption != None) {
            newMap = newMap + (singletons_peer -> (theOption.get.toSet -
              (newMap.get(littlePeer._1, littlePeer._2).get.head)).toList.sortWith (_ < _)) }
          }
            }
              } 
 
                  }
    new Board(newMap)
  }
 
 
  def nextStates(): List[Board] = {
    if (isUnsolvable()) {
      List()
    }
 
    var lst: List[Board] = List[Board]()
    for(s<- available){
      for(v<- s._2)
        if(available.get(s._1).get.length > 1 ){ lst = lst :+ place(s._1._1, s._1._2, v)  }
    }
 
    // for(s<- lst)  printf("NEXT \n%s\n=========================================\n", s) 
    // lst
 
    // overview: optimization.
    var tuple = List[(Int, Board)]()
    for(s: Board<- lst) { 
      var count = 0
      for(map_object: ((Int, Int), List[Int])  <-s.available){
        count += map_object._2.length
      }
            tuple = tuple :+ (count, s) 
    }
 
    tuple = tuple.sortBy(_._1)
    var helloworld = List[Board]()
    for(s<- tuple){ helloworld = helloworld :+ s._2; }
    for(s<- helloworld)  printf("NEXT \n%s\n=========================================\n", s) 
    helloworld
  }
 
  def solve(): Option[Board] = {
    if(this.isSolved)  Some(new Board(available))
     
    else{
      for(aLittleBoard: Board <- nextStates){ // == List[Int]()
         aLittleBoard.solve match{
            case None => //
            case Some(s) =>  Some(s)
          }
   
      }
       None
    }
 
  }
 
  // reference: https://piazza.com/class/hvp6pl9zbhk281?cid=1207
  def toString2(): String = {
    var str: String = ""
    for(i <- 0 to 8){
      if(i == 0 || i == 3 || i == 6) str = str + "-------------\n"
        for(j <- 0 to 8){
          if(j == 0 || j == 3 || j == 6) str = str + "|"
          val ls:List[Int] = available((i, j))
          if(ls.size == 1) str = str + ls(0)
          else str = str + "."
          if(j == 8) str = str + "|"
        }
        str = str + "\n"
        if(i == 8) str = str + "-------------\n"
      }
       str
  } 
}