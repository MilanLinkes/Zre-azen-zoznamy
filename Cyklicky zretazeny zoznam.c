#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

typedef struct TWN {
	float data;
	struct TWN *prev;
	struct TWN *next;
}TWN;

typedef struct {
	TWN *cur;
}CTWL;


CTWL *ctwl_create_empty(void) {
	
	CTWL *novy_zoznam;

	novy_zoznam = (CTWL*)malloc(sizeof(CTWL));

	novy_zoznam->cur = NULL;

	return novy_zoznam;
}

TWN *ctwl_insert_right(CTWL* list, float val){
	TWN *flag, *novy;
	
	flag = malloc(sizeof(TWN));
	novy = malloc(sizeof(TWN));
	
	novy->data = val;

	if(list->cur==NULL){
		list->cur = novy;
		list->cur->next = novy;
		list->cur->prev = novy;
			
		return novy;
	} else {
		flag = list->cur->next;
		novy->prev = list->cur;
		list->cur->next = novy;
		novy->next = flag;
		flag->prev = novy;

		return novy;
		}
}

TWN *ctwl_insert_left(CTWL* list, float val){
	TWN *flag, *novy;
	
	flag = malloc(sizeof(TWN));
	novy = malloc(sizeof(TWN));
	
	novy->data = val;
	
	if(list->cur==NULL){
		list->cur = novy;
		list->cur->next = novy;
		list->cur->prev = novy;
		
		return novy;
	} else {
		flag = list->cur->prev;
		novy->next = list->cur;
		list->cur->prev = novy;
		novy->prev = flag;
		flag->next = novy;

		return novy;
		}
}

CTWL *ctwl_create_random(unsigned int size) {
	int i;
	float data;
	CTWL *list;
	TWN *flag;
	
	list = ctwl_create_empty();
		
	flag = malloc(sizeof(TWN));
	
	flag = list->cur;
	
	for(i=1; i<=size; i++){
		data = rand()%5;
		list->cur = ctwl_insert_right(list, data);
		printf("%d ", list->cur->data);
		}

	return list;	
}

void ctwl_print(CTWL *list){
	CTWL *prvy;
	int i;
	prvy = list;
	
	do{
		printf("%d ", list->cur->data);
	} while(prvy != list);

}

int main(void) {
	unsigned int b =5;
	CTWL *nieco;
	srand(time(0));
	//nieco = ctwl_create_empty();
    //nieco->cur = ctwl_insert_left(nieco, 5);
    nieco = ctwl_create_random(b);
    ctwl_print(nieco);
	
	//ieco = ctwl_create_random(b);
}

