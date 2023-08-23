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
        while(aux){
            Arista* auxArista = aux->adyacenciaH;
            while(auxArista){
                std::cout<<auxArista->origen->nombre<<" ------------> "<<auxArista->destino->nombre<<std::endl;
                auxArista = auxArista->siguiente;
            }
            aux = aux->siguiente;
        }
    }
};
 
int main(){
    /*Grafo* a = new Grafo;
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
    aris->destino = d;

    Arista* aris3 = new Arista;
    aris3->origen = b;
    aris3->destino = c;

    Arista* aris5 = new Arista;
    aris5->origen = b;
    aris5->destino = b;

    Arista* aris4 = new Arista;
    aris4->origen = b;
    aris4->destino = b;

    Arista* aris2 = new Arista;
    aris2->origen = c;
    aris2->destino = b;

    Arista* aris6 = new Arista;
    aris6->origen = c;
    aris6->destino = d;

    Arista* aris7 = new Arista;
    aris7->origen = d;
    aris7->destino = d; 

    a->insertarArista(aris4);
    a->insertarArista(aris);
    a->insertarArista(aris3);
    a->insertarArista(aris2);
    a->insertarArista(aris5);
    a->insertarArista(aris6);
    a->insertarArista(aris7);
    

    a->mostrarAristas();*/
    int opc = 0;

    while(opc != 7){
        system("cls");
        std::cout<<"\n\t GRAFOS DIRIGIDO \n\n";
        std::cout<<" 1. INSERTAR UN NODO "<<std::endl;
        std::cout<<" 2. INSERTAR UNA ARISTA "<<std::endl;
        std::cout<<" 3. ELIMINAR UN NODO "<<std::endl;
        std::cout<<" 4. ELIMINAR UNA ARISTA "<<std::endl;
        std::cout<<" 5. MOSTRAR GRAFO "<<std::endl;
        std::cout<<" 6. MOSTRAR ARISTAS DE UN NODO "<<std::endl;
        std::cout<<" 7. SALIR "<<std::endl;
        std::cout<<"\n INGRESE OPCION: ";
        std::cin>>opc;
    }


    return 0;
} 