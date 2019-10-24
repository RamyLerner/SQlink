#ifndef ASCIIIO_H
#define ASCIIIO_H 

#include "virtio_t.h"
#include <cstdio>
#include <string>

class AsciiIO_t : public VirtIO_t{
	public:
		~AsciiIO_t(){}
		AsciiIO_t(){}
		AsciiIO_t(const std::string& path, const std::string& mode) : VirtIO_t(path, mode){}

		AsciiIO_t& operator>> (int& n);
		AsciiIO_t& operator<< (int n);

		AsciiIO_t& operator>> (float& n);
		AsciiIO_t& operator<< (float n);

		AsciiIO_t& operator>> (char& n);
		AsciiIO_t& operator<< (char n);

		AsciiIO_t& operator>> (long& n);
		AsciiIO_t& operator<< (long n);

		AsciiIO_t& operator>> (double& n);
		AsciiIO_t& operator<< (double n);

		AsciiIO_t& operator>> (short& n);
		AsciiIO_t& operator<< (short n);

		AsciiIO_t& operator>> (unsigned int& n);
		AsciiIO_t& operator<< (unsigned int n);

		AsciiIO_t& operator>> (unsigned char& n);
		AsciiIO_t& operator<< (unsigned char n);

		AsciiIO_t& operator>> (unsigned long& n);
		AsciiIO_t& operator<< (unsigned long n);

		AsciiIO_t& operator>> (unsigned short& n);
		AsciiIO_t& operator<< (unsigned short n);
	private:
		AsciiIO_t(const AsciiIO_t&);
		AsciiIO_t& operator= (const AsciiIO_t&);
		AsciiIO_t& operator>> (void* buf) { return *this;}
		AsciiIO_t& operator<< (const void* buf) { return *this;}
		void operator, (size_t bytes){}
		
		template <class T>
		AsciiIO_t& readTemplate(T& num, std::string format);
		
		template <class T>
		AsciiIO_t& writeTemplate(T num, std::string format);
};

template <class T>
AsciiIO_t& AsciiIO_t::readTemplate(T& num, std::string format){
	readChecks();
	if (m_status == ok_e && fscanf(m_fp, format.c_str(), num) < 1){
		m_status = readErr_e;
		throw std::string ("read error");
	}
	return *this;
}

template <class T>
AsciiIO_t& AsciiIO_t::writeTemplate(T num, std::string format){
	writeChecks();
	if (m_status == ok_e && fprintf(m_fp, format.c_str(), num) < 0){
		m_status = writeErr_e;
		throw std::string ("write error");
	}
	return *this;
}


#endif
