#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,f,i,j,pf=0,move=0,index;
    
    printf("enter no. of pages : ");
    scanf("%d",&p);
    //find ref_str and set flag for each page to 0
    int ref[p],flag[p];
    printf("enter %d pages : ",p);
    for(i=0;i<p;i++){
        scanf("%d",&ref[i]);
        flag[i] = 0;
    }
    
    printf("enter no. of frames : ");
    scanf("%d",&f);
    int frame[f],freq[f];
    //set value of each frame to -1 // & set frequency for each to 0
    for (i=0;i<f;i++){
        frame[i] = -1;
        freq[i] = 0;
    }
    
    //implement lfu
    //increase frequency of pages being used
    printf("\nref str\t\tpage frame\t\thit or fault\n");
    
    for(i=0;i<p;i++){
        printf("%d\t->\t",ref[i]);
        
        //1st check whether page is present
        for (j=0;j<f;j++){
            if (frame[j] == ref[i]) {
                flag[i] = 1;   // ==> HIT
                freq[j]++;
            }
        }
        
        //in case of fault
        if (flag[i] == 0) {
            //case 1: i<f :- insert into (move)th frame
            if (pf<f) {
                //printf("%d\t",freq[i]);
                frame[move] = ref[i];
                freq[move] = 1;
                move = (move + 1) % f;
            }
            
            //case 2: i>=f :- replace least frequently used page (has least frequency)
            else {
                index = 0;
                for (j=1;j<f;j++) {
                    if (freq[index] > freq[j]) {
                        index = j;
                    }
                }    
                    frame[index] = ref[i];
                    freq[index]=1;
            }
            
            pf++;
        }
        
        // display the results
        for (j=0; j<f; j++) {
            printf("%d,%d\t",frame[j],freq[j]);
        }
        if (flag[i] == 0)
            printf("PF\n");
        else
            printf("HIT\n");
        //printf("\n");
    }
    printf("\ntotal no. of page faults is : %d\n",pf);
      
    return 0;
}

/*
output:
enter no. of pages : 10
enter 10 pages : 1 2 3 1 1 2 2 2 4 3
enter no. of frames : 3

ref str         page frame              hit or fault
1       ->      1,1     -1,0    -1,0    PF
2       ->      1,1     2,1     -1,0    PF
3       ->      1,1     2,1     3,1     PF
1       ->      1,2     2,1     3,1     HIT
1       ->      1,3     2,1     3,1     HIT
2       ->      1,3     2,2     3,1     HIT
2       ->      1,3     2,3     3,1     HIT
2       ->      1,3     2,4     3,1     HIT
4       ->      1,3     2,4     4,1     PF
3       ->      1,3     2,4     3,1     PF

total no. of page faults is : 5
*/
