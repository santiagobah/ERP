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
	usuarioActual = nullptr;
}

SistemaDeVentas::~SistemaDeVentas()
{
	delete usuarioActual;
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
			// Llama al método MenuPrincipal() para mostrar el menú principal del Sistema
			IniciarSesion();
			break;
		case 2:
			LimpiarPantalla();
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
	LimpiarPantalla();
	ifstream archivoLeido(rutaUsuarios.c_str());
	if (!archivoLeido) {
		ofstream archivo;
		archivo.open(rutaUsuarios.c_str(), fstream::out);
		DateTime dateJoined = ConvertirFechaADateTime();
		Usuarios auxUsuario = Usuarios("Admin", "Admin", "admin", "admin", "Admin", 1, dateJoined);
		archivo << "1,admin,admin,admin," << auxUsuario.Encrypt("admin") << ",Admin," 
			<< dateJoined.year << "," << dateJoined.month << "," << dateJoined.day << ","
			<< dateJoined.hour << "," << dateJoined.minute << "," << dateJoined.second << endl;
		archivo.close();
		string password = auxUsuario.Encrypt(auxUsuario.getPassword());
		auxUsuario.setPassword(password);
		usuarioActual = new Usuarios(auxUsuario.getName(), auxUsuario.getLastname(), auxUsuario.getUsername(), auxUsuario.getPassword(), auxUsuario.getRole(), auxUsuario.getId(), auxUsuario.getDateJoined());
		usuarios.push_back(auxUsuario);
	}
	else
	{
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
				usuarioActual = new Usuarios(usuarios[i].getName(), usuarios[i].getLastname(), usuarios[i].getUsername(), usuarios[i].getPassword(), usuarios[i].getRole(), usuarios[i].getId(), usuarios[i].getDateJoined());
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
	ifstream archivoLeido(rutaUsuarios.c_str());
	vector<Usuarios> usuarios1;
	string linea;
	while (getline(archivoLeido, linea))
	{
		string username, password, role, name, lastname;
		int id;
		DateTime dateJoined;
		vector<string> CargAtrib;
		string dato;
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
		int year = stoi(CargAtrib[6]);
		int month = stoi(CargAtrib[7]);
		int day = stoi(CargAtrib[8]);
		int hour = stoi(CargAtrib[9]);
		int minute = stoi(CargAtrib[10]);
		int second = stoi(CargAtrib[11]);
		dateJoined = DateTime{ year, month, day, hour, minute, second };
		Usuarios auxUsuario = Usuarios(name, lastname, username, password, role, id, dateJoined);
		auxUsuario.setId(id);
		usuarios1.push_back(auxUsuario);
	}
	archivoLeido.close();
	return usuarios1;
}

vector<Productos> SistemaDeVentas::LeerProductos()
{
	vector<Productos> productos;
	ifstream lectura_archivo(rutaProductos.c_str());
	string linea, parte;
	while (getline(lectura_archivo, linea)) {
		string upc, name;
		int id_u, id_p, stock, has_iva;
		float price, cost;
		vector <string> carga_productos;
		for (int i = 0; i < linea.size(); i++) {
			if (linea[i] == ',') {
				carga_productos.push_back(parte);
				parte = "";
			}
			else {
				parte += linea[i];
			}
		}
		carga_productos.push_back(parte);
		upc = carga_productos[0];
		name = carga_productos[1];
		id_u = stoi(carga_productos[2]);
		id_p = stoi(carga_productos[3]);
		stock = stoi(carga_productos[4]);
		has_iva = stoi(carga_productos[5]);
		price = stof(carga_productos[6]);
		cost = stof(carga_productos[7]);
		Productos guardado_productos = Productos(id_u, upc, name, id_p, price, cost, has_iva, stock);
		productos.push_back(guardado_productos);
	}
	return productos;
}

void SistemaDeVentas::MenuPrincipal()
{
	switch (usuarioActual->getRoleInt())
	{
	case ADMIN:
		MenuAdministrador();
		break;
	case VENDEDOR:
		MenuVendedor();
		break;
	case RH:
		MenuRH();
		break;
	case ALMACEN:
		MenuAlmacen();
		break;
	default:
		break;
	}
}

void SistemaDeVentas::MenuAdministrador()
{
	// Variable para almacenar la opción seleccionada por el usuario
	int opcionMA = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del juego
	while (opcionMA != 6) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout << "Menu de Administrador: " << endl
			<< "1. Gestion de Usuarios" << endl
			<< "2. Gestion de Clientes" << endl
			<< "3. Gestion de Productos" << endl
			<< "4. Gestion de Ventas" << endl
			<< "5. Gestion de Informes" << endl
			<< "6. Salir" << endl
			<< "Opcion: ";
		cin >> opcionMA;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMA)
		{
		case 1:
			// Llama al método GestionDeUsuarios
			GestionDeUsuarios();
			break;
		case 2:
			// Llama al método GestionDeClientes
			//GestionDeClientes();
			break;
		case 3:
			// Llama al método GestionDeProductos
			GestionDeProductos();
			break;
		case 4:
			// Llama al método GestionDeVentas
			//GestionDeVentas();
			break;
		case 5:
			// Llama al método GestionDeInformes
			//GestionDeInformes();
			break;
		case 6:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error 
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
			cout << "Selecciona una de las opciones validas" << endl;
			PausaConEnter();
			break;
		}
	}
}

void SistemaDeVentas::MenuVendedor()
{
}

void SistemaDeVentas::MenuRH()
{
}

void SistemaDeVentas::MenuAlmacen()
{
}

void SistemaDeVentas::GestionDeUsuarios()
{
	// Variable para almacenar la opción seleccionada por el usuario
	int opcionGU = 0;
	do {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		cout << "\nBienvenido al menú de Usuarios" << endl;
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout <<
			"1. Add Users" <<
			"\n2. Edit Users" <<
			"\n3. Delete Users" <<
			"\n4. Return" <<
			"\nOpción elegida: ";
		cin >> opcionGU;
		switch (opcionGU) {
		case 1:
		{
			AgregarUsuario();
			break;
		}
		case 2:
		{
			EditarUsuario();
			break;
		}
		case 3:
		{
			EliminarUsuario();
			break;
		}
		case 4:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGU != 4);
}

void SistemaDeVentas::AgregarUsuario()
{
	usuarios = LeerUsuarios();
	string name, surname, username, password, role;
	int id = 0;
	DateTime dateJoined = ConvertirFechaADateTime();
	cout << "\nType the name of the user: ";
	cin >> name;
	cout << "Type the surname of the user: ";
	cin.ignore();
	getline(cin, surname);
	cout << "Type the username of the user: ";
	cin >> username;
	cout << "Type the password of the user: ";
	cin >> password;
	while (id < 1 || id > 4) {
		cout << "Select the role of the user: " << endl
			<< "1. Admin" << endl 
			<< "2. Vendedor" << endl 
			<< "3. RH" << endl 
			<< "4. Almacen" << endl
			<< "Option: ";
		cin >> id;
		switch (id)
		{
			case 1:
				role = "Admin";
				break;
			case 2:
				role = "Vendedor";
				break;
			case 3:
				role = "RH";
				break;
			case 4:
				role = "Almacen";
				break;
		}
	}
	id = usuarios[usuarios.size() - 1].getId() + 1; //Para que el ID vaya creciendo
	Usuarios NuevoUsuario = Usuarios(name, surname, username, password, role, id, dateJoined);
	NuevoUsuario.setPassword(NuevoUsuario.Encrypt(password));
	usuarios.push_back(NuevoUsuario);
	ofstream archivo;
	archivo.open(rutaUsuarios.c_str(), fstream::out);
	for (int i = 0; i < usuarios.size(); i++) {
		archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << "," << usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << "," << usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month << "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour << "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second << endl;
	}
	archivo.close();
	

}

void SistemaDeVentas::EditarUsuario()
{
	usuarios = LeerUsuarios();
	cout << "Choose the user which you want to select: " << endl;
	int user_edit;
	for (int i = 0; i < usuarios.size(); i++) {
		cout << i + 1 << ".- " << usuarios[i].getName() << " " << usuarios[i].getLastname() << " (" << usuarios[i].getRole() << ") " << endl;
	}
	cout << "User to edit: ";
	cin >> user_edit;
	int var_edit;
	cout << "You are now editing " << usuarios[user_edit - 1].getName() << " " << usuarios[user_edit - 1].getLastname() << " (" << usuarios[user_edit - 1].getRole() << ") " << endl;
	cout << "Choose the variable to edit: " << endl;
	cout << "1. Name" 
		<< "\n2. Lastname" 
		<< "\n3. Username" 
		<< "\n4. Password" 
		<< "\n5. Role" 
		<< "\nOption: "; 
	cin >> var_edit;
	switch (var_edit)
	{
	case 1:
	{
		string new_name;
		cout << "Type the new name: "; 
		cin.ignore(); 
		getline(cin, new_name);
		usuarios[user_edit - 1].setName(new_name);
		break;
	}
	case 2:
	{
		string new_lastname;
		cout << "Type the new lastname: "; 
		cin.ignore(); 
		getline(cin, new_lastname);
		usuarios[user_edit - 1].setLastname(new_lastname);
		break;
	}
	case 3:
	{
		string new_username;
		cout << "Type the new username: "; 
		cin >> new_username;
		usuarios[user_edit - 1].setUsername(new_username);
		break;
	}
	case 4:
	{
		string new_password;
		cout << "Type the new password: "; 
		cin >> new_password;
		usuarios[user_edit - 1].setPassword(usuarios[user_edit - 1].Encrypt(new_password));
		break;
	}
	case 5:
	{
		string new_role;
		int opc_role = 0;
		while (opc_role < 1 || opc_role > 4) {
			cout << "Select the role of the user: " << endl
				<< "1. Admin" << endl
				<< "2. Vendedor" << endl
				<< "3. RH" << endl
				<< " 4. Almacen" << endl
				<< "Option: ";
			cin >> opc_role;
			switch (opc_role)
			{
				case 1:
					new_role = "Admin";
					break;
				case 2:
					new_role = "Vendedor";
					break;
				case 3:
					new_role = "RH";
					break;
				case 4:
					new_role = "Almacen";
					break;
			}
		}
		usuarios[user_edit - 1].setRole(new_role);
		break;
	}
	}
	ofstream archivo;
	archivo.open(rutaUsuarios.c_str(), fstream::out);
	for (int i = 0; i < usuarios.size(); i++) {
		archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << "," << usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << "," << usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month << "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour << "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second << endl;
	}
	archivo.close();
}

void SistemaDeVentas::EliminarUsuario()
{
	usuarios = LeerUsuarios();
	string username;
	int id_user = 0;
	for (int i = 0; i < usuarios.size(); i++) {
		cout << i + 1 << ".- " << usuarios[i].getName() << " " << usuarios[i].getLastname() << " (" << usuarios[i].getRole() << ") " << endl;
	}
	cout << "Type the username of the user to delete: ";
	cin >> id_user;
	//confirmar si se quiere eliminar
	int opc_del;
	cout << "Are you sure you want to delete this user? " << endl
		<< "Data: " << usuarios[id_user - 1].getName() << " " << usuarios[id_user - 1].getLastname() << " (" << usuarios[id_user - 1].getRole() << ") " << endl
		<< "1. YES" << endl
		<< "2. NO" << endl
		<< "Option: ";
	cin >> opc_del;
	if (opc_del == 1) {

		usuarios.erase(usuarios.begin() + id_user - 1);
		ofstream archivo;
		archivo.open(rutaUsuarios.c_str(), fstream::out);
		for (int i = 0; i < usuarios.size(); i++) {
			archivo << usuarios[i].getId() << "," << usuarios[i].getName() << "," << usuarios[i].getLastname() << "," 
				<< usuarios[i].getUsername() << "," << usuarios[i].getPassword() << "," << usuarios[i].getRole() << "," 
				<< usuarios[i].getDateJoined().year << "," << usuarios[i].getDateJoined().month 
				<< "," << usuarios[i].getDateJoined().day << "," << usuarios[i].getDateJoined().hour 
				<< "," << usuarios[i].getDateJoined().minute << "," << usuarios[i].getDateJoined().second 
				<< endl;
		}
		archivo.close();
	}

}

void SistemaDeVentas::GestionDeProductos()
{
	// Variable para almacenar la opción seleccionada por el usuario
	int opc_men_pod = 0;
	do {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		cout << "\nBienvenido al menú de Productos" << endl;
		// Muestra las opciones del menú y solicita la entrada del usuario
		cout <<
			"1. Add Products" <<
			"\n2. Edit Products" <<
			"\n3. See Products" << //SEE?
			"\n4. Delete Products" <<
			"\n5. Return" <<
			"\nOpción elegida: ";
		cin >> opc_men_pod;
		switch (opc_men_pod) {
		case 1:
		{
			AgregarProducto();
			break;
		}
		case 2:
		{
			EditarProducto();
			break;
		}
		case 3:
		{
			VerProductos();
			break;
		}
		case 4:
		{
			EliminarProducto();
			break;
		}
		case 5:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
			cout << "Seleccione una opción válida" << endl;
			PausaConEnter();
			break;
		}
		}


	} while (opc_men_pod != 5);
}

void SistemaDeVentas::AgregarProducto()
{
	//Crear excepciones por si aún no se crea el archivo de productos
	//Hacer que ID vaya creciendo
	productos = LeerProductos(); //Para que inicie el vector ya cargado con los productos que estén ya registrados
	int id_u_actual; //Para hacer ID's consecutivos
	int id_p_actual; //Para hacer ID's consecutivos
	int cant_prod_reg = productos.size();
	id_u_actual = productos[cant_prod_reg].get_id();
	id_p_actual = productos[cant_prod_reg].get_id_presentation();
	ofstream archivo_productos(rutaProductos, ios::app);
	string upc, name;
	float price, cost;
	bool has_iva;
	int stock;
	cout << "\nScan the barcode of the product: ";
	cin >> upc; archivo_productos << upc << ";";
	cout << "Type name for the product: ";
	cin >> name; archivo_productos << name << ",";
	cout << "\nThe unique ID for " << name << "is going to be: " << id_u_actual++ << endl; archivo_productos << id_u_actual++ << ",";
	cout << "The  ID for this " << name << "presentation is going to be: " << id_p_actual++ << endl; archivo_productos << id_p_actual++ << ",";
	cout << "\nType the price for " << name << ": ";
	cin >> price; archivo_productos << price << ",";
	cout << "Type the cost for " << name << ": ";
	cin >> cost; archivo_productos << cost << ",";
	//Implementar un switch para el IVA
	cout << name << " has IVA? (1. YES/ 0.NO): "; //implementar método que sea un switch para 1.yes, 2.no
	cin >> has_iva; archivo_productos << has_iva << ",";
	cout << "How many " << name << " are available right now? ";
	cin >> stock; archivo_productos << stock << ",";
	Productos NuevoProducto(id_u_actual, upc, name, id_p_actual, price, cost, has_iva, stock);
	productos.push_back(NuevoProducto);
	archivo_productos.close();
}

void SistemaDeVentas::EditarProducto()
{
	cout << "Choose the product which you want to select: " << endl;
	int prod_edit;
	productos = SistemaDeVentas::LeerProductos();
	for (int i = 0; i < productos.size(); i++) {
		cout << i + 1 << ".- " << productos[i].get_name() << endl;
	}
	cout << "Product to edit: ";
	cin >> prod_edit;
	int var_edit;
	cout << "You are now editing " << productos[prod_edit - 1].get_name() << endl;
	cout << "Choose the variable to edit: " << endl;
	cout << "1. Name" << "\n2. Price" << "\n3.Cost" << "\n4. IVA" << "\n5. Stock" << "\nOption: " << endl;
	cin >> var_edit;
	switch (var_edit)
	{
	case 1:
	{
		string new_name;
		cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
		productos[prod_edit - 1].set_name(new_name);
		break;
	}
	case 2:
	{
		float new_price;
		cout << "Type the new price for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_price;
		productos[prod_edit - 1].set_price(new_price);
		break;
	}
	case 3:
	{
		float new_cost;
		cout << "Type the new cost for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_cost;
		productos[prod_edit - 1].set_cost(new_cost);
		break;
	}
	case 4:
	{
		bool set_iva;
		cout << "Type the new IVA option: "; cin >> set_iva;
		productos[prod_edit - 1].set_has_iva(set_iva);
		break;
	}
	case 5:
	{
		int new_stock;
		cout << "Type the new stock for " << productos[prod_edit - 1].get_name() << ": "; cin >> new_stock;
		productos[prod_edit - 1].set_stock(new_stock);
		break;
	}
	}
}

void SistemaDeVentas::VerProductos()
{
	productos = SistemaDeVentas::LeerProductos();
	vector <Productos> aux_ord_prod;
	aux_ord_prod = productos;
	int sort_filter;
	cout << "1. Sort products" << "\n2. Filter products" << "\nOption: " << endl; cin >> sort_filter;
	switch (sort_filter) {
	case 1:
	{
		int sort_opc;
		cout << "\nSort by: " << "\n1. Stock" << "\n2. ID" << "\n3. Price: Low to High" << "\n4.Price: High to Low" << "\n5. Cost" << "\nOption: "; cin >> sort_opc;
		switch (sort_opc) {
		case 1:
		{
			//Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
			//***************************************************HECHO CON IA: (IDK IF IT WORKS)
			//sort(aux_ord_prod.begin(), aux_ord_prod.end(), [](Productos& a, Productos& b) {return a.get_stock() < b.get_stock(); });
			//*************************************************************

				for (int i = 0; i < productos.size(); i++) {
					cout << i + 1 << ".- " << aux_ord_prod[i].get_name() << ". Stock: " << aux_ord_prod[i].get_stock() << endl;
				}
				break;
			}
			case 2:
			{
				//Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
				//***************************************************HECHO CON IA: (IDK IF IT WORKS)
				//sort(aux_ord_prod.begin(), aux_ord_prod.end(), [](Productos& a, Productos& b) {return a.get_id() < b.get_id(); });
				//*************************************************************

				for (int i = 0; i < productos.size(); i++) {
					cout << i + 1 << ".- " << aux_ord_prod[i].get_name() << ". ID: " << aux_ord_prod[i].get_id() << endl;
				}
				break;
			}
			case 3:
			{   //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
				//***************************************************HECHO CON IA: (IDK IF IT WORKS)
				//sort(aux_ord_prod.begin(), aux_ord_prod.end(), [](Productos& a, Productos& b) {return a.get_price() < b.get_price(); });
				//*************************************************************

				for (int i = 0; i < productos.size(); i++) {
					cout << i + 1 << ".- " << aux_ord_prod[i].get_name() << ". Price: " << aux_ord_prod[i].get_price() << endl;
				}
				break;
			}
			case 4:
			{
				//Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
				//***************************************************HECHO CON IA: (IDK IF IT WORKS)
				//sort(aux_ord_prod.begin(), aux_ord_prod.end(), [](Productos& a, Productos& b) {return a.get_price() < b.get_price(); });
				//*************************************************************
				int max_prod = productos.size();
				for (int i = max_prod; i < 0; i--) {
					cout << i + 1 << ".- " << aux_ord_prod[max_prod].get_name() << ". Price: " << aux_ord_prod[i].get_price() << endl;
				}

				break;
			}
			case 5:
			{
				//Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
					//***************************************************HECHO CON IA: (IDK IF IT WORKS)
				//sort(aux_ord_prod.begin(), aux_ord_prod.end(), [](Productos& a, Productos& b) {return a.get_cost() < b.get_cost(); });
				//*************************************************************

				for (int i = 0; i < productos.size(); i++) {
					cout << i + 1 << ".- " << aux_ord_prod[i].get_name() << ". Cost: " << aux_ord_prod[i].get_cost() << endl;
				}
				break;
			}
			}
			break;
		}
		case 2:
		{
			break;
		}
	}
}

void SistemaDeVentas::EliminarProducto()
{
	productos = LeerProductos();
	string upc;
	int band_prod = 0;
	cout << "\nScan the barcode of the product which you want to delete: ";
	cin >> upc;
	for (int i = 0; i < productos.size(); i++) {
		if (upc == productos[i].get_UPC()) {
			cout << productos[i].get_name() << "eliminado exitosamente" << endl;
			productos.erase(productos.begin() + i);
			band_prod = 1;
			break;
		}
	}
	if (band_prod == 0) {
		cout << "El artículo no fue encontrado" << endl;
	}
	ofstream archivo_productos(rutaProductos);
}


DateTime SistemaDeVentas::ConvertirFechaADateTime()
{
	DateTime dateAux;
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
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
	// Pausa la ejecución del programa hasta que el usuario presiona Enter
	cin.ignore();
	cin.get();
}

void SistemaDeVentas::LimpiarPantalla()
{
	// Limpia la pantalla de la consola
	system("cls");
}