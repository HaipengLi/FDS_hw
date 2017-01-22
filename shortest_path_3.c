#include <stdio.h>
#include <stdlib.h>

// typedef enum {false, true} bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S );

int main()
{
    int dist[MaxVertexNum], count[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, count, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", count[V]);
    printf("\n");

    return 0;
}
MGraph ReadG(){
    MGraph G=(MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d",&G->Nv,&G->Ne);
    
    int i,a,b,c;
    for(i=0;i<G->Nv;i++){
        int j;
        for(j=0;j<G->Nv;j++){
            G->G[i][j]=0;
        }
    }
    for(i=0;i<G->Ne;i++){
        scanf("%d %d %d",&a,&b,&c);
        G->G[a][b]=c;
    }
    return G;
}
/* Your function will be put here */



void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S ){
int Known[MaxVertexNum];
Vertex CN;
int i;
for(i=0;i<Graph->Nv;i++){Known[i]=0;count[i]=0;dist[i]=INFINITY;}
CN=S;
Known[CN]=1;
dist[CN]=0;
count[CN]=1;
while(1){
	for(i=0;i<Graph->Nv;i++){
        if(Known[i])continue;
	if(Graph->G[CN][i]>0){
		//there is a path
		if(Graph->G[CN][i]+dist[CN]<dist[i]){//shorter
            dist[i]=Graph->G[CN][i]+dist[CN];
            count[i]=count[CN];
        }
        else if(Graph->G[CN][i]+dist[CN]==dist[i]){
        //equal to 
            count[i]+=count[CN];    
        }
		}	
	}
    //FindMin
    int Min=INFINITY;
    int MinN=INFINITY;
    for(i=0;i<Graph->Nv;i++){
        if(Known[i])continue;
        if(dist[i]<Min){
            Min=dist[i];
            MinN=i;
        }
    }
    if(MinN==INFINITY)break;
    Known[MinN]=1;
    CN=MinN;
}
for(i=0;i<Graph->Nv;i++){
    if(dist[i]==INFINITY){
        dist[i]=-1;
        count[i]=0;
    }
}
}
/*
error1: confuse "break"&"continue"
error2: no..
*/