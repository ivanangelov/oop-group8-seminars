#ifndef CALENDAR_H
#define CALENDAR_H

#include <vector>
#include <string>
#include "Event.h"
#include "Date.h"

class Calendar
{
    public:
        Calendar(std::string name="<New Calendar>");
        Calendar(const Calendar& other);
        Calendar& operator=(const Calendar& other);
        ~Calendar();
        std::string getName() const;
        void rename(const std::string&);
        void addEvent(const Date&, int, int, std::string="Event", std::string="");
        void addWeeklyEvent(const Date&, int, int, int, std::string="Weekly Event", std::string="");
        bool isFree (const Date& date, int hour) const;
        friend std::ostream& operator<< (std::ostream&, const Calendar&);
    protected:
    private:
        std::string name;
        std::vector<Event*> events;
        void init(const Calendar& other);
        void destroy();
};

#endif // CALENDAR_H
