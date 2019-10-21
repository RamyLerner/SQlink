#ifndef MEETING_H
#define MEETING_H

#include <string>
	class Meeting_t{
		public:
			~Meeting_t(){}
			Meeting_t(float start, float end, std::string& topic);
			Meeting_t& operator=(const Meeting_t& m);
			Meeting_t(const Meeting_t& m);
			
			

			inline float getStart() const;
			inline float getEnd() const;
			inline std::string getTopic() const;
			inline void setTopic(const std::string topic);

		private:
			float m_start;
			float m_end;
			std::string m_topic;
			
			void update(const Meeting_t& meet);
			
			
	};
	
	inline float Meeting_t::getStart() const { return m_start;}
	inline float Meeting_t::getEnd() const { return m_end;}
	inline std::string Meeting_t::getTopic() const { return m_topic;}
	inline void Meeting_t::setTopic(const std::string topic){ m_topic = topic;}
	

#endif