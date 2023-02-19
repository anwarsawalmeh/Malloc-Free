#include <kernel/types.h>
#include <user/user.h>
#include "memory_management.h"


struct node *head = 0;
struct node *current = 0;

// Malloc function
void* _malloc(int size){

    // starting point of the heap
    void* startingPoint = sbrk(0);

    // checks for free space
    void* checkSpace = fitFirst(head, size);

    // checks if fit first algorithm works
    if(checkSpace != NULL){
        
        return checkSpace;

    // if its null then new memory location allocated
    }else{
    
    // allocates a new program break based on size passed in
    struct node *link = (struct node*) (sbrk((size + sizeof(struct node))));
    // checks if sbrk worked
    if(link == (void*)-1){
        return NULL;
    }
        // initializing the variables
        link -> memAdd = startingPoint;
        link -> isFree = 1;
        link->size = size;

        // insert at the beginning of the linked list
        link -> next = head;
        head = link;
        current = head;
    // returns an instance of the struct node
    return link;

    }
}

// Fit first algorithm implementation
void* fitFirst(struct node *d,int size){
    d = head;
    
    while(d!=NULL){
        // searches for a free memory location with enough space
        if(d->isFree == 0 && d->size >= size){
            
            d->isFree = 1;
            return d;
        }
        d = d->next;
    }
    return NULL;

}

// free function. Memory address passed through
void _free(void *ptr){
    struct node *linked = head;
    while(linked != NULL){
        if(linked == ptr){
            linked->isFree = 0;
            // if the next node is not NULL and is free
            if(linked->next != 0 && linked->next->isFree == 0){
            // merge the free blocks of memory
            linked->size += linked->next->size + sizeof(head);
            linked->next = linked->next->next;

        }else{
            break;
        }
            
        }

        linked = linked->next;

    }
}
