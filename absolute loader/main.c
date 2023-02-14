#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *fp;
    int i,j,l,addr1,staddr1;
    char name[10],line[50],name1[10],addr[10],staddr[10];
    //clrscr();
    
    printf("enter program name : ");
    scanf("%s",name);
    
    fp = fopen("abs_src.txt","r");
    fscanf(fp,"%s",line);
    //printf("1st line : %s",line);
    
    //get pgm name
    for (i=2,j=0;i<8,j<6;i++,j++) {
        name1[j] = line[i];
    }name1[j] = '\0';
    printf("\nname from obj. : %s\n",name1);
    
    //get addr
    for (i=9,j=0;i<15,j<6;i++,j++)    {
        addr[j] = line[i];
    }addr[j] = '\0';
    addr1 = atoi(addr);
    printf("staddr from obj. : 00%d\n",addr1);
    
    //get length
    for (i=17,j=0;i<21,j<4;i++,j++)    {
        addr[j] = line[i];
    }addr[j] = '\0';
    l = atoi(addr);
    printf("len from obj. : 00%d\n\n",l);
    
    //verify pgm name
    if (strcmp(name,name1) == 0) {
        do{
            fscanf(fp,"%s",line);
            if(line[0] == 'T')
            {
                for(i=2,j=0;i<8,j<6;i++,j++) {
                    staddr[j] = line[i];
                }
                staddr[j] = '\0';
                staddr1 = atoi(staddr);
                //printf("00%d\n",staddr1);
                
                i=12;
                while(line[i] != '$') {
                    if (line[i] != '^') {
                        //print the staddr,1st byte,2nd byte
                        printf("00%d\t%c%c\n",staddr1,line[i],line[i+1]);
                        staddr1++;
                        i=i+2;
                    }
                    else i++;
                }
            }
            else if (line[0] == 'E')
                fclose(fp);
        }while(!feof(fp));
    }
    getch();
}
