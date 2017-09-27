object FunctionalDataStructures{

case class Queue [A ]( front : List [A], back : List [A ])

def enqueue [A ]( elt : A , q : Queue [ A ]): Queue [A ] = {
	Queue(q.front,elt::q.back)
}


def dequeue [A ]( q: Queue [A ]): Option [( A , Queue [ A ])] = {

				q.front match {
				
				case head::tail => Option((head,Queue(tail,q.back)))
				case Nil => dequeue(Queue(q.back.reverse,/*List()*/Nil))
				}

}

sealed trait JoinList [A ] {
val size : Int
}

case class Empty [A ]() extends JoinList [A] {
val size = 0
}

case class Singleton [A ]( elt : A ) extends JoinList [A ] {
val size = 1
}

case class Join [A ]( lst1 : JoinList [A ], lst2 : JoinList [A] , size : Int ) extends JoinList [A ]

/*
def max [A ]( lst : JoinList [A ], compare : (A , A) => Boolean ): Option [A] = {

	lst match{
		case Empty () => None
		case Singleton ( x) => Option(x)//List ( x)
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match {
												case (Empty(),Empty()) => None
												case (Join(_, _, _), Join(_, _, _)) => None
												case (Singleton(x), Empty()) => Option(x)
												case (Empty(),Singleton(x)) => Option(x)
												case (Singleton(x),Singleton(y)) =>	if(compare(x,y))
																						Option(x)
																					else
																						Option(y)

												case (Join(alist3,alist4,_),Empty()) => Option(maxElt(Join(Singleton(maxElt(alist3,compare)),Singleton(maxElt(alist4,compare)),2),compare))
												case (Empty(),Join(alist3,alist4,_)) => Option(maxElt(Join(Singleton(maxElt(alist3,compare)),Singleton(maxElt(alist4,compare)),2),compare))
												case (Join(alist3,alist4,_),Singleton(x)) => 
																		Option(maxElt(Join(Singleton(maxElt(Join(Singleton(maxElt(alist3,compare)),Singleton(maxElt(alist4,compare)),2),compare)),Singleton(x),2),compare))
												case (Singleton(x),Join(alist3,alist4,_)) => 
																		Option(maxElt(Join(Singleton(maxElt(Join(Singleton(maxElt(alist3,compare)),Singleton(maxElt(alist4,compare)),2),compare)),Singleton(x),2),compare))

		}
	}

}

def maxElt [A ]( lst : JoinList [A ], compare : (A , A) => Boolean ): A  = {
		//Singleton(err)

		//val err:A = [A]0
		lst match{
		case _ =>
		case Singleton ( x) => x//List ( x)
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match{
												//case (Empty(),Empty()) => 0
												//case (Join(_, _, _), Join(_, _, _)) => 0
												case (Singleton(x), Empty()) => x
												case (Empty(),Singleton(x)) => x
												case (Singleton(x),Singleton(y)) =>	if(compare(x,y))
																						x
																					else
																						y

												case (Join(alist3,alist4,_),Empty()) => maxElt(Join(alist3,alist4,alist3.size+alist4.size),compare)
												case (Empty(),Join(alist3,alist4,_)) => maxElt(Join(alist3,alist4,alist3.size+alist4.size),compare)
												case (Join(alist3,alist4,_),Singleton(x)) => 
																		//if (compare(maxElt(Join(alist3,Singleton(x),alist3.size+1)),maxElt(Join(alist4,Singleton(x),alist4.size+1))),compare)==true)
																			maxElt(Join(Singleton(maxElt(Join(alist3,alist4,alist3.size+alist4.size),compare)),Singleton(x),2),compare)
																		//else
																			//maxElt(alist4,Singleton(x),compare)
												case (Singleton(x),Join(alist3,alist4,_)) => maxElt(Join(Singleton(maxElt(Join(alist3,alist4,alist3.size+alist4.size),compare)),Singleton(x),2),compare)
																		//if (compare(max(Join(alist3,Singleton(x),alist3.size+1)),max(Join(alist4,Singleton(x),alist4.size+1)))==true)
																		//	maxElt(Join(alist3,Singleton(x),alist3.size+1),compare)
																		//else
																		//	maxElt(Join(alist4,Singleton(x),alist4.size+1),compare)
											}
		}
}		
*/
def max [A ]( lst : JoinList [A ], compare : (A , A) => Boolean ): Option [A]  = {
		
		lst match{
		case Empty() => None
		case Singleton ( x) => Option(x)
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match{
												case (Empty(),Empty()) => None
												case (Join(_, _, _), Join(_, _, _)) => None
												case (Singleton(x), Empty()) => Option(x)
												case (Empty(),Singleton(x)) => Option(x)
												case (Singleton(x),Singleton(y)) =>	if(compare(x,y))
																						Option(x)
																					else
																						Option(y)

												case (Join(alist3,alist4,_),Empty()) => max(Join(alist3,alist4,alist3.size+alist4.size),compare)
												case (Empty(),Join(alist3,alist4,_)) => max(Join(alist3,alist4,alist3.size+alist4.size),compare)
												case (Join(alist3,alist4,_),Singleton(x)) => max(Join(alist3,alist4,alist3.size+alist4.size),compare) match {
    																							case Some(i) => max(Join(Singleton(i),Singleton(x),2),compare)
    																							case None => None
    																						}
																			//max(Join(Singleton(max(Join(alist3,alist4,alist3.size+alist4.size),compare).flatten),Singleton(x),2),compare)
																		//else
																			//maxElt(alist4,Singleton(x),compare)
												case (Singleton(x),Join(alist3,alist4,_)) => max(Join(alist3,alist4,alist3.size+alist4.size),compare) match {
    																							case Some(i) => max(Join(Singleton(i),Singleton(x),2),compare)
    																							case None => None
    																						}

												//max(Join(Singleton(max(Join(alist3,alist4,alist3.size+alist4.size),compare).flatten),Singleton(x),2),compare)
																		//if (compare(max(Join(alist3,Singleton(x),alist3.size+1)),max(Join(alist4,Singleton(x),alist4.size+1)))==true)
																		//	maxElt(Join(alist3,Singleton(x),alist3.size+1),compare)
																		//else
																		//	maxElt(Join(alist4,Singleton(x),alist4.size+1),compare)
											}
		}
		/*max(Join(alist3,alist4,alist3.size+alist4.size),compare) match {
    case Some(i) => max(Join(Singleton(i),Singleton(x),2),compare)
    case None => None
}
*/
}		

def first [A ]( lst : JoinList [A ]): Option [A] = {
	lst match{
		case Empty () => None	
		case Singleton ( x) => Option(x)
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match {
												case (Empty(),_) => None
												case (Singleton(x), _) => Option(x)
												//case (Empty(),Singleton(x)) => Option(x)
												//case (Singleton(x),Singleton(y)) =>	Option (x)
												case (Join(alist3,alist4,_),_) =>  first(alist3)

		}
	}
}

def rest [ A ]( lst : JoinList [ A ]): Option [ JoinList [ A ]] = {
	lst match{
		case Empty () => None
		case Singleton ( x) => Some(Empty())
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match {
												case (Empty(),Empty()) => None
												case (Singleton(x), Empty()) => None
												case (Empty(),Singleton(x)) => Option(Singleton(x))
												case (Singleton(x),Singleton(y)) => Option(Singleton(y))
												case (Join(alist3,alist4,_),Empty()) => Option(Join(tail(alist3),alist4,alist3.size+alist4.size-1))
												case (Empty(),Join(alist3,alist4,_)) => Option(Join(alist3,alist4,alist4.size+alist3.size))
												case (Join(alist3,alist4,_),Singleton(x)) => Option(Join(tail(alist3),Join(alist4,Singleton(x),alist4.size+1), alist3.size+alist4.size))
												case (Singleton(x),Join(alist3,alist4,_)) => Option(Join(alist3,alist4,alist3.size+alist4.size))
												case (Join(_,_,_),Join(_,_,_)) => None
}
}
}

def tail [ A ]( lst : JoinList [ A ]): JoinList [ A ] = {
	lst match{
		case Empty () => Empty()
		case Singleton ( _) => Empty()
		case Join ( alist1 , alist2, _) => (alist1, alist2) match{
										//case Empty () => Empty()
										//case Singleton ( x) => Empty()
										//case (Singleton(x), Empty()) => Empty()
										//case (Join(_,_,_),Join(_,_,_)) => Empty()
										case ( alist1, Empty()) => tail(alist1)
										//case (Singleton(x), Empty()) => Empty()
										case (Singleton(x),Singleton(y)) => Singleton(y)
										case ( Singleton(x), alist2) => alist2
	
										//case(Empty(),Empty()) => Empty()
										case ( alist3 , alist4) => Join(tail(alist3),alist4,alist4.size+alist3.size-1)
	
									
		}
		
	}

}


def map [A ,B ]( f: A => B , lst : JoinList [ A ]): JoinList [B] = {
	lst match{
		case Empty () => Empty()	
		case Singleton ( x) => Singleton(f(x))
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match {
												case (Empty(),Empty()) => Empty()
												case (Singleton(x), Empty()) => Join(Singleton(f(x)),Empty(),1)
												case (Empty(),Singleton(x)) => Join(Empty(),Singleton(f(x)),1)
												case (Singleton(x),Singleton(y)) => Join(Singleton(f(x)),Singleton(f(y)),2)
												case (Join(alist3,alist4,_),Empty()) => Join(map(f,alist3),map(f,alist4),alist3.size+alist4.size)
												case (Empty(),Join(alist3,alist4,_)) => Join(map(f,alist3),map(f,alist4),alist4.size+alist3.size)
												case (Join(alist3,alist4,_),Singleton(x)) => Join(map(f,alist3),Join(map(f,alist4),Singleton(f(x)),alist4.size+1), alist3.size+alist4.size+1)
												case (Singleton(x),Join(alist3,alist4,_)) => Join(Singleton(f(x)),Join(map(f,alist3),map(f,alist4),alist3.size+alist4.size),alist3.size+alist4.size+1)
												case (Join(_,_,_),Join(_,_,_)) => Empty()
	}
}	
	
}

def filter [A ]( pred : A => Boolean , lst : JoinList [ A ]): JoinList [A] = {
	lst match{
		case Empty () => Empty()	
		case Singleton ( x) if pred(x) == true => Singleton(x)
		case Singleton ( x) if pred(x) == false => Empty()
		case Join ( alist1 , alist2 , _) => (alist1,alist2) match{
												case (Empty(),Empty()) => Empty()
												case (Singleton(x), Empty()) if pred(x) == true  => Join(Singleton(x),Empty(),1)
												case (Singleton(x), Empty()) if pred(x) == false  => Join(Empty(),Empty(),0)


												case (Empty(),Singleton(x)) if pred(x) == true  => Join(Empty(),Singleton(x),1)
												case (Empty(),Singleton(x)) if pred(x) == false  => Join(Empty(),Empty(),0)

												case (Singleton(x),Singleton(y)) => Join(filter(pred,Singleton(x)),filter(pred,Singleton(y)),filter(pred,Singleton(x)).size+filter(pred,Singleton(y)).size)
												case (Join(alist3,alist4,_),Empty()) => Join(filter(pred,alist3),filter(pred,alist4),filter(pred,alist3).size+filter(pred,alist4).size)
												case (Empty(),Join(alist3,alist4,_)) => Join(filter(pred,alist3),filter(pred,alist4),filter(pred,alist3).size+filter(pred,alist4).size)

												case (Join(alist3,alist4,_),Singleton(x)) => Join(Join(filter(pred,alist3),filter(pred,alist4),filter(pred,alist3).size+filter(pred,alist4).size), filter(pred,Singleton(x)), filter(pred,alist3).size+filter(pred,alist4).size+filter(pred,Singleton(x)).size)
												case (Singleton(x),Join(alist3,alist4,_)) => Join(filter(pred,Singleton(x)),Join(filter(pred,alist3),filter(pred,alist4),filter(pred,alist3).size+filter(pred,alist4).size), filter(pred,alist3).size+filter(pred,alist4).size+filter(pred,Singleton(x)).size)
												case (Join(_,_,_),Join(_,_,_)) => Empty()
											}
	}
}

def nth [A ]( lst : JoinList [A ], n: Int ): Option [A] = {
	if(n==0) {
		lst match{
		case Empty () => None
		case Singleton ( x) => Option(x)
		case Join ( alist1 , alist2 , _) => first(lst)
		}
	}
		else{

			lst match{
		case Empty () => None	
		case Singleton ( x) => None
		case Join ( alist1 , alist2 , _) =>
											rest(lst) match {
												case Some(i) => nth(i,n-1)
												case None => None
											}
		//nth(rest(lst),n-1)
	}
	
		}


}

/*
def first [A ]( lst : JoinList [A ]): Option [A] = {
	lst match{
		case Empty () => None	
		case Singleton ( x) => Option(x)
		case Join ( alist1 , alist2 , _) => alist1 match {
			case head::tail => Option(head)
			case Nil => ???
		}
	}
}

def first [A ]( lst : JoinList [A ]): Option [A] = ???
def rest [ A ]( lst : JoinList [ A ]): Option [ JoinList [ A ]] = ???
def nth [A ]( lst : JoinList [A ], n: Int ): Option [A] = ???
def map [A ,B ]( f: A => B , lst : JoinList [ A ]): JoinList [B] = ???
def filter [A ]( pred : A => Boolean , lst : JoinList [ A ]): JoinList [A] = ???
*/
}


