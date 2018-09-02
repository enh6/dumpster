#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <string.h>

#define QUEUE_INITIAL_CAP 8

typedef struct _QueueRecord {
  int capacity;
  int front;
  int rear;
  queue_element_t *array;
} * Queue;

Queue queue_create() {
  Queue q = malloc(sizeof(struct _QueueRecord));
  q->capacity = QUEUE_INITIAL_CAP;
  q->front = 0;
  q->rear = 0;
  q->array = malloc(sizeof(queue_element_t) * q->capacity);
  return q;
}

void queue_destroy(Queue q) {
  if (!q)
    return;
  free(q->array);
  free(q);
}

void queue_enqueue(Queue q, queue_element_t e) {
  q->array[q->rear++] = e;
  if (q->rear >= q->capacity)
    q->rear -= q->capacity;
  if (q->rear == q->front) { // queue is full, increase capacity
    int first_half_size = q->capacity - q->front;
    q->rear = q->capacity;
    q->capacity *= 2;
    queue_element_t *new_array = malloc(sizeof(queue_element_t) * q->capacity);
    memcpy(new_array, &(q->array[q->front]),
           sizeof(queue_element_t) * first_half_size);
    memcpy(new_array + first_half_size, q->array,
           sizeof(queue_element_t) * q->front);
    free(q->array);
    q->array = new_array;
    q->front = 0;
  }
}

queue_element_t queue_dequeue(Queue q) {
  if (q->front == q->rear)
    exit(1);
  queue_element_t e = q->array[q->front++];
  if (q->front >= q->capacity)
    q->front -= q->capacity;
  return e;
}

int queue_empty(Queue q) { return q->front == q->rear; }

#endif
