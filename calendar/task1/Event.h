#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
using namespace std;
#include "Date.h"
class Event
{
public:
	Event(const Date&, int, int,
		std::string title = "<Untitled Event>", std::string description = "", std::string place = "");
	virtual ~Event();
	virtual bool isInProgress(const Date&, int) const;
	friend std::ostream& operator<< (std::ostream&, const Event&);
	friend std::istream& operator>> (std::istream&, Event&);
	virtual bool isHappeningAt(string, const Date&, int)const;
	Date getDate()const;
protected:
	Date date;
	int startHour;
	int endHour;
	std::string title;
	std::string description;
	std::string place;
	virtual std::ostream& write(std::ostream& out) const;
};

#endif // EVENT_H
