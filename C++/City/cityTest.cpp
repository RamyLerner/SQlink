#include "building_t.h"
#include "street_t.h"
#include "city_t.h"
#include <string>

int main(){
	Building_t<string> bd;
	Street_t<int, int> st;
	City_t<string, int, string> ct;
	
	return 0;
	
}