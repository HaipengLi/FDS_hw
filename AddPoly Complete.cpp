#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Add(Polynomial a, Polynomial b);

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    return 0;
}
Polynomial Read()
{
    Polynomial head, p, tail;
    int Coefficient, Exponent;
    int size = sizeof(struct Node);
    head = tail = NULL;
    scanf("%d%d", &Coefficient, &Exponent);
    while (Exponent != -1)
    {
        p = (Polynomial)malloc(size);
        p->Coefficient = Coefficient;
        p->Exponent = Exponent;
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
        scanf("%d%d", &Coefficient, &Exponent);
        tail = p;
    }
    return head;
}
Polynomial Add( Polynomial a, Polynomial b )  
{  
    Polynomial c;  
    c=(Polynomial)malloc(sizeof(struct Node));  
    c->Next=NULL;  
    a=a->Next;  
    b=b->Next;  
    Polynomial temp=c;  
    while(a&&b){  
        if(a->Exponent>b->Exponent){  
            temp->Next=a;  
            a=a->Next;  
            temp->Next->Next=NULL;  
            temp=temp->Next;  
  
        }  
        else if(b->Exponent>a->Exponent){  
            temp->Next=b;  
            b=b->Next;  
            temp->Next->Next=NULL;  
            temp=temp->Next;  
        }  
        else{  
            Polynomial t;  
            t=(Polynomial)malloc(sizeof(struct Node));  
            t->Coefficient=a->Coefficient+b->Coefficient;  
            t->Exponent=a->Exponent;  
            t->Next=NULL;  
            if(t->Coefficient!=0){  
                temp->Next=t;  
                temp=temp->Next;  
            }  
            a=a->Next;  
            b=b->Next;  
        }  
    }  
    while(a){  
        temp->Next=a;  
        temp=temp->Next;  
        a=a->Next;  
    }  
    while(b){  
        temp->Next=b;  
        temp=temp->Next;  
        b=b->Next;  
    }  
    temp->Next=NULL;  
    return c;  
}  