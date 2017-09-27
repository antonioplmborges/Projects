import hw.tictactoe._


class Game (turn : Player , dim : Int , board: Map [( Int , Int ) , Player ]) extends GameLike [ Game ] {


	val currentTurn = turn
  	val boardSize = dim
  	val myBoard = board
  	val nextTurn = setNextTurn()
  	val numb = 0

  	def setNextTurn(): Player = {
    	if(currentTurn == X) 	
    		O
   	 	else 
   	 		X
  	}



	def printGame() = println(myBoard.toString)

  	def getWinnerRow(numb: Int) : Option [Player] = {
		if(numb == boardSize) None
		else{
			if(row(numb) == List.fill(dim)(currentTurn)) Option(currentTurn)
			else if(row(numb) == List.fill(dim)(nextTurn)) Option(nextTurn)
			else getWinnerRow(numb+1)
		}
	}

	

	def row(numb: Int): List[Player] = {
		
			myBoard.filter((x:((Int,Int), Player))=>x._1._1==numb).values.toList
	}

	def getWinnerCol(numb: Int) : Option [Player] = {
		if(numb == boardSize) None
		else{
			if(cols(numb) == List.fill(boardSize)(currentTurn)) Option(currentTurn)
			else if(cols(numb) == List.fill(boardSize)(nextTurn)) Option(nextTurn)
			else getWinnerRow(numb+1)
		}
	}

	def cols(numb: Int) : List[ Player ] = {

			myBoard.filter((x:((Int,Int), Player))=>x._1._2==numb).values.toList
	}

	def mainDiagonal() : Option [Player] = {
		
		if( myBoard.filter((x:((Int,Int), Player))=>x._1._1==x._1._2).values.toList == List.fill(boardSize)(currentTurn) )	
			Option(currentTurn)
		else if( myBoard.filter((x:((Int,Int), Player))=>x._1._1==x._1._2).values.toList == List.fill(boardSize)(nextTurn) )	
			Option(nextTurn)
		else	None
	}

	def antiDiagonal() : Option [Player] = {
		
		if( myBoard.filter((x:((Int,Int), Player))=>x._1._1 + x._1._2 == dim-1).values.toList == List.fill(boardSize)(currentTurn) )	
			Option(currentTurn)
		else if( myBoard.filter((x:((Int,Int), Player))=>x._1._1 + x._1._2 == dim-1).values.toList == List.fill(boardSize)(nextTurn) )	
			Option(nextTurn)
		else	None
	}

	 def getWinPlayer(value: Option[Player]): Boolean = {

	 	getWinnerRow(numb) == value|| getWinnerCol(numb) == value || mainDiagonal() == value || antiDiagonal() == value
 	}

 	def fullBoard (numb: Int) : Boolean = {

 			if(numb <= boardSize-1) {
 				if(myBoard.filter((x:((Int,Int), Player))=>x._1._1==numb).values.toList.size != boardSize)
 					false
 				else
 					fullBoard(numb+1)
 			}
 			else{
 				true
 			}	
 			
 	}
	
	def isDraw(): Boolean = {   //board is full & nobody won
		(fullBoard(numb) == true && getWinner() == None)
	}

	def isFinished(): Boolean = {
	
		isDraw == true || getWinPlayer(Some(X)) == true || getWinPlayer(Some(O))

	}

	def getWinner(): Option[Player] = {
		if(getWinPlayer(Some(O))) Some(O)
    	else if (getWinPlayer(Some(X))) Some(X)
    	else None
	}

	



	def nextBoards(): List[Game] = {

		val avaliableSpaces = 0.to(dim - 1).toList.map { x =>
	      
	      0.to(dim - 1).toList.map { y =>
	        if(myBoard.get(x, y) == None) List(x, y)
	        else Nil
	      }
	    }.flatten.filter(_ != Nil)


  		listNextBoards(avaliableSpaces)

	}

	 def listNextBoards(lst: List[List[Int]]): List[Game] = lst match {

    		case Nil => Nil
   		 	case h :: t => new Game(nextTurn, boardSize, 
      		myBoard+((h(0),h(1)) -> currentTurn)):: listNextBoards(t)


  		}

	
}


object Solution extends MinimaxLike {
	
	type T = Game // T is an " abstract type member " of MinimaxLike
	def createGame ( turn : Player , dim : Int , board : Map [( Int , Int ) , Player ]): Game = {

		new Game(turn, dim, board)
	}
	
	def minimax ( board : Game ): Option [ Player ] = {

		val gameBoard = board

		def minimaxHelp ( lst : List[Game] ): Option [ Player ] = {
			
			lst match {
				case h::t if (h.isFinished()) =>  minimax(h)//h.getWinner
															//else minimax(h)
				
				case h::t  if ( minimax(h.nextBoards().head) ==Some (X) || minimax(h.nextBoards().head) == Some(O)) => 
								minimaxHelp(t)
				case h::t  if ( minimax(h.nextBoards().head) == None ) => None//h.getWinner
			}
		}
		

		if(gameBoard.currentTurn == X) {

			//println(board.getWinner)
			//print(board.getWinner == Some(X)) 
	      
	      if(gameBoard.getWinner == Some(X)) 
			Some(X)
	      else if (gameBoard.getWinner() == Some(O)) 
	      	Some(O)
	      else if(gameBoard.isDraw())
	      //print("erro")	
	      	None
	      	
	      	
	      	
	      
	      else {

	      	if(gameBoard.boardSize == 2)
	      		if(gameBoard.myBoard == Map())
	      			Option(gameBoard.currentTurn)
	      		else if(gameBoard.fullBoard(0))
	      			gameBoard.getWinner
	      		else
	      			minimax(gameBoard.nextBoards.head)
	      	else if(gameBoard.nextBoards.size <= 2 ){
	      		//print(board.getWinner)
	      		//println(board.nextBoards.head.myBoard)
	      		minimax(gameBoard.nextBoards.head)
	      			
	      		}
	      	
	      	else
	      	{//println(board.myBoard)
	      	minimaxHelp(gameBoard.nextBoards)}

	      }
	      	
		}						
	      	
	      	//minimax(board.nextBoards().head)
	       

	       else if(gameBoard.currentTurn == O) {

	    	//print(board.getWinner) 

	      if(gameBoard.getWinner() == Some(O)) 
	      	Some(O)
	      else if(gameBoard.getWinner == Some(X)) 
	      	Some(X)
	      else if(gameBoard.isDraw()) 
	      	{//print("erro")	
	      		//println(gameBoard.isFinished)
	      		//println(gameBoard.getWinPlayer(Option(X)))
	      		//(gameBoard.isDraw)
	      	None}
	      else {	

	      
	      	if(gameBoard.boardSize == 2)
	      		if(gameBoard.myBoard == Map())
	      			Option(gameBoard.currentTurn)
	      		else if(gameBoard.fullBoard(0))
	      			gameBoard.getWinner
	      		else
	      			minimax(gameBoard.nextBoards.head)
	      	else if(gameBoard.nextBoards.size <= 2 ){
	      		
	      		minimax(gameBoard.nextBoards.head)
	      		}
	      	
	      	else
	      	{//println(gameBoard.myBoard)
	      	minimaxHelp(gameBoard.nextBoards)
	      	}
	      }
	      	
	    }

	    else{
	    	//println(board.getWinner)
	    	//print("erro")	
	    	None

	    	} 
}

}

