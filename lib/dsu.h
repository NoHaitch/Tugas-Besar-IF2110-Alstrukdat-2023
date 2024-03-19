#ifndef DSU_h
#define DSU_h
#include "user.h"
typedef struct 

{
    int parent;
    int rank;
}ElmtSet;
typedef struct
{
    /* data */ElmtSet kelompokTeman[MAX_USER];
}DisjointSet;

void makeSet(int v, DisjointSet* set);
int findSet(int v, DisjointSet set);
void unionSets(int a , int b, DisjointSet *set);


#endif 