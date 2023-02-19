#define NULL 0
struct node {
    int size;
    int *memAdd;
    int isFree;
    struct node *next;
};

void* _malloc(int size);
void* fitFirst(struct node *d, int size);
void _free(void *ptr);
