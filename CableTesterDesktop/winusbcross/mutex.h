#ifndef MUTEX_H
#define MUTEX_H

#ifdef __cplusplus
extern "C" {
#endif

void mutex_init(void);
void mutex_lock(void);
void mutex_unlock(void);
void mutex_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // MUTEX_H
