#pragma once

#include <cassert>
#include <utility>

template <typename T>
class SharedPtr {
public:
    constexpr SharedPtr() noexcept = default;

    constexpr SharedPtr(std::nullptr_t) noexcept
    : data_{nullptr}
    , count_{nullptr}
    {}

    explicit SharedPtr(T *raw_data) noexcept //todo test throw?
    try
    : data_{raw_data}
    , count_{new int64_t{raw_data ? 1 : 0}}
    {}
    catch (...) {
        delete data_;
    }

    SharedPtr(const SharedPtr& other)
    : data_(other.data_)
    , count_(other.count_) {
        if (count_) {
            ++*count_;
        }
    }

    SharedPtr &operator=(T* raw_ptr) { //todo test it
        SharedPtr tmp{raw_ptr};
        swap(tmp);
        return *this;
    }

    SharedPtr &operator=(const SharedPtr& other) {
        if (this == &other) {
            return *this;
        }

        SharedPtr copy{other};
        swap(copy);
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept {
        if (!other.count_) {
            return;
        }
        swap(other);
    }

    SharedPtr &operator=(SharedPtr&& other) {
        if (this == &other) {
            return *this;
        }
        SharedPtr tmp{std::move(other)};
        swap(tmp);
    }

    ~SharedPtr() {
        if (!count_)
            return;

        if (*count_ > 0) {
            --*count_;
        }
        
        if (*count_ == 0u) {
            if (data_)
                delete data_;
            delete count_;
        }
    }

    int64_t use_count() const noexcept {
        return count_ ? *count_ : 0u;
    }

    operator bool() const noexcept {
        return data_ != nullptr;
    }

    T* get() const noexcept {
        return data_;
    }

    T& operator*() const noexcept {
        assert(data_ != nullptr);
        return *data_;
    }

    T* operator->() const noexcept {
        return data_;
    }

    void swap(SharedPtr& other) noexcept {
        std::swap(count_, other.count_);
        std::swap(data_, other.data_);
    }

    void reset() noexcept {
        SharedPtr<T>{}.swap(*this);
    }

private:
    int64_t *count_ = nullptr;
    T *data_ = nullptr;
};
