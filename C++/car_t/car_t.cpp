#include "car_t.h"

int Car_t::idPool = 0;

Car_t:: Car_t(const Car_t& car) : id(idPool){
    capacity = car.capacity;
}

Car_t& operator= (const Car_t& car){
    if (this != &car){
        capacity = car.capacity;
    }
}