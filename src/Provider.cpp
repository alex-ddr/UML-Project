#include "Provider.h"

Provider::Provider(long id) : provider_id(id) {}

Provider::~Provider() {}

long Provider::getProviderId() const
{
    return provider_id;
}