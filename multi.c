#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
/* Peng Gu, Xuran Wang
 * 11/20/2018
 * This program reads in lines of characters and ignores invalid characters.
 * After reading each line, it  prints out the result of multiplication of 
 * all numbers read in past lines.
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
    struct BigInt* loopo;
    struct BigInt* loopp;
    struct BigInt* loopq;
    struct BigInt* headq;
    struct BigInt* tailq;
    struct BigInt* tmp;
    headm = (struct BigInt*)malloc(sizeof(struct BigInt));
    tailm = (struct BigInt*)malloc(sizeof(struct BigInt));
    headn = (struct BigInt*)malloc(sizeof(struct BigInt));
    tailn = (struct BigInt*)malloc(sizeof(struct BigInt));
    headq = (struct BigInt*)malloc(sizeof(struct BigInt));
    tailq = (struct BigInt*)malloc(sizeof(struct BigInt));
    tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
    if(headm==NULL||headn==NULL||tailm==NULL||tailn==NULL){
	exit(3);
    }
    loopn = headn;
    tmp->digit=1;
    headm->next = tmp;
    tmp->next = tailm;
    headn->next = tailn;
    headq->next = tailq;
    headm->prev = NULL;
    headn->prev = NULL;
    headq->prev = NULL;
    tailm->prev = tmp;
    tmp->prev = headm;
    tailn->prev = headn;
    tailq->prev = headq;
    tailm->next = NULL;
    tailq->next = NULL;
    tailn->next = NULL;
    while (a==1){
	input = getchar();
	if(input=='\n'||input==EOF){
	    printf("Total: ");
	    //If no valid number is read from a line, it equals reading just '1' from the line
	    if(headn->next!=tailn){
	        loopm = tailm;
	        loopn = tailn->prev;
		add = 0;
		loopq = tailq;
	        while((loopm->prev)->prev!=NULL){
	            loopm = loopm->prev;
		    loopo = loopm;
		    loopp = loopn;
		    num = add + (loopo->digit)*(loopp->digit);
		    while((loopo->next)->next!=NULL&&(loopp->prev)->prev!=NULL){
		        loopo = loopo->next;
			loopp = loopp->prev;
		        num = num + (loopo->digit)*(loopp->digit);
		    }
		    if(num>=10){
			add = num/10;
			num = num%10;
		    }
		    else{
		 	add = 0;
		    }
		    struct BigInt* tmp = NULL;
		    tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
		    loopq->prev = tmp;
		    headq->next = tmp;
		    tmp->next = loopq;
		    tmp->prev = headq;
		    tmp->digit = num;
		    loopq = tmp;
	        }
	        while((loopn->prev)->prev!=NULL){
		    loopn = loopn->prev;
		    loopo = loopm;
		    loopp = loopn;
		    num = add + (loopo->digit)*(loopp->digit);
		    while((loopo->next)->next!=NULL&&(loopp->prev)->prev!=NULL){
			loopo = loopo->next;
			loopp = loopp->prev;
			num = num + (loopo->digit)*(loopp->digit);
		    }
		    if(num>=10){
			add = num/10;
			num = num%10;
		    }
		    else{
			add = 0;
		    }
		    struct BigInt* tmp = NULL;
		    tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
		    loopq->prev = tmp;
		    headq->next = tmp;
		    tmp->next = loopq;
		    tmp->prev = headq;
		    tmp->digit = num;
		    loopq = tmp;
	        }
		if(add>0){
		    struct BigInt* tmp = NULL;
		    tmp = (struct BigInt*)malloc(sizeof(struct BigInt));
		    loopq->prev = tmp;
		    headq->next = tmp;
		    tmp->next = loopq;
		    tmp->prev = headq;
		    tmp->digit = add;
		    add = 0;
		}
		num = 0;
		//Trying to make sure no memory leaks in Valgrind, but failed
		/* 
		loopm = headm->next;
		while(loopm->next!=NULL){
		    loopm = loopm->next;
		    free(loopm->prev);
		}
		struct BigInt* headm = NULL;
		headm = (struct BigInt*)malloc(sizeof(struct BigInt));
		struct BigInt* tailm = NULL;
		tailm = (struct BigInt*)malloc(sizeof(struct BigInt));
		headm->next = tailm;
                tailm->prev = headm;
		headm->prev = NULL;
		tailm->next = NULL;*/
    		headm = headq;
		tailm = tailq;
		loopn = headn;
		struct BigInt* headq = NULL;
		headq = (struct BigInt*)malloc(sizeof(struct BigInt));
		struct BigInt* tailq = NULL;
		tailq = (struct BigInt*)malloc(sizeof(struct BigInt));
		headq->prev = NULL;
		tailq->next = NULL;
		headq->next = tailq;
		tailq->prev = headq;
		loopq = tailq;
	    }
    	    loopm = headm;
	    while((loopm->next)->next!=NULL){
		loopm = loopm->next;
	        printf("%d",loopm->digit);
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
		free(tailq);
		free(headq);
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
