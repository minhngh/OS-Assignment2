#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void swap(struct pcb_t** a, struct pcb_t ** b){
	struct pcb_t* temp = *a;
	*a = *b;
	*b = temp;
}

void heap_up(struct pcb_t** proc, int size){
	if (size){
		int parent = (size - 1) / 2;
		if (proc[size]->priority > proc[parent]->priority){
			swap(proc + size, proc + parent);
			heap_up(proc, parent);
		}
	}
}

void heap_down(struct pcb_t** proc, int pos, int size){
	int l = 2 * pos + 1;
	int r = 2 * pos + 2;
	int child;
	if (r < size && proc[r]->priority > proc[l]->priority){
		child = r;
	}
	else if (l < size){
		child = l;
	}
	else{
		return;
	}
	if (proc[pos]->priority < proc[child]->priority){
		swap(proc + pos, proc + child);
		heap_down(proc, child, size);
	}
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */	
	if (proc == NULL){
		return;
	}
	q->proc[q->size] = proc;
	heap_up(q->proc, q->size);
	q->size++;
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if (empty(q)){
		return NULL;
	}
	struct pcb_t* top = q->proc[0];
	--q->size;
	swap(q->proc, q->proc + q->size);
	heap_down(q->proc, 0, q->size);
	return top;
}

