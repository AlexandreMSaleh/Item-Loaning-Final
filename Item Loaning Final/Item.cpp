#include <iostream>
using namespace std;

#include "Item.h"

Item::Item(string name, string description)
{
	itemName = name;
	itemDescription = description;
}

string Item::GetName()
{
	return itemName;
}

string Item::GetDescription()
{
	return itemDescription;
}