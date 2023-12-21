#include<stdio.h>
#include <limits.h>
#include <stdbool.h>


void MinCostPaths(int n, int mat[][n]) {
    int cost[n];
    int count[n];
    int visited[n];
    for (int i = 0; i < n; i++) {
        cost[i] = INT_MAX;
        count[i] = 0;
        visited[i]=0;
    }

    cost[0] = 0;
    count[0] = 1;


    // Find minimum cost and count of paths
    for (int i = 0; i < n - 1; i++) {
        int mincost = INT_MAX;
        int minIndex = -1;

        // Find the unvisited minimum distance node
        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[j] < mincost) {
                mincost = cost[j];
                minIndex = j;
            }
        }

        visited[minIndex] = 1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && mat[minIndex][j] && cost[minIndex] != INT_MAX && cost[minIndex] + mat[minIndex][j] < cost[j]) {
                cost[j] = cost[minIndex] + mat[minIndex][j];
                count[j] = count[minIndex];
            } else if (!visited[j] && mat[minIndex][j] && cost[minIndex] != INT_MAX && cost[minIndex] + mat[minIndex][j] == cost[j]) {
                count[j] += count[minIndex];
            }
        }
    }

    printf("Number of Paths: %d\n", count[n - 1]);
    printf("Minimum Cost : %d\n", cost[n - 1]);
}


int main(){
    int n;
    printf("Enter n followed by occupancy matrix\n");
    scanf("%d",&n);
    int mat[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }
    MinCostPaths(n,mat);
}