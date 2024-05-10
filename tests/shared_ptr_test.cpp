#include <gtest/gtest.h>
#include <vector>

#include "my_shared_ptr.h"

TEST(shared_ptr_suite, dft_ctr) {
    SharedPtr<int> ptr{};
    ASSERT_FALSE(ptr);
    ASSERT_EQ(ptr.use_count(), 0);
}

TEST(shared_ptr_suite, ctr_nullptr) {
    SharedPtr<int> ptr{nullptr};
    ASSERT_FALSE(ptr);
    ASSERT_EQ(ptr.use_count(), 0);
}

TEST(shared_ptr_suite, ctr_direct_raw_ptr) {
    SharedPtr<int> ptr{new int{69}};
    ASSERT_TRUE(ptr);
    ASSERT_EQ(*ptr, 69);
    ASSERT_EQ(ptr.use_count(), 1);
}

TEST(shared_ptr_suite, ctr_raw_ptr_null) {
    int *raw_ptr = nullptr;
    SharedPtr<int> ptr{raw_ptr};
    ASSERT_FALSE(ptr);
    ASSERT_EQ(ptr.use_count(), 0);
}

TEST(shared_ptr_suite, ctr_raw_ptr_non_null) {
    int *raw_ptr = new int{69};
    SharedPtr<int> ptr{raw_ptr};
    ASSERT_TRUE(ptr);
    ASSERT_EQ(*ptr, 69);
    ASSERT_EQ(ptr.use_count(), 1);
}
