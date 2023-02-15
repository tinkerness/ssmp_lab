/** pass1 of two-pass assembler*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1,*f2,*f3,*f4;
    int lc,sa,op_val,len;   //loctr,staddr,operand value,length
    char label[20],opcode[20],optc[20],operand[20];  //optc=opcode in optab
    
    f1 = fopen("input.txt","r");
    f3 = fopen("symtab.txt","w");
    f4 = fopen("inter.txt","w");
    
    fscanf(f1,"%s %s %d",label,opcode,&op_val);
    if (strcmp(opcode,"START") == 0) {
        sa = op_val;
        lc = sa;
        fprintf(f4,"\t%s\t%s\t%d\n",label,opcode,op_val);
    }
    else
        lc = 0;
    fscanf(f1,"%s %s",label,opcode);
    
    while (!feof(f1)) {
        fscanf(f1,"%s",operand);
        fprintf(f4,"%d\t%s\t%s\t%s\n",lc,label,opcode,operand);
        
        //if label present, insert (locctr,label) into symtab
        if(strcmp(label,"**") != 0) {
            fprintf(f3,"%d\t%s\n",lc,label);
        }
        
        //check optab for opcode, if present add 3 to locctr
        f2 = fopen("optab.txt","r");
        fscanf(f2,"%s",optc);
        while(!feof(f2)) {
            if (strcmp(opcode,optc) == 0) {
                lc = lc + 3;
                break;
            }
            fscanf(f2,"%s",optc);
        }
        fclose(f2);
        
        //else check for word,resw,resb, or byte
        if (strcmp(opcode,"WORD") == 0) {
            lc = lc + 3;
        }
        else if (strcmp(opcode,"RESW") == 0) {
            op_val = atoi(operand);
            lc = lc + (3 * op_val);
        }
        else if (strcmp(opcode,"RESB") == 0) {
            op_val = atoi(operand);
            lc = lc + op_val;
        }
        else if (strcmp(opcode,"BYTE") == 0) {
            if (operand[0] == 'X') {
                lc = lc + 1;
            }
            else {
                len = strlen(operand) - 3;
                lc = lc + len;
            }
        }
        fscanf(f1,"%s %s",label,opcode);
    }
    
    if (strcmp(opcode,"END") == 0) {
        fprintf(f4,"program length = %d\n",lc-sa);
    }
    fclose(f1);
    fclose(f3);
    fclose(f4);
    
    return 0;
}
