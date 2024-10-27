#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>

template <typename T>
class Singleton {
  public:
    template <typename... Args>
    static T& Instance(Args&&... args) {
        static_assert(!std::is_move_constructible<T>::value, "T cannot be move constructible");
        static_assert(!std::is_copy_constructible<T>::value, "T cannot be copy constructible");
        static_assert(!std::is_default_constructible<T>::value, "T must not have a default constructor");
        static_assert(!std::is_constructible<T, Args&&...>::value, "T must not have a public constructor");
        static_assert(!std::is_destructible<T>::value, "T must not have a public destructor");
        static std::once_flag flag;
        std::call_once(
            flag, [&](Args&&... args) {
                _value.reset(new T(std::forward<Args>(args)...));
            },
            std::forward<Args>(args)...);
        return *_value;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

  private:
    Singleton() = default;
    ~Singleton() = default;
    struct Deleter {
        void operator()(T* ptr) const {
            delete ptr;
        }
    };

    static std::unique_ptr<T, Deleter> _value;
};

template <typename T>
std::unique_ptr<T, typename Singleton<T>::Deleter> Singleton<T>::_value = nullptr;

#endif
