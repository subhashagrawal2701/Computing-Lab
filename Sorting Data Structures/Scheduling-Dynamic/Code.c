#include <stdio.h>
struct presentation{
    int start;
    int end;
    int pop;
    char title[100];
};


int MaxPopularScore(struct presentation arr[], int n)
{
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
 
        // To Find latest non-conflicting presentation for each presentation
    int latestNonConflict[n];
    for (int i=0;i<n;i++){
        for (int j= i-1; j>=0; j--) {
            if (arr[j].end <= arr[i].start)
            {    
                latestNonConflict[i]=j;
                break;
            }else{
                latestNonConflict[i]=-1;
            }
        }
    }


    // Create table to store maximum popularity score
    int dp[n];
    dp[0] = arr[0].pop;  //include 1st presentation
 
    //   Fill table using dynamic programming
    for (int i = 1; i < n; i++) {
        // Find profit including the current job
        int include = arr[i].pop;
        int l = latestNonConflict[i];
        if (l != -1)    //if latest non-conflicting presentation for presentation i exists:
        {    include += dp[l];
        }
        int exclude=dp[i-1];
        // Store maximum of including and excluding
        if(include>exclude){
            dp[i]=include;
        }else{
            dp[i]=exclude;
        }
    }
     int result = dp[n - 1];

    //print output
    FILE *f_op=fopen("PartC_output.txt","w");
    if(f_op==NULL){
        printf("Unable to open Input File");
    }
    fprintf(f_op,"Max Sum is : %d", result);
    printf("Max Sum is : %d", result);
    return result;
}

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: <program name> <input_file>");
    }
    char *input_file=argv[1];
    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("Unable to open Input File");
    }
    int n;
    fscanf(fp,"%d",&n);
    struct presentation arr[n];

    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d %d %s\n",&arr[i].start, &arr[i].end, &arr[i].pop, arr[i].title);
        //printf("%d %d %d %s\n",&arr[i].start, &arr[i].end, &arr[i].pop, arr[i].title);
    }
    MaxPopularScore(arr,n);
    return 0;
}