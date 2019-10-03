#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>
#include "street_t.h"
using namespace std;

	template <class CID, class SID, class BID>
	class City_t{
		public:
			City_t();
			City_t(const City_t<CID, SID, BID>&);
			City_t<CID, SID, BID>& operator=(const City_t<CID, SID, BID>&);
			
			inline CID getCityID() const;
			inline void setCityID(CID id);
			void AddStreet(Street_t<SID, BID>& st);
			Street_t<SID, BID>& getStreet(SID id) const;
		
		private:
			CID m_id;
			vector<SID> m_streets;
	};
	
	template <class CID, class SID, class BID>
	City_t<CID, SID, BID>::City_t(){} 
	
	template <class CID, class SID, class BID>
	City_t<CID, SID, BID>::City_t(const City_t<CID, SID, BID>& ct){
		m_id = ct.m_id;
		m_streets = ct.m_streets;
	}
	
	template <class CID, class SID, class BID>
	City_t<CID, SID, BID>& City_t<CID, SID, BID>::operator=(const City_t<CID, SID, BID>& ct){
		if (*this != ct){
			m_id = ct.m_id;
			m_streets = ct.m_streets;
		}
	}
	
	template <class CID, class SID, class BID>
	inline CID City_t<CID, SID, BID>::getCityID() const { return m_id;}
	
	template <class CID, class SID, class BID>
	inline void City_t<CID, SID, BID>::setCityID(CID id) { m_id = id;} 
	
	template <class CID, class SID, class BID>
	void City_t<CID, SID, BID>::AddStreet(Street_t<SID, BID>& st) { m_streets.push_back(st);}
	
	template <class CID, class SID, class BID>
	Street_t<SID, BID>& City_t<CID, SID, BID>::getStreet(SID id) const{
		int i;
		for (i=0; i<m_streets.size(); i++)
			if (m_streets[i].m_id == id)
				return m_streets[i];
		throw string ("Not Found");
	}
#endif