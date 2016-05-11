#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include "Event.h"
#include "Calendar.h"
#include "Date.h"

using namespace std;

class TimeLord{
private:
	string nameTl;
	vector <Calendar*> archives;
public:
	void init(const TimeLord& other){
		nameTl = other.nameTl;
		archives = other.archives;
		for (unsigned int i = 0; i < archives.size(); i++){
			archives[i] = new Calendar(*archives[i]);
		}
	}
	void destroy(){
		for (unsigned int i = 0; i < archives.size(); i++){
			delete  archives[i];
		}
	}
	TimeLord(string name){
		nameTl = name;
	}
	TimeLord(const TimeLord& other){
		init(other);
	}
	TimeLord& operator=(const TimeLord& other){
		if (this != &other){
			destroy();
			init(other);
		}
		return *this;
	}
	~TimeLord(){
		destroy();
	}
	string getName()const{
		return nameTl;
	}
	void newCalendar(string name){
		Calendar* e = new Calendar(name);
		archives.push_back(e);
	}
	void newEvent(const Date& date, int start, int end, string title, string description, string place){
		archives.back()->addEvent(date, start, end, title, description, place);
	}
	Calendar allArchives(){
		Calendar* all = new Calendar(*archives[0]);
		for (unsigned int i = 1; i < archives.size(); i++){
			*all += *archives[i];
		}
		return *all;
	}
	bool canVisit(string mqsto, const Date& when, int hour){
		for (unsigned int i = 0; i < archives.size(); i++){
			if (archives[i]->hasEventAt(mqsto, when, hour)){
				return false;
			}
		}
		return true;
	}
};
int main(){
	TimeLord lord1("ivan");
	lord1.newCalendar("Calendar1");
	lord1.newEvent(Date(2016, 4, 1), 18, 19, "First Event", "Study time!", "Home");
	lord1.newEvent(Date(2016, 3, 31), 9, 11, "Second Event", "Nap time!", "Home");
	lord1.newEvent(Date(2009, 4, 8), 14, 18, "Third Event", "Work!", "Work");
	lord1.newCalendar("Calendar2");
	lord1.newEvent(Date(2016, 3, 31), 9, 11, "Fourth event", "Movie time", " ");
	lord1.newEvent(Date(2016, 3, 31), 9, 11, "Fifth event", "Enjoy", "Out");
	lord1.newEvent(Date(2016, 2, 1), 9, 11, "Sixth event", "Workout", "Gym");

	cout << "All events of the time lord:" << endl;
	cout << lord1.allArchives() << endl;

	if (lord1.canVisit("fmi", Date(2016, 4, 1), 10) == 1) cout << "Free to visit!" << endl;
	else cout << "Not free to visit!" << endl;


	system("pause");
	return 0;
}