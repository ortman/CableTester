#ifdef __linux__

#include "../mutex.h"

#include <pthread.h>

/* Блокировка инициализируется статически и живёт всё время работы процесса.
   Раньше pthread_mutex_init вызывался заново в каждом smc3_connect, что для
   уже инициализированного (и, возможно, захваченного) мьютекса является
   неопределённым поведением. */
static pthread_mutex_t hMutex = PTHREAD_MUTEX_INITIALIZER;

/* Оставлены для совместимости с существующими вызовами. Блокировке не нужны
   ни инициализация, ни освобождение. */
void mutex_init(void) {
}

void mutex_lock(void) {
    pthread_mutex_lock(&hMutex);
}

void mutex_unlock(void) {
    pthread_mutex_unlock(&hMutex);
}

void mutex_deinit(void) {
}

#endif