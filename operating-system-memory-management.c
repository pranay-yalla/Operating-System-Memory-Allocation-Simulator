#include <stdio.h>

#define MAX 50

void copyArray(int dest[], int src[], int n){
    for(int i=0;i<n;i++)
        dest[i]=src[i];
}

int firstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    int tempBlocks[MAX];
    int totalFrag=0;

    copyArray(tempBlocks,blockSize,m);

    for(int i=0;i<n;i++)
        allocation[i]=-1;

    printf("\n----- First Fit Allocation -----\n");
    printf("------------------------------------------------------------\n");
    printf("Process\tSize\tBlock Allocated\tBlock Size\tFragmentation\n");
    printf("------------------------------------------------------------\n");

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(tempBlocks[j] >= processSize[i]){
                allocation[i]=j;
                int frag=tempBlocks[j]-processSize[i];
                totalFrag+=frag;

                printf("Process %d\t%d\tBlock %d\t\t%d\t\t%d\n",
                       i+1,processSize[i],j+1,blockSize[j],frag);

                tempBlocks[j]=0;
                break;
            }
        }

        if(allocation[i]==-1){
            printf("Process %d\t%d\tNot Allocated\n",i+1,processSize[i]);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("Total Fragmentation: %d\n",totalFrag);

    return totalFrag;
}

int bestFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    int tempBlocks[MAX];
    int totalFrag=0;

    copyArray(tempBlocks,blockSize,m);

    for(int i=0;i<n;i++)
        allocation[i]=-1;

    printf("\n----- Best Fit Allocation -----\n");
    printf("------------------------------------------------------------\n");
    printf("Process\tSize\tBlock Allocated\tBlock Size\tFragmentation\n");
    printf("------------------------------------------------------------\n");

    for(int i=0;i<n;i++){
        int bestIndex=-1;

        for(int j=0;j<m;j++){
            if(tempBlocks[j]>=processSize[i]){
                if(bestIndex==-1 || tempBlocks[j]<tempBlocks[bestIndex])
                    bestIndex=j;
            }
        }

        if(bestIndex!=-1){
            allocation[i]=bestIndex;
            int frag=tempBlocks[bestIndex]-processSize[i];
            totalFrag+=frag;

            printf("Process %d\t%d\tBlock %d\t\t%d\t\t%d\n",
                   i+1,processSize[i],bestIndex+1,blockSize[bestIndex],frag);

            tempBlocks[bestIndex]=0;
        }
        else{
            printf("Process %d\t%d\tNot Allocated\n",i+1,processSize[i]);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("Total Fragmentation: %d\n",totalFrag);

    return totalFrag;
}

int worstFit(int blockSize[], int m, int processSize[], int n){
    int allocation[MAX];
    int tempBlocks[MAX];
    int totalFrag=0;

    copyArray(tempBlocks,blockSize,m);

    for(int i=0;i<n;i++)
        allocation[i]=-1;

    printf("\n----- Worst Fit Allocation -----\n");
    printf("------------------------------------------------------------\n");
    printf("Process\tSize\tBlock Allocated\tBlock Size\tFragmentation\n");
    printf("------------------------------------------------------------\n");

    for(int i=0;i<n;i++){
        int worstIndex=-1;

        for(int j=0;j<m;j++){
            if(tempBlocks[j]>=processSize[i]){
                if(worstIndex==-1 || tempBlocks[j]>tempBlocks[worstIndex])
                    worstIndex=j;
            }
        }

        if(worstIndex!=-1){
            allocation[i]=worstIndex;
            int frag=tempBlocks[worstIndex]-processSize[i];
            totalFrag+=frag;

            printf("Process %d\t%d\tBlock %d\t\t%d\t\t%d\n",
                   i+1,processSize[i],worstIndex+1,blockSize[worstIndex],frag);

            tempBlocks[worstIndex]=0;
        }
        else{
            printf("Process %d\t%d\tNot Allocated\n",i+1,processSize[i]);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("Total Fragmentation: %d\n",totalFrag);

    return totalFrag;
}

int main(){

    int m,n;
    int blockSize[MAX];
    int processSize[MAX];

    printf("Memory Allocation Simulator\n");

    printf("Enter number of memory blocks: ");
    scanf("%d",&m);

    if(m<=0){
        printf("Invalid number of blocks.\n");
        return 0;
    }

    printf("\nEnter sizes of memory blocks:\n");
    for(int i=0;i<m;i++){
        printf("Enter size of Block %d: ",i+1);
        scanf("%d",&blockSize[i]);

        if(blockSize[i]<=0){
            printf("Invalid block size.\n");
            return 0;
        }
    }

    printf("\nEnter number of processes: ");
    scanf("%d",&n);

    if(n<=0){
        printf("No processes to allocate.\n");
        return 0;
    }

    printf("\nEnter sizes of processes:\n");
    for(int i=0;i<n;i++){
        printf("Enter size of Process %d: ",i+1);
        scanf("%d",&processSize[i]);

        if(processSize[i]<=0){
            printf("Invalid process size.\n");
            return 0;
        }
    }

    int f1=firstFit(blockSize,m,processSize,n);
    int f2=bestFit(blockSize,m,processSize,n);
    int f3=worstFit(blockSize,m,processSize,n);

    printf("\n----- Algorithm Comparison -----\n");
    printf("--------------------------------\n");
    printf("First Fit Fragmentation : %d\n",f1);
    printf("Best Fit Fragmentation  : %d\n",f2);
    printf("Worst Fit Fragmentation : %d\n",f3);

    if(f1<=f2 && f1<=f3){
        printf("\nFirst Fit performed best because it produced the minimum total fragmentation.\n");
    }
    else if(f2<=f1 && f2<=f3){
        printf("\nBest Fit performed best because it selects the smallest suitable block, reducing wasted memory.\n");
    }
    else{
        printf("\nWorst Fit performed best for this input because allocating the largest blocks reduced fragmentation here.\n");
    }

    return 0;
}