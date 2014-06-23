

#include <UnitTest++.h>
#include "cutils.h"

class ArrayTestFixture
{
public:
    ArrayTestFixture()
    {
    }

    virtual ~ArrayTestFixture()
    {
    }
};

/**
 * Test basic memory creation.
 */
TEST_FIXTURE(ArrayTestFixture, TestCreate)
{
    CUArray *array = cu_array_with_capacity(0);
    CHECK(cu_collection_size(array) == 0);
}

/**
 * Insertions
 */
TEST_FIXTURE(ArrayTestFixture, TestAdd)
{
    CUArray *array = cu_array_with_capacity(0);
    CUString *str = cu_string("hello world");
    cu_collection_add(array, str);
    CHECK(cu_collection_size(array) == 1);
}

/**
 * Insertions at index
 */
TEST_FIXTURE(ArrayTestFixture, TestAddAtIndex)
{
    CUArray *array = cu_array_with_capacity(0);
    CUString *str = cu_string("hello");
    CUString *str2 = cu_string("world");
    cu_collection_add(array, str);
    cu_list_add_item_at(array, str2, 0);
    CHECK(cu_collection_size(array) == 2);
    CHECK(cu_equals(cu_list_get_item_at(array, 0), str2));
    CHECK(cu_equals(cu_list_get_item_at(array, 1), str));
}

