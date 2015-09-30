/*
 * semrelay.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>

#include "semrelay.h"
#include "statistics.h"
#include "multilock.h"
#include "utils.h"

void *semrelay_worker(void *ptr) {
    unsigned long i, j;
    struct experiment *exp = ptr;

    for (i = 0; i < exp->outer; i++) {
        // TODO: attendre notre tour
        for (j = 0; j < exp->inner; j++) {
            unsigned long idx = (i * exp->inner) + j;
            statistics_add_sample(exp->data, (double) idx);
        }
        // TODO: signaler le travailleur suivant
    }
    return NULL;
}

void semrelay_init(struct experiment *exp) {
    int i;

    exp->data = make_statistics();
    // TODO: allocation d'un tableau de sémaphores sem_t dans exp->lock
    // TODO: initialisation des sémaphores
}

void semrelay_done(struct experiment *exp) {
    int i;

    // copie finale dans exp->stats
    statistics_copy(exp->stats, exp->data);
    free(exp->data);

    // TODO: destruction du verrou
    // TODO: liberation de la memoire du verrou
}

