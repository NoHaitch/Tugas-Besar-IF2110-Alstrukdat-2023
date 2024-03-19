
#include<stdio.h>
#include <stdlib.h>

#include "max_heap.h"
#include "string.h"

alamat createMaxHeap(int capacity) {
    alamat maxHeap = (alamat)malloc(sizeof(MaxHeap));
    if (maxHeap == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed for maxHeap\n");
        exit(EXIT_FAILURE);
    }

    maxHeap->elements = (Tweet**)malloc(capacity * sizeof(Tweet*));
    if (maxHeap->elements == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed for maxHeap->elements\n");
        free(maxHeap);  // Free previously allocated memory
        exit(EXIT_FAILURE);
    }

    maxHeap->size = 0;
    maxHeap->capacity = capacity;

    return maxHeap;
}

void insertTweet(alamat maxHeap, Tweet tweet) {
    if (isFullTree(maxHeap)) {
        increaseCapacity(maxHeap);
    }

    // Allocate memory for the new tweet
    maxHeap->elements[maxHeap->size] = (Tweet*)malloc(sizeof(Tweet));
    if (maxHeap->elements[maxHeap->size] == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Memory allocation failed for maxHeap->elements[%d]\n", maxHeap->size);
        exit(EXIT_FAILURE);
    }

    // Assign values to the new tweet
    maxHeap->elements[maxHeap->size]->like = tweet.like;
    maxHeap->elements[maxHeap->size]->id = tweet.id;
    maxHeap->elements[maxHeap->size]->author = tweet.author;
    string_copy(tweet.dateTime, maxHeap->elements[maxHeap->size]->dateTime, 20);
    // maxHeap->elements[maxHeap->size]->dateTime = tweet.dateTime;

    // Increment size
    maxHeap->size++;

    // Perform heapifyUp to ensure heap property is maintained
    heapifyUp(maxHeap, maxHeap->size - 1);
}

boolean isEmpty(alamat maxHeap){
    return maxHeap->size == 0;
}
Tweet* removeMax(alamat maxHeap) {
    if (isEmpty(maxHeap)) {
        // Heap kosong, tidak ada yang dihapus
        return NULL ;
    }
    // Simpan elemen maksimum untuk dikembalikan
    Tweet* maxElement = maxHeap->elements[0];
    // Pindahkan elemen terakhir ke posisi root
    maxHeap->elements[0] = maxHeap->elements[maxHeap->size - 1];
    // Kurangi ukuran heap
    maxHeap->size--;
    // Lakukan proses heapifyDown untuk memastikan properti heap terjaga
    heapifyDown(maxHeap, 0);

    return maxElement;
}

boolean isFullTree(alamat maxHeap){
    return maxHeap->size == maxHeap->capacity;
}
int getParentIndex(int index){
    return index/2;
}
int getLeftChildIndex(int index){
    return index*2+1;
}
int getRightChildIndex(int index){
    return (index+1)*2;
}
void swap(Tweet **a, Tweet **b){
    Tweet* temp =*a;
    *a =*b;
    *b = temp;
}
void destroyMaxHeap(alamat maxHeap){
    free(maxHeap->elements);
    free(maxHeap);
}

void heapifyDown(alamat maxHeap, int index) {
    int largest = index;
    int left = getLeftChildIndex(index);
    int right = getRightChildIndex(index);

    // Check if left child exists and is greater than the largest
    if (left < maxHeap->size &&
        (maxHeap->elements[left]->like > maxHeap->elements[largest]->like ||
         (maxHeap->elements[left]->like == maxHeap->elements[largest]->like &&
          maxHeap->elements[left]->id < maxHeap->elements[largest]->id))) {
        largest = left;
    }

    // Check if right child exists and is greater than the largest
    if (right < maxHeap->size &&
        (maxHeap->elements[right]->like > maxHeap->elements[largest]->like ||
         (maxHeap->elements[right]->like == maxHeap->elements[largest]->like &&
          maxHeap->elements[right]->id < maxHeap->elements[largest]->id))) {
        largest = right;
    }

    // Swap and recursively heapify down if needed
    if (largest != index) {
        swap(&maxHeap->elements[index], &maxHeap->elements[largest]);
        heapifyDown(maxHeap, largest);
    }
}


void heapifyUp(alamat maxHeap, int index){
    while(index >0 && maxHeap->elements[index]->like >=maxHeap->elements[getParentIndex(index)]->like){
        swap(&maxHeap->elements[index],&maxHeap->elements[getParentIndex(index)]);
        index = getParentIndex(index);
        if( index> 0 && maxHeap->elements[index]->like == maxHeap->elements[getParentIndex(index)]->like){
                if(maxHeap->elements[index]->id > maxHeap->elements[getParentIndex(index)]->id){
                    swap(&maxHeap->elements[index],&maxHeap->elements[getParentIndex(index)]);
                    index = getParentIndex(index);
                }
        }
    }
}
void increaseCapacity(alamat maxHeap){
    int newCapacity = maxHeap->capacity *2;
    maxHeap->elements =  (Tweet**)realloc(maxHeap->elements,newCapacity * sizeof(Tweet*));
    maxHeap->capacity = newCapacity;
    // if(maxHeap->elements == NULL){
    //     ex
    // }
}

void showFYB(){
    alamat maxHeap;
    maxHeap = createMaxHeap(10);
    int cnt = 0;
    for (int i=0;i<tweets.nEff;i++){
        insertTweet(maxHeap,tweets.buffer[i]);
    }
    if(tweets.nEff>=8){
    printf("Berikut %d kicauan dengan like tertinggi di FYB\n", 8);
    }else{
        printf("Berikut %d kicaucan dengan like tertinggi di FYB\n", tweets.nEff);
    }
    printf("\n");
    while(cnt<8  && cnt<tweets.nEff){
        Tweet * topTweet = removeMax(maxHeap);
        printf("Kicauan %d:\n",cnt+1);
        printf(" | %s \n",getUser(topTweet->author)->name);
        printf(" | %s \n", topTweet->dateTime);
        printf(" | plz FYB (For Your Burbir) ! \n");
        printf(" | Disukai:  %d\n",topTweet->like);
        cnt++;
    }
    destroyMaxHeap(maxHeap);
}