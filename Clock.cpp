    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <cmath>
    using namespace std;

    class Clock {
    private:
        int hours;
        int minutes;
        int seconds;

        void normalizeTime() {
            if (seconds >= 60) {
                minutes += seconds / 60;
                seconds %= 60;
            }
            if (minutes >= 60) {
                hours += minutes / 60;
                minutes %= 60;
            }
            hours %= 24;
        }

    public:
        Clock() : hours(0), minutes(0), seconds(0) {}

        Clock(int h, int m, int s) {
            setTime(h, m, s);
        }

        void setTime(int h, int m, int s) {
            hours = (h >= 0 && h < 24) ? h : 0;
            minutes = (m >= 0 && m < 60) ? m : 0;
            seconds = (s >= 0 && s < 60) ? s : 0;
            normalizeTime();
        }

        void incrementTime(int h, int m, int s) {       
            hours += h;
            minutes += m;
            seconds += s;
            normalizeTime();
        }

        string getTime() const {
            ostringstream timeStream;
            timeStream << setw(2) << setfill('0') << hours << ":"
                    << setw(2) << setfill('0') << minutes << ":"
                    << setw(2) << setfill('0') << seconds;
            return timeStream.str();
        }

        bool isEqual(const Clock& other) const {
            return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
        }

        string compareTime(const Clock& other) const {
            int totalSeconds1 = hours * 3600 + minutes * 60 + seconds;
            int totalSeconds2 = other.hours * 3600 + other.minutes * 60 + other.seconds;

            if (totalSeconds1 == totalSeconds2)
                return "Both clocks show the same time.";

            int diff = abs(totalSeconds1 - totalSeconds2);
            int diffHours = diff / 3600;
            int diffMinutes = (diff % 3600) / 60;
            int diffSeconds = diff % 60;

            ostringstream result;
            if (totalSeconds1 > totalSeconds2)
                result << "Clock 1 is ahead by " << diffHours << ":" << diffMinutes << ":" << diffSeconds << ".";
            else
                result << "Clock 2 is ahead by " << diffHours << ":" << diffMinutes << ":" << diffSeconds << ".";

            return result.str();
        }
    };

    int main() {
        Clock clock1, clock2;
        int h, m, s;

        cout << "Set time for Clock 1 (hh mm ss): ";
        cin >> h >> m >> s;
        clock1.setTime(h, m, s);

        cout << "Set time for Clock 2 (hh mm ss): ";
        cin >> h >> m >> s;
        clock2.setTime(h, m, s);

        cout << "Clock 1: " << clock1.getTime() << endl;
        cout << "Clock 2: " << clock2.getTime() << endl;

        cout << "\nIncrement Clock 1 (hh mm ss): ";
        cin >> h >> m >> s;
        clock1.incrementTime(h, m, s);
        cout << "Clock 1 after increment: " << clock1.getTime() << endl;

        cout << "\nIncrement Clock 2 (hh mm ss): ";
        cin >> h >> m >> s;
        clock2.incrementTime(h, m, s);
        cout << "Clock 2 after increment: " << clock2.getTime() << endl;

        cout << "\nComparison Result: " << clock1.compareTime(clock2) << endl;

        cout << "\nExiting program..." << endl;
        return 0;
    }
