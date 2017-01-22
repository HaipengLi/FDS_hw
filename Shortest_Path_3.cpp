#include <stdio.h>
#include <stdlib.h>

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
MGraph ReadG()
{
    MGraph G=(MGraph)malloc(sizeof(struct GNode));
    int Row,Col,Weight;
    scanf("%d%d",&G->Nv,&G->Ne);
    for (int j = 0; j < G->Nv; ++j) {
        for (int i = 0; i < G->Nv; ++i) {
            G->G[j][i]=0;
        }
    }
    for (int i = 0; i < G->Ne; ++i) {
        scanf("%d%d%d",&Row,&Col,&Weight);
        G->G[Row][Col]=Weight;
    }
    return G;
}


/* Your function will be put here */
void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S )
{/*from V to S, we can regard all arrows to be reversed, that is, T[i][j]->T[j][i]*/
    int Sequence[Graph->Nv];/*the Sequence from near to far*/
    int Known[Graph->Nv];
    int PtrToSequence=-1;
    for (int i = 0; i < Graph->Nv; ++i)
    {
        /* code */
        dist[i]=INFINITY;
        count[i]=0;

        Known[i]=0;
    }
    dist[S]=0;
    Known[S]=1;
    count[S]=1;
    Sequence[++PtrToSequence]=S;
    while(PtrToSequence!=Graph->Nv-1)
    {
        int CurrentNode=Sequence[PtrToSequence];
        for (int i = 0; i < Graph->Nv; ++i)
        {
            if(Graph->G[CurrentNode][i]>0)/*adjacent*/
            {
                /*choose the smaller dist*/
                if(dist[i]>=(Graph->G[CurrentNode][i]+dist[CurrentNode]))
                {
                    if(dist[i]==(Graph->G[CurrentNode][i]+dist[CurrentNode]))
                    {
                        count[i]+=count[CurrentNode];
                    }
                    else {
                        count[i]=count[CurrentNode];
                        dist[i] = (Graph->G[CurrentNode][i] + dist[CurrentNode]);
                    }
                }
            }

        }
        int temp;
        int Min=INFINITY;
        for (int i = 0; i < Graph->Nv; ++i)/*choose the smallest node as CurrentNode*/
        {
            if (Known[i])
            {
                continue;
                /* code */
            }
            if (Min>dist[i])
            {
                temp=i;
                Min=dist[i];
                /* code */
            }
        }
        Sequence[++PtrToSequence]=temp;
        Known[temp]=1;
    }
    for (int i = 0; i < Graph->Nv; ++i)
    {
        if(dist[i]==INFINITY)
        {
            dist[i]=-1;
        }
        /* code */
    }
}