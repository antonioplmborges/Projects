import hw.tictactoe._
import Solution._

class TestSuite extends org.scalatest.FunSuite {



val obj = createGame (X , 3, Map ((0 , 0) -> X , (0 , 1) -> X, (0, 2) -> X, 
								  (1 , 0) -> X , (1 , 1) -> X ,(1,2)->O,
								  (2,0) ->O, (2,1)->X
								   ))

val obj2 = createGame(X,3,Map((0,0)->X,(0,1)->O,(0,2)->X,(1,0)->X,(1,1)->X))
val obj3 = createGame(X,4,Map())


val obj5 = createGame (X , 3, Map ((0 , 0) -> X , 				 (0, 2) -> X, 
								  				 				(1,2)->O,
								  (2,0) ->X,  (2 , 1) -> O
								   ))


val finali = createGame(O,3, Map((0,2) -> X, (0,0) -> X, (2,0) -> O, (1,1) -> X, (2,2) -> X, (0,1) -> O, (1,2) -> O, (2,1) -> X, (1,0) -> X))

//println(obj2.nextBoards())
println(minimax(obj3))

//print(obj.printGame)
//print(obj.getWinnerRow(0))
//print(obj.getWinnerCol(0))
//println("")
//println("")
//println(finali.mainDiagonal)
//println(finali.isDraw)
//println("")
//println("")
//print(obj.antiDiagonal())
//println(obj.getWinPlayer(Option(X)))
//println(obj.fullBoard(0))
//println(obj.avaliableSpaces)

//println(obj.nextBoards())

}
