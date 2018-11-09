//
// Created by toozi on 08/11/2018.
//





#include <malloc.h>
#include <mem.h>
#include "parser.h"
#include "calculateMatch.h"

/**
 * calculate the location of a node in an array
 */
#define INDEX(x, y, row) ((x) * (row) + y)

/**
 * represents rubiq in the matrix
 * next and prev are there to get the way to get the best match
 */
typedef struct Node
{
    int data;
    size_t row;
    size_t col;
    struct Node *next;
    struct Node *prev;
    char print[MATCH_RELATION];
} Node;

void updateCell(Node *cell, const Node *nodeArr, size_t index, int grade,
                const char rowChar, const char colChar, const char space)
{
    cell->data = grade;
    Node *dad = (Node *) &nodeArr[index];
    dad->next = cell;
    cell->prev = dad;
    sprintf(cell->print, "%c%c%c", rowChar, space, colChar);
}


/**
 * This function initialize matrix  for the match calculation
 * @param nodeArr the matrix
 * @param rowLen the length of the row
 * @param colLen the length of the column
 * @param gap the gap factor
 * @return  0 if failed, 1 otherwise
 */
static void initializeMatrix(Node *nodeArr, const size_t rowLen, const size_t colLen, const int gap)
{
    size_t i;
    //initialize row
    nodeArr[0].data = 0;
    Node *node;
    size_t index;
    for (i = 1; i < rowLen; i++)
    {
        index = INDEX(0, i, colLen);
        node = &nodeArr[index];
        node->data = gap * i;
        node->row = 0;
        node->col = i;
    }
    for (i = 1; i < colLen; ++i)
    {
        index = INDEX(i, 0, rowLen);
        node = &nodeArr[index];
        node->data = gap * i;
        node->row = i;
        node->col = 0;
    }
}

/**
 * this function calculate the grade for a given cell
 * @param cell  the cell to grade
 * @param nodeArr cell's array
 * @param row the sequence of the row
 * @param col the sequence of the col
 * @param matchFactor the factor for matching
 * @param gapFactor the factor given for gap
 * @param misMatchFactor factor for miss matching
 */
void calculateCell(Node *cell, Node *nodeArr, const char rowChar, const char colChar,
                   size_t colLen, int matchFactor, int gapFactor, int misMatchFactor)
{
    int doesMatch = rowChar == colChar;
    int matchScore = doesMatch ? (nodeArr[INDEX(cell->row - 1, cell->col - 1, colLen)].data + matchFactor) :
                     (nodeArr[INDEX(cell->row - 1, cell->col - 1, colLen)].data + misMatchFactor);
    int gapRowGrade = nodeArr[INDEX(cell->row - 1, cell->col, colLen)].data + gapFactor;
    int gapColGrade = nodeArr[INDEX(cell->row, cell->col - 1, colLen)].data + gapFactor;

    if (matchScore >= gapColGrade && matchScore >= gapRowGrade)
    {
        char space;
        if (doesMatch)
        {
            space = '-';
        } else
        {
            space = ' ';
        }
        updateCell(cell, nodeArr, INDEX(cell->row - 1, cell->col - 1, colLen), matchScore, rowChar, colChar, space);
        return;
    }
    if (gapRowGrade >= matchScore && gapRowGrade >= gapColGrade)
    {
        updateCell(cell, nodeArr, INDEX(cell->row - 1, cell->col, colLen), gapRowGrade, '|', colChar, ' ');
        return;
    }
    updateCell(cell, nodeArr, INDEX(cell->row, cell->col - 1, colLen), gapColGrade, rowChar, '|', ' ');
}

void printResults(char *seq1Name, char *seq2Name, Node *cell)
{
    seq1Name[strlen(seq1Name) -1] = '\0';
    seq2Name[strlen(seq2Name) -1] = '\0';
    printf("Score for alignment of %s to %s is %d", seq1Name, seq2Name, cell->data);
    Node *head = cell;
    while (head->prev != NULL)
    {
        head->prev->next = head;
        head = head->prev;
    }
    while (head != NULL)
    {
        printf("%s\n", head->print);
        head = head->next;
    }
}

int calculateMatch(Node *nodeArr, const char *row, const char *col, size_t rowLen, size_t colLen,
                   const int gap, const int match, const int misMatch)
{
//    size_t rowLen = row->seqLen + 1, colLen = col->seqLen + 1;
//    nodeArr = (Node *) calloc(colLen * rowLen, sizeof(Node));
//    if (nodeArr == NULL)
//    {
//        fprintf(stderr, "ERROR memory problem");
//        return 0;
//    }
//    initializeMatrix(nodeArr, rowLen, colLen, gap);
    printf("    ");
    for (int k = 0; k < rowLen; k++)
    {
        printf("| %c  ", row[k]);
    }
    size_t i;
    size_t j;
    for (i = 1; i < rowLen; i++)
    {
        printf("| %c ", col[i - 1]);
        char rowChar = row[i - 1];
        for (j = 1; j < colLen; j++)
        {
            char colChar = col[j - 1];
            Node *node = &nodeArr[INDEX(i, j, colLen)];
            node->row = i;
            node->col = j;
            calculateCell(node, nodeArr, rowChar, colChar, colLen, match, gap, misMatch);
            printf("| %d ", node->data);
            if (j + 1 == colLen)
            {
                printf("|\n");
            }
        }
    }
//    printf("\n------------------\n");
//    printf("          ");
//    for (int k = 0; k < rowLen; k++)
//    {
//        printf("| %c  ", row[k]);
//    }
//    printf(" |\n| %c |", col[0]);
//    int x = 1;
//    for (int l = 0; l < rowLen * colLen; l++)
//    {
//        if (l % rowLen == 0 && l != 0)
//        {
//            printf("|\n| %c ", col[x]);
//            x++;
//        }
//        printf("| %d ", nodeArr[l].data);
//    }
    return 1;
}

int calculateMatches(Sequence seqArr[], size_t numOfSeq, int gap, int match, int misMatch)
{

    size_t i;
    size_t j;
    for (i = 0; i < numOfSeq - 1; i++)
    {
        Sequence *row = &seqArr[i];
        for (j = i + 1; j < numOfSeq; j++)
        {
            Sequence *col = &seqArr[j];
            Node *nodeArr;
            size_t rowLen = row->seqLen + 1, colLen = col->seqLen + 1;
            nodeArr = (Node *) calloc(colLen * rowLen, sizeof(Node));
            if (nodeArr == NULL)
            {
                fprintf(stderr, "ERROR memory problem");
                return 0;
            }
            initializeMatrix(nodeArr, rowLen, colLen, gap);
            calculateMatch(nodeArr, row->sequenceArr, col->sequenceArr,rowLen,
                    colLen, gap, match, misMatch);
            printResults(row->name, col->name, &nodeArr[rowLen*colLen -1]);

        }
    }
    return 1;
}
