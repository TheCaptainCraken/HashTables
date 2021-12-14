#pragma once

#define TABLE_LENGTH 100

typedef struct list_s element;
typedef element** table;

table InitTable();

void PrintTable(table hash_table);

void DestroyTable(table hash_table);

void Insert(char* key, int value, table hash_table);

element* LookUp(char* key, table hash_table);