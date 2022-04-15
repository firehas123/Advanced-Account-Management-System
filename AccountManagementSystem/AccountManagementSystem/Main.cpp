#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;
//functions
string getDate();
//
class Customer;
enum AccType
{
	order, deadline
};
enum MoveType {
	credit,debit
};
class Movement
{
private:
	//data members
	string date;
	double value;
	MoveType movetyp;
public:
	//constructor
	Movement() {
		date = "";
		value = 0;
		movetyp = debit;
	}
	//getter and setter
	string getDate() {
		return date;
	}
	double getValue() {
		return value;
	}
	MoveType getMoveType() {
		return movetyp;
	}
	void setDate(string date) {
		this->date = date;
	}
	void setValue(double value) {
		this->value = value;
	}
	void setMoveType(MoveType movetyp) {
		this->movetyp = movetyp;
	}
};

class Account {
private:
	//data members
	int code;
	double balance;
	AccType accType;
	list<Movement> movements;

public:
	//operator overloading
	bool operator == (const Account& s) const { return balance == s.balance && code == s.code; }
	//constructors
	Account() {

	}
	~Account() {

	}
	//getter and setter
	void setCode(int code) {
		this->code = code;
	}
	void setBalance(double balance) {
		this->balance = balance;
	}
	void setAccountType(AccType accType) {
		this->accType = accType;
	}
	int getCode() {
		return code;
	}
	double getBalance() {
		return balance;
	}
	AccType getAccType() {
		return accType;
	}
	void printMovements() {
		list<Movement>::iterator it;
		for (auto item : movements) {
			cout << "Amount  = " + to_string(item.getValue()) + " is ";
			if (item.getMoveType() == 0)
				cout << "credit";
			else
				cout << "debit";
			cout << " on " +item.getDate() + "\n";

		}
	}
	void setZero() {
		balance = 0;
		code = -1;
		accType = order;
		if (movements.size() != 0)
		{
			movements.clear();
		}
	}
	void credit(int code, int amount) {
		Movement temp;
		
		temp.setMoveType(MoveType::credit);
		temp.setValue(amount);
		temp.setDate(getDate());
		
		movements.push_back(temp);
	}
	void debit(int code, int amount) {
		Movement temp;
		
		temp.setMoveType(MoveType::debit);
		temp.setValue(amount);
		temp.setDate(getDate());

		movements.push_back(temp);
	}
};
class Customer {
private:
	//data members
	Account acc;
	int code;
	string name;
	string address;
public:
	//operator overloading
	bool operator == (const Customer& s) const { return name == s.name && code == s.code && address == s.address; }
	bool operator != (const Customer& s) const { return !operator==(s); }
	//constructors
	Customer() {

	}
	~Customer() {

	}
	//getter and setter
	void setAcc(Account acc) {
		this->acc = acc;
	}
	void setCode(int code) {
		this->code = code;
	}
	void setName(string name) {
		this->name = name;
	}
	void setAddress(string address) {
		this->address = address;
	}
	Account& getAccount() {
		return acc;
	}
	int getCode() {
		return code;
	}
	string getName() {
		return name;
	}
	string getAddress() {
		return address;
	}
	//methods
	string toString() {
		string temp = "Code = " + to_string(code)+"\nName  = "+name+"\nAddress = "+address+"\nBalance = " + 
			to_string(acc.getBalance()) + "\n";
		return temp;
	}
	
};

class ManageCustomers {
private:
	//data members for taking input
	int temp1;
	string temp2;
	Customer obj;
public:
	void createCustomer(list<Customer>& cust) {
		cout << "Enter customer ID = ";
		cin >> temp1;
		obj.setCode(temp1);
		cout << "\nEnter customer name = ";
		cin >> temp2;
		obj.setName(temp2);
		cout << "\nEnter customer address = ";
		cin >> temp2;
		obj.setAddress(temp2);
		cust.push_back(obj);
	}
	void editCustomers(list<Customer>& cust) {
		cout << "Enter customer id you want to edit\n";
		cin >> temp1;
		bool chk = false;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				cout << "Enter new Code = ";
				cin >> temp1;
				it->setCode(temp1);
				cout << "\nEnter new name =  ";
				cin >> temp2;
				it->setName(temp2);
				cout << "\nEnter new Address = ";
				cin >> temp2;
				it->setAddress(temp2);
				chk = true;
				break;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}
	void consultCustomer(list<Customer>& cust) {
		cout << "Enter which customer id you want to consult\n";
		cin >> temp1;
		bool chk = false;
		for (auto item : cust) {
			if (item.getCode() == temp1) {
				cin.ignore();
				cout << "\nCode = "+to_string(item.getCode());
				cout << "\nName =  "+item.getName();
				cout << "\nAddress = "+item.getAddress();
				cout << "\nBalance = "+to_string(item.getAccount().getBalance());
				cout << "\n";
				chk = true;
			}
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}
	void removeCustomer(list<Customer>& cust) {
		cout << "Enter which customer id you want to consult\n";
		cin >> temp1;
		bool chk = false;
		int i = 0;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				it = cust.erase(it);
				chk = true;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}

};

class ManageCustomersAccount {
private:
	//data members for taking input
	int temp1;
	string temp2;
	double temp3;
	Customer obj;
public:
	void createAccount(list<Customer>& cust) {
		cout << "Enter customer ID = ";
		cin >> temp1;
		bool chk = false;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				it->getAccount().setCode(temp1);
				cout << "Which account you want to open?\n1. Order\n2. Deadline\n";
				cin >> temp1;
				if (temp1 == 1)
					it->getAccount().setAccountType(order);
				else if (temp1 == 2)
					it->getAccount().setAccountType(deadline);
				else
				{
					cout << "Invalid Input\n";
					return;
				}
				cout << "Enter amount you want to deposit?\n";
				cin >> temp3;
				it->getAccount().setBalance(temp3);
				it->getAccount().printMovements();
				
				chk = true;
				break;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}
	void editAccount(list<Customer>& cust) {
	
		cout << "Enter customer id you want to edit\n";
		cin >> temp1;
		bool chk = false;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				cout << "Change account type to:\n1. Order\n2. Deadline\n";
				cin >> temp1;
				if (temp1 == 1)
					it->getAccount().setAccountType(order);
				else if (temp1 == 2)
					it->getAccount().setAccountType(deadline);
				else
				{
					cout << "Invalid Input\n";
					return;
				}
				cout << "Enter new amount?\n";
				cin >> temp3;
				it->getAccount().setBalance(temp3);
				chk = true;
				break;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}
	void queryAccount(list<Customer>& cust) {
		cout << "Enter customer id you want to edit\n";
		cin >> temp1;
		bool chk = false;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				cout << "Customer code = " + to_string(temp1);
				temp1 = it->getAccount().getAccType();
				if (temp1 == 0)
					cout << "\nAccount type = Order\n";
				else 
					cout << "\nAccount type = Deadline\n";
				cout << "Balance = " + to_string(it->getAccount().getBalance())+ "\n";
				chk = true;
				break;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}

	void removeAccount(list<Customer>& cust) {
		cout << "Enter which customer id account you want to remove\n";
		cin >> temp1;
		bool chk = false;
		int i = 0;
		list<Customer>::iterator it;
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == temp1) {
				it->getAccount().setZero();
				chk = true;
				break;
			}
			else
				it++;
		}
		if (!chk)
			cout << "ID doesn't exist\n";
	}

};
//all functions
void showlist(list<Customer> g);
void manageCustomers(list<Customer> &cust);
void manageCustomerAccount(list<Customer>& cust);
void recordMovement(list<Customer>& cust);
void consult(list<Customer>& cust);
void groupCustomerbyLocale(list<Customer> cust);
void groupCustomerbyNegativeBalance(list<Customer> cust);
void getAccountInfo(int temp1, list<Customer> cust);
bool custExists(int temp1, list<Customer> cust);

//main function
int main() {
	//data members
	list<Customer> cust;
	// remove start
	Customer c1;
	c1.setName("Hassan");
	c1.setCode(123);
	c1.setAddress("DHA");
	Customer c2;
	c2.setName("Nauman");
	c2.setCode(456);
	c2.setAddress("DHA");
	cust.push_back(c1);
	cust.push_back(c2);
	showlist(cust);
	// remove end
	//showing console pannel
	bool pannel = true;
	int option;
	while (pannel) {
		cout << "Select an option\n";
		cout << "1. Manage customers\n";
		cout << "2. Manage customer accounts\n";
		cout << "3. Record movements\n";
		cout << "4. Consult\n";
		cout << "5. Group customer by locale\n";
		cout << "6. Group customer by negative balance\n";
		cout << "7. Exit\n";
		cin >> option;
		switch (option)
		{
		case 1:
			manageCustomers(cust);
			break;
		case 2:
			manageCustomerAccount(cust);
			break;
		case 3:
			recordMovement(cust);
			break;
		case 4:
			consult(cust);
			break;
		case 5:
			groupCustomerbyLocale(cust);
			break;
		case 6:
			groupCustomerbyNegativeBalance(cust);
			break;
		case 7:
			cout << "Have a nice day\n";
			pannel = false;
			break;
		default:
			cout << "Invalid input\nEnter again\n";
			break;
		}
	}
	return 0;
}
//functions defined
void showlist(list<Customer> g)
{
	list<Customer>::iterator it;
	for (auto item : g)
		cout <<item.toString();
}

void showlistAccount(list<Customer> g)
{
	list<Customer>::iterator it;
	for (auto item : g)
	{
		cout << item.toString();
		getAccountInfo(item.getCode(), g);
		item.getAccount().printMovements();
	}
}

void manageCustomers(list<Customer>& cust) {
	//showing console pannel
	bool pannel = true;
	int option;
	ManageCustomers mangageCustomers;
	while (pannel) {
		cout << "Select an option\n";
		cout << "1. Create customer\n";
		cout << "2. Edit customer\n";
		cout << "3. Consult customer\n";
		cout << "4. Remove customer\n";
		cout << "5. List customers\n";
		cout << "6. Exit\n";
		cin >> option;
		switch (option)
		{
		case 1:
			mangageCustomers.createCustomer(cust);
			break;
		case 2:
			mangageCustomers.editCustomers(cust);
			break;
		case 3:
			mangageCustomers.consultCustomer(cust);
			break;
		case 4:
			mangageCustomers.removeCustomer(cust);
			break;
		case 5:
			showlist(cust);
			break;
		case 6:
			pannel = false;
			break;
		default:
			cout << "Invalid input\nEnter again\n";
			break;
		}
	}
}

void manageCustomerAccount(list<Customer>& cust) {

	//showing console pannel
	bool pannel = true;
	int option;
	ManageCustomersAccount mangageCustomersacc;
	while (pannel) {
		cout << "Select an option\n";
		cout << "1. Create account\n";
		cout << "2. Edit account\n";
		cout << "3. Query account\n";
		cout << "4. Remove account\n";
		cout << "5. List accounts\n";
		cout << "6. Exit\n";
		cin >> option;
		switch (option)
		{
		case 1:
			mangageCustomersacc.createAccount(cust);
			break;
		case 2:
			mangageCustomersacc.editAccount(cust);
			break;
		case 3:
			mangageCustomersacc.queryAccount(cust);
			break;
		case 4:
			mangageCustomersacc.removeAccount(cust);
			break;
		case 5:
			showlistAccount(cust);
			break;
		case 6:
			pannel = false;
			break;
		default:
			cout << "Invalid input\nEnter again\n";
			break;
		}
	}
}

void recordMovement(list<Customer>& cust) {
	cout << "Enter your code = ";
	int code1; //nauman
	cin >> code1;
	cout << "\nEnter the code you want to make transaction with = ";
	int code2; //hassan
	cin >> code2;
	cout << "\n";
	if (custExists(code1,cust) && custExists(code2,cust)) {
		list<Customer>::iterator it;
		int amount = 0;
		cout << "Enter amount you want to send = ";
		cin >> amount;
		cout << "\n";
		for (it = begin(cust); it != end(cust);) {
			if (it->getCode() == code1) {
				//remove balance
				if (it->getAccount().getBalance() >= amount) {
					it->getAccount().setBalance(it->getAccount().getBalance() - amount);
					it->getAccount().credit(code2, amount);
				}
				else
					cout << "Insufficient balance in your bank\n";
			}
			if (it->getCode() == code2) {
				//add balance
				it->getAccount().setBalance(it->getAccount().getBalance() + amount);
				it->getAccount().debit(code1, amount);
			}
			it++;
		}
	}
	else {
		if (!custExists(code1, cust)) {
			cout << code1 + " doesn't exists\n";
		}
		else
			cout << code2 + " doesn't exists\n";
	}
}

void consult(list<Customer>& cust) {
	showlistAccount(cust);
}

void groupCustomerbyLocale(list<Customer> cust) {
	cout << "Enter the address = ";
	string temp1;
	cin >> temp1;
	list<Customer>::iterator it;
	cout << "\n";
	for (it = begin(cust); it != end(cust);) {
		if (it->getAddress() == temp1) {
			cout << it->toString();		
		}
		it++;
	}
}

void groupCustomerbyNegativeBalance(list<Customer> cust) {
	list<Customer>::iterator it;
	for (it = begin(cust); it != end(cust);) {
		if (it->getAccount().getBalance() == 0) {
			cout << it->toString();
		}
		it++;
	}
}
void getAccountInfo(int temp1, list<Customer> cust) {
	list<Customer>::iterator it;
	for (it = begin(cust); it != end(cust);) {
		if (it->getCode() == temp1) {
			cout << "Customer code = " + to_string(temp1);
			temp1 = it->getAccount().getAccType();
			if (temp1 == 0)
				cout << "\nAccount type = Order\n";
			else
				cout << "\nAccount type = Deadline\n";
			cout << "Balance = " + to_string(it->getAccount().getBalance()) + "\n";
			break;
		}
		else
			it++;
	}
}
bool custExists(int temp1, list<Customer> cust) {
	list<Customer>::iterator it;
	for (it = begin(cust); it != end(cust);) {
		if (it->getCode() == temp1) {
			return true;
		}
		else
			it++;
	}
	return false;
}
string getDate() {
	return "16/4/2022";
}
