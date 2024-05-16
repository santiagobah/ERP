#include "Usuarios.h"
#include <string>

using namespace std;

Usuarios::Usuarios(string name, string surname, string username, string password, string role, int id, DateTime date_joined)
{
    _id = id;
    _password = password;
    _role = role;
    _name = name;
    _lastname = surname;
    _date_joined = date_joined;
    _username = username;
}

Usuarios::~Usuarios()
{
}

void Usuarios::setId(int id_s) {
    _id = id_s;
}
void Usuarios::setUsername(string username_s) {
    _username = username_s;
}
void Usuarios::setPassword(string password_s) {
    _password = password_s;
}
void Usuarios::setRole(string role_s) {
    _role = role_s;
}
void Usuarios::setName(string name_s) {
    _name = name_s;
}
void Usuarios::setLastname(string lastname_s) {
    _lastname = lastname_s;
}

void Usuarios::setDateJoined(DateTime date_joined)
{
    _date_joined = date_joined;
}

int Usuarios::getId() {
    return _id;
}
string Usuarios::getUsername() {
    return _username;
}
string Usuarios::getPassword() {
    return _password;
}
string Usuarios::getRole() {
    return _role;
}
int Usuarios::getRoleInt()
{
    if (_role == "Admin") {
        return 1;
    }
    else if (_role == "Vendedor") {
        return 2;
    }
    else if (_role == "RH") {
        return 3;
    }
    else if (_role == "Almacen") {
        return 4;
    }
    else
    {
       return 0;
    }

}
string Usuarios::getName() {
    return _name;
}
string Usuarios::getLastname() {
    return _lastname;
}

DateTime Usuarios::getDateJoined()
{
    return _date_joined;
}

string Usuarios::Encrypt(string password)
{
    //Obtiene hash por medio de los c—digos ascii
    unsigned int hash = 0;
    for (int i = 0; i < password.length(); ++i) {
        hash = hash * 37 + password[i];
    }
    int hashInt = hash;
    string final = to_string(hashInt);
    return final;
}

