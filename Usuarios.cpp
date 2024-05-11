#include "Usuarios.h"

Usuarios::Usuarios(string name, string surname, string username, string password, string role, int id, int shift)
{
    _id = id;
    _password = password;
    _role = role;
    _name = name;
    _lastname = surname;
    //date_joined = chrono::system_clock::now();
    _username = username;
    _shift = shift;
}

Usuarios::~Usuarios()
{
}

void Usuarios::setId(int id_s) {
    _id = id_s;
}
void Usuarios::setUsername(string& username_s) {
    _username = username_s;
}
void Usuarios::setPassword(string& password_s) {
    _password = password_s;
}
void Usuarios::setRole(string& role_s) {
    _role = role_s;
}
void Usuarios::setName(string& name_s) {
    _name = name_s;
}
void Usuarios::setLastname(string& lastname_s) {
    _lastname = lastname_s;
}

void Usuarios::setShift(int shift)
{
    _shift = shift;
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
string Usuarios::getName() {
    return _name;
}
string Usuarios::getLastname() {
    return _lastname;
}

int Usuarios::getShift()
{
    return _shift;
}

string Usuarios::encrypt(string text)
{
    int shift = _shift;
    string encryptedText;
    char ch;
    for (int i = 0; i < text.length(); i++) {
        ch = text[i];
        if (isalpha(ch)) {
            // Convert character to uppercase for easier handling
            ch = toupper(ch);
            // Get the new index by shifting and handling wrap-around
            int newIndex = (ch - 'A' + shift % 26) % 26;
            // Convert back to lowercase if original was lowercase
            ch = (islower(text[i])) ? (newIndex + 'a') : (newIndex + 'A');
        }
        encryptedText += ch;
    }
    return encryptedText;
}

void Usuarios::add_user() {
    cout << "\nYou are about to add a new user:" << endl;
    cout << "Type a username: ";
    cin >> _username;
    cout << "Create a password: ";
    cin >> _password;
    cout << "Assign a role: ";
    cin >> _role;
    cout << "Type the first name of the new user: ";
    cin >> _name;
    cout << "Type the last name od the new user: ";
    cin >> _lastname;
    gen_id(_name, _lastname);

}
void Usuarios::gen_id(string name, string surname) {
    for (int i = 0; i < 3; i++) {
        cout << name[i] << surname[i];
        //Idea para crear el ID, aún faaltaría checar que en la base de datos no haya un ID idéntico
        //Si hay otro id igual se movería a la tercera letra y así hasta que cree uno nuevo (podemos usar recursividad)
    }
}
