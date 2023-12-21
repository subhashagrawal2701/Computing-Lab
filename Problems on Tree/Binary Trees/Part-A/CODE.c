#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode {
    int val;
    struct treeNode* left;
    struct treeNode* right;
    int cost;
};

struct treeNode* createNode(int val) {
    struct treeNode* node = (struct treeNode*)malloc(sizeof(struct treeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->cost = val; // Initialize cost with the node value
    return node;
}

void constructTree(struct treeNode* root, char* str) {
    struct treeNode* ptr = root;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '0') {
            if (ptr->left == NULL) {
                ptr->left = createNode(0); // Create a placeholder node for '0'
            }
            ptr = ptr->left;
        } else if (str[i] == '1') {
            if (ptr->right == NULL) {
                ptr->right = createNode(0); // Create a placeholder node for '1'
            }
            ptr = ptr->right;
        } else if (str[i] >= '0' && str[i] <= '9') {
            int num = 0;
            while (i < len && str[i] >= '0' && str[i] <= '9') {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            i--; // Move back to the last digit
            ptr->val = num;
        }
    }
}

// Function to compute the minimum cost from root to leaf
int minCostToLeaf(struct treeNode* root) {
    if (root == NULL) {
        return 0; // Return 0 for NULL nodes
    }

    // If it's a leaf node, return its value as cost
    if (root->left == NULL && root->right == NULL) {
        return root->val;
    }

    // Recursively compute the minimum cost for the left and right subtrees
    int leftCost = minCostToLeaf(root->left);
    int rightCost = minCostToLeaf(root->right);

    // Returns the minimum cost between the left and right subtrees
    return root->val + ((leftCost < rightCost) ? leftCost : rightCost);
}

void printMinCostPath(struct treeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->val);

    int leftCost = minCostToLeaf(root->left);
    int rightCost = minCostToLeaf(root->right);

    // Choose minimum cost
    if (leftCost < rightCost) {
        printMinCostPath(root->left);
    } else {
        printMinCostPath(root->right);
    }
}

int main() {
    char filename[100];
    printf("Enter Input File Name\n");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("COULDN'T OPEN FILE");
        return 1; // Exit with an error code
    }

    int n;
    fscanf(fp, "%d", &n);
    char str[100];
    fgets(str, 100, fp); // no. of nodes

    fgets(str, 100, fp); // 1st node
    int rootvalue = str[strlen(str) - 3] - '0';
    struct treeNode* root = createNode(rootvalue); // Create the root node

    struct treeNode* pointer = root;

    for (int i = 1; i < n; i++) {
        pointer = root;
        fgets(str, 100, fp); // Read the next line
        int value;
        for (int j = 0; j < strlen(str) - 1; j++) {
            if (str[j] == '0') {
                if (pointer->left == NULL) {
                    pointer->left = createNode(0); // Create a placeholder node for '0'
                }
                pointer = pointer->left;
            } else if (str[j] == '1') {
                if (pointer->right == NULL) {
                    pointer->right = createNode(0); // Create a placeholder node for '1'
                }
                pointer = pointer->right;
            } else if ((str[j] >= '0') && (str[j] <= '9')) {
                value = str[j] - '0';
            }
        }
        pointer->val = value;
    }

    fclose(fp); 

    int minCost = minCostToLeaf(root);

    printf("Minimum Cost from Root to Leaf: %d\n", minCost);
    printf("Minimum Cost Path: ");
    printMinCostPath(root);

    return 0;
}
