#include <iostream>
#include <regex>
#include "Event.h"
#include "Athlete.h"
#include <vector>
#include <fstream>
#include <map>

class Team {
	string uniqueMark;
	string country;
	string sport;
	vector<int> players;
	string discipline = "";

	vector<pair<int, string>> medalsWon;

public:
	Team(string s, string dis) {

		discipline = dis;
		uniqueMark = s;

		string delim = ",";
		string str = uniqueMark;

		//teams.insert(pair<string, Team*>(str, new Team(str)));

		size_t pos = 0;
		string token;

		pos = str.find(delim);
		token = str.substr(2, pos - 2);

		//athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
		players.push_back(stoi(token));
		str.erase(0, pos + delim.length());

		while ((pos = str.find(delim)) != std::string::npos)
		{
			token = str.substr(2, pos); // store the substring   
			//cout << token1 << endl;
			//athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
			players.push_back(stoi(token));
			str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
		}

		token = str.substr(2, token.length() - 2);
		//athletes.insert(pair<int, Athlete*>(stoi(token), newAtl));
		players.push_back(stoi(token));
	}

	~Team() {
		players.clear();
	}

	int numberOfPlayers() {

		int number = 0;
		string delim = ",";
		string str = uniqueMark;

		size_t pos = 0;
		string token;

		while ((pos = str.find(delim)) != std::string::npos)
		{
			token = str.substr(2, pos); // store the substring   
			//cout << token1 << endl;
			number++;
			str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
		}

		return ++number;
	}

	vector<int>* allPlayers() {
		return &players;
	}

	string getDiscipline() {
		return discipline;
	}

	void addMedal(int year, string medal) {
		medalsWon.push_back(pair<int, string>(year, medal));
	}

	int numberOfMedals() {
		return medalsWon.size();
	}

	friend ostream& operator<< (ostream& outs, const Team& obj) {

		string out = "";
		for (auto i = obj.players.begin(); i != obj.players.end(); ++i) {
			out += to_string(*i) + " ";
		}
		return outs << out << "\n";
	}

};