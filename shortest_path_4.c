#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
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

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S );

int main()
{
    int dist[MaxVertexNum], path[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, path, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", path[V]);
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
void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S ){
    int Known[Graph->Nv];
    int Num[Graph->Nv];
    int i;
    for(i=0;i<Graph->Nv;i++){
        Known[i]=0;
        dist[i]=INFINITY;
        path[i]=-1;
        Num[i]=INFINITY;
    }
    int CN=S;
    Known[S]=1;
    dist[S]=0;
    path[S]=-1;
    Num[S]=1;
    while(1){
        for(i=0;i<Graph->Nv;i++){
            if(Known[i])continue;
            if(Graph->G[CN][i]>0){
                if(Graph->G[CN][i]+dist[CN]<dist[i]){
                    //shorter
                    dist[i]=Graph->G[CN][i]+dist[CN];
                    path[i]=CN;
                    Num[i]=Num[CN]+1;
                }
                else if(Graph->G[CN][i]+dist[CN]==dist[i]){
                    if(Num[CN]+1<Num[i]){
                        //still shorter
                        path[i]=CN;
                        Num[i]=Num[CN]+1;
                    }
                }

            }

 
        }
                    //FindMin
           int Min=INFINITY;
            int MinN;
            for(i=0;i<Graph->Nv;i++){
                if(Known[i])continue;
                if(dist[i]<Min){
                    Min=dist[i];
                    MinN=i;
                }
            }
            if(Min==INFINITY)break;
            CN=MinN;
            Known[MinN]=1;
    }
    for(i=0;i<Graph->Nv;i++){
        if(dist[i]==INFINITY){
            dist[i]=-1;
            path[i]=-1;//essential 
        }

    }
}
/*
error 1: forget to set Known[CN] as 1
error 2: forget to set the unreachable points' distance as -1 and path as -1

*/