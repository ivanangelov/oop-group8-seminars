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
	TimeLord(std::string name1){
		nameTl = name1;
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
	void newCalendar(std::string name){
		Calendar* e = new Calendar(name);
		archives.push_back(e);
	}
	void newEvent(const Date& date, int start, int end, std::string title, std::string description, std::string place){
		archives.back()->addEvent(date, start, end, title, description, place);
	}
	Calendar allArchives(){
		Calendar* all = new Calendar(*archives[0]);
		for (unsigned int i = 1; i < archives.size(); i++){
			*all += *archives[i];
		}
		return *all;
	}
	bool canVisit(std::string mqsto, const Date& when, int hour){
		for (unsigned int i = 0; i < archives.size(); i++){
			if (archives[i]->hasEventAt(mqsto, when, hour)){
				return false;
			}
		}
		return true;
	}
	bool canVisitV2(std::string mqsto, const Date& when){
		for (unsigned int i = 0; i < archives.size(); i++){
			if (archives[i]->hasEventAtV2(mqsto, when)){
				return false;
			}
		}
		return true;
	}
	int numEvents()const{
		int counter = 0;
		for (int i = 0; i < archives.size(); i++){
			counter = counter + archives[i]->getSize();
		}
		return counter;
	}
	Date earliestVisitedDate()const{
		int tmpDatee = 0;
		for (int i = 0; i < archives.size() - 1; i++){
			if (archives[i]->earliestVisitedDatee() > archives[i + 1]->earliestVisitedDatee()){
				tmpDatee = i;
			}
		}
		return archives[tmpDatee]->earliestVisitedDatee();
	}
	int timeSpentInCenturyy(int century) const{
		int counterCentury = 0;
		for (int i = 0; i < archives.size(); i++){
			counterCentury += archives[i]->timeSpentInSentury(century);
		}
		return counterCentury;
	}
	string readTl()const{
		return nameTl;
	}
	void printTimeLord() const {
		cout << "Name: " << nameTl << endl;
		cout << "Archives: " << endl;
		for (unsigned int i = 0; i < archives.size(); i++) {
			cout << *archives[i] << endl;
		}
	}
};
class Competition{
private:
protected:
	std::string place;
	Date datee;
	vector <TimeLord*> participants;
public:
	void init(const Competition& other){
		place = other.place;
		datee = other.datee;
		participants = other.participants;
		for (unsigned int i = 0; i < participants.size(); i++){
			participants[i] = new TimeLord(*participants[i]);
		}
	}
	void destroy(){
		for (unsigned int i = 0; i < participants.size(); i++){
			delete  participants[i];
		}
	}
	Competition(string place1, Date& date1){
		place = place1;
		datee = date1;
	}
	Competition(const Competition& other){
		init(other);
	}
	Competition& operator=(const Competition& other){
		if (this != &other){
			destroy();
			init(other);
		}
		return *this;
	}
	~Competition(){
		destroy();
	}
   bool registerr(TimeLord& Timelord){
		if (Timelord.canVisitV2(place, datee)){
			TimeLord* lord = new TimeLord(Timelord);
			participants.push_back(lord);
			return true;
		}
		else {
			return false;
		}
	}
	int numParticipants()const{
		return participants.size();
	}
	void printCompetition(){
		for (int i = 0; i < participants.size(); i++){
			participants[i]->printTimeLord();
		}
	}
	virtual TimeLord winner(){
		int randomIndex = rand() % participants.size();
		if (participants.size() == 0) return "None!";
		return *participants[randomIndex];
	}
};
class MostEvents : public Competition{
private:
public:
	MostEvents(string place1, Date& date1) : Competition(place1, date1)
	{

		place = place1;
		datee = date1;
	}
	MostEvents(const MostEvents& other) : Competition(other)
	{
		init(other);
	}
	MostEvents& operator = (const MostEvents& other)
	{
		if (this != &other)
		{
			Competition:: operator = (other);
			destroy();
			init(other);
		}
		return *this;
	}
	TimeLord winner(){
		int tmp = 0;
		if (participants.size() == 0) return "Noone!";
		for (int i = 0; i < participants.size() - 1; i++){
			if (participants[i]->numEvents()>participants[i + 1]->numEvents()){
				tmp = i;
			}
		}
		return *participants[tmp];
	}
};
class EarliestDate : public Competition{
public:
	TimeLord winner(){
		if (participants.size() == 0) return "Noone!";
		int tmp = 0;
		for (int i = 0; i < participants.size() - 1; i++){
			if (participants[i]->earliestVisitedDate()>participants[i + 1]->earliestVisitedDate()){
				tmp = i;
			}
		}
		return *participants[tmp];
	}
	EarliestDate(string place1, Date& date1) : Competition(place1, date1)
	{

		place = place1;
		datee = date1;
	}
	EarliestDate(const MostEvents& other) : Competition(other)
	{
		init(other);
	}
	EarliestDate& operator = (const EarliestDate& other)
	{
		if (this != &other)
		{
			Competition:: operator = (other);
			destroy();
			init(other);
		}
		return *this;
	}
};
class MostTime15Cent : public Competition{
public:

	TimeLord winner(){
		int tmp = 0;
		for (int i = 0; i < participants.size() - 1; i++){
			if (participants.size() == 0) return "Noone!";
			if (participants[i]->timeSpentInCenturyy(15)>participants[i + 1]->timeSpentInCenturyy(15)){
				tmp = i;
			}
		}
		return *participants[tmp];
	}
	MostTime15Cent(string place1, Date& date1) : Competition(place1, date1)
	{

		place = place1;
		datee = date1;
	}
	MostTime15Cent(const MostEvents& other) : Competition(other)
	{
		init(other);
	}
	MostTime15Cent& operator = (const MostTime15Cent& other)
	{
		if (this != &other)
		{
			Competition:: operator = (other);
			destroy();
			init(other);
		}
		return *this;
	}
};
int main(){
	Competition a1("Home", Date(2016, 4, 1));

	TimeLord lord1("ivan");
	lord1.newCalendar("Calendar1");
	lord1.newEvent(Date(1623, 4, 1), 18, 19, "First Event", "Study time!", "Home");
	lord1.newEvent(Date(1643, 3, 31), 9, 11, "Second event", "Nap time!", "noooooooooooooooooooooooooooooooooo");
	TimeLord lord2("dimcho");
	lord2.newCalendar("Calendar2");
	lord2.newEvent(Date(1641, 5, 1), 5, 6, "Third Event", "Study time!", "Home");
	lord2.newEvent(Date(1638, 2, 31), 9, 11, "Fourth event", "Nap time!", "noooooooooooooooooooooooooooooooooo");
	TimeLord lord3("petko");
	lord3.newCalendar("Calendar3");
	lord3.newEvent(Date(1685, 5, 19), 20, 23, "Sixth Event", "Study time!", "Home");
	TimeLord lord4("gosho");
	lord4.newCalendar("Calendar4");
	lord4.newEvent(Date(1945, 5, 19), 20, 23, "Seventh Event", "Study time!", "Home");


	cout << a1.registerr(lord1) << endl;
	cout << a1.registerr(lord2) << endl;;
	cout << a1.registerr(lord3) << endl;
	cout << a1.registerr(lord4) << endl;
	cout << "Number of participants: " << a1.numParticipants() << endl;
	cout << "The winner is: "; a1.winner().printTimeLord();

	MostEvents a2("outside", Date(2013, 5, 15));
	cout << a2.registerr(lord1) << endl;
	cout << a2.registerr(lord2) << endl;
	cout << a2.registerr(lord3) << endl;
	cout << "Number of participants: " << a2.numParticipants() << endl;
	cout << "The winner is: ";
	a2.winner().printTimeLord();

	EarliestDate a3("outside", Date(2013, 5, 15));
	cout << a3.registerr(lord1) << endl;
	cout << a3.registerr(lord2) << endl;
	cout << a3.registerr(lord3) << endl;
	cout << "Number of participants: " << a3.numParticipants() << endl;
	cout << "The winner is: ";
	a3.winner().printTimeLord();

	MostTime15Cent a4("outside", Date(2013, 5, 15));
	cout << a4.registerr(lord1) << endl;
	cout << a4.registerr(lord2) << endl;
	cout << a4.registerr(lord3) << endl;
	cout << "Number of participants: " << a4.numParticipants() << endl;
	cout << "The winner is: ";
	a4.winner().printTimeLord();

	system("pause");
	return 0;
}