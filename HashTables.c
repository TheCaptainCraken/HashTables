#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTables.h"

struct list_s {
    char* key;
    int val;
    struct list_s* next;
};

/*
*   Written by Daniel J. Bernstein (also known as djb), this simple hash function dates back to 1991.
*   For every character in the input string it:
*     - multiplies the hash by 33.
*     - adds the ASCII value of the current char.
*   It uses bit shifting instead of normal multiplication cuz it's faster on many CPUs
*   The starting number 5381 was picked by djb simply because testing showed that it results in fewer collisions and better avalanching.
*/
unsigned long int Djb2Hash(const char* input) {
    unsigned long int hash = 5381;
    int c;
    while (c = (int)*input++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void PrintDjb2Hash(const char* input) {
    printf("=> %u\n", Djb2Hash(input) % 100);
}

unsigned long int GenerateIndex(const char* key) {
    return Djb2Hash(key) % TABLE_LENGTH;
}

table InitTable() {
    table new_table = (table)malloc(sizeof(element*) * TABLE_LENGTH);
    for (int i = 0; i < TABLE_LENGTH; i++) {
        *(new_table + i) = NULL;
    }
    return new_table;
}

void PrintTable(table hash_table) {
    for (int i = 0; i < TABLE_LENGTH; i++) {
        element* current = *(hash_table + i);
        while (current != NULL) {
            printf("=> %s : %d\n", current->key, current->val);
            current = current->next;
        }
    }
}

void DestroyTable(table hash_table) {
    for (int i = 0; i < TABLE_LENGTH; i++) {
        element* current = *(hash_table + i);
        while (current != NULL) {
            element* next = current->next;
            free(current);
            current = next;
        }
    }
    free(hash_table);
}

void Insert(char* key, int value, table hash_table) {
    element* new_element = (element*)malloc(sizeof(element));
    new_element->key = key;
    new_element->val = value;
    new_element->next = NULL;
    unsigned long int index = GenerateIndex(key);
    element* current = *(hash_table + index);
    if (current == NULL) {
        *(hash_table + index) = new_element;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_element;
    }
}

element* LookUp(char* key, table hash_table) {
    unsigned long int index = GenerateIndex(key);
    element* current = *(hash_table + index);
    while (current != NULL) {
        if (strcmp(key, current->key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

