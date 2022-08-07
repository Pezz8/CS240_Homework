#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    int value;        // character stored in the node
    struct NODE *next; // address pointing to the next node in the list
    struct NODE *prev; // address pointing to the previous node in the list
};

void printLinkedList(struct NODE *p)
{
    while (p != NULL)
    {
        printf("%d", (*p).value);
        p = (*p).next;
    }
    printf("\n");
}

void printLinkedList_ReverseOrder(struct NODE *p)
{
    if (p == NULL)
        return;
    struct NODE *last;
    last = p;
    while ((*last).next != NULL)
    {
        last = (*last).next;
    }
    struct NODE *ptr = last;
    while (ptr != NULL)
    {
        printf("%d", (*ptr).value);
        ptr = (*ptr).prev;
    }
    printf("\n");
}

void insertNode(struct NODE **addr_first_pointer, int pos, struct NODE *p)
{

    struct NODE *first_pointer;
    first_pointer = *addr_first_pointer;
    struct NODE *node_pointer = first_pointer;
    int i;
    for (i = 0; i < pos; i++)
    {
        node_pointer = (*node_pointer).next;
        if (node_pointer == NULL)
        {
            // position pos does not exist
            return;
        }
    }

    struct NODE *p1 = node_pointer->prev;

    if (node_pointer == NULL)
    {
        if (p1 == NULL)
        {
            *addr_first_pointer = node_pointer;
        }
        else
        {
            (*p1).next = node_pointer;
            (*node_pointer).prev = p1;
        }
    }
    else
    {

        if (p1 == NULL)
        {
            (*p).next = node_pointer;
            (*node_pointer).prev = p;
            *addr_first_pointer = p;
        }
        else
        {
            (*p1).next = p;
            (*p).prev = p1;
            (*p).next = node_pointer;
            (*node_pointer).prev = p;
        }
    }
}

struct NODE *addNewNode_append(struct NODE *head, int new_int)
{
    struct NODE *new_node = NULL;
    struct NODE *last = NULL;
    new_node = malloc(sizeof(struct NODE));
    (*new_node).value = new_int;
    (*new_node).next = NULL;
    (*new_node).prev = NULL;

    if (head == NULL)
    {

        head = new_node;
    }
    else
    {
        struct NODE *last = NULL;
        last = head;
        while ((*last).next != NULL)
        {
            last = (*last).next;
        }
        (*last).next = new_node;
        (*new_node).prev = last;
    }
    return head;
}

int getPosition(struct NODE *p, int number)
{
    int pos = 0;
    int flag1;

    while (p != NULL)
    {
        //printf("%d - %d\n",p->value, number);

        if (p->value < number)
        {
            //printf("flag is 1\n");
            flag1 = 1;
        }
        else{
            if(flag1 == 1){
                return pos;
            }
            else{
                flag1 = 0;
            }
        }
        if ((p->value > number) && (flag1 == 1))
        {
            return pos;
            break;
        }
        pos++;
        //printf("%d pos\n",pos);
         if(p->next == NULL){
             if(flag1 == 0){
                 return 0;
             }
             else{
                return pos;
             }

        }
        p = p->next;
    }
}

int main()
{
    int ch;
    int numberOfNodes;
    int numberToInsert;
    int pos;
    struct NODE *p = NULL;

    scanf("%d", &numberOfNodes);

    for (int i = 0; i < numberOfNodes; i++)
    {
        scanf("%d", &ch);
        p = addNewNode_append(p, ch);
    }

    scanf("%d", &numberToInsert);

    pos = getPosition(p, numberToInsert);

    struct NODE *node_p;
    node_p = malloc(sizeof(struct NODE));
    (*node_p).value = numberToInsert;
    (*node_p).next = NULL;
    (*node_p).prev = NULL;

    if(pos == numberOfNodes){
        p = addNewNode_append(p, numberToInsert);
    }
    else{
        insertNode(&p, pos, node_p);
    }

    printLinkedList(p);
    printLinkedList_ReverseOrder(p);

    return 0;
}