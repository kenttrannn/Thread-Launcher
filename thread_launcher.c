// Kent Tran

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int result;
} thread_data;

static void *worker(void *arg)
{
    thread_data *data = arg;

    printf("[thread %d] started\n", data->id);
    data->result = data->id * data->id;
    return NULL;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    long count = 0;
    int i, created = 0, failed = 0;

    if (argc == 2)
    {
        count = strtol(argv[1], &end, 10);
    }
    
    if (argc != 2 || *argv[1] == '\0' || *end != '\0' || count < 1 || count > 100)
    {
        fprintf(stderr, "Usage %s <thread_count> (integer from 1 to 100)\n", argv[0]);
        return EXIT_FAILURE;
    }

    pthread_t *threads = malloc(count * sizeof(pthread_t));
    thread_data *data = malloc(count * sizeof(thread_data));
    if (threads == NULL || data == NULL)
    {
        fprintf(stderr, "Error: out of memory\n");
        free(threads);
        free(data);
        return EXIT_FAILURE;
    }

    printf("[main] creating %ld threads\n", count);

    for (i = 0; i < count; i++)
    {
        data[i].id = i + 1;

        if (pthread_create(&threads[i], NULL, worker, &data[i]) != 0)
        {
            fprintf(stderr, "Error: pthread_create failed for thread %d\n", i + 1);
            failed = 1;
            break;
        }
        created++;
    }

    for (i = 0; i < created; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "Error: pthread_join failed for thread %d\n", i + 1);
            failed = 1;
        }
    }

    if (!failed)
    {
        for (i = 0; i < count; i++)
        {
            printf("[main] thread %d result: %d\n", data[i].id, data[i].result);
        }
        printf("[main] completed successfully\n");
    }

    free(threads);
    free(data);
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}