#include "SistemaDeVentas.h"

SistemaDeVentas::SistemaDeVentas()
{
	rutaUsuarios = "./Scr/Usuarios.csv";
	rutaProductos = "./Scr/Productos.csv";
	rutaClientes = "./Scr/Clientes.csv";
	rutaPresentaciones = "./Scr/Presentaciones.csv";
	rutaRegimenesFiscales = "./Scr/RegimenesFiscales.csv";
	rutaVentas = "./Scr/Ventas.csv";
	rutaProductosVendidos = "./Scr/ProductosVendidos.csv";
}

SistemaDeVentas::~SistemaDeVentas()
{
}

void SistemaDeVentas::MenuInicial()
{
	// Limpia la pantalla antes de mostrar el menú
	LimpiarPantalla();
	// Variable para almacenar la opción seleccionada por el usuario
	int opcionMI = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del juego
	while (opcionMI != 2) {
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu de Inicio: " << endl
			<< "1. Iniciar Sesion" << endl
			<< "2. Salir del Sistema" << endl
			<< "Opcion: ";
		cin >> opcionMI;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMI)
		{
		case 1:
			// Llama al método MenuPrincipal() para mostrar el menú principal del juego
			IniciarSesion();
			break;
		case 2:
			LimpiarPantalla();
			// Muestra un mensaje de despedida y termina el juego
			cout << "Gracias por jugar" << endl;
			PausaConEnter();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error 
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
		// Limpia la pantalla antes de mostrar el menú nuevamente
		LimpiarPantalla();	
	}
}

void SistemaDeVentas::IniciarSesion()
{
	// Limpia la pantalla antes de mostrar el menú
	LimpiarPantalla();
	ifstream archivoLeido(rutaUsuarios.c_str());
	if (!archivoLeido) {
		ofstream archivo;
		archivo.open(rutaUsuarios.c_str(), fstream::out);
		archivo << "1,admin,admin,admin,admin,admin";
		archivo.close();
		Usuarios auxUsuario = Usuarios("admin", "admin", "admin", "admin", "admin", 1);
		usuarios.push_back(auxUsuario);
	}
	else
	{
		string linea, dato;
		while (getline(archivoLeido, linea))
		{
			string username, password, role, name, lastname;
			int id;
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
			Usuarios auxUsuario = Usuarios(name, lastname, username, password, role, id);
			usuarios.push_back(auxUsuario);
		}
		archivoLeido.close();
	}
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
			if (username == usuarios[i].getUsername() && password == usuarios[i].getPassword())
			{
				bandera = true;
			}
		}
		if (bandera)
		{
			MenuPrincipal();
			contador = 1;
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

void SistemaDeVentas::MenuPrincipal()
{
	// Limpia la pantalla antes de mostrar el menú
	LimpiarPantalla();
	// Variable para almacenar la opción seleccionada por el usuario
	int opcionMP = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del juego
	while (opcionMP != 6) {
	// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu Principal: " << endl
			<< "1. Realizar Venta" << endl
			<< "2. Consultar Ventas" << endl
			<< "3. Consultar Productos" << endl
			<< "4. Consultar Clientes" << endl
			<< "5. Consultar Regimenes Fiscales" << endl
			<< "6. Salir" << endl
			<< "Opcion: ";
		cin >> opcionMP;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMP)
		{
		case 1:
			// Llama al método RealizarVenta() para mostrar el menú de venta
			//RealizarVenta();
			break;
		case 2:
			// Llama al método ConsultarVentas() para mostrar el menú de consulta de ventas
			//ConsultarVentas();
			break;
		case 3:
			// Llama al método ConsultarProductos() para mostrar el menú de consulta de productos
			//ConsultarProductos();
			break;
		case 4:
			// Llama al método ConsultarClientes() para mostrar el menú de consulta de clientes
			//ConsultarClientes();
			break;
		case 5:
			// Llama al método ConsultarRegimenesFiscales() para mostrar el menú de consulta de regimenes fiscales
			//ConsultarRegimenesFiscales();
			break;
		case 6:
			LimpiarPantalla();
			// Muestra un mensaje de despedida y termina el juego
			cout << "Gracias por jugar" << endl;
			PausaConEnter();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error 
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
		// Limpia la pantalla antes de mostrar el menú nuevamente
		LimpiarPantalla();
	}
}

void SistemaDeVentas::PausaConEnter()
{
	// Pausa la ejecución del programa hasta que el usuario presiona Enter
	cin.ignore();
	cin.get();
}

void SistemaDeVentas::LimpiarPantalla()
{
	// Limpia la pantalla de la consola
	system("cls");
}
