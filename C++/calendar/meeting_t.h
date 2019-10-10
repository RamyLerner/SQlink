#ifndef MEETING_H
#define MEETING_H

#include <string>
	class Meeting_t{
		public:
			~Meeting_t();
			Meeting_t(float start, float end, string& topic);
			
			

			inline float getStart const();
			inline float getEnd const ();
			inline string getTopic const ();

		private:
			const float m_start;
			const float m_end;
			const string m_topic;
			
			Meeting_t& operator=(const Meeting_t& m);
			Meeting_t(const Meeting_t& m);
	};
	
	inline float Meeting_t::getStart const(){ return m_start;}
	inline float Meeting_t::getEnd const (){ return m_end;}
	inline string Meeting_t::getTopic const (){ return m_topic;}

#endif