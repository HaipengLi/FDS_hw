#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#define ERROR 1E8
/*#define DEBUG */

typedef int ElementType;
typedef struct stack
{
	int Capacity;
	int Top;
	ElementType *array;
}Stack;
typedef Stack* PtrToStack;
ElementType* p;

PtrToStack CreateStack(int);
int Push(ElementType,PtrToStack);
ElementType Pop(PtrToStack);

#ifndef DEBUG
int main(int argc, char const *argv[])
{
	/* code */
	PtrToStack S;
	int IsEmpty(PtrToStack S);
	int sequence[1000],i,j;
	int ri,flag=1,M,N,K;
	scanf("%d%d%d",&M,&N,&K);
	S=CreateStack(M);
	for(ri=0;ri<K;ri++)
	{
		flag=1;
		for(i=0;i<N;i++)
		{
			scanf("%d",&sequence[i]);
		}
		i=j=0;
		S->Top = -1;
		Push(++j,S);
		while(!(IsEmpty(S)))
		{
			while(p[S->Top]!=sequence[i])
			{
				flag=Push(++j,S);
				if(flag==0)/*Full -> NO*/
				{
					break;
				}
			}
			if(flag==0)/*Full -> NO*/
			{
				break;
			}
			i++;
			Pop(S);
			if(i==N)/*Complete -> YES*/
			{
				break;
			}
			if(IsEmpty(S))
				flag=Push(++j,S);
		}
		switch(flag)
		{
			case 0: printf("NO\n");break;
			case 1: printf("YES\n");break;
		}
	}
	free(p);
	return 0;
}
#else
int main(int argc, char const *argv[])
{
	PtrToStack S;
	int i;
	S=CreateStack(5);
	i=Push(1,S);
	i=Push(2,S);
	i=Push(3,S);
	i=Push(4,S);
	i=Push(5,S);
	i=Push(6,S);
	i=Pop(S);
	i=Pop(S);
	i=Pop(S);
	i=Pop(S);
	i=Pop(S);
	i=Pop(S);
	return 0;
}
#endif
PtrToStack CreateStack(int M)
{
	PtrToStack S;
	S=(PtrToStack)malloc(sizeof(Stack));
	S->array=(ElementType*)malloc(M*sizeof(ElementType));
	S->Capacity=M;
	S->Top=-1;
	p=S->array;
	return S;
}
int Push(ElementType X,PtrToStack S)
{
	int IsFull(PtrToStack S);
	if(IsFull(S))return 0;
	p[++S->Top]=X;
	return 1;
}
int Pop(PtrToStack S)
{
	int IsEmpty(PtrToStack S);
	int result;
	if(IsEmpty(S))return ERROR;
	result=p[S->Top--];
	return result;
}
int IsFull(PtrToStack S)
{
	if(S->Top==S->Capacity-1)return 1;
	return 0;
}
int IsEmpty(PtrToStack S)
{
	if(S->Top==-1)return 1;
	return 0;
}