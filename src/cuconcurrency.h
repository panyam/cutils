
#ifndef __CUTILS_CONCURRENCY_H__
#define __CUTILS_CONCURRENCY_H__

#include "cufwddefs.h"
#if defined(_cplusplus) || defined(__cplusplus)
extern "C" {
#endif

struct CULock
{
    void (*lock)(CULock *lock);
    void (*unlock)(CULock *lock);
};

struct CUSemaphore
{
    void (*increment)(CUSemaphore *semaphore);
    void (*decrement)(CUSemaphore *semaphore);
};

struct CUCondition
{
    void (*wait)(CUCondition *condition);
    void (*signal)(CUCondition *condition);
};

extern void cu_lock_lock(CULock *lock);
extern void cu_lock_unlock(CULock *lock);

extern void cu_semaphore_inc(CUSemaphore *semaphore);
extern void cu_semaphore_dec(CUSemaphore *semaphore);

extern void cu_condition_wait(CUCondition *condition);
extern void cu_condition_signal(CUCondition *condition);

#if defined(_cplusplus) || defined(__cplusplus)
}
#endif

#endif

