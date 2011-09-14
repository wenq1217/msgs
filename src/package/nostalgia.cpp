#include "standard.h"
#include "skill.h"
#include "wind.h"
#include "client.h"
#include "carditem.h"
#include "engine.h"
#include "nostalgia.h"
#include "standard-skillcards.h"

class MoonSpearSkill: public WeaponSkill{
public:
    MoonSpearSkill():WeaponSkill("moon_spear"){
        events << CardFinished << CardResponsed;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(player->getPhase() != Player::NotActive)
            return false;

        CardStar card = NULL;
        if(event == CardFinished){
            CardUseStruct card_use = data.value<CardUseStruct>();
            card = card_use.card;
        }else if(event == CardResponsed)
            card = data.value<CardStar>();

        if(card == NULL || !card->isBlack())
            return false;

        Room *room = player->getRoom();
        room->askForUseCard(player, "slash", "@moon-spear-slash");

        return false;
    }
};

class MoonSpear: public Weapon{
public:
    MoonSpear(Suit suit = Card::Diamond, int number = 12)
        :Weapon(suit, number, 3){
        setObjectName("moon_spear");
        skill = new MoonSpearSkill;
    }
};

class SuperGuanxing: public PhaseChangeSkill{
public:
    SuperGuanxing():PhaseChangeSkill("super_guanxing"){
        frequency = Frequent;
    }

    virtual bool onPhaseChange(ServerPlayer *zhuge) const{
        if(zhuge->getPhase() == Player::Start && zhuge->askForSkillInvoke(objectName()))
        {
            Room *room = zhuge->getRoom();
            room->playSkillEffect("super_guanxing");

            room->doGuanxing(zhuge, room->getNCards(5, false), false);
        }
        return false;
    }
};

class SuperZhiheng: public ViewAsSkill{
public:
    SuperZhiheng():ViewAsSkill("super_zhiheng"){}

    virtual bool viewFilter(const QList<CardItem *> &, const CardItem *) const{
        return true;
    }

    virtual const Card *viewAs(const QList<CardItem *> &cards) const{
        if(cards.isEmpty())
            return NULL;

        ZhihengCard *zhiheng_card = new ZhihengCard;
        zhiheng_card->addSubcards(cards);

        return zhiheng_card;
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return player->usedTimes("ZhihengCard") < (player->getLostHp() + 1);
    }
};

NostalgiaPackage::NostalgiaPackage()
    :Package("nostalgia")
{
    General *wuxing_zhuge = new General(this, "wuxingzhuge", "shu", 3);
    wuxing_zhuge->addSkill(new SuperGuanxing);
    wuxing_zhuge->addSkill("kongcheng");
    wuxing_zhuge->addSkill("#kongcheng-effect");

    General *zhiba_sunquan = new General(this, "zhibasunquan$", "wu", 4);
    zhiba_sunquan->addSkill(new SuperZhiheng);
    zhiba_sunquan->addSkill("jiuyuan");
}

NostalgiaCardPackage::NostalgiaCardPackage()
    :Package("nostalgia_cards")
{
    Card *moon_spear = new MoonSpear;
    moon_spear->setParent(this);

    type = CardPack;
}

ADD_PACKAGE(Nostalgia);
ADD_PACKAGE(NostalgiaCard);
