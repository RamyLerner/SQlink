#include "meeting_t.h"
#include <string>

Meeting_t::Meeting_t(float start, float end, std::string& topic) : 
	m_start(start), m_end(end), m_topic (topic)
{
	if (start < 0 || start >= 24 || end <= 0 || end > 24 || start > end)
		throw std::string ("Invalid times");
}

void Meeting_t::update(const Meeting_t& meet){
	m_start = meet.m_start;
	m_end = meet.m_end;
	m_topic = meet.m_topic;
}

Meeting_t::Meeting_t(const Meeting_t& meet){
	update(meet);
}

Meeting_t& Meeting_t::operator=(const Meeting_t& m){
	if (this != &m)
		update(m);
	return *this;
}



