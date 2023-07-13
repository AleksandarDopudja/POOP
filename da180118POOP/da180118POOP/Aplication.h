#pragma once

#include <iostream>
#include <regex>
#include "Event.h"
#include "Athlete.h"
#include "Team.h"
#include <vector>
#include <fstream>
#include <map>

class Aplication
{
	static Aplication *instance;
	map<int, Athlete*> athletes;
	map<string, Team*> teams;
	vector<Event*> events;
	vector<int> borders;
	Aplication() {}

public:
	~Aplication();

	void readAthletes(string directory);
	void readEvents(string directory, int year = 0);
	static Aplication* getInstance() {
		if (instance == nullptr) {
			instance = new Aplication();
		}
		return instance;
	}
	void writeEvents();
	void writeAthletes();
	void writeTeams();
	int numberOfAthletes(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");
	int numberOfDisciplines(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");
	double averageAthletesHeight(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");
	double averageAthletesWheight(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");
	void filterData(string sport = "", string country = "", int year = 0, string typeEvent = "", string typeMedal = "");
	int numberOfSportsByCountyWithMedal(string county);
	string big3byOG(int year, string season, bool mod = false);
	void bestCountryEveryYear();
	void allCityesOG();
	void pairOG(int yr1,string tyOG1,int y2, string tyOG2);
	vector<Team*> getTeam(string country, int yr, string tyOG);
	vector<pair<string, Athlete*>> getPairs();
	void youngest10Champs();
	
};
