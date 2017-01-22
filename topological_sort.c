#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool TopSort( LGraph Graph, Vertex TopOrder[] );

int main()
{
    int i;
    Vertex TopOrder[MaxVertexNum];
    LGraph G = ReadG();

    if ( TopSort(G, TopOrder)==true )
        for ( i=0; i<G->Nv; i++ )
            printf("%d ", TopOrder[i]);
    else
        printf("ERROR");
    printf("\n");

    return 0;
}

/* Your function will be put here */
int InDegree[MaxVertexNum];
int Stack[MaxVertexNum];
int PtrToStack=-1;
void CalInDegree(LGraph G){
int i=0;
for(;i<G->Nv;i++){
PtrToAdjVNode p=G->G[i].FirstEdge;
while(p){
InDegree[p->AdjV]++;
p=p->Next;
}
}
}

bool TopSort( LGraph Graph, Vertex TopOrder[] ){
int Count=0;
CalInDegree(Graph);
int i;
for(i=0;i<Graph->Nv;i++){
if(InDegree[i]==0){
Stack[++PtrToStack]=i;
}
}
while(PtrToStack>=0){
TopOrder[Count++]=Stack[PtrToStack--];

PtrToAdjVNode p=Graph->G[TopOrder[Count-1]].FirstEdge;
while(p){
InDegree[p->AdjV]--;
if(InDegree[p->AdjV]==0){
Stack[++PtrToStack]=p->AdjV;
}
p=p->Next;
}




}
if(Count==Graph->Nv)return true;
else return false;
}