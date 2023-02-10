#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


/*
Todas estas funciones devuelve 0 si se ejecutan con éxito y -1 en caso de algún error.
Cada vez que se inserta un elemento en la lista hay que reservar memoria dinámica para almacenar el nuevo elemento:
    struct Node *ptr = (struct Node *) malloc(sizeof(struct Node));
*/


int init(List *l) {
    /*
    Inicializa una lista como lista vacía. 
    Una lista vacía es una lista que apunta a NULL.
    */
    *l = NULL;
    return 0;
}


int set(List *l, char *key , int value ){
    /*
    Inserta un nuevo par en la lista.
    La inserción se hace al principio de la lista.
    */

    struct Node *ptr;
    ptr = (struct Node *) malloc(sizeof(struct Node));  // new element
    if (ptr == NULL) return -1;
    if (*l == NULL) {  // emtpy list
        strcpy (ptr->key, key);
        ptr->value = value;
        ptr-> next = NULL;
        *l = ptr;
    }
    else {
        // insert in head
        strcpy(ptr->key, key);
        ptr->value = value;
        ptr->next = *l;
        *l = ptr;
    }
    return 0;
}


int get(List l, char *key, int * value) {
    /*
    Obtiene el valor asociado a una clave.
    Busca en la lista el para cuya clave coincida con key y devuelve el valor asociado en el argumento value.
    */

    List aux;
    aux = l;
    while (aux != NULL) {
        if (strcmp (aux->key, key) == 0) {
            *value = aux->value;
            return 0;  // found
        } else {
            aux = aux->next;  // next element
        }
    }
    return -1;  // not found
}


int printList(List l) {
    /*
    Recorre todos los elementos de la lista e imprime por cada uno su clave y valor.
    */

    List aux;
    aux = l;
    while (aux != NULL) {
        printf("Key= %s value= %d\n", aux->key, aux->value);
        aux = aux->next;
    }
    return 0;
}

int deleteNode(List *l, char *key) {
    /*
    Elimina un par de la lista.
    */

    List aux, back;
    if (*l == NULL)  // lista vacia
        return 0;
    
    // primer elemento de la lista
    if (strcmp(key, (*l)->key) == 0) {
        aux = *l;
        *l = (*l)->next;
        free(aux);
        return 0;
    }

    aux = *l;
    back = *l;
    while (aux != NULL) {
        if (strcmp(aux->key, key) == 0) {
            back->next = aux->next;
            free(aux);
            return 0;  // found
        }
        else {
            back = aux;
            aux = aux->next;
        }
    }
    return 0;
}


int destroy ( List *l) {
    /*
    Elimina todos los elementos de la lista.
    */

    List aux;
    while (*l != NULL ) {
        aux = *l;
        *l = aux->next;
        free(aux);
    }
    return 0;
}

