#ifndef PROVIDER_H
#define PROVIDER_H

class Provider
{
private:
    long provider_id;

public:
    Provider(long id);
    ~Provider();

    long getProviderId() const;
};

#endif