import java.nio.file._
import java.time._

object PathImplicits {
	
	implicit class RichPath (p: Path) {

		def /(str2: String): Path = p.resolve(str2)
		def /(p2: Path): Path = p.resolve(p2)
		def write(str: String): Path = Files.write(p, str.getBytes)
		def read(): String = Files.readAllBytes(p).map(_.toChar).mkString
		
		def append(str: String): Path = {
			if(Files.exists(p)) Files.write(p, str.getBytes, StandardOpenOption.APPEND)
			else write(str)

		}
	}

	implicit class RichString (str: String) {
		def /(str2: String): Path = Paths.get(str).resolve(str2)
		def /(p2: Path): Path = Paths.get(str).resolve(p2)
	}
}

object DateImplicits {

	implicit class RichInt(numb: Int) {

		def jan(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 1, numb)
		def feb(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 2, numb)
		def mar(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 3, numb)
		def apr(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 4, numb)
		def may(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 5, numb)
		def jun(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 6, numb)
		def jul(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 7, numb)
		def aug(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 8, numb)
		def sep(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 9, numb)
		def oct(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 10, numb)
		def nov(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 11, numb)
		def dec(implicit year: Int = LocalDate.now.getYear): LocalDate = LocalDate.of(year, 12, numb)

		def day(): Period = Period.ofDays(numb)
		def month(): Period = Period.ofMonths(numb)
		def year(): Period = Period.ofYears(numb)
		def days(): Period = Period.ofDays(numb)
		def months(): Period = Period.ofMonths(numb)
		def years(): Period = Period.ofYears(numb)
	}

	implicit class RichDate(date: LocalDate) {
		def +(x: Period): LocalDate = date.plus(x)
		def -(y: Period): LocalDate = date.minus(y)
	}
}