/*main.cpp*/

//
// Grade Analysis program in modern C++.
//
// Michael Lederer
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;
using  std::getline;


class Course
{
private:
	string Dept;
	int ClassNum;
	string Title;
	int A;
	int B;
	int C;
	int D;
	int F;
	int I;
	int NR;
	int S;
	int U;
	int W;
	string Instructor;
	int totalGrades;
	vector<double> distrib;
	double dfwRate;
	int totalStudents;
public:


	Course(string dept, int classNum, string title, int a, int b, int c, int d, int f, int i, int nr, int s, int u, int w, string instructor)
		: Dept(dept), ClassNum(classNum), Title(title), A(a), B(b), C(c), D(d), F(f), I(i), NR(nr), S(s), U(u), W(w), Instructor(instructor)

	{
		distrib.resize(5);
		for (auto &i : distrib)
		{
			i = 0;
		}
		totalGrades = 0;
		dfwRate = 0;
		totalStudents = 0;
		setDistrib();
	}

	void setDistrib()
	{

		//Gather total number of grades for distribution calculation
		totalStudents = totalStudents + A + B + C + D + F + I + NR + S + U + W;
		totalGrades = totalGrades + A + B + C + D + F;
		double dfw = A + B + C + D + F + W;
		if (D + F + W == 0)
		{
			dfwRate = 0.0;
		}
		else
		{
			dfwRate = ((((double)D + (double)F + (double)W) / (double)dfw) * 100);
		}

		//Calculate distribution

		distrib.at(0) = ((double)(A) / (double)totalGrades * 100);
		distrib.at(1) = ((double)(B) / (double)totalGrades * 100);
		distrib.at(2) = ((double)(C) / (double)totalGrades * 100);
		distrib.at(3) = ((double)(D) / (double)totalGrades * 100);
		distrib.at(4) = ((double)(F) / (double)totalGrades * 100);


	}

	string getDept()
	{
		return Dept;
	}
	int getTotalGrades()
	{
		return totalGrades;
	}
	int getA()
	{
		return A;
	}

	int getB()
	{
		return B;
	}

	int getC()
	{
		return C;
	}

	int getD()
	{
		return D;
	}

	int getF()
	{
		return F;
	}
	int getI()
	{
		return I;
	}
	int getNR()
	{
		return NR;
	}
	int getS()
	{
		return S;
	}
	int getU()
	{
		return U;
	}
	int getW()
	{
		return W;
	}
	string getInstructor()
	{
		return Instructor;
	}
	void printInfo()
	{
		cout << setprecision(2);
		cout << fixed;
		cout << Dept << " " << ClassNum << " " << "(" << Instructor << "):" << endl;
		cout << "  Num students: " << totalStudents << endl;
		if (totalGrades == 0)
		{
			cout << "  Distribution: no report" << endl;
		}
		else
		{
			cout << "  Distribution: " << distrib[0] << "%, " << distrib[1] << "%, " << distrib[2] << "%, " << distrib[3] << "%, " << distrib[4] << "%" << endl;
		}
		cout << "  DFW rate: " << dfwRate << "%" << endl;
	}
};

void fileRead(ifstream &file, vector<Course>& Courses)
{
	string line;
	string classEntries[14];
	getline(file, line); //Skip first line

	//Loop through file, taking each line as a course, until EOF
	while (!file.eof())
	{
		getline(file, line);
		//Stringstream for easier parsing
		stringstream ss(line);

		if (line.compare("") == 0)
		{
			break;
		}

		//Take in all values in the row
		for (auto &i : classEntries)
		{
			getline(ss, i, ',');
		}

		string dept = classEntries[0];
		int classNum = stoi(classEntries[1]);
		string title = classEntries[2];
		int A = stoi(classEntries[3]);
		int B = stoi(classEntries[4]);
		int C = stoi(classEntries[5]);
		int D = stoi(classEntries[6]);
		int F = stoi(classEntries[7]);
		int I = stoi(classEntries[8]);
		int NR = stoi(classEntries[9]);
		int S = stoi(classEntries[10]);
		int U = stoi(classEntries[11]);
		int W = stoi(classEntries[12]);
		string instructor = classEntries[13];

		Course c(dept, classNum, title, A, B, C, D, F, I, NR, S, U, W, instructor);
		Courses.push_back(c);
	}
}

void printDistributions(vector<Course>& Courses)
{
	vector<string> departments;

	for (auto &i : Courses)
	{
		bool found = false;
		for (auto &j : departments)
		{
			if (j.compare(i.getDept()) == 0)
			{
				found = true;
			}
		}
		if (!found)
		{
			departments.push_back(i.getDept());
		}
	}

	for (auto &j : departments)
	{
		int numCourses = 0;
		int totalGrades = 0;
		vector<double> distrib;
		int totalA = 0;
		int totalB = 0;
		int totalC = 0;
		int totalD = 0;
		int totalF = 0;
		int totalI = 0;
		int totalNR = 0;
		int totalS = 0;
		int totalU = 0;
		int totalW = 0;
		for (auto &i : Courses)
		{
			if ((i.getDept()).compare(j) == 0)
			{
				totalA += i.getA();
				totalB += i.getB();
				totalC += i.getC();
				totalD += i.getD();
				totalF += i.getF();
				totalI += i.getI();
				totalNR += i.getNR();
				totalS += i.getS();
				totalU += i.getU();
				totalW += i.getW();
				numCourses++;
			}
		}
		totalGrades = totalGrades + totalA + totalB + totalC + totalD + totalF;

		distrib.push_back((double)(totalA) / (double)totalGrades * 100);
		distrib.push_back((double)(totalB) / (double)totalGrades * 100);
		distrib.push_back((double)(totalC) / (double)totalGrades * 100);
		distrib.push_back((double)(totalD) / (double)totalGrades * 100);
		distrib.push_back((double)(totalF) / (double)totalGrades * 100);

		cout << setprecision(2);
		cout << fixed;
		cout << j << ":" << endl;
		cout << "  Num courses:  " << numCourses << endl;
		cout << "  Num grades:   " << totalGrades << endl;
		if (totalGrades == 0)
		{
			cout << "  Distribution: no report" << endl;
		}
		else
		{
			cout << "  Distribution: " << distrib[0] << "%, " << distrib[1] << "%, " << distrib[2] << "%, " << distrib[3] << "%, " << distrib[4] << "%" << endl;
		}
	}
}

bool isPrefix(const string& instructor, const string& name)
{
	string substr = instructor.substr(0, name.size());
	if (substr.compare(name) == 0) return true;
	else return false;
}

void printCoursesByInstructor(vector<Course>& Courses, string name)
{
	for (auto &i : Courses)
	{
		if (isPrefix(i.getInstructor(), name) == true)
		{
			i.printInfo();
		}
	}
}

void collegeDistrib(vector<Course>& Courses)
{
	int numCourses = 0;
	int totalGrades = 0;
	vector<double> distrib;
	int totalA = 0;
	int totalB = 0;
	int totalC = 0;
	int totalD = 0;
	int totalF = 0;

	for (auto &i : Courses)
	{
		totalA += i.getA();
		totalB += i.getB();
		totalC += i.getC();
		totalD += i.getD();
		totalF += i.getF();
		numCourses++;
	}

	totalGrades = totalGrades + totalA + totalB + totalC + totalD + totalF;

	distrib.push_back((double)(totalA) / (double)totalGrades * 100);
	distrib.push_back((double)(totalB) / (double)totalGrades * 100);
	distrib.push_back((double)(totalC) / (double)totalGrades * 100);
	distrib.push_back((double)(totalD) / (double)totalGrades * 100);
	distrib.push_back((double)(totalF) / (double)totalGrades * 100);

	cout << setprecision(2);
	cout << fixed;
	cout << "College of Engineering:" << endl;
	cout << "  Num courses:  " << numCourses << endl;
	cout << "  Num grades:   " << totalGrades << endl;
	if (totalGrades == 0)
	{
		cout << "  Distribution: no report" << endl;
	}
	else
	{
		cout << "  Distribution: " << distrib[0] << "%, " << distrib[1] << "%, " << distrib[2] << "%, " << distrib[3] << "%, " << distrib[4] << "%" << endl;
	}
}

int main()
{
	string  filename;
	int numLines = 0;

	vector<Course> Courses;

	ifstream file;

	string input;
	cin >> input;

	if (!file.good())
	{
		cout << "cannot  open  file!" << endl;
		return  -1;
	}

	file.open(input);

	cout << input << endl << endl;

	//Parse file
	fileRead(file, Courses);

	collegeDistrib(Courses);

	//Output distributions for all departments
	printDistributions(Courses);

	cout << "Please enter instructor's name (or prefix or #)> ";

	//Loop for user searches
	while (1)
	{

		string input;
		cin >> input;
		cout << endl;

		if (input.compare("#") == 0) break;

		printCoursesByInstructor(Courses, input);

		cout << "Please enter instructor's name (or prefix or #)> " << endl;

	}

	cout << endl;
	return 0;
}
