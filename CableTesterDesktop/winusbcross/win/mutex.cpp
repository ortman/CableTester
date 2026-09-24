#ifdef _WIN32

#include "../mutex.h"

#include <windows.h>

/* Блокировка инициализируется статически и живёт всё время работы процесса.
   Раньше она создавалась заново в каждом smc3_connect: это теряло предыдущий
   HANDLE, а вызовы до первого подключения работали с NULL, то есть вообще без
   синхронизации. */
static SRWLOCK hLock = SRWLOCK_INIT;

/* Оставлены для совместимости с существующими вызовами. Блокировке не нужны
   ни инициализация, ни освобождение. */
void mutex_init(void) {
}

void mutex_lock(void) {
  AcquireSRWLockExclusive(&hLock);
}

void mutex_unlock(void) {
  ReleaseSRWLockExclusive(&hLock);
}

void mutex_deinit(void) {
}

#endif