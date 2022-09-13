#ifndef HEADER_H
#define HEADER_H
#include <stdlib.h>
    
#define SKIPLIST_MAXLEVEL        16
#define SKIPLIST_NUM_NODES(l)    (l->numNodes)
#define SKIPLIST_NODE_FIRST(l)   (l->header->forward[0])
#define SKIPLIST_NODE_NEXT(n)    (n->forward[0])
#define SKIPLIST_NODE_VALUE(n)   (n ? n->value : NULL)


struct node  //nodes tou hashtable mou
{
    char * data;
    struct SkipList_t *vaccinated_persons;
    struct SkipList_t *not_vaccinated_persons;
    unsigned char *bloom_filter;
    struct node *next;
};

typedef int  (*SkipListCmp_t)  (void *key1, void *key2);
typedef void (*SkipListFree_t) (void *value);
typedef void * (*SkipListUserAlloc_t)(void *key, void *data, void **newKey, void **newData);

typedef struct SkipListNode_s  //nodes tis skip list mou
{
    void           *key;
    void           *value;
    struct node* name;
    struct node* country;
    int age;
    char date[10];
	unsigned char	level;
	unsigned char	reserved[3];
    struct SkipListNode_s *forward[1]; //pinakas forward pointers
} SkipListNode_t;

typedef struct SkipList_s 
{
    int             numNodes; 
    int             maxLevels; 
    int             level;         // Maximum level of the list

    SkipListCmp_t   cmpFn;
    SkipListFree_t  freeFn;

    void            **bh;

    SkipListNode_t  *header;    /* pointer to header */
}
SkipList_t;

SkipList_t *SkipListAlloc( SkipListCmp_t, SkipListFree_t );

void SkipListFree( SkipList_t * );

int SkipListInsert( SkipList_t *, void *, void *, int  );

int SkipListDelete( SkipList_t *, void * ); 

SkipListNode_t *SkipListGetNode( SkipList_t *, void * );

SkipListNode_t *SkipListGetFirst( SkipList_t * );

void
SkipListClear( SkipList_t *list );

int
SkipListDeleteNode( SkipList_t *list, void *key );


#endif /* HEADER_H */
