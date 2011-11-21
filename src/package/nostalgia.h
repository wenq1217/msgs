#ifndef NOSTALGIA_H
#define NOSTALGIA_H

#include "package.h"
#include "card.h"

class SuperFanjianCard: public SkillCard{
    Q_OBJECT

public:
    Q_INVOKABLE SuperFanjianCard();
    virtual void onEffect(const CardEffectStruct &effect) const;
};

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
