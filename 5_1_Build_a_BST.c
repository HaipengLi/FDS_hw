#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode* Tree;
struct TreeNode
{
    int Element;
    int Left;
    int Right;
};
Tree PtrToTree;
int* Data;

void InsetToBST(int start,Tree node){
    int CountNodes(Tree);
    if (node->Left != -2){
        int begin = start;
        int stop = start + CountNodes(PtrToTree+node ->Left);
        node->Element = Data[stop];
        InsetToBST(begin,PtrToTree + node->Left);
        begin = stop + 1;
        stop = begin + CountNodes(PtrToTree+node->Right);
        InsetToBST(begin,PtrToTree + node->Right);
    }

}


int main(int argc, char const *argv[])
{
    int i,N;
    void insertion_sort(int,int[]);
    void Match(Tree,int*,int);
    void LevelOrder(Tree);

    scanf("%d",&N);
    PtrToTree=(Tree)malloc((N+1)*sizeof(struct TreeNode));
    Data=(int *)malloc(N*sizeof(int));
    PtrToTree->Element=PtrToTree->Left=PtrToTree->Right=-2;
    PtrToTree++;
    for(i=0;i<N;i++)
    {
        scanf("%d %d",&PtrToTree[i].Left,&PtrToTree[i].Right);
        (PtrToTree+i)->Element=0;
    }
    for (i=0; i < N; ++i)
    {
        scanf("%d",Data+i);
        /* code */
    }
    insertion_sort(N,Data);
   	InsetToBST(0,PtrToTree);

    LevelOrder(PtrToTree);
    /* code */
    return 0;
}
void insertion_sort(int N ,int unsorted[] )
{
    for (int i = 1; i < N; i++)
    {
        if (unsorted[i - 1] > unsorted[i])
        {
            int temp = unsorted[i];
            int j = i;
            while (j > 0 && unsorted[j - 1] > temp)
            {
                unsorted[j] = unsorted[j - 1];
                j--;
            }
            unsorted[j] = temp;
        }
    }
}
void Match(Tree PtrToTree,int* Data,int N)
{
    int i;
    int CountNodes(Tree);
    int temp;
    int j;
    int start[N];
    if(PtrToTree->Element==-2)return;
    for(i=0;i<N;i++)
    {
        start[i]=0;
    }
    for (i = 0; i < N; ++i)
    {
        j=0;
        temp=0;
        while(start[j++]!=0)temp+=1;
        PtrToTree[i].Element=Data[temp+CountNodes(&PtrToTree[(PtrToTree+i)->Left])];
        start[temp+CountNodes(&PtrToTree[(PtrToTree+i)->Left])]=1;
    }
}
int CountNodes(Tree T)
{

    int Counts=1;
    if(T->Element==-2)return 0;
    if(T->Left==-1&&T->Right==-1)
        return 1;
    else
    {
        if(T->Left>0)Counts+=CountNodes(PtrToTree+T->Left);
        if(T->Right>0)Counts+=CountNodes(PtrToTree+T->Right);
    }
    return Counts;
}
void LevelOrder(Tree T)
{
    if (T->Element==-2)/*Emply Tree*/
    {
        return;
    }
    Tree Queue[100];
    int count=0;
    int Front=-1,Rear=-1;
    Queue[++Rear]=T;
    while(Rear!=Front)
    {
        T=Queue[++Front];
        if (count==0)
        {
            count=1;
            printf("%d",T->Element);
        }
        else printf(" %d",T->Element);
        if(T->Left!=-1)Queue[++Rear]=PtrToTree+T->Left;
        if(T->Right!=-1)Queue[++Rear]=PtrToTree+T->Right;
    }
}