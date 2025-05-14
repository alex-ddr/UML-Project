#ifndef ADMIN_H
#define ADMIN_H

#include "Responsable.h"

class Admin : public Responsable
{
private:
    /* data */
public:
    Admin(std::string id, std::string nom);
    ~Admin();
};

#endif
