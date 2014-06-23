
#include <UnitTest++.h>
#include "cutils.h"

class AllocatorTestFixture
{
public:
    AllocatorTestFixture()
    {
    }

    virtual ~AllocatorTestFixture()
    {
    }
};

/**
 * Test basic memory creation.
 */
TEST_FIXTURE(AllocatorTestFixture, TestCreate_RefCountShouldBeZero)
{
    CUAllocator *allocator = cu_default_allocator();
    void *memory = cu_allocator_alloc(allocator, 256, 1);
    CHECK(cu_allocator_refcount(allocator, memory) == 1);
    cu_allocator_dealloc(allocator, memory);
}

/**
 * Inc refs
 */
TEST_FIXTURE(AllocatorTestFixture, TestIncRef)
{
    CUAllocator *allocator = cu_default_allocator();
    void *memory = cu_allocator_alloc(allocator, 256, 1);
    cu_allocator_incref(allocator, memory);
    cu_allocator_incref(allocator, memory);
    cu_allocator_incref(allocator, memory);
    CHECK(cu_allocator_refcount(allocator, memory) == 4);
    cu_allocator_dealloc(allocator, memory);
}

/**
 * Test dec refs.
 */
TEST_FIXTURE(AllocatorTestFixture, TestDecRef)
{
    CUAllocator *allocator = cu_default_allocator();
    void *memory = cu_allocator_alloc(allocator, 256, 1);
    cu_allocator_incref(allocator, memory);
    cu_allocator_incref(allocator, memory);
    cu_allocator_incref(allocator, memory);
    CHECK(cu_allocator_decref(allocator, memory) == 3);
    CHECK(cu_allocator_decref(allocator, memory) == 2);
    CHECK(cu_allocator_decref(allocator, memory) == 1);
    CHECK(cu_allocator_refcount(allocator, memory) == 1);
    CHECK(cu_allocator_decref(allocator, memory) == 0);
}

