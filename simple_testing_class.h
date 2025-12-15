//
// Created by micha-grzebielec on 14.12.2025.
//

#ifndef TEP_5_SIMPLE_TESTING_CLASS_H
#define TEP_5_SIMPLE_TESTING_CLASS_H

class simple_testing_class {
public:
    simple_testing_class(const int size) {
        this->size = size;
        tab = new int[size];
        for (int i = 0; i < size; i++) tab[i] = i;
    }

    simple_testing_class(const simple_testing_class &other) {
        this->size = other.size;
        this->tab = new int[size];
        for (int i = 0; i < size; i++) {
            this->tab[i] = other.tab[i];
        }
    }

    simple_testing_class(simple_testing_class &&other) noexcept {
        this->size = other.size;
        this->tab = other.tab;
        other.tab = nullptr;

        std::cout << "moved" << std::endl;
    }

    ~simple_testing_class() {
        delete[] tab;
    }

    simple_testing_class& operator=(const simple_testing_class &other) {
        if (this != &other) {
            delete[] tab;
            this->size = other.size;
            this->tab = new int[size];
            for (int i = 0; i < size; i++) {
                this->tab[i] = other.tab[i];
            }
            return *this;
        }
        return *this;
    }
private:
    int *tab;
    int size;
};

#endif //TEP_5_SIMPLE_TESTING_CLASS_H