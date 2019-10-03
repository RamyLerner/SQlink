#ifndef BUILDING_H
#define BUILDING_H

	template <class TID>
	class Building_t{
		public:
			Building_t();
			Building_t(const Building_t<TID>& b);
			Building_t<TID>& operator= (const Building_t<TID>& b);
		
			inline TID getBuildingID() const;
			inline void setBuildingID(TID id);
		private:
			TID m_id;		
	};
	
	template <class TID>
	Building_t<TID>::Building_t(){}
	
	template <class TID>
	Building_t<TID>::Building_t(const Building_t<TID>& b){ m_id = b.m_id;}
	
	template <class TID>
	Building_t<TID>& Building_t<TID>::operator= (const Building_t<TID>& b){
		if (*this != b)
			m_id = b.m_id;
	}

	template <class TID>
	inline TID Building_t<TID>::getBuildingID() const{ return m_id;}
	
	template <class TID>
	inline void Building_t<TID>::setBuildingID(TID id){ m_id = id;}
	
#endif