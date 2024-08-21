//
// Created by Geraldo Nascimento on 14/08/2024.
//

#ifndef CPP_LEARNING_ENTITYPOOL_H
#define CPP_LEARNING_ENTITYPOOL_H

#include <vector>
#include <memory>

template <typename T>
class EntityPool {
public:
    std::vector<std::unique_ptr<T>> pool;

    EntityPool(std::size_t size = 100) {
        pool.reserve(size);
        for (std::size_t i = 0; i < size; ++i) {
            pool.push_back(std::make_unique<T>());
        }
    }

    std::shared_ptr<T> acquire() {
        if (!pool.empty()) {
            auto entity = std::move(pool.back());
            pool.pop_back();

            return std::shared_ptr<T>(entity.release(), [this](T* p) {
                release(p);
            });
        } else {
            return std::shared_ptr<T>(new T(), [this](T* p) {
                release(p);
            });
        }
    }

    void release(T* entity) {
        pool.push_back(std::unique_ptr<T>(entity));
    }
};


#endif //CPP_LEARNING_ENTITYPOOL_H
