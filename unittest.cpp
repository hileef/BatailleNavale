// unittest.cpp
#include <math.h>
#include <stdlib.h>
#include "unittest.h"

void assertTrue(bool cond, const std::string& s) {
	assertEquals(cond, true, s);
}

void assertFalse(bool cond, const std::string& s){
	assertEquals(cond, false, s);
}

void assertEqualsDouble(double x, double y, double precision,const std::string&s) {
	std::cout << "Test " << s;
	if (abs(x-y) < precision)
		std::cout << " a reussi\n";
	else {	std::cout << " a ECHOUE ###\n";
			std::cout << x << " != " << y << " ecart : " 
				      << abs(x-y) << " > " << precision << std::endl;
	}
}
