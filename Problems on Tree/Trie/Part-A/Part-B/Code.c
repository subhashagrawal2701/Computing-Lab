#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

struct trie{
    struct trie* al[26];
    bool eof;
};

struct trie *newnode(void){
    struct trie *np = NULL;
    np=(struct trie*)malloc(sizeof(struct trie));
    if(np){
        np->eof=false;
        for(int i=0;i<26;i++){
            np->al[i]=NULL;
        }
    }
    return np;
}

struct trie* add_to_trie(struct trie* node, const char *str){
    // for(;i<strlen(str);i++){
        struct trie *crawl=node;
        for(int i=0;i<strlen(str);i++){
            int index=(str[i]-'a');
            if(!crawl->al[index]){
                crawl->al[index]=newnode();
            }
            crawl=crawl->al[index];
        }
        crawl->eof=true;
    
}

int search(struct trie*node,const char str[]){
    struct trie *crawl = node;
    for(int i=0;i<strlen(str);i++){
        int index=(str[i]-'a');
        if(!crawl->al[index]){
            return false;
        }
        crawl=crawl->al[index];
    }
    return (crawl->eof);
}

char* stringrev(char str[],int start, int end){
    // for(int i=0;i<=(end-start+1)/2;i++){
    //     char temp=str[start+i];
    //     str[start+i]=str[end-i];
    //     str[end-i]=temp;    
    // }
    while(start<end){
        char temp=str[start];
        str[start]=str[end];
        str[end]=temp;
        start++;
        end--; 
    }
    return str;
}

int main(){
     char str[100];
     char revstr[100];
     struct trie *root=newnode();
     printf("Enter a string\n");
     scanf("%s",str);
     add_to_trie(root,str); //add Base to root i.e given string

     FILE *fp=fopen("output.txt","w");
     if(!fp){
        printf("Could Not Create Output File");
     }
     
     int count=0;
     for(int i=0;i<strlen(str)-1;i++){
        for(int j=i+1;j<strlen(str);j++){
            strcpy(revstr,str);
            char *rev=stringrev(revstr,i,j);
            if(!search(root,rev)){
                add_to_trie(root,rev);
                printf("%s\n",rev);
                fprintf(fp,"%s\n",rev);
                count++;
            }
            // printf("%s\n",rev);
        }
     }
     printf("Total Unique Substrings other than the input is %d\n",count);
     fprintf(fp,"Total Unique Substrings other than the input is %d\n",count);
}