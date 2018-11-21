#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
/* Peng Gu, Xuran Wang
 * 11/20/2018
 * This program reads in lines of characters, ignores invalid characters,
 * and prints out the current numeric sum after each line.
 */

struct BigInt{
    int digit;
    struct BigInt *next, *prev;
};

int main(){
    int input;
    int a = 1;
    int read = 0;
    int num = 0;
    int add = 0;
    struct BigInt* headm = NULL;
    struct BigInt* tailm = NULL;
    struct BigInt* headn = NULL;
    struct BigInt* tailn = NULL;
    struct BigInt* loopm;
    struct BigInt* loopn;
    headm = (struct BigInt*)malloc(sizeof(struct BigInt));
    tailm = (struct BigInt*)malloc(sizeof(struct BigInt));
    headn = (struct BigInt*)malloc(sizeof(struct BigInt));
    tailn = (struct BigInt*)malloc(sizeof(struct BigInt));
    if(headm==NULL||headn==NULL||tailm==NULL||tailn==NULL){
	exit(3);
    }
    loopn = headn;
    headm->next = tailm;
    headn->next = tailn;
    headm->prev = NULL;
    headn->prev = NULL;
    tailm->prev = headm;
    tailn->prev = headn;
    tailm->next = NULL;
    tailn->next = NULL;
    while (a==1){
	input = getchar();
	if(input=='\n'||input==EOF){
	    printf("Total: ");
	    loopm = tailm;
	    loopn = tailn;
    	    while((loopm->prev)->prev!=NULL&&(loopn->prev)->prev!=NULL){
		loopm = loopm->prev;
		loopn = loopn->prev;
		num = loopm->digit + loopn->digit + add;
		if(num>=10){
		    loopm->digit = num-10;
		    add = 1;
		}
		else{
		    loopm->digit = num;
		    add = 0;
		}
	    }
	    while(add==1&&(loopm->prev)->prev!=NULL){
		loopm = loopm->prev;
		if(loopm->digit!=9){
		    loopm->digit++;
		    add=0;
		    break;
		}
		loopm->digit = 0;
	    }
    	    if((loopm->prev)->prev==NULL){
		while((loopn->prev)->prev!=NULL||add==1){
    		    if ((loopn->prev)->prev!=NULL){
			loopn = loopn->prev;
			num = loopn->digit + add;
			if(num!=10){
			    add = 0;
			}
			else{
			    num = 0;
			}
		    }
		    else{
			num = 1;
			add = 0;
		    }
		    struct BigInt* tmp = NULL;
		    tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
    	            loopm->prev = tmp;
		    headm->next = tmp;
		    tmp->next = loopm;
		    tmp->prev = headm;
		    tmp->digit = num;
		    loopm = tmp;
		}
	    }
	    loopm = headm;
	    if(headm->next == tailm){
		printf("0");
	    }
	    else{
	        while((loopm->next)->next!=NULL){
		    loopm = loopm->next;
		    printf("%d",loopm->digit);
	        }
	    }
	    printf("\n");
	    if(input==EOF){
		loopm = headm;
		while(loopm->next!=NULL){
		    loopm = loopm->next;
		    free(loopm->prev);
		}
		free(loopm);
		free(tailn);
		free(headn);
		return 0;
	    }
	    loopm = NULL;
	    loopn = headn->next;
	    add = 0;
	    num = 0;
	    read = 0;
	    while(headn->next != tailn){
		headn->next = loopn->next;
		free((headn->next)->prev);
		loopn = headn->next;
		loopn->prev = headn;
	    }
	    loopn = headn;
    	}
	else if(read==0){
	    if(isdigit(input)&&input!='0'){
		read = 1;
		struct BigInt* tmp = NULL;
		tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
	        loopn->next = tmp;
		tailn->prev = tmp;
		tmp->next = tailn;
		tmp->prev = loopn;
		tmp->digit = input-'0';
    		loopn = tmp;
	    }
	    else if(!isspace(input)&&!isdigit(input)){
		read = 2;
	    }
	}
	else if(read==1){
	    if(!isdigit(input)){
		read = 2;
	    }
	    else{
                struct BigInt* tmp = NULL;
		tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
		loopn->next = tmp;
		tailn->prev = tmp;
		tmp->next = tailn;
		tmp->prev = loopn;
		tmp->digit = input-'0';
		loopn = tmp;
	    }
	}
    }
    return 0;
}
