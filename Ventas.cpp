#include "Ventas.h"

Ventas::Ventas(int ID, DateTime DateOfSale, int userID, int clientID, float total)
{
	_ID = ID;
	_DateOfSale = DateOfSale;
	_userID = userID;
	_clientID = clientID;
	_total = total;
}

Ventas::~Ventas()
{
}

void Ventas::setID(int ID)
{
	_ID = ID;
}

int Ventas::getID()
{
	return _ID;
}

void Ventas::setDateOfSale(DateTime DateOfSale)
{
	_DateOfSale = DateOfSale;
}

DateTime Ventas::getDateOfSale()
{
	return _DateOfSale;
}

void Ventas::setUserID(int userID)
{
	_userID = userID;
}

int Ventas::getUserID()
{
	return _userID;
}

void Ventas::setClientID(int clientID)
{
	_clientID = clientID;
}

int Ventas::getClientID()
{
	return _clientID;
}

void Ventas::setTotal(float total)
{
	_total = total;
}

float Ventas::getTotal()
{
	return _total;
}
