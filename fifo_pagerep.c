#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,f,i,j,pf=0;
    
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
    int frame[f];
    //set value of each frame to -1
    for (i=0;i<f;i++){
        frame[i] = -1;
    }
    
    //implement fifo
    //replace the pages that arrived first
    printf("\nref str\t\tpage frame\t\thit or fault\n");
    
    for(i=0;i<p;i++){
        printf("%d\t->\t",ref[i]);
        
        //1st check whether page is present
        for (j=0;j<f;j++){
            if (frame[j] == ref[i]) {
                flag[i] = 1;   // ==> HIT
                //pf--;
            }
        }
        
        //pf++;
        //in case of fault
        if (flag[i] == 0) {
            pf++;
            
            //case 1: pf <= f :- insert into ith frame
            if (pf <= f) {
                frame[i] = ref[i];
            }
            
            //case 2: pf>f :- 
            else {
                frame[(pf - 1) % f] = ref[i];
            }
        }
        
        //display the results
        for (j=0; j<f; j++) 
            printf("%d\t",frame[j]);
        if (flag[i] == 0)
            printf("PF\n");
        else
            printf("HIT\n");
    }
    printf("\ntotal no. of page faults is : %d\n",pf);
  
    return 0;
}

/*
output:-
enter no. of pages : 6
enter 6 pages : 1 2 3 2 4 5
enter no. of frames : 3

ref str         page frame              hit or fault
1       ->      1       -1      -1      PF
2       ->      1       2       -1      PF
3       ->      1       2       3       PF
2       ->      1       2       3       HIT
4       ->      4       2       3       PF
5       ->      4       5       3       PF

total no. of page faults is : 5
*/
