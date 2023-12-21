#include <stdio.h>
#include <stdlib.h>
struct node{
    struct node*p;
    struct node*f;
    int n;
};
int main(){
    struct node*head;
    struct node*pointer;
    head=malloc(sizeof(struct node));
    pointer=head;
    int input;
    printf("Enter the number [Enter -1 to stop]: ");
    scanf("%d",&input);
    if(input==-1){
        pointer->f=NULL;
    }else{
        head->n=input;
        pointer->p=NULL;
        while(input!=-1){
            printf("Enter the number [Enter -1 to stop]: ");
            scanf("%d",&input);
            pointer->f=malloc(sizeof(struct node));
            (pointer->f)->p=pointer;
            pointer=pointer->f;
            pointer->n=input;
        }
        if(input=-1){
            pointer->f=NULL;
        }
    }
    struct node*pointer1;
    pointer1=head;
    while((pointer1->f)!=NULL){
        printf("%d ->",pointer1->n );
        pointer1=pointer1->f;
    }printf("NULL/n");
    int nbr;
    printf("Enter the value of N (size of neighborhood) :");
    scanf("%d",&nbr);
    int array[100];
    int i=0;//array pointer
    pointer1=head;
    while((pointer1->f)!=NULL){
        struct node*pointer2;
        pointer2=pointer1;
        int count=0;//to keep count of smaller element than the current one
        //CHECK LEFT N ELEMENTS
        int k=nbr;
        while(k>0){
            pointer2=pointer2->p;
            if((pointer2->n)<(pointer1->n)){
                count++;
                break;
            }
            k--;
        }
        //CHECK RIGHT N ELEMENTS
        k=nbr;
        while(k>0){
            pointer2=pointer2->f;
            if((pointer2->n)<(pointer1->n)){
                count++;
                break;
            }
            k--;
        }
        if(count==0){
            array[i]=(pointer1->n);
            i++;
            //add element to array
        }
        int max=0;
        printf("The minimas stored in the arrays are: ");
        for(int j=0;j<i;j++){
            printf("%d ",array[j]);
            if(array[j]>max){
                max=array[j];
            }
        }
        printf("The maximum of these minimas are: %d",max);
    }

}