object HOF{

	def map2 [A ,B , C ]( f: (A , B ) => C , alist1 : List [A ], alist2 : List [B ]): List [C] = {
		(alist1, alist2) match {
		case (Nil,Nil) => Nil
		case (h :: t, head::tail) => f(h,head) :: map2(f,t,tail)
		case (_,_ ) => Nil	
		}	
	}
	
		
	def zip [A ,B ]( lst1 : List [A] , lst2 : List [B ]): List [(A , B )] = {
		(lst1, lst2) match {
		case (Nil,Nil)=> Nil
		case (h :: t, head::tail) => (h, head) :: zip(t,tail)
		case (_,_) => Nil
		}
	}

	
	def flat[A](aList: List[A],bList: List[A]) : List[A] =
	{
	/*	
		aList match{
			case h::t => h::flat(t,bList)
			case Nil => 
						bList match{
							case head::tail => head::flat(Nil,tail)
							case Nil => Nil
						}
		}
		*/
		
			//TRY CASE _
//slower

		(aList,bList) match{
			case (h::t,head::tail) => h::flat(t,bList)
			case (h::t, Nil) => h :: flat(t,Nil)
			case (Nil, head::tail) => head :: flat(Nil,tail)
			case (Nil,Nil) => Nil
		}
		

	}

	def flatten [A ]( lst : List[ List[A ]]): List [A] = {
		lst match{
			case Nil => Nil 
			case h::t=> flat(h,flatten(t))
			
		}
	}


	def flatten3 [ A ]( alist : List [ List [ List [A ]]]): List [A ] = {
		alist match {
			case h::t=>flatten(h):::flatten3(t)
			case Nil => Nil
			
		}
	}

	

	def buildList [A ]( length : Int , f: Int => A ): List [A] = {

		length match {
			case 0 => Nil
			case _ if (length>=0) => buildList(length-1,f):::List(f(length-1))
		}
	}

	def mapList [A , B ]( lst : List [A ], f: A => List [B ]): List [B] = {

		lst match {
			case h::t => f(h):::mapList(t,f)
			case Nil => Nil
		}
	}


	def isTrue[A] ( f : A => Boolean , aList: List[A]): List[A] =
	{
		aList match {
			case h::t if f(h)==true => h::isTrue(f,t)
			case h::t if f(h)==false => isTrue(f,t)
			case Nil => Nil
		}
	}

	def isFalse[A] ( f : A => Boolean , aList: List[A]): List[A] =
	{
		aList match {
			case h::t if f(h)==false=> h::isFalse(f,t)
			case h::t if f(h)==true => isFalse(f,t)
			case Nil => Nil
		}
	}

	def partition [A ]( f : A => Boolean , alist : List [A ]): ( List [A], List [A ]) =
	{
		(isTrue(f,alist),isFalse(f,alist))
	}


	def merge [A ]( lessThan : (A , A) => Boolean , alist1 : List [ A], alist2 : List [A ]): List [A ] ={

		 sort(lessThan,alist1:::alist2)
			
	}

	def sort [ A ]( lessThan : (A , A) => Boolean , alist : List [A ]): List [ A] = {

		alist match {
			case h::t => sortHelper(lessThan,sort(lessThan,t),h)
			case Nil => Nil
		}
	}

	def sortHelper [ A ]( lessThan : (A , A) => Boolean , alist : List [A ], h: A): List [ A] = {

		alist match {
			case Nil => List(h)
			case head :: tail => {
				if (lessThan (h ,head)==true) {
					h ::head::tail
				}
				else {
					 head::sortHelper (lessThan,tail,h) 
				}	
			}
		}
	}

}