//Name: Ariel Souza de Carvalho
//Class: Fall - COSC 1436.81003
//Project 10: Test Grader
//Revision: 1.0
//Date: 12/4/2019
//Description: This program will read test data from a file and calculate score and grade letter for each student

#include <iostream>
#include <fstream>
#include <iomanip>

void readFile(ifstream&); //Function to read information from file
float studentGrade(); //Function to calculate test score
char studentGradeLetter(float); //Function to calculate test letter
void printTestResult(float, char); //Function to print test results to prompt

namespace globalVar { //Variables declaration that will used by different functions
	char answersKey[20], studentAnswers[20]; //Arrays declarion that will store test key and student answers respectivelly
	char studentLetterID[3]; //Array to store sudent's ID letters
	char studentNumID[5] = { 0 }; //Array to store sudent's ID numbers
}

using namespace std;
using namespace globalVar;

int main() {
	ifstream inFile;
	inFile.open("testData.txt");

	while (!inFile.eof()) { //Flag loop that will check if end of file is true
		readFile(inFile);
		printTestResult(studentGrade(), studentGradeLetter(studentGrade()));
		return 0;
	}
}

void readFile(ifstream& inFile) {

		inFile.getline(answersKey, 21); //Read test key from file

		for (int i = 0; i <= 2; i++) //Stores each student's ID letter into one index of array
			inFile >> studentLetterID[i];
		for (int j = 0; j <= 4; j++) ////Stores each student's ID number into one index of array
			inFile >> studentNumID[j];

		inFile.ignore(1000, ' ');
		inFile.getline(studentAnswers, 21); //Read student's test answers from file
}

float studentGrade() {
	float testScore = 0;
	for (int i = 0; i <= 19; i++) { //Compare each student's answer with test key
		if (studentAnswers[i] == answersKey[i])
			testScore = testScore + 2; //Counts two points for each correct answer

		else if (studentAnswers[i] == 32) //Counts no point if question is not answered
			testScore = testScore;

		else if (studentAnswers[i] != answersKey[i]) //Take off 1 point for each wrong answer
			testScore = testScore - 1;
	}
	return testScore;
}

char studentGradeLetter(float testScore){ //Transcript test score to a letter
	char testLetter;

	if (testScore >= 0.90 * 40)
		testLetter = 'A';
	else if (testScore >= 0.80 * 40 && testScore <= 0.8999 * 40)
		testLetter = 'B';
	else if (testScore >= 0.70 * 40 && testScore <= 0.7999 * 40)
		testLetter = 'C';
	else if (testScore >= 0.60 * 40 && testScore <= 0.6999 * 40)
		testLetter = 'D';
	else
		testLetter = 'F';

	return testLetter;
}

void printTestResult(float testScore, char testGrade) { //Display test results
	cout << setprecision(2) << fixed;
	cout << "ID:";
	for (int i = 0; i <= 2; i++)
		cout << studentLetterID[i];
	for (int j = 0; j <= 4; j++)
		cout << studentNumID[j];
	cout << " Answers: ";
	for (int i = 0; i <= 19; i++)
		cout << studentAnswers[i];
	cout << " Test score: " << testScore << " Test grade: " << testGrade << endl;
}
