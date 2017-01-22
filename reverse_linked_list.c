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
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */
List Reverse( List L ){
List head=L->Next;
if(!head||!(head->Next))return L;
List pp=head;
List p=head->Next;
while(p){
List pn=p->Next;
pp->Next=pn;
p->Next=head;
L->Next=p;
p=p->Next;
}
return L;
}