#include "car_t.h"

int Car_t::idPool = 0;

Car_t:: Car_t(const Car_t& car) : id(idPool){
    name = car.name;
    capacity = car.capacity;
    gear = car.gear;
}