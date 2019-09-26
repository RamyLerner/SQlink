#ifndef BUS_H
#define BUS_H

class Bus_t{
    public:
        ~Bus_t();
        Bus_t();
        Bus_t(int seats, int line);
        Bus_t(const Bus_t&);
        Bus_t& operator=(const Bus_t& bus);
        
        inline int getLine();
        inline int getSeats();
        inline void setSeats(int seats);
        inline void setLine(int line);


    private:
        int seats;
        int line;

};

int Bus_t::getLine(){ return line;}
int Bus_t::getSeats(){ return seats;}
void Bus_t::setSeats(int seats){ seats = seats;}
void Bus_t::setLine(int line) {line = line;}



#endif