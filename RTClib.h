// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#ifndef _RTCLIB_H_
#define _RTCLIB_H_


class DateTime;
class Time
{
  public:
    Time() {};
    Time(uint8_t hour, uint8_t min, uint8_t sec = 0) : hh(hour), mm(min), ss(sec) {}
    Time(const char* time);
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    DateTime onDate(DateTime);
    DateTime nextOccurence(DateTime);
    DateTime prevOccurence(DateTime);
  protected:
    uint8_t hh, mm, ss;
};

// Simple general-purpose date/time class (no TZ / DST / leap second handling!)
class DateTime {
public:
    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
    DateTime (const char* date, const char* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return time.hour(); }
    uint8_t minute() const      { return time.minute(); }
    uint8_t second() const      { return time.second(); }
    Time getTime() const           { return time; }
    uint8_t dayOfWeek() const;

    // 32-bit times as seconds since 1/1/2000
    long secondstime() const;   
    // 32-bit times as seconds since 1/1/1970
    uint32_t unixtime(void) const;
    int compare (const DateTime&);
    bool operator == (DateTime d) {
        return !compare(d);
    }
    bool operator != (DateTime d) {
        return !!compare(d);
    }
    bool operator < (DateTime d) {
        return compare(d)<0;
    }
    bool operator <= (DateTime d) {
        return compare(d)<1;
    }
    bool operator > (DateTime d) {
        return compare(d)>0;
    }
    bool operator >= (DateTime d) {
        return compare(d)>-1;
    }

protected:
    uint8_t yOff, m, d;
    Time time;
};

// RTC based on the DS1307 chip connected via I2C and the Wire library
class RTC_DS1307 {
public:
    static uint8_t begin(void);
    static void adjust(const DateTime& dt);
    uint8_t isrunning(void);
    static DateTime now();
};

// RTC using the internal millis() clock, has to be initialized before use
// NOTE: this clock won't be correct once the millis() timer rolls over (>49d?)
class RTC_Millis {
public:
    static void begin(const DateTime& dt) { adjust(dt); }
    static void adjust(const DateTime& dt);
    static DateTime now();

protected:
    static long offset;
};

#endif // _RTCLIB_H_
