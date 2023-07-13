#pragma once

#include <iostream>
#include <regex>
using namespace std;

class Athlete {
	int uniqueMark;
	string name;
	char gender;
	string years;
	string height;
	string weight;

	string sport;
	vector<pair<int, string>> medalsWon;
	string country;

public:
	Athlete(string s) {
		regex rx("([0-9]+)!([^!]+)!(.)!([^!]+)!([^!]+)!(.+)");
		smatch res;
		if (regex_match(s, res, rx)) {
			uniqueMark = stoi(res.str(1));
			name = res.str(2);
			gender = res.str(3)[0];
			years = res.str(4);
			height = res.str(5);		
			weight = res.str(6);
			sport = "";
		}
	}

	Athlete() {}

	~Athlete() {
		
	}

	int numberOfMedals() {
		return medalsWon.size();
	}

	friend ostream& operator<< (ostream& outs, const Athlete& obj) {

		string medals = "";
		for (auto i = obj.medalsWon.begin(); i != obj.medalsWon.end(); ++i)medals += " (" + to_string(i->first) +":"+ i->second + ")";
		return outs << to_string(obj.uniqueMark) << "!" << obj.name << "!" << obj.gender << "!" << obj.years << "!" << obj.height << "!" << obj.weight << " :" << obj.sport << " :"<<obj.medalsWon.size();
	}

	int getMark() { return uniqueMark; }
	string getHeight() { return height; }
	string getWeight() { return weight; }
	void setSport(string s) { sport = s; }
	string getSport() { return sport; }
	string getName() { return name; }
	char getGender() { return gender; }
	string getYears() { return years; }
	void setMark(int mark) { uniqueMark = mark; }
	void setCountry(string c) { country = c; }
	string getCountry() { return country; }

	void addMedal(int year, string medal) {
		medalsWon.push_back(pair<int, string>(year, medal));
	}


	int winOnFirst() {

		bool in = false;
		int min = 0;
		for (int i = 0; i < medalsWon.size(); i++) {
			if (medalsWon[i].first <= medalsWon[min].first) {
				if (medalsWon[i].second == "Gold") {
					in = true;
					min = i;
				}
			}
		}
		
		if (!in)return -1;
		else
			return stoi(years);
	}


	void copyAthlete(Athlete* a) {
		uniqueMark = a->getMark();
		name = a->getName();
		gender = a->getGender();
		years = a->getYears();
		height = a->getHeight();
		weight = a->getWeight();
	}
};