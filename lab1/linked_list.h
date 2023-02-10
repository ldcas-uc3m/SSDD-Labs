#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

const unsigned int MAX_KEY_LENGTH = 8;

struct Node {
    char key[MAX_KEY_LENGTH];
    int value;
    struct Node * next;
};

typedef struct Node * List;
int init(List *l);
int set(List *l, char *key, int value);
int get(List l, char *key, int * value);
int printList(List l);
int delete_list(List *l, char *key);
int destroy(List *l);

#endif