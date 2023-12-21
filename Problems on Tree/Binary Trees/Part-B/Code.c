#include <stdio.h>
#include <string.h>
#include <math.h>

void construct_tree(int arr[], int i){
    //printf("  Enter  value ");
    int val;
    scanf("%d",&val);
    arr[i]=val;
    if(val==-1){
        return;
    }
    printf("Enter value of left node of %d (-1 if no node) : ",val);
    construct_tree(arr, 2*i);
    printf("Enter value of right node of %d (-1 if no node) : ",val);
    construct_tree(arr, 2*i+1);

}

int main(){
    char filename[100];
    printf("Enter Input File Name\n");
    scanf("%s",filename);

    FILE *fp=fopen(filename,"r");
    if(fp==NULL){
        printf("COULDN'T OPEN FILE");
    }
    char ch;
    char array[200];
    do{
        strncat(array, &ch, 1);
    }while((ch=fgetc(fp))!='\n');
    char source=fgetc(fp);

    int tree[100];
    int treeindex=1;
    for(int i=0;i<strlen(array);i++){
        if((array[i]>='0')&&(array[i]<='9')){
            tree[treeindex]=array[i]-'0';
            treeindex++;
        }
        if(array[i]>='N'){
            tree[treeindex]=-1;
            treeindex++;
        }
    }
    int visited[treeindex];

    for(int i=1;i<treeindex;i++){
        visited[i]=-1;   //initially nothing visited
    }

    int indexofsource=1;
    while(tree[indexofsource]!=(source-'0')){
        indexofsource++;
    }
    // printf("index of source%c is %d\n",source,indexofsource);
    
    visited[indexofsource]=0;   //source have the information

    int change;
    int count=1;    //counts no of ties loop runs
    do{
        change=0;
        for(int i=1;i<treeindex;i++){
            if((visited[i]==(count-1))&&(tree[i]!=-1)){
                int c=floor(i/2);
                if(visited[c]==-1){
                    visited[i/2]=count;
                    change++;
                }
                if(visited[i*2]==-1){
                    visited[i*2]=count;
                    change++;
                }
                if(visited[(i*2)+1]==-1){
                    visited[(i*2)+1]=count;
                    change++;
                }
                visited[i]=visited[i]+1;
            }
            
        }
        // printf("%d Iteration :",(count-1));
            // for(int i=1;i<treeindex;i++){
            //     printf("%d ",visited[i]);
            // }
            // printf("\n");  
        count++;
  
    }while(change!=0);
    // count--;
    printf("Hours Needed is : %d\n",count-2);   //2 is subtracted, bcoz initial value of count is 1 and source element already have information so no timr needed for it

}