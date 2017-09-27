import Lists._

class TestSuite extends org.scalatest.FunSuite {

	test(" oddNumbers properly defined ") {
		assert( oddNumbers == List (1 , 3 , 5))
	}

	test(" sumDouble function") {
		assert( sumDouble( List(10, 5)) == 30)
	}

	test(" removeZeroes function") {
		assert( removeZeroes (List (1,0,2,0,3,0)) == List (1 , 2 , 3))
	}

	test(" countEvens function") {
		assert( countEvens (List (0,1,2,3,4,5,6)) == 4)
	}

	test(" removeAlternating function") {
		assert ( removeAlternating ( List ( "A" , "B" )) == List ( "A" ))
		assert ( removeAlternating ( List ( "A" , "B" )) != List ( "B" ))
	}

	test(" isAscending function") {
		assert( isAscending(List(1,2,3,4)) == true)
		assert( isAscending(List(1,2,3,4,0)) == false)
	}

	test(" addSub function") {
		assert( addSub(List(10, 20, 30, 40)) == -20)
	}


	test(" alternate list function") {
		assert ( alternate ( List (1 , 3, 5) , List ()) == List (1, 3, 5))
	}

	test(" fromTo function") {
		assert ( fromTo (9 , 13) == List (9 , 10 , 11 , 12))
	}

	test(" insertOrdered function") {
		assert ( insertOrdered(-2, List(1, 3, 7, 9)) == List(-2 ,1, 3, 7, 9))
		assert ( insertOrdered(5, List(1, 2, 3, 1)) == List())
	}

	test(" sort function") {
		assert ( sort(List(1, 3, 2, 0)) == List(0, 1, 2, 3))
	}
}