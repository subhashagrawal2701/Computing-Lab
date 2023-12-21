#include <stdio.h>
#include <string.h>
int reverse(char s[],int start, int end){
    for(int i=0;i<(end-start)/2;i++){
        char temp=s[end+i];
        s[end-i]=s[start+i];
        s[start+i]=temp;
    }
    printf("%s\n",s);
}
int main()
{
    char str[100];
    printf("Enter String\n");
    scanf("%s",str);
    int n = strlen(str);

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n-1;j++){
            reverse(str,i,j);
        }
    }

    return 0;
}

