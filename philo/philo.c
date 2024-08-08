#include "philo.h"

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);
    free(arg);

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        usleep(rand() % 5);

        printf("Philosopher %d is hungry...\n", id);

        // Try to pick up left fork
        pthread_mutex_lock(&forks[id]);

        // Try to pick up right fork
        if (pthread_mutex_trylock(&forks[(id + 1) % NUM_PHILOSOPHERS]) != 0) {
            // Could not acquire right fork, put down left fork and try again
            pthread_mutex_unlock(&forks[id]);
            continue;
        }

        printf("Philosopher %d is eating...\n", id);
        usleep(rand() % 5);

        // Put down right fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Put down left fork
        pthread_mutex_unlock(&forks[id]);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    t_times philo_time;
    if (argc != 4 && argc != 5)
    {
        printf("The number of arguments must be either 3 or 4.\n");
        return (1);
    }
    if (get_inpt(&philo_time, argv))
        return (1);
    printf("nif; %d\n", philo_time.number_of_philosophers);
    printf("ttd: %d\n", philo_time.time_to_die);
    printf("tte: %d\n", philo_time.time_to_eat);
    printf("xx: %d\n", philo_time.number_of_times_epme);
    return (0);
    pthread_t threads[NUM_PHILOSOPHERS];
    int* ids[NUM_PHILOSOPHERS];

    // Initialize forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}