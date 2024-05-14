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

SistemaDeVentas::~SistemaDeVentas(){
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

void SistemaDeVentas::EditarProducto(){
}
void SistemaDeVentas::VerProductos(){
}
void SistemaDeVentas::EliminarProducto(){
}
void SistemaDeVentas::GestionDeProductos(){
    cout << "\nBienvenido al menú de Productos" << endl;
    int opc_men_pod = 0;
    do {
        cout <<
        "1. Add Products" <<
        "\n2. Edit Products" <<
        "\n3. See Products" << //SEE?
        "\n4. Delete Products" <<
        "\n5. Return" <<
        "\nOpción elegida: ";
        cin >> opc_men_pod;
        switch(opc_men_pod){
            case 1:
            {
                SistemaDeVentas::AgregarProducto();
                break;
            }
            case 2:
            {
                SistemaDeVentas::EditarProducto();
                break;
            }
            case 3:
            {
                SistemaDeVentas::VerProductos();
                break;
            }
            case 4:
            {
                SistemaDeVentas::EliminarProducto();
                break;
            }
            case 5:
            {
                break;
            }
            default:
            {
                cout << "Seleccione una opción válida" << endl;
                SistemaDeVentas::GestionDeProductos();
                break;
            }
        }


    } while (opc_men_pod != 5);
}
void SistemaDeVentas::AgregarProducto(){
    //Hacer que ID vaya creciendo
    ofstream archivo_productos (rutaProductos, ios::app);
    int id = 1;
    string upc, name;
    int id_presentation = 1;
    float price, cost;
    bool has_iva;
    int stock;
    cout << "\nScan the barcode of the product: ";
    cin >> upc; archivo_productos << upc;
    cout << "Type name for the product: ";
    cin >> name; archivo_productos << name;
    cout << "\nThe unique ID for " << name << "is going to be: " << id << endl; archivo_productos << id;
    cout << "The  ID for this " << name << "presentation is going to be: " << id_presentation << endl; archivo_productos << id_presentation;
    cout << "\nType the price for " << name << ": ";
    cin >> price; archivo_productos << price;
    cout << "Type the cost for " << name << ": ";
    cin >> cost; archivo_productos << cost;
    //Implementar un switch para el IVA
    cout << name << " has IVA? (1. YES/ 0.NO): ";
    cin >> has_iva; archivo_productos << has_iva;
    cout << "How many " << name << " are available right now? ";
    cin >> stock; archivo_productos << stock;
    Productos NuevoProducto(id, upc, name, id_presentation, price, cost, has_iva, stock);
    productos.push_back(NuevoProducto);
    archivo_productos.close();
}
