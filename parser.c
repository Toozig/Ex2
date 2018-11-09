//
// Created by toozi on 07/11/2018.
//
#include <stdio.h>
#include <mem.h>
#include <malloc.h>
#include "parser.h"


/**
 * @brief the maximal char in a line of a file.
 */
#define MAX_CHAR_IN_LINE 100



/**
 * @brief the char which start each sequence header
 */
#define HEADER ">"


/**
 * Creates a new struct of sequence
 * @return pointer to the struct, 0 if failed
 */
static Sequence* createSequence()
{
    Sequence *sequence = (Sequence *) malloc(sizeof(Sequence));
    if (sequence == NULL)
    {
        fprintf(stderr, "ERROR could not create new sequence");
        return NULL;
    }
    sequence->sequenceArr =  malloc(sizeof(char) * MAX_CHAR_IN_LINE + 1);
    sequence->seqLen = 0;
    sequence->arrSize = MAX_CHAR_IN_LINE;
    return sequence;
}

/**
 * This function adds a given line into a sequence.
 * @param sequence struct of sequence
 * @param line the line to add
 * @return 0 if faild, 1 otherwise
 */
static int addLineToSequence(Sequence* sequence, char *line)
{
    if (strlen(line) > sequence->arrSize - sequence->seqLen)
    {
        sequence->sequenceArr = realloc(sequence->sequenceArr,
                sequence->arrSize + sizeof(char) * MAX_CHAR_IN_LINE + END_OF_STR);
        if (!sequence->sequenceArr)
        {
            fprintf(stderr, "ERROR Could not make more memory");
            return 0;
        }
        sequence->arrSize += MAX_CHAR_IN_LINE;
    }
    memcpy(sequence->sequenceArr + sequence->seqLen , line, strlen(line));
    sequence->seqLen += strlen(line) - END_OF_STR;

    return 1;
}

/**
 * free the memory of the sequence array if the program fails.
 * @param seqArr  the array of sequence.
 * @param numOfSeq the number of sequences in it.
 */
void freeArr(Sequence* seqArr[], size_t numOfSeq)
{
    size_t i;
    for (i = 0; i < numOfSeq; i++)
    {
        free(seqArr[i]->name);
        free(seqArr[i]);
    }
}


/**
 * This function resize the char array of a sequence down if the array is bigger than the string.
 * @param sequence
 * @return 0 if faild, 1 otherwise
 */
static int sizeDownArr(Sequence* sequence){
    if( sequence->seqLen < sequence->arrSize)
    {
        sequence->sequenceArr = realloc(sequence->sequenceArr,sequence->seqLen);
        if(!sequence->sequenceArr){
            fprintf(stderr,"ERROR memory problem");
            return 0;
        }
        sequence->sequenceArr[strlen(sequence->sequenceArr)] = '\0';
        sequence->arrSize = sequence->seqLen;
    }
    return 1;
}

/**
 * This function  parse a fle of sequnce and convert it into an array of sequnces
 * @param fileName the name of the file
 * @param seqArr  the array which the sequnces will be put into
 * @return 0 if failed or no sequence were read, the number of sequences otherwise
 */
size_t parseFile(char fileName[], Sequence seqArr[MAX_SEQUENCES])
{
    FILE *file = NULL;
    file = fopen(fileName, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return 0;
    }
    Sequence *cur = NULL;
    size_t numOfSeq = 0;
    char line[MAX_CHAR_IN_LINE + END_OF_STR];
    while (fgets(line, MAX_CHAR_IN_LINE, file))
    {
        if (strncmp(line, HEADER, FIRST_CHAR) != 0)
        {
            addLineToSequence(cur, line);
        } else
        {
            if (cur != NULL)
            {
                if(!sizeDownArr(cur)){
                    freeArr(&seqArr, numOfSeq);
                    free(cur);
                    return 0;
                }

                seqArr[numOfSeq] = *cur;
                numOfSeq++;
            }
            cur = createSequence();
            if (cur == NULL)
            {
                freeArr(&seqArr, numOfSeq);
                return 0;
            }
            cur->name = malloc(sizeof(char)* strlen(line));
            if (cur->name == NULL)
            {
                freeArr(&seqArr, numOfSeq);
                return 0;
            }
            memcpy(cur->name, line + 1,strlen(line));
        }
    }
    if(cur != NULL)
    {
        seqArr[numOfSeq] = *cur;
        numOfSeq++;
    }
    return numOfSeq;

}


