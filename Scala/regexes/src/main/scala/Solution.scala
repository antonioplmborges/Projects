import scala.util.matching.Regex

object Regexes extends hw.regex.RegexLike { 
	def notAlphanumeric: Regex = "[^A-Za-z0-9]*".r
	//val regtime = """(2[0-3])|([0-1][0-9]):[0-5][0-9]""".r
	def time: Regex = "(2[0-3]|[0-1][0-9]):[0-5][0-9]".r
	def phone: Regex = "^\\(\\d{3}\\)\\s\\d{3}-\\d{4}".r
	//val zCode ="""(([0-9]{5})|([0-9]{5}[-][0-9]{4}))""".r
	def zip: Regex = "(\\d{5}|\\d{5}-\\d{4})".r
	def comment: Regex = "/\\*.*\\*/".r
	def numberPhrase: Regex = "(twenty|thirty|forty|fifty|sixty|seventy|eighty|ninety)(-(one|two|three|four|five|six|seven|eight|nine)){0,1}".r
	def roman: Regex = "X{0,3}(IX|IV|V?I{0,3})".r
	// val dat="""([0-9]{4}[-](01|03|05|07|08|10|12)[-]((3[0-1])|([0-2][0-9])))|([0-9]{4}[-](04|06|09|11)[-]((30)|([0-2][0-9])))|[0-9][0-9][02468][048][-](02)[-](2[0-9])|([0-9][0-9][13579][26][-](02)[-]((2[0-8])|([0-1][0-9])))""".r
	def date: Regex = "((\\d{2}([02468][048]|[13579][26])-02-0?(1[0-9]|2[0-9]))|(\\d{4}-02-0?(1[0-9]|2[0-8]))|(\\d{4}-(0[13578]|1[02])-([012]\\d|3[01]))|(\\d{4}-(0[469]|11)-([012]\\d|30)))".r
	//val parity ="""(([02468]*[13579]){2})|[02468]*$""".r
	def evenParity: Regex = "[02468]*([02468]*[13579][02468]*[13579][02468]*)*".r
}