
#include "cutils.h"

void cu_lock_lock(CULock *lock)
{
    lock->lock(lock);
}

void cu_lock_unlock(CULock *lock)
{
    lock->unlock(lock);
}

void cu_semaphore_inc(CUSemaphore *semaphore)
{
    semaphore->increment(semaphore);
}

void cu_semaphore_dec(CUSemaphore *semaphore)
{
    semaphore->decrement(semaphore);
}

void cu_condition_wait(CUCondition *condition)
{
    condition->wait(condition);
}

void cu_condition_signal(CUCondition *condition)
{
    condition->signal(condition);
}

