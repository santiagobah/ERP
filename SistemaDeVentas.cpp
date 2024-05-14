#include "SistemaDeVentas.h"

SistemaDeVentas::SistemaDeVentas()
{
	rutaUsuarios = "./Scr/Usuarios.csv";
	rutaClientes = "./Scr/Clientes.csv";
	rutaProductos = "./Scr/Productos.csv";
	rutaVentas = "./Scr/Ventas.csv";
	rutaProductosVendidos = "./Scr/ProductosVendidos.csv";
	rutaPresentaciones = "./Scr/Presentaciones.csv";
	rutaRegimenesFiscales = "./Scr/RegimenesFiscales.csv";

}

SistemaDeVentas::~SistemaDeVentas()
{
}

void SistemaDeVentas::MenuInicial()
{
	cout << "Bienvenido al sistema de ventas" << endl;
	cout << "1. Iniciar sesion" << endl;
	cout << "2. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		IniciarSesion();
		break;
	case 2:
		break;
	default:
		LimpiarPantalla();
		cout << "Opcion no valida" << endl;
		PausaConEnter();
		break;
	}
}

void SistemaDeVentas::IniciarSesion()
{
	LimpiarPantalla();
	ifstream archivoLeido(rutaUsuarios.c_str());
	if (!archivoLeido) {
		ofstream archivo;
		archivo.open(rutaUsuarios.c_str(), fstream::out);
		DateTime dateJoined = ConvertirFechaADateTime();
		Usuarios auxUsuario = Usuarios("admin", "admin", "admin", "admin", "admin", 1, dateJoined);
		archivo << "1,admin,admin,admin," << auxUsuario.Encrypt("admin") << ",admin," 
			<< dateJoined.year << "," << dateJoined.month << "," << dateJoined.day << "," << dateJoined.hour << "," 
			<< dateJoined.minute << "," << dateJoined.second << endl;
		archivo.close();
		string password = auxUsuario.Encrypt(auxUsuario.getPassword());
		auxUsuario.setPassword(password);
		usuarios.push_back(auxUsuario);
		archivoLeido.close();
	}
	else
	{
		archivoLeido.close();
		usuarios = LeerUsuarios();
		
	}
	ValidacionDeCredenciales();
}

void SistemaDeVentas::ValidacionDeCredenciales()
{
	int contador = 1;
	bool bandera = false;
	do {
		string username, password;
		cout << "Ingrese su nombre de usuario: ";
		cin >> username;
		cout << "Ingrese su contrase–a: ";
		cin >> password;
		for (int i = 0; i < usuarios.size(); i++)
		{
			if (username == usuarios[i].getUsername() && usuarios[i].Encrypt(password) == usuarios[i].getPassword())
			{
				bandera = true;
			}
		}
		if (bandera)
		{
			MenuPrincipal();
		}
		else
		{
			if (contador == 3)
			{
				exit(1);
			}
			cout << "Usuario o contrase–a incorrectos" << endl;
			PausaConEnter();
			contador++;
		}
	} while (bandera == false);
}

vector<Usuarios> SistemaDeVentas::LeerUsuarios() 
{
	vector<Usuarios> usuarios;
	ifstream archivoLeido(rutaUsuarios.c_str());
	string linea, dato;
	while (getline(archivoLeido, linea))
	{
		string username, password, role, name, lastname;
		int id, year, month, day, hour, minute, second;
		time_t dateJoined;
		vector<string> CargAtrib;
		for (int i = 0; i < linea.size(); i++)
		{
			if (linea[i] == ',')
			{
				CargAtrib.push_back(dato);
				dato = "";
			}
			else
			{
				dato += linea[i];
			}
		}
		CargAtrib.push_back(dato);
		id = stoi(CargAtrib[0]);
		name = CargAtrib[1];
		lastname = CargAtrib[2];
		username = CargAtrib[3];
		password = CargAtrib[4];
		role = CargAtrib[5];
		year = stoi(CargAtrib[6]);
		month = stoi(CargAtrib[7]);
		day = stoi(CargAtrib[8]);
		hour = stoi(CargAtrib[9]);
		minute = stoi(CargAtrib[10]);
		second = stoi(CargAtrib[11]);
		DateTime AuxDateJoined = { year, month, day, hour, minute, second };
		Usuarios auxUsuario = Usuarios(name, lastname, username, password, role, id, AuxDateJoined);
		usuarios.push_back(auxUsuario);
	}
	archivoLeido.close();
	return usuarios;
}

void SistemaDeVentas::MenuPrincipal()
{
	cout << "Menu Principal" << endl;
	cout << "1. Administrador" << endl;
	cout << "2. Vendedor" << endl;
	cout << "3. Recursos Humanos" << endl;
	cout << "4. Almacen" << endl;
	cout << "5. Salir" << endl;
	int opcion;
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		//MenuAdministrador();
		break;
	case 2:
		//MenuVendedor();
		break;
	case 3:
		//MenuRH();
		break;
	case 4:
		//MenuAlmacen();
		break;
	case 5:
		break;
	default:
		LimpiarPantalla();
		cout << "Opcion no valida" << endl;
		PausaConEnter();
		break;
	}
}

DateTime SistemaDeVentas::ConvertirFechaADateTime() 
{
	DateTime dateAux;
	time_t now = time(0);
	tm localTime;
	//localtime_s(&localTime, &now);
	dateAux.year = 1900 + localTime.tm_year;
	dateAux.month = 1 + localTime.tm_mon;
	dateAux.day = localTime.tm_mday;
	dateAux.hour = localTime.tm_hour;
	dateAux.minute = localTime.tm_min;
	dateAux.second = localTime.tm_sec;
	return dateAux;
}

DateTimeV SistemaDeVentas::ConvertirFechaADateTimeV() 
{
	DateTimeV dateAux;
	time_t now = time(0);
	tm localTime;
	//localtime_s(&localTime, &now);
	dateAux.year = 1900 + localTime.tm_year;
	dateAux.month = 1 + localTime.tm_mon;
	dateAux.day = localTime.tm_mday;
	dateAux.hour = localTime.tm_hour;
	dateAux.minute = localTime.tm_min;
	dateAux.second = localTime.tm_sec;
	return dateAux;
}

void SistemaDeVentas::PausaConEnter()
{
	cout << "Presione enter para continuar...";
	cin.ignore();
	cin.get();
}

void SistemaDeVentas::LimpiarPantalla()
{
	system("cls");
}
