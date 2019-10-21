#ifndef DAY_H
#define DAY_H

#include<map>
#include "meeting_t.h"

	class Day_t{
		public:
			~Day_t();
			Day_t();
			Day_t(const Day_t& d);
			Day_t& operator= (const Day_t& d);
			bool insert (const Meeting_t* const meeting);
			Meeting_t* remove (float begin);
			Meeting_t* remove (Meeting_t* m);
			Meeting_t* find(float begin) const;
			void clean ();
			void print() const;
		
		private:
			std::map<float, Meeting_t*> m_meetings;
			
			void update(const Day_t& day);
			
			typedef typename std::map<float, Meeting_t*>::iterator iter_t;
			typedef typename std::map<float, Meeting_t*>::const_iterator citer_t;
	};
	
	

#endif