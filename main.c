#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<pthread.h>
#include<dos.h>
#include<windows.h>
#include<mmsystem.h>

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
typedef struct
{
    int data4;
    struct Node4 *right, *left;
}Node4;

typedef struct
{
    int front, rear, size;
    unsigned capacity;
    Node4* arr[100];
}Queue;

Queue* createQ()
{
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->capacity = 100;
    q->front = q->size = 0;
    q->rear = q->capacity - 1;
    return q;
}

int isEmpty(Queue* q)
{
    return (q->size == 0);
}
int isFull(Queue* q)
{
    return (q->size == q->capacity);
}
void enqueue(Queue* q, Node4* item)
{
    if (isFull(q))
        return;
    q->rear = (q->rear + 1)%q->capacity;
    q->arr[q->rear] = item;
    q->size = q->size + 1;
}
Node4* dequeue(Queue* q)
{
    if (isEmpty(q))
        return NULL;
    Node4* item = q->arr[q->front];
    q->front = (q->front + 1)%q->capacity;
    q->size = q->size - 1;
    return item;
}

Node4* create(Node4* root4, int data4)
{
    if(root4==NULL)
    {
        root4 = (Node4*)malloc(sizeof(Node4));
        root4->data4 = data4;
        root4->left = root4->right = NULL;
        return root4;
    }
    else
    {
        if(data4>root4->data4)
        {
            root4->right = create(root4->right,data4);
        }
        else
        {
            root4->left = create(root4->left,data4);
        }
        return root4;
    }
}
void levelorder(Node4* root4)
{
    if(root4==NULL) return;
    else
    {
        Queue* q = createQ();
        enqueue(q,root4);
        while(!isEmpty(q))
        {
            Node4* temp = dequeue(q);
            printf("%d ",temp->data4);
            if(temp->right)
                enqueue(q,temp->right);
            if(temp->left)
                enqueue(q,temp->left);
        }
    }
}
typedef struct tree3 tree3;
struct tree3
{
    tree3 * left3, * right3;
    int element;
};

tree3 *make_empty(tree3 *t)
{
    if (t != NULL)
    {
        make_empty(t->left3);
        make_empty(t->right3);
        free(t);
    }
    return NULL;
}
tree3 *find_min(tree3 *t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else if (t->left3 == NULL)
    {
        return t;
    }
    else
    {
        return find_min(t->left3);
    }
}

tree3 *find_max3(tree3 *t)
{
    if (t == NULL)
    {
        return NULL;
    }
    else if (t->right3 == NULL)
    {
        return t;
    }
    else
    {
        return find_max3(t->right3);
    }
}

tree3 *find(int elem, tree3 *t)
{
    if (t == NULL)
    {
        return NULL;
    }

    if (elem < t->element)
    {
        return find(elem, t->left3);
    }
    else if (elem > t->element)
    {
        return find(elem, t->right3);
    }
    else
    {
        return t;
    }
}

//insert3 i into the tree3 t, duplicate will be discarded
//Return a pointer to the resulting tree3.
tree3 * insert3(int value, tree3 * t)
{
    tree3 * new_node3;

    if (t == NULL)
    {
        new_node3 = (tree3 *) malloc (sizeof (tree3));
        if (new_node3 == NULL)
        {
            return t;
        }
        new_node3->element = value;
        new_node3->left3 = new_node3->right3 = NULL;
        return new_node3;
    }

    if (value < t->element)
    {
        t->left3 = insert3(value, t->left3);
    }
    else if (value > t->element)
    {
        t->right3 = insert3(value, t->right3);
    }
    else
    {
        //duplicate, ignore it
        return t;
    }
    return t;
}

tree3 * delete(int value, tree3 * t)
{
    //Deletes node3 from the tree3
    // Return a pointer to the resulting tree3
    tree3 * x;
    tree3 *tmp_cell;

    if (t==NULL) return NULL;

    if (value < t->element)
    {
        t->left3 = delete(value, t->left3);
    }
    else if (value > t->element)
    {
        t->right3 = delete(value, t->right3);
    }
    else if (t->left3 && t->right3)
    {
        tmp_cell = find_min(t->right3);
        t->element = tmp_cell->element;
        t->right3 = delete(t->element, t->right3);
    }
    else
    {
        tmp_cell = t;
        if (t->left3 == NULL)
            t = t->right3;
        else if (t->right3 == NULL)
            t = t->left3;
        free(tmp_cell);
    }

    return t;
}


//printing tree3 in ascii

typedef struct asciinode3_struct asciinode3;

struct asciinode3_struct
{
    asciinode3 * left3, * right3;

    //length of the edge from this node3 to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left3, 0=I am root3, 1=right3
    int parent_dir;

    //max3 supported unit32 in dec, 10 digits max3
    char label[11];
};


#define max3_HEIGHT 1000
int lprofile[max3_HEIGHT];
int rprofile[max3_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between left3 and right3 node3s
int gap = 3;

//used for printing next node3 in the same level,
//this is the x coordinate of the next char printed
int print_next;

int MIN (int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int max3 (int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

asciinode3 * build_ascii_tree3_recursive(tree3 * t)
{
    asciinode3 * node3;

    if (t == NULL) return NULL;

    node3 = malloc(sizeof(asciinode3));
    node3->left3 = build_ascii_tree3_recursive(t->left3);
    node3->right3 = build_ascii_tree3_recursive(t->right3);

    if (node3->left3 != NULL)
    {
        node3->left3->parent_dir = -1;
    }

    if (node3->right3 != NULL)
    {
        node3->right3->parent_dir = 1;
    }

    sprintf(node3->label, "%d", t->element);
    node3->lablen = strlen(node3->label);

    return node3;
}


//Copy the tree3 into the ascii node3 structre
asciinode3 * build_ascii_tree3(tree3 * t)
{
    asciinode3 *node3;
    if (t == NULL) return NULL;
    node3 = build_ascii_tree3_recursive(t);
    node3->parent_dir = 0;
    return node3;
}

//Free all the node3s of the given tree3
void free_ascii_tree3(asciinode3 *node3)
{
    if (node3 == NULL) return;
    free_ascii_tree3(node3->left3);
    free_ascii_tree3(node3->right3);
    free(node3);
}

//The following function fills in the lprofile array for the given tree3.
//It assumes that the center of the label of the root3 of this tree3
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree3.
void compute_lprofile(asciinode3 *node3, int x, int y)
{
    int i, isleft3;
    if (node3 == NULL) return;
    isleft3 = (node3->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x-((node3->lablen-isleft3)/2));
    if (node3->left3 != NULL)
    {
        for (i=1; i <= node3->edge_length && y+i < max3_HEIGHT; i++)
        {
            lprofile[y+i] = MIN(lprofile[y+i], x-i);
        }
    }
    compute_lprofile(node3->left3, x-node3->edge_length-1, y+node3->edge_length+1);
    compute_lprofile(node3->right3, x+node3->edge_length+1, y+node3->edge_length+1);
}

void compute_rprofile(asciinode3 *node3, int x, int y)
{
    int i, notleft3;
    if (node3 == NULL) return;
    notleft3 = (node3->parent_dir != -1);
    rprofile[y] = max3(rprofile[y], x+((node3->lablen-notleft3)/2));
    if (node3->right3 != NULL)
    {
        for (i=1; i <= node3->edge_length && y+i < max3_HEIGHT; i++)
        {
            rprofile[y+i] = max3(rprofile[y+i], x+i);
        }
    }
    compute_rprofile(node3->left3, x-node3->edge_length-1, y+node3->edge_length+1);
    compute_rprofile(node3->right3, x+node3->edge_length+1, y+node3->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified tree3
void compute_edge_lengths(asciinode3 *node3)
{
    int h, hmin, i, delta;
    if (node3 == NULL) return;
    compute_edge_lengths(node3->left3);
    compute_edge_lengths(node3->right3);

    /* first fill in the edge_length of node3 */
    if (node3->right3 == NULL && node3->left3 == NULL)
    {
        node3->edge_length = 0;
    }
    else
    {
        if (node3->left3 != NULL)
        {
            for (i=0; i<node3->left3->height && i < max3_HEIGHT; i++)
            {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node3->left3, 0, 0);
            hmin = node3->left3->height;
        }
        else
        {
            hmin = 0;
        }
        if (node3->right3 != NULL)
        {
            for (i=0; i<node3->right3->height && i < max3_HEIGHT; i++)
            {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node3->right3, 0, 0);
            hmin = MIN(node3->right3->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i=0; i<hmin; i++)
        {
            delta = max3(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node3 has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node3->left3 != NULL && node3->left3->height == 1) ||
                (node3->right3 != NULL && node3->right3->height == 1))&&delta>4)
        {
            delta--;
        }

        node3->edge_length = ((delta+1)/2) - 1;
    }

    //now fill in the height of node3
    h = 1;
    if (node3->left3 != NULL)
    {
        h = max3(node3->left3->height + node3->edge_length + 1, h);
    }
    if (node3->right3 != NULL)
    {
        h = max3(node3->right3->height + node3->edge_length + 1, h);
    }
    node3->height = h;
}

//This function prints the given level of the given tree3, assuming
//that the node3 has the given x cordinate.
void print_level(asciinode3 *node3, int x, int level)
{
    int i, isleft3;
    if (node3 == NULL) return;
    isleft3 = (node3->parent_dir == -1);
    if (level == 0)
    {
        for (i=0; i<(x-print_next-((node3->lablen-isleft3)/2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        printf("%s", node3->label);
        print_next += node3->lablen;
    }
    else if (node3->edge_length >= level)
    {
        if (node3->left3 != NULL)
        {
            for (i=0; i<(x-print_next-(level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node3->right3 != NULL)
        {
            for (i=0; i<(x-print_next+(level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node3->left3,
                    x-node3->edge_length-1,
                    level-node3->edge_length-1);
        print_level(node3->right3,
                    x+node3->edge_length+1,
                    level-node3->edge_length-1);
    }
}

//prints ascii tree3 for given tree3 structure
void print_ascii_tree3(tree3 * t)
{
    asciinode3 *proot3;
    int xmin, i;
    if (t == NULL) return;
    proot3 = build_ascii_tree3(t);
    compute_edge_lengths(proot3);
    for (i=0; i<proot3->height && i < max3_HEIGHT; i++)
    {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot3, 0, 0);
    xmin = 0;
    for (i = 0; i < proot3->height && i < max3_HEIGHT; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot3->height; i++)
    {
        print_next = 0;
        print_level(proot3, -xmin, i);
        printf("\n");
    }
    if (proot3->height >= max3_HEIGHT)
    {
        printf("(This tree3 is taller than %d, and may be drawn incorrectly.)\n", max3_HEIGHT);
    }
    free_ascii_tree3(proot3);
}
//
struct node1
{
    int key1;
    struct node1 *left1, *right1;
};

// A utility function to create a new BST node1
struct node1 *newnode1(int item)
{
    struct node1 *temp1 =  (struct node1 *)malloc(sizeof(struct node1));
    temp1->key1 = item;
    temp1->left1 = temp1->right1 = NULL;
    return temp1;
}

// A utility function to do inorder traversal of BST
void inorder(struct node1 *root1)
{
    if (root1 != NULL)
    {
        inorder(root1->left1);
        printf("%d ", root1->key1);
        inorder(root1->right1);
    }
}

/* A utility function to insert1 a new node1 with given key1 in BST */
struct node1* insert1(struct node1* node1, int key1)
{
    /* If the tree is empty, return a new node1 */
    if (node1 == NULL) return newnode1(key1);

    /* Otherwise, recur down the tree */
    if (key1 < node1->key1)
        node1->left1  = insert1(node1->left1, key1);
    else
        node1->right1 = insert1(node1->right1, key1);

    /* return the (unchanged) node1 pointer */
    return node1;
}
/* Given a non-empty binary search tree, return the node1 with minimum
   key1 value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node1 * minValuenode1(struct node1* node1)
{
    struct node1* current = node1;

    /* loop down to find the left1most leaf */
    while (current->left1 != NULL)
        current = current->left1;

    return current;
}
/* Given a binary search tree and a key1, this function deletes the key1
   and returns the new root1 */
struct node1* deletenode1(struct node1* root1, int key1)
{
    // base case
    if (root1 == NULL) return root1;
    // If the key1 to be deleted is smaller than the root1's key1,
    // then it lies in left1 subtree
    if (key1 < root1->key1)
        root1->left1 = deletenode1(root1->left1, key1);
    // If the key1 to be deleted is greater than the root1's key1,
    // then it lies in right1 subtree
    else if (key1 > root1->key1)
        root1->right1 = deletenode1(root1->right1, key1);
    // if key1 is same as root1's key1, then This is the node1
    // to be deleted
    else
    {
        // node1 with only one child or no child
        if (root1->left1 == NULL)
        {
            struct node1 *temp1 = root1->right1;
            free(root1);
            return temp1;
        }
        else if (root1->right1 == NULL)
        {
            struct node1 *temp1 = root1->left1;
            free(root1);
            return temp1;
        }
        // node1 with two children: Get the inorder successor (smallest
        // in the right1 subtree)
        struct node1* temp1 = minValuenode1(root1->right1);
        // Copy the inorder successor's content to this node1
        root1->key1 = temp1->key1;
        // Delete the inorder successor
        root1->right1 = deletenode1(root1->right1, temp1->key1);
    }
    return root1;
}
struct bin_tree {
    int data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;
void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }
    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val);
    }
}
void print_preorder(node * tree)
{

    if (tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}
void print_inorder(node * tree)
{
    int a;
    struct  Tree3 * root3;
    root3 = NULL;
    make_empty(root3);
    // FILE  *in = fopen("in.txt","a+");
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
        // fprintf(in,"%d\n",tree->data);
        //fclose(in); // i want to print this as a tree
    }

}
void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n",tree->data);
    }
}
void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}
node* search(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }
    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}
void main()
{
    system("Color C");
    int w;
    system("cls");
    fflush(stdin);
    clock_t tic = clock();
    pthread_t play;
    pthread_t playa;
    pthread_t playb;
    pthread_t playc;
    pthread_t playd;
    pthread_t playe;
    pthread_t playf;
    pthread_t play4;
    pthread_t play5;
    int data4;
    Node4 *root4 = NULL;
    char m;
    srand(time(NULL));
    printf("Loading all assets. Please wait");
    delay(1000);
    system("cls");

    fflush(stdin);

    struct  Tree3 * root3;
    int i;
    root3 = NULL;
    make_empty(root3);
    int a,b,r,l,h,f;
    int deletearg;
    char option;
    inceput:

    system("cls");
    if (option=='9' || option=='7' || option=='8'){goto jump;}
    node *root;
    node *tmp;
    int searcharg;
    root = NULL;
    struct node1 *root1 = NULL;
    printf("Please type what nodes to insert. To stop, input any letter: ");
    while (scanf("%d", &a) && a!='q') {
        root4 = create(root4,a);
        insert(&root,a);
        root1 = insert1(root1, a);
        root3 = insert3(a, root3);
        printf("Please type what nodes to insert. To stop, input any letter: ");
    }
    jump:
    do{
    fflush(stdin);
    printf("0:Insert More Nodes\n1:PreOrder\n2:InOrder\n3:PostOrder\n4:search\n5:Delete Node\n6:Print Tree\n7:Print Random Tree\n8:Exit\n9:Level Traverse\nYour Option: ");
    scanf("%c", &option);
    system("cls");
    switch(option)
    {
        case '0':
        printf("Please type what nodes to insert. To stop, input any letter: ");
        while (scanf("%d", &a) && a!='q') {
        root4 = create(root4,a);
        insert(&root,a);
        root1 = insert1(root1, a);
        root3 = insert3(a, root3);}
        //printf("Input secret. A fost introdus codu ista\nin caz ca cineva imi fura codul.\nScris de Catalin Turcan.");
        break;
    case '1':

        printf("Pre Order Display\n");
        print_preorder(root);
        break;
    case '2':
        printf("In Order Display\n");
        print_inorder(root);
        break;
    case '3':
        printf("Post Order Display\n");
        print_postorder(root);
        break;
    case '4':
        fflush(stdin);
        printf("what to search: ");
        scanf("%d", &searcharg);
        tmp = search(&root, searcharg);
        if (tmp)
        {
            printf("The searched node is present = %d\n", tmp->data);
        }
        else
        {
            printf("Data Not found in tree.\n");
        }
        break;
    default:
        printf("Error! operator is not correct\n");
        break;
    case '5':
        fflush(stdin);
        printf("What to delete: ");
        scanf("%d", &deletearg);
        root1 = deletenode1(root1, deletearg);
        inorder(root1);
        break;
    case '6':
        printf("The tree looks like this:\n");
        print_ascii_tree3(root3);

        break;
        case '7':
            fflush(stdout);
     fflush(stdin);
         fflush(stdout);
         for (l=0;l<100;l++)
         {
            h=rand()%(32000+1-0)+0;
            root3 = insert3(h, root3);
         }
         print_ascii_tree3(root3);
         make_empty(root3);
        break;
           case '8':
       exit(0);
        break;
        case '9':
         fflush(stdin);
         fflush(stdout);
 //       for(;;)
 //   {
 //       printf("\nEnter the elements (-1 to stop) : ");
 //       scanf("%d",&data4);
 //       if(data4==-1) break;
 //      root4 = create(root4,data4);
 //   }

    printf("\nPrinting the elemtents in level order : ");
    levelorder(root4);
    }
    }while(1);
    /* Deleting all nodes of tree */
    //deltree(root);
    clock_t toc = clock();
    printf("\nElapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    getch();
}
