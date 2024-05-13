#include "Productos.h"

Productos::Productos(){
    
}

Productos::~Productos(){
}
product NuevoProducto; //Instancia de la estructura product
void Productos::Menu_Principal(){
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
                Agregar_Productos();
                break;
            }
            case 2:
            {
                Editar_Productos();
                break;
            }
            case 3:
            {
                Ver_Productos();
                break;
            }
            case 4:
            {
                Eliminar_Productos();
                break;
            }
            case 5:
            {
                break;
            }
            default:
            {
                cout << "Seleccione una opción válida" << endl;
                Menu_Principal();
                break;
            }
        }

        
    } while (opc_men_pod != 5);
}
void Productos::Agregar_Productos(){
    //Falta crear encabezados
    ofstream archivo_p("Productos.csv", ios::app);
    cout << "Let´s start by scanning the product barcode: " << endl;
    cin >> NuevoProducto.UPC;
    archivo_p << endl; //Para asegurarnos de crear una nueva fila
    archivo_p << NuevoProducto.UPC << ",";
    cout << "Type the product name: ";
    cin >> NuevoProducto.name;
    archivo_p << NuevoProducto.name << ",";
    cout << "Type the ID for this presentation of " << NuevoProducto.name << ": ";
    cin >> NuevoProducto.id_presentation;
    archivo_p << NuevoProducto.id_presentation << ",";
    cout << "Type the price of " << NuevoProducto.name << ": ";
    cin >> NuevoProducto.price;
    archivo_p << NuevoProducto.price << ",";
    cout << "Type the cost of " << NuevoProducto.name << ": ";
    cin >> NuevoProducto.cost;
    archivo_p << NuevoProducto.cost << ",";
    Decision_IVA();
    cout << "Type the stock of " << NuevoProducto.name << ": ";
    cin >> NuevoProducto.stock;
    archivo_p << NuevoProducto.stock;
    _productos.push_back(NuevoProducto);
    archivo_p.close();
}
void Productos::Eliminar_Productos(){
    cout << "Type or scan the product barcode: " << endl;
    cin >> NuevoProducto.UPC;
    for (int i = 0; i < _productos.size(); i++) {
        if (NuevoProducto.UPC == _productos[i].UPC) {
            cout << _productos[i].name << " eliminado exitosamente." << endl;
            //ELIMINAR ESPACIO COMPLETO DEL VECTOR
        }
    }
}
void Productos::Ver_Productos(){
    cout << "Would you prefer to order or to fliter the products?" << endl;
    cout << "1. Order"
    << "\n2. Filter" << endl;
    
}
void Productos::Editar_Productos(){
}
void Productos::Decision_IVA(){
    int opc_iva = 0;
    cout << NuevoProducto.name << " has IVA? " << endl;
    cout << "(1. YES/2.NO): ";
    cin >> opc_iva;
    switch(opc_iva){
        case 1:
        {
            NuevoProducto.has_iva = true;
            break;
        }
        case 2:
        {
            NuevoProducto.has_iva = false;
            break;
        }
    }
}
void Productos::Assign_ID(){
    ifstream archivo_lectura;
    archivo_lectura.open("Productos.csv");
    string linea;
    while (getline(archivo_lectura, linea)) {
        vector <string> id_pp;
        string parte;
        for (int i = 0; i < linea.size(); i++) {
            if (linea[i] == ',') {
                id_pp.push_back(parte);
                parte = "";
            }
            else{
                parte += linea[i];
            }
        }
        for (int i = 0; i < id_pp.size(); i++) {
            
        }
    }
}
