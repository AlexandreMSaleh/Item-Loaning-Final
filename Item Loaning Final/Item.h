#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {
	public:
		Item(string name, string description);
		string GetName();
		string GetDescription();
	private:
		string itemName;
		string itemDescription;
};



#endif
