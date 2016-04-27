#include "Event.h"
#include <string>
#include <iostream>
Event::Event(const Date& date, int start, int end,
              std::string title, std::string description)
                :date(date),startHour(start),endHour(end), title(title),description(description)
{ }

Event::~Event () {}

bool Event::isInProgress(const Date& when, int hour) const {
    return date == when && hour >= startHour && hour < endHour;
}

std::ostream& Event::write(std::ostream& out) const {
    out << title << "@" << date <<
        " (from " << startHour << "h to " << endHour << "h)" << std::endl;
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
    return in;
}
