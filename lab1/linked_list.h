#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_


struct Node {
    char *key;
    int value;
    struct Node *next;
};

typedef struct Node* List;

int init(List* l);
int set(List* l, char* key, int value);
int get(List l, char* key, int* value);
int printList(List l);
int deleteNode(List* l, char* key);
int destroy(List* l);

#endif