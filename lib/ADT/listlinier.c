#include <stdlib.h>
#include <stdio.h>
#include "listlinier.h"

Address newNode(ElType val){
    Address address = (Address) malloc(sizeof(Node));
    (*address).info = val;
    (*address).next = NULL;
    return address;
}

void CreateList(List* l){
    (*l) = NULL;
}

boolean isEmpty(List l){
    return l == NULL;
}

Address getNode(Address start, int idx){
    int i = 0;
    Address curr = start;
    while(i < idx && curr != NULL){
        curr = curr->next;
        ++i;
    }
    return curr;
}

ElType getElmt(List l, int idx){
    Address t = getNode(l, idx);
    return t->info;
}

void setElmt(List* l, int idx, ElType val){
    Address t = getNode(*l, idx);
    t->info = val;
}

int indexOf(List l, ElType val){
    int r = IDX_UNDEF;
    int i = 0;
    Address curr = l;
    while(curr != NULL && r == IDX_UNDEF){
        if(curr->info == val) r = i;
        curr = curr->next; ++i;
    }

    return r;
}

void insertAt(List* l, ElType val, int idx){
    Address n = newNode(val);
    if(idx == 0){
        n->next = (*l);
        (*l) = n;
    } else {
        Address t = getNode(*l, idx - 1);

        n->next = t->next;
        t->next = n;
    }
}

void insertFirst(List* l, ElType val){
    insertAt(l, val, 0);
}

void insertLast(List* l, ElType val){
    insertAt(l, val, length(*l));
}

void deleteAt(List* l, int idx, ElType* val){
    if(idx == 0){
        Address n = (*l);
        (*val) = n->info;
        (*l) = (**l).next;
        free(n);
    } else {
        Address p = getNode(*l, idx - 1);
        Address n = (*p).next;
        (*val) = n->info;
        p->next = n->next;
        free(n);
    }
}

void deleteFirst(List* l, ElType *val){
    deleteAt(l, 0, val);
}

void deleteLast(List* l, ElType *val){
    deleteAt(l, length(*l) - 1, val);
}

void displayList(List l){
    printf("[");
    Address curr = l;
    while(curr != NULL){
        printf("%d", curr->info);
        curr = curr->next;
        if(curr != NULL) printf(",");
    }
    printf("]");
}

int length(List l){
    int i = 0;
    Address curr = l;
    while(curr != NULL){
        curr = curr->next; ++i;
    };
    return i;
}

List concat(List l1, List l2){
    List l3;
    CreateList(&l3);

    Address curr = l1;
    while(curr != NULL){
        insertLast(&l3, curr->info);
        curr = curr->next;
    };

    curr = l2;
    while(curr != NULL){
        insertLast(&l3, curr->info);
        curr = curr->next;
    }

    return l3;
}