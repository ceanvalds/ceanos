#include <list.h>
#include <malloc.h>

List *create_list(){
    List* listptr = kmalloc(sizeof(List));
    listptr->first = NULL;
    listptr->count = 0;
    return listptr;
}

void delete_list(List *list){
    struct listElement *current = list->first;
    for (int64_t i = 0; i < list->count; i++)
    {
        struct listElement *next = current->next;
        kfree(current);
        current = next;
    }
    kfree(list);
}

struct listElement *list_find_index(List *list,uint64_t index){
    struct listElement *current = list->first;
    for(uint64_t i;i < index - 1; i++){
        current = current->next;
    }
}

void list_append(List *list, void *value){
    struct listElement *current = list->first;
    for(uint64_t i;i < list->count - 1; i++){
        current = current->next;
    }
    struct listElement *new = kmalloc(sizeof(struct listElement));
    current->next = new;
    new->prev = current;
    new->next = NULL;
    new->value = value;
    list->count ++;
}

void list_set(List *list, void *value,uint64_t index){
    struct listElement *element = list_find_index(list,index);
    element->value = value;
}

void list_remove(List *list, uint64_t index){
    struct listElement *element = list_find_index(list,index);
    if(element->prev){
        element->prev->next = element->next;
    } else {
        //in this case it is probaly the first element so let chek
        if(list->first == element){
            //set the next as the first
            list->first = element->next;
        }
    }

    if(element->next){
        element->next->prev = element->prev;
    }
    list->count --;
}

void list_insert(List *list, void *value, uint64_t index){
    struct listElement *element = list_find_index(list,index);
    struct listElement *new = kmalloc(sizeof(struct listElement));
    //special case we try to set the first 
    if(index = 0){
        new->prev = NULL;
        list->first = new;
    } else {
        new->prev = element->prev;
        new->prev->next = new;
    }
    new->next = element;
    element->prev = new;

    list->count ++;
}

void *list_get(List *list, uint64_t index){
    struct listElement *element = list_find_index(list,index);
    return element->value;
}

uint64_t list_count(List *list){
    return list->count;
}
