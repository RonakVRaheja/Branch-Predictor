#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
    size_t byte, nb = 0,i;
    char *pc,*act;
    int PC1;
    char *line;
    long int mispred = 0;
    long int total =0;
    float percent;
    int GHR = 0x0000000000;
    int  bits;
    int decd_limit,uppr_limit;
    FILE *que1;
    int PHT[1023];


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

        que1 = fopen("/home/jaydeep/CA-ASSIGNMENTS/HW2/branch-trace-gcc.trace","r");

        if (que1 == NULL)
        { printf("file can not be opened");
        exit(1);
        }
        byte = getline(&line,&nb,que1);
        pc = strtok(line, " ");
        act = strtok(NULL, " ");
        decd_limit = (0x000000001 << (bits-1));
        uppr_limit = ((0x000000001 << bits) - 1);

        while(byte != -1)
        {



            if (*act == 'T'){


                if (PHT[GHR] < decd_limit){
                    mispred++;
                }
                PHT[GHR]++;
                if (PHT[GHR] >= uppr_limit)
                    PHT[GHR] = uppr_limit;

                GHR = (GHR<<1) |0x01;
                GHR = GHR & 0x0000003FF;

            }

            if (*act == 'N'){


                if(PHT[GHR] >= decd_limit){
                    mispred++;
                }
                PHT[GHR]--;
                if (PHT[GHR] <= 0)
                    PHT[GHR] = 0;

                GHR = (GHR<<1) & 0x0000003FE;
                GHR = GHR & 0x0000003FF;

            }

            byte = getline(&line,&nb,que1);
            pc = strtok(line, " ");
            act = strtok(NULL, " ");
            total++;



        }

        percent =  100*((float)mispred)/((float)total);


        printf(" \nBITS: %d percent:%f\n",bits,percent);

        fclose(que1);


    }


}
