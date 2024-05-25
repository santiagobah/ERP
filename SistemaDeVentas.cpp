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
    rutaRegistrosUsuarios = "./Scr/RegistrosUsuarios.csv";
    usuarioActual = nullptr;

}

//Corregir: Ya no sirve el usuario admin una vez que se registraron nuevos, o eso fue por la prueba que hice? no estoy seguro xd, verificar al final

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
        cout << "Start menu: " << endl
			<< "1. Log in" << endl
			<< "2. Exit the System" << endl
			<< "Option: ";
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
            cout << "Select one of the valid options" << endl;
            PausaConEnter();
            break;
        }
        // Limpia la pantalla antes de mostrar el menú nuevamente
        LimpiarPantalla();
        delete usuarioActual;
        usuarioActual = nullptr;
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
        RegistroDeActividad("User Creation");
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
        LimpiarPantalla();
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        for (int i = 0; i < usuarios.size(); i++)
        {
            if (username == usuarios[i].getUsername() && usuarios[i].Encrypt(password) == usuarios[i].getPassword())
            {
                bandera = true;
                usuarioActual = new Usuarios(usuarios[i].getName(), usuarios[i].getLastname(), usuarios[i].getUsername(), usuarios[i].getPassword(), usuarios[i].getRole(), usuarios[i].getId(), usuarios[i].getDateJoined());
                RegistroDeActividad("Log In");
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
                cout << "You have exceeded the number of allowed attempts" << endl; 
                PausaConEnter();
                RegistroDeActividad("Log In Attempt Failed");
                exit(1);
            }
            cout << "Incorrect username or password" << endl;
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
        cout << "Administrator menu: " << endl
			<< "1. User Management" << endl
			<< "2. Customer Management" << endl
			<< "3. Product Management" << endl
			<< "4. Sales Management" << endl
			<< "5. Reports Management" << endl
			<< "6. Exit" << endl
			<< "Option: ";
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
            GestionDeClientes();
            break;
        case 3:
            // Llama al método GestionDeProductos
            GestionDeProductos();
            break;
        case 4:
            // Llama al método GestionDeVentas
            GestionDeVentas();
            break;
        case 5:
            // Llama al método GestionDeInformes
            GestionDeInformes();
            break;
        case 6:
            LimpiarPantalla();
            break;
        default:
            // En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
            // y espera a que el usuario presione Enter
            LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
            PausaConEnter();
            break;
        }
    }
}

void SistemaDeVentas::MenuVendedor()
{
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionMV = 0;
    // Bucle que se ejecuta hasta que el usuario elige salir del Sistema
    while (opcionMV != 4) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
        cout << "Seller menu: " << endl
            << "1. Customer Management" << endl
            << "2. Sales Management" << endl
            << "3. Reports Management" << endl
            << "4. Exit" << endl
            << "Option: ";
		cin >> opcionMV;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMV)
		{
		case 1:
			// Llama al método GestionDeClientes
			GestionDeClientes();
			break;
		case 2:
			// Llama al método Gestión de Ventas
			GestionDeVentas();
			break;
		case 3:
			// Llama al método Gestión de Informes
			GestionDeInformes();
			break;
		case 4:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
	}
}

void SistemaDeVentas::MenuRH()
{
    // Variable para almacenar la opción seleccionada por el usuario
	int opcionMRH = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del Sistema
	while (opcionMRH != 3) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
        cout << "Human Resources menu: " << endl
			<< "1. Customer Management" << endl
			<< "2. Reports Management" << endl
			<< "3. Exit" << endl
			<< "Option: ";
		cin >> opcionMRH;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMRH)
		{
		case 1:
			// Llama al método GestionDeUsuarios
			GestionDeUsuarios();
			break;
		case 2:
			// Llama al método GestionDeClientes
			GestionDeClientes();
			break;
		case 3:
			// Llama al método GestionDeInformes
			GestionDeInformes();
			break;
		case 4:
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

void SistemaDeVentas::MenuAlmacen()
{
    // Variable para almacenar la opción seleccionada por el usuario
	int opcionMAL = 0;
	// Bucle que se ejecuta hasta que el usuario elige salir del Sistema
	while (opcionMAL != 3) {
		// Limpia la pantalla antes de mostrar el menú
		LimpiarPantalla();
		// Muestra las opciones del menú y solicita la entrada del usuario
        cout << "Warehouse menu: " << endl
            << "1. Product Management" << endl
            << "2. Reports Management" << endl
            << "3. Exit" << endl
            << "Option: ";
		cin >> opcionMAL;
		// Realiza acciones basadas en la opción seleccionada por el usuario
		switch (opcionMAL)
		{
		case 1:
			// Llama al método GestionDeProductos
			GestionDeProductos();
			break;
		case 2:
			// Llama al método GestionDeInformes
			GestionDeInformes();
			break;
		case 3:
			LimpiarPantalla();
			break;
		default:
			// En caso de que el usuario seleccione una opción no válida, muestra un mensaje de error
			// y espera a que el usuario presione Enter
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
	}

}

void SistemaDeVentas::GestionDeProductos() {
    int opc_men_pod = 0;
    do {
        LimpiarPantalla();
        cout << "Welcome to the Products menu" << endl <<
            "1. Add Products" <<
            "\n2. Edit Products" <<
            "\n3. View Products" << //SEE?
            "\n4. Delete Products" <<
            "\n5. Return" <<
            "\nOption: ";
        cin >> opc_men_pod;
        switch (opc_men_pod) {
        case 1:
        {
            RegistroDeActividad("Add Product");
            SistemaDeVentas::AgregarProducto();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Edit Product");
            SistemaDeVentas::EditarProducto();
            break;
        }
        case 3:
        {
            RegistroDeActividad("View Products");
            SistemaDeVentas::VerProductos();
            break;
        }
        case 4:
        {
            RegistroDeActividad("Delete Product");
            SistemaDeVentas::EliminarProducto();
            break;
        }
        case 5:
        {
            break;
        }
        default:
        {
            LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
            SistemaDeVentas::GestionDeProductos();
            break;
        }
        }
    } while (opc_men_pod != 5);
}

void SistemaDeVentas::AgregarProducto() { //Crear excepciones por si aún no se crea el archivo de productos
    //Hacer que ID vaya creciendo
    //Hacer que ID vaya creciendo
    int id_u_actual; //Para hacer ID's consecutivos
    int id_p_actual; //Para hacer ID's consecutivos
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        ofstream archivo_prod(rutaProductos.c_str());
        id_u_actual = 0;
        id_p_actual = 0;
    }
    else {
        productos = SistemaDeVentas::leer_productos(); //Para que inicie el vector ya cargado con los productos que estén ya registrados
        int cant_prod_reg = productos.size();
        id_u_actual = productos[cant_prod_reg - 1].get_id();
        id_p_actual = presentaciones[cant_prod_reg - 1].getID();
    }
    ofstream archivo_productos(rutaProductos, ios::app);
    string upc, name;
    float price, cost;
    bool has_iva;
    int stock;

    //    cout << "The  ID for this " << name << " presentation is going to be: " << id_p_actual + 1 << endl; archivo_productos << id_p_actual + 1 << ",";
    string first_part_name;
    int n_presentations = 0;
    cout << "Type the main name of the new product: "; cin.ignore(); getline(cin, first_part_name);
    cout << "How many presentations are there for " << first_part_name << "? "; cin >> n_presentations;
    for (int i = 0; i < n_presentations; i++) {
        archivo_productos << first_part_name << ",";
        ofstream presentaciones_productos(rutaPresentaciones.c_str(), ios::app);
        cout << "\nAdd something to this name to create a unique name for presentation " << i + 1 << " of " << first_part_name << ": ";
        cin.ignore(); getline(cin, name); name = first_part_name + " " + name;
        cout << "\nScan the barcode of " << name << ": ";
        cin >> upc; archivo_productos << upc << ",";
        cout << "\nThe unique ID for " << name << " is going to be: " << id_u_actual + 1 << endl; archivo_productos << id_u_actual + 1 << ",";
        cout << "\nType the price for " << name << ": ";
        cin >> price; archivo_productos << price << ",";
        cout << "Type the cost for " << name << ": ";
        cin >> cost; archivo_productos << cost << ",";
        //Implementar un switch para el IVA
        cout << name << " has IVA? (1. YES/ 0.NO): "; //implementar método que sea un switch para 1.yes, 2.no
        cin >> has_iva; archivo_productos << has_iva << ",";
        cout << "How many " << name << " are available right now? ";
        cin >> stock; archivo_productos << stock << ",";
        cout << "The ID for this presentation of " << name << " is " << id_p_actual + 1 << endl;
        presentaciones_productos << id_p_actual + 1 << ",";
        presentaciones_productos << name << endl;
        archivo_productos << id_p_actual + 1 << endl;
        Productos NuevoProducto(id_u_actual, upc, first_part_name, id_p_actual, price, cost, has_iva, stock, id_p_actual, name);
        productos.push_back(NuevoProducto);
        id_u_actual++;
        id_p_actual++;
    }
    archivo_productos.close();
}

void SistemaDeVentas::EditarProducto() { //crear confirmaciones de edit
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
    }
    cout << "Choose the product which you want to edit: " << endl;
    int prod_edit;
    for (int i = 0; i < productos.size(); i++) {
        cout << i + 1 << ".- " << productos[i].get_name() << endl;
    }
    cout << "Product to edit: ";
    cin >> prod_edit;
    int var_edit;
    cout << "You are now editing " << productos[prod_edit - 1].get_name() << endl;
    cout << "Choose the variable to edit: " << endl;
    cout << "1. Name" << "\n2. Price" << "\n3.Cost" << "\n4. IVA" << "\n5. Stock" << "\nOption: ";
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
    Actualizar_Productos(); //Actualiza los cambios que se hayan realizado al momento del edit
}

void SistemaDeVentas::VerProductos() {
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
    }
    vector <Productos> aux_ord_prod;
    aux_ord_prod = productos;
    int sort_filter;
    cout << "1. Sort products" << "\n2. Filter products" << "\nOption: "; cin >> sort_filter;
    switch (sort_filter) {
    case 1:
    {
        int sort_opc;
        cout << "\nSort by: " << "\n1. Stock" << "\n2. ID" << "\n3. Price: Low to High" << "\n4. Price: High to Low" << "\n5. Cost" << "\nOption: "; cin >> sort_opc;
        switch (sort_opc) {
        case 1:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size(); j++) {
                    if (productos[j].get_stock() > productos[j + 1].get_stock()) {
                        aux_ord_prod[0] = productos[j + 1];
                        productos[j + 1] = productos[j];
                        productos[j] = aux_ord_prod[0];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << productos[i].get_name() << " with a stock of " << productos[i].get_stock() << endl;
            }
            break;
        }
        case 2:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size(); j++) {
                    if (productos[j].get_id() > productos[j + 1].get_id()) {
                        aux_ord_prod[0] = productos[j + 1];
                        productos[j + 1] = productos[j];
                        productos[j] = aux_ord_prod[0];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << productos[i].get_name() << ". ID: " << productos[i].get_id() << endl;
            }
            break;
        }
        case 3:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size(); j++) {
                    if (productos[j].get_price() > productos[j + 1].get_price()) {
                        aux_ord_prod[0] = productos[j + 1];
                        productos[j + 1] = productos[j];
                        productos[j] = aux_ord_prod[0];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << productos[i].get_name() << " with a price of $" << productos[i].get_price() << endl;
            }
            break;
        }
        case 4:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size(); j++) {
                    if (productos[j].get_price() > productos[j + 1].get_price()) {
                        aux_ord_prod[0] = productos[j + 1];
                        productos[j + 1] = productos[j];
                        productos[j] = aux_ord_prod[0];
                    }
                }
            }
            for (int i = productos.size(); i > 0; i--) {
                cout << i << ".- " << productos[i].get_name() << " with a price of $" << productos[i].get_price() << endl;
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < productos.size(); i++) {
                for (int j = 0; j < productos.size(); j++) {
                    if (productos[j].get_cost() > productos[j + 1].get_cost()) {
                        aux_ord_prod[0] = productos[j + 1];
                        productos[j + 1] = productos[j];
                        productos[j] = aux_ord_prod[0];
                    }
                }
            }
            for (int i = 0; i < productos.size(); i++) {
                cout << i + 1 << ".- " << productos[i].get_name() << " with a cost of $" << productos[i].get_cost() << endl;
            }
            break;
        }
        }
        //Restuarar el vector a estar ordenado por ID para que no ocasione problemas con el aumento de 1 en 1 para el ID
        for (int i = 0; i < productos.size(); i++) {
            for (int j = 0; j < productos.size(); j++) {
                if (productos[j].get_id() > productos[j + 1].get_id()) {
                    aux_ord_prod[0] = productos[j + 1];
                    productos[j + 1] = productos[j];
                    productos[j] = aux_ord_prod[0];
                }
            }
        }
        break;
    }
    case 2:
    {
        int opc_fil;
        vector <Productos> aux_bus;
        cout << "\nFilter by: " << "\n1. Name" << "\n2. ID" << "\n3. UPC" << "\nOption: "; cin >> opc_fil;
        switch (opc_fil) {
        case 1:
        {
            string nombre_bus;
            cout << "Type the name of the product: "; cin.ignore(); getline(cin, nombre_bus);
            for (int i = 0; i < productos.size(); i++) {
                if (nombre_bus == productos[i].get_name()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                cout << j + 1 << ".- " << aux_bus[j].get_name() << endl;
            }
            break;
        }
        case 2:
        {
            int id_bus;
            cout << "Type the ID of the product: "; cin >> id_bus;
            for (int i = 0; i < productos.size(); i++) {
                if (id_bus == productos[i].get_id()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                cout << j + 1 << ".- " << aux_bus[j].get_name() << ". ID: " << aux_bus[j].get_id() << endl;
            }
            break;
        }
        case 3:
        {
            string upc_bus;
            cout << "Scan the barcode of the product: "; cin.ignore(); getline(cin, upc_bus);
            for (int i = 0; i < productos.size(); i++) {
                if (upc_bus == productos[i].get_UPC()) {
                    aux_bus.push_back(productos[i]);
                }
            }
            for (int j = 0; j < aux_bus.size(); j++) {
                cout << j + 1 << ".- " << aux_bus[j].get_name() << endl;
            }
            break;
        }
        }
        break;
    }
    }
}

void SistemaDeVentas::EliminarProducto() { //crear confirmaciones de delete
    ifstream archivo_pr(rutaProductos.c_str());
    if (!archivo_pr) {
        cout << "There are not registered products" << endl;
        GestionDeProductos();
    }
    else {
        productos = SistemaDeVentas::leer_productos();
    }
    string upc;
    int band_prod = 0;
    cout << "\nScan the barcode of the product which you want to delete: ";
    cin >> upc;
    for (int i = 0; i < productos.size(); i++) {
        if (upc == productos[i].get_UPC()) {
            cout << productos[i].get_name() << " successfully deleted" << endl;
            productos.erase(productos.begin() + i);
            band_prod = 1;
            break;
        }
    }
    if (band_prod == 0) {
        cout << "The product with the barcode " << upc << " was not found" << endl;
    }
    Actualizar_Productos();
}

void SistemaDeVentas::Actualizar_Productos() {
    ofstream archivo_p(rutaProductos.c_str());
    for (int i = 0; i < productos.size(); i++) {
        archivo_p << productos[i].get_name() << "," << productos[i].get_UPC() << "," << productos[i].get_id() << "," << productos[i].get_price() << "," << productos[i].get_cost() << "," << productos[i].get_has_iva() << "," << productos[i].get_stock() << "," << productos[i].get_id_presentation() << endl;
    }
    archivo_p.close();
}

void SistemaDeVentas::Actualizar_Presentaciones()
{
    ofstream presentaciones_pr(rutaPresentaciones.c_str());
    for (int i = 0; i < presentaciones.size(); i++) {
        presentaciones_pr << presentaciones[i].getID() << "," << presentaciones[i].getName() << endl;
    }
}

vector<Productos> SistemaDeVentas::leer_productos() {
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
            else {
                parte += linea[i];
            }
        }
        carga_productos.push_back(parte);
        name = carga_productos[0];
        upc = carga_productos[1];
        id_u = stoi(carga_productos[2]);
        price = stof(carga_productos[3]);
        cost = stof(carga_productos[4]);
        has_iva = stoi(carga_productos[5]);
        stock = stoi(carga_productos[6]);
        id_p = stoi(carga_productos[7]);
        presentaciones = leer_presentaciones();
        string nombre_p;
        int id_pr = 0;
        for (int i = 0; i < presentaciones.size(); i++) {
            id_pr = presentaciones[i].getID();
            nombre_p = presentaciones[i].getName();
        }
        Productos guardado_productos = Productos(id_u, upc, name, id_p, price, cost, has_iva, stock, id_pr, nombre_p);
        guardado_productos.set_id(id_u);
        guardado_productos.set_UPC(upc);
        guardado_productos.set_name(name);
        guardado_productos.set_id_presentation(id_p);
        guardado_productos.set_price(price);
        guardado_productos.set_cost(cost);
        guardado_productos.set_has_iva(has_iva);
        guardado_productos.set_stock(stock);
        guardado_productos.setID(id_pr);
        guardado_productos.setName(nombre_p);
        productos1.push_back(guardado_productos);
    }
    return productos1;
}

vector<Presentacion> SistemaDeVentas::leer_presentaciones()
{
    vector<Presentacion> presentaciones1;
    ifstream lectura_presentaciones(rutaPresentaciones.c_str());
    string linea_p;
    while (getline(lectura_presentaciones, linea_p)) {
        vector <string> carga_presentaciones;
        string parte_p;
        string name_p;
        int id_p_pcsv;
        for (int i = 0; i < linea_p.size(); i++) {
            if (linea_p[i] == ',') {
                carga_presentaciones.push_back(parte_p);
                parte_p = "";
            }
            else {
                parte_p += linea_p[i];
            }
        }
        carga_presentaciones.push_back(parte_p);
        id_p_pcsv = stoi(carga_presentaciones[0]);
        name_p = carga_presentaciones[1];
        Presentacion lectura_pr = Presentacion(id_p_pcsv, name_p);
        lectura_pr.setID(id_p_pcsv);
        lectura_pr.setName(name_p);
        presentaciones1.push_back(lectura_pr);
    }
    return presentaciones1;
}

void SistemaDeVentas::GestionDeUsuarios()
{
    // Variable para almacenar la opción seleccionada por el usuario
    int opcionGU = 0;
    do {
        // Limpia la pantalla antes de mostrar el menú
        LimpiarPantalla();
        cout << "Welcome to the Users menu" << endl;
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
            RegistroDeActividad("User Creation");
            AgregarUsuario();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Edit User");
            EditarUsuario();
            break;
        }
        case 3:
        {
            RegistroDeActividad("Delete User");
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
            
            cout << "Select one of the valid options" << endl;
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
    bool validar = false;
    while (validar == false)
    {
        cout << "Type the username of the user: ";
        cin >> username;
        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i].getUsername() == username) {
                cout << "The username already exists, choose another username" << endl;
            }
            else {
                validar = true;
            }
        }
    }
    cout << "Type the password of the user: ";
    cin >> password;
    while (id < 1 || id > 4) {
        cout << "Select the role of the user: " << endl
            << "1. Administrator" << endl
            << "2. Seller" << endl
            << "3. HR" << endl
            << "4. Warehouse" << endl
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
    int cantidad_usuarios = usuarios.size();
    int current_id = usuarios[cantidad_usuarios - 1].getId(); //Para que el ID vaya creciendo
    id = current_id + 1;
    Usuarios NuevoUsuario = Usuarios(name, surname, username, password, role, id, dateJoined);
    NuevoUsuario.setPassword(NuevoUsuario.Encrypt(password));
    NuevoUsuario.setId(id);
    usuarios.push_back(NuevoUsuario);
    ofstream archivo;
    archivo.open(rutaUsuarios.c_str());
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

void SistemaDeVentas::GestionDeClientes() {
    int opc_cli;
    do {
        cout << "Welcome to the Clients menu: " << endl
			<< "1. Add Client" << endl
			<< "2. Edit Client" << endl
			<< "3. View Clients" << endl
			<< "4. Delete Client" << endl
			<< "5. Return" << endl
			<< "Option: ";
        cin >> opc_cli;
        switch (opc_cli) {
        case 1:
        {
            RegistroDeActividad("Add Client");
            AgregarCliente();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Edit Client");
            EditarCliente();
            break;
        }
        case 3:
        {
            RegistroDeActividad("View Clients");
            VerClientes();
            break;
        }
        case 4:
        {
            RegistroDeActividad("Delete Client");
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

void SistemaDeVentas::AgregarCliente() { //Corregir con cin.ignore()
    int actual_id_cliente;
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        ofstream archivo_cll(rutaClientes.c_str());
        actual_id_cliente = 0;
    }
    else {
        clientes = leer_clientes();
        int cant_client_reg = clientes.size();
        actual_id_cliente = clientes[cant_client_reg - 1].getID();
    }
    string name, rfc, address, city, state, zipcode, name_reg_fis;
    int code_reg_fis;
    ofstream archivo_clientes(rutaClientes, ios::app);
    cout << "\nType the client´s name: "; cin >> name; archivo_clientes << name << ",";
    cout << "Type the rfc of " << name << ": "; cin >> rfc; archivo_clientes << rfc << ",";
    cout << "Type the address of " << name << ": "; cin >> address; archivo_clientes << address << ",";
    cout << "Type the city where " << name << " lives: "; cin >> city; archivo_clientes << city << ",";
    cout << "Type the state where " << name << " lives: "; cin >> state; archivo_clientes << state << ",";
    cout << "Type the zipcode where " << address << " is located: "; cin >> zipcode; archivo_clientes << zipcode << ",";
    cout << "The ID for the 'fiscal register' of " << name << " is: " << actual_id_cliente + 1; archivo_clientes << actual_id_cliente + 1 << ",";
    ofstream archivo_regimenes(rutaRegimenesFiscales, ios::app);
    archivo_regimenes << actual_id_cliente + 1 << ",";
    cout << "\nType the code of the fiscal register of " << name << ": "; cin >> code_reg_fis; archivo_regimenes << code_reg_fis << ",";
    cout << "Type the name of the fiscal register of " << name << ": "; cin.ignore(); getline(cin, name_reg_fis); archivo_regimenes << name_reg_fis << endl;
    cout << "The assigned id for " << name << " is " << actual_id_cliente + 1; archivo_clientes << actual_id_cliente + 1 << endl;
    Clientes nuevoCliente = Clientes(actual_id_cliente, name, rfc, actual_id_cliente, address, city, state, zipcode, actual_id_cliente, code_reg_fis, name_reg_fis);
    clientes.push_back(nuevoCliente);
    archivo_clientes.close();
}

void SistemaDeVentas::EditarCliente() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    int opc_cli_edit;
    cout << "Choose the client which information you would like to edit: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
        cout << i + 1 << ".- " << clientes[i].getName() << endl;
    }
    cout << "Client to edit: "; cin >> opc_cli_edit;
    int var_edit;
    cout << "You are now editing " << clientes[opc_cli_edit - 1].getName() << "'s data. " << "\nChoose the variable to edit: ";
    cout << "\n1. Name" << "\n2. RFC" << "\n3. Address" << "\n4. City" << "\n5. State" << "\n6. Zipcode" << "\n7. Fiscal Regimen" << "\nOption: ";  cin >> var_edit;
    switch (var_edit) {
    case 1:
    {
        string new_name;
        cout << "Type the new name: "; cin.ignore(); getline(cin, new_name);
        clientes[opc_cli_edit - 1].setName(new_name);
        break;
    }
    case 2:
    {
        string new_rfc;
        cout << "Type the new RFC of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_rfc);
        clientes[opc_cli_edit - 1].setRFC(new_rfc);
        break;
    }
    case 3:
    {
        string new_address;
        cout << "Type the new address of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_address);
        clientes[opc_cli_edit - 1].setAddress(new_address);
        break;
    }
    case 4:
    {
        string new_city;
        cout << "Type the new city of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_city);
        clientes[opc_cli_edit - 1].setCity(new_city);
        break;
    }
    case 5:
    {
        string new_state;
        cout << "Type the new state of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_state);
        clientes[opc_cli_edit - 1].setState(new_state);
        break;
    }
    case 6:
    {
        string new_zipcode;
        cout << "Type the new zipcode of " << clientes[opc_cli_edit - 1].getName() << ": "; cin.ignore(); getline(cin, new_zipcode);
        clientes[opc_cli_edit - 1].setZipCode(new_zipcode);
        break;
    }
    case 7:
    {
        int new_fiscal_regimen;
        cout << "Type the new fiscal regimen of " << clientes[opc_cli_edit - 1].getName() << ": "; cin >> new_fiscal_regimen;
        clientes[opc_cli_edit - 1].setRegimenFiscalID(new_fiscal_regimen);
        break;
    }
    }
    Actualizar_Clientes();
}

void SistemaDeVentas::VerClientes() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    int opc_bus_cli;
    cout << "\nChoose an option: " << "\n1. See all Clients" << "\n2. Seacrh by name" << "\n3. Search by city" << "\n4. Search by state" << "\nOption: "; cin >> opc_bus_cli;
    vector <Clientes> aux_bus_cli;
    switch (opc_bus_cli) {
    case 1:
    {
        for (int i = 0; i < clientes.size(); i++) {
            cout << i + 1 << ".- " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
        }
        break;
    }
    case 2:
    {
        string name_bus; cout << "Type the client you are searching for: "; cin.ignore(); getline(cin, name_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (name_bus == clientes[i].getName()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". ID: " << aux_bus_cli[j].getID() << endl;
        }
        break;
    }
    case 3:
    {
        string city_bus; cout << "Type the city where the client is located: "; cin.ignore(); getline(cin, city_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (city_bus == clientes[i].getCity()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". City: " << aux_bus_cli[j].getCity() << endl;
        }
        break;
    }
    case 4:
    {
        string state_bus; cout << "Type the state where the client is located: "; cin.ignore(); getline(cin, state_bus);
        for (int i = 0; i < clientes.size(); i++) {
            if (state_bus == clientes[i].getState()) {
                aux_bus_cli.push_back(clientes[i]);
            }
        }
        for (int j = 0; j < aux_bus_cli.size(); j++) {
            cout << j + 1 << ".- " << aux_bus_cli[j].getName() << ". State: " << aux_bus_cli[j].getState() << endl;
        }
        break;
    }
    }
}

void SistemaDeVentas::EliminarCliente() {
    ifstream archivo_cl(rutaClientes.c_str());
    if (!archivo_cl) {
        cout << "There aren´t any registered clients" << endl;
        GestionDeClientes();
    }
    else {
        clientes = SistemaDeVentas::leer_clientes();
    }
    cout << "Choose the client you would like to delete: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
        cout << i + 1 << ".-  " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
    }
    int opc_cli_del;
    cout << "Client to delete (type the ID): "; cin >> opc_cli_del;
    int band_cli_elim = 0;
    for (int j = 0; j < clientes.size(); j++) {
        if (opc_cli_del == clientes[j].getID()) {
            cout << "The client " << clientes[j].getName() << " has been succesfully deleted." << endl;
            clientes.erase(clientes.begin() + j);
            band_cli_elim = 1;
            break;
        }
    }
    if (band_cli_elim == 0) {
        cout << "Make sure to type correctly the ID of the client. " << endl;
    }
    Actualizar_Clientes();
}

void SistemaDeVentas::Actualizar_Clientes() {
    ofstream archivo_clientes(rutaClientes);
    for (int i = 0; i < clientes.size(); i++) {
        archivo_clientes << clientes[i].getName() << "," << clientes[i].getRFC() << "," << clientes[i].getAddress() << "," << clientes[i].getCity() << "," << clientes[i].getState() << "," << clientes[i].getZipCode() << "," << clientes[i].getRegimenFiscalID() << "," << clientes[i].getID() << endl;
    }
    archivo_clientes.close();
}

void SistemaDeVentas::Actualizar_Regimenes()
{
    ofstream archivo_regimenes(rutaRegimenesFiscales.c_str());
    for (int i = 0; i < regimenesFiscales.size(); i++) {
        archivo_regimenes << regimenesFiscales[i].getID() << "," << regimenesFiscales[i].getCode() << "," << regimenesFiscales[i].getName() << endl;
    }
}

vector<RegimenFiscal> SistemaDeVentas::leer_regimenes_fiscales()
{
    vector<RegimenFiscal> regimenes;
    ifstream lectura_regimenes(rutaRegimenesFiscales.c_str());
    string linea;
    while (getline(lectura_regimenes, linea)) {
        string nombre_reg;
        int id, cod;
        vector <string> carga_regimenes;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_regimenes.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_regimenes.push_back(parte);
        id = stoi(carga_regimenes[0]);
        cod = stoi(carga_regimenes[1]);
        nombre_reg = carga_regimenes[2];
        RegimenFiscal traslado_regimen = RegimenFiscal(id, cod, nombre_reg);
        traslado_regimen.setID(id);
        traslado_regimen.setCode(cod);
        traslado_regimen.setName(nombre_reg);
        regimenes.push_back(traslado_regimen);
    }
    return regimenes;
}

vector<Clientes> SistemaDeVentas::leer_clientes() {
    vector<Clientes> clientes1;
    ifstream lectura_clientes(rutaClientes.c_str());
    string linea;
    while (getline(lectura_clientes, linea)) {
        string name, rfc, address, city, state, zipcode, name_reg_fis;
        int id_c, reg_fis_id, code_reg_fis;
        vector<string> carga_clientes;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_clientes.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_clientes.push_back(parte);
        name = carga_clientes[0];
        rfc = carga_clientes[1];
        address = carga_clientes[2];
        city = carga_clientes[3];
        state = carga_clientes[4];
        zipcode = carga_clientes[5];
        reg_fis_id = stoi(carga_clientes[6]);
        id_c = stoi(carga_clientes[7]);
        regimenesFiscales = leer_regimenes_fiscales();
        for (int j = 0; j < regimenesFiscales.size(); j++) { //buscando el id en el objeto de regimenes para asignar los correctos
            if (reg_fis_id == regimenesFiscales[j].getID()) {
                code_reg_fis = regimenesFiscales[j].getCode();
                name_reg_fis = regimenesFiscales[j].getName();
            }
        }
        Clientes cliente_guardado = Clientes(id_c, name, rfc, reg_fis_id, address, city, state, zipcode, reg_fis_id, code_reg_fis, name_reg_fis);
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

void SistemaDeVentas::GestionDeVentas()
{
	int opcionGV = 0;
	do {
		LimpiarPantalla();
        cout << "Welcome to the Sales menu" << endl;
        cout << "1. Add Sale" << endl
            << "2. View Sales" << endl
			<< "3. Return" << endl
			<< "Option: ";
		cin >> opcionGV;
		switch (opcionGV) {
		case 1:
		{
            RegistroDeActividad("Add Sale");
			AgregarVenta();
			break;
		}
		case 2:
		{
            RegistroDeActividad("View Sales");
			VerVentas();
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGV != 3);
}

void SistemaDeVentas::AgregarVenta()
{
    clientes = leer_clientes();
    int cliente_actual = 0;
    cout << "\nSeleccione al cliente actual: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
        cout << i + 1 << ".- " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
    }
    cout << "Opcin: "; cin >> cliente_actual;
    productos = leer_productos();
    presentaciones = leer_presentaciones();
    //Siempre hay que leer los productos y presentaciones porque sino marca error
    ifstream archivo_ventas(rutaProductosVendidos.c_str());
    int id_sale = 0;
    int id_num_prod_vendido = 0;
    int quantity_same_product = 0;
    string upc_producto_vendido = "";
    if (!archivo_ventas) {
        ofstream archivo_productos_vendidos(rutaProductosVendidos.c_str());
    }
    else {
        productosVendidos = LeerProductosVendidos();
        int tam_prod_vend = productosVendidos.size();
        id_sale = productosVendidos[tam_prod_vend - 1].getID_Sale();
    }
    id_sale++; //Va creciendo el id cada que hay un nuevo registro de venta
    int id_producto_vendido;
    float precio_unidad;
    float total_compra = 0.0;
    vector <ProductosVendidos> compras_actuales;
    ofstream productos_vendidos(rutaProductosVendidos.c_str(), ios::app);
    cout << "Type 0 when you want to end, start scanning now: \n" << endl;
    do {
        int iterador_p_borrar;
        int band_dup = 0;
        int unidades_producto_vendido = 0;
        getline(cin, upc_producto_vendido);
        for (int i = 0; i < productos.size(); i++) {
            if (upc_producto_vendido == productos[i].get_UPC()) {
                unidades_producto_vendido++;//El cliente lleva al menos un artculo del encontrado
                for (int j = 0; j < presentaciones.size(); j++) {
                    if (productos[i].get_id_presentation() == presentaciones[j].getID()) {
                        cout << presentaciones[j].getName() << " --- $" << productos[i].get_price() << "\n" << endl;
                        id_producto_vendido = productos[i].get_id();
                        precio_unidad = productos[i].get_price();
                        if (productosVendidos.size() >= 1) {
                            int cant_prod_vend = productosVendidos.size();
                            id_num_prod_vendido = productosVendidos[cant_prod_vend - 1].getID() + 1;
                        }
                        else {
                            id_num_prod_vendido++;
                        }
                        for (int m = 0; m < compras_actuales.size(); m++) {
                            if (id_producto_vendido == compras_actuales[m].getID_Product()) {
                                unidades_producto_vendido++;
                                band_dup = 1;
                            }
                        }
                        ProductosVendidos nuevoProductoVendido = ProductosVendidos(id_num_prod_vendido, id_sale, id_producto_vendido, unidades_producto_vendido, precio_unidad);
                        nuevoProductoVendido.setID_Sale(id_sale);
                        nuevoProductoVendido.setQuantity(unidades_producto_vendido);
                        nuevoProductoVendido.setID(id_num_prod_vendido);
                        nuevoProductoVendido.setID_Product(id_producto_vendido);
                        nuevoProductoVendido.setSalePricePerUnit(precio_unidad);
                        compras_actuales.push_back(nuevoProductoVendido);
                        if (band_dup == 0) {
                            productosVendidos.push_back(nuevoProductoVendido);//Vector auxiliar para ver si ya se haba llevado ese producto en la misma compra/venta
                        }

                        for (int ii = 0; ii < compras_actuales.size(); ii++) {
                            if (id_sale == productosVendidos[ii].getID_Sale()) {
                                if (id_producto_vendido == productosVendidos[ii].getID_Product()) {
                                    productosVendidos[ii].setQuantity(unidades_producto_vendido);
                                }
                            }
                        }
                        productos_vendidos << id_num_prod_vendido << "," << id_sale << "," << id_producto_vendido << "," << unidades_producto_vendido << "," << precio_unidad << endl;
                        total_compra += precio_unidad;
                        break;
                    }
                }
            }
        }
    } while (upc_producto_vendido != "0");
    cout << "El total de la compra es de  $" << total_compra << endl;
    Actualizar_Productos_Vendidos();
    productos_vendidos.close();
    int usuario_actual_id = usuarioActual->getId();
    DateTime fecha_venta = ConvertirFechaADateTime();
    int cliente_actual_id = clientes[cliente_actual - 1].getID();
    //Registrar esta venta:
    Ventas nuevaVenta = Ventas(id_sale, fecha_venta, usuario_actual_id, cliente_actual_id, total_compra);
    nuevaVenta.setID(id_sale);
    nuevaVenta.setDateOfSale(fecha_venta);
    nuevaVenta.setUserID(usuario_actual_id);
    nuevaVenta.setClientID(cliente_actual_id);
    nuevaVenta.setTotal(total_compra);
    ventas_vector.push_back(nuevaVenta);
    ofstream archivo_venta(rutaVentas.c_str());
    for (int i = 0; i < ventas_vector.size(); i++) {
        archivo_venta << ventas_vector[i].getID() << "," << ventas_vector[i].getDateOfSale().year << "," << ventas_vector[i].getDateOfSale().month << "," << ventas_vector[i].getDateOfSale().day << "," << ventas_vector[i].getDateOfSale().hour << "," << ventas_vector[i].getDateOfSale().minute << "," << ventas_vector[i].getDateOfSale().second << "," << ventas_vector[i].getUserID() << "," << ventas_vector[i].getClientID() << "," << ventas_vector[i].getTotal() << endl;
    }
    archivo_venta.close();

}

void SistemaDeVentas::VerVentas()
{
    ventas_vector = LeerVentas();
    int opc_ventas;
    cout << "Sales: " << "\n1. See all sales" << "\n2. Filter by date" << "\n3. Filter by client" << "\n4. Filter by seller" << "\nOption: "; cin >> opc_ventas;
    switch (opc_ventas) {
    case 1:
    {
        for (int i = 0; i < ventas_vector.size(); i++) {
            cout << i + 1 << ".- Venta realizada para el cliente " << ventas_vector[i].getClientID() << " por un monto de $" << ventas_vector[i].getTotal() << endl;
        }
        break;
    }
    case 2:
    {
        vector <Ventas> aux_ventas;
        aux_ventas = ventas_vector;
        for (int i = 0; i < ventas_vector.size(); i++) {
            for (int j = 0; j < ventas_vector.size() - 1; j++) {
                if (ventas_vector[j].getDateOfSale().day > ventas_vector[j + 1].getDateOfSale().day) {
                    aux_ventas[j] = ventas_vector[j];
                    ventas_vector[j] = ventas_vector[j + 1];
                    ventas_vector[j + 1] = aux_ventas[j];
                }
            }
        }
        for (int i = 0; i < ventas_vector.size(); i++) {
            cout << "Venta " << i + 1 << " para " << ventas_vector[i].getClientID() << " en " << ventas_vector[i].getDateOfSale().day << endl;
        }

        break;
    }
    case 3:
    {
        int opc_cliente;
        cout << "Type the ID for the client you want to see the sales " << endl;
        for (int i = 0; i < clientes.size(); i++) {
            cout << i + 1 << ".- " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
        }
        cout << "Option: "; cin >> opc_cliente;
        for (int i = 0; i < clientes.size(); i++) {
            if (opc_cliente == clientes[i].getID()) {
                for (int j = 0; j < ventas_vector.size(); j++) {
                    if (clientes[i].getID() == ventas_vector[j].getClientID()) {
                        cout << "Sale for " << ventas_vector[j].getTotal() << " on " << ventas_vector[j].getDateOfSale().year << endl;
                    }
                }
            }
        }
        break;
    }
    case 4:
    {
        cout << "Sales by seller" << endl;
        break;
    }
    }
}

vector<Ventas> SistemaDeVentas::LeerVentas()
{
    vector <Ventas> ventas1;
    DateTime dateJoined;
    ifstream archivo_ventas(rutaVentas.c_str());
    string linea;

    while (getline(archivo_ventas, linea)) {
        int day, month, year, hour, minute, second;
        int id_v, usuario_actual_id, cliente_actual_id;
        float total_compra;
        vector <string> carga_ventas;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_ventas.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_ventas.push_back(parte);
        id_v = stoi(carga_ventas[0]);
        year = stoi(carga_ventas[1]);
        month = stoi(carga_ventas[2]);
        day = stoi(carga_ventas[3]);
        hour = stoi(carga_ventas[4]);
        minute = stoi(carga_ventas[5]);
        second = stoi(carga_ventas[6]);
        dateJoined = DateTime{ year, month, day, hour, minute, second };
        usuario_actual_id = stoi(carga_ventas[7]);
        cliente_actual_id = stoi(carga_ventas[8]);
        total_compra = stof(carga_ventas[9]);
        Ventas venta = Ventas(id_v, dateJoined, usuario_actual_id, cliente_actual_id, total_compra);
        ventas1.push_back(venta);
    }
    return ventas1;
}

vector<ProductosVendidos> SistemaDeVentas::LeerProductosVendidos()
{
    vector <ProductosVendidos> pven1;
    ifstream lectura_productos_vendidos(rutaProductosVendidos.c_str());
    string linea;
    while (getline(lectura_productos_vendidos, linea)) {
        int id, id_venta, id_producto, cantidad_prod;
        float precio;
        vector <string> carga_productos_vendidos;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                carga_productos_vendidos.push_back(parte);
                parte = "";
            }
            else {
                parte += linea[i];
            }
        }
        carga_productos_vendidos.push_back(parte);
        id = stoi(carga_productos_vendidos[0]);
        id_venta = stoi(carga_productos_vendidos[1]);
        id_producto = stoi(carga_productos_vendidos[2]);
        cantidad_prod = stoi(carga_productos_vendidos[3]);
        precio = stof(carga_productos_vendidos[4]);
        ProductosVendidos producto_vendido = ProductosVendidos(id, id_venta, id_producto, cantidad_prod, precio);
        pven1.push_back(producto_vendido);
    }
    return pven1;
}

void SistemaDeVentas::Actualizar_Productos_Vendidos()
{
    ofstream archivo_productos_vendidos(rutaProductosVendidos.c_str());
    for (int i = 0; i < productosVendidos.size(); i++) {
        archivo_productos_vendidos << productosVendidos[i].getID() << "," << productosVendidos[i].getID_Sale() << "," << productosVendidos[i].getID_Product() << "," << productosVendidos[i].getQuantity() << "," << productosVendidos[i].getSalePricePerUnit() << endl;
    }
}

void SistemaDeVentas::GestionDeInformes()
{
    switch (usuarioActual->getRoleInt())
    {
    case ADMIN:
        MenuInformesAdministrador();
        break;
    case VENDEDOR:
        MenuInformesVendedor();
        break;
    case RH:
		MenuInformesRH();
		break;
    case ALMACEN:
        MenuInformesAlmacen(); 
        break;
    default:
        LimpiarPantalla();
        PausaConEnter();
        break;
    }
}

void SistemaDeVentas::MenuInformesAdministrador()
{
    int opcionGI = 0;
    do {
        LimpiarPantalla();
        cout << "Welcome to the Reports menu" << endl;
        cout << "1. Sales Report" << endl
			<< "2. Inventory Report" << endl
			<< "3. User Activity Report" << endl
			<< "4. Return" << endl
			<< "Option: ";
        cin >> opcionGI;
        switch (opcionGI) {
        case 1:
        {
            RegistroDeActividad("Sales Report");
            InformeDeVentas();
            break;
        }
        case 2:
        {
            RegistroDeActividad("Stock Report");
            InformeDeInventarios();
            break;
        }
        case 3:
        {
            RegistroDeActividad("User Activity Report");
            InfromesDeActividadDeUsuarios();
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
            PausaConEnter();
            break;
        }
        }
    } while (opcionGI != 4);
}

void SistemaDeVentas::MenuInformesVendedor()
{
	int opcionGI = 0;
	do {
		LimpiarPantalla();
        cout << "Welcome to the Reports menu" << endl;
        cout << "1. Sales Report" << endl
            << "2. Return" << endl
            << "Option: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
            RegistroDeActividad("Sales Report");
			InformeDeVentas();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::MenuInformesRH()
{
    int opcionGI = 0;
	do {
		LimpiarPantalla();
        cout << "Welcome to the Reports menu" << endl;
        cout << "1. User Activity Report" << endl
			<< "2. Return" << endl
			<< "Option: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
            RegistroDeActividad("User Activity Report");
			InfromesDeActividadDeUsuarios();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::MenuInformesAlmacen()
{
    int opcionGI = 0;
	do {
		LimpiarPantalla();
        cout << "Welcome to the Reports menu" << endl;
        cout << "1. Inventory Report" << endl
            << "2. Return" << endl
            << "Option: ";
		cin >> opcionGI;
		switch (opcionGI) {
		case 1:
		{
            RegistroDeActividad("Stock Report");
			InformeDeInventarios();
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
		}
	} while (opcionGI != 2);
}

void SistemaDeVentas::InformeDeVentas()
{
int opc_inf = 0;
while (opc_inf != 3) {
	LimpiarPantalla();
	cout << "Welcome to the Sales Reports menu" << endl;
	cout << "Select the type of sales you want to see: " << endl
		<< "1. Sales by client" << endl
		<< "2. Sales by product" << endl
		<< "3. Return" << endl
		<< "Option chosen: ";
	cin >> opc_inf;
	switch (opc_inf)
	{
	case 1:
	{
        InformeDeVentasPorCliente();
		break;
	}
	case 2:
	{
        InformeDeVentasPorProducto();
		break;
	}
	case 3:
	{
		break;
	}
	default:
	{
		LimpiarPantalla();
		cout << "Select one of the valid options" << endl;
		PausaConEnter();
		break;
	}
	}
}
}

void SistemaDeVentas::InformeDeVentasPorCliente()
{
    clientes = leer_clientes();
	ventas_vector = LeerVentas();
    int opp_inf;
    cout << "Select the client you want to see the sales: " << endl;
    for (int i = 0; i < clientes.size(); i++) {
		cout << i + 1 << ".- " << clientes[i].getName() << ". ID: " << clientes[i].getID() << endl;
	}
    cout << "Option: "; cin >> opp_inf;
	int id_client = clientes[opp_inf - 1].getID();
	for (int i = 0; i < ventas_vector.size(); i++) {
		if (id_client == ventas_vector[i].getClientID()) {
			cout << "Sale for " << ventas_vector[i].getTotal() << " on " << ventas_vector[i].getDateOfSale().year << "/" << ventas_vector[i].getDateOfSale().month << "/" << ventas_vector[i].getDateOfSale().day << endl;
		}
	}
	PausaConEnter();
}

void SistemaDeVentas::InformeDeVentasPorProducto()
{
    productos = leer_productos();
	ventas_vector = LeerVentas();
    productosVendidos = LeerProductosVendidos();
	int opc_inf;
	cout << "Select the product you want to see the sales: " << endl;
	for (int i = 0; i < productos.size(); i++) {
		cout << i + 1 << ".- " << productos[i].get_name() << ". UPC: " << productos[i].get_UPC() << endl;
	}
	cout << "Option: "; cin >> opc_inf;
	int id_product = productos[opc_inf - 1].get_id();
	for (int i = 0; i < ventas_vector.size(); i++) {
		for (int j = 0; j < productosVendidos.size(); j++) {
			if (id_product == productosVendidos[j].getID_Product()) {
				cout << "Sale for " << productosVendidos[j].getQuantity() << " of " << productos[opc_inf - 1].get_name() << " on " << ventas_vector[i].getDateOfSale().year << "/" << ventas_vector[i].getDateOfSale().month << "/" << ventas_vector[i].getDateOfSale().day << endl;

			}
		}
	}
	PausaConEnter();

}

void SistemaDeVentas::InformeDeInventarios()
{
    int opc_inf = 0;
    while (opc_inf != 4) {
        LimpiarPantalla();
        cout << "Welcome to the Stock Reports menu" << endl;
        cout << "Select the type of stock you want to see: " << endl
			<< "1. Products with the most stock" << endl
			<< "2. Products with 0 in stock" << endl
			<< "3. Products that need to be restocked" << endl
			<< "4. Return" << endl
			<< "Option chosen: ";
		cin >> opc_inf;
        switch (opc_inf)
        {
        case 1:
        {
			InformeProductosConMayorInventario();
			break;
		}
        case 2:
        {
			InformeProductosConCeroInventario();
			break;
		}
		case 3:
        {
			InformeProductosResurtir();
			break;
		}
        case 4:
        {
			break;
		}
        default:
        {
            LimpiarPantalla();
            cout << "Select one of the valid options" << endl;
			PausaConEnter();
			break;
		}
		}
	}
}

void SistemaDeVentas::InformeProductosConMayorInventario()
{
    LimpiarPantalla();
    productos = leer_productos();
    //ordenar productos por inventario (orden descendente)(ordenamiento de burbuja)
    for (int i = 0; i < productos.size(); i++) {
        for (int j = 0; j < productos.size() - 1; j++) {
            if (productos[j].get_stock() < productos[j + 1].get_stock()) {
				Productos temp = productos[j];
				productos[j] = productos[j + 1];
				productos[j + 1] = temp;
			}
		}
	}
    cout << "Products with the most stock: " << endl;
    int n = 0;
    if (productos.size() < 10) {
        n = productos.size();
    }
    else {
        n = 10;
    }
    for (int i = 0; i < n; i++) {
		cout << "Name: " << productos[i].get_name() << " Stock: " << productos[i].get_stock() << endl;
	}
	PausaConEnter();
}

void SistemaDeVentas::InformeProductosConCeroInventario()
{
    LimpiarPantalla();
    productos = leer_productos();
	bool band = false;
    cout << "Products with 0 in stock: " << endl;
    for (int i = 0; i < productos.size(); i++) {
        if (productos[i].get_stock() == 0) {
			band = true;
			cout << "Name: " << productos[i].get_name() << " UPC: " << productos[i].get_UPC() << endl;
		}
	}
    if (!band) {
        cout << "There are no products with 0 in stock" << endl;
	}
	PausaConEnter();
}

void SistemaDeVentas::InformeProductosResurtir()
{
    LimpiarPantalla();
    productos = leer_productos();
	bool band = false;
    cout << "Products that need to be restocked: " << endl;
    for (int i = 0; i < productos.size(); i++) {
        if (productos[i].get_stock() < 10) {
			band = true;
			cout << "Name: " << productos[i].get_name() << " Stock: " << productos[i].get_stock() << endl;
		}
	}
    if (!band) {
        cout << "There are no products to restock" << endl;
	}
	PausaConEnter();
}

void SistemaDeVentas::InfromesDeActividadDeUsuarios()
{
	vector<RegistroDeActividadUser> registros = leerRegistrosUsuarios();
    int opc_inf;
    do{
		LimpiarPantalla();
        cout << "Welcome to the menu of User Activity Reports" << endl;
		cout << "1. Filter by User" << endl
            << "2. Filter by Action" << endl
            << "3. Filter by Date" << endl
            << "4. Show all" << endl
			<< "5. Return" << endl
            << "Option: ";
		cin >> opc_inf;
        switch (opc_inf)
        {
        case 1:
        {
            bool band = false;
            int id_user;
            cout << "Type the ID of the user: "; cin >> id_user;
            for (int i = 0; i < registros.size(); i++)
            {
                if (registros[i].ID_user == id_user)
                {
                    band = true;
                    cout << "user ID: " << registros[i].ID_user << " Date: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << " Action: " << registros[i].action << endl;
                }
            }
            if (!band)
			{
                cout << "There are no records of user activity with the ID " << id_user << endl;
			}
            PausaConEnter();
            break;
        }
        case 2:
        {
            InformeFiltroPorAccion(registros);
            break;
        }
        case 3:
        {
            int year, month, day;
            bool band = false;
            cout << "Type the year: "; cin >> year;
            cout << "Type the month: "; cin >> month;
            cout << "Type the day: "; cin >> day;
            for (int i = 0; i < registros.size(); i++)
            {
                if (registros[i].date.year == year && registros[i].date.month == month && registros[i].date.day == day)
                {
                    band = true;
                    cout << "user ID: " << registros[i].ID_user << " Date: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << " Action: " << registros[i].action << endl;
                }
            }
            if (!band) {
                cout << "There are no records of user activity on the date " << year << "/" << month << "/" << day << endl;
            }
            PausaConEnter();
            break;
        }
        case 4:
            for (int i = 0; i < registros.size(); i++)
            {
                cout << "user ID: " << registros[i].ID_user << " Date: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << " Action: " << registros[i].action << endl;
            }
       		PausaConEnter();
			break;
        }
	} while (opc_inf != 5);
}

void SistemaDeVentas::InformeFiltroPorAccion(vector<RegistroDeActividadUser>& registros)
{
    int opc_action = 0;
    string action;
    while (opc_action != 18) {
        LimpiarPantalla();
        cout << "Welcome to the menu of User Activity Reports" << endl
            << "Select the action by which you want to filter: " << endl
            << "1. User Creation" << endl
            << "2. Edit User" << endl
            << "3. Delete User" << endl
            << "4. Add Product" << endl
            << "5. Edit Product" << endl
            << "6. View Products" << endl
            << "7. Delete Product" << endl
            << "8. Add Client" << endl
            << "9. Edit Client" << endl
            << "10. View Clients" << endl
            << "11. Delete Client" << endl
            << "12. Add Sale" << endl
            << "13. View Sales" << endl
            << "14. Sales Report" << endl
            << "15. Stock Report" << endl
            << "16. User Activity Report" << endl
            << "17. Log In" << endl
            << "18. Log In Attempt Failed" << endl
            << "19. Return" << endl
            << "Option chosen: ";
        cin >> opc_action;
        switch (opc_action)
		{
        case 1:
        { action = "User Creation"; break; }
        case 2:
		{ action = "Edit User"; break; }
		case 3:
		{ action = "Delete User"; break; }
		case 4:
		{ action = "Add Product"; break; }
		case 5:
		{ action = "Edit Product"; break; }
        case 6:
		{ action = "View Products"; break; }
		case 7:
        { action = "Delete Product"; break; }
        case 8:
		{ action = "Add Client"; break; }
		case 9:
		{ action = "Edit Client"; break; }
		case 10:
		{ action = "View Clients"; break; }
		case 11:
		{ action = "Delete Client"; break; }
		case 12:
		{ action = "Add Sale"; break; }
        case 13:
        { action = "View Sales"; break; }
		case 14:
		{ action = "Sales Report"; break; }
		case 15:
		{ action = "Stock Report"; break; }
		case 16:
		{ action = "User Activity Report"; break; }
		case 17:
		{ action = "Log In"; break; }
		case 18:
            { action = "Log In Attempt Failed"; break; }
		case 19:
		{ break; }
		}
        bool band = false;
        for (int i = 0; i < registros.size(); i++)
        {
            if (registros[i].action == action)
            {
                cout << "user ID: " << registros[i].ID_user << " Date: " << registros[i].date.year << "/" << registros[i].date.month << "/" << registros[i].date.day << " Hora: " << registros[i].date.hour << ":" << registros[i].date.minute << ":" << registros[i].date.second << " Action: " << registros[i].action << endl;
        	    band = true;
            }
        }
        if (!band)
	    {
            cout << "There are no records of user activity with the action " << action << endl;
	    }
	    PausaConEnter();
	}
}

void SistemaDeVentas::RegistroDeActividad(string action)
{
    ifstream archivoLeido(rutaUsuarios.c_str());
    if (!archivoLeido) {
        ofstream archivo;
        archivo.open(rutaUsuarios.c_str(), fstream::out);
        archivo << "";
        archivo.close();
        EscribirRegistro(action);
    }
    else
    {
        EscribirRegistro(action);
    }
}

void SistemaDeVentas::EscribirRegistro(string actionER)
{
    ofstream archivo;
    archivo.open(rutaRegistrosUsuarios.c_str(), fstream::app);
    DateTime dateOfAction = ConvertirFechaADateTime();
    archivo << usuarioActual->getId() << "," << dateOfAction.year << "," << dateOfAction.month << ","
        << dateOfAction.day << "," << dateOfAction.hour << "," << dateOfAction.minute << ","
        << dateOfAction.second << "," << actionER << endl;
    archivo.close();
}

vector<RegistroDeActividadUser> SistemaDeVentas::leerRegistrosUsuarios()
{
    vector<RegistroDeActividadUser> registros;
    ifstream lectura_archivo(rutaRegistrosUsuarios.c_str());
    string linea;
    if(!lectura_archivo)
	{
        cout << "There are no user activity records" << endl;
	}
	else
	{
		while (getline(lectura_archivo, linea))
		{
			string parte;
			vector<string> carga_registros;
			for (int i = 0; i < linea.size(); i++)
			{
				if (linea[i] == ',')
				{
					carga_registros.push_back(parte);
					parte = "";
				}
				else
				{
					parte += linea[i];
				}
			}
			carga_registros.push_back(parte);
			int id_user = stoi(carga_registros[0]);
            DateTime dateOfAction = DateTime{ stoi(carga_registros[1]), stoi(carga_registros[2]), stoi(carga_registros[3]), stoi(carga_registros[4]), stoi(carga_registros[5]), stoi(carga_registros[6]) };
			string action = carga_registros[7];
            RegistroDeActividadUser registro = RegistroDeActividadUser{ id_user, action, dateOfAction };
			registros.push_back(registro);
		}
	}
    return registros;
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
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void SistemaDeVentas::LimpiarPantalla()
{
    system("cls");
}
