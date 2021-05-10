#include "defn.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT 10
#define INC 10

typedef struct {
	DTYPE *arr;
	int numnodes;
	int headpos;
	int tailpos;
	int currsize;
} arrqueue;

arrqueue* newqueue();

void enqueue(arrqueue *queue, DTYPE elem);

DTYPE dequeue(arrqueue *queue);

DTYPE head(arrqueue *queue);

int queue_length(arrqueue *queue);

bool is_empty(arrqueue *queue);
