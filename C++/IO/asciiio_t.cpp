#include "asciiio_t.h"

AsciiIO_t& AsciiIO_t::operator>>(int& num){ return readTemplate(num, "%d");}
AsciiIO_t& AsciiIO_t::operator<<(int num){ return writeTemplate(num, "%d");}

AsciiIO_t& AsciiIO_t::operator>>(float& num){ return readTemplate(num, "%f");}
AsciiIO_t& AsciiIO_t::operator<<(float num){ return writeTemplate(num, "%f");}

AsciiIO_t& AsciiIO_t::operator>>(char& num){ return readTemplate(num, "%c");}
AsciiIO_t& AsciiIO_t::operator<<(char num){ return writeTemplate(num, "%c");}

AsciiIO_t& AsciiIO_t::operator>>(double& num){ return readTemplate(num, "%lf");}
AsciiIO_t& AsciiIO_t::operator<<(double num){ return writeTemplate(num, "%lf");}

AsciiIO_t& AsciiIO_t::operator>>(short& num){ return readTemplate(num, "%hi");}
AsciiIO_t& AsciiIO_t::operator<<(short num){ return writeTemplate(num, "%hi");}

AsciiIO_t& AsciiIO_t::operator>>(long& num){ return readTemplate(num, "%li");}
AsciiIO_t& AsciiIO_t::operator<<(long num){ return writeTemplate(num, "%li");}

AsciiIO_t& AsciiIO_t::operator>>(unsigned int& num){ return readTemplate(num, "%u");}
AsciiIO_t& AsciiIO_t::operator<<(unsigned int num){ return writeTemplate(num, "%u");}

AsciiIO_t& AsciiIO_t::operator>>(unsigned short& num){ return readTemplate(num, "%hu");}
AsciiIO_t& AsciiIO_t::operator<<(unsigned short num){ return writeTemplate(num, "%hu");}

AsciiIO_t& AsciiIO_t::operator>>(unsigned char& num){ return readTemplate(num, "%c");}
AsciiIO_t& AsciiIO_t::operator<<(unsigned char num){ return writeTemplate(num, "%c");}

AsciiIO_t& AsciiIO_t::operator>>(unsigned long& num){ return readTemplate(num, "%lu");}
AsciiIO_t& AsciiIO_t::operator<<(unsigned long num){ return writeTemplate(num, "%lu");}