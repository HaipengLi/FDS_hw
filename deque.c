#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}
Operation GetOp(){}
void PrintDeque( Deque D ){}



/* Your function will be put here */
int IsEmpty(Deque D){
return (D->Front==D->Rear);
}


Deque CreateDeque(){
Deque D=(Deque)malloc(sizeof(struct DequeRecord));
D->Front=D->Rear=(PtrToNode)malloc(sizeof(struct Node));
D->Front->Next=D->Front->Last=0;
return D;
}
int Push( ElementType X, Deque D ){
PtrToNode NewNode=(PtrToNode)malloc(sizeof(struct Node));
if(!NewNode)return 0;
NewNode->Element=X;
NewNode->Last=NewNode->Next=0;
if(IsEmpty(D)){
D->Rear=NewNode;
D->Front->Next=NewNode;
NewNode->Last=D->Front;

}
else{
NewNode->Next=D->Front->Next;
D->Front->Next->Last=NewNode;
D->Front->Next=NewNode;
NewNode->Last=D->Front;
}

return 1;}
ElementType Pop( Deque D ){
if(IsEmpty(D))return ERROR;
PtrToNode p=D->Front->Next;
ElementType Result=p->Element;
D->Front->Next=p->Next;
p->Next->Last=D->Front;
free(p);
return Result;
}
int Inject( ElementType X, Deque D ){
PtrToNode NewNode=(PtrToNode)malloc(sizeof(struct Node));
if(!NewNode)return 0;
NewNode->Element=X;
NewNode->Last=NewNode->Next=0;
D->Rear->Next=NewNode;
NewNode->Last=D->Rear;
D->Rear=NewNode;
return 1;
}
ElementType Eject( Deque D ){
if(IsEmpty(D))return ERROR;
PtrToNode p=D->Rear;
ElementType Result=p->Element;
p->Last->Next=NULL;
free(p);
return Result;
}