#include <iostream>
using namespace std;
#include "Event.h"
#include "Aplication.h"


void printMenu() {
	cout << "\n";
	cout << "----------------------------------\n";
	cout << "Unesite operaciju: \n";
	cout << "1.Ucitaj podatke \n";
	cout << "2.Osnovne metrike \n";
	cout << "3.Napredne manipulacije \n";
	cout << "4.Kraj \n";
}

void printBasicMet() {
	cout << "\n";
	cout << "----------------------------------\n";
	cout << "1.Broj ucesnika na svim dogadjajima na Olimpijskim igrama\n";
	cout << "2.Ukupan broj disciplina na Olimpijskim igrama\n";
	cout << "3.Prosecnu visinu svih sportista (ukoliko postoji podatak o visini sportiste)\n";
	cout << "4.Prosecnu težinu svih sportista (ukoliko postoji podatak o težini sportiste)\n";
	cout << "5.Nazad\n";
}

int main(int argc, char* argv[])
{
	//Event *e = new Event("1992 Summer!Barcelona!Football!Football Men's Football!Team!Spain!['401', '2629', '3332', '10478', '35012', '43467', '48056', '59680', '66935', '71402', '72154', '94995', '112897', '112996', '121042', '126362', '126587']!Gold");
	//printf("%s", *e);
	//cout << *e;
	int mod = 0;
	bool kraj = false;
	string comand = "";
	Aplication& a = *(Aplication::getInstance());;


	while (!kraj) {

		printMenu();
		cin >> mod;
		
		if (mod == 1) {
			cout << "\nZadaj godinu?\n";
			cin >> comand;
			if (stoi(comand) != 0) {
				//a = *(Aplication::getInstance());
				a.readEvents("C:\\Users\\User\\Desktop", stoi(comand));
				a.writeEvents();
				a.writeAthletes();
			}
			else {
				//a = *(Aplication::getInstance());
				a.readEvents("C:\\Users\\User\\Desktop");
				a.writeEvents();
				a.writeAthletes();
			}
		}		
		else if (mod == 2) {
			printBasicMet();
			cin >> comand;
			bool filterEnd = false;
			int filter = 0;
			string p1, p2, p4, p5;
			p1 = p2 = p4 = p5 = "";
			int p3 = 0;

			while (!filterEnd) {
				cout << "Filter?\n";
				cout << "1. Na osnovu zadatog sporta\n";
				cout << "2. Na osnovu drzave za koju nastupa takmicar\n";
				cout << "3. Na osnovu godine odrzavanja Olimpijskih igara\n";
				cout << "4. Na osnovu tipa događaja (individualan ili timski)\n";
				cout << "5. Na osnovu osvojene medalje (zlatna, srebrna, bronzana ili bez medalje)\n";
				cout << "6. Dosta\n";
				cin >> filter;

				if (filter == 1) {
					cout << "Sport:\n";
					cin >> p1;
				}
				else if (filter == 2) {
					cout << "Drzava:\n";
					cin >> p2;
				}
				else if (filter == 3) {
					cout << "Godina:\n";
					cin >> p3;
				}
				else if (filter == 4) {
					cout << "Tip dogadjaja:\n";
					cin >> p4;
				}
				else if (filter == 5) {
					cout << "Medalja:\n";
					cin >> p5;
				}
				else {
					filterEnd = true;
				}

			}

			if (stoi(comand) == 1) {
				cout<<a.numberOfAthletes(p1, p2, p3, p4, p5)<<"\n";
			}
			else if (stoi(comand) == 2) {
				cout<<a.numberOfDisciplines(p1, p2, p3, p4, p5)<<"\n";
			}
			else if (stoi(comand) == 3) {
				cout<<a.averageAthletesHeight(p1, p2, p3, p4, p5)<<"\n";
			}
			else {
				cout<<a.averageAthletesWheight(p1, p2, p3, p4, p5)<<"\n";
			}
		}
		else if (mod==3) {

			cout << "\n----------------------\n";
			cout << "1.Određivanje broja različitih sportova u kojima je zadata država osvojila barem jednu medalju\n";
			cout << "2.Odrađivanje tri najbolje države po uspehu na zadatim Olimpijskim igrama\n";
			cout << "3.Određivanje država koje su na barem jednim Olimpijskim igrama ostvarile najbolji uspeh\n";
			cout << "4.Određivanje deset najmlađih učesnika Olimpijskih igara koji su osvojili medalju na svom prvom ucescu\n";
			cout << "5.Dohvatanje svih parova država\n";
			cout << "6.Određivanje svih sportista koji su učestvovali na zadatom paru Olimpijskih igara\n";
			cout << "7.Dohvatanje svih timova koje je zadata država imala na zadatim igrama\n";
			cout << "8.Određivanje svih gradova u kojima su Olimpijske igre održane barem jednom\n";

			cin >> comand;

			if (stoi(comand)==1) {

				cout << "Drzava:\n";
				string country;
				cin >> country;
				cout<<a.numberOfSportsByCountyWithMedal(country)<<"\n";
			}
			else if (stoi(comand)==2) {

				cout << "Godina:\n";
				int yr;
				cin >> yr;
				cout << "Tip igara:\n";
				string typ;
				cin >> typ;
				a.big3byOG(yr,typ);
			}
			else if (stoi(comand)==3) {
				a.bestCountryEveryYear();
			}
			else if (stoi(comand)==4) {
				a.youngest10Champs();
			}
			else if (stoi(comand)==5) {
				a.getPairs();
			}
			else if (stoi(comand)==6) {

				cout << "Godina:\n";
				int yr;
				cin >> yr;
				cout << "Tip igara:\n";
				string typ;
				cin >> typ;

				cout << "Godina:\n";
				int yr2;
				cin >> yr2;
				cout << "Tip igara:\n";
				string typ2;
				cin >> typ2;

				a.pairOG(yr, typ, yr2, typ2);
			}
			else if (stoi(comand)==7) {
				cout << "Drazava:\n";
				string cty;
				cin >> cty;
				cout << "Godina:\n";
				int yr;
				cin >> yr;
				cout << "Tip igara:\n";
				string typ;
				cin >> typ;

				a.getTeam(cty, yr, typ);
			}
			else if (stoi(comand)==8) {
				a.allCityesOG();
			}
		
		}
		else{
			delete& a;
			kraj = true;
		}

		
			
	}
	


	//Aplication& a = *(Aplication::getInstance());
	//a.readEvents("C:\\Users\\User\\Desktop");
	//a.writeEvents();
	//a.writeAthletes();

	///a.filterData(, , 0, , );
	//cout << a.numberOfAthletes("","",1992,"","Bronze") <<"\n";
	//cout << a.averageAthletesHeight("","",0,"Individual") << "\n";
	//cout << a.averageAthletesWheight("Football") << "\n";
	//cout << a.numberOfDisciplines("","",0,"","Gold") << "\n";
	//a.sort("AJMO");
	//cout << a.numberOfSportsByCountyWithMedal("United States");
	//cout << a.numberOfAthletes() << "\n";
	//cout << a.numberOfDisciplines() << "\n";
	//cout << a.averageAthletesHeight() << "\n";
	//cout << a.averageAthletesWheight() << "\n";
	//cout << a.numberOfSportsByCountyWithMedal("Unified Team");
	//a.big3byOG(1992,"Summer");
	//a.bestCountryEveryYear();
	//a.allCityesOG();
	//a.writeTeams();
	//a.pairOG(1992,"Summer", 1982,"Summer");
	//a.youngest10Champs();
	//a.getPairs();
	//a.getTeam("Spain",1992,"Summer");
	return 0;
}