#include "Clientes.h"

Clientes::Clientes(int ID, string Name, string RFC, int RegimenFiscalID, string Address, string City, string State, string ZipCode, int id_reg, int code_reg, string name_reg) : RegimenFiscal(id_reg, code_reg, name_reg)
{
	_ID = ID;
	_Name = Name;
	_RFC = RFC;
	_RegimenFiscalID = RegimenFiscalID;
	_Address = Address;
	_City = City;
	_State = State;
	_ZipCode = ZipCode;
}

Clientes::~Clientes()
{
}

void Clientes::setID(int ID)
{
	_ID = ID;
}

int Clientes::getID()
{
	return _ID;
}

void Clientes::setName(string Name)
{
	_Name = Name;
}

string Clientes::getName()
{
	return _Name;
}

void Clientes::setRFC(string RFC)
{
	_RFC = RFC;
}

string Clientes::getRFC()
{
	return _RFC;
}

void Clientes::setRegimenFiscalID(int RegimenFiscalID)
{
	_RegimenFiscalID = RegimenFiscalID;
}

int Clientes::getRegimenFiscalID()
{
	return _RegimenFiscalID;
}

void Clientes::setAddress(string Address)
{
	_Address = Address;
}

string Clientes::getAddress()
{
	return _Address;
}

void Clientes::setCity(string City)
{
	_City = City;
}

string Clientes::getCity()
{
	return _City;
}

void Clientes::setState(string State)
{
	_State = State;
}

string Clientes::getState()
{
	return _State;
}

void Clientes::setZipCode(string ZipCode)
{
	_ZipCode = ZipCode;
}

string Clientes::getZipCode()
{
	return _ZipCode;
}
