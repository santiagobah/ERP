#include "Presentacion.h"

Presentacion::Presentacion(int ID, string Name)
{
	_ID = ID;
	_Name = Name;
}

Presentacion::~Presentacion()
{
}

void Presentacion::setID(int ID)
{
	_ID = ID;
}

int Presentacion::getID()
{
	return _ID;
}

void Presentacion::setName(string Name)
{
	_Name = Name;
}

string Presentacion::getName()
{
	return _Name;
}