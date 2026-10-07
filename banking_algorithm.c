#include <stdio.h>

int n,m;

void calNeed(int max[][m],int allocation[][m],int need[][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
}

void findsafeseq(int allocation[][m],int need[][m],int ava[],int finish[],int safe[],int count){

    if(count==n){
        for(int i=0;i<n;i++){
            printf("P%d ", safe[i]);
            if(i<n-1){
                printf("->");
            }
        }
            printf("\n");
            return;
    }

     for(int i=0;i<n;i++){
        if(!finish[i]){
            int pos=1;

            for(int j=0;j<m;j++){
                if(need[i][j]>ava[j]){
                    pos=0;
                    break;
                }
            }

            if(pos){
                finish[i]=1;
                safe[count]=i;

                for(int j=0;j<m;j++){
                    ava[j]+=allocation[i][j];
                }
                    findsafeseq(allocation,need,ava,finish,safe,count+1);

                    for(int j=0;j<m;j++){
                        ava[j]-=allocation[i][j];
                    }
                        finish[i]=0;
            }
        }
    } 
}

int main(){
    printf("enter no. of processes: ");
    scanf("%d",&n);

    printf("enter no. of resources: ");
    scanf("%d",&m);

    int total[m],ava[m];
    int finish[n],safe[n];
    int allocation[n][m],max[n][m],need[n][m];

    printf("enter total instances of the resources:\n");
    for(int j=0;j<m;j++){
        printf("%c: ",'a'+j);
        scanf("%d",&total[j]);
    }

    printf("enter allocation table:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
        scanf("%d",&allocation[i][j]);
       }
    }

    printf("enter maximum table:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }

    for(int j=0;j<m;j++){
        int allocated=0;
        
        for(int i=0;i<n;i++){
            allocated=allocated+allocation[i][j];
            ava[j]=total[j]-allocated;
        }
    }

    calNeed(max,allocation,need);

    for(int i=0;i<n;i++){
        finish[i]=0;
    }

    printf("need table:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    printf("\nall safe sequences are:\n");
    findsafeseq(allocation,need,ava,finish,safe,0);
    
    return 0;
}