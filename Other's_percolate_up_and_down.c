#include <stdio.h>

int main(int argc, const char * argv[]) {
    int N, i, j, tmp, largest;
    int List[101], Target[101];
    
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", List + i);
    }
    for (i = 0; i < N; i++) {
        scanf("%d", Target + i);
    }
    for(i = 1; i < N; i++){
        if(Target[i] < Target[i - 1]){
            break;
        }
    }
    if(i == 1){
        printf("Heap Sort\n");
        for (i = N - 1; i >= 0; i--) {
            if(Target[i] < Target[0]){
                break;
            }
        }
        tmp = Target[i];
        Target[i] = Target[0];
        Target[0] = tmp;
        j = 0;
        while (1) {
            largest = j;
            if(j * 2 + 1 < i&&Target[j * 2 + 1] > Target[largest]){
                largest = j * 2 + 1;
            }
            if(j * 2 + 2 < i&&Target[j * 2 + 2] > Target[largest]){
                largest = j * 2 + 2;
            }
            if (largest != j) {
                tmp = Target[j];
                Target[j] = Target[largest];
                Target[largest] = tmp;
                j = largest;
            }
            else{
                break;
            }
        }
    }
    else{
        printf("Insertion Sort\n");
        tmp = Target[i];
        i--;
        while(i >= 0){
            if (Target[i] > tmp){
                Target[i + 1] = Target[i];
                i--;
            }
            else{
                break;
            }
        }
        Target[i + 1] = tmp;
    }
    for (i = 0; i < N; i++) {
        if (0 == i) {
            printf("%d", Target[i]);
        }
        else{
            printf(" %d", Target[i]);
        }
    }
}