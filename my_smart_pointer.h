//
// Created by micha-grzebielec on 13.12.2025.
//

#ifndef TEP_5_MY_SMART_POINTER_H
#define TEP_5_MY_SMART_POINTER_H

#include "ref_counter.h"

template<typename T>
class my_smart_pointer {
public:
    explicit my_smart_pointer(T *ptr) {
        this->ptr = ptr;
        counter = new ref_counter();
        counter->add();
    }

    my_smart_pointer(const my_smart_pointer &other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        counter->add();
    }

    my_smart_pointer(my_smart_pointer &&other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        other.ptr = NULL;
        other.counter = NULL;
    }

    ~my_smart_pointer() {
        if (counter != NULL) {
            //std::cout << "nanana jestem smart pointer i znikam ze stosu" << std::endl;
            counter->dec();
            if (counter->get() == 0) {
                //std::cout << "oraz usuwam: " << *ptr << std::endl;
                delete ptr;
                delete counter;
            }
        } // else std::cout << "jestem pusty po przeniesieniu i znikam" << std::endl;
    }

    T& operator*() {
        return(*ptr);
    }

    T* operator->() {
        return ptr;
    }

    my_smart_pointer& operator=(const my_smart_pointer &other) {
        if (this == other) return *this;

        if (this->ptr != NULL) {
            counter->dec();
            if (counter->get() == 0) {
                delete ptr;
                delete counter;
            }
        }

        this = my_smart_pointer(other);
        return *this;
    }

    my_smart_pointer& operator=(my_smart_pointer &&other) {
        if (this == &other) return *this;

        if (this->ptr != NULL) {
            counter->dec();
            if (counter->get() == 0) {
                delete ptr;
                delete counter;
            }
        }

        this->ptr = other.ptr;
        this->counter = other.counter;
        other.ptr = NULL;
        other.counter = NULL;
        return *this;
    }
private:
    T *ptr;
    ref_counter *counter;
};

#endif //TEP_5_MY_SMART_POINTER_H