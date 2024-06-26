#include <iostream>
#include <string>

using namespace std;

class Persona {
public:
    string nombre;
    string apellido;
    int registro;
    int edad;

    //constructor
    Persona(string nombre, string apellido, int registro, int edad) : nombre(nombre), apellido(apellido), registro(registro), edad(edad) {}
};

class Nodo {
public:
    Persona* datos;
    Nodo* siguiente;
    Nodo* anterior; //agregamos un puntero al nodo anterior

    //constructor
    Nodo() : datos(NULL), siguiente(NULL), anterior(NULL) {}
    Nodo(Persona* datos) : datos(datos), siguiente(NULL), anterior(NULL) {}
};

class Lista {
private:
    Nodo* inicio;
    int contador;
    Nodo* iterador;

public:
    //constructor
    Lista() : inicio(NULL), contador(0), iterador(NULL) {}

    //funciones principales
    void agregar(Persona* datos);
    bool buscar(string criterio, string valor, string& resultado);
    bool eliminar(int registro);
    bool modificar(int registro, Persona* nuevosDatos);
    int contar();
    void mostrar();

    //funciones del iterador
    void iterador_first();
    void iterador_next();
    void iterador_prev();
    Nodo* iterador_getItem();

    Nodo* getInicio() {
        return inicio;
    }
};

void Lista::agregar(Persona* datos) {
    Nodo* nuevo = new Nodo(datos);
    if (inicio == NULL) {
        inicio = nuevo;
        inicio->siguiente = inicio; //el siguiente del primer nodo apunta a s� mismo
        inicio->anterior = inicio; //el anterior del primer nodo apunta a s� mismo
    }
    else {
        Nodo* temp = inicio;
        while (temp->siguiente != inicio) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->anterior = temp; //el anterior del nuevo nodo apunta al �ltimo nodo
        nuevo->siguiente = inicio; //el siguiente del nuevo nodo apunta al primer nodo
        inicio->anterior = nuevo; //el anterior del primer nodo apunta al nuevo nodo
    }
    contador++;
}

bool Lista::buscar(string criterio, string valor, string& resultado) {
    Nodo* temp = inicio;
    do {
        if (criterio == "nombre" && temp->datos->nombre == valor) {
            resultado = "Nombre: " + temp->datos->nombre + "\nApellido: " + temp->datos->apellido + "\nRegistro: " + to_string(temp->datos->registro) + "\nEdad: " + to_string(temp->datos->edad) + "\n";
            return true;
        }
        else if (criterio == "registro" && temp->datos->registro == stoi(valor)) {
            resultado = "Nombre: " + temp->datos->nombre + "\nApellido: " + temp->datos->apellido + "\nRegistro: " + to_string(temp->datos->registro) + "\nEdad: " + to_string(temp->datos->edad) + "\n";
            return true;
        }
        temp = temp->siguiente;
    } while (temp != inicio);
    resultado = "No hay un nodo con ese registro\n";
    return false;
}

bool Lista::eliminar(int registro) {
    if (inicio == NULL)
        return false;

    Nodo* temp = inicio;
    do {
        if (temp->datos->registro == registro) {
            if (temp == inicio) {
                inicio = temp->siguiente;
            }
            temp->anterior->siguiente = temp->siguiente;
            temp->siguiente->anterior = temp->anterior;
            delete temp->datos;
            delete temp;
            contador--;
            return true;
        }
        temp = temp->siguiente;
    } while (temp != inicio); //recorrer hasta que se regrese al inicio
    return false;
}

bool Lista::modificar(int registro, Persona* nuevosDatos) {
    Nodo* temp = inicio;
    do {
        if (temp->datos->registro == registro) {
            temp->datos->nombre = nuevosDatos->nombre;
            temp->datos->apellido = nuevosDatos->apellido;
            temp->datos->edad = nuevosDatos->edad;
            return true;
        }
        temp = temp->siguiente;
    } while (temp != inicio);
    return false;
}

int Lista::contar() {
    return contador;
}

void Lista::iterador_first() {
    //Mueve el iterador al primer nodo de la lista
    iterador = inicio;
}

void Lista::iterador_prev() {
    if (iterador != NULL && iterador->anterior != inicio) {
        iterador = iterador->anterior; //cambia al nodo anterior
    }
}

void Lista::iterador_next() {
    if (iterador != NULL) {
        iterador = iterador->siguiente;
    }
    else {
        cout << "El iterador no est� apuntando a ning�n nodo." << endl;
    }
}

Nodo* Lista::iterador_getItem() {
    //Obtiene el nodo que apunta el iterador
    return iterador;
}

int main() {
    Lista lista;
    char opcion;

    lista.agregar(new Persona("juan", "lopez", 22100191, 21));
    lista.agregar(new Persona("pedro", "lopez", 22100192, 21));
    lista.agregar(new Persona("valentino", "lopez", 22100193, 21));
    lista.agregar(new Persona("pedro", "lopez", 22100194, 21));
    lista.agregar(new Persona("valentino", "lopez", 22100195, 21));

    //Menu
    while (true) {
        cout << endl << "Lista circular doble" << endl << endl;
        cout << "a. Agregar nodo" << endl;
        cout << "b. Buscar" << endl;
        cout << "c. Eliminacion" << endl;
        cout << "d. Modificacion" << endl;
        cout << "e. Contar" << endl;
        cout << "f. Mostrar" << endl;
        cout << "g. Iterador" << endl;
        cout << endl << "Ingrese una opcion: ";
        cin >> opcion;

        if (opcion == 'a') {
            string nombre, apellido;
            int registro, edad;
            cout << "Ingrese el nombre: ";
            cin >> nombre;
            cout << "Ingrese el apellido: ";
            cin >> apellido;
            cout << "Ingrese el registro: ";
            cin >> registro;
            cout << "Ingrese la edad: ";
            cin >> edad;
            lista.agregar(new Persona(nombre, apellido, registro, edad));
        }
        if (opcion == 'b') {
            string criterio, valor;
            string resultado;
            cout << "Seleccione el criterio de busqueda (nombre o registro): ";
            cin >> criterio;
            cout << "Ingrese el valor a buscar: ";
            cin >> valor;
            if (lista.buscar(criterio, valor, resultado)) {
                cout << resultado;
            }
            else {
                cout << "Nodo no encontrado" << endl << endl;
            }
        }
        if (opcion == 'c') {
            int registro;
            cout << "Ingrese el numero de registro del nodo a eliminar: ";
            cin >> registro;
            if (lista.eliminar(registro)) {
                cout << "Nodo eliminado exitosamente" << endl << endl;
            }
            else {
                cout << "Nodo no encontrado" << endl << endl;
            }
        }
        if (opcion == 'd') {
            int registro;
            string nombre, apellido;
            int edad;
            cout << "Ingrese el numero de registro del nodo a modificar: ";
            cin >> registro;
            cout << "Ingrese el nuevo nombre: ";
            cin >> nombre;
            cout << "Ingrese el nuevo apellido: ";
            cin >> apellido;
            cout << "Ingrese la nueva edad: ";
            cin >> edad;
            if (lista.modificar(registro, new Persona(nombre, apellido, registro, edad))) {
                cout << "Nodo modificado exitosamente" << endl << endl;
            }
            else {
                cout << "Nodo no encontrado" << endl << endl;
            }
        }
        if (opcion == 'e') {
            cout << "Cantidad de nodos en la lista: " << lista.contar() << endl << endl;
        }
        if (opcion == 'f') {
            Nodo* temp = lista.getInicio();

            if (temp == NULL) {
                cout << "Lista vac�a" << endl;
            }
            else {
                Nodo* actual = temp;
                do {
                    if (actual != NULL) {
                        cout << "Nombre: " << actual->datos->nombre << endl;
                        cout << "Apellido: " << actual->datos->apellido << endl;
                        cout << "Registro: " << actual->datos->registro << endl;
                        cout << "Edad: " << actual->datos->edad << endl;
                        cout << "Direccion del nodo: " << actual << endl;
                        cout << "Direccion del nodo siguiente: " << actual->siguiente << endl;
                    }
                    actual = actual->siguiente;
                } while (actual != temp);
            }
        }
        if (opcion == 'g') {
            //submenu
            char opcionIterador;
            do {
                cout << endl << "Submenu Iterador: " << endl;
                cout << "a. Mostrar" << endl;
                cout << "b. First" << endl;
                cout << "c. Last" << endl;
                cout << "d. Next" << endl;
                cout << "e. Prev" << endl;
                cout << "f. getItem" << endl;
                cout << "g. Volver al menu principal" << endl;
                cout << endl << "Ingrese una opcion: ";
                cin >> opcionIterador;

                if (opcionIterador == 'a') {
                    Nodo* iterador = lista.iterador_getItem();
                    if (iterador != NULL) {
                        cout << "Nodo actual" << endl;
                        cout << "Nombre: " << iterador->datos->nombre << endl;
                        cout << "Apellido: " << iterador->datos->apellido << endl;
                        cout << "Registro: " << iterador->datos->registro << endl;
                        cout << "Edad: " << iterador->datos->edad << endl << endl;
                    }
                    else {
                        cout << "El iterador no apunta a nada" << endl << endl;
                    }
                }
                if (opcionIterador == 'b') {
                    lista.iterador_first();
                    cout << "Iterador movido al primer nodo" << endl << endl;
                }
                if (opcionIterador == 'c') {
                    //lista.iterador_last();
                    cout << "En la lista circular no existe un ultimo nodo" << endl << endl;
                }
                if (opcionIterador == 'd') {
                    lista.iterador_next();
                }
                if (opcionIterador == 'e') {
                    cout << "la lista circular simple, el iterador no puede ir hacia atras";
                    //lista.iterador_prev();
                }
                if (opcionIterador == 'f') {
                    Nodo* nodo_actual = lista.iterador_getItem();
                    if (nodo_actual != NULL) {
                        cout << "Direccion de memoria del nodo actual: " << nodo_actual << endl;
                    }
                    else {
                        cout << "El iterador no apunta a ningun nodo" << endl << endl;
                    }
                }
            } while (opcionIterador != 'g');
        }
    }
    return 0;
}