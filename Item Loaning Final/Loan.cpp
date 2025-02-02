#include <iostream>
using namespace std;

#include "Loan.h"

Loan::Loan(string item, string loanee, int id)
{
	itemName = item;
	loaneeName = loanee;
	loanID = id;
}

string Loan::GetItemName()
{
	return itemName;
}

string Loan::GetLoaneeName()
{
	return loaneeName;
}

int Loan::GetID()
{
	return loanID;
}