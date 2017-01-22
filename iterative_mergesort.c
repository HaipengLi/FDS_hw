#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
int s1,s2,e1,e2;
s1=0;

while(s1<N){
if((e1=s1+length-1)>=N-1)

{
    e1=N-1;
    int p1=s1,p=s1;
    while(p1<=e1)sorted[p++]=list[p1++];
    break;}
s2=s1+length;
e2=s1+2*length-1<N-1?s1+2*length-1:N-1;
int p1=s1,p2=s2,p=s1;

while(p1<=e1&&p2<=e2){
if(list[p1]<list[p2])sorted[p++]=list[p1++];
else sorted[p++]=list[p2++];
}
while(p1<=e1)sorted[p++]=list[p1++];
while(p2<=e2)sorted[p++]=list[p2++];
s1+=2*length;


}

}
/*error1: 
if(e1=s1+length-1>=N-1)

should be :
if((e1=s1+length-1)>=N-1)

assignment is less сеох than comparison


error 2:
when we find the reminding array is only one list: don't forget to copy it to sorted array.

*/