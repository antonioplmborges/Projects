class ProvidedTests extends org.scalatest.FunSuite {

  import java.nio.file.{Paths, Files}
  import java.time.LocalDate
  import PathImplicits._
  import DateImplicits._


  test("test string paths") {
    assert("usr" / "bin" / "scala" == Paths.get("usr/bin/scala"))
  }


  test("test join paths") {
    val p1 = "usr" / "local"
    val p2 = "bin" / "scala"
    assert(p1/p2 == Paths.get("usr/local/bin/scala"))
  }


  test("test current year") {
    assert(29.feb == LocalDate.of(2016, 2, 29))
    assert(1.jan == LocalDate.of(2016, 1, 1))   
  }

  test("test date1") {
    val date1 = 28 feb 2015
    assert(date1 == LocalDate.of(2015, 2, 28))
    val date2 = 15 oct 1989
    assert(date2 == LocalDate.of(1989, 10, 15))
  }

  test("test date2") {
    val date1 = LocalDate.of(2016, 1, 31) + 2.days
    assert(date1 == LocalDate.of(2016, 2, 2))
  }


  test("test date3") {
    val date1 = LocalDate.of(2016, 1, 31) + 3.months
    assert(date1 == LocalDate.of(2016, 4, 30))
  }



}