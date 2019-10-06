#include <string>
#include "tException_t.h"

template <class T>
TException_t<T>::TException_t(const T& excep, const std::string& message, const char* fileName, int lineNumber): 
	m_excep(excep), m_message(message), m_fileName(fileName), m_line(lineNumber){}
		
template <class T>
TException_t<T>::TException_t(const TException_t& excep):
	m_excep(excep.m_excep), m_message(excep.m_message), m_fileName(excep.m_fileName), m_line(excep.m_line){}
	
template <class T>
TException_t<T>& TException_t<T>::operator=(const TException_t<T>& excep){
	if (*this != excep){
		m_excep = excep.m_excep;
		m_message = excep.m_message;
		m_fileName = excep.m_fileName;
		m_line = excep.m_line;
	}
}