#include "building_t.h"
#include "street_t.h"
#include "city_t.h"
#include <string>
#include <iostream>

int main(){
	Building_t<string> bd;
	Street_t<int, int> st;
	City_t<string, int, string> ct;

	bd.setBuildingID("build");
	st.setStreetID(8);
	ct.setCityID("NATANYA");
	
	std::cout << bd.getBuildingID() << endl;
	std::cout << st.getStreetID() << endl;
	std::cout << ct.getCityID() << endl;

	return 0;
	
}