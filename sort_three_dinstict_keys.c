#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void Read( ElementType A[], int N ); /* details omitted */

void MySort( ElementType A[], int N );

void PrintA( ElementType A[], int N )
{
    int i, k;

    k = i = 0;
    for ( ; i<N && A[i]==false; i++ );
    if ( i > k )
        printf("false in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==maybe; i++ );
    if ( i > k )
        printf("maybe in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==true; i++ );
    if ( i > k )
        printf("true in A[%d]-A[%d]\n", k, i-1);
    if ( i < N )
        printf("Wrong Answer\n");
}

int main()
{
    int N;
    ElementType *A;

    scanf("%d", &N);
    A = (ElementType *)malloc(N * sizeof(ElementType));
    Read( A, N );
    MySort( A, N );
    PrintA( A, N );
    return 0;
}

/* Your function will be put here */
void MySort( ElementType A[], int N ){
int NumOfFalse=0;
int NumOfMaybe=0;
int NumOfTrue=0;
int i=0;
for(;i<N;i++){
switch(A[i]){
case false:NumOfFalse++;break;
case maybe:NumOfMaybe++;break;
default: NumOfTrue++;break;
}
}
for(i=0;i<NumOfFalse;i++){
A[i]=false;
}
for(;i<NumOfFalse+NumOfMaybe;i++){
A[i]=maybe;
}
for(;i<N;i++){
A[i]=true;
}
}