#include <iostream>
#include <regex>
using namespace std;
#include "Event.h"
#include "Athlete.h"
#include "Aplication.h"
#include "Filter.h"
#include <vector>
#include <fstream>
#include <cstring>  
#include <algorithm>
#include <cstring>

Aplication* Aplication::instance = nullptr;

void Aplication::readEvents(string directory, int year) {
	ifstream file;
	file.open(directory + "\\eventsshort.txt");
	string textline;
	Event* prev = nullptr;

	if (year == 0) {

		while (getline(file, textline)) {
			
			Event* e = new Event(textline);
			events.push_back(e);
			string medalWon = e->getTypeMedal();


			if (prev != nullptr && prev->getYear() != e->getYear()) {
				borders.push_back(events.size() - 1);
			}
						
			if (e->getTypeEvent() == "Individual") {
				Athlete* newAtl = new Athlete();
				newAtl->setSport(e->getSport());
				newAtl->setCountry(e->getCounty());
				athletes.insert(pair<int, Athlete*>(stoi(e->getMark()), newAtl));/// bio nullptr na mestu newAtl
				if (medalWon != "") {
					athletes[stoi(e->getMark())]->addMedal(e->getYear(), medalWon);
				}
			}
			else {
				Athlete* newAtl = new Athlete();
				newAtl->setSport(e->getSport());
				newAtl->setCountry(e->getCounty());
				string delim = ",";
				string str = e->getMark();
				Team* team = new Team(str, e->getDiscipline());
				teams.insert(pair<string, Team*>(str, team));
				if (medalWon != "") {
					teams[e->getMark()]->addMedal(e->getYear(), medalWon);
				}

				size_t pos = 0;
				string token;

				pos = str.find(delim);
				token = str.substr(2, pos-2);   

				athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
				if (medalWon != "") {
					athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
				}
				str.erase(0, pos + delim.length());

				while ((pos = str.find(delim)) != std::string::npos)
				{
					newAtl = new Athlete();
					newAtl->setSport(e->getSport());
					newAtl->setCountry(e->getCounty());
					token = str.substr(2, pos); // store the substring   
					//cout << token1 << endl;
					athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));///na mestu newAtl bio nullptr
					if (medalWon != "") {
						athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
					}
					str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
				}

				newAtl = new Athlete();
				newAtl->setSport(e->getSport());
				newAtl->setCountry(e->getCounty());
				token = str.substr(2, token.length()-2);
				athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
				if (medalWon != "") {
					athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
				}
			}
			prev = e;
		}

	}
	else {
		while (getline(file, textline)) {
			//cout << textline << "\n";
			Event* e = new Event(textline);
			string medalWon = e->getTypeMedal();

			if (prev != nullptr && prev->getYear() != e->getYear())borders.push_back(events.size()-1);

			if (e->getYear() == year) {
				events.push_back(e);
				if (e->getTypeEvent() == "Individual") {
					Athlete* newAtl = new Athlete();
					newAtl->setSport(e->getSport());
					newAtl->setCountry(e->getCounty());
					athletes.insert(pair<int, Athlete*>(stoi(e->getMark()), newAtl));
					if (medalWon != "") {
						athletes[stoi(e->getMark())]->addMedal(e->getYear(), medalWon);
					}
				}
				else {
					Athlete* newAtl = new Athlete();
					newAtl->setSport(e->getSport());
					newAtl->setCountry(e->getCounty());
					string delim = ",";
					string str = e->getMark();
					Team* team = new Team(str, e->getDiscipline());
					teams.insert(pair<string, Team*>(str, team));
					if (e->getTypeMedal() != "") {
						teams[e->getMark()]->addMedal(e->getYear(), medalWon);
					}


					size_t pos = 0;
					string token;

					pos = str.find(delim);
					token = str.substr(2, pos-2);   

					athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
					if (medalWon != "") {
						athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
					}
					str.erase(0, pos + delim.length());

					while ((pos = str.find(delim)) != std::string::npos)
					{
						newAtl = new Athlete();
						newAtl->setSport(e->getSport());
						newAtl->setCountry(e->getCounty());
						token = str.substr(2, pos); // store the substring   
						//cout << token1 << endl;
						athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
						if (medalWon != "") {
							athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
						}
						str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
					}

					newAtl = new Athlete();
					newAtl->setSport(e->getSport());
					newAtl->setCountry(e->getCounty());
					token = str.substr(2, token.length()-2);
					athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
					if (medalWon != "") {
						athletes[stoi(token)]->addMedal(e->getYear(), medalWon);
					}
				}
				
			}
			prev = e;
		}
	}

	file.close();
	Aplication::readAthletes(directory);
}

void Aplication::writeEvents() {
	for (auto i = events.begin(); i != events.end(); ++i) {
		cout << **i << "\n";
	}
}

void Aplication::readAthletes(string directory) {
	ifstream file;
	file.open(directory + "\\shortatl.txt");
	string textline;
	Athlete* a;

	while (getline(file, textline)) {
		//cout << textline << "\n";
		a = new Athlete(textline);
		int id = a->getMark();
		auto it = athletes.find(id);
		if (it != athletes.end()) {
			it->second->copyAthlete(a);
		}
		delete a;
	}	
}

void Aplication::writeAthletes() {
	for (auto iter = athletes.begin(); iter != athletes.end(); ++iter) {
		cout << iter->first << " - " << *(iter->second) << "\n";
	}
}

int Aplication::numberOfAthletes(string sport, string country, int year, string typeEvent, string typeMedal) {

	//sort("");
	int number = 0;
	Filter* f = new Filter(&events, &athletes);
	f->sort(sport, country, year, typeEvent, typeMedal);//string sport="", string country="", int year=0, string typeEvent="", string typeMedal=""
	vector<Event*>* filteredEvents = f->getFilteredEvents();

	for (auto i = (*filteredEvents).begin(); i != (*filteredEvents).end(); ++i) {
		//cout << (**i) << "\n";
		if ((**i).getTypeEvent() == "Individual") {
			number++;
		}
		else {
			number+=teams.find((**i).getMark())->second->numberOfPlayers();
		}
	}
	return number;
}

int Aplication::numberOfDisciplines(string sport, string country, int year, string typeEvent, string typeMedal) {

	Filter* f = new Filter(&events, &athletes);
	f->sort(sport, country, year, typeEvent, typeMedal);//string sport="", string country="", int year=0, string typeEvent="", string typeMedal=""
	vector<Event*>* filteredEvents = f->getFilteredEvents();

	vector<Event*> copy;
	for (auto i = (*filteredEvents).begin(); i != (*filteredEvents).end(); ++i) {
		copy.push_back(*i);
	}

	std::sort(copy.begin(), copy.end(), [](Event* a, Event* b)
		{
			return a->getDiscipline() > b->getDiscipline();
		});

	auto ip = std::unique(copy.begin(), copy.end(), [](Event* a, Event* b)
		{
			return a->getDiscipline() == b->getDiscipline();
		});

	int size = 0;
	for (auto i = copy.begin(); i != ip; ++i)size++;

	return size;
}

double Aplication::averageAthletesHeight(string sport, string country, int year, string typeEvent, string typeMedal) {

	Filter* f = new Filter(&events, &athletes);
	f->sort(sport, country, year, typeEvent, typeMedal);//string sport="", string country="", int year=0, string typeEvent="", string typeMedal=""
	vector<Event*>* filteredEvents = f->getFilteredEvents();

	int num = 0;
	double sum = 0;
	for (auto iter = (*filteredEvents).begin(); iter != (*filteredEvents).end(); ++iter) {
		if ((*iter)->getTypeEvent() == "Individual") {
			
			string h = athletes.find(stoi((*iter)->getMark()))->second->getHeight();
			if (h != "NA") { 
				sum += stod(h); 
				num++;
			}
		}
		else {
			vector<int>* players = teams.find((*iter)->getMark())->second->allPlayers();

			for (auto i = (*players).begin(); i != (*players).end(); ++i) {
				
				string h = athletes.find(*i)->second->getHeight();
				if (h != "NA") {
					sum += stod(h);
					num++;
				}
			}

		}
	}
	return sum / num;
}

double Aplication::averageAthletesWheight(string sport, string country, int year, string typeEvent, string typeMedal) {
	Filter* f = new Filter(&events, &athletes);
	f->sort(sport, country, year, typeEvent, typeMedal);//string sport="", string country="", int year=0, string typeEvent="", string typeMedal=""
	vector<Event*>* filteredEvents = f->getFilteredEvents();

	int num = 0;
	double sum = 0;
	for (auto iter = (*filteredEvents).begin(); iter != (*filteredEvents).end(); ++iter) {
		if ((*iter)->getTypeEvent() == "Individual") {

			string w = athletes.find(stoi((*iter)->getMark()))->second->getWeight();
			if (w != "NA") {
				sum += stod(w);
				num++;
			}
		}
		else {
			vector<int>* players = teams.find((*iter)->getMark())->second->allPlayers();

			for (auto i = (*players).begin(); i != (*players).end(); ++i) {

				string w = athletes.find(*i)->second->getWeight();
				if (w != "NA") {
					sum += stod(w);
					num++;
				}
			}

		}
	}

	return sum / num;
}

void Aplication::filterData(string sport, string country, int year, string typeEvent, string typeMedal) {

	//filteredData = new Filter( &events, &athletes);
	//filteredData->sort(sport,country,year,typeEvent,typeMedal);//string sport="", string country="", int year=0, string typeEvent="", string typeMedal=""
}

int Aplication::numberOfSportsByCountyWithMedal(string counrty) {

	vector<Event*> filterEvents;
	for (auto i = events.begin(); i != events.end(); ++i) {
		if ((*i)->getCounty() == counrty && ((*i)->getTypeMedal()=="Gold" || (*i)->getTypeMedal() == "Silver" || (*i)->getTypeMedal() == "Bronze"))filterEvents.push_back(*i);
	}

	std::sort(filterEvents.begin(), filterEvents.end(), [](Event* a, Event* b)
		{
			return a->getSport() > b->getSport();
		});

	auto ip = std::unique(filterEvents.begin(), filterEvents.end(), [](Event* a, Event* b)
		{
			return a->getDiscipline() == b->getDiscipline();
		});

	int size = 0;
	for (auto i = filterEvents.begin(); i != ip; ++i)size++;

	return size;
}

string Aplication::big3byOG(int year, string season, bool mod) {

	string keyPrefix = std::to_string(year) +"-"+ season;
	map<string, vector<int>> countyMedals;
	
	bool in = false;
	for (auto i = events.begin(); i != events.end(); ++i) {
		//cout << **i << "\n";
		if ((**i).getYear() == year && (**i).getTypeOG() == season) {

			in = true;
			string country = (**i).getCounty();
			string key = keyPrefix + "-" + country;

			if (countyMedals.find(key) != countyMedals.end()) {

				if ((**i).getTypeMedal() == "Gold")countyMedals.find(key)->second[0] += 1;
				else if ((**i).getTypeMedal() == "Silver")countyMedals.find(key)->second[1] += 1;
				else if ((**i).getTypeMedal() == "Bronze")countyMedals.find(key)->second[2] += 1;
			}
			else {
				if ((**i).getTypeMedal() != "") {
					countyMedals.insert(pair<string, vector<int>>(key, vector<int>(3, 0)));
					if ((**i).getTypeMedal() == "Gold")countyMedals.find(key)->second[0] += 1;
					else if ((**i).getTypeMedal() == "Silver")countyMedals.find(key)->second[1] += 1;
					else if ((**i).getTypeMedal() == "Bronze")countyMedals.find(key)->second[2] += 1;
				}
			}
		}
		else {
			///if (in)break;
		}
	}

	vector<pair<string, vector<int>>> vec;

	map<string, vector<int>> ::iterator it2;
	for (it2 = countyMedals.begin(); it2 != countyMedals.end(); it2++)
	{
		//cout << (*it2).first <<"\n";
		vec.push_back(pair<string, vector<int>>(it2->first, it2->second));
	}
	//cout << "----\n";

	std::sort(vec.begin(), vec.end(), [](pair<string, vector<int>> a, pair<string, vector<int>> b)
		{
			if (a.second[0] > b.second[0])return true;
			else if (a.second[0] == b.second[0]) {

				if (a.second[1] > b.second[1])return true;
				else if (a.second[1] == b.second[1]) {

					if (a.second[2] > b.second[2])return true;
					else
						return false;
				}
				else
					return false;
			}
			else 
				return false;		
		});

	int j = 0;
	//cout << "Ispis:" << "\n";
	if (!mod) {
		for (auto i = vec.begin(); i != vec.end(); ++i,j++) {

			cout << (*i).first << " - " << (*i).second[0] << ":" << (*i).second[1] << ":" << (*i).second[2] << "\n";
			if (j == 2)break;
		}
		return "";
	}
	

	auto i = vec.begin();
	//cout << (*i).first << " - " << (*i).second[0] << ":" << (*i).second[1] << ":" << (*i).second[2] << "\n";

	string s = (*i).first;

	string delim = "-"; // delimiter  

			
			size_t pos = 0;
			string token1; // define a string variable  

			// use find() function to get the position of the delimiters  
			while ((pos = s.find(delim)) != std::string::npos)
			{
				token1 = s.substr(0, pos); // store the substring   
				//if(!mod)cout << token1 << endl;
				s.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
			}

	return s;
}

void Aplication::bestCountryEveryYear() {

	vector<string> counties;

	auto next = events.begin();
	++next;
	auto i = events.begin();
	for (; next != events.end(); ++i,++next) {
		//cout << **i << "\n";
		if ((**i).getYear() != (**next).getYear()) {

			string s =big3byOG((**i).getYear(), (**i).getTypeOG(), true);

			//string given_str = "How_to_split_a_string_using_find()_and_substr()_function_in_C++";
			//string delim = " "; // delimiter  

			//cout << " Your string with delimiter is: " << given_str << endl;
			//size_t pos = 0;
			//string token1; // define a string variable  

			// use find() function to get the position of the delimiters  
			//while ((pos = s.find(delim)) != std::string::npos)
			//{
				//token1 = s.substr(0, pos); // store the substring   
				//cout << token1 << endl;
				//s.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
			//}
			//cout << given_str << endl; // it print last token of the string.  

			auto it = std::find(counties.begin(), counties.end(), s);
			if (it == counties.end()) {
				counties.push_back(s);
			}
		}

		//if(next+1== events.end())big3byOG((**i).getYear(), (**i).getTypeOG());
	}

	string str = big3byOG((**i).getYear(), (**i).getTypeOG());
	
	auto it = std::find(counties.begin(), counties.end(), str);
	if (it == counties.end()) {
		counties.push_back(str);
	}

	for (auto iter = counties.begin(); iter != counties.end(); ++iter) {
		cout << (*iter) << "\n";
	}
}

void Aplication::allCityesOG() {

	map<string, int> citys;

	citys.insert(pair<string, int>(events[0]->getCity(), 0));
	for (auto iter = borders.begin(); iter != borders.end(); ++iter) {
		//cout << (*iter)->getCity() << "\n";
		citys.insert(pair<string, int>(events[(*iter)]->getCity(), 0));
	}

	for (auto iter = citys.begin(); iter != citys.end(); ++iter) {
		cout << (*iter).first << "\n";
	}

	citys.clear();
}

void Aplication::pairOG(int year1, string tyOG1, int year2, string tyOG2) {

	map<int, int> atl;
	int begin = 0, end = 0;

	if (events[0]->getYear() == year1 && events[0]->getTypeOG() == tyOG1) {
		end = borders[0];
	}
	else {

		for (auto iter = borders.begin(); iter != borders.end(); ++iter) {
			//cout << (*iter)->getCity() << "\n";
			if (events[(*iter)]->getYear() == year1 && events[(*iter)]->getTypeOG() == tyOG1) {
				begin = *iter;
				++iter;
				end = *iter;
				break;
			}
		}
	}

	for (int i = begin; i < end;i++) {
		
		if (events[i]->getTypeEvent() == "Individual") {
			atl.insert(pair<int,int>(stoi(events[i]->getMark()),0));
		}
		else {

			vector<int>* players = teams[events[i]->getMark()]->allPlayers();

			for (auto iter = (*players).begin(); iter != (*players).end(); ++iter) {

				atl.insert(pair<int, int>(*iter, 0));
			}
		}
	}

	if (events[0]->getYear() == year2 && events[0]->getTypeOG() == tyOG2) {
		end = borders[0];
	}
	else {

		for (auto iter = borders.begin(); iter != borders.end(); ++iter) {
			//cout << (*iter)->getCity() << "\n";
			if (events[(*iter)]->getYear() == year2 && events[(*iter)]->getTypeOG() == tyOG2) {
				begin = *iter;
				++iter;
				if (iter != borders.end())end = *iter;
				else
					end = events.size();
				break;
			}
		}
	}

	cout << "Result:" << "\n";
	for (int i = begin; i < end; i++) {
		if (events[i]->getTypeEvent() == "Individual") {

			//auto it = atl.find(stoi(events[i]->getMark()));
			//if (it != atl.end())
				cout << *(athletes[stoi(events[i]->getMark())]) << "\n";
		}
		else {

			vector<int>* players = teams[events[i]->getMark()]->allPlayers();

			for (auto iter = (*players).begin(); iter != (*players).end(); ++iter) {

				auto it = atl.find(*iter);
				if (it != atl.end())
					cout << *(athletes[(*iter)]) << "\n";
			}
		}
	}

	
	atl.clear();
}


vector<Team*> Aplication::getTeam(string country, int yr, string tyOG) {

	int begin = 0, end = 0;
	vector<Team*> teamsForFilter;

	if (events[0]->getYear() == yr && events[0]->getTypeOG() == tyOG) {
		end = borders[0];
	}
	else {

		for (auto iter = borders.begin(); iter != borders.end(); ++iter) {
			//cout << (*iter)->getCity() << "\n";
			if (events[(*iter)]->getYear() == yr && events[(*iter)]->getTypeOG() == tyOG) {
				begin = *iter;
				++iter;
				if (iter != borders.end())end = *iter;
				else
					end = events.size();
				break;
			}
		}
	}

	for (int i = begin; i < end; i++) {

		if (events[i]->getCounty() == country && events[i]->getTypeEvent() == "Team") {

			teamsForFilter.push_back(teams.find(events[i]->getMark())->second);
		}
	}

	std::sort(teamsForFilter.begin(), teamsForFilter.end(), [](Team* a, Team* b)
		{
			return (*a).numberOfPlayers() > (*b).numberOfPlayers();
		});

	std::sort(teamsForFilter.begin(), teamsForFilter.end(), [](Team* a, Team* b)
		{
			return (*a).getDiscipline() > (*b).getDiscipline();
		});

	cout<<("res:\n");
	for (auto i = teamsForFilter.begin(); i != teamsForFilter.end(); ++i) {
		cout << *(*i);
	}

	return teamsForFilter;

}

vector<pair<string, Athlete*>> Aplication::getPairs() {

	vector<pair<string, Athlete*>> pairs;

	cout << "Res:\n";
	for (auto iter = teams.begin(); iter != teams.end(); ++iter) {

		if ((*iter).second->numberOfMedals() > 0) {

			vector<int>* players = (*iter).second->allPlayers();

			for (int i = 0; i < (*players).size(); i++) {

				if (athletes[(*players)[i]]->numberOfMedals() > 1) {
					pairs.push_back(pair<string, Athlete*>(athletes[(*players)[i]]->getCountry(), athletes[(*players)[i]]));///fali zemlja
					cout <<athletes[(*players)[i]]->getCountry()<<" : "<< *(athletes[(*players)[i]]) << "\n";
				}
				//auto it = athletes.find((*players)[i]);
				//if (it != athletes.end())
					//cout << events[i]->getMark() << "\n";
			}
		}
	}

	return pairs;
}

void Aplication::youngest10Champs() {

	vector<Athlete*> youngs;

	for (auto iter = athletes.begin(); iter != athletes.end(); ++iter) {

		int num = (*iter).second->winOnFirst();
		if (num != -1)youngs.push_back((*iter).second);//youngs[num] = (*iter).second;
	}

	std::sort(youngs.begin(), youngs.end(), [](Athlete* a, Athlete* b)
		{
			return (*a).getYears() < (*b).getYears();
		});

	int number = 10;
	cout << "Res:\n";
	for (int i = 0; i < number; i++) {		
			cout << *(youngs[i]) << "\n";
		
	}
}


void Aplication::writeTeams() {

	for (auto i = teams.begin(); i != teams.end(); ++i) {
		cout << *((*i).second);
	}
}

Aplication::~Aplication() {
	for (auto i = events.begin(); i != events.end(); ++i) {
		delete* i;
	}

	for (auto i = athletes.begin(); i != athletes.end(); ++i) {
		delete (*i).second;
	}

	for (auto i = teams.begin(); i != teams.end(); ++i) {
		delete (*i).second;
	}

	borders.clear();
}
