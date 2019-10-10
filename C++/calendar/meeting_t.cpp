#include "meeting_t.h"
#include <string>

Meeting_t::Meeting_t(float start, float end, std::string& topic) : 
	m_start(start), m_end(end), m_topic (topic)
{
	if (start < 0 || start >= 24 || end <= 0 || end > 24 || start > end)
		throw std::string ("Invalid times");
}


