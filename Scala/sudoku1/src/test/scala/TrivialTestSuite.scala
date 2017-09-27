import hw.sudoku._
import Solution._

class TrivialTestSuite extends org.scalatest.FunSuite {

   val puzzle = "....8.3...6..7..84.3.5..2.9...1.54.8.........4.27.6...3.1..7.4.72..4..6...4.1...3"

    

    test("The solution object must be defined") {
        val obj : hw.sudoku.SudokuLike = Solution

        assert(obj.peers(1, 3) == List((1,0), (1,1), (1,2), (1,4), (1,5), (1,6), (1,7), (1,8), (0,3), (2,3), (3,3), (4,3),
            (5,3), (6,3), (7,3), (8,3), (0,4), (0,5), (2,4), (2,5)))

        assert(obj.parse(puzzle).valueAt(0,4) == Some(8))
        assert(obj.parse(puzzle).valueAt(0,0) == None)

        assert(obj.parse(puzzle).isSolved == true)

        
    }
}

