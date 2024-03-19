#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"
#include "boolean.h"

void CreateListDin(ListDin* l, int capacity){
    ElType* buff = (ElType*) malloc(sizeof(ElType) * capacity);
    if(!buff) return;

    NEFF(*l) = 0;
    BUFFER(*l) = buff;
    CAPACITY(*l) = capacity;
}

void dealocateList(ListDin* l){
    free(BUFFER(*l));
    NEFF(*l) = 0;
    CAPACITY(*l) = 0;
}

int listLength(ListDin l){
    return NEFF(l);
}

IdxType getFirstIdx(ListDin l){
    return IDX_MIN;
}

IdxType getLastIdx(ListDin l){
    return NEFF(l) - 1;
}

boolean isIdxValid(ListDin l, IdxType i){
    return 0 <= i && i < CAPACITY(l);
}

boolean isIdxEff(ListDin l, IdxType i){
    return 0 <= i && i < NEFF(l);
}

boolean isEmpty(ListDin l){
    return NEFF(l) == 0;
}

boolean isFull(ListDin l){
    return NEFF(l) == CAPACITY(l);
}

void readList(ListDin* l){
    int n;
    do{
        scanf("%d", &n);
    } while(!(0 <= n && n <= CAPACITY(*l)));

    int i;
    for(i = 0; i < n; ++i){
        ElType t;
        scanf("%d", &t);
        insertLast(l, t);
    }
}

/*
void printList(ListDin l){
    printf("[");
    int i;
    for(i = 0; i < NEFF(l); ++i){
        printf("%d", ELMT(l, i));
        if(i != NEFF(l) - 1) printf(",");
    }
    printf("]");
}
*/

ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus){
    int c = CAPACITY(l1), n = NEFF(l1);
    ListDin r;
    CreateListDin(&r, c);

    int i;
    for(i = 0; i < n; ++i){
        ElType t;
        if(plus) t = ELMT(l1, i) + ELMT(l2, i);
        else     t = ELMT(l1, i) - ELMT(l2, i);
        insertLast(&r, t);
    }

    return r;
}

boolean isListEqual(ListDin l1, ListDin l2){
    if(NEFF(l1) != NEFF(l2)) return false;

    int i, n = NEFF(l1);
    for(i = 0; i < n; ++i){
        if(ELMT(l1, i) != ELMT(l2, i)) return false;
    }

    return true;
}

IdxType indexOf(ListDin l, ElType val){
    int i, n = NEFF(l);
    for(i = 0; i < n; ++i){
        if(ELMT(l, i) == val) return i;
    }
    return IDX_UNDEF;
}

void extremeValues(ListDin l, ElType* max, ElType* min){
    int i, n = NEFF(l);
    for(i = 0; i < n; ++i){
        ElType c = ELMT(l, i);
        if(i == 0){
            *max = c;
            *min = c;
        } else {
            if(c > *max) *max = c;
            if(c < *min) *min = c;
        }
    }
}

void copyList(ListDin lIn, ListDin* lOut){
    CreateListDin(lOut, CAPACITY(lIn));

    int i, n = NEFF(lIn);
    for(i = 0; i < n; ++i){
        insertLast(lOut, ELMT(lIn, i));
    }
}

ElType sumList(ListDin l){
    int i, n = NEFF(l), r = 0;
    for(i = 0; i < n; ++i) r += ELMT(l, i);
    return r;
}

int countVal(ListDin l, ElType val){
    int i, n = NEFF(l), c = 0;
    for(i = 0; i < n; ++i) if(ELMT(l, i) == val) ++c;
    return c;
}

void swap(ElType* a, ElType* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(ListDin* l, boolean asc){
    int i, j, s = NEFF(*l);
    for (i = s - 1; i > 0; --i){
        for (j = 0; j < i; ++j){
            if (
                (asc && ELMT(*l, j) > ELMT(*l, j + 1)) ||
                (!asc && ELMT(*l, j) < ELMT(*l, j + 1))
            ) swap(&ELMT(*l, j), &ELMT(*l, j + 1));
        }
    }
}

void insertLast(ListDin* l, ElType val){
    int c = CAPACITY(*l);
    if(isFull(*l)){
        int a = c;
        if(a == 0) a = 1;
        expandList(l, a);
    };

    ELMT(*l, NEFF(*l)) = val;
    ++NEFF(*l);
}

void deleteLast(ListDin* l, ElType* val){
    *val = ELMT(*l, getLastIdx(*l));
    --NEFF(*l);
    if(NEFF(*l) * 2 <= CAPACITY(*l)) shrinkList(l, CAPACITY(*l) / 2);
}

void expandList(ListDin* l, int num){
    int newCapacity = CAPACITY(*l) + num;
    ElType* buff = (ElType*) realloc(BUFFER(*l), sizeof(ElType) * newCapacity);
    if(!buff) return;
    BUFFER(*l) = buff;
    CAPACITY(*l) = newCapacity;
}

void shrinkList(ListDin* l, int num){
    expandList(l, (-1) * num);
}

void compressList(ListDin* l){
    expandList(l, NEFF(*l) - CAPACITY(*l));
}