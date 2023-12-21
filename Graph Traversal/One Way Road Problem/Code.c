#include <stdio.h>

typedef struct point {
    int x;
    int y;
} point;

int distancesq(int x1, int y1, int x2, int y2) {
    int dist = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
    return dist;
}

int dfs(int m, int n, int mat[][n], point start, point end, int visited[][n]) {
    point stack[m * n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = 0;
        }
    }

    int pointer = 0;
    stack[pointer] = start;
    visited[start.x][start.y] = 1;
    pointer++;
    
    while (pointer != 0) {
        point a = stack[pointer - 1];
        if (a.x == end.x /*&& a.y == end.y*/) {
            return 1;
        }
        pointer--;

        // Check right
        if (a.y + 1 < n && visited[a.x][a.y + 1] != 1 && mat[a.x][a.y + 1] == 0) {
            visited[a.x][a.y + 1] = 1;
            stack[pointer].x = a.x;
            stack[pointer].y = a.y + 1;
            pointer++;
        }

        // Check down
        if (a.x + 1 < m && visited[a.x + 1][a.y] != 1 && mat[a.x + 1][a.y] == 0) {
            visited[a.x + 1][a.y] = 1;
            stack[pointer].x = a.x + 1;
            stack[pointer].y = a.y;
            pointer++;
        }
    }

    return 0;
}

int main() {
    int m, n, k;
    printf("Enter m, n, k followed by k lines in the form <x, y, r>\n");
    scanf("%d %d %d", &m, &n, &k);
    int guard[k][3];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &guard[i][j]);
        }
    }

    int mat[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = 0;
        }
    }

    for (int i = 0; i < k; i++) {
        int x = guard[i][0];
        int y = guard[i][1];
        int r = guard[i][2];
        for (int p = 0; p < m; p++) {
            for (int q = 0; q < n; q++) {
                if (distancesq(p, q, x, y) <= r * r) {
                    mat[p][q] = 1;
                }
            }
        }
    }


    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            point start = {0, i};
            point end = {n - 1,j};
            int visited[m][n];
            if (dfs(m, n, mat, start, end, visited) == 1) {
                printf("possible");
                return 0;
            }
        }
    }
    

    printf("Not possible");
    return 0;
}
