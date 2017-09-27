class TrivialTestSuite extends org.scalatest.FunSuite {
	
	test("The Regexes object must be defined") { 
		
		val regexes: hw.regex.RegexLike = Regexes

		assert(regexes.notAlphanumeric.pattern.matcher("abcd1234").matches() == false)
		assert(regexes.notAlphanumeric.pattern.matcher("@#$!").matches() == true)
		assert(regexes.notAlphanumeric.pattern.matcher("asdf#$").matches() == false)
		assert(regexes.notAlphanumeric.pattern.matcher(" _ ").matches() == true)

		assert(regexes.time.pattern.matcher("10:33").matches() == true)
		assert(regexes.time.pattern.matcher("00;51").matches() == false)
		assert(regexes.time.pattern.matcher("00:51").matches() == true)
		assert(regexes.time.pattern.matcher("01:60").matches() == false)
		assert(regexes.time.pattern.matcher("24:10").matches() == false)


		assert(regexes.phone.pattern.matcher("[458] 123_3451").matches() == false)
		assert(regexes.phone.pattern.matcher("(123) 456-7890").matches() == true)
		assert(regexes.phone.pattern.matcher("(z91) 123-123").matches() == false)
		assert(regexes.phone.pattern.matcher("(000) 000-0000").matches() == true)
	

		assert(regexes.zip.pattern.matcher("01234").matches() == true)
		assert(regexes.zip.pattern.matcher("123a2-1234").matches() == false)
		assert(regexes.zip.pattern.matcher("10234a121").matches() == false)
	

		assert(regexes.comment.pattern.matcher("/* */").matches() == true)
		assert(regexes.comment.pattern.matcher("/*123asd,.*/").matches() == true)
		assert(regexes.comment.pattern.matcher("/*   /").matches() == false)
		assert(regexes.comment.pattern.matcher("/*abcd*/").matches() == true)

		assert(regexes.numberPhrase.pattern.matcher("forty").matches() == true)
		assert(regexes.numberPhrase.pattern.matcher("twenty-thirty").matches() == false)

		assert(regexes.roman.pattern.matcher("IVI").matches() == false)
		assert(regexes.roman.pattern.matcher("XXIX").matches() == true)
		assert(regexes.roman.pattern.matcher("XXV").matches() == true)
		assert(regexes.roman.pattern.matcher("XXXX").matches() == false)

		assert(regexes.date.pattern.matcher("2016-04-01").matches() == true)
		assert(regexes.date.pattern.matcher("2016-04-31").matches() == false)
		assert(regexes.date.pattern.matcher("2016-02-29").matches() == true)
		assert(regexes.date.pattern.matcher("2017-02-29").matches() == false)
		assert(regexes.date.pattern.matcher("2016-12-31").matches() == true)

		assert(regexes.evenParity.pattern.matcher("11").matches() == true)
		assert(regexes.evenParity.pattern.matcher("305").matches() == true)
		assert(regexes.evenParity.pattern.matcher("1132455").matches() == false)
		assert(regexes.evenParity.pattern.matcher("223465").matches() == true)
	
	} 
}