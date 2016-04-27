#include <iostream>
#include "Event.h"
#include "WeeklyEvent.h"
#include "Calendar.h"
#include "Date.h"
int main()
{
    Calendar c("My Calendar");
    c.addEvent(Date(2016, 3, 31), 9, 11, "First");
    c.addEvent(Date(2016, 4, 1), 18, 19, "Second Event", "Study time!");
    c.addWeeklyEvent(Date(2016, 2, 25), 9, 11, 15, "OOP Seminar", "Seminar with group 8");
    std::cout << "Current calendar state: " << std::endl << c;

    std::cout << std::endl;
    Date d(2016, 4, 28);
    int hour = 10;
    std::cout << "Are we free on " << d << "@" << hour << "h? " << std::endl;
    // Try removing "virtual" from Event.h and see how the answer changes
    std::cout << (c.isFree(d, hour) ? "Yes" : "No" )<< std::endl;
    std::cout << std::endl;
    std::cout << "Virtual Event::write example" << std::endl;
    Event e(Date(2016, 5, 1), 12, 14, "Easter lunch");
    WeeklyEvent we(Date(2016, 5, 7), 9, 10, 50, "5km run", "See 5kmrun.bg for more info");
    std::cout << e;
    // Note we do not have a separate friend operator<< for WeeklyEvent
    // since Event::write is a virtual method, the friend operator<< for Event
    // will use WeeklyEvent::write when called with a WeeklyEvent parameter
    std::cout << we;

    return 0;
}
