#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
        case push: 
            scanf("%d %d", &Sn, &X);
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}
Operation GetOp(){} /* details omitted */
void PrintStack( Stack S, int Stacknum ){}
/* Your function will be put here */


Stack CreateStack( int MaxElements ){
Stack S=(Stack)malloc(sizeof(struct StackRecord));
S->Capacity=MaxElements;
S->Array=(ElementType*)malloc(MaxElements*sizeof(ElementType));
S->Top1=-1;
S->Top2=MaxElements;
return S;
}
int IsEmpty( Stack S, int Stacknum ){
switch(Stacknum){
case 1: {
	if(S->Top1==-1)return 1;
	else return 0;break;
}
case 2: {
	return (S->Top2==S->Capacity);break;

}
}
}
int IsFull( Stack S ){
	return (S->Top2-S->Top1==1);
}
int Push( ElementType X, Stack S, int Stacknum ){
	if(IsFull(S))return ERROR;
switch(Stacknum){
case 1: S->Array[++S->Top1]=X;break;
case 2: S->Array[--S->Top2]=X;break;
}
return 1;
}
ElementType Top_Pop( Stack S, int Stacknum ){
if(IsEmpty(S,Stacknum))return ERROR;
switch(Stacknum){
case 1: return S->Array[S->Top1--];break;
case 2: return S->Array[S->Top2++];break;
}
}