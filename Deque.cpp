#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5


#define DEBUG 1


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
int Push(ElementType X, Deque D);
ElementType Pop(Deque D);
int Inject(ElementType X, Deque D);
ElementType Eject(Deque D);

Operation GetOp();          /* details omitted */
void PrintDeque(Deque D); /* details omitted */
#ifndef DEBUG
int main()/*NORMAL RUN*/
{
	ElementType X;
	Deque D;
	int done = 0;

	D = CreateDeque();
	while (!done) {
		switch (GetOp()) {
		case push:
			scanf("%d", &X);
			if (!Push(X, D)) printf("Memory is Full!\n");
			break;
		case pop:
			X = Pop(D);
			if (X == ERROR) printf("Deque is Empty!\n");
			break;
		case inject:
			scanf("%d", &X);
			if (!Inject(X, D)) printf("Memory is Full!\n");
			break;
		case eject:
			X = Eject(D);
			if (X == ERROR) printf("Deque is Empty!\n");
			break;
		case end:
			PrintDeque(D);
			done = 1;
			break;
		}
	}
	return 0;
}
#else
int main(int argc, char const *argv[])/*DEGUB*/
{
	ElementType X;
	Deque D;
	int done = 0;

	D = CreateDeque();
	Push(1, D);
	Push(2, D);
	Push(3, D);
	done = Pop(D);
	done = Pop(D);
	done = Pop(D);
	Inject(1, D);
	Inject(2, D);
	done = Eject(D);
	done = Eject(D);
	return 0;
}
#endif
Deque CreateDeque()
{
	Deque p;
	p = (Deque)malloc(sizeof(struct DequeRecord));
	p->Front = (PtrToNode)malloc(sizeof(struct Node));
	p->Front->Last = NULL;
	p->Rear = p->Front;
	p->Rear->Next = NULL;
	return p;
}
int Push(ElementType X, Deque D)
{
	PtrToNode p;
	p=(PtrToNode)malloc(sizeof(struct Node));
	if(p==NULL)return 0;
	p->Element=X;
	if(D->Front==D->Rear)/*empty deque*/
	{
		D->Rear=p;
		D->Front->Next=p;
		p->Last=D->Front;
		p->Next=NULL;
	}
	else
	{
		D->Front->Next->Last=p;
		p->Next=D->Front->Next;
		p->Last=D->Front;
		D->Front->Next=p;
	}
	return 1;
}
ElementType Pop(Deque D)
{
	ElementType result;
	PtrToNode p;
	if(D->Front==D->Rear)/*Empty Deque*/
		return ERROR;
	p=D->Front->Next;
	result=p->Element;
	if(p==D->Rear)/*single Element*/
		{
			D->Front->Next=NULL;
			D->Rear = D->Front;
		}
	else/*more than one Element*/
	{
		D->Front->Next=p->Next;
		p->Next->Last=D->Front;
	}
	free(p);
	return result;
}
int Inject(ElementType X, Deque D)
{
	PtrToNode p;
	p=(PtrToNode)malloc(sizeof(struct Node));
	if(p==NULL)return 0;
	p->Element=X;
	D->Rear->Next=p;
	p->Last=D->Rear;
	p->Next=NULL;
	D->Rear=p;
	return 1;
}
ElementType Eject(Deque D)
{
	ElementType result;
	PtrToNode p;
	if(D->Front==D->Rear)
		return ERROR;
	p=D->Rear;
	result=p->Element;
	D->Rear=p->Last;
	D->Rear->Next=NULL;
	free(p);
	return result;
}