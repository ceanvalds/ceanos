//@file list.h
//@brief simple list function
//@author Tayoky4848

#pragma once
#include <stdint.h>

struct listElement;

struct listElement {
    struct listElement *prev;
    struct listElement *next;
    void *value;
};

typedef struct {
    struct listElement *first;
    uint64_t count;
}List;

List *create_list();
void delete_list(List *list);
void list_append(List *list, void *value);
void list_set(List *list, void *value, uint64_t index);
void list_remove(List *list, uint64_t index);
void list_insert(List *list, void *value, uint64_t index);
void *list_get(List *list, uint64_t index);