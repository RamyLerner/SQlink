#include "day_t.h"
#include "meeting_t.h"
#include <map>


bool insert (const Meeting_t* const meeting){
	if (meeting == 0)
		return 0;
	iter_t it = m_meeting.begin();
	float start = meeting.getStart();
	
	//if day is empty or meeting is last
	if (m_meetings.empty() || 
	    m_meetings.end() - 1 -> second . getEnd() < start){
		m_meetings[start] = meeting;
		return 0;
	}
		
	while (it -> second . getEnd() > start){
		it++;
	}
	//if time for meeting is available
	if (it->first <= meeting.getEnd()){
		m_meetings[start] = meeting;
		return 1;
	}
	return 0;
}

Meeting_t* remove (float begin){
	
}

void Day_t::clean(){
	/*iter_t it;
	for (it = m_meetings.begin(); i<m_meetings.end(); ++i)
		delete *it;*/
	m_meetings.clear();
}