#include "day_t.h"
#include "meeting_t.h"
#include <map>
#include <iostream>

Day_t::~Day_t() {
	iter_t it = m_meetings.begin();
	while (it != m_meetings.end()){
		delete it -> second;
		it ++;
	}
}

Day_t::Day_t() {}

void Day_t::update(const Day_t& day){
	citer_t it = day.m_meetings.begin();
	while (it != day.m_meetings.end()){
		Meeting_t newMeeting(*(it->second));
		m_meetings.insert(std::pair<float, Meeting_t*>(newMeeting.getStart(), &newMeeting));
		it++;	
	}
}

Day_t::Day_t(const Day_t& day){
	update(day);
}


Day_t& Day_t::operator= (const Day_t& day){
	if (this != &day){
		update(day);
	}
	return *this;
}

bool Day_t::insert (const Meeting_t* const meetPtr){
	if (meetPtr == 0)
		return 0; 
	iter_t it = m_meetings.begin();
	float start = meetPtr->getStart();
	
	//if day is empty or meeting is last
	if (m_meetings.empty() || 
	    m_meetings.rbegin() -> second -> getEnd() <= start){
		m_meetings[start] = (Meeting_t*)meetPtr;
		return 1;
	}
		
	while (it -> second -> getEnd() <= start){
		it++;
	}
	//if time for meeting is available
	if (it->first >= meetPtr->getEnd()){
		m_meetings[start] = (Meeting_t*)meetPtr;
		return 1;
	}
	return 0;
}

Meeting_t* Day_t::find (float begin) const{
	citer_t it = m_meetings.find(begin);
	if (it != m_meetings.end())
		return it -> second;
	return 0;
}

Meeting_t* Day_t::remove (float begin){
	Meeting_t* m = find(begin);
	return remove(m);	
}

//using erase(const keyType k) version
Meeting_t* Day_t::remove (Meeting_t* m){
	if (m)
		m_meetings.erase(m->getStart());
	return m;
}

void Day_t::clean(){
	iter_t it;
	for (it = m_meetings.begin(); it!=m_meetings.end(); ++it)
		delete it -> second;
	m_meetings.clear();
}

void Day_t::print() const{
	citer_t it = m_meetings.begin();
	while (it != m_meetings.end()){
		std::cout << "Meeting from " << it->second->getStart() << " until " << it->second->getEnd() << " about: " << it->second->getTopic() << std::endl;
		it++;
	}
}