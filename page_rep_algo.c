#include <stdio.h>
#include <stdlib.h>

void fifo()
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
}

void lru()
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
        for (j=0; j<f; j++)
            printf("%d\t",frame[j]);
        if (flag[i] == 0)
            printf("PF\n");
        else
            printf("HIT\n");
    }
    printf("\ntotal no. of page faults is : %d\n",pf);
}

void lfu()
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
        for (j=0; j<f; j++)
            printf("%d\t",frame[j]);
        if (flag[i] == 0)
            printf("PF\n");
        else
            printf("HIT\n");
    }
    printf("\ntotal no. of page faults is : %d\n",pf);
}

int main()
{
    int choice;
    printf("page replacement algorithms\n\n");
    printf("menu\n");
    printf("1.fifo\n2.lru\n3.lfu\n4.exit\n\n");
    while (1) {
        printf("enter choice : ");
        scanf("%d",&choice);
        
        switch(choice) {
            case 1: printf("\nfifo\n");
            fifo();
            break;
            case 2: printf("\nlru\n");
            lru();
            break;
            case 3: printf("\nlfu\n");
            lfu();
            break;
            case 4: printf("\nthank you\n");
            exit(0);break;
            default: printf("\ninvalid choice\n");
            break;
        }
    }
    
    return 0;
}

/*
output:-
page replacement algorithms

menu
1.fifo
2.lru
3.lfu
4.exit

enter choice : 1

fifo
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
enter choice : 2

lru
enter no. of pages : 6
enter 6 pages : 1 2 3 2 4 5
enter no. of frames : 3

ref str page frame              hit or fault
1       ->      1       -1      -1      PF
2       ->      1       2       -1      PF
3       ->      1       2       3       PF
2       ->      1       2       3       HIT
4       ->      4       2       3       PF
5       ->      4       2       5       PF

total no. of page faults is : 5
enter choice : 3

lfu
enter no. of pages : 6
enter 6 pages : 1 2 3 2 4 5
enter no. of frames : 3

ref str         page frame              hit or fault
1       ->      1       -1      -1      PF
2       ->      1       2       -1      PF
3       ->      1       2       3       PF
2       ->      1       2       3       HIT
4       ->      4       2       3       PF
5       ->      5       2       3       PF

total no. of page faults is : 5
enter choice : 4

thank you

*/
