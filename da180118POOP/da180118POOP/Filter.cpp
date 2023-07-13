#include <iostream>
#include <regex>
#include "Event.h"
#include "Athlete.h"
#include <vector>
#include <fstream>
#include <map>
#include "Filter.h"

void Filter::sort(string sport, string country, int year, string typeEvent, string typeMedal) {

	for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
		if ((sport == "" || (*i)->getSport() == sport) && (country == "" || (*i)->getCounty() == country) && (year == 0 || (*i)->getYear() == year) && (typeEvent == "" || (*i)->getTypeEvent() == typeEvent) && (typeMedal == "" || (*i)->getTypeMedal() == typeMedal)) {
			events.push_back(*i);
		}
		//cout << **i << "\n";
	}
	writeEvents();
}

void Filter::bySport(string sport) {

	for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
		if ((*i)->getSport() == sport) {
			events.push_back(*i);
		}
		//cout << **i << "\n";
	}
	//writeEvents();
}

void Filter::byCounty(string country) {

	if (events.empty()) {
		for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
			if ((*i)->getSport() == country)events.push_back(*i);
			//cout << **i << "\n";
		}
	}
	else {
		int number = 0;
		for (auto i = events.begin(); i != events.end(); ++i) {
			if ((*i)->getSport() == country) events[number++] = (*i);
			//cout << **i << "\n";
		}
		events.resize(number);
	}
}

void Filter::byYear(int year) {

	if (events.empty()) {
		for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
			if ((*i)->getYear() == year)events.push_back(*i);
			//cout << **i << "\n";
		}
	}
	else {
		int number = 0;
		for (auto i = events.begin(); i != events.end(); ++i) {
			if ((*i)->getYear() == year) events[number++] = (*i);
			//cout << **i << "\n";
		}
		events.resize(number);
	}
}

void Filter::byEventType(string type) {

	if (events.empty()) {
		for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
			if ((*i)->getTypeEvent() == type)events.push_back(*i);
			//cout << **i << "\n";
		}
	}
	else {
		int number = 0;
		for (auto i = events.begin(); i != events.end(); ++i) {
			if ((*i)->getTypeEvent() == type) events[number++] = (*i);
			//cout << **i << "\n";
		}
		events.resize(number);
	}
}

void Filter::byMedalType(string type) {

	if (events.empty()) {
		for (auto i = (*originalEvents).begin(); i != (*originalEvents).end(); ++i) {
			if ((*i)->getTypeMedal() == type)events.push_back(*i);
			//cout << **i << "\n";
		}
	}
	else {
		int number = 0;
		for (auto i = events.begin(); i != events.end(); ++i) {
			if ((*i)->getTypeMedal() == type) events[number++] = (*i);
			//cout << **i << "\n";
		}
		events.resize(number);
	}
}

void Filter::writeEvents() {

	cout << "Filter : " << "\n";
	for (auto i = events.begin(); i != events.end(); ++i) {
		cout << **i << "\n";
	}
}

void Filter::writeAthletes() {

	//cout << "Filter by sport: " << "\n";
	for (auto i = events.begin(); i != events.end(); ++i) {
		cout << *((*originalAthletes).find(stoi((**i).getMark()))->second) << "\n";
	}
}

vector<Event*>* Filter::getFilteredEvents() {
	return &events;
}