#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct DateTimeV
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class Ventas
{
public:
	Ventas(int ID, DateTimeV DateOfSale, int userID, int clientID, float total);
	~Ventas();

	void setID(int ID);
	int getID();
	void setDateOfSale(DateTimeV DateOfSale);
	DateTimeV getDateOfSale();
	void setUserID(int userID);
	int getUserID();
	void setClientID(int clientID);
	int getClientID();
	void setTotal(float total);
	float getTotal();
private:
	int _ID;
	DateTimeV _DateOfSale;
	int _userID;
	int _clientID;
	float _total;

};
