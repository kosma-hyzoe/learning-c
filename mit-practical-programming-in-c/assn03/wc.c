#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define IN 1
#define OUT 0
int main(int argc,char* argv[])
{
    FILE* fp=NULL;
    int   nfiles =--argc; /*ignore the name of the program itself*/
    int   argidx =1;      /*ignore the name of the program itself*/
    char* currfile="";
    char  c;
    /*count of words,lines,characters*/
    unsigned long nw=0,nl=0,nc=0;
	int state;

    if(nfiles==0)
    {
        fp=stdin; /*standard input*/
        nfiles++;
    }
    else /*set to first*/
    {
        currfile=argv[argidx++];
        fp=fopen(currfile,"r");
    }
    while(nfiles>0) /*files left >0*/
    {
       if(fp==NULL)
        {
            fprintf(stderr,"Unable to open input\n");
            exit(-1);
        }

        nc=nw=nl=0;
		state = OUT;
        while((c=getc(fp))!=EOF)
        {
			nc++;
			if (isspace(c)) {
				if (state == IN)
					state = OUT;
				if (c == '\n')
					nl++;
			} else if (state == OUT) {
				state = IN;
				nw++;
			}
        }
        printf("%ld %ld %ld %s\n",nl,nw,nc,currfile);

        /*next file if exists*/
        nfiles--;
        if(nfiles>0)
        {
            currfile=argv[argidx++];
            fp     =fopen(currfile,"r");
        }
    }
	return 0;
}
