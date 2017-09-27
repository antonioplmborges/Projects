import FunctionalDataStructures._

class TestSuite extends org.scalatest.FunSuite {

import FunctionalDataStructures._

test ("rest test000") {
		assert ( rest(Singleton(1)) == Some(Empty()) )
}

test ("dequeue test000") {
		assert ( dequeue(Queue(List())) == Some(1, Queue(List(2,3),List(6,5,4))) )
}

test ("enqueue test") {
		assert ( enqueue(2,Queue(List(1,2,3),List(6,5,4))) == Queue(List(1,2,3),List(2,6,5,4)) )
}

test ("enqueue test2") {
		assert ( enqueue(2,Queue(List(1,2,3),List())) == Queue(List(1,2,3),List(2)) )
}

test ("dequeue test1") {
		assert ( dequeue(Queue(List(1,2,3),List(6,5,4))) == Some(1, Queue(List(2,3),List(6,5,4))) )
}

test ("dequeue test2") {
		assert (  dequeue(Queue(List(),List(6,5,4))) == Some(4, Queue(List(5,6),List())) )
}



def fromList [ A ]( alist : List [A ]): JoinList [A ] = alist match {
case Nil => Empty ()
case List ( x) => Singleton ( x)
case _ => {
val len = alist.length
val (lhs,rhs ) = alist.splitAt ( len / 2)
Join (fromList ( lhs ), fromList ( rhs ) , len )
}
}
def toList [A ]( alist : JoinList [ A ]): List [A] = alist match {
case Empty () => Nil
case Singleton ( x) => List ( x)
case Join ( alist1 , alist2 , _) => toList ( alist1 ) ++ toList ( alist2 )
}

def compare(x:Int , y:Int): Boolean = x > y

val zero : JoinList[Int] = Empty()
val one = Singleton(1)
val two = Singleton(2)
val three = Singleton(3)
val lst12 = Join[Int](one,two,1+1)
val lst123 = Join[Int](lst12,three,lst12.size+1)
val four = Singleton(4)
val lst1234 = Join[Int](lst123,four,lst123.size+1)

//println(toList(Join[Int](lst1234,lst5,lst4.size+1)))
test ("match first test") {
first(lst1234) match {
	case Some(i) => 
		assert (  toList(Singleton(i)) == List(1) )
	
	case None => None
	}
}


test ("first test") {
		assert (  first(lst1234) == Some(1) )
}

test ("first test2") {
		assert (  first(lst123) == Some(1) )
}

test ("first test3") {
		assert (  first(zero) == None )
}

test ("match rest test") {
rest(lst1234) match {
	case Some(i) => 
		assert (  toList(Join(Empty(),i,i.size)) == List(2,3,4) )
	
	case None => None
	}
}

test ("match rest1 test") {
rest(one) match {
	case Some(i) => 
		assert (  toList(Join(Empty(),i,i.size)) == List() )
	
	case None => None
	}
}

test ("match rest2 test") {
rest(zero) match {
	case Some(i) => 
		//assert (  toList(Join(Empty(),i,i.size)) == List() )
	assert(false)
	case None => None
	}
}
//println(rest(one))
//println(rest(lst1234))
//println(rest(Join[Int](lst4,lst5,lst4.size+1)))

def f(x: Int ) = x + x


	
test ("map test") {
		assert (  toList(map(f,lst123))  == List(2,4,6) )
}

test ("map test2") {
		assert (  toList(map(f,lst1234))  == List(2,4,6,8) )
}

//println(map(f,lst123))
//println(map(f,lst1234))

def pred(x: Int ) = x<=2

test ("filter test") {
		assert (  toList(filter(pred,lst1234))  == List(1,2) )
}

test ("match nth test") {
nth(lst1234,2) match {
	case Some(i) => 
		assert (  toList(Singleton(i)) == List(3) )
	
	case None => None
	}
}

test ("match max test") {
max(lst1234,compare) match {
	case Some(i) => 
		assert (  toList(Singleton(i)) == List(4) )
	
	case None => None
	}
}

test ("match max2 test") {
max(lst123,compare) match {
	case Some(i) => 
		assert (  toList(Singleton(i)) == List(3) )
	
	case None => None
	}
}


//println(max(lst1234,compare))
//println(toList(Join[Int](List(Singleton(1),Singleton(2),Singleton(3)),Singleton(4),3+1)))


}
