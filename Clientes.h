#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "RegimenFiscal.h"

using namespace std;

class Clientes : public RegimenFiscal
{
public:
    Clientes(int ID, string Name, string RFC, int RegimenFiscalID, string Address, string City, string State, string ZipCode, int id_reg, int code_reg, string name_reg);
	~Clientes();

	void setID(int ID);
	int getID();
	void setName(string Name);
	string getName();
	void setRFC(string RFC);
	string getRFC();
	void setRegimenFiscalID(int RegimenFiscalID);
	int getRegimenFiscalID();
	void setAddress(string Address);
	string getAddress();
	void setCity(string City);
	string getCity();
	void setState(string State);
	string getState();
	void setZipCode(string ZipCode);
	string getZipCode();

private:
	int _ID;
	string _Name;
	string _RFC;
	int _RegimenFiscalID;
	string _Address;
	string _City;
	string _State;
	string _ZipCode;
};
