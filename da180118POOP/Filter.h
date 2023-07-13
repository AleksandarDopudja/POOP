#include <iostream>
#include <regex>
#include "Event.h"
#include "Athlete.h"
#include <vector>
#include <fstream>
#include <map>

class Filter {
	map<int,Athlete*> athletes;
	vector<Event*> events;
	map<int, Athlete*>* originalAthletes;
	vector<Event*>* originalEvents;

public:
	Filter(vector<Event*> *events, map<int, Athlete*> *athletes) {
		originalAthletes = athletes;
		originalEvents = events;
	}

	~Filter() {
		for (auto i = events.begin(); i != events.end(); ++i) {
			delete* i;
		}

		for (auto i = athletes.begin(); i != athletes.end(); ++i) {
			delete (*i).second;
		}

		originalAthletes = nullptr;
		originalEvents = nullptr;
	}

	void sort(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");

	void bySport(string sport);

	void byCounty(string country);

	void byYear(int year);

	void byEventType(string type);

	void byMedalType(string type);

	void writeEvents();

	void writeAthletes();

	vector<Event*>* getFilteredEvents();

};
