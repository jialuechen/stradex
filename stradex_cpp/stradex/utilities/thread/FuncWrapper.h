

#pragma once
#ifndef stradex_UTILITIES_THREAD_FUNCWRAPPER_H
#define stradex_UTILITIES_THREAD_FUNCWRAPPER_H

#include <memory>
#include <functional>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4521)
#endif

namespace stradex {


class FuncWrapper {
public:
    FuncWrapper() = default;
    FuncWrapper(const FuncWrapper&) = delete;
    FuncWrapper(FuncWrapper&) = delete;
    FuncWrapper& operator=(const FuncWrapper&) = delete;

    template <typename F>
    FuncWrapper(F&& f)  
    : impl(new impl_type<F>(std::move(f))) {}

    void operator()() {
        if (impl) {
            impl->call();
        }
    }

    FuncWrapper(FuncWrapper&& other) : impl(std::move(other.impl)) {}

    /** 移动复制函数 */
    FuncWrapper& operator=(FuncWrapper&& other) {
        impl = std::move(other.impl);
        return *this;
    }

    bool isNullTask() const {
        return impl ? false : true;
    }

private:
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    std::unique_ptr<impl_base> impl;

    template <typename F>
    struct impl_type : impl_base {
        F f;
        impl_type(F&& f_) : f(std::move(f_)) {}
        void call() {
            f();
        }
    };
};

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
