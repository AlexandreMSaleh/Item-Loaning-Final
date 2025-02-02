#ifndef LOAN_H
#define LOAN_H

#include <string>
using namespace std;

class Loan {
public:
	Loan(string itemName, string loaneeName, int loanID);
	string GetItemName();
	string GetLoaneeName();
	int GetID();
private:
	string itemName;
	string loaneeName;
	int loanID;
};



#endif
