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
    GestionDeProductos();
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
void SistemaDeVentas::AgregarProducto(){ //Crear excepciones por si aún no se crea el archivo de productos
    //Hacer que ID vaya creciendo
    productos = SistemaDeVentas::leer_productos(); //Para que inicie el vector ya cargado con los productos que estén ya registrados
    int id_u_actual; //Para hacer ID's consecutivos
    int id_p_actual; //Para hacer ID's consecutivos
    int cant_prod_reg = productos.size();
    id_u_actual = productos[cant_prod_reg].get_id();
    id_p_actual = productos[cant_prod_reg].get_id_presentation();
    ofstream archivo_productos (rutaProductos, ios::app);
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
void SistemaDeVentas::EliminarProducto(){ //crear confirmaciones de delete
    productos = SistemaDeVentas::leer_productos();
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

vector<Productos> SistemaDeVentas::leer_productos(){
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
            else{
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
void SistemaDeVentas::EditarProducto(){ //crear confirmaciones de edit
    cout << "Choose the product which you want to select: " << endl;
    int prod_edit;
    productos = SistemaDeVentas::leer_productos();
    for (int i = 0; i < productos.size(); i++) {
        cout << i+1 << ".- " << productos[i].get_name() << endl;
    }
    cout << "Product to edit: ";
    cin >> prod_edit;
    int var_edit;
    cout << "You are now editing " << productos[prod_edit-1].get_name() << endl;
    cout << "Choose the variable to edit: " << endl;
    cout << "1. Name" << "\n2. Price" << "\n3.Cost" << "\n4. IVA" << "\n5. Stock"<< "\nOption: " << endl;
    cin >> var_edit;
    switch(var_edit)
    {
        case 1:
        {
            string new_name;
            cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
            productos[prod_edit-1].set_name(new_name);
            break;
        }
        case 2:
        {
            float new_price;
            cout << "Type the new price for " << productos[prod_edit-1].get_name() << ": "; cin >> new_price;
            productos[prod_edit-1].set_price(new_price);
            break;
        }
        case 3:
        {
            float new_cost;
            cout << "Type the new cost for " << productos[prod_edit-1].get_name() << ": "; cin >> new_cost;
            productos[prod_edit-1].set_cost(new_cost);
            break;
        }
        case 4:
        {
            bool set_iva;
            cout << "Type the new IVA option: "; cin >> set_iva;
            productos[prod_edit-1].set_has_iva(set_iva);
            break;
        }
        case 5:
        {
            int new_stock;
            cout << "Type the new stock for " << productos[prod_edit-1].get_name() << ": "; cin >> new_stock;
            productos[prod_edit-1].set_stock(new_stock);
            break;
        }
    }
}
void SistemaDeVentas::VerProductos(){
    productos = SistemaDeVentas::leer_productos();
    vector <Productos> aux_ord_prod;
    aux_ord_prod = productos;
    int sort_filter;
    cout << "1. Sort products" << "\n2. Filter products" << "\nOption: " << endl; cin >> sort_filter;
    switch(sort_filter){
        case 1:
        {
            int sort_opc;
            cout << "\nSort by: " << "\n1. Stock" << "\n2. ID" << "\n3. Price: Low to High" << "\n4.Price: High to Low" << "\n5. Cost" << "\nOption: "; cin >> sort_opc;
            switch(sort_opc){
                case 1:
                {
                    //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
                    //***************************************************HECHO CON IA: (IDK IF IT WORKS)
                    sort(aux_ord_prod.begin(), aux_ord_prod.end(), []( Productos &a,  Productos &b) {return a.get_stock() < b.get_stock();});
                    //*************************************************************
                    
                    for (int i = 0; i < productos.size(); i++) {
                        cout << i+1 << ".- " << aux_ord_prod[i].get_name() << ". Stock: " << aux_ord_prod[i].get_stock() << endl;
                    }
                    break;
                }
                case 2:
                {
                    //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
                    //***************************************************HECHO CON IA: (IDK IF IT WORKS)
                    sort(aux_ord_prod.begin(), aux_ord_prod.end(), []( Productos &a,  Productos &b) {return a.get_id() < b.get_id();});
                    //*************************************************************
                    
                    for (int i = 0; i < productos.size(); i++) {
                        cout << i+1 << ".- " << aux_ord_prod[i].get_name() << ". ID: " << aux_ord_prod[i].get_id() << endl;
                    }
                    break;
                }
                case 3:
                {   //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
                    //***************************************************HECHO CON IA: (IDK IF IT WORKS)
                    sort(aux_ord_prod.begin(), aux_ord_prod.end(), []( Productos &a,  Productos &b) {return a.get_price() < b.get_price();});
                    //*************************************************************
                    
                    for (int i = 0; i < productos.size(); i++) {
                        cout << i+1 << ".- " << aux_ord_prod[i].get_name() << ". Price: " << aux_ord_prod[i].get_price() << endl;
                    }
                    break;
                }
                case 4:
                {
                    //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
                    //***************************************************HECHO CON IA: (IDK IF IT WORKS)
                    sort(aux_ord_prod.begin(), aux_ord_prod.end(), []( Productos &a,  Productos &b) {return a.get_price() < b.get_price();});
                    //*************************************************************
                    int max_prod = productos.size();
                    for (int i = max_prod; i < 0; i--) {
                        cout << i+1 << ".- " << aux_ord_prod[max_prod].get_name() << ". Price: " << aux_ord_prod[i].get_price() << endl;
                    }
                    
                    break;
                }
                case 5:
                {
                    //Ocuparemos un vector auxiliar en el que filtraremos y ese será el que se mostrará
                        //***************************************************HECHO CON IA: (IDK IF IT WORKS)
                        sort(aux_ord_prod.begin(), aux_ord_prod.end(), []( Productos &a,  Productos &b) {return a.get_cost() < b.get_cost();});
                        //*************************************************************
                        
                        for (int i = 0; i < productos.size(); i++) {
                            cout << i+1 << ".- " << aux_ord_prod[i].get_name() << ". Cost: " << aux_ord_prod[i].get_cost() << endl;
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
