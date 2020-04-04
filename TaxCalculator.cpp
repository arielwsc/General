//Name: Ariel Souza de Carvalho
//Class: Fall - COSC 1436-81003
//Project 9: Tax calculator
//Revision: 1.0
//Date: 11/25/2019
//Description: This program will calculate how much the user needs to pay for their tax based on several details about them

#include <iostream>
#include <iomanip>

void getData(); //Function that will collect user's info to calculate their tax
float taxAmount(); //Function that will calculate user's tax

namespace variables{ //Declaration of variables that will be used to calculate user's tax
	enum civilStatus { SINGLE, MARRIED };
	char maritalStatus;
	float pensionFund, taxableIncome, tax, grossSalary;
	int numChildren;
}

using namespace variables;
using namespace std;

int main() {
	char again;
	do {
		getData(); //Call of getData function
		cout << fixed << setprecision(2);
		cout << "The amount of tax you need to pay is: $" << taxAmount() << endl; //Display to user how much tax they owe
		cout << "Would you like to calculate another tax return? (y/n)"; //Ask if user wishes to calculate tax again
		cin >> again;
	} while (again == 'y' || again == 'Y');

	return 0;
}

void getData() { //getData function definition

	cout << "What is your civil status (Enter 'S' for Single or 'M' for Married): ";
	cin >> maritalStatus; //Input user's civil status
	cin.ignore(1000, '\n');

	while ((maritalStatus != 'S') && (maritalStatus != 's') 
		&& (maritalStatus != 'm') && (maritalStatus != 'M')) { //This block validates user's input of their civil status
		cout << "Enter a valid input! \nEnter 'S' for Single or 'M' for Married\n";
		cin >> maritalStatus;
		cin.ignore(1000, '\n');
	}
	if (maritalStatus == 'm' || maritalStatus == 'M') { 
		maritalStatus = MARRIED; //Saves user's input into enum variable
		cout << "You entered you are married." << endl;
		cout << "How many children do you have? (Enter 0 if none)" << endl;
		cin >> numChildren; //Input user's number of kids
		
		cout << "Enter the combined gross salary of you and your spouse: ";
		cin >> grossSalary; //Input user's total gross salary from them and their spouses
	}
	else { //This block evaluates in case user is single
		maritalStatus = SINGLE; //Saves user's input into enum variable
		cout << "You entered you are single." << endl;
		cout << "Enter the Gross Salary of you this year: ";
		cin >> grossSalary; //Input user's total gross salary
		cout << endl;
	}
	cout << "What is the total fund you put into your pension for this year?" << endl;
	cin >> pensionFund; //input user's amount of pension fund

	while (pensionFund > 0.06*grossSalary) { //Validates user's pension fund not letting them enter a value greater than 6% of their Gross Salary
		cout << "The total pension fund can only be up to 6% of total Gross Salary. Enter again: ";
		cin >> pensionFund;
	}
}

float taxAmount() { //taxAmount function definition

	if (maritalStatus == MARRIED) //Verifies if user is married
		taxableIncome = grossSalary - (7000 + pensionFund + 2 * 1500 + 1500 * numChildren); //Calculates the taxable income based on married user's input
	else //This block evaluates if user is single
		taxableIncome = grossSalary - (4000 + pensionFund + 1500); //Calculates the taxable income based on single user's input

	if (taxableIncome >= 0 && taxableIncome <= 15000) { //Determine how much tax user will have to pay
		tax = 0.15 * taxableIncome;
		return tax;
	}
	else if (taxableIncome >= 15001 && taxableIncome <= 40000) {
		tax = 2250 + 0.25*(taxableIncome - 15000);
		return tax;
	}
	else if (taxableIncome > 40000){
		tax = 8460 + 0.35*(taxableIncome - 40000);
		return tax;
	}
	else{
		tax = 0;
		return tax;
	}
}