//
// Created by toozi on 08/11/2018.
//

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
//#include <wsman.h>
//#include <dxtmpl.h>
#include "parser.h"
#include "calculateMatch.h"

void decode(char *text)
{
    int a = 0;
    int i;
    for(i=0; i < strlen(text); i++)
    {
        if((int) (text[i] -'0') > 9)
        {
            printf("%c", text[i]);
        }else{
            while((int) (text[i] - '0') <10){
                a = a*10 + (int) (text[i] - '0');
                i++;
            }
            while( a != 0)
            {
                printf("%c",text[i]);
                a--;
            }
        }
    }
}

int main()
{
    Sequence seqArr[MAX_SEQUENCES];
    size_t numOfSeq = parseFile("input.txt", seqArr);
    calculateMatches(seqArr,numOfSeq,-1,1,-1);


//    int a;
//    scanf("%d\n", &a);
//    char *b = (char *) malloc(sizeof(char)*a + 1);
//    fgets(b, a+1, stdin);
//    int i;
//    for(i = a-1;  i >= 0; i--)
//    {
//        printf("%c", b[i]);
//    }
}




