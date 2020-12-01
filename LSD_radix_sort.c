#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Did not pad results with zeroes.

int radix;
int maxindex;

typedef struct BLOCK
{
    struct BLOCK* parent;
    int data;
}BLOCK;

void Reset(int array[])
{
    int i;
    for(i=0; i< radix+1; ++i)
    array[i] = 0;
}

void Transfer_To_Array(BLOCK* p, int array[], int i)
{
    array[i-1] = p->data;
    --i;

    if(i>0)
    Transfer_To_Array(p->parent, array, i);

    free(p);

}

int Largest_Element_Index(int array[], int i)
{
    int j;
    int LE = array[0];

    for(j=1; j<i; ++j)
    if(LE<array[j])
    LE = array[j];

    int k=0;
    while(LE>=pow(radix, k))
    ++k;

    return k;
}

void Sort(int array[], int counter[], int j)
{
    int i,k;
    int k_store[maxindex];
    int aux[maxindex];

    for(i=0; i<maxindex; ++i)
    {
        k_store[i] = (int)(array[i]/pow(radix,j))%radix;
        counter[k_store[i]+1]=counter[k_store[i]+1]+1;
    }

    for(i=0; i<radix; ++i)
    counter[i+1] = counter[i+1] + counter[i];

    for(i=0; i<maxindex; ++i)           
    {
        aux[counter[k_store[i]]] = array[i];
        counter[k_store[i]] = counter[k_store[i]] + 1;
    }

    for(i=0; i<maxindex; ++i)
    array[i] = aux[i];              
}

BLOCK* Link(int dummyint, BLOCK* dummyBLOCK)
{
    BLOCK* p = calloc(1, sizeof(BLOCK));

    (*p).parent = dummyBLOCK;
    (*p).data = dummyint;

    return p;
}

int main(int argc, char* argv[])
{   
    radix = atoi(argv[1]);
    int i=0;

    BLOCK* head = calloc(1, sizeof(BLOCK));
    int dummyint;
    BLOCK* dummyBLOCK = head;
    
    int counter [radix+1];
    
    while(scanf("%d", &dummyint)==1)
    {   
        dummyBLOCK = Link(dummyint, dummyBLOCK);
        ++i;
    }

    int array [i];
    Transfer_To_Array(dummyBLOCK, array, i);
    

    int k = Largest_Element_Index(array, i);

    maxindex = i;
    int j;

    for(j=0; j<k; ++j)
    {
        Reset(counter); 
        Sort(array, counter, j);
    }

    printf("\n");
    for(j=0; j<maxindex; j++)
    printf("%d  ",array[j]);

    return 0;
}