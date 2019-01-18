#ifndef UTIL_H
#define UTIL_H
#pragma once

#include <iostream>
#include <regex>
#include <cmath>
#include <string>
#include <sstream>
#include <locale>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// remeber, if you arent' going to make a util.cpp file, you need to preface all your defined functions here with inline
// because otherwise, everywhere you include "util.h" you would be difining each function multiple times
// inline prevents redefinition errors

namespace util {


	inline void removeThisFromVector(std::vector<std::string>& v, std::string str) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == str) {
				v.erase(v.begin() + i);
			}
		}
	}

	inline bool vectorContains(std::vector<std::string>& v, std::string str) {

		bool flag = false;
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == str) { // how would you write this in pointer notation? declare v as pointer to vector?
				flag = true;
			}
		}

		return flag;
	}

	inline double radsToDegs(double rads) {
		double degs = rads * (180 / 3.14159265358979323846264338327950);
		return degs;
	}

	inline double degsToRads(double degs) {
		double rads = degs * (3.14159265358979323846264338327950 / 180);
		return rads;
	}

	// takes a string and returns it but with no white space
	inline std::string removeSpaces(std::string str) {
		int n = 0;
		for (int i = 0; i < str.length(); ++i) {
			if (str[i] != ' ') {
				str[n++] = str[i];
			}
		}
		str.resize(n);
		return str;
	}

	// takes a string and returns the same string but every charachter is lowercase
	inline std::string thisToLowerCase(std::string str) {
		std::locale loc;
		for (std::string::size_type i = 0; i < str.length(); ++i) {
			str[i] = std::tolower(str[i], loc);
		}
		return str;
	}

	inline std::string thisToUpperCase(std::string str) {
		std::locale loc;
		for (std::string::size_type i = 0; i < str.length(); ++i) {
			str[i] = std::toupper(str[i], loc);
		}
		return str;
	}

	// takes a regex and a string. Returns the first match of that regex in the string
	inline std::string getRegexFromString(std::string gettingThis, std::string enteredString) {

		std::regex expression(gettingThis);
		std::smatch match;

		if (regex_search(enteredString, match, expression)) {
			std::string matchInString = match.str(0);
			return matchInString;
		}
		else {
			return "Match Not Found";
		}
	}

	// takes a string and tests it to see if it contains a regular expression - returns a bool
	inline bool thisStringHasThisRegex(std::string str, std::string testingFor) {

		std::regex expression(testingFor, std::regex_constants::icase);
		bool match = regex_search(str, expression);
		return match;
	}

	inline int stringToInt(std::string s) {

		std::stringstream myStream(s);
		int x = 0;
		myStream >> x;

		return x;
	}

	inline int randomNumXtoY(int x, int y) {
		int rn = x + (rand() % (y - x + 1));
		return rn;
	}

	// calculates the impact anlge. Impact angle is more severe the closer it is to 90
	inline double impactAngleFrom(double fireHeading, double armorHeading) {

		double impactAngle;
		double difference;
		double other;

		difference = abs(fireHeading - armorHeading);
		if (difference > 180) {
			difference = abs(180 - difference);
		}

		other = abs(180 - difference);

		if (difference > other) {
			impactAngle = other;
		}
		else if (difference <= other) {
			impactAngle = difference;
		}
		return impactAngle;
	}

	inline double getChanceToMiss(double distanceToTarget, double dispersion, double potentialImpactAngle) {

		double chanceToMiss = (distanceToTarget / 100)*(dispersion / 1.7) + ((90 - potentialImpactAngle) / 130);
		return chanceToMiss;
	}


} // end of util namespace
#endif


