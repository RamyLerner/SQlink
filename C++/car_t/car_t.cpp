#include "car_t.h"

int Car_t::idPool = 0;

Car_t() : id(idPool++){
    
};
Car_t(unsigned int cap)