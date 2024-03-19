#ifndef KELOMPOKTEMAN_H
#define KELOMPOKTEMAN_H
#include "dsu.h"
#include "user.h"
#include "relation.h"

void friendGroup(DisjointSet set,int currentUser );

boolean areFriend(int a,int b , DisjointSet set);

void showFriendGroup();

#endif

