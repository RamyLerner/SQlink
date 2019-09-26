#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;


class Car_t{
    public:
        inline Car_t();
        inline Car_t(unsigned int cap);
        Car_t (const Car_t& car);
        Car_t& operator= (const Car_t& car);
        inline int getCapacity();
        inline string getName();
        inline string getGear();
        bool compare(Car_t& car);

        bool operator< (Car_t& car);

    protected:
        ~Car_t(){}
        inline void setCapacity(int cap);
        inline void setName(string name);
        inline void setGear(string gear);

    private:
        unsigned int capacity;
        string name;
        const int id;
        string gear;

        static int idPool;
};

Car_t::Car_t() : id(idPool++) {}
Car_t::Car_t(unsigned int cap) : id(idPool++), capacity(cap) {}

int Car_t::getCapacity(){ return capacity;}
string Car_t::getName(){ return name;}
string Car_t::getGear(){ return gear;}
void Car_t::setCapacity(int cap){ capacity = cap;}
void Car_t::setName(string name){ name = name;}
void Car_t::setGear(string gear){ gear = gear;}


#endif