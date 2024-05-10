#pragma once

#include <cassert>
#include <utility>

template <typename T>
class SharedPtr {
public:
    constexpr SharedPtr() noexcept = default;

    SharedPtr(T *raw_data) {
        data_ = raw_data;
        count_ = new uint64_t{1u};
    }

    ~SharedPtr() {
        if (count_) {
            --count_;
            if (*count_ == 0u) {
                delete count_;
                delete data_;
            }
        }
    }

    operator bool() const noexcept {
        return data_ != nullptr;
    }

    T* get() const noexcept {
        return data_;
    }

    T operator*() const noexcept {
        assert(data_ != nullptr);
        return *data_;
    }

    T* operator->() const noexcept {
        return data_;
    }

private:
    uint64_t *count_ = nullptr;
    T *data_ = nullptr;
};
