#include "virtio_t.h"
#include <cstdio>
#include <string>

VirtIO_t::VirtIO_t(){
	m_status = ok_e;
	m_fp = 0;
}

VirtIO_t::VirtIO_t(const std::string& path, const std::string& mode) : m_name(path), m_access(mode){
	open();
}

void VirtIO_t::open(){ 
	m_fp = fopen(m_name.c_str(), m_access.c_str());
	if (!m_fp){
		m_status = cant_open_file_e;
		throw std::string ("cant_open_file");
	}
}
		
bool VirtIO_t::setPosition(size_t pos){
	if (fseek(m_fp, pos, SEEK_SET) == 0)
		return 1;
	else
		return 0;
}

long VirtIO_t::getLength() const{
	long current, end;
	current = ftell(m_fp);
	fseek(m_fp, 0, SEEK_END);
	end = ftell(m_fp);
	fseek(m_fp, current, SEEK_SET);
	return end;
}

void VirtIO_t::writeChecks(){
	if (m_access!="w" && m_access!="w+" && m_access!="r+")
		m_status = bad_access_e;
	if (!m_fp)
		m_status = writeErr_e;
}

void VirtIO_t::readChecks(){
	if (m_access!="r" && m_access!="w+" && m_access!="r+")
		m_status = bad_access_e;
	if (!m_fp)
		m_status = readErr_e;
}