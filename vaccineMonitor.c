#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "header.h"

int size = 7;

int vaccinatedPopulationByCountry;
int vaccinatedPopulationByCountry1;
int vaccinatedPopulationByCountry2;
int vaccinatedPopulationByCountry3;
int vaccinatedPopulationByCountry4;

int populationByCountry;
int populationByCountry1;
int populationByCountry2;
int populationByCountry3;
int populationByCountry4;

//------------------------------HASHTABLE FUNCTIONS-------------------------------

//Hashtable Initizalization

void init(int size, struct node **hashtable)
{
    int i;
    for(i = 0; i < size; i++)
        hashtable[i] = NULL;
}

 //Anazitisi gia to ean uparxei to key sto hashtable moy, Epistrefei to index ean uparxei alliws to -1 ean den uparxei

int find(int size, struct node **hashtable, char* key)
{

	int retval = 0;
	struct node *temp;
   int i;
   for(i = 0; i < size; i++)
   {
      temp = hashtable[i];
      while (temp != NULL) 
      {
         if (strcmp(temp->data, key) == 0 )
         {
            return retval;
         }
         temp = temp->next;
      }  
      retval++;
   }

	return -1;
 
}

 //Anazitisi gia to ean uparxei to key sto hashtable moy, Epistrefei pointer sto node tou key ean uparxei alliws pointer sto NULL ean den uparxei


struct node *findp(int size, struct node **hashtable, char* key)
{

	int retval = 0;
	struct node *temp;
   int i;
   for(i = 0; i < size; i++)
   {
      temp = hashtable[i];
      while (temp != NULL) 
      {
         if (strcmp(temp->data, key) == 0 )
         {
            return temp;
         }
         temp = temp->next;
      }  
      retval++;
   }

	return NULL;
 
}

//eisagwgi sto hashtable mou

void insert(char* value, int size, struct node *hashtable[size])
{
    //ftiaxnw neo node
    
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = malloc(12*sizeof(char));
    strcpy(newNode->data, value);
    
    newNode->next = NULL;

    //upologizw to hash key
    int key = (int)(value) % size;

    if(hashtable[key] == NULL)
        hashtable[key] = newNode;
    else
    {
        struct node *temp = hashtable[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

}


void removee(struct node **head_ref, char* key) 
{  
    struct node* temp = *head_ref, *prev; 
  
    if (temp != NULL && strcmp(temp->data, key) == 0 ) 
    { 
        *head_ref = temp->next;   
        free(temp);              
        return; 
    } 
  
    // Psaxnw gia to key poy prepei na ginei remove
 
    while (temp != NULL && strcmp(temp->data, key) != 0) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // ean den uparxei to key
    if (temp == NULL) return; 
  
    prev->next = temp->next; 
  
    free(temp);  
}

//ektypwnw to hashtable mou

void print(int size, struct node *hashtable[size])
{
    int i;
    printf("\n");
    for(i = 0; i < size; i++)
    {
        struct node *temp = hashtable[i];
        printf("hashtable[%d]-->",i);
        while(temp)
        {
            printf("%s -->",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

//apodesmevw tis mnimes tou hashtable mou

void freeHashTable(int size, struct node *hashtable[size])
{

    int i;
    printf("\n");
    for(i = 0; i < size; i++)
    {
        struct node *temp = hashtable[i];
        struct node *tbf;

        while(temp)
        {
            tbf = temp;
            temp = temp->next;
            free(tbf);
        }

    }
    
}

//-------------------------------END OF HASHTABLE FUNCTIONS--------------------------------


char diseaseBuffer[20][14];

void createDiseaseBuffer(int size, struct node *hashtable[size])
{
    int i;
    int k;
    for(k = 0; k < 20; k++)
    strcpy(diseaseBuffer[k], "-1");

    printf("\n");
    int j=0;
    for(i = 0; i < size; i++)
    {
        struct node *temp = hashtable[i];
        while(temp)
        {
            strcpy(diseaseBuffer[j], temp->data);
            printf("%s -->",temp->data);
            temp = temp->next;
            j++;
        }

        
    }

}


char countryBuffer[200][20];

void createCountryBuffer(int size, struct node *hashtable[size])
{
    int i;
    int k;
    for(k = 0; k < 20; k++)
    strcpy( countryBuffer[k], "-1");

    printf("\n");
    int j=0;
    for(i = 0; i < size; i++)
    {
        struct node *temp = hashtable[i];
        while(temp)
        {
            strcpy( countryBuffer[j], temp->data);
            printf("%s -->",temp->data);
            temp = temp->next;
            j++;
        }

        
    }

}


//-------------------------BLOOM FILTER FUNCTIONS-----------------------------------

unsigned long djb2(unsigned char *str) {
	unsigned long hash = 5381;
	int c; 
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}

unsigned long sdbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while (c = *str++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned long hash_i(unsigned char *str, unsigned int i) {
	return djb2(str) + i*sdbm(str) + i*i;
}

unsigned long *hashing(char *s,int K)
{   
    int i = 0;        
    unsigned long *newArray = malloc(sizeof(unsigned long) * K);
    
	//printf("djb2   (%s) : %lu \n", s, djb2(s));
	//printf("sdbm2  (%s) : %lu \n", s, sdbm(s));

	for (i = 0 ; i < K ; i++) {
		//printf("hash_%d (%s) : %lu \n", i, s, hash_i(s, i));
        newArray[i] = hash_i(s, i);
    }

    return newArray;
}

unsigned char * BloomFilterInit(int M, int K)
{
	int i = 0;  
	unsigned char *newArray = malloc(sizeof(unsigned char) * M);

	for(i = 0 ; i < M ; i++)
	{
		newArray[i] = 0;
	}

	return newArray;
}

unsigned char * BloomFilterInsert(int M, int K, unsigned char *bf, unsigned long *buffer) //inserts a record to the Bloom Filter
{
	int	j = 0;

    //printf("-----INSERTING IN THE BF------- \n");

	while(j<K) //inserts at bloom filter all 
    {
		bf[buffer[j] % M] = 1; //makes 1 the right place of the bloom filter
        j++;
    }

	return bf;
}

int BloomFilterCheck(int M, int K, unsigned char *bf, unsigned long *buffer) //Checks a record of the Bloom Filter
{
	int	j = 0;

    printf("-----PRINTNG THE BF------- \n");

	while(j<K) 
    {
		//printf("Bff of %d is %lu mod %d\n",j,buffer[j],M);
		//printf("ttttt %lu and Bloom filter is\n",(buffer[j] % M));

        int	p = 0;



		if(bf[buffer[j] % M] == 0) //checks in K-th hash function result, DOESNT'S exists..
		return 0;

        j++;
    }
	return 1;
}

void BloomFilterPrint(unsigned char *bf, int M)
{

    int p=0;
    while(p<M) //prints the bloom filter
    {
        printf("Bf of %d is %d\n",p,bf[p]);
        p++;
    }
}

void BloomFilterFree(unsigned char *bf, int M)
{
    free(bf);
}
 
//---------------------------------END OF BLOOM FILTER FUNCTIONS--------------------


// LOCAL DEFINITIONS

#define SKIPLIST_DEFAULT_BLOCK_SIZE    4096
#define SKIPLIST_NODE_NEAREST_UNIT(n)  ((n) + ((~((n) & 3) + 1) & 3))
#define SKIPLIST_NODE_UNIT_SIZE(ns)    (SKIPLIST_NODE_NEAREST_UNIT((ns)))
#define SKIPLIST_UNIT_MULT    (4)
#define SKIPLIST_NODE_SIZE(l)         (sizeof(SkipListNode_t) + (l) * sizeof(SkipListNode_t *))
#define SKIPLIST_NODE_UNIT_LEVEL(l)    (SKIPLIST_NODE_UNIT_SIZE(SKIPLIST_NODE_SIZE(l)) / SKIPLIST_UNIT_MULT  - 1)
#define SKIPLIST_MAX_NODE_SIZE         (SKIPLIST_NODE_SIZE(SKIPLIST_MAXLEVEL))
#define SKIPLIST_MAX_UNIT_SIZE        (SKIPLIST_NODE_UNIT_SIZE(SKIPLIST_MAX_NODE_SIZE))
#define SKIPLIST_NUM_UNITS            (SKIPLIST_MAX_UNIT_SIZE / SKIPLIST_UNIT_MULT)
#define MAX 15 


// DECLARATIONS

static int getNewLevel( int );
static SkipListNode_t *newSkipListNode( SkipList_t *, void *, void *, int );
static SkipListNode_t *newSkipListNodeOthers( SkipList_t *, void *, void *, int , char* , char* , char* , char* ,struct node **,struct node **  );
static void * skipListNodeAlloc( SkipList_t *list, int level );
static void skipListNodeFree( SkipList_t *list, void *node );


// ---------------------------------SKIP LIST FUNCTIONS---------------------------------

//  Arxikopoihsh SkipList

SkipList_t *
SkipListAlloc( SkipListCmp_t cmpFn, SkipListFree_t freeFn )
{
    int        i = 0;
    SkipList_t *list = NULL;
     
    if ( cmpFn == NULL || freeFn == NULL )
        return( NULL);
    
    //demsevw mnimi

    i = sizeof(SkipList_t);
    if ( (list = (SkipList_t *)malloc( i )) == NULL )
        return( NULL );
    memset( list, 0, i ); 
    
     // vazw random level gia tin list kai arxikopoiw tis metablites 
    
    srand( (unsigned long)time(NULL) );
    

    
    list->level  = 0;
    list->cmpFn  = cmpFn;
    list->freeFn = freeFn;
    list->numNodes = 0;
    list->maxLevels = SKIPLIST_MAXLEVEL - 1;
    list->header = newSkipListNode( list, (void *)0, (void *)0, list->maxLevels );

    
    
    return( list );
}


//Diagrafi kai Free tis Skip List 

void
SkipListFree( SkipList_t *list ) 
{
    register SkipListNode_t *p, *q;
    int i;

    //episkeptimai kai diagrafw ka8e node tis list 
    
    p = list->header->forward[0];

    while ( p ) {
 
        q = p->forward[0];

        //kalw tin user registered freeFn gia na kanw free to stoixeio poy einai apo8ikevmeno sto node 
        
        list->freeFn( p->value );

        //kanw free to sygkekrimeno node
        skipListNodeFree( list, p );

        p = q;

    }
   
    free(list->header);

    //twra pou ola ta nodes exoun ginei free mporw na kanw free tin lista
    free( list );
}

//kanw insert to key sti lista mou 

int
SkipListInsert( SkipList_t *list, void *key, void *value, int replace ) 
{
    int i = 0;
    int newLevel = 0;
    SkipListNode_t *x= NULL;
    SkipListNode_t *update[SKIPLIST_MAXLEVEL];
    

    for ( x=list->header, i=list->level; i >= 0; i-- ) {
        while ( x->forward[i] != 0 &&
                list->cmpFn(x->forward[i]->key, key) < 0 ) {
            x = x->forward[i];
        }
       
        update[i] = x;
    }
    x = x->forward[0];
    
    //ean yparxei hdh to key

    if ( x && list->cmpFn(x->key, key) == 0 ) {
        if ( replace ) {
            list->freeFn( x->value );
            x->key = key;
            x->value = value;
            return( 0 );
        }
        else
            return( -1 );
    }
    
    //kainourio key element

    newLevel = getNewLevel( list->maxLevels );
    
    if ( newLevel > list->level ) {
        for ( i=list->level+1; i<=newLevel; i++ ) {
            update[i] = list->header;
        }
        list->level = newLevel;
    }
    
    x = newSkipListNode( list, key, value, newLevel );
    
    for ( i=0; i<=newLevel; i++ ) {
        
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
    list->numNodes++;
    
    return(0);
}

// delete an existing key from the list

int
SkipListDelete( SkipList_t *list, void *key ) 
{
    int i = 0;
    SkipListNode_t *x = NULL;
    SkipListNode_t *y = NULL;
    SkipListNode_t *update[SKIPLIST_MAXLEVEL];
    
    for ( x=list->header, i=list->level; i >= 0; i-- ) {
        while ( x->forward[i] != 0 &&
                list->cmpFn(x->forward[i]->key, key) < 0 ) {
            x = x->forward[i];
        }
        
        update[i] = x;
    }
    x = x->forward[0];
    
    //ean uparxei to key, delete it

    if ( x && list->cmpFn(x->key, key) == 0 ) {
        for ( i=0; i<=list->level; i++ ) {
            if ( (y=update[i])->forward[i] == x ) {
                y->forward[i] = x->forward[i];
            }    
        }
        list->freeFn( x->value );
        skipListNodeFree( list, x );
      
        while ( list->level > 0 &&
            list->header->forward[list->level] == NULL ) {
            list->level--; 
        }
        list->numNodes--;
        return( 0 );
    }
    else {
        return( -1 );
    }    
}

static void
SkipListDummyFree( void *dummy )
{

}


// delete an existing key from the list 
// kalw tin SkipListDeelete
int
SkipListDeleteNode( SkipList_t *list, void *key )
{
    SkipListFree_t saveFree = list->freeFn;
    int ret;

    list->freeFn = SkipListDummyFree;

    ret = SkipListDelete(list,key);

    list->freeFn = saveFree;

    return ret;

}

// pairnw to node enos sygkekrimenoy key ths listas

SkipListNode_t *
SkipListGetNode( SkipList_t *list, void *key )
{
    int i = 0;
    SkipListNode_t *x= NULL;
     
    for ( x=list->header, i=list->level; i >= 0; i-- ) {
        while ( x->forward[i] != 0 &&
                list->cmpFn(x->forward[i]->key, key) < 0 ) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if ( x && list->cmpFn(x->key, key) == 0 ) {
        return( x );
    }
    else {
        return( NULL );
    }    
}


//pairnw to prwto node tis listas
SkipListNode_t *
SkipListGetFirst( SkipList_t *list )
{
    return( SKIPLIST_NODE_FIRST(list) );
}

//apodesmevw oli tin mnimi tis skip list mou

void
SkipListClear( SkipList_t *list ) 
{
    register SkipListNode_t *p, *q;
    int i;    

    p = list->header->forward[0];

    while ( p ) 
    {

        q = p->forward[0];

       //kalw tin user registered gia na kanw free to stoixeio poy einai apo8ikevmeno sto node 
        list->freeFn( p->value );

        //free to node
        skipListNodeFree( list, p );

        p = q;
    }
    

    //oles oi listes exoun ginei free, twra kanw ta headers

    for ( i=0; i<=list->maxLevels; i++ ) {

        list->header->forward[i] = NULL;

    }

	list->level = 0;

    list->numNodes = 0;
    
}


static int
getNewLevel( int maxLevel )
{
    int level;

    for ( level = 0; (rand() < (RAND_MAX / 2)) && level < SKIPLIST_MAXLEVEL; level++ )
        ;

    level = level > maxLevel ? maxLevel : level;

    return( level );

}

static SkipListNode_t *
newSkipListNode( SkipList_t *list, void *key, void *value, int newLevel )
{
    int i;
    SkipListNode_t *node;

    node = skipListNodeAlloc(list,newLevel);
    if ( node == NULL )
        return( NULL );
    for ( i=0; i<=newLevel; i++ ) {
        node->forward[i] = NULL;
    }
    node->key   = key;
    node->value = value;
	node->level = newLevel;
    return( node );
}


static void *
skipListNodeAlloc( SkipList_t *list, int level )
{
    int idx;

    return malloc(SKIPLIST_NODE_SIZE(level));

}

static void
skipListNodeFree( SkipList_t *list, void *node )
{
    int idx;

    free(node);            
}


static int myCmp( void *key1, void *key2 )
{
    int key1Val = (int) ((int *)key1);
    int key2Val = (int) ((int *)key2);

    return( key1Val - key2Val );
}

static void myFree( void *value )
{
   printf("Freed %d\n",(int)value);

}


static void insertValue(char* buf, SkipList_t *list )
{
    //char buf[256];
    int  value = 0;

    // printf( "\n\nEnter the value to be inserted : " );
    // fgets( buf, MAX, stdin );
    value = atoi(buf);
    //printf( "Inserting %d ...\n", value );
    if ( SkipListInsert( list, (void *)value, (void *)value, 0 ) != 0 ) {
        printf( "Error in inserting the value\n" );
    }
    else {
        //printf( "Insertion is successful\n" );
    }    
}

static void insertotherValues(char* id, SkipList_t *list, char* a, char* country, char* age, char* date, struct node *hashtablecountries[size], struct node *hashtablenames[size])
{

    int value = atoi(id);
    //printf( "Inserting %d ...\n", value );
    if ( SkipListInsertOthers( list, (void *)value, (void *)value, 0,  a, country, age, date, hashtablecountries, hashtablenames) != 0 ) {
        printf( "Error in inserting the value\n" );
    }
    else {
        //printf( "Insertion is successful\n" );
    } 
}

int
SkipListInsertOthers( SkipList_t *list, void *key, void *value, int replace, char* a, char* country, char* age, char* date , struct node *hashtablecountries[size], struct node *hashtablenames[size]) 
{
    int i = 0;
    int newLevel = 0;
    SkipListNode_t *x= NULL;
    SkipListNode_t *update[SKIPLIST_MAXLEVEL];
    
   
    for ( x=list->header, i=list->level; i >= 0; i-- ) {
        while ( x->forward[i] != 0 &&
                list->cmpFn(x->forward[i]->key, key) < 0 ) {
            x = x->forward[i];
        }
        
        update[i] = x;
    }
    x = x->forward[0];
    
    if ( x && list->cmpFn(x->key, key) == 0 ) {
        if ( replace ) {
            list->freeFn( x->value );
            x->key = key;
            x->value = value;
            x->name = findp(size, hashtablenames, a);
            x->country = findp(size, hashtablecountries, country);
            //printf("----------------EDW AGE %d", atoi(age));
            x->age = atoi(age);
            //printf("----------------EDW AGE %d", x->age);
            strcpy(x->date, date);

            return( 0 );
        }
        else
            return( -1 );
    }
   
    newLevel = getNewLevel( list->maxLevels );
    
    if ( newLevel > list->level ) {
        for ( i=list->level+1; i<=newLevel; i++ ) {
            update[i] = list->header;
        }
        list->level = newLevel;
    }
   
    x = newSkipListNodeOthers( list, key, value, newLevel, a, country, age, date, hashtablecountries, hashtablenames );
  
    for ( i=0; i<=newLevel; i++ ) {
      
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
    list->numNodes++;
    
    return(0);
}

static SkipListNode_t *
newSkipListNodeOthers( SkipList_t *list, void *key, void *value, int newLevel, char* a, char* country, char* age, char* date,  struct node *hashtablecountries[size], struct node *hashtablenames[size]  )
{
    int i;
    SkipListNode_t *node;

    node = skipListNodeAlloc(list,newLevel);
    if ( node == NULL )
        return( NULL );
    for ( i=0; i<=newLevel; i++ ) {
        node->forward[i] = NULL;
    }
    node->key   = key;
    node->value = value;
    node->name = findp(size, hashtablenames, a);
    node->country = findp(size, hashtablecountries, country);
    //printf("----------------EDW AGE %d", atoi(age));
    node->age = atoi(age);
    //printf("----------------EDW AGE %d", node->age);
    strcpy(node->date, date);
	node->level = newLevel;
    return( node );

}


static void deleteValue(char* buf, SkipList_t *list )
{
    //char buf[256];
    int  key = 0;

    // printf( "\n\nEnter the value to be deleted : " );
    // fgets( buf, MAX, stdin );
    key = atoi(buf);
    printf( "Deleting the matched element for the key %d ...\n", key );
    if ( SkipListDelete(list, (void *)key) != 0 ) {
        printf( "Error in deleting the value\n" );
    }
    else {
        printf( "Deletion is successful\n" );
    }    
}

static int searchValue(char* buf, SkipList_t *list )
{
    //char buf[256];
    int  key = 0;
    SkipListNode_t *node;
    // printf( "\n\nEnter the value to be searched : " );
    // fgets( buf, MAX, stdin );
    key = atoi(buf);
    node = SkipListGetNode( list, (void *)key );
    if ( node == NULL ) {
        return 0;
    }
    else {
        return 1;
    }    
}


static void printValue( SkipList_t *list )
{
    int i = 0;
    SkipListNode_t *node;
    
    printf( "\n\n" );
    node = SkipListGetFirst( list );
    for ( ; node; node=node->forward[0] ) {
        printf( "%d", (int)node->value);
        printf(" %s", node->name->data);
        printf(" %s", node->country->data);
        printf(" %d", (int)node->age);
        printf( "%s\n", node->date);
    }    
}

static void clearList( SkipList_t *list )
{

    printf("\n\nClearing list\n");

    SkipListClear(list);

}

//-------------------------END OF SKIP LIST FUNCTIONS----------------------------


int argumentsCheck(char* a, char* b, char* c, char* d, int argc)
{
    
    if(strcmp(a, "-c")!=0) //if it is not "-c"
    return 0;
    
    int exists = access (b, F_OK); //check if the given file exists
    if(exists!=0) //if it does NOT exists
    return 0;
    
    if(strcmp(c, "-b")!=0) //if it is not "-b"
    return 0;
    
    if(atoi(d)==0) //if it is not a number
    return 0;
    
    if(argc != 5) //if arguments are not 5 (5 including the ./vaccineMonitor)
    return 0;

    return 1; //if it survives return 1 which means "Succesful Arguments Check"
}


void process_line(char *linebuf, size_t linesiz, int M, int K, struct node *hashtableviruses[size], struct node *hashtablecountries[size], struct node *hashtablenames[size], int size)
{

    char *linebuf2 = linebuf;
    linebuf2[strlen(linebuf2)-1] = '\0';

    //printf(" pritned viruses Succesful Arguments Check\n");
   char * id;
   char* first;
   char* second;
   char* country;
   char* age;
   char *disease;
    char* vaccinated;
    char* date;
  
  //printf("Succesful Arguments Check\n");
    int i=0;


  char *ch;
  ch = strtok(linebuf2, " ");
  while (ch != NULL) 
  {
    if(i==0)
        id=ch;
    if(i==1)
        first=ch;
    if(i==2)
        second=ch;
    if(i==3)
        country = ch;
    if(i==4)
        age = ch;
    if(i==5)
        disease = ch;
    if(i==6)
        vaccinated = ch;
    if(i==7)
        date = ch;

    ch = strtok(NULL, " ");
    i++;
  }


  if(strcmp(vaccinated, "NO")==0 && strlen(date) > 3) //elegxos ean exw kapoia date meta to "NO" 
  {
    printf("ERROR IN RECORD %s %s %s %s %s %s %s %s\n",id, first, second, country, age, disease, vaccinated, date);
    return; //stamata edw

  }
    
    if(find(size,hashtableviruses,disease) ==-1) //ean den uparxei h as8eneia
    {
        insert(disease, size, hashtableviruses);
        createDataStructures(disease, hashtableviruses, M, K); //create my new data structures for the new disease
    }


    if(find(size,hashtablecountries,country) ==-1) //ean den yparxei h xwra
    {
        insert(country, size, hashtablecountries);
    }

    char *a =  malloc (sizeof (char) * 16);
    strcpy(a, first);
    strcat(a, " ");
    strcat(a, second);

    if(find(size,hashtablenames,a) ==-1) //ean den uparxei to onomatepwnumo
    {   
        insert(a, size, hashtablenames);
    }


    if(find(size,hashtableviruses,disease) !=-1 && strncmp(vaccinated, "YES", 2)==0) //ean uparxei h as8eneia kai o xristis einai emvoliasmenos
    {
        struct node *temp = findp(size, hashtableviruses, disease);

        if( searchValue(id, temp->vaccinated_persons)==0 )  //ean den uparxei TO ID sto hash table mou
        {
            //insertValue(id, temp->vaccinated_persons); //kane tin insert
            unsigned long *buffer = hashing(id, K); //pinakas me ta K funcion results etoimos gia insert sto bloomfilter
            temp->bloom_filter =  BloomFilterInsert(M,K,temp->bloom_filter,buffer); //inserts a record (buffer of its K's hash function)
            free(buffer);
         //printf("------------------------------------------------------------------------------------\n");
            insertotherValues(id, temp->vaccinated_persons, a, country, age, date, hashtablecountries, hashtablenames);
        }
        

        // printf("printing the skip list vaccinated_persons--------------------------\n");
        // printValue(temp->vaccinated_persons);

    }


    if(find(size,hashtableviruses,disease) !=-1 && strncmp(vaccinated, "NO",2)==0) //ean uparxei h as8eneia kai o xristis DEN einai emvoliasmenos
    {
        struct node *temp = findp(size, hashtableviruses, disease);

        if( searchValue(id, temp->not_vaccinated_persons)==0 )  //ean den uparxei TO ID sto hash page table mou
            insertotherValues(id, temp->not_vaccinated_persons, a, country, age, " ", hashtablecountries, hashtablenames);

    }

    free(a);

}

void createDataStructures(char *disease, struct node **hashtableviruses, int M, int K)
{
    struct node *temp = findp(size, hashtableviruses, disease);

    printf("\n\nCreateDataStructures------------------------------------for %s:\n\n", disease);
    SkipList_t *vaccinated_persons_skiplist = NULL; //vaccinated_persons_skiplist Initialization
    vaccinated_persons_skiplist = SkipListAlloc( myCmp, myFree );
    temp->vaccinated_persons = vaccinated_persons_skiplist;
    
    if ( vaccinated_persons_skiplist == NULL ) {
        printf( "ERROR: Allocation of skip list failed\n" );
    }

    printf("vaccinated_persons_skiplist Initialization\n");

    SkipList_t *not_vaccinated_persons_skiplist = NULL; //not_vaccinated_persons_skiplist Initialization
    not_vaccinated_persons_skiplist = SkipListAlloc( myCmp, myFree );
    temp->not_vaccinated_persons = not_vaccinated_persons_skiplist;

    if ( not_vaccinated_persons_skiplist == NULL ) {
        printf( "ERROR: Allocation of skip list failed\n" );
    }
    
    printf("not vaccinated_persons_skiplist Initialization\n");

    unsigned char *bf = BloomFilterInit(M,K); //Bloom Filter Initialization
    temp->bloom_filter = bf;
    //printf("temp->data = %s ((((((((((((((((((((((\n", temp->data );
    //printValue(temp->vaccinated_persons);
    printf("Bloom Filter Initialization\n");

}



int dateGreater (int day1, int month1, int year1, int day2, int month2, int year2) //ean epistrepsei 1 tote date1 > date2
{
    if (year1 < year2)
       return 0;

    if (year1 > year2)
       return 1;

    if (year1 == year2)
    {
         if (month1<month2)
              return 0;
         else if (month1>month2)
              return 1;
         else if (day1<day2)
              return 0;
         else if(day1>day2)
              return 1;
         else
              return 1; //akrivws idies imerominies
    }
}


int dateCheck(char *date, char *date1, char *date2)
{
    char *day = malloc (sizeof (char) * 3);
    char *month = malloc (sizeof (char) * 3);
    char *year = malloc (sizeof (char) * 5);
    char *dt = date;

    char *day1 = malloc (sizeof (char) * 3);
    char *month1 = malloc (sizeof (char) * 3);
    char *year1 = malloc (sizeof (char) * 5);
    char *dt1 = date1;
    
    char *day2 = malloc (sizeof (char) * 3);
    char *month2 = malloc (sizeof (char) * 3);
    char *year2 = malloc (sizeof (char) * 5);
    char *dt2 = date2;

    

    ////////////////////////////////////////////////// gia date
    memcpy(day, dt, 3);  //day
    day[2] = '\0'; 

    memcpy(month, dt + 3, 3);  //month
    month[2] = '\0'; 

    year = dt + 6; //year
    ////////////////////////////////////////////////// gia date1
    memcpy(day1, dt1, 3);  //day
    day1[2] = '\0'; 

    memcpy(month1, dt1 + 3, 3);  //month
    month1[2] = '\0'; 

    year1 = dt1 + 6; //year
    ////////////////////////////////////////////////// gia date2:
    memcpy(day2, dt2, 3);  //day
    day2[2] = '\0'; 

    memcpy(month2, dt2 + 3, 3);  //month
    month2[2] = '\0'; 

    year2 = dt2 + 6; //year

    /////////////////////////////////////////////// 3ekinaei to date comparison

    if(dateGreater(atoi(day1), atoi(month1), atoi(year1), atoi(day2), atoi(month2), atoi(year2)) == 1) //elegxos gia to ean h date1 einai megaluteri ths date2
    {
        return -1; //ean isxuei date1 > date2 tote kati den pei kala, epistrepse la8os
    }
    else
    {
        if( dateGreater(atoi(day), atoi(month), atoi(year), atoi(day1), atoi(month1), atoi(year1)) == 1 && dateGreater(atoi(day), atoi(month), atoi(year), atoi(day2), atoi(month2), atoi(year2)) == 0) //ean to date einai mesa sto pedio [date1...date2] tote return 1, alliws return 0
        {
   
            return 1; //einai mesa sto pedio
        }
        else
        {

            return 0;
        }
    }


}

static double getVaccinationPercentage(char* country, char* date1, char* date2, SkipList_t *list1, SkipList_t *list2)
{
    double percentage;
    populationByCountry = 0;
    int i = 0;
    SkipListNode_t *node;
    
    printf( "\n" );
    node = SkipListGetFirst( list1 ); // vaccinated list
    for ( ; node; node=node->forward[0] ) 
    {

        if( strcmp(node->country->data, country ) == 0 ) //ean episkeftoume to node tis xwras pou mas endiaferei
        {
            if(dateCheck(node->date, date1, date2) == -1) //elegxos gia otan date1 > date2 
            {
                return -1;
            }

            if(dateCheck(node->date, date1, date2) == 1) //otan date anikei sto [date1...date2]
            {
                vaccinatedPopulationByCountry++;
            }

            populationByCountry++;
        }
        
    } 


    node = SkipListGetFirst( list2 ); // not vaccinated list
    for ( ; node; node=node->forward[0] ) 
    {

        if( strcmp(node->country->data, country ) == 0 ) //ean episkeftoume to node tis xwras pou mas endiaferei
        {
            if(dateCheck(node->date, date1, date2) == -1) //elegxos gia otan date1 > date2 
            {
                return -1;
            }

            populationByCountry++;
        }
    } 

    ////// calculating the percentage
    percentage = ((double)vaccinatedPopulationByCountry) / populationByCountry;
    percentage = percentage*100;

    return percentage;
    
}


static double getVaccinationPercentageByAge(int ageArea, char* country, char* date1, char* date2, SkipList_t *list1, SkipList_t *list2)
{
    double percentage;
    populationByCountry = 0;
    int i = 0;
    int minAge, maxAge;
    SkipListNode_t *node;

    switch (ageArea)
    {
        case 1: minAge = 0; maxAge = 19;
                break;
        case 2: minAge = 20; maxAge = 39;
                break;
        case 3: minAge = 40; maxAge = 59;
                break;
        case 4: minAge = 60; maxAge = 120;
                break;
      
    }
    
    printf( "\n" );
    node = SkipListGetFirst( list1 ); // vaccinated list
    for ( ; node; node=node->forward[0] ) 
    {

        if( strcmp(node->country->data, country ) == 0 && node->age >= minAge && node->age <= maxAge) //ean episkeftoume to node tis xwras pou mas endiaferei kai einai mesa stin katallili ilikiaki katogoria
        {
            if(dateCheck(node->date, date1, date2) == -1) //elegxos gia otan date1 > date2 
            {
                return -1;
            }

            if(dateCheck(node->date, date1, date2) == 1) //otan date anikei sto [date1...date2]
            {
                vaccinatedPopulationByCountry++;
            }

            populationByCountry++;
        }
        
    } 


    node = SkipListGetFirst( list2 ); // not vaccinated list
    for ( ; node; node=node->forward[0] ) 
    {

        if( strcmp(node->country->data, country ) == 0 && node->age >= minAge && node->age <= maxAge) //ean episkeftoume to node tis xwras pou mas endiaferei
        {
            if(dateCheck(node->date, date1, date2) == -1) //elegxos gia otan date1 > date2 
            {
                return -1;
            }

            populationByCountry++;
        }
    } 

    ////// calculating the percentage
    percentage = ((double)vaccinatedPopulationByCountry) / populationByCountry;
    percentage = percentage*100;

    return percentage;
    
}



int performTheOperation(char* operation, int M, int K, struct node *hashtableviruses[size], struct node *hashtablecountries[size], struct node *hashtablenames[size], int size)
{
    char *ch,*s1,*s2,*s3,*s4,*s5,*s6,*s7,*s8,*s9;
    s1 = "-1";
    s2 = "-1";
    s3 = "-1";
    s4 = "-1";
    s5 = "-1";
    s6 = "-1";
    s7 = "-1";
    s8 = "-1";
    s9 = "-1";
    char *operation2 = operation;
    operation2[strlen(operation2)-1] = '\0';
    ch = strtok(operation2, " ");
    int i = 1;
    while (ch != NULL) 
    {
        //printf("ch is: %s\n", ch);
        if(i==1) //operation
            s1=ch; // einai to "/..."
        if(i==2) 
            s2=ch; //einai sini8ws to citizenId..
        if(i==3)
            s3 = ch;
        if(i==4)
            s4 = ch;
        if(i==5)
            s5 = ch;
        if(i==6)
            s6 = ch;
        if(i==7 )
            s7 = ch;
        if(i==8)
            s8 = ch;
        if(i==9)
            s9 = ch;

        ch = strtok(NULL, " ");
        i++;
    }
    //printf("Succesful!!!! einai: SI %s S2 %s S3 %s\n", s1,s2,s3);
    

        if(strcmp(s1, "/vaccineStatusBloom") ==0)
        {
            struct node *temp = findp(size, hashtableviruses, s3);
            printf("Succesful!!!!\n");
            
              
            printf("Succesful!!!!\n");
            unsigned long *buffer = hashing(s2, K); //pinakas me ta K funcion results
            printf("Succesful!!!!\n");
            int checkflag = BloomFilterCheck(M,K,temp->bloom_filter,buffer); // if 0 is returned, the record is NOT in the bloom filter, otherwise it MAY be in
            free(buffer);
            printf("Succesful!!!!!!!!!!!!!!!!!\n\n");

            if(checkflag ==0)
            printf("NOT_VACCINATED\n");

            if(checkflag ==1)
            printf("MAYBE\n");

            return 1;

        }

        if(strcmp(s1, "/vaccineStatus" ) ==0 && s3!="-1" )
        {
            struct node *temp = findp(size, hashtableviruses, s3);
            int checkflag2;
            checkflag2 = searchValue(s2, temp->vaccinated_persons);
            

            if(checkflag2 ==0)
            printf("NOT_VACCINATED\n");

            if(checkflag2 ==1)
            {
                
                SkipListNode_t *temp2 = NULL;
                temp2 = SkipListGetNode(temp->vaccinated_persons, (void *)atoi(s2));
                
                printf("VACCINATED ON %s\n", temp2->date);
            }

            return 1;
            
        }

        if(strcmp(s1, "/vaccineStatus" ) ==0  &&  s3=="-1" )
        {
            //printf("EEE\n");
            //struct node *temp = findp(size, hashtableviruses, s3);
            createDiseaseBuffer(size, hashtableviruses);  //ftiaxnw enan pinaka me oles tis uparxouses as8eneies mexri twra
            int k;
            //printf("EEE\n");

            for(k = 0; k < 20; k++)
            {
                if( strncmp(diseaseBuffer[k], "-1", 2) ==0 ) //stamata tin epanalispi otan teleiwsoyn oi as8eneies
                break;

                printf("%s ------ ", diseaseBuffer[k]);

                struct node *temp = findp(size, hashtableviruses, diseaseBuffer[k]);

                int checkflag2;
                checkflag2 = searchValue(s2, temp->vaccinated_persons);
                

                if(checkflag2 ==0)
                printf("NOT_VACCINATED\n");

                if(checkflag2 ==1)
                {
                    
                    SkipListNode_t *temp2 = NULL;
                    temp2 = SkipListGetNode(temp->vaccinated_persons, (void *)atoi(s2));
                    
                    printf("VACCINATED ON %s\n", temp2->date);
                }

                
                
            }

            return 1;
            
        }


        if(strcmp(s1, "/insertCitizenRecord" ) ==0 )
        {
            char* id = s2;
            char* first = s3;
            char* second = s4;
            char* country = s5;
            char* age = s6;
            char* disease = s7;
            char* vaccinated = s8;
            char* date = s9;

            char *a =  malloc (sizeof (char) * 16);
            strcpy(a, first);
            strcat(a, " ");
            strcat(a, second);
            printf("NAME is %s\n", a);

            struct node *temp = findp(size, hashtableviruses, s7);
            int checkflag2;
            checkflag2 = searchValue(s2, temp->vaccinated_persons);

            if(strcmp(vaccinated, "YES" ) ==0)
            {
                if(checkflag2 ==1)
                {
                    SkipListNode_t *temp2 = NULL;
                    temp2 = SkipListGetNode(temp->vaccinated_persons, (void *)atoi(id));

                    printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s",s2,temp2->date);
                }
                else
                {
                    if( searchValue(s2, temp->not_vaccinated_persons) == 1 )  //ean uparxei stin not_vaccinated_persons vgale ton apo ekei
                    deleteValue(s2, temp->not_vaccinated_persons);

                    unsigned long *buffer = hashing(id, K); //pinakas me ta K funcion results etoimos gia insert sto bloomfilter
                    temp->bloom_filter =  BloomFilterInsert(M,K,temp->bloom_filter,buffer); //inserts a record (buffer of its K's hash function)
                    free(buffer);
                    printf("------------------------------------------------------------------------------------\n");
                    insertotherValues(id, temp->vaccinated_persons, a, country, age, date, hashtablecountries, hashtablenames);
                    printf("Value has been inserted to the Bloom Filter and the SkipList.\n");

                }

            }

            if(strcmp(vaccinated, "NO" ) ==0)
            {
                if( searchValue(id, temp->not_vaccinated_persons)==0 )  //ean den uparxei TO ID sto hash page table mou
                insertotherValues(id, temp->not_vaccinated_persons, a, country, age, " ", hashtablecountries, hashtablenames);
                printf("Value has been inserted to the Bloom Filter and the SkipList.\n");

            }

            free(a);
            return 1;

        }


        if(strcmp(s1, "/vaccinateNow" ) ==0 )
        {
            char* id = s2;
            char* first = s3;
            char* second = s4;
            char* country = s5;
            char* age = s6;
            char* disease = s7;

            char* date= malloc (sizeof (char) * 10);
            int day, month, year;

            time_t present_time;
            time(&present_time);
            struct tm *local = localtime(&present_time);
            day = local->tm_mday;          // day
            month = local->tm_mon + 1;     // month
            year = local->tm_year + 1900;  // get year since 1900

            sprintf(date, "%02d-%02d-%d", day, month, year);

            printf("TODAYS DATE IS %s\n", date);


            char *a =  malloc (sizeof (char) * 16);
            strcpy(a, first);
            strcat(a, " ");
            strcat(a, second);
            printf("NAME is %s\n", a);

            struct node *temp = findp(size, hashtableviruses, s7);
            int checkflag2;
            checkflag2 = searchValue(s2, temp->vaccinated_persons);

          
            if(checkflag2 ==1)
            {
                SkipListNode_t *temp2 = NULL;
                temp2 = SkipListGetNode(temp->vaccinated_persons, (void *)atoi(id));

                printf("ERROR: CITIZEN %s ALREADY VACCINATED ON %s",s2,temp2->date);
            }
            else
            {
                if( searchValue(id, temp->not_vaccinated_persons) == 1 )  //ean uparxei stin not_vaccinated_persons vgale ton apo ekei
                deleteValue(id, temp->not_vaccinated_persons);

                unsigned long *buffer = hashing(id, K); //pinakas me ta K funcion results etoimos gia insert sto bloomfilter
                temp->bloom_filter =  BloomFilterInsert(M,K,temp->bloom_filter,buffer); //inserts a record (buffer of its K's hash function)
                free(buffer);
                printf("------------------------------------------------------------------------------------\n");
                insertotherValues(id, temp->vaccinated_persons, a, country, age, date, hashtablecountries, hashtablenames);
                printf("Value has been inserted to the Bloom Filter and the SkipList.\n");

            }

    
            free(date);
            free(a);

            return 1;

        }


        if(strcmp(s1, "/list-nonVaccinated-Persons" ) ==0 )
        {
            char* disease = s2;
            struct node *temp = findp(size, hashtableviruses, disease);
            // SkipListNode_t *temp2 = NULL;
            // temp2 = SkipListGetNode(temp->not_vaccinated_persons, (void *)atoi(id));
            printf("____________________________\n");
            printValue(temp->not_vaccinated_persons);

            return 1;
            
        }


        if(strcmp(s1, "/populationStatus" ) ==0 )
        {
            printf("\n");
            struct node *checkcountryargument = findp(size, hashtablecountries, s2);

            if(checkcountryargument != NULL)  //ean uparxei to argument ths xwras
            {
                char* country = s2;
                char* disease = s3;
                char* date1 = s4;
                char* date2 = s5;
                double percentage;

                if(strlen(date1) != strlen(date2)) //elegxos gia to ean uparxoun kai oi 2 imerominies
                {
                    printf("ERROR: in date arguments");
                    return 0;
                }
                

                struct node *temp = findp(size, hashtableviruses, disease);
                vaccinatedPopulationByCountry = 0; //global variable
                percentage = getVaccinationPercentage(country, date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);


                if(percentage < 0)
                    printf("ERROR: in date arguments");
                else
                {
                    printf("%s %d %f%c\n",country, vaccinatedPopulationByCountry, percentage, '%');
                }

            }

            if(checkcountryargument == NULL) ////ean DEN uparxei to argument ths xwras
            {
                
                char* disease = s2;
                char* date1 = s3;
                char* date2 = s4;

                if(strlen(date1) != strlen(date2)) //elegxos gia to ean uparxoun kai oi 2 imerominies
                {
                    printf("ERROR: in date arguments");
                    return 0;
                }
                
                printf("_________________________\n");
                createCountryBuffer(size, hashtablecountries);  //ftiaxnw enan pinaka me oles tis uparxouses as8eneies mexri twra
                int k;
                printf("_________________________\n");
                for(k = 0; k < 200; k++)
                {
                    if( strncmp(countryBuffer[k], "-1", 2) ==0 ) //stamata tin epanalispi otan teleiwsoyn oi as8eneies
                    break;
                    printf("_________________________\n");
                    //printf("%s ------ ", countryBuffer[k]);
                    double percentage;

                    struct node *temp = findp(size, hashtableviruses, disease);
                    vaccinatedPopulationByCountry = 0; //global variable
                    percentage = getVaccinationPercentage(countryBuffer[k], date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);

                    if(percentage < 0)
                        printf("ERROR: date1 > date2");
                    else
                    {
                        printf("%s %d %f%c\n",countryBuffer[k], vaccinatedPopulationByCountry, percentage, '%');
                    }                    
                }
            }

            return 1;
        }


        if(strcmp(s1, "/popStatusByAge" ) ==0 )
        {
             printf("\n");
            struct node *checkcountryargument = findp(size, hashtablecountries, s2);

            if(checkcountryargument != NULL)  //ean uparxei to argument ths xwras
            {
                char* country = s2;
                char* disease = s3;
                char* date1 = s4;
                char* date2 = s5;
                double percentage1, percentage2, percentage3, percentage4;
                

                if(strlen(date1) != strlen(date2)) //elegxos gia to ean uparxoun kai oi 2 imerominies
                {
                    printf("ERROR: in date arguments");
                    return 0;
                }
                

                struct node *temp = findp(size, hashtableviruses, disease);

                vaccinatedPopulationByCountry = 0; //global variable
                vaccinatedPopulationByCountry2 = 0; //global variable
                vaccinatedPopulationByCountry3 = 0; //global variable
                vaccinatedPopulationByCountry4 = 0; //global variable

                percentage1 = getVaccinationPercentageByAge(1, country, date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                percentage2 = getVaccinationPercentageByAge(2, country, date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                percentage3 = getVaccinationPercentageByAge(3, country, date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                percentage4 = getVaccinationPercentageByAge(4, country, date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);



                if(percentage1 < 0 || percentage2 < 0 || percentage3 < 0 || percentage4 < 0)
                    printf("ERROR: in date arguments");
                else
                {
                    printf("%s\n", country);
                    printf("0-20 %d %f%c\n", vaccinatedPopulationByCountry1, percentage1, '%');
                    printf("20-40 %d %f%c\n", vaccinatedPopulationByCountry2, percentage2, '%');
                    printf("40-60 %d %f%c\n", vaccinatedPopulationByCountry3, percentage3, '%');
                    printf("60+ %d %f%c\n", vaccinatedPopulationByCountry4, percentage4, '%');
                }

            }

            if(checkcountryargument == NULL) ////ean DEN uparxei to argument ths xwras
            {

                char* disease = s2;
                char* date1 = s3;
                char* date2 = s4;
                double percentage1, percentage2, percentage3, percentage4;

                if(strlen(date1) != strlen(date2)) //elegxos gia to ean uparxoun kai oi 2 imerominies
                {
                    printf("ERROR: in date arguments");
                    return 0;
                }
                

                createCountryBuffer(size, hashtablecountries);  //ftiaxnw enan pinaka me oles tis uparxouses as8eneies mexri twra
                int k;

                for(k = 0; k < 200; k++)
                {
                    if( strncmp(countryBuffer[k], "-1", 2) ==0 ) //stamata tin epanalispi otan teleiwsoyn oi as8eneies
                    break;

                    //printf("%s ------ ", countryBuffer[k]);
                    double percentage;

                    struct node *temp = findp(size, hashtableviruses, disease);

                    vaccinatedPopulationByCountry = 0;
                    vaccinatedPopulationByCountry1 = 0; //global variable
                    vaccinatedPopulationByCountry2 = 0; //global variable
                    vaccinatedPopulationByCountry3 = 0; //global variable
                    vaccinatedPopulationByCountry4 = 0; //global variable

                    percentage1 = getVaccinationPercentageByAge(1, countryBuffer[k], date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                    vaccinatedPopulationByCountry1 = vaccinatedPopulationByCountry;
                    vaccinatedPopulationByCountry = 0;
                    percentage2 = getVaccinationPercentageByAge(2, countryBuffer[k], date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                    vaccinatedPopulationByCountry2 = vaccinatedPopulationByCountry;
                    vaccinatedPopulationByCountry = 0;
                    percentage3 = getVaccinationPercentageByAge(3, countryBuffer[k], date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                    vaccinatedPopulationByCountry3 = vaccinatedPopulationByCountry;
                    vaccinatedPopulationByCountry = 0;
                    percentage4 = getVaccinationPercentageByAge(4, countryBuffer[k], date1, date2, temp->vaccinated_persons, temp->not_vaccinated_persons);
                    vaccinatedPopulationByCountry4 = vaccinatedPopulationByCountry;
            

                    if(percentage < 0)
                        printf("ERROR: date1 > date2");
                    else
                    {
                    printf("%s\n", countryBuffer[k]);
                    printf("0-20 %d %f%c\n", vaccinatedPopulationByCountry1, percentage1, '%');
                    printf("20-40 %d %f%c\n", vaccinatedPopulationByCountry2, percentage2, '%');
                    printf("40-60 %d %f%c\n", vaccinatedPopulationByCountry3, percentage3, '%');
                    printf("60+ %d %f%c\n", vaccinatedPopulationByCountry4, percentage4, '%');
                    }                    
                }
            }

            return 1;
        }


        if(strcmp(s1, "/exit" ) ==0 )
        {
            createDiseaseBuffer(size, hashtableviruses);  //ftiaxnw enan pinaka me oles tis uparxouses as8eneies mexri twra
            int k;

            for(k = 0; k < 20; k++)
            {
                if( strncmp(diseaseBuffer[k], "-1", 2) ==0 ) //stamata tin epanalispi otan teleiwsoyn oi as8eneies
                break;

                struct node *temp = findp(size, hashtableviruses, diseaseBuffer[k]);
                SkipListFree( temp->vaccinated_persons ); 
                SkipListFree( temp->not_vaccinated_persons ); 
                BloomFilterFree( temp->bloom_filter, M );

            }

            freeHashTable(size, hashtableviruses);
            freeHashTable(size, hashtablecountries);
            freeHashTable(size, hashtablenames);

            printf("Everything freed!\n");

            return -1;
        }

      printf("\n\nERROR: syntax error at the operation\nPlease try again!\n");   
}




int main(int argc, char *argv[])
{

    char* a=argv[1];
    char* b=argv[2];
    char* c=argv[3];
    char* d=argv[4];

    int size = 3;
    struct node *hashtableviruses[size];
    init(size, hashtableviruses); 

    struct node *hashtablecountries[size];
    init(size, hashtablecountries);

    struct node *hashtablenames[size];
    init(size, hashtablenames);

    printf("\n");
    
    if(argumentsCheck(a,b,c,d,argc) == 0) //kanei olous tous elegxous gia ta arguments pou dinoume kata tin ektelesi 
    {
        printf("Error in your Arguments!\n Please Try Again!\n");
        return 0;
    }
    else
        printf("Succesful Arguments Check!\n");


    int K = 16; //gia to bloomfilter
	int bloomsize = atoi(argv[4]); //last argument se bytes  (BloomSize)
	int M = bloomsize*8;

    FILE *inputfile=fopen(argv[2], "r");
    size_t linesiz=0;
    char* linebuf=0;
    ssize_t linelen=0;
    int i=1;

    while (linelen=getline(&linebuf, &linesiz, inputfile) > 0 ) //read the file line by line 
    {  
        process_line(linebuf, linesiz, M, K, hashtableviruses, hashtablecountries, hashtablenames, size);
        free(linebuf);
        linebuf=NULL;
        i++;
    }

    while(1)  //now we begin with the operations
    {
        int stopFlag = 0;
        printf("\n\nGive me an operation:\n");

        char operation[100];
        fgets(operation, 100, stdin);

        stopFlag = performTheOperation(operation, M, K, hashtableviruses, hashtablecountries, hashtablenames, size);
        printf("\n");

        if(stopFlag == -1)
        break;
    }

    return 1;

}

