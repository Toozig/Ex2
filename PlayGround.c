//
// Created by toozi on 08/11/2018.
//

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
//#include <dxtmpl.h>
#include "parser.h"
#include "calculateMatch.h"

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node *head = NULL;

void deleteAlt()
{
    Node *tmp;
    Node *cur = head;
    while(cur != NULL)
    {
        tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
        cur = cur->next;
    }
}

void push(int new_data)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data  = new_data;
    new_node->next = head;
    head = new_node;
}

void printList()
{
    Node *temp = head;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void deleteList()
{
    Node *temp = head;
    while(temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;
}

int main()
{
//    Sequence seqArr[MAX_SEQUENCES];
//    size_t numOfSeq = parseFile("input.txt", seqArr);
//    calculateMatches(seqArr,numOfSeq,-1,1,-1);
    push(1);
    push(2);
    push(3);
    push(4);
    printList();
    deleteAlt();
    printList();
    deleteList();



    }




