#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


/*
Todas estas funciones devuelve 0 si se ejecutan con éxito y -1 en caso de algún error.
*/


int init(List* l) {
    /*
    Inicializa una lista como lista vacía. 
    Una lista vacía es una lista que apunta a NULL.
    */
   
    *l = NULL;

    return 0;
}


int set(List* l, char* key, int value){
    /*
    Inserta un nuevo par (key, value) en la lista l.
    La inserción se hace al principio de la lista.
    No comprueba si hay keys repetidas.
    */

    struct Node* ptr;
    ptr = (struct Node*) malloc(sizeof(struct Node));  // new element
    
    if (ptr == NULL) {
        perror("malloc() fail\n");
        return -1;
    }

    // allocate memory for key
    ptr->key = (char*) malloc(strlen(key) + 1);  // new string
    if (ptr->key == NULL) {  // failed allocation
        free(ptr);
        perror("malloc() fail\n");
        return -1;
    }

    if (*l == NULL) {  // emtpy list
        strcpy(ptr->key, key);
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


int get(List l, char* key, int* value) {
    /*
    Obtiene el valor asociado a una clave key en la lista l, y lo guarda en el argumento value.
    */

    List aux = l;  // head

    // traverse the list 
    while (aux != NULL) {
        if (strcmp(aux->key, key) == 0) {  // found
            *value = aux->value;

            return 0;  
        } else {  // next element
            aux = aux->next;
        }
    }
    perror("Element not found\n");
    return -1;  // not found
}


int printList(List l) {
    /*
    Recorre todos los elementos de la lista l e imprime por cada uno su clave y valor.
    */

    List aux = l;

    printf("[");
    while (aux != NULL) {
        printf("(%s, %d)", aux->key, aux->value);
        aux = aux->next;
        if (aux != NULL)
            printf(", ");
    }
    printf("]\n");

    return 0;
}


int deleteNode(List* l, char* key) {
    /*
    Elimina un par de la lista l, identificado por su clave key.
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

    // resto de elementos
    while (aux != NULL) {
        if (strcmp(aux->key, key) == 0) {  // found
            back->next = aux->next;
            free(aux);

            return 0;  
        }
        else {
            back = aux;
            aux = aux->next;
        }
    }
    perror("Element not found\n");
    return -1;  // not found
}


int destroy(List* l) {
    /*
    Elimina todos los elementos de la lista l.
    */

    List aux;

    while (*l != NULL) {
        aux = *l;
        *l = aux->next;
        free(aux);
    }
    return 0;
}
