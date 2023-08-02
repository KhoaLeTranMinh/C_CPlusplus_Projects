//
//  thirdBattle.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//
// Students can remove the final initial return of the functions

#ifndef thirdBattle_h
#define thirdBattle_h

#include "SLLDataController.h"
#include "ArrayDataController.h"
#include <vector>
#include <string>

//////////////////////////////////////////////////////
/// TASK 1
//////////////////////////////////////////////////////

bool push(Array& array, Soldier soldier){
    //Return true if push successfully, false otherwise
    //TODO
    insertAt(array, soldier, array.size);
    return true;
}

bool pop(Array& array){
    //Return true if pop successfully, false otherwise
    //TODO
    bool check = removeAt(array, array.size-1);
    return check;
}

Soldier top(Array& array){
    //TODO
    if (!empty(array)) {
        return(array.arr[array.size - 1]);
    }
    else
    {
        return Soldier();
    }  //return this if cannot get top
}

//////////////////////////////////////////////////////
/// TASK 2
//////////////////////////////////////////////////////

bool enqueue(SLinkedList& list, Soldier soldier){
    //Return true if enqueue successfully, false otherwise
    //TODO
    int index = 0;
    SoldierNode* track = list.head;
    while (track != NULL) {
        track = track->next;
        index++;
    }
    insertAt(list, soldier, index);
    return true;
}

bool dequeue(SLinkedList& list){
    //Return true if dequeue successfully, false otherwise
    //TODO
    if (empty(list)) {
        return false;
    }
    removeAt(list, 0);
    return true;
}

Soldier front(SLinkedList& list){
    //TODO
    return (list.head->data);
    if (empty(list)) {
        return Soldier();
    }
    else {
        return (list.head->data);
    }
}

//////////////////////////////////////////////////////
/// TASK 3
//////////////////////////////////////////////////////

void reverse(SLinkedList& list){
    //TODO
    SoldierNode* next = list.head;
    SoldierNode* track = list.head;
    SoldierNode* prev = NULL;
    while (track != NULL) {
        next = track->next;
        track->next = prev;
        prev = track;
        track = next;
    }
    list.head = prev;
}

//////////////////////////////////////////////////////
/// TASK 4
//////////////////////////////////////////////////////

SLinkedList merge(SLinkedList& list1, SLinkedList& list2) {
    //TODO
    if (!empty(list1) && empty(list2)) {
        return SLinkedList(list1.head, list1.size);
    }
    if (empty(list1) && !empty(list2)) {
        return SLinkedList(list2.head, list2.size);
    }
    if (empty(list1) && empty(list2)) {
        return SLinkedList();
    }
    SoldierNode* tail1 = NULL;
    SoldierNode* tail2 = NULL;
    SoldierNode* track1 = list1.head;
    SoldierNode* track2 = list2.head;
    while (track1 != NULL) {
        if (track1->next == NULL) {
            tail1 = track1;
        }
        track1 = track1->next;
    }
    while (track2 != NULL) {
        if (track2->next == NULL) {
            tail2 = track2;
        }
        track2 = track2->next;
    }
    tail1->next = list2.head;
    SLinkedList final(list1.head, list1.size+ list2.size);

    {// First Priority
        SoldierNode* track = final.head;
        SoldierNode* loop = final.head;
        while (loop->next != NULL) {
            track = loop;
            while (track != NULL) {
                track = track->next;
                if (track == NULL) {
                    break;
                }
                if (track->data.HP < loop->data.HP) {
                    Soldier temp = track->data;
                    track->data = loop->data;
                    loop->data = temp;
                }
            }
            loop = loop->next;
        }
    }

    {// Second Priority
        SoldierNode* track = final.head;
        SoldierNode* loop = final.head;
        while (loop->next != NULL) {
            track = loop;
            while (track != NULL) {
                track = track->next;
                if (track == NULL) {
                    break;
                }
                if( (track->data.HP <= loop->data.HP) && (loop->data.isSpecial== true 
                    && track->data.isSpecial== false) ) 
                {
                    Soldier temp = track->data;
                    track->data = loop->data;
                    loop->data = temp;
                }
            }
            loop = loop->next;
        }
    }

    {// final priority
        SoldierNode* track = final.head;
        SoldierNode* loop = final.head;
        while (loop->next != NULL) {
            track = loop;
            while (track != NULL) {
                track = track->next;
                if (track == NULL) {
                    break;
                }
                if ((track->data.HP <= loop->data.HP)  &&  (loop->data.isSpecial >=
                     track->data.isSpecial) && (loop->data.ID > track->data.ID) ) {
                    Soldier temp = track->data;
                    track->data = loop->data;
                    loop->data = temp;
                }
            }
            loop = loop->next;
        }
    }
    return final;
}

//You can write your own functions here

//End your own functions

#endif /* thirdBattle_h */
