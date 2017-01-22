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


/* Your function will be put here */
int findmin(MGraph graph, int d[], int know[])
{
    int i;
    int count = 0;
    int min;
    for (min = 0; min<graph->Nv; min++){
        if (know[min] == -1)
            break;
    }
    for (i = 0; i<graph->Nv; i++){
        if (d[min]>d[i] && know[i] == -1)
            min = i;
        if (know[i] == 1)
            count++;
    }
    if (count != graph->Nv)
        return min;
    else return -1;
}
void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
    int Known[Graph->Nv];
    int NumOfEdges[Graph->Nv];

    for (int i = 0; i < Graph->Nv; ++i)
    {
        /* code */
        dist[i] = INFINITY;
        NumOfEdges[i] = INFINITY;
        Known[i] = -1;
    }
    dist[S] = 0;
    Known[S] = 1;
    NumOfEdges[S]=1;
    path[S]=-1;
    int CurrentNode = S;
    while (1)
    {

        for (int i = 0; i < Graph->Nv; ++i)
        {
            if (Graph->G[CurrentNode][i]>0)/*adjacent*/
            {
                /*choose the smaller dist*/
                if (dist[i] >= (Graph->G[CurrentNode][i] + dist[CurrentNode]))
                {
                    if (dist[i] == (Graph->G[CurrentNode][i] + dist[CurrentNode]))
                    {
                        if(NumOfEdges[i]>1+NumOfEdges[CurrentNode])
                        {
                            NumOfEdges[i]=1+NumOfEdges[CurrentNode];
                            path[i]=CurrentNode;
                        }
                    }
                    else {
                        dist[i] = (Graph->G[CurrentNode][i] + dist[CurrentNode]);
                        NumOfEdges[i]=1+NumOfEdges[CurrentNode];
                        path[i]=CurrentNode;
                    }
                }
            }

        }
        CurrentNode = findmin(Graph, dist, Known);
        if (CurrentNode == -1)break;

        Known[CurrentNode] = 1;
    }
    for (int i = 0; i < Graph->Nv; ++i)
    {
        if (dist[i] == INFINITY)
        {
            dist[i] = -1;
            path[i]=-1;
        }
        /* code */
    }
}