#include<string.h>
#include<stdio.h>
#include "hashTable.h"
#include "linkedList.h"
#include "destroyFunc.h"



void errorPrint(hStatus result){
    switch (result){
        case OK: printf("OK\n");
                break;
        case AllocationError: printf("ALLOCATION ERROR\n");
                break;
        case KeyNotFound: printf("KEY NOT FOUND\n");
                break;
        case NullPointerError: printf("NULL POINTER ERROR\n");
                break;
        case KeyAlreadyExits: printf("KEY ALREADY EXISTS\n");
                break;     
    }
}

unsigned long hashSrting(void* ptr)
{
    unsigned char *str = (unsigned char*)ptr;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != 0)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int compareStrings (void* ptr1, void* ptr2){
    char* str1 = (char*)ptr1;
    char* str2 = (char*)ptr2;
    return strcmp(str1, str2);
}

void printStrings(void* ptr1, void* ptr2){
    char* str1 = (char*)ptr1;
    char* str2 = (char*)ptr2;
    printf("%s\n%s\n", str1, str2);
}
 void destroyStrings(void* ptr1, void* ptr2){
    char* str1 = (char*)ptr1;
    char* str2 = (char*)ptr2;
    printf("destroyed: ");
    printStrings(str1, str2);
}




int testCreate(){
    hashTable* ht;
    int capacity = 6;
    hStatus res = hashCreate(&ht, capacity, compareStrings, hashSrting);
    if (res == OK){
        res = hashDestroy(ht, destroyStrings);
        if (res == OK)
            return 1;
    }
    return 0;
}


int insertOne(){
    hashTable* ht;
    void* value;
    int capacity = 6;
    hStatus res = hashCreate(&ht, capacity, compareStrings, hashSrting);
    if (res != OK) return 0;
    
    res = hashInsert(ht, "City", "KFAR SABA");
    if (res != OK) return 0;
    
    res = hashFind(ht, "City", &value);
    if (res != OK) return 0;

  
    printf("value: %s\n",(char*) value);
    res = hashDestroy(ht, destroyStrings);
    if (res == OK)
        return 1;
    
    return 1;
}

int insertFive(){
    hashTable* ht;
    void* value;
    int capacity = 6;
    hStatus res = hashCreate(&ht, capacity, compareStrings, hashSrting);
    if (res != OK) return 0;
    
    res = hashInsert(ht, "City", "KFAR SABA");
    if (res != OK) return 0;
    res = hashInsert(ht, "Country", "Israel");
    if (res != OK) return 0;
    res = hashInsert(ht, "Phone", "0508438458");
    if (res != OK) return 0;
    res = hashInsert(ht, "ID", "038053294");
    if (res != OK) return 0;
    res = hashInsert(ht, "NAME", "RAMY LERNER");
    if (res != OK) return 0;
    
    res = hashFind(ht, "ID", &value);
    if (res != OK) return 0;

  
    printf("value: %s\n",(char*) value);
    res = hashDestroy(ht, destroyStrings);
    if (res == OK)
        return 1;
    
    return 1;
}

int testInsert(){
    return insertOne() && insertFive();
}

int testDestroy(){
    return 0;
}

int testFind(){
    return 0;
}
    
int testDelete(){
    return 0;
}



int main(){
    

    printf("test Create: %d\n",testCreate());
  
    printf("test Insert: %d\n",testInsert());
    testDestroy();
    testFind();
    testDelete();
    return 0;
}