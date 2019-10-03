#ifndef STREET_H
#define STREET_H

#include <vector>
#include <string>
#include "building_t.h"
using namespace std;

	template <class SID, class BID>
	class Street_t{
		public:
			Street_t();
			Street_t(const Street_t<SID, BID>&);
			Street_t<SID, BID>& operator=(const Street_t<SID, BID>&);
			
			inline SID getStreetID() const;
			inline void setStreetID(SID id);
			void AddBuilding2Street(Building_t<BID>& bd);
			Building_t<BID>& getBuilding(BID id) const;
		
		private:
			SID m_id;
			vector<BID> m_buildings;
	};
	
	template <class SID, class BID>
	Street_t<SID, BID>::Street_t(){} 
	
	template <class SID, class BID>
	Street_t<SID, BID>::Street_t(const Street_t<SID, BID>& st){
		m_id = st.m_id;
		m_buildings = st.m_buildings;
	}
	
	template <class SID, class BID>
	Street_t<SID,BID>& Street_t<SID, BID>::operator=(const Street_t<SID, BID>& st){
		if (*this != st){
			m_id = st.m_id;
			m_buildings = st.m_buildings;
		}
	}
	
	template <class SID, class BID>
	inline SID Street_t<SID, BID>::getStreetID() const { return m_id;}
	
	template <class SID, class BID>
	inline void Street_t<SID, BID>::setStreetID(SID id) { m_id = id;} 
	
	template <class SID, class BID>
	void Street_t<SID, BID>::AddBuilding2Street(Building_t<BID>& bd) { m_buildings.push_back(bd);}
	
	template <class SID, class BID>
	Building_t<BID>& Street_t<SID, BID>::getBuilding(BID id) const{
		int i;
		for (i=0; i<m_buildings.size(); i++)
			if (m_buildings[i].m_id == id)
				return m_buildings[i];
		throw string ("Not Found");
	}	
#endif