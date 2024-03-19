#include<stdio.h>
#include "dsu.h"

void makeSet(int v, DisjointSet* set){
    set->kelompokTeman[v].parent = v;
    set->kelompokTeman[v].rank = 0;
}
int findSet(int v, DisjointSet set){
    if(v ==set.kelompokTeman[v].parent)return v;
    return set.kelompokTeman[v].parent = findSet(set.kelompokTeman[v].parent,set);
}
void unionSets(int a , int b, DisjointSet *set){
    a= findSet(a,* set);
    b = findSet(b,*set);
    if(a!=b){
        if(set->kelompokTeman[a].rank>=set->kelompokTeman[b].rank){
            set->kelompokTeman[b].parent = a;
            if(set->kelompokTeman[b].rank>0){
            set->kelompokTeman[a].rank +=set->kelompokTeman[b].rank+1;
            }
            else{set->kelompokTeman[a].rank++;
            }
        }else if(set->kelompokTeman[a].rank<set->kelompokTeman[b].rank){
            set->kelompokTeman[a].parent = b;
            if(set->kelompokTeman[a].rank>0){
            set->kelompokTeman[b].rank +=set->kelompokTeman[a].rank+1;
            }
            else{set->kelompokTeman[b].rank++;
            }
        }
    }
}
