#ifndef MAX_HEAP_H
#define MAX_HEAP_H
#include "tweet.h"

typedef struct maxHeap 
{
    Tweet** elements;
    int size;
    int capacity;
}MaxHeap;
typedef struct maxHeap* alamat;
boolean isEmpty(alamat maxHeap);
boolean isFullTree(alamat maxHeap);
void heapifyUp(alamat maxHeap, int index);

alamat createMaxHeap(int capacity);

void heapifyDown(alamat maxHeap,int index);

void insertTweet(alamat maxHeap,Tweet tweet);

Tweet* removeMax(alamat maxHeap);

void destroyMaxHeap(alamat maxHeap);

void increaseCapacity(alamat maxHeap);
void showFYB();
#endif