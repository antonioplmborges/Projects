#include <iostream>
#include <iomanip>

using namespace std;


class studentInfo
{
private:
	string studentName;//(First name and last name)
	int	studentId; //(an integer)
	double studentGpa; //(a double)

public:
	//Acessor
	string getStudentName() const;
	int getStudentId() const;
	double getStudentGpa() const;
	//Mutators
	void setStudentName(string);
	void setStudentId(int);
	void setStudentGpa(double);
	friend std::ostream& operator<<(std::ostream&, const studentInfo);
};

string studentInfo::getStudentName()const
{	return studentName;		}

int studentInfo::getStudentId() const
{	return studentId;	}

double studentInfo::getStudentGpa() const
{	return studentGpa;			}

void studentInfo::setStudentName(string name)
{
	studentName = name;
}

void studentInfo::setStudentId(int id)
{
	studentId = id;
}

void studentInfo::setStudentGpa(double gpa)
{
	studentGpa = gpa;
}


ostream& operator<<(std::ostream& cout, const studentInfo student)
{
	return cout << "\tID: " << student.getStudentId() << "\t\tGPA: " << setprecision(1) << fixed << student.getStudentGpa();
}
