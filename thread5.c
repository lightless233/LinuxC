#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World!";
int thread_finished = 0;

int main()
{
    int res;
    pthread_t a_thread;

    pthread_attr_t thread_attr;

    //initialize a thread attribute
    res = pthread_attr_init(&thread_attr);
    if (res != 0)
    {
        perror("Attribute creation failed.");
        exit(EXIT_FAILURE);
    }

    //set attribute to the detached
    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (res != 0)
    {
        perror("setting detached attribute failed");
        exit(EXIT_FAILURE);
    }
    
    //create a thread
    res = pthread_create(&a_thread, &thread_attr, thread_function, (void*)message);
    if (res != 0 )
    {
        perror("Thread create failed.");
        exit(EXIT_FAILURE);
    }

    //destory thread attribute
    (void)pthread_attr_destroy(&thread_attr);
    while (!thread_finished)
    {
        printf("Waitting for thread to say it's finished...\n");
        sleep(1);
    }
    printf("other threads finished. end\n");
    exit(EXIT_SUCCESS);
}


void *thread_function(void *arg)
{
    printf("thread_function is running. Argument was %s", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}

