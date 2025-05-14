#ifndef CLEANER_H
#define CLEANER_H

#include <string>
#include <ctime>

class Cleaner
{
private:
    std::string cleaner_id;
    float latitude;
    float longitude;
    time_t timestamp_start;
    time_t timestamp_stop;

public:
    Cleaner(const std::string &id, float lat, float lon, const time_t &start, const time_t &stop);
    ~Cleaner();

    std::string getCleanerId() const;
    float getLatitude() const;
    float getLongitude() const;
    time_t getTimestampStart() const;
    time_t getTimestampStop() const;
};

#endif