#ifndef CLEANER_H
#define CLEANER_H

#include <string>
#include <ctime>

class Cleaner
{
    private:
        std::string cleanerId;
        float latitude;
        float longitude;
        time_t timestampStart;
        time_t timestampStop;

    public:
        // Constructeurs
        Cleaner(const std::string &id, float lat, float lon, const time_t &start, const time_t &stop)
            : cleanerId(id), latitude(lat), longitude(lon), timestampStart(start), timestampStop(stop) {}
        Cleaner() {}

        // Destructeur
        ~Cleaner() {}

        // Getters
        std::string getCleanerId() const {return cleanerId;}
        float getLatitude() const {return latitude;}
        float getLongitude() const {return longitude;}
        time_t getTimestampStart() const {return timestampStart;}
        time_t getTimestampStop() const {return timestampStop;}

        // Setters
        void setCleanerId(const std::string& cleanerId)  { this->cleanerId = cleanerId; } 
        void setLatitude(const float latitude)  { this->latitude = latitude; }
        void setLongitude(const float longitude) { this->longitude = longitude; } 
        void setTimestampStart(const time_t& timestampStart) { this->timestampStart = timestampStart; } 
        void setTimestampStop(const time_t& timestampStop)  { this->timestampStop = timestampStop; }

};

#endif