// Jake Gorski
// CS 370 - Project 3
// This program practices the use of semaphores
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

// Globals

const int DATACNT_MIN = 5;
const int DATACNT_MAX = 20;
const int BUFFER_MIN = 5;
const int BUFFER_MAX = 20;
const int THREAD_CNT = 5;

// Locks | Semaphores

sem_t producerSem;
sem_t consumerSem;
pthread_mutex_t tLock;
unsigned int threadID[5];

// Buffer

int *buffer;
unsigned int bufferSize = 0;
unsigned int bufferCount = 0;
unsigned int maxSize = 0;
unsigned int count, insrt, rmv = 0; // Couldn't get working with one counter :c

// Functions

int commandLine(int argc, char* argv[], unsigned int *maxValue, unsigned int *bufferSize){

    // Argv[0] holds {./proCons}
    // Argv[1] holds "-i"
    // Argv[2] holds {maxValue}
    // Argv[3] holds "-b"
    // Argv[4] holds {sizeValue}

    if(argc != 5){
        printf("Usage: ./prodCons -i |value > 5| -b |value < 20|\n");
        exit(1);
    }

    if(strcmp(argv[1], "-i")){
        printf("Error: Invalid Command Line Arguments\n");
        exit(1);
    }

    if(strcmp(argv[3], "-b")){
        printf("Error: Invalid Command Line Arguments\n");
        exit(1);
    }

    // Count of data items each thread should produce
    *maxValue = atoi(argv[2]);
    if(*maxValue < DATACNT_MIN || *maxValue > DATACNT_MAX){
        printf("Error: Value's must be greater than 5 and less than 20\n");
        exit(1);
    }

    // Buffer Size
    *bufferSize = atoi(argv[4]);
    if(*bufferSize < BUFFER_MIN || *bufferSize > BUFFER_MAX){
        printf("Error: Value's must be greater than 5 and less than 20\n");
        exit(1);
    }

    return -1;
}

void *producer(void *threadID){

    int _threadID = *((int *)threadID);
    int data;
    for(int i = 0; i < maxSize; i++){
        // Produce random data
        usleep(rand() % 2000);
        data = rand();

        sem_wait(&producerSem);
        // Critical Section
        // Insert Data Item into buffer
        pthread_mutex_lock(&tLock);
        buffer[insrt % bufferSize] = data;
        insrt = (insrt + 1) % bufferSize;
        
        //Print in Red
        printf("\033[0;31mProducer %d: Insert Item %d at %d\033[0m\n", _threadID, data, insrt);
        count++;
        pthread_mutex_unlock(&tLock);
        // End Critical Section

        //Wake up Consumer
        sem_post(&consumerSem);
    }

    return 0;
}

void *consumer(void *threadID){
    int _threadID = *((int *)threadID);
    int item;
    for(int i = 0; i < maxSize; i++){
    
        sem_wait(&consumerSem);
        // Critical Section
        // Remove Data Item from buffer
        pthread_mutex_lock(&tLock);
        item = buffer[rmv % bufferSize];
        buffer[rmv % bufferSize] = -1;
        rmv = (rmv + 1) % bufferSize;
       
        //Print in Green
        printf("\033[0;92mConsumer %d: Remove Item %d from %d\033[0m\n", _threadID, item, rmv);
        count--;
        pthread_mutex_unlock(&tLock);
        // End Critical Section

        //Sleep random
        usleep(rand() % 2000);

        //Wake up producer
        sem_post(&producerSem);

    }
    
    return 0;
}

// Main
int main(int argc, char* argv[]){

    // Check command line arugments
    commandLine(argc, argv, &maxSize, &bufferSize);

    // Initalize Semaphores
    unsigned int a = 0;
    sem_init(&producerSem, 0, bufferSize); // 2nd value is shared
    sem_init(&consumerSem, 0, a); // 2nd value is shared

    // Generate Thread ID's
    for(int i = 0; i < bufferCount; i++){
        threadID[i] = '\0';
    }

    // Declare Buffer Memory
    buffer = (int*)malloc(bufferSize * sizeof(unsigned int));
    if(buffer == NULL){
        printf("Error: Out of memory\n");
        exit(1);
    }
 
    // Declare Thread Memory
    pthread_t *pro, *con;
    pro = (pthread_t *)malloc(THREAD_CNT * sizeof(pthread_t));
    con = (pthread_t *)malloc(THREAD_CNT * sizeof(pthread_t));
    if(pro == NULL || con == NULL){
        printf("Error: Out Of Memory\n");
        exit(1);
    }
    
    // Header
    printf("\n");
    printf("\033[0;4mCS 370 Producer-Consumer Project\033[0m\n\n");

    // Start Producers and Consumer Threads
    for(int i = 0; i < THREAD_CNT; i++){
        int *threadID = malloc(sizeof(*threadID));
        *threadID = i;
        pthread_create(&pro[i], NULL, &producer, (void *)threadID);
        pthread_create(&con[i], NULL, &consumer, (void *)threadID);
    }

    // Wait for Threads to Finish
    for(int i = 0; i < THREAD_CNT; i++){
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }
    return 0;
}