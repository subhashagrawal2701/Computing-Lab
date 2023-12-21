#include <stdio.h>
struct presentation{
    int start;
    int end;
    int pop;
    char title[100];
};

int divide(int start, int end, int k){
    //return start time of the last slot
    int slot_start;
    int initial_end=end;
    int minutes=0;
        int sh,sm,eh,em;    //start hour, startmin, end hour, end min
        sh=start/100;
        sm=start%100;
        eh=end/100;
        em=end%100;
        minutes=(eh*60)+em-sm-(sh*60);      //total minutes between start and end time
        int slot_min=minutes/k;            
            int fh,fm;  //final hour, final min
            minutes=(eh*60)+em-slot_min;    //store the start time of last slot in minutes 
            fh=(minutes/60);
            fm=minutes%60;
            slot_start=(fh*100)+fm;     // 
        // if(initial_end%100>=slot_min){
        //     slot_start=initial_end-slot_min;
        // }else{
        //     slot_min=slot_min-(initial_end%100);
        //     initial_end=initial_end-(initial_end%100);
        //     slot_start=initial_end-100+(60-(slot_min%60)-100*(slot_min/60));
        // }
    return slot_start;
}

int choose_best(struct presentation arr[],int n,int start, int end){
    int index_of_best=-1;
    int pop_of_best=0;
    for(int i=0;i<n;i++){
        if((arr[i].start>=start)&&(arr[i].end<=end)&&(arr[i].pop>pop_of_best)){
            pop_of_best=arr[i].pop;
            index_of_best=i;
        }
    }
    return index_of_best;
}


int greedy(struct presentation arr[],int n,int k){
    //------------------------SORT BY FINISH TIME -----------------------------
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i].end>arr[j].end){
                struct presentation temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }

    int timeline_start=arr[0].start;
    int timeline_end=arr[n-1].end;
    int bestGreedySum=0;
//printf("K= %d\n",k);
    while(k>1){
//printf("LOOP STARTS AGAIN\n");
        //divide current timeline into k equal parts    
        int slot_start=divide(timeline_start, timeline_end, k);
//printf("Time Slot start - End  %d %d\n", slot_start,timeline_end);
        //select best presentation that lies completely inside this slot
        int pKBest=choose_best(arr,n,slot_start,timeline_end);
//printf("Best chosen in this slot is %s \n",arr[pKBest].title);
        if(pKBest!=-1){
            bestGreedySum = bestGreedySum +arr[pKBest].pop;
            printf("%d %d %d %s \n",arr[pKBest].start, arr[pKBest].end, arr[pKBest].pop, arr[pKBest].title);
            timeline_end=arr[pKBest].start;
        }
        k--;
    }
    //------USE Part B of Aug 7

    //-----filter eligible presentations based on time deadline
    struct presentation eligible_presentation[n];
    int count=0;
//printf("ELIGIBLE PRESENTATIONS\n");
    for(int i=0;i<n;i++){
        if(arr[i].end<=timeline_end){   //only eligible presentation gets inside this loop whose end is before deadline
            eligible_presentation[count]=arr[i];
            
//printf("%d %d %d %s \n",arr[i].start, arr[i].end, arr[i].pop, arr[i].title);
//printf("%d %d %d %s \n",eligible_presentation[count].start, eligible_presentation[count].end, eligible_presentation[count].pop, eligible_presentation[count].title);                
            count++;
        }
    }
    //------------------------SORT BY POPULARITY IN DESCENDING ORDER -----------------------------
    int chosen[count];
    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            if(eligible_presentation[i].pop<eligible_presentation[j].pop){
                struct presentation temp=eligible_presentation[i];
                eligible_presentation[i]=eligible_presentation[j];
                eligible_presentation[j]=temp;
            }
        }
        chosen[i]=0;
    }
    chosen[0]=1;
    bestGreedySum = bestGreedySum +eligible_presentation[0].pop;
    printf("%d %d %d %s \n",eligible_presentation[0].start, eligible_presentation[0].end, eligible_presentation[0].pop, eligible_presentation[0].title);                
    for(int i=1;i<count;i++){
        for(int j=0;j<i;j++){
            if(chosen[j]==1){
                if(((eligible_presentation[i].end<=eligible_presentation[j].start)||(eligible_presentation[i].start>=eligible_presentation[j].end))){
                    //choose
                    chosen[i]=1;
                    //continue;
                }else{
                    chosen[i]=0;
                    break;
                }
                // chosen[i]=1;
            }
        }
        if(chosen[i]==1){
            bestGreedySum = bestGreedySum +eligible_presentation[i].pop;
            printf("%d %d %d %s \n",eligible_presentation[i].start, eligible_presentation[i].end, eligible_presentation[i].pop, eligible_presentation[i].title);                
        }
    }

    printf("Maximum Total Popularity: %d",bestGreedySum);
    
}

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: <program name> <algorithm (a/b)> <input_file>");
    }
    char *input_file=argv[1];

    FILE *fp=fopen(argv[1],"r");

    if(fp==NULL){
        printf("Unable to open Input File");
    }

    int n,k;
    fscanf(fp,"%d %d",&n,&k);
    struct presentation can[n];

    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d %d %s",&can[i].start, &can[i].end, &can[i].pop, can[i].title);

    }

    greedy(can,n,k);
    return 0;

}