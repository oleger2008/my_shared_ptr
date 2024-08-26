#include <gtest/gtest.h>
#include <vector>

#include "my_shared_ptr.h"

TEST(shared_ptr_suite, dft_ctr) {
    SharedPtr<int> ptr{};
    ASSERT_FALSE(ptr);
    ASSERT_EQ(ptr.use_count(), 0);
}

TEST(shared_ptr_suite, reset) {
    SharedPtr<int> alpha(new int{69});
    alpha.reset();
    ASSERT_FALSE(alpha);
    ASSERT_EQ(alpha.use_count(), 0);
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

TEST(shared_ptr_suite, copy_ctr_not_null) {
    SharedPtr<int> ptr(new int{69});
    SharedPtr<int> ptr_copy{ptr};

    ASSERT_EQ(ptr.use_count(), 2);
    ASSERT_TRUE(ptr_copy);
    ASSERT_EQ(*ptr_copy, 69);
}

TEST(shared_ptr_suite, copy_ctr_null) {
    SharedPtr<int> ptr(nullptr);
    SharedPtr<int> ptr_copy{ptr};

    ASSERT_EQ(ptr.use_count(), 0);
    ASSERT_EQ(ptr_copy.use_count(), 0);
    ASSERT_FALSE(ptr_copy);
}

TEST(shared_ptr_suite, copy_ctr_scoped_copy) {
    SharedPtr<int> ptr(new int{69});
    {
        SharedPtr<int> ptr_copy{ptr};

        ASSERT_EQ(ptr.use_count(), 2);
        ASSERT_TRUE(ptr_copy);
        ASSERT_EQ(*ptr_copy, 69);
    }
    ASSERT_EQ(ptr.use_count(), 1);
}

TEST(shared_ptr_suite, copy_assign) {
    SharedPtr<int> ptr(new int{69});
    SharedPtr<int> ptr_copy = ptr;

    ASSERT_EQ(ptr.use_count(), 2);
    ASSERT_TRUE(ptr_copy);
    ASSERT_EQ(*ptr_copy, 69);
}

TEST(shared_ptr_suite, copy_assign_null) {
    SharedPtr<int> ptr(nullptr);
    SharedPtr<int> ptr_copy = ptr;

    ASSERT_EQ(ptr.use_count(), 0);
    ASSERT_EQ(ptr_copy.use_count(), 0);
    ASSERT_FALSE(ptr_copy);
}

TEST(shared_ptr_suite, copy_assign_scoped) {
    SharedPtr<int> ptr(new int{69});
    {
        SharedPtr<int> ptr_copy = ptr;

        ASSERT_EQ(ptr.use_count(), 2);
        ASSERT_TRUE(ptr_copy);
        ASSERT_EQ(*ptr_copy, 69);
    }
    ASSERT_EQ(ptr.use_count(), 1);
}

TEST(shared_ptr_suite, copy_reassign) {
    SharedPtr<int> alpha(new int{69});
    SharedPtr<int> betta(new int{142});
    {
        SharedPtr<int> delta(betta);
        ASSERT_TRUE(delta);
        ASSERT_EQ(alpha.use_count(), 1);
        ASSERT_EQ(betta.use_count(), 2);
        ASSERT_EQ(*delta, 142);

        delta = alpha;
        ASSERT_TRUE(delta);
        ASSERT_EQ(alpha.use_count(), 2);
        ASSERT_EQ(betta.use_count(), 1);
        ASSERT_EQ(*delta, 69);
    }
    ASSERT_EQ(alpha.use_count(), 1);
    ASSERT_EQ(betta.use_count(), 1);
}

//todo move assign and ctr tests