object Lists {

	val oddNumbers = 1 :: 3 :: 5 :: Nil

	def sumDouble(aList: List[Int]) : Int = {
		
		aList match {
			
			case h :: t => h + h + sumDouble(t)
			case Nil => 0
		}
	      		
	}

	def removeZeroes(aList: List[Int]) : List[Int] = {
		
		aList match {
			case 0 :: t => removeZeroes(t)
			case h :: t => h :: removeZeroes(t)
			case Nil => Nil
		}	
	}

	def countEvens(aList: List[Int]) : Int = {
		
		aList match {

			case h :: t => {
				if (h%2 == 0)
					1 + countEvens(t)
				else
				countEvens(t)
			}
			case Nil => 0
		}
	      		
	}

	def removeAlternating(aList: List[String]) : List[String] = {

		aList match {

			case h :: t => h :: removeAlternating(remove(t))
			case Nil => Nil
		}
	}


	def remove(aList: List[String]) : List[String] = {

		aList match {

			case h :: t => t
			case Nil => Nil
		}
	}

	def isAscending(aList : List[Int]) : Boolean = {

 		aList match {

 			case h :: t => isGreater(t,h)
 			case Nil => true
 		}
	}

	def isGreater(aList : List[Int],n : Int) : Boolean = {

 		aList match {

 			case h :: t if n > h => false
 			case h :: t => isGreater(t,h) 
 			case Nil => true 
 		}
	}

	def addSub(aList: List[Int]) : Int = {
		aList match {
			case h :: t => h + add(t)
			case Nil => 0
		}
	}

	def add(aList: List[Int]) : Int = {
		aList match {
			case h :: t => addSub(t) - h
			case Nil => 0
		}
	}

	def alternate(aList: List[Int], bList: List[Int]) : List[Int] = {
		
		(aList,bList) match{

			case (h :: t, head :: tail) => h :: head :: alternate(t,tail)
			case (h::t, Nil) => h :: alternate(t,Nil)
			case (Nil, head::tail) => head :: alternate(Nil,tail)
			case (Nil,Nil) => Nil
		}
	}


	def fromTo(x: Int,y:  Int) : List[Int] = {
			
		(x,y) match{
			case (x,y) if x<y =>x::fromTo(x+1,y)
			case (x,y) if x>y => Nil
			case (x,y) if x==y => Nil
		}
					
	}

	def insertOrdered (n: Int , lst :List[Int]): List[Int] = {

		if(isAscending(lst)==true)
		{
			lst match {
			case h::t if n<h => n :: lst
			case h::t =>  compare(h,n,t)
			case Nil => n::Nil
			}
		} else
			Nil
		
	}

	def compare (h: Int, n: Int, aList: List[Int]) = {
		aList match {
			case head :: tail if ((h<=n)&&(head>=n)) => h :: n :: head :: tail
			case head :: tail => h :: head :: insertOrdered(n,tail)
			case Nil => Nil
		}
	}

	def sort (lst: List[Int]): List[Int] = {
		lst match {
			case h :: t => insert(h,sort(t))
			case Nil => Nil
		}
	}

	def insert (h: Int , aList: List[Int]): List[Int] = {
		aList match {
			case head :: tail if head>=h => h :: aList
			case head :: tail => head :: insert(h,tail)
			case Nil => List(h)
		}
	}

}
