#include <gtest/gtest.h>
#include <vector>

#include "my_shared_ptr.h"

TEST(shared_ptr_suite, dft_ctr) {
    SharedPtr<int> ptr{};
    ASSERT_FALSE(ptr);
}

TEST(shared_ptr_suite, ctr_raw_ptr) {
    SharedPtr<int> ptr{new int{69}};
    ASSERT_TRUE(ptr);
    ASSERT_EQ(*ptr, 69);
}

TEST(shared_ptr_suite, ctr_var_args) {
}
