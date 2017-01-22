#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
Graph ReadG(){

}

int Visited[MaxVertices];
Vertex Stack[MaxVertices];
int PtrToStack=-1;
void Push(Vertex V){
	Stack[++PtrToStack]=V;
}


int DFS(PtrToVNode Node,PtrToVNode Map[],void (*Do)(Vertex V)){
	if(Visited[Node->Vert]>0)return 0;
	Visited[Node->Vert]=1;
	PtrToVNode p=Node->Next;
	while(p!=NULL){
		DFS(Map[p->Vert],Map,Do);
		p=p->Next;
	}
	(*Do)(Node->Vert);
	return 1;
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){

	int i,j;
	//Preparation

	//Reverse the 
	PtrToVNode p;
	PtrToVNode ReversedGraph[G->NumOfVertices]=(PtrToVNode*)malloc(G->NumOfVertices*(sizeof(struct VNode)));
	for(i=0;i<G->NumOfVertices;i++){
		p=G->Array[i]->Next;
		while(p!=NULL){
			//add
			PtrToVNode q=(PtrToVNode)malloc(sizeof(struct VNode));
			PtrToVNode r=ReversedGraph[p->Vert];
			while(r->Next!=NULL){
				r=r->Next;
			}
			r->Next=q;
			p=p->Next;
		}
	}

	//DFS
	for(i=0;i<G->NumOfVertices;i++){
		DFS(G->Array[i],G->Array,Push);	
	}
	for(i=0;i<G->NumOfVertices;i++){
		Visited[i]=-1;
	}
	while(PtrToStack>-1){
		p=ReversedGraph[Stack[PtrToStack--]];
		if(DFS(p,ReversedGraph,visit)){
			printf("\n");
		}
	}
}