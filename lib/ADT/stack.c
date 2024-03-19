#include "stack.h"

void CreateEmpty(Stack* S){
    (*S).TOP = Nil;
}

boolean IsEmpty(Stack S){
    return S.TOP == Nil;
}

boolean IsFull(Stack S){
    return S.TOP == MaxEl - 1;
}

void Push(Stack* S, infotype X){
    (*S).TOP += 1;
    (*S).T[(*S).TOP] = X;
}

void Pop(Stack* S, infotype* X){
    (*X) = (*S).T[(*S).TOP];
    (*S).TOP -= 1;
}