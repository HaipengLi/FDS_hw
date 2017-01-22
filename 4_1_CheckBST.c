#include <stdio.h>
#include <stdlib.h>
#define DEBUG
typedef struct TNode *BinTree;
struct TNode{
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST ( BinTree T, int K );
#ifndef DEBUG
int main()
{
    BinTree T;
    int K, out;

    T = BuildTree();
    scanf("%d", &K);
    out = CheckBST(T, K);
    if ( out < 0 )
        printf("No.  Height = %d\n", -out);
    else
        printf("Yes.  Key = %d\n", out);

    return 0;
}
#else
int main(int argc, char const *argv[])
{
    /* code */
    int i=0;
    BinTree T[9];
    for (; i < 9; ++i)
    {
        T[i]=(BinTree)malloc(sizeof(struct TNode));
        T[i]->Key=i;
        T[i]->Left=T[i]->Right=NULL;
    }
    T[0]->Key=10;
    T[5]->Key=100;
    T[3]->Left=T[2];
    T[1]->Right=T[3];
    T[4]->Left=T[1];
    T[5]->Left=T[4];
    T[5]->Right=T[6];
    T[6]->Right=T[0];
    T[0]->Left=T[7];
    T[7]->Right=T[8];
    /*T[5]is the root Node*/
    int Depth(BinTree T);
    i=Depth(T[8]);
    int Result=CheckBST (T[5], 5 );

    return 0;
}
#endif
/* 你的代码将被嵌在这里 */



int CheckBST ( BinTree T, int K )
{
    int Base[100];
    int CountNodes(BinTree);
    int InOrder(BinTree,int*,int);
    int N=CountNodes(T);
    int i,flag=1,Result;
    int Depth(BinTree);
    InOrder(T,Base,0);
    if(N==1)
    {
        return T->Key;
    }
    for (i = N-1; i >0; --i)
    {
        if(Base[i]<=Base[i-1])
        {
            flag=0;
            break;
        }
        if(i==N-K)
            Result=Base[i];
    }
    if (flag)
    {
        return Result;
        /* code */
    }
    else
    {
        return -Depth(T);
    }


}

int CountNodes(BinTree T)
{

    int Counts=1;
    if(T==NULL)return 0;
    if(T->Left>0)Counts+=CountNodes(T->Left);
    if(T->Right>0)Counts+=CountNodes(T->Right);
    return Counts;
}
int InOrder(BinTree T,int* Base,int start)
{
    if (T==NULL)
    {
        /* code */
        return start;
    }

    if(T->Left!=NULL)start=InOrder(T->Left,Base,start);

    {
        Base[start++]=T->Key;
    }
    if(T->Right!=NULL)start=InOrder(T->Right,Base,start);
    return start;
}
int Depth(BinTree T)
{
    if (T==NULL)
    {
        return 0;
        /* code */
    }
    else
    {
        int a,b;
        return (a=Depth(T->Left))>=(b=Depth(T->Right))?a+1:b+1;
        /* code */
    }
}