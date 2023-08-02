//
//  SLLDataControler.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//

// Students can remove the final initial return of the functions

#ifndef SLLDataController_h
#define SLLDataController_h

#include "dataStructure.h"
#include <vector>
#include <string>
using namespace std;
//Functions used to manage Singly Linked List
bool operator== (Soldier current, Soldier another) {
    return (   (current.HP == another.HP) && (current.isSpecial == another.isSpecial) && 
        (current.ID == another.ID)  );
}

void print(SLinkedList& list){
    if (!list.size) {
        cout << "List is empty" << endl;
        return;
    }
    SoldierNode* head = list.head;
    while (head){
        cout << head->data.ID << "->";
        head = head->next;
    }
    std::cout << "NULL"<<endl;
}

bool empty(SLinkedList& list) {
    //Check whether the list is empty
    //TODO
    if (list.size == 0 ) {
        return true;
    }
    return false;
}

bool insertAt(SLinkedList& list, Soldier element, int pos) {
    //Insert element into a pos in the SLL
    //Return true if insert successfully, false otherwise
    //TODO
    if (empty(list)) {
        list.head = new SoldierNode;
        list.head->data = element;
        list.head->next = NULL;
        list.size++;
        return true;
    }
    if (list.size == 1) {
        if (pos >= 2) {
            return false;
        }
        else if (pos == 0){
            SoldierNode* another = new SoldierNode;
            another->next = list.head; 
            another->data = element;
            list.head = another;
            list.size++;
            return true;
        }
        else if (pos == 1) {
            SoldierNode* another = new SoldierNode;
            another->data = element;
            list.head->next = another;
            list.size++;
            return true;
        }
    }
    if (list.size >= 2) {
        int index = 0;
        SoldierNode* track = list.head;
        if (pos > list.size || pos < 0) {
            return false;
        }
        else {
            do {
                if (pos == 0) {
                    SoldierNode* another = new SoldierNode;
                    another->data = element;
                    another->next = list.head;
                    list.head = another;
                    list.size++;
                    break;
                }else if (index == pos - 1 && track-> next != NULL) {
                        SoldierNode* another = new SoldierNode;
                        another->data = element;
                        another->next = track->next;
                        track->next = another;
                        list.size++;
                        break;
                } else if (pos == list.size && track->next == NULL) {
                        SoldierNode* another = new SoldierNode;
                        another->data = element;
                        another->next = NULL;
                        track->next = another;
                        list.size++;
                         break;
                    }
                       index++;
                       track = track->next;
            } while (track != NULL);
            return true;
        }
    }

    return false;
}

bool removeAt (SLinkedList& list, const int idx){
    //Remove element at index idx in the SLL
    //Return true if remove successfully, false otherwise
    //TODO
   if (list.size == 0 || idx < 0 || idx >= list.size) {
        return false;
    }
    if (list.size == 1) {
        if (idx != 0)
            return false;
        else {
            delete list.head;
            list.head->next = NULL;
            list.size = 0;
        }
    }
    if (list.size >= 2) {
        SoldierNode* track = list.head;
        int index = 0;
        while (track != NULL) {
            if (idx == 0) {
                list.head = track->next;
                track->next = NULL;                
                delete track;
                list.size--;
                return true;
            }
            else if (idx == list.size - 1 && track->next == NULL) {
                delete track;
                list.size--;
                return true;
            }
            else if (index == idx-1) {
                SoldierNode* target = track->next;
                SoldierNode* des = track->next->next;
                track->next = des;
                target->next = NULL;
                delete target;
                list.size--;
                return true;
            }
            index++;
            track = track->next;
        }
    }
    return false;
 }

bool removeFirstItemWithHP (SLinkedList& list, int HP){
    //Remove the first element with HP equals to HP
    //Return true if remove successfully, false otherwise
    //TODO
    int index = 0;
    SoldierNode* track = list.head;
    SoldierNode* target = NULL;
    if (empty(list)) {
        return false;
    }
    while (track != NULL) {
        if (track->data.HP == HP) {
            target = track;
            break;
        }
        index++;
        track = track->next;
    }
    if (target == NULL) {
        return false;
    }
    if (index == 0) {
        list.head = track->next;
        delete track;
        list.size--;
        return true;
    }
    int time = index - 1;
    track = list.head;
    for (int i = 0; i < time; i++) {
        track = track->next;
    }
    SoldierNode* des = track->next->next;
    target->next = NULL;
    track->next = des;
    delete target;
    list.size--;
    return true;
}

int indexOf(SLinkedList& list, Soldier soldier){
    //Find index of soldier (start from 0)
    //Return -1 if the soldier does not exist
    //TODO
    int index = 0;
    SoldierNode* track = list.head;
    if (track == NULL || list.size == 0) {
        return -1;
    }
    while (track != NULL) {
        if (track->data == soldier) {
            return index;
        }
        track = track->next;
        index++;
    }
    return -1;
    
}

int size(SLinkedList& list){
    //Return size of the list
    //TODO    
    return list.size;
}


void clear(SLinkedList& list){
    //Delete all of the elements in list
    //TODO
    if (list.size == 0) { return; }
    SoldierNode* track = list.head;
    while (track != NULL) {
        SoldierNode* current = track;
        track = track->next;
        delete current;
    }
    delete track;
    list.size = 0;
}

string getIDAt(SLinkedList& list, int pos) {
    //Get ID of the Soldier at pos
    //TODO
    if (empty(list) || pos >= list.size) {
        return "-1";
    }
    int index = 0;
    SoldierNode* track = list.head;
    while (track != NULL) {
        if (index == pos) {
            break;
        }
        track = track->next;
        index++;
    }
    if (index > pos || track == NULL) {
        return "-1";
    }
    return track->data.ID;
}

int getHPAt(SLinkedList& list, int pos){
    //Get HP of the Soldier at pos
    //TODO
    if (empty(list) || pos >= list.size) {
        return -1;
    }
    int index = 0;
    SoldierNode* track = list.head;
    while (track != NULL) {
        if (index == pos) {
            break;
        }
        track = track->next;
        index++;
    }
    if (index > pos || track == NULL) {
        return -1;
    }
    return track->data.HP;
}

bool setHPAt(SLinkedList& list, int HP, int pos){
    //Set value of HP at pos
    //TODO
    //Return true if set successfully, false otherwise
    if (empty(list) || pos >= list.size) {
        return false;
    }
    SoldierNode* track = list.head;
    int index = 0;
    while (track != NULL) {
        if (index == pos) {
            track->data.HP = HP;
            return true;
        }
        track = track->next;
        index++;
    }
    return false;
}

bool contains (SLinkedList& list, Soldier soldier){
    //Check if array contains soldier
    //TODO
    if (empty(list)) {
        return false;
    }
    SoldierNode* track = list.head;
    while (track != NULL) {
        if (track->data == soldier) {
            return true;
        }
        track = track->next;
    }
    return false;
}

//You can write your own functions here

//End your own functions

#endif /* SLLDataControler_h */
