#include "binio_t.h"

BinIO_t& BinIO_t::operator<<(int num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(float num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(short num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(long num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(double num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(char num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(unsigned int num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(unsigned char num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(unsigned long num) { return writeTemplate(num);}
BinIO_t& BinIO_t::operator<<(unsigned short num) { return writeTemplate(num);}


BinIO_t& BinIO_t::operator>>(int& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(float& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(short& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(long& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(double& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(char& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(unsigned int& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(unsigned char& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(unsigned long& num) { return readTemplate(num);}
BinIO_t& BinIO_t::operator>>(unsigned short& num) { return readTemplate(num);}


BinIO_t& BinIO_t::operator>>(void* ptr){ 
	m_op = r_shift;
	m_ptr = ptr;
}

BinIO_t& BinIO_t::operator<<(const void* ptr){ 
	m_op = l_shift;
	m_ptr = (void*)ptr;
}


void BinIO_t::operator, (size_t bytes){
	if (!m_ptr){
		m_status = bad_access_e;
		throw std::string("NULL pointer");
	}
	
	if (m_op == l_shift){
		writeChecks();
		if (m_status == ok_e &&	fwrite(m_ptr, bytes, 1, m_fp) < 1){
			m_status = writeErr_e;
			throw std::string ("write error");
		
		}
	}
	
	if (m_op == r_shift){
		readChecks();
		if (m_status == ok_e && fread(m_ptr, bytes, 1, m_fp) < 1){
			m_status = readErr_e;
			throw std::string ("read error");
		
		}
	}
}


