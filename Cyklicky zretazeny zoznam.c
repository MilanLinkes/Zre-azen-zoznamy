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


void ctwl_cur_step_right(CTWL *list){
	list->cur = list->cur->next;
}

void ctwl_cur_step_left(CTWL *list){
	list->cur = list->cur->prev;
}

char ctwl_delete(CTWL* list){
	TWN *kurzor, *dalsi, *predosly;
	char CTWL_OK=1, CTWL_FAIL=-1;
	
	if(list->cur == NULL){
		return CTWL_FAIL;
	}
	
	if(list->cur->next == list->cur && list->cur->prev == list->cur){
		free(list->cur);
		return CTWL_OK;
	}
	
	kurzor = list->cur;
	dalsi = list->cur->next;
	predosly = list->cur->next;
	
	ctwl_cur_step_right(list);
	list->cur->prev = predosly;
	ctwl_cur_step_left(list);
	list->cur->next = dalsi;
	ctwl_cur_step_right(list);
	
	free(kurzor);
	return CTWL_OK;
}

void ctwl_destroy(CTWL* list){
	TWN *kurzor, *predosly;
		
	kurzor = list->cur;
	
	if(kurzor == NULL){
		free(list);
		list->cur = NULL;
	} else {
	
		while(list->cur != kurzor){
			free(list->cur);
			ctwl_cur_step_right(list);
		}
	
		free(list->cur->prev);
		free(list->cur);
		list->cur = NULL;
	}
}

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
		ctwl_cur_step_right(list);
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
		list->cur->prev = novy;
	    novy->next = list->cur;
		novy->prev = flag;
		flag->next = novy;
		ctwl_cur_step_left(list);
		}
			return novy;
}

CTWL *ctwl_create_random(unsigned int size) {
	int i;
	float data;
	CTWL *list;
	
	if(size == 0){
		list = ctwl_create_empty();
		return list;
	}
	
	list = ctwl_create_empty();

	for(i=0; i<size; i++){
		data = rand()%10;
		list->cur = ctwl_insert_right(list, data);
	}
	return list;	
}

void ctwl_print(CTWL *list){
	TWN *prvy;
	
	if(list->cur == NULL){
		printf("List is empty.\n");
	} else {	
		prvy = list->cur;

		printf("cur:%f \n", list->cur->data);
		ctwl_cur_step_right(list);
	
		while(list->cur != prvy){
			printf("%f ", list->cur->data);
			ctwl_cur_step_right(list);
		} 
	}
}

unsigned int ctwl_get_size(CTWL *list){
	TWN *prvy;
	unsigned int size = 0;
	
	if(list->cur == NULL){
		size = 0;
		return size;
	}
	
	prvy = list->cur;
	ctwl_cur_step_right(list);
	size++;
	
	 while(list->cur != prvy){
		size++;
		ctwl_cur_step_right(list);
	}
	return size;
}

int main(void) {
	unsigned int b = 0, size;
	CTWL *nieco;
	srand(time(0));
    
	nieco = ctwl_create_random(b);
	printf("Size of the list is: %d\n",ctwl_get_size(nieco));
	printf("\n");
    ctwl_destroy(nieco);
    ctwl_print(nieco); 
}
