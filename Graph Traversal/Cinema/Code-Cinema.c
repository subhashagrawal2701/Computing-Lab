#include <stdio.h>
#include <stdlib.h>

void dfs(int start, int v, int mat[][v], int visited[]) {
    int stack[v];
    int pointer = 0;
    stack[pointer] = start;
    visited[start] = 1;
    pointer++;

    while (pointer != 0) {
        int a = stack[pointer - 1];
        pointer--;

        for (int i = 0; i < v; i++) {
            if (mat[a][i] == 1 && visited[i] != 1) {
                visited[i] = 1;
                stack[pointer] = i;
                pointer++;
            }
        }
    }
}


int main(){
    int n,m;
    printf("Enter n & m followed by occupancy matrix\n");
    scanf("%d %d",&n,&m);
    int hall[n][m];
    int occupancy=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&hall[i][j]);
            if(hall[i][j]==1){
                hall[i][j]=occupancy;
                occupancy++;
            }
        }
    }
    occupancy--;

    // printf("------To print the seating position fo every node present in the cinema hall-------------------);
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         printf("%d ", hall[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("%d - present \n", occupancy);

    // printf("---------Initialize Graph with 0 --------------------------\n\n");
    int graph[occupancy][occupancy];
    for(int i=0;i<occupancy;i++){
        for(int j=0;j<occupancy;j++){
            graph[i][j]=0;
        }
    }

    //--------Converting given data into graph----------------------
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(hall[i][j]!=0){
                int k=hall[i][j]-1;
                
                 // graph[k][k]=1;
                
                if((hall[i][j+1]!=0)&&(j+1<m)){    //right
                    int l=hall[i][j+1]-1;
                    graph[k][l]=1;
                }
                if((hall[i][j-1]!=0)&&(j>0)){    //left
                    int l=hall[i][j-1]-1;
                    graph[k][l]=1;
                }
                if((hall[i-1][j]!=0)&&(i>0)){    //up
                    int l=hall[i-1][j]-1;
                    graph[k][l]=1;
                }
                if((hall[i+1][j]!=0)&&(i+1<n)){    //down
                    // int k=hall[i][j]-1;
                    int l=hall[i+1][j]-1;
                    graph[k][l]=1;
                }
                if((hall[i+1][j+1]!=0)&&(i+1<n)&&(j+1<m)){    //diagonal south east
                    int l=hall[i+1][j+1]-1;
                    graph[k][l]=1;
                }
                if((hall[i+1][j-1]!=0)&&(i+1<n)&&(j>0)){    //diagonal south west
                    int l=hall[i+1][j-1]-1;
                    graph[k][l]=1;
                }
                if((hall[i-1][j+1]!=0)&&(i>0)&&(j+1<m)){    //diagonal north east
                    int l=hall[i-1][j+1]-1;
                    graph[k][l]=1;
                }
                if((hall[i-1][j-1]!=0)&&(i>0)&&(j>1)){    //diagonal north west
                    int l=hall[i-1][j-1]-1;
                    graph[k][l]=1;
                }
                 // printf("%d ", hall[i][j]);
            }
            
        }
    }

    //----------------To print the adjency matrix of graph representation of the given data-----------------------
    // for(int i=0;i<occupancy;i++){
    //     for(int j=0;j<occupancy;j++){
    //         printf("%d ",graph[i][j]);            
    //     }
    //     printf("\n");
    // }
    
    
    int visited[occupancy];
    for (int i = 0; i < occupancy; i++) {
        visited[i] = 0;
    }

    int count = 0;

    for (int i = 0; i < occupancy; i++) {
        if (visited[i] == 0) {
            count++;
            dfs(i, occupancy, graph, visited);
        }
    }

    printf("Number of Groups in the hall are = %d\n", count);
    
}