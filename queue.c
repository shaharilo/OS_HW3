#ifndef QUEUE_C
#define QUEUE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include "queue.h"


// Initialize queue
void initQueue(Queue* q1) {
    q1->head = NULL;
    q1->tail = NULL;
    q1->num_of_elements = 0;
}


// insert node
void insertToQueue(Queue *q1, int new_elem, struct timeval clock) {
    Node *new_node = malloc(sizeof(Node));
    new_node->fd = new_elem;
    new_node->time = clock;
    new_node->next = NULL;

    if (q1->num_of_elements == 0)
    {
        q1->tail = new_node;
        q1->head = new_node;
    }
    else
    {
        q1->tail->next = new_node;
        q1->tail = q1->tail->next;
    }
    q1->num_of_elements ++;

}


// Remove node from head
int removeHeadFromQueue(Queue *q1) {
    int to_return;
    if (q1->head == NULL) {
        // queue is empty
        return -1;
    }
    Node *temp = q1->head;
    to_return = temp->fd;
    q1->head = temp->next;
  
    if (q1->head == NULL) {
        // after remove queue should be empty
        q1->tail = NULL;
    }
    free(temp);
    q1->num_of_elements--;
    temp = NULL;
    return to_return;
}


// Remove node from tail
int removeTailFromQueue(Queue *q1) {
    int to_return;
    if (q1->tail == NULL) {
        // queue is empty
        return -1;
    }
    Node *temp = q1->head;
    while (temp->next != q1->tail)
    {
        temp = temp->next;
    }
    to_return = temp->next->fd;
    Node *to_delete = temp->next;
    free(to_delete);
    temp->next = NULL;
    q1->tail = temp;
    q1->num_of_elements--;
    return to_return;
}



int removeRandom(Queue *q1) 
{
	int to_return;
    if (q1->head == NULL) {
        // queue is empty
        return -1;
    }
    int random_num = rand() % (q1->num_of_elements);
    if (0 == random_num)
    {
        return removeHeadFromQueue(q1);
    }
    if (q1->num_of_elements -1  == random_num)
    {
        return removeTailFromQueue(q1);
    }
    Node *temp = q1->head;
    Node *prev = NULL;
    for (int i = 0; i < random_num-1 ; ++i) {
        temp = temp->next;
    }
    to_return = temp->next->fd;
    prev = temp;
    temp = temp->next;
    prev->next = prev->next->next;
    free(temp);
    q1->num_of_elements--;
    return to_return;
}



// display
void display(Queue *q1) {
    Node *temp = q1->head;
    printf("***   Display function:  ***\n");
    while (temp != NULL) {
        printf(" fd is: %d\n", temp->fd);
        printf(" time of request is: %lu.%06lu\r\n", (temp->time).tv_sec,(temp->time).tv_sec);
        temp = temp->next;
    }
    printf("\n num of elelm is :%d \n", q1->num_of_elements);
    printf("***   END display:  ***\n");

}


void deleteQueue(Queue *q1) {
    Node *temp = q1->head;
    while (temp != NULL) {
        Node *curr = temp;
        temp = temp->next;
        free(curr);
    }
    q1->head = NULL;
    q1->tail = NULL;
    q1->num_of_elements = 0;
}


void enqueue(Queue *q1, int new_elem, struct timeval clock) {
    //pthread_mutex_lock(&m);
    //add x to tail
    insertToQueue(q1,new_elem, clock);
    //pthread_cond_signal(&c);
    //pthread_mutex_unlock(&m);
}

int dequeueHead(Queue *q1) {
    int to_return;
    //pthread_mutex_lock(&m);
    
    /*while (q1->num_of_elements == 0) {
		//printf("--------inside dequeue while----------\n");
        pthread_cond_wait(&c, &m);
    }*/
    
    //printf("--------before remove from queue----------\n");
    to_return = removeHeadFromQueue(q1);
    return to_return;
}




int dequeueTail(Queue *q1) {
    int to_return;
    //pthread_mutex_lock(&m);
    while (q1->num_of_elements == 0) {
        pthread_cond_wait(&c, &m);
    }
    to_return = removeTailFromQueue(q1);
    //pthread_mutex_unlock(&m);
    return  to_return;
}


int dequeueRandom(Queue *q1) {
   int to_return;
    //pthread_mutex_lock(&m);
    while (q1->num_of_elements == 0) {
        pthread_cond_wait(&c, &m);
    }
    to_return = removeRandom(q1);
    
    //pthread_mutex_unlock(&m);
    return  to_return;
}


//int main() {
//
//    return 0;
//}


#endif
