#ifndef TEXCEPTION_H
#define TEXCEPTION_H

#include<string>
#include<iostream>
#define THROW_TEXCEPTION(obj,msg) throw TException_t(obj, msg, __FILE__, __LINE__)

	template <class T>
	class TException_t{
		public:
			~TException_t();
			TException_t(){}
			TException_t(const T& excep, const std::string& message, const char* fileName, int lineNumber);
			TException_t(const TException_t& texcp);
			TException_t& operator=(const TException_t& texcep);
			inline void print() const;
			
			inline const T           getException()  const;
			inline const std::string getMessage()    const;
			inline const char*       getFileName()   const;
			inline       int         getLineNumber() const;
		
		private:
			T m_excep;
			std::string m_message;
			char* m_fileName;
			int m_line;
	};
	
	template <class T>
	inline const T TException_t<T>::getException() const { return m_excep;}
	
	template <class T>
	inline const std::string TException_t<T>::getMessage() const { return m_message;}
	
	template <class T>
	inline const char* TException_t<T>::getFileName() const {return m_fileName;}
	
	template <class T>
	inline int TException_t<T>::getLineNumber() const {return m_line;}
		
	template <class T>
	inline void TException_t<T>::print() const {
		std::cout << "EXCEPTION: in " << m_fileName << "(" << m_line << ") " << m_message << ": " << m_excep << std::endl;
	}

#endif