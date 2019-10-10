#include "meeting_t.h"
#include <string>

Meeting_t::~Meeting_t(){}

/*Meeting_t::Meeting_t() : m_start(0), m_end(0) {
	m_topic = new string ("");
}*/

Meeting_t::Meeting_t(float start, float end, string& topic){
	m_start = start;
	m_end = end;
	m_topic = topic;
}