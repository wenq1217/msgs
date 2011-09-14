#ifndef NOSTALGIA_H
#define NOSTALGIA_H

#include "package.h"
#include "card.h"

class NostalgiaPackage: public Package{
    Q_OBJECT

public:
    NostalgiaPackage();
};

class NostalgiaCardPackage: public Package{
    Q_OBJECT

public:
    NostalgiaCardPackage();
};



#endif // NOSTALGIA_H
