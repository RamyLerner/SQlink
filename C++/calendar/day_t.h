#ifndef DAY_H
#define DAY_H

#include<map>

	class Day_t{
		public:
			~Day_t();
			Day_t();
			bool insert (const Meeting_t* const meeting);
			Meeting_t* remove (float begin);
			Meeting_t* find(float begin) const;
			void clean ();
		
		private:
			map<float, Meeting_t*> m_meetings;
			
			typedef typename std::map<float, Meeting_t*>::iterator iter_t;
			typedef typename std::map<float, Meeting_t*>::const_iterator citer_t;
	};
	
	

#endif