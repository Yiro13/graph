#include <iostream>
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
            std::cout<<"PRIMER NODO"<<std::endl;
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
                
                auxAristaAnterior = auxArista;
                auxArista = auxArista->siguiente;
            }
            
            auxAnterior = aux;
            aux = aux->siguiente;
        }
    }

    void eliminarArista(std::string origen, std::string destino){

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
            std::cout<<"PRIMER ARISTA"<<std::endl; 
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
    }
};
 
int main(){
    Grafo* a = new Grafo;
    Nodo* b = new Nodo();
    b->nombre = "A";
    Nodo* c = new Nodo();
    c->nombre = "B";
    Nodo* d = new Nodo();
    d->nombre = "C";

    a->insertarNodo(b);
    a->insertarNodo(c);
    a->insertarNodo(d);

    Arista* aris = new Arista;
    aris->origen = b;
    aris->destino = c;

    Arista* aris2 = new Arista;
    aris2->origen = c;
    aris2->destino = b;

    a->insertarArista(aris);
    a->insertarArista(aris2);
    a->mostrarGrafo();
    a->eliminarNodo("A");

    a->mostrarGrafo();


    return 0;
} 