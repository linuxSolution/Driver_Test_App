#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float an1_offset=0.0,an2_offset=0.0,an3_offset=0.0,an3_offset2=0.0,an4_offset=0.0,an4_offset2=0.0;
float an5_offset=0.0,an6_offset=0.0,an7_offset=0.0,an8_offset=0.0;

float an1_gain=1.0,an2_gain=1.0,an3_gain=1.0,an4_gain=1.0;
float an5_gain=1.0,an6_gain=0.0,an7_gain=1.0,an8_gain=1.0;


void get_calibration_values()
{

    FILE *f = fopen("/home/tester/Desktop/Calibration_Files/calibration_file.txt", "r");

    char buf[1000];

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }


      char s[256];
      while( fgets( s, 256, f) != NULL )
      {
         printf("%s\n", s);
         char str[255]="\0";
           char str1[255]="\0";
           strcpy(str,s);
           strcpy(str1,str);


           char str2 [20][20]={'\0'};

            int i = 0;
        int j = 0;
            int l=0;

            while (*(str + j) != '\0')
        {
            int k = 0;
            while (*(str1 + j) != '=')
            {
                if (*(str1 + j) == '\0')
                    break;
                str2[i][k] = *(str + j);
                j++;
                k++;
            }
            str2[i][++j] = '\0';
                    printf("\n String value : %s", str2[i]);

            //j++;
            i++;
        }

            if(strcmp(str2[0],"an1_offset")==0)
            {
                an1_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an1_gain")==0)
            {
                an1_gain=atof(str2[1]);
            }


            else if(strcmp(str2[0],"an2_offset")==0)
            {
                an2_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an2_gain")==0)
            {
                an2_gain=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an3_offset")==0)
            {
                an3_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an3_offset2")==0)
            {
                an3_offset2=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an3_gain")==0)
            {
                an3_gain=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an4_offset")==0)
            {
                an4_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an4_offset2")==0)
            {
                an4_offset2=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an4_gain")==0)
            {
                an4_gain=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an5_offset")==0)
            {
                an5_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an6_gain")==0)
            {
                an6_gain=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an7_offset")==0)
            {
                an7_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an7_gain")==0)
            {
                an7_gain=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an8_offset")==0)
            {
                an8_offset=atof(str2[1]);
            }

            else if(strcmp(str2[0],"an8_gain")==0)
            {
                an8_gain=atof(str2[1]);
            }

      }

    fclose(f);
}
