#include <stdio.h>
#include <dxtmpl.h>
#include "parser.h"
#include "calculateMatch.h"

#define NUM_OF_ARGS 5

#define FILE_NAME 2

/**
 * Checks if the args are valid
 * @param argc num of args
 * @param argv  array of the args
 * @return -1 if not vaild, 0 otherwise
 */
static int checkArgs(int argc, char *argv[])
{
    if(argc != NUM_OF_ARGS)
    {
        return -1;
    }
    int i;
    int d;
    for (i = 1; i < NUM_OF_ARGS ; ++i)
    {
        if(!atoi(argv[i]))
        {
            if ((strlen(argv[i]) == 1 && ((char) argv[i] - '0') == 0 ))
            {
                continue;
            }
            return -1;
        }
    }
    return 0;
}
int main(int argc, char *argv[])
{
    if(checkArgs(argc, argv))
    {
        printf("CompareSequences <path_to_sequences_file> <m> <s> <g>\n");
        return -1;
    }
    Sequence seqArr[MAX_SEQUENCES];
    int numOfSeq = parseFile(argv[FILE_NAME], seqArr);
    if(numOfSeq == -1)
    {
        return  -1;
    }
    calculateMatches(seqArr, numOfSeq,-1,1,-1);
    return 0;
}