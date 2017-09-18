#include <iostream>
#include <list>
#include <fstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include "Libro.h"
#include "Evaluador.h"
#include "NodoBinario.h"

using namespace std;

//Escribe todos los datos del libro en un archivo con nombre nombre_archivo en la posicion dada
void escribir(string nombre_archivo, Libro *libro, int posicion)
{
    ofstream out(nombre_archivo.c_str(), ios::in | ios::out | ios::binary);
    if (!out.is_open())
    {
        out.open(nombre_archivo.c_str());
    }

    out.seekp(posicion * 104);
    out.write(libro->nombre.c_str(), 50);
    out.write(libro->autor.c_str(), 50);
    out.write((char *)&libro->existencias, 4);

    out.close();
}

//Devuelve el libro guardado en el archivo en la posicion dada
Libro *leer(string nombre_archivo, int posicion)
{
    char nombre[50];
    char autor[50];
    int existencias;

    ifstream in(nombre_archivo.c_str());
    in.seekg(posicion * 104);

    in.read(nombre, 50);
    in.read(autor, 50);
    in.read((char *)&existencias, 4);

    return new Libro(nombre, autor, existencias);
}

//Crea un mapa en base a las llaves y valores dados, asocia cada llave con los valores en la misma posicion
map<string, int> convertirEnMapa(set<string> llaves, set<int> valores)
{
    std::vector<string> v_llaves;
    std::vector<int> v_valores;

    map<string, int> respuesta;

    std::set<string>::iterator it;
    for (it = llaves.begin(); it != llaves.end(); ++it)
    {
        v_llaves.push_back(*it);
    }

    std::set<int>::iterator iterator;
    for (iterator = valores.begin(); iterator != valores.end(); ++iterator)
    {
        v_valores.push_back(*iterator);
    }

    for(int i = 0; i < llaves.size(); i++)
    {
        respuesta[v_llaves[i]] = v_valores[i];
    }

    return respuesta;
}

//Devuelve una cola con los mismos valores que el parametro exepto que no tiene el ultimo valor
queue<int> popBack(queue<int> cola)
{
    queue<int> respuesta;

    while (cola.size() != 1)
    {
        respuesta.push(cola.front());
        cola.pop();
    }

    return respuesta;
}

//Reemplaza todos los valores del arbol
void reemplazarValores(NodoBinario *raiz, int valor)
{
    if (raiz != NULL)
    {
        raiz->valor = valor;
        reemplazarValores(raiz->izquierdo, valor);
        reemplazarValores(raiz->derecho, valor);
    }
}

//Devuelve la cantidad de bits "encendidos" o con el valores de 1
//00000000
//00001011
int contarBits(char byte)
{
    int cantidad = 0;

    for(int i = 7; 0 <= i; i--)
    {
        if((byte >> i) & 1)
        {
            cantidad++;
        }
    }

    return cantidad;
}

int main()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}
