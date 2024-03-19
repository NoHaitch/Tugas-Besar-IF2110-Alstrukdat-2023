#include <stdio.h>
#include "liststatik.h"

void CreateListStatik(ListStatik *l){
    int i;
    for(i = 0; i < CAPACITY; ++i){
        ELMT(*l, i) = MARK;
    }
}

int listLength(ListStatik l){
    int i = 0;
    while(ELMT(l, i) != MARK && i < CAPACITY) ++i;
    return i;
}

IdxType getFirstIdx(ListStatik l){
    return 0;
}

IdxType getLastIdx(ListStatik l){
    return listLength(l) - 1;
}

boolean isIdxValid(ListStatik l, IdxType i){
    return 0 <= i && i < CAPACITY;
}

boolean isIdxEff(ListStatik l, IdxType i){
    return getFirstIdx(l) <= i && i <= getLastIdx(l);
}

boolean isEmpty(ListStatik l){
    return listLength(l) == 0;
}

boolean isFull(ListStatik l){
    return listLength(l) == CAPACITY;
}

void readList(ListStatik* l){
    int n;
    do{
        scanf("%d", &n);
    } while (!(0 <= n && n <= CAPACITY));

    CreateListStatik(l);

    int i, t;
    for(i = 0; i < n; ++i){
        scanf("%d", &t);
        insertLast(l, t);
    }
}

void printList(ListStatik l){
    int i, s = listLength(l);
    printf("[");
    for(i = 0; i < s; ++i){
        printf("%d", ELMT(l, i));
        if(i != s - 1) printf(",");
    }
    printf("]");
}

ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus){
    ListStatik l;
    CreateListStatik(&l);

    int i, s = listLength(l1);
    if(plus) for(i = 0; i < s; ++i) ELMT(l, i) = ELMT(l1, i) + ELMT(l2, i);
    else for(i = 0; i < s; ++i) ELMT(l, i) = ELMT(l1, i) - ELMT(l2, i);

    return l;
}

boolean isListEqual(ListStatik l1, ListStatik l2){
    if(listLength(l1) != listLength(l2)) return false;

    int i, s = listLength(l1);
    for(i = 0; i < s; ++i) if(ELMT(l1, i) != ELMT(l2, i)) return false;
    return true;
}

int indexOf(ListStatik l, ElType val){
    int i, s = listLength(l);
    for(i = 0; i < s; ++i) if(ELMT(l, i) == val) return i;
    return IDX_UNDEF;
}

void extremeValues(ListStatik l, ElType* max, ElType* min){
    int i, s = listLength(l);
    for(i = 0; i < s; ++i){
        if(i == 0){
            *min = ELMT(l, 0);
            *max = ELMT(l, 0);
        }

        ElType c = ELMT(l, i);
        if(c < *min) *min = c;
        if(c > *max) *max = c;
    }
}

void insertAt(ListStatik* l, ElType val, IdxType idx){
    int i, s = listLength(*l);
    for(i = s; i > idx; --i){
        ELMT(*l, i) = ELMT(*l, i - 1);
    }
    ELMT(*l, idx) = val;
}

void insertFirst(ListStatik* l, ElType val){
    insertAt(l, val, 0);
}

void insertLast(ListStatik* l, ElType val){
    ELMT(*l, listLength(*l)) = val;
}

void deleteAt(ListStatik* l, ElType* val, IdxType idx){
    *val = ELMT(*l, idx);

    int i, s = listLength(*l);
    for(i = idx; i < s; ++i){
        ELMT(*l, i) = ELMT(*l, i + 1);
    }
    ELMT(*l, s - 1) = MARK;
}

void deleteFirst(ListStatik* l, ElType* val){
    deleteAt(l, val, 0);
}

void deleteLast(ListStatik* l, ElType* val){
    deleteAt(l, val, listLength(*l) - 1);
}

void swap(ElType* a, ElType* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortList(ListStatik *l, boolean asc){
    int i, j, s = listLength(*l);
    for(i = s - 1; i > 0; --i){
        for(j = 0; j < i; ++j){
            if(
                ( asc && ELMT(*l, j) > ELMT(*l, j + 1)) ||
                (!asc && ELMT(*l, j) < ELMT(*l, j + 1))
            ){
                swap(&ELMT(*l, j), &ELMT(*l, j + 1));
            }
        }
    }
}