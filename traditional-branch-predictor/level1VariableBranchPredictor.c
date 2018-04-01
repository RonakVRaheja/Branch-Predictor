#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
    FILE *que1;
    size_t byte, nb = 0,i;
    char *pc,*act;
    int PC1;
    char *line;
    long int mispred = 0;
    long int total =0;
    float percent;
    int  bits;
    int decd_limit,uppr_limit;



    for (bits = 2; bits<=20; bits++)
    {
        mispred = 0;
        total =0;
        percent = 0;
        int PHT[1023];

        for(i = 0; i<=1023; i++)
        {
            PHT[i]=00;
        }
        que1 = fopen("branch-trace-gcc.trace","r");

        if (que1 == NULL)
        {
            printf("file can not be opened");
            exit(1);
        }

        byte = getline(&line,&nb,que1);
        decd_limit = (0x000000001 << (bits-1));
        uppr_limit = ((0x000000001 << bits) - 1);

        while(byte != -1)
        {

            pc = strtok(line, " ");
            act = strtok(NULL, " ");

            int PC1 = (atoi(pc) & 0x0000003FF);


            if (*act == 'T')
            {

                if (PHT[PC1] < decd_limit)
                {
                    mispred++;
                }

                PHT[PC1]++;
                if (PHT[PC1] >= uppr_limit)
                    PHT[PC1] = uppr_limit;
            }

            if (*act == 'N')
            {

                if(PHT[PC1] >= decd_limit)
                {
                    mispred++;
                }

                PHT[PC1]--;
                if (PHT[PC1] <= 0)
                    PHT[PC1] = 0;
            }


            byte = getline(&line,&nb,que1);
            total++;



        }

        percent =  100*((float)mispred)/((float)total);


        printf(" \nBITS: %d percent:%f\n",bits,percent);

        fclose(que1);

    }



}
