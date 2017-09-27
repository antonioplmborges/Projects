import hw.sudoku._

object Solution extends SudokuLike {  
  type T = Board

//get coordinates same row r, collumn c and box as(r,c)
  def peersHelper(row: Int, col: Int): List[(Int, Int)] = { 
    
    val rowPeers = 0.to(8).map( c => (row, c))
    val colPeers = 0.to(8).map( r => (r, col))
    val rowBox: Int = (row/3) * 3
    val colBox: Int = (col/3) * 3
    val boxPeers = rowBox.to(rowBox + 2).flatMap{ r => colBox.to( colBox + 2 ).map{ c => (r,c)}}
      
      ( rowPeers ++ colPeers ++ boxPeers ).filterNot{
        case (r, c) => r == row && col == c
        }.toList.distinct
  }
  //matrix of peer coordinates
    val peersMatrix = Map((0.to(8).flatMap { r => 0.to(8).map{ c => ((r,c) -> peersHelper(r,c))}}):_*)


  def peers(row: Int, col: Int): List[(Int, Int)] = peersMatrix((row, col))
  

  def parseHelper(lst: List[Char], currentBoard: Board, index: Int): Board = lst match {
    case Nil => currentBoard
    case '.' :: tail => parseHelper(tail, currentBoard, index+1)
    case integer :: tail => { 

      val newBoard = currentBoard.place(index/9, index%9, integer.toInt-48)
      
      parseHelper(tail, newBoard, index+1)
    }
  }

  def parse(str: String): Board = {

    val pattern = "[\\.1-9]{81}".r
    val parsedString = pattern.findAllIn(str).mkString("").toList
    val emptyPuzzleMap = (0.to(8).flatMap{x => 0.to(8).map{ y => (x,y) -> List(1,2,3,4,5,6,7,8,9)}}).toMap
    val emptyBoard = new Board(emptyPuzzleMap)
    val available = parseHelper(parsedString, emptyBoard, 0)
    
    available///all possible integer in cell

  }

}

 

class Board(val available: Map[(Int, Int), List[Int]]) extends BoardLike[Board] {



  def availableValuesAt(row: Int, col: Int): List[Int] = {
    // Assumes that a missing value means all values are available. Feel
    // free to change this.
    available.getOrElse((row, col), 1.to(9).toList)
  }

 def valueAt(row: Int, col: Int): Option[Int] = {
    if(available.get((row, col)).get.length != 1){ None} else Some (available.get((row, col)).get(0))
  }
  //every cell has 1 value
  def isSolved(): Boolean = available.valuesIterator.forall(_.size == 1)
    
  
  //there's a cell with no value
  def isUnsolvable(): Boolean = available.valuesIterator.exists(_.size == 0)
    
  

  def placeHelper(lst: List[(Int,Int)], currentBoard: Map[(Int, Int), List[Int]]): Map[(Int, Int), List[Int]] = lst match {
    case Nil => currentBoard
    case (row, col) :: tail => {
      if(currentBoard.apply((row, col)).size == 1) {
        val newBoard = currentBoard + ((row, col) -> currentBoard.apply((row, col))) ++ Solution.peers(row, col).map{
        x => x -> currentBoard.apply(x).filter(_ != currentBoard.apply((row, col))(0))}

        placeHelper(tail, newBoard)
      } else placeHelper(tail, currentBoard)
    }
  }

  def place(row: Int, col: Int, value: Int): Board = {
    require(availableValuesAt(row, col).contains(value))

    val peersFiltered = Solution.peers(row, col)
    val newBoard = available + ((row,col) -> List(value)) ++ peersFiltered.map{
      x => x -> available.apply(x).filter(_ != value)}
    val finalBoard = placeHelper(peersFiltered, newBoard)

    new Board(finalBoard)
    
  }

  
  def nextStates(): List[Board] = {
    if (isUnsolvable()) {
      List()
    }

    val availableStates = available.filter{ case ((row,col), value) => value.size == 1}
    
    availableStates.map{ case ((row,col), value) => place(row,col,value(0))}.toList
}
/*
 def place(row: Int, col: Int, value: Int): Board = {
    require(availableValuesAt(row, col).contains(value))
    val newMap:Map[(Int, Int), List[Int]] = available
    if(newMap.get(row, col).get != List()) {
      /**overview: grab first element in list structure and set into map**/ // available.get(row, col).get(0)
      newMap = newMap + ((row, col) -> List(value)) 
 
      for(littlePeer: (Int, Int)  <- Solution.peers(row, col)) { 
 
 
        else if (newMap.get(littlePeer._1, littlePeer._2).get.length == 1) { 
          for(singletons_peer: (Int, Int)  <-Solution.peers(littlePeer._1, littlePeer._2)) {
          \
            if(theOption != None) {
            newMap = newMap + (singletons_peer -> (theOption.get.toSet -
              (newMap.get(littlePeer._1, littlePeer._2).get.head)).toList.sortWith (_ < _)) }
          }
            }
              } 
 
                  }
    new Board(newMap)
  }
 
 */


  def solve(): Option[Board] = (this.isSolved) match {
    case true => Some(this)
    case false => this.nextStates.head.solve

  }
}






