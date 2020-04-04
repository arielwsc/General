//Name: Ariel Souza de Carvalho
//Class: Fall - COSC 1436.81003
//Final Project: Cable Company Billing
//Revision: 1.0
//Date: 12/9/2019
//Description: This program will extract customer data from a file and calculate and output their bill to another file

#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

const double RES_BILL_PROC_FEES = 4.50; //Constant variables declaration
const double RES_BASIC_SERV_COST = 20.50;
const double RES_COST_PREM_CHANNEL = 7.50;
const double BUS_BILL_PROC_FEES = 15.00;
const double BUS_BASIC_SERV_COST = 75.00;
const double BUS_BASIC_CONN_COST = 5.00;
const double BUS_COST_PREM_CHANNEL = 50.00;
enum customer { RESIDENTIAL, BUSINESS, INVALID }; //enum variable to hold types of customers
char accountNumber[6] = { 0 }; //Array to hold customer account number
int rUser = 0, bUser = 0; //Counters for each type of customers
int numOfBasicServConn, numOfPremChannels; //Variables for amenities
double residentialTotal = 0, businessTotal =0; //Variables for sum of each customer type bills

customer getUserInfo(ifstream&); //Function to extract customers data from file
double residentialUser(); //Function to calculate residential customer bill
double businessUser(); //Funtion to calculate business customer bill
void printFile(ofstream&, customer); //Function to print customers bill to file

int main() {
	ifstream inFile;
	ofstream outFile;
	inFile.open("CableCompanyData.txt");
	outFile.open("CableCompanyBill.txt");

	inFile.ignore(200, '\n'); //Ignore header information on input file

	while (!inFile.eof()) { //Evaluates while not end of file
		printFile(outFile, getUserInfo(inFile));
	}
	outFile << "Average of residential customers: $" << residentialTotal / ((rUser == 0) ? rUser = 1:rUser); //Print to file average of residential customers
	outFile << endl;
	outFile << "Average of business customers: $" << businessTotal / ((bUser == 0) ? rUser = 1:bUser); //Print to file average of business customers

	outFile.close();
	inFile.close();

	return 0;
}

customer getUserInfo(ifstream& inFile){
	char customerType;

	inFile >> customerType; //Extract first character of customer info

	for (int i = 0; i <= 5; i++) //For loop to save each single digit of account number to array
		inFile >> accountNumber[i];

	switch (customerType) { //Determine type of customer, check if customer has a valid data and read it

	case 'r':
	case 'R':
		inFile.ignore(1000, ' ');
		rUser++;
		inFile >> numOfPremChannels;
		inFile.ignore(1000, '\n');
		return RESIDENTIAL;
		break;
	case 'b':
	case 'B':
		inFile.ignore(1000, ' ');
		bUser++;
		inFile >> numOfBasicServConn;
		inFile.ignore(1000, ' ');
		inFile >> numOfPremChannels;
		return BUSINESS;
	default:
		inFile.ignore(1000, '\n');
		return INVALID;
	}
}

double residentialUser() { //This function returns amount due for residential customers
	double amountDue = RES_BILL_PROC_FEES + RES_BASIC_SERV_COST + numOfPremChannels * RES_COST_PREM_CHANNEL;
	residentialTotal = residentialTotal + amountDue;
	return amountDue;
}

double businessUser() { //This function returns amount due for business customers
	if (numOfBasicServConn <= 10) {
		double amountDue = BUS_BILL_PROC_FEES + BUS_BASIC_SERV_COST + numOfPremChannels + BUS_COST_PREM_CHANNEL;
		businessTotal = businessTotal + amountDue;
		return amountDue;
	}

	else {
		double amountDue = BUS_BILL_PROC_FEES + BUS_BASIC_SERV_COST + (numOfBasicServConn - 10) * BUS_BASIC_CONN_COST + numOfPremChannels + BUS_COST_PREM_CHANNEL;
		businessTotal = businessTotal + amountDue;
		return amountDue;
	}
}

void printFile(ofstream& outFile, customer customerType) { //Print to file the customer account number and amount due

	outFile << fixed << setprecision(2) << right;

	if (customerType == RESIDENTIAL) {
		outFile << "Account number: ";
		for (int i = 0; i <= 5; i++)
			outFile << accountNumber[i];
		outFile << " / Account type: Residential";
		outFile << setw(2) << "/" << " Total to pay: $" << residentialUser() << endl;
	}
	else if (customerType == BUSINESS) {
		outFile << "Account number: ";
		for (int i = 0; i <= 5; i++)
			outFile << accountNumber[i];
		outFile << " / Account type: Business";
		outFile << setw(5) << "/" << " Total to pay: $" << businessUser() << endl;
	}
	else
		outFile << "Invalid data" << endl;
}