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

int CountConnectedComponents( LGraph Graph );

int main()
{
    LGraph G = ReadG();
    printf("%d\n", CountConnectedComponents(G));

    return 0;
}

/* Your function will be put here */
int Known[MaxVertexNum];

void DFS(LGraph G, Vertex V){
if(Known[V])return;
Known[V]=1;
PtrToAdjVNode p=G->G[V].FirstEdge;
while(p){
DFS(G,p->AdjV);
p=p->Next;
}
}

int CountConnectedComponents( LGraph Graph ){
int count=0;
int i=0;
for(i=0;i<Graph->Nv;i++){
if(!Known[i]){
DFS(Graph,i);
count++;
}
}
return count;
}