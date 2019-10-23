#ifndef VIRTIO_H
#define VIRTIO_H

#include <string>
#include <cstdio>

	

	class VirtIO_t{
		public:
			inline virtual ~VirtIO_t();
			VirtIO_t();
			VirtIO_t(const std::string& path, const std::string& mode);
			
			
			typedef enum {ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e} ioStatus;
			
			inline const std::string& getPath() const;
			inline const std::string& getAccess() const;
			inline long int getPosition() const;
			inline ioStatus getStatus() const;
			long int getLength() const;
			bool setPosition(size_t pos);
			
			void open();
			inline void close();
			
			virtual VirtIO_t& operator>> (int& n) =0;
			virtual VirtIO_t& operator<< (int n) =0;
			
			virtual VirtIO_t& operator>> (float& n) =0;
			virtual VirtIO_t& operator<< (float n) =0;
			
			virtual VirtIO_t& operator>> (char& n) =0;
			virtual VirtIO_t& operator<< (char n) =0;
			
			virtual VirtIO_t& operator>> (long& n) =0;
			virtual VirtIO_t& operator<< (long n) =0;
			
			virtual VirtIO_t& operator>> (double& n) =0;
			virtual VirtIO_t& operator<< (double n) =0;
			
			virtual VirtIO_t& operator>> (short& n) =0;
			virtual VirtIO_t& operator<< (short n) =0;
			
			virtual VirtIO_t& operator>> (unsigned int& n) =0;
			virtual VirtIO_t& operator<< (unsigned int n) =0;
			
			virtual VirtIO_t& operator>> (unsigned char& n) =0;
			virtual VirtIO_t& operator<< (unsigned char n) =0;
			
			virtual VirtIO_t& operator>> (unsigned long& n) =0;
			virtual VirtIO_t& operator<< (unsigned long n) =0;

			virtual VirtIO_t& operator>> (unsigned short& n) =0;
			virtual VirtIO_t& operator<< (unsigned short n) =0;
			
			virtual VirtIO_t& operator>> (void* buf) =0;
			virtual VirtIO_t& operator<< (const void* buf) =0;
			
			virtual void operator, (size_t bytes) =0;
		protected:
			const std::string m_name;
			const std::string m_access;
			ioStatus m_status;
			FILE* m_fp;
			
			void writeChecks();
			void readChecks();
		private:
			VirtIO_t(const VirtIO_t&);
			VirtIO_t& operator= (const VirtIO_t&);
			
			
	};
	
	inline  VirtIO_t::~VirtIO_t() { fclose(m_fp);}
	inline void VirtIO_t::close() { fclose(m_fp);}
	inline const std::string& VirtIO_t::getPath() const { return m_name;}
	inline const std::string& VirtIO_t::getAccess() const { return m_access;}
	inline VirtIO_t::ioStatus VirtIO_t::getStatus () const { return m_status;}
	inline long int VirtIO_t::getPosition () const { return ftell(m_fp);}
	
#endif