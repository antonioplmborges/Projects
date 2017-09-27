import Data._

class TestSuite extends org.scalatest.FunSuite {

/*
val list = List(

List("1980",	"Mary","F","7065"),
List("1980",	"Mary","M",	"2604"),
List("1980",	"Emma","F",	"2003"),
List("1980",	"Eliza","F",	"1939"),
List("1980",	"Bessi","F",	"1746"),
List("1980",	"Marga",	"F",	"1578"),
List("1980",	"Ida", "F",	"1472"),
List("1980",	"Alice",	"F"	,"1414"),
List("1980",	"Berth",	"F",	"132"),
List("1980",	"Sarah",	"F"	,"1288"),
List("1980",	"Annie",	"F",	"1258"),
List("1980",	"Clara",	"F",	"1226"),
List("1980",	"Ella","F",	"1156"),
List("1980",	"Flore", "F",	"1063"),
List("1980",	"Cora",     "F", "1045"),
List("1980",	"Marth",	"F",	"1040"),
List("1980",	"Laura",	"F", "1012"),
List("1980",	"Nelli",	"F",	"995"),
List("1980",	"Grace",	"F",	"982"),
List("1980",	"Carri",	"F",	"949"),
List("1980",	"Maude",	"F"	,"858"),
List("1980",	"Mabel",	"F"	,"808"),
List("1980",	"Bessi", "M" ,"796")
)


println(mostPopular(list))
println(estimatePopulation(list,2001))
println(count(list))
println(genderNeutralNames(list))
println(countGirlsAndBoys(list))
yearIs(list,1880).foreach(println)
//println(yearIs(list,1880))
count(list)
println(expectedAlive("M",1994,2067))
*/

import edu.umass.cs.CSV
val allBirths = CSV.fromFile("ssa-births.csv")
println(countGirlsAndBoys (yearGT(yearLT(allBirths,2001),1989)))
println(count (onlyName(yearIs(allBirths,2010),"Emma")) > count (onlyName(yearIs(allBirths,2009),"Emma")))
println(mostPopular (yearIs(allBirths,2013)))
println(estimatePopulation ( yearGT ( allBirths , 1980) , 2010))
}
