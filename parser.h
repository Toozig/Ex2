//
// Created by toozi on 07/11/2018.
//
#include <stdio.h>
#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#define FIRST_CHAR 1


/**
 * @brief the maximal sequences in a file.
 */
#define MAX_SEQUENCES 100


#define END_OF_STR 1
/**
 * @brief represents sequence
 */
typedef struct
{
    char *sequenceArr;
    size_t arrSize;
    size_t seqLen;
    char *name;

} Sequence;


size_t parseFile(char fileName[], Sequence seqArr[MAX_SEQUENCES]);

#endif //UNTITLED_PARSER_H