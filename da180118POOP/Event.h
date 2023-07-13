#pragma once

#include <iostream>
#include <regex>
using namespace std;

class Event {
	int year;
	string typeOG;
	string city;
	string sport;
	string discipline;
	string typeEvent;
	string country;
	string uniqueMark;
	string typeMedal;

public:
	Event(int yr, string typOG, string ct, string spt, string dis, string typEvt, string cnt, string unqMar, string typMed) :year(yr), typeOG(typOG), sport(spt), discipline(dis), typeEvent(typEvt), country(cnt), uniqueMark(unqMar), typeMedal(typMed) {};
	Event(string s) {
		regex rx("((\\d+) ([a-zA-z]+))!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([a-zA-z]*)");
		smatch res;
		if (regex_match(s, res, rx)) {
			year = stoi(res.str(2));
			typeOG = res.str(3);
			city = res.str(4);
			sport = res.str(5);
			discipline = res.str(6);
			typeEvent = res.str(7);
			country = res.str(8);
			uniqueMark = res.str(9);
			typeMedal = res.str(10);
		}
	}

	int getYear() { return year; }
	string getTypeOG() { return typeOG; }
	string getMark() { return uniqueMark; }
	string getTypeEvent() { return typeEvent; }
	string getDiscipline() { return discipline; }
	string getSport() { return sport; }
	string getCounty() { return country; }
	string getTypeMedal() { return typeMedal; }
	string getCity() { return city; }

	friend ostream& operator<< (ostream& outs, const Event& obj) {
		return outs << to_string(obj.year) << ":" << obj.typeOG << ":" + obj.city << ":" + obj.sport << ":" << obj.discipline << ":" + obj.typeEvent << ":" << obj.country << ":" + obj.uniqueMark << ":" << obj.typeMedal;
	}

};