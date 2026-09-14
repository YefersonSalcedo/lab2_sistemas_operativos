/*
 * Laboratorio 2 - Sistemas Operativos - Universidad de Antioquia
 *
 * Autores: Yeferson Alexis Salcedo Preciado
 *          Jhoan Esteban Echeverri Villa
 *
 * Manipulacion de cadenas usando UNICAMENTE punteros (sin strrev(),
 * sin arreglos auxiliares para invertir; todo se modifica in-place).
 */

#include <iostream>
#include <cctype>   // isalpha, tolower

using namespace std;

const int MAX_LEN = 100;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " \"cadena a procesar\"" << endl;
        return 1;
    }

    // ---------------------------------------------------------------
    // PASO 0: copiamos el argumento a un arreglo propio de tamano fijo.
    // 'buffer' es el UNICO arreglo que usamos durante todo el programa:
    // filtramos, invertimos y modificamos siempre encima de el, nunca
    // creamos un arreglo nuevo.
    // ---------------------------------------------------------------
    char buffer[MAX_LEN + 1];
    int i = 0;
    while (argv[1][i] != '\0' && i < MAX_LEN) {
        buffer[i] = argv[1][i];
        i++;
    }
    buffer[i] = '\0';


    // PASO 1: filtrar caracteres no alfabeticos (se conservan letras
    // y espacios) con la tecnica de "dos punteros sobre el mismo
    // arreglo": un puntero de LECTURA que siempre avanza, y un
    // puntero de ESCRITURA que solo avanza cuando de verdad guarda
    // algo. Como p_write nunca adelanta a p_read, podemos escribir
    // "encima" del mismo arreglo sin pisar datos que aun no hemos
    // leido. Asi se filtra la cadena SIN usar memoria adicional.

    char* p_read  = buffer;   // recorre TODO el arreglo original
    char* p_write = buffer;   // marca donde va el siguiente char valido

    while (*p_read != '\0') {              // *p_read = "el caracter al que apunta p_read"
        if (isalpha((unsigned char)*p_read) || *p_read == ' ') {
            *p_write = *p_read;            // copiamos el caracter valido
            p_write++;                     // el puntero de escritura solo avanza aqui
        }
        p_read++;                          // el puntero de lectura SIEMPRE avanza
    }
    *p_write = '\0';                       // cerramos la cadena filtrada
    int len = p_write - buffer;            // resta de punteros = longitud:
                                            // "distancia" entre el inicio y
                                            // donde quedo apuntando p_write

    // Caso borde: cadena vacia o sin ningun caracter alfabetico.
    if (len == 0) {
        cout << "(vacia) 0 0 (vacia)" << endl;
        return 0;
    }

    
    // PASO 2: invertir la cadena IN PLACE con dos punteros que se
    // acercan desde los extremos ("two pointers converging").
    // 'inicio' arranca en la primera posicion de memoria del arreglo;
    // 'fin' arranca en la ULTIMA posicion valida (buffer + len - 1,
    // aritmetica de punteros: nos movemos len-1 casillas desde el
    // inicio). En cada vuelta intercambiamos *inicio con *fin, y
    // movemos cada puntero un paso hacia el centro (inicio++ avanza,
    // fin-- retrocede) hasta que se cruzan. No se reserva NINGUN
    // arreglo nuevo: solo se intercambian valores dentro del mismo
    // bloque de memoria.
    {
        char* inicio = buffer;
        char* fin    = buffer + len - 1;
        while (inicio < fin) {
            char temp = *inicio;
            *inicio = *fin;
            *fin    = temp;
            inicio++;
            fin--;
        }
    }
    string reversed(buffer, len);   // copia de texto para imprimir luego


    // PASO 3: contar vocales y consonantes recorriendo el arreglo con
    // UN SOLO puntero 'p' que avanza caracter por caracter (p++).
    // El orden no importa para contar (ya esta invertida, pero contar
    // da lo mismo en cualquier orden).
    int countA = 0, countE = 0, countI = 0, countO = 0, countU = 0, consonantes = 0;

    char* p = buffer;
    while (*p != '\0') {
        if (*p != ' ') {
            char c = tolower((unsigned char)*p);   // normalizamos mayus/minus
            switch (c) {
                case 'a': countA++; break;
                case 'e': countE++; break;
                case 'i': countI++; break;
                case 'o': countO++; break;
                case 'u': countU++; break;
                default: consonantes++; break;
            }
        }
        p++;   // el puntero se mueve a la siguiente casilla de memoria
    }
    int totalVocales = countA + countE + countI + countO + countU;

    
    // PASO 4: reemplazar espacios por guiones bajos, otra vez con UN
    // SOLO puntero que recorre el arreglo y ESCRIBE directamente
    // sobre la memoria a la que apunta (*p2 = '_'). No se crea una
    // cadena nueva: se modifica 'buffer' en su propio lugar.
    char* p2 = buffer;
    while (*p2 != '\0') {
        if (*p2 == ' ') {
            *p2 = '_';
        }
        p2++;
    }
    string modified(buffer, len);

    
    // Salida: total de vocales, luego SOLO los conteos de las vocales
    // que realmente aparecen (en orden a-e-i-o-u), luego consonantes.
    cout << reversed << " " << totalVocales;
    if (countA > 0) cout << " " << countA;
    if (countE > 0) cout << " " << countE;
    if (countI > 0) cout << " " << countI;
    if (countO > 0) cout << " " << countO;
    if (countU > 0) cout << " " << countU;
    cout << " " << consonantes << " " << modified << endl;

    return 0;
}