object Data{


def yearIs ( data : List [ List [ String ]] , n : Int ): List [ List [ String ]] = {

	val record = data.head
	
	data.filter(record => record(0).toInt == n)

}

def yearGT ( data : List [ List [ String ]] , bound : Int ): List [ List [ String ]] = {

	val record = data.head
	
	data.filter(record => record(0).toInt > bound)

}

def yearLT ( data : List [ List [ String ]] , bound : Int ): List [ List [ String ]] = {
	
	val record = data.head
	
	data.filter(record => record(0).toInt < bound)
}

def onlyName ( data : List [ List [ String ]] , name : String ): List [ List [ String ]] = {
	val record = data.head
	
	data.filter(record => record(1) == name)
	
}

def mostPopular ( data : List [ List [ String ]]): ( String , Int ) = {
	val record = data.head;

	val lst = data.groupBy(record => record(1))
	
	val recordRec = lst.head

	val mod = lst.map(recordRec => (recordRec._1 ,count(recordRec._2)))

	mod.maxBy(_._2)
	
}

def count ( data : List [ List [ String ]]): Int = {
	
	data match {
		case head::tail => head(3).toInt + count(tail)
		case Nil => 0

	}
	
}

def countGirlsAndBoys ( data : List [ List [ String ]]): ( Int , Int ) = {


	val record = data.head
	val male = data.filter(record =>record(2) == "M")
	val female = data.filter(record => record(2) == "F")
	
	/*data match {
		case head::tail if (head(2)== "F") => (1 + countGirlsAndBoys(tail)._1, countGirlsAndBoys(tail)._2)
		case head::tail if (head(2)== "M") => (countGirlsAndBoys(tail)._1,1 + countGirlsAndBoys(tail)._2)
		case Nil => (0,0)

	}
*/

	(male.length, female.length)
}

def genderNeutralNames ( data : List [ List [ String ]]): Set [ String ] = {

	val record = data.head
	val male = data.filter(record =>record(2) == "M")
	val female = data.filter(record => record(2) == "F")

	val dupRecordMale = male.head
	val dupRecordFemale = female.head
	
	val maleName = male.map(dupRecordMale => dupRecordMale(1))
	val femaleName = female.map(dupRecordFemale => dupRecordFemale(1))

	val dupMale = maleName.toSet
	val dupFemale = femaleName.toSet


	dupMale.intersect(dupFemale)


}


def expectedAlive ( gender : String , birthYear : Int , currentYear : Int ): Boolean = {
	
	if(birthYear >= 1930 && birthYear <= 2010){
		import edu.umass.cs.CSV
		val allBirths = CSV.fromFile("cdc-life-expectancy.csv")
		val record = allBirths.head

		val recordExpected = allBirths.filter(record => record(0).toInt == birthYear)

		val recordRec = recordExpected.head


			if(gender == "M")
		  		(currentYear - birthYear) <= recordRec(1).toInt
		   	else //if(gender == "F")
		   		(currentYear - birthYear) <= recordRec(2).toInt
	}
	else{
		false
	}
	
}

def estimatePopulation ( data : List [ List [ String ]] , year : Int ): Int = {

	val record = data.head
	

	val list = data.filter(record => expectedAlive(record(2),record(0).toInt,year))
	
	list.map(record => record(3).toInt).sum


}

}