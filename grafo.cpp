/*
Bañuelos Leo Yahir Alejandro
218576376
IA 1
MODULO 1, CLASE 2, GRAFO 23-08-23
*/

#include <iostream>
#include <unistd.h>

class Arista;

class Nodo
{
public:
    std::string nombre;
    Nodo* siguiente;
    Arista* adyacenciaH;

    Nodo(){
        nombre = "";
        siguiente = nullptr;
        adyacenciaH = nullptr;
    }
    Nodo(char nombre){
        this->nombre = nombre; 
        siguiente = nullptr;
        adyacenciaH = nullptr;
    }
};

class Arista
{
public:
    Nodo* origen;
    Nodo* destino;
    Arista* siguiente;

    Arista(){
        origen = nullptr;
        destino = nullptr;
        siguiente = nullptr;
    }

    Arista(Nodo* origen, Nodo* destino){
        this->origen = origen;
        this->destino = destino;
        siguiente = nullptr;
    }
};

class Grafo
{
public:
    Nodo* header;
    Grafo(){
        header = nullptr;
    }

    Nodo* buscarNodo(std::string nombre){
        Nodo* aux = header;
        while(aux != nullptr){
                if(nombre == aux->nombre){
                    return aux;
                }
                aux = aux->siguiente;
        }
        return nullptr;
    }

    void insertarNodo(Nodo* nodo){
        if(!header){
            header = nodo;
        }else{
            Nodo* aux = header;
            while(aux->siguiente != nullptr){
                aux = aux->siguiente;
            }
            aux->siguiente = nodo;
        }
    }

    void eliminarNodo(std::string nombre){
        Nodo* aux = header;
        Nodo* auxAnterior = aux;
        while(aux != nullptr){
            Arista* auxArista = aux->adyacenciaH;
            Arista* auxAristaAnterior = auxArista;
            while(auxArista != nullptr){
                if((auxArista->siguiente == nullptr) && (auxArista->destino->nombre == nombre) && (auxArista != aux->adyacenciaH)){
                    auxAristaAnterior->siguiente = auxArista->siguiente;
                    //delete auxArista;
                }else if(auxArista->destino->nombre == nombre && auxArista == aux->adyacenciaH){
                    aux->adyacenciaH = aux->adyacenciaH->siguiente;
                    //delete auxArista;
                }else if(auxArista->destino->nombre == nombre){
                    auxAristaAnterior->siguiente = auxArista->siguiente;
                    //delete auxArista;
                }
                
                auxAristaAnterior = auxArista;
                auxArista = auxArista->siguiente;
            }
            if((aux->siguiente == nullptr) && (aux->nombre == nombre) && (aux != header)){
                auxAnterior->siguiente = aux->siguiente;
            }else if(aux->nombre == nombre && aux == header){
                header = header->siguiente;
            }else if(aux->nombre == nombre){
                auxAnterior->siguiente = aux->siguiente;
            }
            
            auxAnterior = aux;
            aux = aux->siguiente;
        }
    }

    void eliminarArista(std::string origen, std::string destino){
        Nodo* aux = header;
        Nodo* auxAnterior = aux;
        while(aux){
            Arista* auxArista = aux->adyacenciaH;
            Arista* auxAristaAnterior = auxArista;
            while(auxArista){
                if((auxArista->siguiente == nullptr) && (auxArista != aux->adyacenciaH) && ((auxArista->origen->nombre == origen) && (auxArista->destino->nombre == destino))){
                    auxAristaAnterior->siguiente = auxArista->siguiente;
                    //delete auxArista;
                }else if(((auxArista->origen->nombre == origen) && (auxArista->destino->nombre == destino)) && auxArista == aux->adyacenciaH){
                    aux->adyacenciaH = aux->adyacenciaH->siguiente;
                    //delete auxArista;
                }else if(auxArista->origen->nombre == origen && auxArista->destino->nombre == destino){
                    auxAristaAnterior->siguiente = auxArista->siguiente;
                    //delete auxArista;
                }
                auxAristaAnterior = auxArista;
                auxArista = auxArista->siguiente;
            }
            auxAnterior = aux;
            aux = aux->siguiente;
        }
    }

    void insertarArista(Arista* arista){
        if(!buscarNodo(arista->origen->nombre)){
            std::cout<<"NO EXISTE ORIGEN"<<std::endl;
        }
        if(!buscarNodo(arista->destino->nombre)){
            std::cout<<"NO EXISTE EL DESTINO"<<std::endl;
        }
        
        Nodo* encontrado = buscarNodo(arista->origen->nombre);
        if(!encontrado->adyacenciaH){
            encontrado->adyacenciaH = arista;
        }else{
            Arista* aux = encontrado->adyacenciaH;
            while(aux->siguiente != nullptr){
                aux = aux->siguiente;
            }
            aux->siguiente = arista;
        }     
    }

    void mostrarGrafo(void){
        Nodo* aux = header;
        std::cout<<"NODOS \t|LISTAS DE ADYACENCIA"<<std::endl;
        std::cout<<"--------+--------------------"<<std::endl;
        while(aux){
            Arista* auxArista = aux->adyacenciaH;
            std::cout<<aux->nombre + "\t|";
            while(auxArista){
                std::cout<<auxArista->destino->nombre + " ";
                auxArista = auxArista->siguiente;
            }
            aux = aux->siguiente;
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

    void mostrarAristas(void){
        Nodo* aux = header;
        std::cout<<"ORIGEN\t\tDESTINO"<<std::endl;
        while(aux){
            Arista* auxArista = aux->adyacenciaH;
            while(auxArista){
                std::cout<<auxArista->origen->nombre<<" ------------> "<<auxArista->destino->nombre<<std::endl;
                auxArista = auxArista->siguiente;
            }
            aux = aux->siguiente;
        }
    }

    int tamanio(void){
        int cont = 0;
        Nodo* aux = header;
        while(aux){
            cont++;
            aux = aux->siguiente;
        }
        return cont;
    }

    bool conectado(std::string origen, std::string destino){
        Nodo* encontrado = buscarNodo(origen);
        if(!encontrado){
            std::cout<<"NO EXISTE EL ORIGEN"<<std::endl;
            return false;
        }else{
            Arista* auxArista = encontrado->adyacenciaH;
            while (auxArista){
                if(auxArista->destino->nombre == destino){
                    return true;
                }
                auxArista = auxArista->siguiente;
            }
            return false;
        }
    }

    void mostrarMatrizAdyacencia(void){
        Nodo* aux = header;
        Nodo* auxImpr = header;
        Nodo* auxImpr2 = header;
        int auxCont = 0;
        int matriz[tamanio()][tamanio()];

        for(int i = 0; i < tamanio(); i++){
            for(int j = 0; j < tamanio(); j++){
                matriz[i][j] = 0;
            }
        }

        std::cout<<"\nMATRIZ DE ADYACENCIA\n"<<std::endl;

        std::cout<<"  ";

        while(auxImpr){
            std::cout<<auxImpr->nombre<<" ";

            auxImpr = auxImpr->siguiente;
        }

        std::cout<<std::endl;

        while(aux){
            Nodo* aux2 = header;
            int aux2Cont = 0;
            std::cout<<aux->nombre<<"|";
            while(aux2){
                if(conectado(aux->nombre, aux2->nombre)){
                    matriz[auxCont][aux2Cont] = 1;
                }else{
                    matriz[auxCont][aux2Cont] = 0;
                }
                std::cout<<matriz[auxCont][aux2Cont]<<" ";
                aux2 = aux2->siguiente;
                aux2Cont++;
            }
            std::cout<<std::endl;
            aux = aux->siguiente;
            auxCont++;
        }
    }
};
 
int main(){
    Grafo* a = new Grafo;

    /*Nodo* nodoa = new Nodo;
    nodoa->nombre = "A";

    Nodo* nodob = new Nodo;
    nodob->nombre = "B";

    Nodo* nodoc = new Nodo;
    nodoc->nombre = "C";

    Nodo* nodod = new Nodo;
    nodod->nombre = "D";

    a->insertarNodo(nodoa);
    a->insertarNodo(nodob);
    a->insertarNodo(nodoc);
    a->insertarNodo(nodod);

    Arista* arista0 = new Arista;
    arista0->origen = a->buscarNodo("A");
    arista0->destino = a->buscarNodo("B");

    Arista* arista1 = new Arista;
    arista1->origen = a->buscarNodo("A");
    arista1->destino = a->buscarNodo("A");

    Arista* arista2 = new Arista;
    arista2->origen = a->buscarNodo("B");
    arista2->destino = a->buscarNodo("A");

    Arista* arista3 = new Arista;
    arista3->origen = a->buscarNodo("C");
    arista3->destino = a->buscarNodo("B");

    a->insertarArista(arista0);
    a->insertarArista(arista1);
    a->insertarArista(arista2);
    a->insertarArista(arista3);

    a->mostrarGrafo();

    a->mostrarMatrizAdyacencia();*/
    int opc = 0;

    while(opc != 8){
        system("cls");
        std::cout<<"\n\t GRAFOS DIRIGIDO \n\n";
        std::cout<<" 1. INSERTAR UN NODO "<<std::endl;
        std::cout<<" 2. INSERTAR UNA ARISTA "<<std::endl;
        std::cout<<" 3. ELIMINAR UN NODO "<<std::endl;
        std::cout<<" 4. ELIMINAR UNA ARISTA "<<std::endl;
        std::cout<<" 5. MOSTRAR GRAFO "<<std::endl;
        std::cout<<" 6. MOSTRAR ARISTAS DE UN NODO "<<std::endl;
        std::cout<<" 7. MOSTRAR MATRIZ DE ADYACENCIA "<<std::endl;
        std::cout<<" 8. SALIR "<<std::endl;
        std::cout<<"\n INGRESE OPCION: ";
        std::cin>>opc;

        switch(opc)
        {
        case 1: {
            system("cls");
            std::string nombre;
            std::cout<<"INGRESA NOMBRE DEL NODO: ";
            std::cin>>nombre;
            Nodo* nodo = new Nodo;
            nodo->nombre = nombre;

            a->insertarNodo(nodo);
            break;
        }

        case 2: {
            system("cls");
            std::string origen, destino;
            std::cout<<"INGRESA ORIGEN DE LA ARISTA: ";
            std::cin>>origen;
            std::cout<<"INGRESA DESTINO DE LA ARISTA: ";
            std::cin>>destino;
            Arista* arista = new Arista;
            arista->origen = a->buscarNodo(origen);
            arista->destino = a->buscarNodo(destino);

            a->insertarArista(arista); 
            break;
        }

        case 3: {
            system("cls");
            std::string nombre;
            std::cout<<"INGRESA NOMBRE DEL NODO A ELIMINAR: ";
            std::cin>>nombre;

            a->eliminarNodo(nombre); 
            break;
        }

        case 4: {
            system("cls");
            std::string origen, destino;
            std::cout<<"INGRESA ORIGEN DE LA ARISTA A ELIMINAR: ";
            std::cin>>origen;
            std::cout<<"INGRESA DESTINO DE LA ARISTA A ELIMINAR: ";
            std::cin>>destino;

            a->eliminarArista(origen, destino); 
            break;
        }

        case 5: {
            a->mostrarGrafo();
            sleep(5); 
            break;
        }

        case 6: {
            a->mostrarAristas(); 
            sleep(5); 
            break;
        }

        case 7: {
            a->mostrarMatrizAdyacencia(); 
            sleep(5);
            break;
        }

        default: std::cout<<"OPCION NO VALIDA"; break;
        }
    }


    return 0;
} 