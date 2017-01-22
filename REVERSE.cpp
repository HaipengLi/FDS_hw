
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);

    return 0;
}

List Read()
{
    List head, p, tail;
    int Element;
    int size = sizeof(struct Node);
    head = tail = NULL;
    scanf("%d", &Element);
    while (Element != -1)
    {
        p = (List)malloc(size);
        p->Element = Element;
        if (head == NULL)
        {
            head = p;
            head->Next = NULL;
        }
        else
        {
            tail->Next = p;
            tail->Next->Next = NULL;
        }
        scanf("%d", &Element);
        tail = p;
    }
    return head;
}




List Reverse( List L )
{
    List NewList,p;
    List Nodes[100];
    int size=sizeof(struct Node);
    int i=0;
    NewList=L;
    L=L->Next;
    p=L;
    while(p)
    {
        Nodes[i]=(List)malloc(size);
        Nodes[i]->Element=p->Element;
        Nodes[i]->Next=NULL;
        p=p->Next;
        i++;
    }
    i--;
    L=NewList;
    while(i!=-1)
    {
        L->Next=Nodes[i];
        L=L->Next;
        i--;
    }
    return NewList;

}