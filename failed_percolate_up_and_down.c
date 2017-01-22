#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H )
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H )
{
    ElementType MinElement;
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement;
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}
PriorityQueue Initialize( int MaxElements ){
    PriorityQueue H=(PriorityQueue) malloc(sizeof(struct HeapStruct));
    H->Elements=(ElementType*)malloc(MaxElements*sizeof(ElementType));
    H->Capacity=MaxElements;
    H->Size=0;
    return H;
}





/* Your function will be put here */
void PercolateUp( int p, PriorityQueue H ){
    ElementType Temp=H->Elements[p];
    while(p/2>0&&Temp<H->Elements[p/2]){
        H->Elements[p]=H->Elements[p/2];
        p/=2;
    }
    H->Elements[p]=Temp;
}
void PercolateDown( int p, PriorityQueue H ){
    ElementType Temp=H->Elements[p];
    int ChildIndex=2*p;
    while(ChildIndex/2<=H->Size){
        if(ChildIndex<H->Size&&H->Elements[ChildIndex+1]<H->Elements[ChildIndex]){
            ChildIndex++;
        }
        if(Temp>H->Elements[ChildIndex]){
            H->Elements[ChildIndex/2]=H->Elements[ChildIndex];
            ChildIndex*=2;
        }
        else{
            H->Elements[ChildIndex/2]=Temp;
            break;
        }
    }
}