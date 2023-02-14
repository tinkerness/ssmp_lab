#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,f,i,j,pf=0,next=0,min;
    
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
    int frame[f],count[f];
    //set value of each frame to -1 & set count for each to 0
    for (i=0;i<f;i++){
        frame[i] = -1;
        count[i] = 0;
    }
    
    //implement lru
    //increase count of the least recently used page
    printf("\nref str\tpage frame\t\thit or fault\n");
    
    for(i=0;i<p;i++){
        printf("%d\t->\t",ref[i]);
        
        //1st check whether page is present
        for (j=0;j<f;j++){
            if (frame[j] == ref[i]) {
                flag[i] = 1;   // ==> HIT
                count[j] = next;
                next++;
            }
        }
        
        //in case of fault
        if (flag[i] == 0) {
            //case 1: i<f :- insert into ith frame
            if (i<f) {
                //printf("%d\t",count[i]);
                frame[i] = ref[i];
                count[i] = next;
                next++;
            }
            
            //case 2: i>=f :- replace least recently used page (has least count)
            else {
                min = 0;
                for (j=1;j<f;j++) {
                    if (count[min] > count[j]) {
                        min = j;
                    }
                }    
                    frame[min] = ref[i];
                    count[min]=next;
                    next++;
                
            }
            
            pf++;
        }
        
        // display the results
        for (j=0; j<f; j++) {
            printf("%d\t",frame[j]);
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
output :-
enter no. of pages : 5
enter 5 pages : 1 2 3 2 4
enter no. of frames : 3

ref str page frame              hit or fault
1       ->      1       -1      -1      PF
2       ->      1       2       -1      PF
3       ->      1       2       3       PF
2       ->      1       2       3       HIT
4       ->      4       2       3       PF

total no. of page faults is : 4
*/
