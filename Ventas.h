#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DateTime.h"

using namespace std;

class Ventas
{
public:
	Ventas(int ID, DateTime DateOfSale, int userID, int clientID, float total);
	~Ventas();

	void setID(int ID);
	int getID();
	void setDateOfSale(DateTime DateOfSale);
	DateTime getDateOfSale();
	void setUserID(int userID);
	int getUserID();
	void setClientID(int clientID);
	int getClientID();
	void setTotal(float total);
	float getTotal();
private:
	int _ID;
	DateTime _DateOfSale;
	int _userID;
	int _clientID;
	float _total;

};
