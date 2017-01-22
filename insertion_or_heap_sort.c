#include <stdio.h>
#define MaxSize 100


void InsertionOneStep(int A[],int N,int index){
    //index means the index of the Element that needed to be sort now

    int temp=A[index];
    int i;
    for(i=index-1;i>=0&&temp<A[i];i--){
        A[i+1]=A[i];
    }
    A[i+1]=temp;
}

void HeapOneStep(int A[],int N,int index){
    //index means the index of the Element that needed to be sort now
    int Size=index;
    int temp=A[index];
    A[index]=A[0];
    A[0]=temp;
    //PercolateDown(0)
    temp=A[0];
    int ChildIndex=1;
    while((ChildIndex-1)/2<Size){
        if(ChildIndex+1<Size&&A[ChildIndex+1]>A[ChildIndex]){
            ChildIndex++;
        }
        if(A[ChildIndex]>temp){
            A[(ChildIndex-1)/2]=A[(ChildIndex)];
            ChildIndex=ChildIndex*2+1;
        }
        else{
            A[(ChildIndex-1)/2]=temp;
            break;
        }
    }
}
int main(int argc, char const *argv[])
{
    int N;
    int List[MaxSize];
    int Target[MaxSize];
    int index;
    scanf("%d",&N);
    int i;
    for (i = 0; i < N; ++i){
        scanf("%d",&List[i]);
    }
    for (i = 0; i < N; ++i){
        scanf("%d",&Target[i]);
    }
    //is insertion??
    i=0;
    while(i+1<N&&Target[i]<Target[i+1]){
        i++;
    }
    index=++i;
    for(;i<N;i++){
        if(Target[i]!=List[i]){
            break;
        }
    }
    if(i==N){//Insertion sort
        printf("Insertion Sort\n");
        InsertionOneStep(Target,N,index);
    }
    else{//Heap sort
        printf("Heap Sort\n");
        //calculate index of Heap Sort
        for(i=1;Target[0]>Target[i];i++){
        }
        index=i-1;
        HeapOneStep(Target,N,index);
    }
    for(i=0;i<N-1;i++){
        printf("%d ", Target[i]);
    }
    printf("%d", Target[N-1]);
    return 0;
}
