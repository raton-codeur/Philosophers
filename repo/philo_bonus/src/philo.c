/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhauuy <qhauuy@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:51:56 by qhauuy            #+#    #+#             */
/*   Updated: 2024/08/23 14:38:06 by qhauuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h> // Pour O_CREAT, O_EXCL
#include <sys/types.h>
#include <sys/wait.h> // Pour wait()
#include <unistd.h> // Pour fork()

#define SEM_NAME "/mon_semaphore"

void critical_section(int process_id) {
    printf("Processus %d est dans la section critique\n", process_id);
    sleep(1);  // Simule une section critique avec un délai
    printf("Processus %d quitte la section critique\n", process_id);
}

int main() {
    sem_t *sem;

    // Crée un sémaphore nommé avec une valeur initiale de 1
    sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Crée deux processus enfants
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Premier enfant
        printf("Premier enfant lancé (PID %d)\n", getpid());

        // Attente du sémaphore
        sem_wait(sem);

        // Section critique
        critical_section(getpid());

        // Libère le sémaphore
        sem_post(sem);

        exit(0);  // Fin du premier enfant
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Deuxième enfant
        printf("Deuxième enfant lancé (PID %d)\n", getpid());

        // Attente du sémaphore
        sem_wait(sem);

        // Section critique
        critical_section(getpid());

        // Libère le sémaphore
        sem_post(sem);

        exit(0);  // Fin du deuxième enfant
    }

    // Attendre la fin des deux enfants
    wait(NULL);
    wait(NULL);

    // Ferme et supprime le sémaphore
    sem_close(sem);
    sem_unlink(SEM_NAME);

    printf("Parent : Les enfants ont terminé.\n");
    return 0;
}
