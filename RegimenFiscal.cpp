#include "RegimenFiscal.h"

RegimenFiscal::RegimenFiscal(int ID, int code, string Name)
{
    _ID = ID;
    _code = code;
    _Name = Name;
}

RegimenFiscal::~RegimenFiscal()
{
}

void RegimenFiscal::setID(int ID)
{
    _ID = ID;
}

int RegimenFiscal::getID()
{
    return _ID;
}

void RegimenFiscal::setCode(int code)
{
    _code = code;
}

int RegimenFiscal::getCode()
{
    return _code;
}

void RegimenFiscal::setName(string Name)
{
    _Name = Name;
}

string RegimenFiscal::getName()
{
    return _Name;
}
