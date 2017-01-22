#include <stdio.h>
#define MaxSize 1000

int Network[MaxSize];

int main(int argc, char const *argv[])
{
	int N;
	int components;
	char Command;
	int C1,C2;
	void Connect(int,int);
	int CheckConnection(int,int);
	int CountZero(int Size);
	scanf("%d",&N);

	Command=getchar();
	while(Command!='S')
	{
		scanf("%d%d",&C1,&C2);
		switch(Command)
		{
			case 'I':
				Connect(C1,C2);
				break;
			case 'C':
				if (CheckConnection(C1,C2))
				{
					Printf("yes\n");
				}
				else
				{
					Printf("no\n");
				}

		}
		Command=getchar();
	}
	components=CountZero(N);
	if(components)
	{
		printf("The network is connected.\n");
	}
	else
	{
		printf("There are %d components.\n", components);
	}
	return 0;
}
void Connect(int A,int B)
{
/*Find the roots of A and B then Connect Two Root*/
	A=Find(A);
	B=Find(B);
	Network[B]=A;
}
int CheckConnection(int A,int B)
{
	return (Find(A)==Find(B));
}
int Find(int A)
{

	while(Network[A]!=0)
	{
		A=Network[A];
	}
	return A;
}
int CountZero(int Size)
{
	int Result=0,i;
	for(i=0;i<Size;i++)
	{
		if (Network[i]==0)
		{
			Result++;
			/* code */
		}
	}
	return Result;
}