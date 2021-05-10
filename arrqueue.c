#include "arrqueue.h" 

arrqueue* newqueue() {
	arrqueue *queue;
	queue = (arrqueue *)malloc(sizeof(arrqueue));
	queue->arr = (DTYPE *)malloc(DEFAULT * sizeof(DTYPE));
	queue->currsize = DEFAULT;
	queue->numnodes = 0;
	queue->headpos = 0;
	queue->tailpos = 0;

	return queue;
}

void enqueue(arrqueue *queue, DTYPE elem) {
	if(queue->numnodes > 0) {
		if(queue->numnodes >= queue->currsize - 1) {
			DTYPE *new_arr = (DTYPE *)malloc((queue->currsize + INC) * sizeof(DTYPE));
			int i;
			for(i = 0; i < queue->currsize; i++)
				new_arr[i] = queue->arr[i];
			queue->arr = new_arr;
			queue->currsize += INC;
		}
		queue->tailpos = (queue->tailpos + 1) % queue->currsize;
		queue->arr[queue->tailpos] = elem;
	}
	else {
		queue->arr[0] = elem;
		queue->headpos = 0;
		queue->tailpos = 0;
	}

	queue->numnodes++;
}

DTYPE dequeue(arrqueue *queue) {
	assert(queue->numnodes > 0);
	int headpos = queue->headpos;
	queue->numnodes--;
	if(queue->numnodes == 0) {
		queue->headpos = 0;
		queue->tailpos = 0;
	}
	else {
		queue->headpos = (queue->headpos + 1) % queue->currsize;
	}
	return queue->arr[headpos];
}

DTYPE head(arrqueue *queue) {
	assert(queue->numnodes > 0);
	return queue->arr[queue->headpos];
}

int queue_length(arrqueue *queue) {
	return queue->numnodes;
}

bool is_empty(arrqueue *queue) {
	return (queue->numnodes == 0);
}
