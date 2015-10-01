/*
 * mutex.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "statistics.h"
#include "multilock.h"

#include "utils.h"

void *mutex_worker(void *ptr) {
    unsigned long i, j, inner;
    struct experiment *exp = ptr;

    for (i = 0; i < exp->outer; i++) {
        // TODO: verrouiller
		pthread_mutex_lock(&exp->lock);
        for (j = 0; j < exp->inner; j++) {
            unsigned long idx = (i * exp->inner) + j;
            statistics_add_sample(exp->data, (double) idx);
        }
        // TODO deverrouiller
		pthread_mutex_unlock(&exp->lock);
    }
    return NULL;
}

void mutex_init(struct experiment *exp) {
    exp->data = make_statistics();
    // TODO: allocation d'un pthread_mutex_t dans exp->lock
	exp->lock = calloc(sizeof(pthread_mutex_t));
    // TODO: initialisation du mutex
	pthread_mutex_init(&exp->lock, NULL);
}

void mutex_done(struct experiment *exp) {
    statistics_copy(exp->stats, exp->data);
    free(exp->data);
    // TODO: destruction du verrou
	pthread_mutex_destroy(&exp->lock);
    // TODO: liberation de la memoire du verrou
	free(exp->lock);
}


