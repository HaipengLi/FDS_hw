#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXNUMOFSTATIONS 1010
#define INFINITE 100000
typedef  struct System* PtrToSystem;
struct System{
    int Capacity,NumOfStations,NumOfProblem,NumOfRoads;
    int CurrentNum[MAXNUMOFSTATIONS];
    int G[MAXNUMOFSTATIONS][MAXNUMOFSTATIONS];
};

int AllRecord[MAXNUMOFSTATIONS][MAXNUMOFSTATIONS];/*AllRecord[i][0~j] stores the previous stations' number, [0~j] means there could be more than one paths with the same time comsuming*/
int PtrToAllRecord[MAXNUMOFSTATIONS];
int AllPaths[MAXNUMOFSTATIONS][MAXNUMOFSTATIONS];
int NumOfShortestPath;

int main() {
    PtrToSystem NewSystem();
    PtrToSystem G;/*New system */
    int Time[MAXNUMOFSTATIONS];/*Sum of all time spent*/
    int Bikes[MAXNUMOFSTATIONS];/*the number of bikes needed, "<0" means taking back while ">0" means sending out*/
    int Path[MAXNUMOFSTATIONS];
    int IndexOfMin,MinSend,MinReceive;
    void Find(PtrToSystem G,int Time[]);/*Find Time[] and Bikes[]*/
    void FindBest(PtrToSystem G,int Bikes[],int Path[]);/*Find the path that need least number of bikes*/
    void OutPut(PtrToSystem G,int MinSend,int MinReceive,int Path[]);/*Output information*/
    void FindLeast(PtrToSystem G,int* IndexOfMin,int* MinSend,int* MinReceive);
    void ConvertToPath(PtrToSystem G);
    G=NewSystem();/*New system created*/
    Find(G,Time);/*Find AllRecord*/
    ConvertToPath(G);
    FindLeast(G,&IndexOfMin,&MinSend,&MinReceive);
    OutPut(G,MinSend,MinReceive,AllPaths[IndexOfMin]);/*Output information*/
    return 0;

}
PtrToSystem NewSystem(){/*to create a new system*/
    PtrToSystem G=(PtrToSystem)malloc(sizeof(struct System));/*New System*/
    if(G==NULL)return NULL;
    scanf("%d %d %d %d",&G->Capacity,&G->NumOfStations,&G->NumOfProblem,&G->NumOfRoads);/*Essential Information Input*/
    for (int i = 1; i <= G->NumOfStations; ++i) {/*for each station*/
        scanf("%d",G->CurrentNum+i);/*Essential Information Input*/
    }
    G->CurrentNum[0]=0;
    for (int i = 0; i <= G->NumOfRoads; ++i) {/*all to be 0*/
        for (int j = 0; j <= G->NumOfRoads; ++j) {
            G->G[i][j]=0;/*all to be 0*/
        }
    }
    for (int i = 1; i <= G->NumOfRoads; ++i) {/*for each station*/
        int A,B,Time;/*temp variables*/
        scanf("%d %d %d",&A,&B,&Time);/*Essential Information Input*/
        G->G[B][A]=G->G[A][B]=Time;/*Essential Information Input*/
    }
    return G;
}
void Find(PtrToSystem G,int Time[]){

    int Known[G->NumOfStations+1];
    int findmin(PtrToSystem,int[],int[]);
    int CurrentStation=0;
    for (int i = 0; i <=G->NumOfStations ; ++i) {
        Time[i]=INFINITE;/*pretreatment*/
        Known[i]=-1;/*pretreatment*/
        PtrToAllRecord[i]=-1;
    }
    Known[0]=1;/*pretreatment*/
    Time[0]=0;/*pretreatment*/
    while(1){/*do it until all done*/
        for (int i = 0; i <= G->NumOfStations; ++i) {/*traverse all stations that are Unknown*/
            if(G->G[CurrentStation][i]>0){/*if Unknown*/
                if (Time[i] >= (G->G[CurrentStation][i] + Time[CurrentStation])){/*find a path with less or equal time*/

                    if (Time[i] == (G->G[CurrentStation][i] + Time[CurrentStation])){/*if equal time, compare the bikes requirement*/
                        /*create a new line in AllRecord*/
                        AllRecord[++NumOfShortestPath][i]=CurrentStation;/*save the path of previous stations*/
                        for (int j = 0; j <= G->NumOfStations; ++j) {
                            if(!Known[j])continue;
                            if(j==i)continue;
                            AllRecord[NumOfShortestPath][j]=AllRecord[NumOfShortestPath-1][j];
                        }
                    }
                    else {
                        Time[i] = (G->G[CurrentStation][i] + Time[CurrentStation]);/*find a path with less time*/
                        for (int j = 0; j <= NumOfShortestPath; ++j) {
                            AllRecord[j][i]=CurrentStation;
                        }
                    }
                }

            }
        }
        CurrentStation=findmin(G,Time,Known);/*find next station*/
        if(CurrentStation==-1)break;/*all done, exit loop*/
        Known[CurrentStation]=1;/*mark the flag of Known*/
    }


}
void FindLeast(PtrToSystem G,int* IndexOfMin,int* MinSend,int* MinReceive) {
    *MinSend=INFINITE;
    *MinReceive=INFINITE;
    int CurrentRequirementOfSend;
    int CurrentRequirementOfReceive;
    void Calculate(PtrToSystem G,int i,int*CurrentRequirementOfSend,int*CurrentRequirementOfReceive);
    for(int i=0;i<=NumOfShortestPath;i++){/*Calculate the num needed to sent*/
        Calculate(G,i,&CurrentRequirementOfSend,&CurrentRequirementOfReceive);
        if (*MinSend>=CurrentRequirementOfSend){
            if(*MinSend==CurrentRequirementOfSend){
                if(*MinReceive>CurrentRequirementOfReceive){
                    *IndexOfMin=i;
                    *MinReceive=CurrentRequirementOfReceive;
                }
            }
            else{
                *MinSend=CurrentRequirementOfSend;
                *MinReceive=CurrentRequirementOfReceive;
                *IndexOfMin=i;
            }

        }
    }

}

void Calculate(PtrToSystem G,int i,int*CurrentRequirementOfSend,int*CurrentRequirementOfReceive){
    int CurrentNum=AllPaths[i][1];
    int PtrToIndex=1;
    int Requirement;/*Requirement For current single station*/
    *CurrentRequirementOfReceive=*CurrentRequirementOfSend=0;
    while(AllPaths[i][PtrToIndex-1]!=G->NumOfProblem){
        Requirement=G->Capacity/2-G->CurrentNum[CurrentNum];
        if(Requirement>0)/*Need send*/{
            if(*CurrentRequirementOfReceive-Requirement<0){/*No enough to provide, so we have to send them from 0*/
                *CurrentRequirementOfSend+=Requirement-*CurrentRequirementOfReceive;
                *CurrentRequirementOfReceive=0;
            }
            else{/*what we received can afford this station*/
                *CurrentRequirementOfReceive-=Requirement;
            }
        }
        else{/*need receive*/
            *CurrentRequirementOfReceive+=-(Requirement);
        }
        CurrentNum=AllPaths[i][++PtrToIndex];
    }
}
int findmin(PtrToSystem graph, int t[], int know[])
{
    int i;
    int count;
    int min;
    count=0;
    for (min = 0; min<=graph->NumOfStations; min++){
        if (know[min] == -1)/*find first Unknown station*/
            break;/*exit the loop*/
    }
    for (i = 0; i<=graph->NumOfStations; i++){
        if (t[min]>t[i] && know[i] == -1)/*compare and save smaller one*/
            min = i;
        if (know[i] == 1)/*next station to be checked*/
            count++;
    }
    if (count != graph->NumOfStations+1)
        return min;/*return min*/
    else return -1;/*fail to find*/
}
void ConvertToPath(PtrToSystem G) {/*use Stack to Convert Records into Paths*/
    int Stack[G->NumOfStations+1];
    int PtrToOnePath;
    int PtrToStack = -1;
    int i;
    for(int j=0;j<=NumOfShortestPath;j++){
        PtrToOnePath = -1;
        i = G->NumOfProblem;
        while (  i != 0) {
            Stack[++PtrToStack] = i;/*push one by one*/
            i = AllRecord[j][i];
        }
        Stack[++PtrToStack]=0;
        while (PtrToStack >= 0) {
            AllPaths[j][++PtrToOnePath] = Stack[PtrToStack--];/*pop to AllPaths*/
        }
        AllPaths[j][++PtrToOnePath]=-1;/*the mark of end*/
    }

}
void OutPut(PtrToSystem G,int MinSend,int MinReceive,int Path[]){
    int Out=0, In=0;
    int i=1;
    printf("%d 0",MinSend);
    while(Path[i]!=-1){
        printf("->%d",Path[i]);/*Out information*/
        i++;
    }
    printf(" %d\n",MinReceive);/*Out information*/
}