#ifndef PROVIDER_H
#define PROVIDER_H

class Provider
{
    private:
        long providerId;

    public:
        // Constructeurs
        Provider() {}
        Provider(long id) : providerId(id) {}

        // Destructeur
        ~Provider() {}

        // Getters
        long getProviderId() const {return providerId;}

        // Setters
        void setProviderId(const long& providerId) {this->providerId=providerId;}
};

#endif