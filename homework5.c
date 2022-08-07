#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TREENODE
{
    char *value;
    struct TREENODE *parent; // address of parent node
    struct TREENODE *left;   // addreess of left child node
    struct TREENODE *right;  // address of right child node
};

typedef struct TREENODE NODE;

NODE *addNode2Tree(NODE *r, char *x)
{
    // r: root pointer of the tree
    // x: value to add into this tree
    // return the root of the updated tree
    NODE *p;
    p = malloc(sizeof(NODE));
    p->value = x; // same thing as (*p).value = x
    p->parent = NULL;
    p->left = NULL;
    p->right = NULL;

    if (r == NULL)
    {
        //tree is empty
        // tree will consist of node p only
        return p;
    }
    // else: tree is not empty
    if (strcmp(x, r->value) > 0)
    {
        p->left = r;   // r is left child of node p
        r->parent = p; // p is parent of r
        return p;
    }
    if (r->left == NULL)
    {
        // left subtree does not exist
        // make p new left child of root r
        r->left = p;
        return r;
    }
    if (r->right == NULL)
    {
        r->right = p;
        return r;
    }
    // left subtree exists
    // right subtree exists
    if (strcmp(x, r->left->value) <= 0)
    {
        // add x to the left subtree
        NODE *new_subtree = addNode2Tree(r->left, x);
        new_subtree->parent = r;
        r->left = new_subtree;
        return r;
    }
    if (strcmp(x, r->right->value) <= 0)
    {
        NODE *new_subtree = addNode2Tree(r->right, x);
        new_subtree->parent = r;
        r->right = new_subtree;
        return r;
    }
    // x is smaller than both left and right
    p->left = r->right;
    r->right->parent = p;
    r->right = p;
    p->parent = r;
    return r;
}

NODE *addTree2Tree(NODE *t1, NODE *t2)
{
    // merging two trees, t1 and t2
    // return the combination tree
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
        return t1;

    addValue2Tree(&t1, t2->value);    // add root value of three to t2 to tree t1
    t1 = addTree2Tree(t1, t2->left);  // add left subtree of t2 and tree t1
    t1 = addTree2Tree(t1, t2->right); // add right subtree of t2 and tree t1
    return t1;
}

void addValue2Tree(NODE **address_of_root, char *x)
{
    // add value x to the tree located at address address_of_root
    if (address_of_root == NULL)
        return;
    NODE *root = *address_of_root;

    NODE *new_p = malloc(sizeof(NODE));
    new_p->value = x;
    new_p->left = NULL;
    new_p->right = NULL;
    new_p->parent = NULL;

    if (root == NULL)
    {
        // tree is empty
        // update
        *address_of_root = new_p;
        return;
    }

    //int i = (strcmp(x, root->value));
    //printf("Adding %d node to the right!\n", i);

    if (strcmp(x, root->value) >= 0)
    {
        // add new node to the right subtree
        addValue2Tree(&(root->right), x);
        root->right->parent = root; // make sure that the parent information is not lost
    }
    else
    {
        // add new node the left subtree
        addValue2Tree(&(root->left), x);
        root->left->parent = root;
    }
}

unsigned char isRightMostNode(NODE *node)
{
    // return 1 if node is right most node
    // return 0 otherwise
    // alg: keep going up following the right-child link
    // if we reach the root, then node is right most node
    // if we cannot reach root, it is not the right most node
    if (node == NULL)
        return 0;
    if (node->right != NULL)
        return 0;
    while (1)
    {
        NODE *parent = node->parent;
        if (parent == NULL)
        {
            // have reached the root
            return 1;
        }
        if (parent->right == node)
            node = node->parent;
        else
            return 0; // i am left child of my parent, meaning I cannot be right most
    }
}

void printTreeIncreasingOrder(NODE *root)
{
    if (root == NULL)
        return;

    // print all the values on the left subtree
    printTreeIncreasingOrder(root->left);

    // THIS VERSION WILL NOT HAVE A COMMA ON THE LAST VALUE
    if (isRightMostNode(root))
    {
        if (root->value != NULL)
            printf("%s\n", root->value);
    }
    else
    {
        if (root->value != NULL)
            printf("%s ", root->value);
    }
    // print the root
    //printf("%d,", root->value);

    // print all the values on the right subtree
    printTreeIncreasingOrder(root->right);
}

NODE *findNode(NODE *r, char *x)
{
    // return any node that stores value x in tree
    // r: root pointer of the tree
    if (r == NULL)
        return NULL;
    if (strcmp(x, r->value) == 0)
        return r;
    NODE *p = malloc(sizeof(NODE));
    p = findNode(r->left, x);
    if (p == NULL)
    {
        p = findNode(r->right, x);
        if (p == NULL)
            return NULL;
    }
    return p;
}

NODE *removeNode(NODE *r, char *x)
{
    // remove any node that store value x from tree
    // r: root pointer of this tree
    // return root pointer of the updated tree after removal

    NODE *p = malloc(sizeof(NODE));
    p = findNode(r, x);
    if (p == NULL)
        return r;
    NODE *C = p->parent;
    NODE *A = p->left;
    NODE *B = p->right;
    if (C == NULL)
    {
        // p is root of the tree
        free(p);
        return addTree2Tree(A, B); // add tree A and tree B and return the new combination tree
    }
    if (A != NULL)
    {
        // make A a child of C assuming position of P
        if (p == C->left)
            C->left = A;
        else
            C->right = A;
        A->parent = C;
        free(p);
        return addTree2Tree(r, B);
    }
    if (B != NULL)
    {
        if (p == C->left)
            C->left = B;
        else
            C->right = B;
        B->parent = C;
        free(p);
        return r;
    }
    if (p == C->left)
        C->left = NULL;
    else
        C->right = NULL;
    free(p); // free allocation for p
    return r;
}

NODE *removeAllNodes(NODE *r, char *x)
{
    //SOMETHING IS WRONG PLEASE FIGURE OUT
    while (findNode(r, x) != NULL)
    {
        /*printf("---\n");
        printf("Removing %s", r->value);
        printf("---\n");
        */
        removeNode(r, x);
    }
    return r;
}

char *strlwr(char *s)
{
    char *t = s;

    if (!s)
    {
        return 0;
    }

    int i = 0;
    while (*t != '\0')
    {
        if (*t >= 'A' && *t <= 'Z')
        {
            *t = *t + ('a' - 'A');
        }
        t++;
    }

    return s;
}

int main()
{
    NODE *root = NULL;
    char *line_1;
    char *line_2[100];
    char *token;
    int len = 0;

    //scanf("%[^EOF]s", line_1);

    while(scanf("%s", line_1)!=EOF){
        printf("%s\n", line_1);
        addValue2Tree(&root, line_1);
    }

    printTreeIncreasingOrder(root);

    // token = strtok(line_1, " ");
    // while (token != NULL)
    // {
    //     //printf("%s\n", token);
    //     len = strlen(token);
    //     printf("------%s*****", token);
    //     if(token[0]=='\n') printf("**** There is a newline ***");

    //     //token = strlwr(token);
    //     addValue2Tree(&root, token);
    //     token = strtok(NULL, " ");
    // }
    //printTreeIncreasingOrder(root);
    //printf("\n\n");
    /*
    getchar();
    scanf("%[^\n]s", line_2);
    token = strtok(line_2, " ");
    //printf("%s\n", token);
    //removeNode(root, token);
    /*

    while (token != NULL)
    {
        //printf("%s\n", token);
        //token = strlwr(token);
        removeAllNodes(root, token);
        token = strtok(NULL, " ");
    }
    */

    //printTreeIncreasingOrder(root);

    return 0;
}