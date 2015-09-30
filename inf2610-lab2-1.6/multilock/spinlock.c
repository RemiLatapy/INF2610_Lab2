/*
 * spinlock.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "minispinlock.h"
#include "statistics.h"
#include "multilock.h"

/* Spinlock: verrou actif
 *
 * Voir l'implémentation du verrou dans le fichier minispinlock.asm
 * et l'interface dans minispinlock.h
 */
void *spinlock_worker(void *ptr) {
    unsigned long i, j;
    struct experiment *exp = ptr;
    for (i = 0; i < exp->outer; i++) {
        // TODO: verrouiller
        for (j = 0; j < exp->inner; j++) {
            unsigned long idx = (i * exp->inner) + j;
            statistics_add_sample(exp->data, (double) idx);
        }
        // TODO: deverrouiller
    }
    return NULL;
}

void spinlock_init(struct experiment *exp) {
    exp->data = make_statistics();
    // TODO: allocation d'un long dans exp->lock
    // TODO: initialisation à zéro
}

void spinlock_done(struct experiment *exp) {
    statistics_copy(exp->stats, exp->data);
    free(exp->data);
    // TODO: liberation de la memoire du verrou
}

