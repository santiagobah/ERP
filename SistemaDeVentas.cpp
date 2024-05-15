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
    //GestionDeProductos();
    GestionDeClientes();
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
    id_u_actual = productos[cant_prod_reg-1].get_id();
    id_p_actual = productos[cant_prod_reg-1].get_id_presentation();
    ofstream archivo_productos (rutaProductos, ios::app);
    string upc, name;
    float price, cost;
    bool has_iva;
    int stock;
    cout << "\nScan the barcode of the product: ";
    cin >> upc; archivo_productos << "\n"+ upc << ",";
    cout << "Type name for the product: ";
    cin >> name; archivo_productos << name << ",";
    cout << "\nThe unique ID for " << name << " is going to be: " << id_u_actual + 1 << endl; archivo_productos << id_u_actual + 1 << ",";
    cout << "The  ID for this " << name << " presentation is going to be: " << id_p_actual + 1 << endl; archivo_productos << id_p_actual + 1 << ",";
    cout << "\nType the price for " << name << ": ";
    cin >> price; archivo_productos << price << ",";
    cout << "Type the cost for " << name << ": ";
    cin >> cost; archivo_productos << cost << ",";
    //Implementar un switch para el IVA
    cout << name << " has IVA? (1. YES/ 0.NO): "; //implementar método que sea un switch para 1.yes, 2.no
    cin >> has_iva; archivo_productos << has_iva << ",";
    cout << "How many " << name << " are available right now? ";
    cin >> stock; archivo_productos << stock;
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
            cout << productos[i].get_name() << " eliminado exitosamente" << endl;
            productos.erase(productos.begin() + i);
            band_prod = 1;
            break;
        }
    }
    if (band_prod == 0) {
        cout << "El artículo no fue encontrado" << endl;
    }
    Actualizar_Productos();
}

vector<Productos> SistemaDeVentas::leer_productos(){
    vector<Productos> productos1;
    ifstream lectura_archivo(rutaProductos.c_str());
    string linea;
    while (getline(lectura_archivo, linea)) {
        string upc, name;
        int id_u, id_p, stock, has_iva;
        float price, cost;
        vector <string> carga_productos;
        string parte;
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
        price = stof(carga_productos[4]);
        cost = stof(carga_productos[5]);
        has_iva = stoi(carga_productos[6]);
        stock = stoi(carga_productos[7]);
        Productos guardado_productos = Productos(id_u, upc, name, id_p, price, cost, has_iva, stock);
        guardado_productos.set_id(id_u);
        guardado_productos.set_UPC(upc);
        guardado_productos.set_name(name);
        guardado_productos.set_id_presentation(id_p);
        guardado_productos.set_price(price);
        guardado_productos.set_cost(cost);
        guardado_productos.set_has_iva(has_iva);
        guardado_productos.set_stock(stock);
        productos1.push_back(guardado_productos);
    }
    return productos1;
}
void SistemaDeVentas::EditarProducto(){ //crear confirmaciones de edit
    cout << "Choose the product which you want to edit: " << endl;
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
    cout << "1. Name" << "\n2. Price" << "\n3.Cost" << "\n4. IVA" << "\n5. Stock"<< "\nOption: ";
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
    Actualizar_Productos(); //Actualiza los cambios que se hayan realizado al momento del edit
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
                    
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
                case 4:
                {
                    break;
                }
                case 5:
                {
                    break;
                }
            }
            break;
        }
        case 2:
        {
            int opc_fil;
            cout << "\nFilter by: " << "\n1. Name" << "\n2. ID" << "\n3. UPC" << "\nOption: "; cin >> opc_fil;
            switch(opc_fil){
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
            }
            break;
        }
    }
}
void SistemaDeVentas::Actualizar_Productos(){
    ofstream archivo_p(rutaProductos);
    for (int i = 0; i < productos.size(); i++) {
        archivo_p << productos[i].get_UPC() << "," << productos[i].get_name() << "," << productos[i].get_id() << "," << productos[i].get_id_presentation() << "," << productos[i].get_price() << "," << productos[i].get_cost() << "," << productos[i].get_has_iva() << "," << productos[i].get_stock() << endl;
    }
    archivo_p.close();
}

//Propuesta para ordenación de vector:
//#include <algorithm> // Para la función sort
//#include <functional> // Para std::greater y std::less
//#include <iostream>
//#include <vector>
//#include "Productos.h" // Asumiendo que tienes una definición de la clase Productos
//
//using namespace std;
//
//// Definición de la función para ordenar el vector por un atributo específico
//void SistemaDeVentas::OrdenarProductosPorAtributo(int atributo) {
//    switch (atributo) {
//        case 1: // Ordenar por stock
//            sort(productos.begin(), productos.end(), [](const Productos& a, const Productos& b) {
//                return a.get_stock() < b.get_stock(); // Orden ascendente
//            });
//            break;
//        case 2: // Ordenar por precio
//            sort(productos.begin(), productos.end(), [](const Productos& a, const Productos& b) {
//                return a.get_price() < b.get_price(); // Orden ascendente
//            });
//            break;
//        // Puedes agregar más casos para otros atributos como nombre, etc.
//        default:
//            cout << "Atributo no válido." << endl;
//            break;
//    }
//}
//
//int main() {
//    // Suponiendo que ya tienes el vector productos lleno con objetos de la clase Productos
//    // Aquí deberías llamar a la función OrdenarProductosPorAtributo con el atributo deseado
//
//    // Ordenar por stock (atributo 1)
//    OrdenarProductosPorAtributo(1);
//
//    // Luego puedes imprimir el vector ordenado o hacer lo que necesites con él
//    for (const auto& producto : productos) {
//        // Imprimir cada producto ordenado por stock
//        cout << "Nombre: " << producto.get_name() << ", Stock: " << producto.get_stock() << endl;
//    }
//
//    return 0;
//}

void SistemaDeVentas::GestionDeClientes(){
    int opc_cli;
    do {
        cout << "\nBienvenido al Menú de Clientes: " << "\n1. Add Client" << "\n2. Edit Client" << "\n3. See Clients" << "\n4. Delete Client" << "\n5.Return" << "\nOption: "; cin >> opc_cli;
        switch(opc_cli){
            case 1:
            {
                AgregarCliente();
                break;
            }
            case 2:
            {
                EditarCliente();
                break;
            }
            case 3:
            {
                VerClientes();
                break;
            }
            case 4:
            {
                EliminarCliente();
                break;
            }
            case 5:
            {
                break;
            }
        }
    } while (opc_cli != 5);
}
void SistemaDeVentas::AgregarCliente(){ //Corregir con cin.ignore()
    clientes = leer_clientes();
    int actual_id_cliente = 0;
    string name, rfc, address, city, state, zipcode;
    int id_c, reg_fis_id;
    ofstream archivo_clientes(rutaClientes, ios::app);
    cout << "\nType the client´s name: "; cin >> name; archivo_clientes << "\n" << name << ",";
    cout << "Type the rfc of " << name << ": "; cin >> rfc; archivo_clientes << rfc << ",";
    cout << "Type the address of " << name << ": "; cin >> address; archivo_clientes << address << ",";
    cout << "Type the city where " << name << " lives: "; cin >> city; archivo_clientes << city << ",";
    cout << "Type the state where " << name << " lives: "; cin >> state; archivo_clientes << state << ",";
    cout << "Type the zipcode where " << address << " is located: "; cin >> zipcode; archivo_clientes << zipcode << ",";
    cout << "Type the ID for the 'fiscal register' of " << name << ": "; cin >> reg_fis_id; archivo_clientes << reg_fis_id << ",";
    cout << "The assigned id for " << name << " is " << actual_id_cliente; archivo_clientes << actual_id_cliente;
    Clientes nuevoCliente = Clientes(actual_id_cliente, name, rfc, reg_fis_id, address, city, state, zipcode);
    clientes.push_back(nuevoCliente);
    archivo_clientes.close();
}
void SistemaDeVentas::EditarCliente(){
    clientes = SistemaDeVentas::leer_clientes();
    int opc_cli_edit;
    cout << "Choose the client which information you would like to edit: " << endl;
    for (int i  = 0; i < clientes.size(); i++) {
        cout << i+1 << ".- " << clientes[i].getName() << endl;
    }
    cout << "Client to edit: "; cin >> opc_cli_edit;
    int var_edit;
    cout << "You are now editing " << clientes[opc_cli_edit-1].getName() << "'s data. " << "\nChoose the variable to edit: ";
    cout << "\n1. Name" << "\n2. RFC" << "\n3. Address" << "\n4. City" << "\n5. State" << "\n6. Zipcode" << "\n7. Fiscal Regimen" << "\nOption: ";  cin >> var_edit;
    switch(var_edit){
        case 1:
        {
            string new_name;
            cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
            clientes[opc_cli_edit-1].setName(new_name);
            break;
        }
        case 2:
        {
            string new_rfc;
            cout << "Type the new RFC of " << clientes[opc_cli_edit-1].getName() << ": "; cin.ignore(); getline(cin, new_rfc);
            clientes[opc_cli_edit-1].setRFC(new_rfc);
            break;
        }
        case 3:
        {
            string new_address;
            cout << "Type the new address of " << clientes[opc_cli_edit-1].getName() << ": "; cin.ignore(); getline(cin, new_address);
            clientes[opc_cli_edit-1].setAddress(new_address);
            break;
        }
        case 4:
        {
            string new_city;
            cout << "Type the new city of " << clientes[opc_cli_edit-1].getName() << ": "; cin.ignore(); getline(cin, new_city);
            clientes[opc_cli_edit-1].setCity(new_city);
            break;
        }
        case 5:
        {
            string new_state;
            cout << "Type the new state of " << clientes[opc_cli_edit-1].getName() << ": "; cin.ignore(); getline(cin, new_state);
            clientes[opc_cli_edit-1].setState(new_state);
            break;
        }
        case 6:
        {
            string new_zipcode;
            cout << "Type the new zipcode of " << clientes[opc_cli_edit-1].getName() << ": "; cin.ignore(); getline(cin, new_zipcode);
            clientes[opc_cli_edit-1].setZipCode(new_zipcode);
            break;
        }
        case 7:
        {
            int new_fiscal_regimen;
            cout << "Type the new fiscal regimen of " << clientes[opc_cli_edit-1].getName() << ": "; cin >> new_fiscal_regimen;
            clientes[opc_cli_edit-1].setRegimenFiscalID(new_fiscal_regimen);
            break;
        }
    }
    Actualizar_Clientes();
}
void SistemaDeVentas::VerClientes(){
    clientes = leer_clientes();
    int opc_bus_cli;
    cout << "\nChoose an option: " << "\n1. See all Clients" << "\n2. Seacrh by name" << "\n3. Search by city" << "\n4. Search by state" << "\nOption: "; cin >> opc_bus_cli;
    switch (opc_bus_cli) {
        case 1:
        {
            for (int i = 0; i < clientes.size(); i++) {
                cout << i+1 << ".- " << clientes[i].getName() << " - " << clientes[i].getID() << endl;
            }
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
    }
}
void SistemaDeVentas::EliminarCliente(){
    
}
vector<Clientes> SistemaDeVentas::leer_clientes(){
    vector<Clientes> clientes1;
    ifstream lectura_clientes(rutaClientes.c_str());
    string linea;
    while (getline(lectura_clientes, linea)) {
        string name, rfc, address, city, state, zipcode;
        int id_c, reg_fis_id;
        vector<string> carga_clientes;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_clientes.push_back(parte);
                parte = "";
            }
            else{
                parte += linea[i];
            }
        }
        carga_clientes.push_back(parte);
        name  = carga_clientes[0];
        rfc = carga_clientes[1];
        address = carga_clientes[2];
        city =  carga_clientes[3];
        state = carga_clientes[4];
        zipcode = carga_clientes[5];
        reg_fis_id = stoi(carga_clientes[6]);
        id_c = stoi(carga_clientes[7]);
        Clientes cliente_guardado = Clientes(id_c, name, rfc, reg_fis_id, address, city, state, zipcode);
        cliente_guardado.setID(id_c);
        cliente_guardado.setName(name);
        cliente_guardado.setRFC(rfc);
        cliente_guardado.setRegimenFiscalID(reg_fis_id);
        cliente_guardado.setAddress(address);
        cliente_guardado.setCity(city);
        cliente_guardado.setState(state);
        cliente_guardado.setZipCode(zipcode);
        clientes1.push_back(cliente_guardado);
    }
    return clientes1;
}
void SistemaDeVentas::Actualizar_Clientes(){
    ofstream archivo_clientes(rutaClientes);
    for (int i = 0; i < clientes.size() ; i++) {
        archivo_clientes << clientes[i].getName() << "," << clientes[i].getRFC() << "," << clientes[i].getAddress() << "," << clientes[i].getCity() << "," << clientes[i].getState() << "," << clientes[i].getZipCode() << "," << clientes[i].getRegimenFiscalID() << "," << clientes[i].getID() << endl;
    }
    archivo_clientes.close();
}
