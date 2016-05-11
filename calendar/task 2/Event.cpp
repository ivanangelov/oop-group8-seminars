#include "Event.h"
#include <string>
#include <iostream>
#include "Calendar.h"
#include "Date.h"

Event::Event(const Date& date, int start, int end,
	std::string title, std::string description, std::string place)
	:date(date), startHour(start), endHour(end), title(title), description(description), place(place)
{ }

Event::~Event() {}

bool Event::isInProgress(const Date& when, int hour) const {
	return date == when && hour >= startHour && hour < endHour;
}

std::ostream& Event::write(std::ostream& out) const {
	out << title << "@" << date <<
		" (from " << startHour << "h to " << endHour << "h)" << "in: " << place << std::endl;
	out << description << std::endl;

	return out;
}

std::ostream& operator<< (std::ostream& out, const Event& e) {
	return e.write(out);
}

std::istream& operator>> (std::istream& in, Event& e) {
	in >> e.title;
	in >> e.date;
	in >> e.startHour >> e.endHour;
	in >> e.description;
	in >> e.place;
	return in;
}
bool Event::isHappeningAt(string mqsto, const Date& when, int hour)const{
	return date == when && hour >= startHour && hour <= endHour;
}
bool Event::isHappeningAtV2(string mqsto, const Date& when)const{
	return date == when;
}
Date Event::getDate()const{
	return date;
}
int Event::getStartHour()const{
	return startHour;
}
int Event::getEndHour() const{
	return endHour;
}
string Event::getPlace()const{
	return place;
}
int Event::getTime()const{
	return  endHour - startHour;
}
int Event::getTheYear()const{
	return date.getYear();
}

