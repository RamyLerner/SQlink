#ifndef PRIVATE_H
#define PRIVATE_H

class Private_t : public Car_t{
    public:
        ~Private_t();
        Private_t();
        Private_t(int cap);
        Private_t& operator= (const Private_t& prv);
        Private_t(const Private_t&);

        inline Private_t accelerate();
        inline Private_t reduceSpeed();
        inline int getSpeed();

    private:
        int speed;

};

Private_t& Private_t::accelerate(){ speed += 10; return *this;}
Private_t& Private_t::reduceSpeed(){ speed = speed-10>=0 ? speed-10 : 0; return *this;}
int Private_t::getSpeed(){ return speed;}

#endif