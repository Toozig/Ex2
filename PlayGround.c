//
// Created by toozi on 08/11/2018.
//

#include <stdio.h>
#include "parser.h"
#include "calculateMatch.h"
int main()
{
    Sequence seqArr[MAX_SEQUENCES];
    size_t numOfSeq = parseFile("input.txt", seqArr);
    calculateMatches(seqArr,numOfSeq,-1,1,-1);
}




