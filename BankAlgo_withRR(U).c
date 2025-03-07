#include <stdio.h>

void calculateNeed(int n, int m, int max[n][m], int alloc[n][m], int need[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int isSafe(int n, int m, int alloc[n][m], int max[n][m], int avail[m]) {
    int f[n], ans[n], ind = 0;
    int need[n][m];

    calculateNeed(n, m, max, alloc, need);

    for (int i = 0; i < n; i++) {
        f[i] = 0;  
    }

    int y = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            printf("The system is not in a safe state (deadlock detected).\n");
            return 0;  
        }
    }

    printf("Following is the SAFE Sequence: \n");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", ans[i]);
    }
    printf("P%d\n", ans[n - 1]);

    return 1;
}

int resourceRequest(int n, int m, int alloc[n][m], int max[n][m], int avail[m], int pid, int request[m]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > max[pid][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            printf("Error: Not enough resources available.\n");
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[pid][i] += request[i];
    }

    if (isSafe(n, m, alloc, max, avail)) {
        printf("Resource request granted.\n");
        return 1;
    } else {
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[pid][i] -= request[i];
        }
        printf("Error: Request cannot be granted as it leads to an unsafe state.\n");
        return 0;
    }
}

int main() {
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    if (m == 0) {
        printf("No resources available. Exiting...\n");
        return 0;
    }

    int alloc[n][m];
    int max[n][m];
    int avail[m];

    printf("\nEnter the available resources: ");
    for (int i = 0; i < m; i++) {
        printf("\nResource %d: ", i + 1);
        scanf("%d", &avail[i]);
    }

    printf("\nEnter the Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d: ", i + 1);
        for (int j = 0; j < m; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter the Max matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d: ", i + 1);
        for (int j = 0; j < m; j++) {
            printf("\nResource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    isSafe(n, m, alloc, max, avail);

    int pid;
    printf("\nEnter the process number (P1, P2, P3, ...) for the resource request: ");
    scanf("%d", &pid);
    // pid--;

    int request[m];
    printf("\nEnter the resource request for Process P%d:\n", pid + 1);
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    resourceRequest(n, m, alloc, max, avail, pid, request);

    return 0;
}
