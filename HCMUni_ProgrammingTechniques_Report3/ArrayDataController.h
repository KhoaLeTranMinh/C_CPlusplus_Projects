//
//  ArrayDataController.h
//  KTLT ASS 3
//
//  Created by Nhân Nguyễn on 17/05/2021.
//

// Students can remove the final initial return of the functions

#ifndef ArrayDataController_h
#define ArrayDataController_h

#include "dataStructure.h"
#include <vector>
#include <string>
//Functions used to manage Array
void refresh(Array& array) {
    array.capacity *= 2;
    int newCap = array.capacity;
    Soldier* another = new Soldier[newCap];
    for (int i = 0; i < array.size; i++) {
        another[i] = array.arr[i];
    }
    delete[] array.arr;
    array.arr = another;
}
void renew(Soldier*& another, Array& a) {
    int size = a.size;
    for (int i = 0; i < size; i++) {
        another[i] = a.arr[i];
    }
    delete[]a.arr;
    a.arr = another;
}
void renew(Soldier*& another, Array& a, int newcap) {
    
    int size = a.size;
    if (size > newcap) {
        size = newcap;
    }
    for (int i = 0; i < size; i++) {
        another[i] = a.arr[i];
    }
    delete[]a.arr;
    a.arr = another;
}
bool empty(Array& array) {
    //Check whether the array is empty
    //TODO
    if (array.size == 0) {
        return true;
    }
    return false;
}
void clear(Array& array) {
    //Delete all of the elements in array
    //TODO
    delete[] array.arr;
    array.arr = NULL;
    array.size = 0;
    array.capacity = 0;
}

void initArray(Array& array, int cap) {
    //Init a new array with capacity equals to cap
    //TODO
    if (!empty(array)) {
        clear(array);
    }
    array.capacity = cap;
    Soldier* another = new Soldier[cap];
    array.arr = another;
}
bool eq(Array a) {
    return (a.size >= a.capacity);
}
void ex(Array& a) {
        a.capacity *= 2;
        Soldier* another = new Soldier[a.capacity];
        renew(another, a);
}
void print(Array& array){
    if (!array.size) {
        std::cout << "Array is empty" << endl;
        return;
    }
    std::cout <<"[";
    for(int i=0;i<array.size;i++){
        std::cout << array.arr[i].ID << " ";
    }
    std::cout <<"]" << endl;
}

bool insertAt(Array& array, Soldier element, int pos){
    //Insert element into a pos in the array
    //Return true if insert successfully, false otherwise
    //TODO
    if (array.size == 0) {
        if (pos >= 1) {
            return false;
        }
    }
    if (empty(array)) {
        initArray(array, 1);
        array.size = 0;
        array.arr[0] = element;
        array.size++;
        return true;
    }
    if (array.size >= array.capacity) {
        refresh(array);
    }
    if (pos >= array.size + 1  || pos < 0) {
        return false;
    }
    else {
        if (pos == array.size) {
            array.arr[pos] = element;
            array.size++;         
            return true;
        }
        else {
            Soldier* another = new Soldier[array.size + 1];    
            for (int i = 0; i < pos; i++) {
                another[i] = array.arr[i];
            }
            for (int i = pos + 1; i < array.size + 1; i++) {
                another[i] = array.arr[i-1];
            }
            another[pos] = element;
            delete[]array.arr;
            array.arr = another;
            array.size++;

            return true;
        }       
    }   
    return false;
}

bool removeAt (Array& array, int idx){
    //Remove element at index idx in the array
    //Return true if remove successfully, false otherwise
    //TODO
    if (idx >= array.size) {
        return false;
    }
    if (empty(array)) {
        return false;
    }
    if (array.size == 1) {
        if (idx != 0) {
            return false;
        }
    }
    else {
        Soldier* another = new Soldier[array.capacity];
        for (int i = 0; i < idx; i++) {
            another[i] = array.arr[i];
        }
        for (int i = idx; i < array.size - 1; i++) {
            another[i] = array.arr[i + 1];
        }
        
        delete[] array.arr;
        array.arr = another;
        array.size--;
        return true;
    }
      
    return false;
}

bool removeFirstItemWithHP (Array& array, int HP){
    //Remove the first element with HP equals to HP
    //Return true if remove successfully, false otherwise
    //TODO
    int index = 0;
    if (empty(array)) {
        return false;
    }
    else {
        for (int i = 0; i < array.size; i++) {
            if (array.arr[i].HP == HP) {
                index = i;
                break;
            }
        }
        removeAt(array, index);
        return true;
    }
    return false;
}

void ensureCapacity(Array& array, int newCap){
    //Extend the capacity of the array
    //TODO
    array.capacity = newCap;
    Soldier* another = new Soldier[newCap];
    renew(another, array, newCap);
}

int indexOf(Array& array, Soldier soldier){
    //Find index of soldier (start from 0)
    //Return -1 if the soldier does not exist
    //TODO
    for (int i = 0; i < array.size; i++) {
        if (array.arr[i] == soldier) {
            return i;
        }
    }
    return -1;
}

int size(Array& array){
    //Return size of the array
    //TODO
    if (empty(array)) { return -1; }
    return array.size;
}


string getIDAt(Array& array, int pos){
    //Get ID of the Soldier at pos
    //TODO
    if (pos >= array.size) {
        return "-1";
   }
    return array.arr[pos].ID;
}

int getHPAt(Array& array, int pos){
    //Get HP of the Soldier at pos
    //TODO
    if (empty(array) || pos >= array.size) {
        return -1;
    }
    
    return array.arr[pos].HP;
}

bool setHPAt(Array& array, int HP, int pos){
    //Set value of HP at pos
    //TODO
    //Return true if set successfully, false otherwise
    if (empty(array)|| pos >= array.size || pos < 0) {
        return false;
    }
    else {
        array.arr[pos].HP = HP;
        return true;
    }
    return false;
}

bool contains (Array& array, Soldier soldier){
    //Check if array contains soldier
    //TODO
    for (int i = 0; i < array.size; i++) {
        if (array.arr[i] == soldier) {
            return true;
        }
    }
    return false;
}

//You can write your own functions here

//End your own functions

#endif /* ArrayDataController_h */
