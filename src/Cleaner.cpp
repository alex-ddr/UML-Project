#include "Cleaner.h"
#include <iostream>

Cleaner::Cleaner(const std::string &id, float lat, float lon, const time_t &start, const time_t &stop)
    : cleaner_id(id), latitude(lat), longitude(lon), timestamp_start(start), timestamp_stop(stop) {}

Cleaner::~Cleaner() {}

std::string Cleaner::getCleanerId() const
{
    return cleaner_id;
}

float Cleaner::getLatitude() const
{
    return latitude;
}

float Cleaner::getLongitude() const
{
    return longitude;
}

time_t Cleaner::getTimestampStart() const
{
    return timestamp_start;
}

time_t Cleaner::getTimestampStop() const
{
    return timestamp_stop;
}