#include <stdio.h>
struct presentation{
    int start;
    int end;
    int pop;
    char title[100];
};
void greedy_start(struct presentation arr[],int n){
    //------------------------SORT-----------------------------
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i].start>arr[j].start){
                struct presentation temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    //------------Print--------------------------

    FILE *fo = fopen("PartA_output.txt","w");
    if(fo==NULL){
        printf("Could Not open txt File for Output");
    }

    int pointer=0;          //to store last selected presentation
    printf("%d %d %d %s \n",arr[0].start, arr[0].end, arr[0].pop, arr[0].title); //to print 1st presentation
    fprintf(fo,"%d %d %d %s \n",arr[0].start, arr[0].end, arr[0].pop, arr[0].title);
    for(int i=0;i<n;i++){
        if(arr[pointer].end<=arr[i].start){
            pointer=i;
            printf("%d %d %d %s \n",arr[i].start, arr[i].end, arr[i].pop, arr[i].title);
            fprintf(fo,"%d %d %d %s \n",arr[i].start, arr[i].end, arr[i].pop, arr[i].title);
        }
    }
    fclose(fo);
}

void greedy_popularity(struct presentation arr[],int n){
    int chosen[n];  //track if the presentation is chosen
    //------------------------SORT-----------------------------
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i].pop<arr[j].pop){
                struct presentation temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }     
        chosen[i]=0;    //initialize all with 0 as nothing is chosen
    }
    //------------Print--------------------------
    FILE *fo = fopen("PartB_output.txt","w");
    if(fo==NULL){
        printf("Could Not open txt File for Output");
    }

    chosen[0]=1;//1st one in sorted list is chosen
    printf("%d %d %d %s \n",arr[0].start, arr[0].end, arr[0].pop, arr[0].title); //to print 1st presentation
    fprintf(fo,"%d %d %d %s \n",arr[0].start, arr[0].end, arr[0].pop, arr[0].title);

    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){         
            if((arr[i].end<arr[j].start)&&(chosen[j]==1)&&(arr[i].start<arr[j].start)){
                //If both Start & end of a presentation is before the chosen prsentation
                chosen[i]=1;
            }
            else if((arr[i].end>arr[j].end)&&(chosen[j]==1)&&(arr[i].start>arr[j].end)){
                //If both Start & end of a presentation is after the chosen prsentation

                chosen[i]=1;
            }else{
                //If both Start & end of a presentation conside with chosen prsentation time           
                chosen[i]=0;
                break;
            }

            if(chosen[i]==1){
                //Print if current element is to be chosen
                printf("%d %d %d %s \n",arr[i].start, arr[i].end, arr[i].pop, arr[i].title);
                fprintf(fo,"%d %d %d %s \n",arr[i].start, arr[i].end, arr[i].pop, arr[i].title);
            }
            
        }
    }
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("Usage: <program name> <algorithm (a/b)> <input_file>");
    }
    char algorithm=argv[1][0];
    char *input_file=argv[2];

    printf("Algorithm %c\n",algorithm);
    printf("Input File %s\n",input_file);

    FILE *fp=fopen(argv[2],"r");

    if(fp==NULL){
        printf("Unable to open Input File");
    }

    int n;
    fscanf(fp,"%d",&n);
    //printf("%d", n);
    struct presentation can[n];

    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d %d %s",&can[i].start, &can[i].end, &can[i].pop, can[i].title);
        //printf("%d %d %d %s \n",can[i].start, can[i].end, can[i].pop, can[i].title);
    }

    switch(algorithm){
        case 'a':
                //greedy_start(struct presentation *arr,int n)
            greedy_start(can,n);
            break;
        case 'b':
            greedy_popularity(can,n);
            //greedy_popularity(struct presentation *arr,int n)
            break;
        default:
            printf("Error: Invalid algorithm option.");
    }

    return 0;

}