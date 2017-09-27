import hw.generics._

sealed trait BinTree[A] extends ListLike [A, BinTree[A]]

case class Node[A](lhs: BinTree[A], value: A, rhs: BinTree[A]) extends BinTree[A] {
	
	def head(): Option[A] = lhs.head match {
		case Some(h) => Some(h)
		case None => Some(value) 
	}

	def tail(): Option[BinTree[A]] = lhs.tail match {
		case Some(t) => Some(Node(t, value, rhs))
		case None => Some(rhs)  
	}

	def isEmpty(): Boolean = false
	def cons(h: A): BinTree[A] = Node(Leaf(), value, this)
}

case class Leaf[A]() extends BinTree[A] {

	def head(): Option[A] = None

	def tail(): Option[BinTree[A]] = None

	def isEmpty(): Boolean = true
	def cons(h: A): BinTree[A] = Node(this, h, Leaf())
}

object ListFunctions {

	def filter[A, L <: ListLike[A, L]](f: A => Boolean, alist: L): L = listLikeMatch[A, L](alist) match {
		    
		    case Some((h, t)) => {
		    							if (f(h)) filter(f, t).cons(h)
	    								else filter(f, t)
	    							}
	    	case None => alist
	}
	

	def append[A, L <: ListLike[A, L]](alist1: L, alist2: L): L = {
		listLikeMatch[A, L](alist1) match {
			case Some((h, t)) => append[A, L](t, alist2).cons(h)
			case None => alist2
		}
	}

	def insertOrdered[A <: Ordered [A], L <: ListLike[A, L]](value: A, alist: L): L = {
		listLikeMatch[A, L](alist) match {
			case Some((h, t)) => {
				if(h.compare(value) == EQ || h.compare(value) == GT) alist.cons(value)
				else insertOrdered[A, L](value, t).cons(h)
			}
			case None => alist.cons(value)
		}
	}

	def sort[A <: Ordered [A], L <: ListLike[A, L]](alist: L): L = listLikeMatch[A, L](alist) match {
			case Some((h, t)) => insertOrdered[A, L](h, sort[A, L](t))
			case None => alist
		}

	def listLikeMatch[A, L <: ListLike[A, L]](alist: L): Option[(A, L)] = {
		(alist.head(), alist.tail()) match {
			case (Some(h), Some(t)) => Some((h, t))
		    case (None, None) => None
		    case _ => throw new IllegalArgumentException("Not ListLike")
		}
	}
		
	
}

class C1 extends T2[Int, Int, String, String] with T3[Int, Int, Int, String, String, String, Int]{
// Do not change the class body . Simply extend T1 , T2 , and /or T3.
	def f(a: Int , b: Int ): Int = 0
	def g(c: String ): String = ""
	def h(d: String ): Int = 0
}
class C2 extends T1[Int, Int] with T2[Int, Int, Int, Int] with T3[Int, Int, Int, Int, Int, Int, Int]{
// Do not change the class body . Simply extend T1 , T2 , and /or T3.
	def f(a: Int , b: Int ): Int = 0
	def g(c: Int ): Int = 0
	def h(d: Int ): Int = 0
}
class C3[A](x: A) extends T3[Int, A, Int, A, String, String, A]{
// Do not change the class body . Simply extend T1 , T2 , and /or T3.
	def f(a: Int , b: A): Int = 0
	def g(c: A): String = ""
	def h(d: String ): A = x
}
class C4[A](x: Int , y: C4[A]) extends T3[Int, C4[A], C4[A], Int, C4[A], C4[A], Int]{
// Do not change the class body . Simply extend T1 , T2 , and /or T3.
	def f(a: Int , b: C4[A]): C4[A] = b
	def g(c: Int ): C4[A] = y
	def h(d: C4[A]): Int = x
}