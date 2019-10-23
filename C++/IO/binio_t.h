#ifndef BINIO_H
#define BINIO_H 

#include "virtio_t.h"
#include <cstdio>

class BinIO_t : public VirtIO_t{
	public:
		~BinIO_t(){}
		BinIO_t(){}
		BinIO_t(const std::string& path, const std::string& mode) : VirtIO_t(path, mode){}

		BinIO_t& operator>> (int& n);
		BinIO_t& operator<< (int n);

		BinIO_t& operator>> (float& n);
		BinIO_t& operator<< (float n);

		BinIO_t& operator>> (char& n);
		BinIO_t& operator<< (char n);

		BinIO_t& operator>> (long& n);
		BinIO_t& operator<< (long n);

		BinIO_t& operator>> (double& n);
		BinIO_t& operator<< (double n);

		BinIO_t& operator>> (short& n);
		BinIO_t& operator<< (short n);

		BinIO_t& operator>> (unsigned int& n);
		BinIO_t& operator<< (unsigned int n);

		BinIO_t& operator>> (unsigned char& n);
		BinIO_t& operator<< (unsigned char n);

		BinIO_t& operator>> (unsigned long& n);
		BinIO_t& operator<< (unsigned long n);

		BinIO_t& operator>> (unsigned short& n);
		BinIO_t& operator<< (unsigned short n);

		BinIO_t& operator>> (void* buf);
		BinIO_t& operator<< (const void* buf);

		void operator, (size_t bytes);
	private:
		enum operation{r_shift, l_shift};
		
		enum operation m_op;
		void* m_ptr;
	
		template <class T>
		BinIO_t& readTemplate(T& num);
		
		template <class T>
		BinIO_t& writeTemplate(T num);

};

template <class T>
BinIO_t& BinIO_t::writeTemplate(T num){
	writeChecks();
	if (m_status == ok_e &&	fwrite(&num, 1, sizeof(T), m_fp) < 1){
		m_status = writeErr_e;
		throw std::string ("write error");
		
	}
	return *this;
}

template <class T>
BinIO_t& BinIO_t::readTemplate(T& num){
	readChecks();
	if (m_status == ok_e && fread(&num, 1, sizeof(T), m_fp) < 1){
		m_status = readErr_e;
		throw std::string ("read error");
		
	}
	return *this;
}


#endif
