#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "darknet.h"

list *make_list()
{
	struct list *l = (struct list *) malloc(sizeof(struct list));
	l->size = 0;
	l->front = 0;
	l->back = 0;
	return l;
}

/*
void transfer_node(list *s, list *d, node *n)
{
    node *prev, *next;
    prev = n->prev;
    next = n->next;
    if(prev) prev->next = next;
    if(next) next->prev = prev;
    --s->size;
    if(s->front == n) s->front = next;
    if(s->back == n) s->back = prev;
}
*/

void *list_pop(list *l){
    if(!l->back) return 0;
    node *b = l->back;
    void *val = b->val;
    l->back = b->prev;
    if(l->back) l->back->next = 0;
    free(b);
    --l->size;

    return val;
}

void list_insert(list *l, void *val)
{
	struct node *new1 = (struct node *) malloc(sizeof(struct node));
	new1->val = val;
	new1->next = 0;

	if(!l->back){
		l->front = new1;
		new1->prev = 0;
	}else{
		l->back->next = new1;
		new1->prev = l->back;
	}
	l->back = new1;
	++l->size;
}

void free_node(node *n)
{
	struct node *next;
	while(n) {
		next = n->next;
		free(n);
		n = next;
	}
}

void free_list(list *l)
{
	free_node(l->front);
	free(l);
}

void free_list_contents(list *l)
{
	struct node *n = l->front;
	while(n){
		free(n->val);
		n = n->next;
	}
}

void **list_to_array(list *l)
{
    void **a = (void **) calloc(l->size, sizeof(void*));
    int count = 0;
    struct  node *n = l->front;
    while(n){
        a[count++] = n->val;
        n = n->next;
    }
    return a;
}
