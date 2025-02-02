#include <iostream>
#include <vector>
using namespace std;

#include "Loan.h"
#include "Item.h"

static bool IsValidString(string s)
{
    if (s.length() == 0 || s.at(0) == ' ' || s.at(s.length()-1) == ' ' || isdigit(s.at(0))) return false;
    for (int i = 1; i < s.length(); i++)
    {
        if (s.at(i) == ' ' && s.at(i - 1) == ' ') return false;
        if (isdigit(s.at(i))) return false;
    }
}

static bool IsCommand(string input)
{
    if (input == "create item" || input == "create loan" || input == "list items" || input == "list loans" || input == "delete item"
        || input == "delete loan" || input == "save" || input == "exit" || input == "help") return true;
    else return false;
}

static void PrintCommands()
{
    cout << "Available commands:" << endl << "create item: creates an item to be loaned." << endl <<
        "create loan: creates a loan to be tracked." << endl << "list items: lists all known items." << endl <<
        "list loans: list all known loans." << endl << "delete item: deletes an item from the known list." << endl <<
        "delete loan: deletes a loan from the known list." << endl <<
        "save: saves known items and loans to a file to be used later." << endl << "exit: quits LoanIt." << endl << endl;
}

static Item CreateItem()
{
    string name = "";
    string description = "";

    while (!IsValidString(name))
    {
        cout << "Please enter the item name:" << endl << endl;
        getline(cin, name);
        if (!IsValidString(name)) cout << "Invalid input, please try again." << endl << endl;
    }
    
    while (!IsValidString(description))
    {
        cout << "Please enter the item description:" << endl << endl;
        getline(cin, description);
        if (!IsValidString(description)) cout << "Invalid input, please try again." << endl << endl;
    }

    return Item(name, description);
}

static void ListItems(vector<Item> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "Item " << i+1  << ": " << endl << "Name: " << list[i].GetName() << endl 
            << "Description: " << list[i].GetDescription() << endl << endl;
    }
    cout << endl;
}

static vector<Item> DeleteItem(vector<Item> list)
{
    bool wasDeleted = false;
    string deleteName = "";
    
    while (!wasDeleted)
    {
        cout << "Please enter the name of the item you want to delete:" << endl << endl;
        getline(cin, deleteName);

        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].GetName() == deleteName)
            {
                list.erase(list.begin() + i);
                wasDeleted = true;
            }
        }
        if (!wasDeleted) cout << "Entered item name did not match a known item, please try again." << endl << endl;
    }
    cout << "All items of selected name successfully deleted!" << endl << endl;
    return list;
}

static Loan CreateLoan(int loanID, vector<Item> list)
{
    string itemName = "";
    string loaneeName = "";
    bool validName = false;

    while (!validName)
    {
        cout << "Please enter the name of the item you are loaning:" << endl << endl;
        getline(cin, itemName);
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].GetName() == itemName)
            {
                validName = true;
            }
        }
        if (!validName)
        {
            cout << "Entered name did not match a known item name, please enter a name from this list:" << endl << endl;
            cout << "Known Item Names:" << endl;
            for (int i = 0; i < list.size(); i++)
            {
                cout << list[i].GetName() << endl;
            }
            cout << endl;
        }
    }
    
    while (!IsValidString(loaneeName))
    {
        cout << "Please enter the name of the person to whom the item is being loaned:" << endl << endl;
        getline(cin, loaneeName);
        if (!IsValidString(loaneeName)) cout << "Invalid input, please try again." << endl << endl;
    }
    
    return Loan(itemName, loaneeName, loanID);
}

static void ListLoans(vector<Loan> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << "Loan " << i + 1 << ": " << endl << "Item Name: " << list[i].GetItemName() << endl
            << "Loanee: " << list[i].GetLoaneeName() << endl << "Loan ID: " << list[i].GetID() << endl << endl;
    }
    cout << endl;
}

static vector<Loan> DeleteLoan(vector<Loan> list)
{
    bool wasDeleted = false;
    int deleteID = -1;
    string input = "";
    bool isValidID = false;
    
    while (!wasDeleted)
    {
        while (!isValidID)
        {
            isValidID = true;
            cout << "Please enter the ID of the loan you want to delete:" << endl << endl;
            cin >> input;
            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input.at(i))) isValidID = false;
            }
            if (!isValidID) cout << "Invalid loan ID entered, please try again." << endl << endl;
            if (isValidID) deleteID = stoi(input);
        }

        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].GetID() == deleteID)
            {
                list.erase(list.begin() + i);
                wasDeleted = true;
            }
        }
        if (!wasDeleted)
        {
            cout << "Entered loan ID did not match a known loan ID, please try again." << endl << endl;
            isValidID = false;
        }
    }
    cout << "Loan successfully deleted." << endl << endl;
    cin.ignore();
    return list;
}

int main()
{
    string command = " ";
    bool done = false;
    vector<Item> items;
    vector<Loan> loans;

    cout << "Welcome to LoanIt!" << endl << "For command list type 'help'." << endl << endl;
    
    while (!done)
    {
        getline(cin, command);
        if (!IsCommand(command))
        {
            cout << "Unrecognized command: " << command << endl << endl;
            PrintCommands();
            continue;
        }

        if (command == "exit") done = true;
        if (command == "help") PrintCommands();
        if (command == "create item")
        {
            items.push_back(CreateItem());
            cout << "Item successfully created!" << endl << endl;
        }
        if (command == "list items")
        {
            if (items.size() == 0)
            {
                cout << "No items available." << endl << endl;
                continue;
            }
            ListItems(items);
        }
        if (command == "delete item")
        {
            if (items.size() == 0)
            {
                cout << "No items available for deletion." << endl << endl;
                continue;
            }
            items = DeleteItem(items);
        }
        if (command == "create loan")
        {
            loans.push_back(CreateLoan(loans.size(), items));
            cout << "Loan successfully created!" << endl << endl;
        }
        if (command == "list loans")
        {
            if (loans.size() == 0)
            {
                cout << "No loans available." << endl << endl;
                continue;
            }
            ListLoans(loans);
        }
        if (command == "delete loan")
        {
            if (loans.size() == 0)
            {
                cout << "No loans available for deletion." << endl << endl;
                continue;
            }
            loans = DeleteLoan(loans);
        }
    }
    return 0;
}