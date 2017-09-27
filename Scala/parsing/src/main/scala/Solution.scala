import hw.parsing._
import scala.util.parsing.combinator._

object ArithEval extends ArithEvalLike { 

	def eval(e: Expr): Double = e match {
		case Num(e1) => e1.toDouble
		case Add(e1,e2) => eval(e1) + eval(e2)
		case Sub(e1,e2) => eval(e1) - eval(e2)
		case Mul(e1,e2) => eval(e1) * eval(e2)
		case Div(e1,e2) => eval(e1) / eval(e2)
		case Exponent(e1,e2) => Math.pow(eval(e1), eval(e2))
	}

}

object ArithParser extends ArithParserLike {

 	//number: PackratParser[Double] is defined in ArithParserLike
	lazy val atom: PackratParser[Expr] = number ^^ (x => Num(x)) | "("~>expr<~ ")"
	lazy val exponent: PackratParser[Expr] = exponent~"^"~atom ^^ { case x~"^"~y => Exponent(x,y)} | atom
	lazy val add: PackratParser[Expr] = mul~"+"~add ^^ { case x~"+"~y => Add(x,y)} | mul~"-"~add ^^ { case x~"-"~y => Sub(x,y)} | mul
	lazy val mul: PackratParser[Expr] = exponent~"*"~mul ^^ { case x~"*"~y => Mul(x,y)} | exponent~"/"~mul ^^ { case x~"/"~y => Div(x,y)} | exponent
	lazy val expr: PackratParser[Expr] = add
}

object ArithPrinter extends ArithPrinterLike {
	
	def print(e: Expr): String = e match {
		case Num(e1) => e1.toString
		case Add(e1,e2) => "("+print(e1)+")" + " + " + "("+print(e2)+")"
		case Sub(e1,e2) => "("+print(e1)+")" + " - " + "("+print(e2)+")"
		case Mul(e1,e2) => "("+print(e1)+")" + " * " + "("+print(e2)+")"
		case Div(e1,e2) => "("+print(e1)+")" + " / " + "("+print(e2)+")"
		case Exponent(e1,e2) => "("+print(e1)+")" + " ^ " + "("+print(e2)+")"
	}
	
}