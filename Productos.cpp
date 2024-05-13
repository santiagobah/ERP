#include "Productos.h"

Productos::Productos(int ID, int UPC, string Name, int ID_Presentation, float Price, float Cost, bool hasIVA, int stock)
{
	_ID = ID;
	_UPC = UPC;
	_Name = Name;
	_ID_Presentation = ID_Presentation;
	_Price = Price;
	_Cost = Cost;
	_hasIVA = hasIVA;
	_stock = stock;
}

Productos::~Productos()
{
}

void Productos::setID(int ID)
{
	_ID = ID;
}

int Productos::getID()
{
	return _ID;
}

void Productos::setUPC(int UPC)
{
	_UPC = UPC;
}

int Productos::getUPC()
{
	return _UPC;
}

void Productos::setName(string Name)
{
	_Name = Name;
}

string Productos::getName()
{
	return _Name;
}

void Productos::setID_Presentation(int ID_Presentation)
{
	_ID_Presentation = ID_Presentation;
}

int Productos::getID_Presentation()
{
	return _ID_Presentation;
}

void Productos::setPrice(float Price)
{
	_Price = Price;
}

float Productos::getPrice()
{
	return _Price;
}

void Productos::setCost(float Cost)
{
	_Cost = Cost;
}

float Productos::getCost()
{
	return _Cost;
}

void Productos::setHasIVA(bool hasIVA)
{
	_hasIVA = hasIVA;
}

bool Productos::getHasIVA()
{
	return _hasIVA;
}

void Productos::setStock(int stock)
{
	_stock = stock;
}

int Productos::getStock()
{
	return _stock;
}