#include "sp-package.h"
#include "firepackage.h"
#include "mountainpackage.h"
#include "thicket.h"
#include "wind.h"
#include "general.h"
#include "skill.h"
#include "standard-skillcards.h"
#include "carditem.h"
#include "engine.h"
#include "standard.h"

class Yongsi: public TriggerSkill{
public:
    Yongsi():TriggerSkill("yongsi"){
        events << DrawNCards << PhaseChange;
        frequency = Compulsory;
    }

    int getKingdoms(ServerPlayer *yuanshu) const{
        QSet<QString> kingdom_set;
        Room *room = yuanshu->getRoom();
        foreach(ServerPlayer *p, room->getAlivePlayers()){
            kingdom_set << p->getKingdom();
        }

        return kingdom_set.size();
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *yuanshu, QVariant &data) const{
        Room *room = yuanshu->getRoom();

        if(event == DrawNCards){
            int x = getKingdoms(yuanshu);
            data = data.toInt() + x;

            LogMessage log;
            log.type = "#YongsiGood";
            log.from = yuanshu;
            log.arg = QString::number(x);
            room->sendLog(log);            
            room->playSkillEffect("yongsi");
        }else if(event == PhaseChange && yuanshu->getPhase() == Player::Discard){
            int x = getKingdoms(yuanshu);
            int total = yuanshu->getEquips().length() + yuanshu->getHandcardNum();

            if(total <= x){
                yuanshu->throwAllHandCards();
                yuanshu->throwAllEquips();

                LogMessage log;
                log.type = "#YongsiWorst";
                log.from = yuanshu;
                log.arg = QString::number(total);
                room->sendLog(log);
            }else{
                room->askForDiscard(yuanshu, "yongsi", x, false, true);

                LogMessage log;
                log.type = "#YongsiBad";
                log.from = yuanshu;
                log.arg = QString::number(x);
                room->sendLog(log);
            }
            room->playSkillEffect("yongsi");
        }
        return false;
    }
};

class WeidiViewAsSkill:public ZeroCardViewAsSkill{
public:
    WeidiViewAsSkill():ZeroCardViewAsSkill("weidi"){}

    virtual bool isEnabledAtPlay(const Player *player) const{
        return player->hasSkill("weidi") && player->hasFlag("canjijiang");
    }

    virtual const Card *viewAs() const{
        return new JijiangCard;
    }
};

class Weidijijiang: public PhaseChangeSkill{
public:
    Weidijijiang():PhaseChangeSkill("#weidijijiang"){
    }

    virtual int getPriority() const{
        return 3;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill("weidi");
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        Room *room = target->getRoom();
        bool can_jijiang = false;
        foreach(ServerPlayer *p, room->getAllPlayers()){
            if(p->isLord() && p->hasLordSkill("jijiang") && !target->hasLordSkill("jijiang")){
                can_jijiang = true;
                break;
            }
        }
        if(target->getPhase() == Player::Start && can_jijiang)
            room->setPlayerFlag(target, "canjijiang");
        else if(target->getPhase() == Player::Finish && target->hasFlag("canjijiang"))
            room->setPlayerFlag(target, "-canjijiang");

        return false;
    }
};


class Weidi:public TriggerSkill{
public:
    Weidi():TriggerSkill("weidi"){
        events << CardAsked << CardEffected;

        view_as_skill = new WeidiViewAsSkill;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(player->isLord())
            return false;
        Room *room = player->getRoom();
        QList<ServerPlayer *> all_players = room->getAllPlayers();
        foreach(ServerPlayer *p, all_players){
            if(p->isLord()){
                if(event == CardAsked){
                    QString pattern = data.toString();
                    if(p->hasLordSkill("hujia") && pattern == "jink"){
                        const TriggerSkill *hujia = Sanguosha->getTriggerSkill("hujia");
                        if(hujia && player->askForSkillInvoke("weidi", data)){
                            room->playSkillEffect("weidi");
                            hujia->trigger(event, player, data);
                        }
                    }else if(p->hasLordSkill("jijiang") && pattern == "slash"){
                        const TriggerSkill *jijiang = Sanguosha->getTriggerSkill("jijiang");
                        if(jijiang && player->askForSkillInvoke("weidi", data)){
                            room->playSkillEffect("weidi");
                            jijiang->trigger(event, player, data);
                        }
                    }
                }else if(event == CardEffected){
                    CardEffectStruct effect = data.value<CardEffectStruct>();
                    if(
                        p->hasLordSkill("jiuyuan")
                        && effect.card->inherits("Peach")
                        && effect.from->getKingdom() == "wu"
                        && player != effect.from
                        && player->hasSkill("weidi")
                        && player->hasFlag("dying")
                      )
                    {
                        const TriggerSkill *jiuyuan = Sanguosha->getTriggerSkill("jiuyuan");
                        jiuyuan->trigger(event, player, data);
                        room->getThread()->delay(2000);
                        room->playSkillEffect("weidi");
                    }
                }
            }
        }

        return false;
    }
};

class Weidixueyi: public PhaseChangeSkill{
public:
    Weidixueyi():PhaseChangeSkill("#weidixueyi"){
        frequency = Compulsory;
    }

    virtual bool triggerable(const ServerPlayer *player) const{
        Room *room = player->getRoom();
        QList<ServerPlayer *> all_players = room->getAllPlayers();
        foreach(ServerPlayer *p, all_players){
            if(p->isLord() && p->hasLordSkill("xueyi") && !player->hasLordSkill("xueyi"))
                return player->getPhase() == Player::Discard && player->hasSkill("weidi");
        }
        return false;
    }

    virtual int getPriority() const{
        return 3;// promote the priority in order to avoid the conflict with Yongsi
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        if(player->getPhase() == Player::Discard){
            Room *room = player->getRoom();
            int n = room->getLieges("qun", player).length();
            int weidixueyi = n * 2;
            player->setXueyi(weidixueyi, false);
            room->getThread()->delay(2000);
            room->playSkillEffect("weidi");
        }
        return false;
    }
};

class Weidiruoyu: public PhaseChangeSkill{
public:
    Weidiruoyu():PhaseChangeSkill("#weidiruoyu"){
        frequency = Wake;
    }

    virtual bool triggerable(ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getMark("weidiruoyu") == 0
                && target->getPhase() == Player::Start;
    }

    virtual bool onPhaseChange(ServerPlayer *player) const{
        Room *room = player->getRoom();

        bool can_invoke = true;
        foreach(ServerPlayer *p, room->getAllPlayers()){
            if(player->getHp() > p->getHp()){
                can_invoke = false;
                break;
            }
        }

        bool lord_has_ruoyu = false;
        foreach(ServerPlayer *p, room->getAllPlayers()){
            if(p->isLord() && p->hasLordSkill("ruoyu")){
                lord_has_ruoyu = true;
                break;
            }
        }

        if(can_invoke && lord_has_ruoyu && player->hasSkill("#weidiruoyu") && !player->hasLordSkill("ruoyu")){
            LogMessage log;
            log.type = "#RuoyuWake";
            log.from = player;
            log.arg = QString::number(player->getHp());
            room->sendLog(log);

            room->setPlayerMark(player, "weidiruoyu", 1);
            room->setPlayerProperty(player, "maxhp", player->getMaxHP() + 1);

            RecoverStruct recover;
            recover.who = player;
            room->recover(player, recover);

            room->acquireSkill(player, "jijiang");
            room->playSkillEffect("weidi");
            room->getThread()->delay(2000);
        }

        return false;
    }
};

class Yicong: public DistanceSkill{
public:
    Yicong():DistanceSkill("yicong"){
        frequency = Compulsory;
    }

    virtual int getCorrect(const Player *from, const Player *to) const{
        int correct = 0;
        if(from->hasSkill(objectName()) && from->getHp() > 2)
            correct --;
        if(to->hasSkill(objectName()) && to->getHp() <= 2)
            correct ++;

        return correct;
    }
};

class YicongEffect: public TriggerSkill{
public:
   YicongEffect():TriggerSkill("#yicong-effect"){
       events << HpLost << Damaged << HpRecover;
   }

   virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
       Room *room = player->getRoom();
       int hp = player->getHp();
       if(event == HpRecover){
           RecoverStruct recover = data.value<RecoverStruct>();
           if(hp<=2 && hp+recover.recover>2){
               LogMessage log;
               log.type = "#YicongAttack";
               log.from = player;
               log.to << player;
               log.arg = QString::number(hp);

               room->sendLog(log);
               room->playSkillEffect("yicong",1);
           }
       }else if(event == Damaged){
           DamageStruct damage = data.value<DamageStruct>();
           if(hp<=2 && hp+damage.damage>2){
               LogMessage log;
               log.type = "#YicongDefend";
               log.from = player;
               log.to << player;
               log.arg = QString::number(hp);

               room->sendLog(log);
               room->playSkillEffect("yicong",2);
           }
       }else{
           int lose = data.toInt();
           if(hp>2 && hp-lose<=2){
               LogMessage log;
               log.type = "#YicongDefend";
               log.from = player;
               log.to << player;
               log.arg = QString::number(hp);

               room->sendLog(log);
               room->playSkillEffect("yicong",2);
           }
       }
       return false;
   }
};

class Xiuluo: public PhaseChangeSkill{
public:
    Xiuluo():PhaseChangeSkill("xiuluo"){

    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getPhase() == Player::Start
                && !target->isKongcheng()
                && !target->getJudgingArea().isEmpty();
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        if(!target->askForSkillInvoke(objectName()))
            return false;

        Room *room = target->getRoom();
        int card_id = room->askForCardChosen(target, target, "j", objectName());
        const Card *card = Sanguosha->getCard(card_id);

        QString suit_str = card->getSuitString();
        QString pattern = QString(".%1").arg(suit_str.at(0).toUpper());
        QString prompt = QString("@xiuluo:::%1").arg(suit_str);
        if(room->askForCard(target, pattern, prompt)){
            room->throwCard(card);
        }

        return false;
    }
};

class Shenwei: public TriggerSkill{
public:
    Shenwei():TriggerSkill("shenwei"){
        events << DrawNCards << GameStart;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        if(event == DrawNCards)
            data = data.toInt() + 2;
        else if(event == GameStart)
            player->setXueyi(2);

        return false;
    }
};

class Danji: public PhaseChangeSkill{
public:
    Danji():PhaseChangeSkill("danji"){
        frequency = Wake;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return PhaseChangeSkill::triggerable(target)
                && target->getPhase() == Player::Start
                && target->getMark("danji") == 0
                && target->getHandcardNum() > target->getHp();
    }

    virtual bool onPhaseChange(ServerPlayer *guanyu) const{
        Room *room = guanyu->getRoom();
        ServerPlayer *the_lord = room->getLord();
        if(the_lord && the_lord->getGeneralName() == "caocao"){
            LogMessage log;
            log.type = "#DanjiWake";
            log.from = guanyu;
            log.arg = QString::number(guanyu->getHandcardNum());
            log.arg2 = QString::number(guanyu->getHp());
            room->sendLog(log);

            guanyu->setMark("danji", 1);

            room->loseMaxHp(guanyu);
            room->acquireSkill(guanyu, "mashu");
        }

        return false;
    }
};

class JileiClear: public PhaseChangeSkill{
public:
    JileiClear():PhaseChangeSkill("#jilei-clear"){

    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        if(target->getPhase() == Player::NotActive){
            Room *room = target->getRoom();
            QList<ServerPlayer *> players = room->getAllPlayers();
            foreach(ServerPlayer *player, players){
                if(player->hasFlag("jilei")){
                    player->jilei(".");
                    player->invoke("jilei");

                    LogMessage log;
                    log.type = "#JileiClear";
                    log.from = player;
                    room->sendLog(log);
                }
            }
        }

        return false;
    }
};

class Jilei: public TriggerSkill{
public:
    Jilei():TriggerSkill("jilei"){
        events << Predamaged;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *yangxiu, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();

        if(damage.from == NULL)
           return false;

        Room *room = yangxiu->getRoom();
        if(room->askForSkillInvoke(yangxiu, objectName(), data)){
            QString choice = room->askForChoice(yangxiu, objectName(), "basic+equip+trick");
            room->playSkillEffect(objectName());

            damage.from->jilei(choice);
            damage.from->invoke("jilei", choice);
            damage.from->setFlags("jilei");

            LogMessage log;
            log.type = "#Jilei";
            log.from = yangxiu;
            log.to << damage.from;
            log.arg = choice;
            room->sendLog(log);
        }

        return false;
    }
};

class Danlao: public TriggerSkill{
public:
    Danlao():TriggerSkill("danlao"){
        events << CardEffected;
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        CardEffectStruct effect = data.value<CardEffectStruct>();

        if(effect.multiple && effect.card->inherits("TrickCard")){
            Room *room = player->getRoom();
            if(room->askForSkillInvoke(player, objectName(), data)){
                room->playSkillEffect(objectName());

                LogMessage log;

                log.type = "#DanlaoAvoid";
                log.from = player;
                log.arg = effect.card->objectName();

                room->sendLog(log);

                player->drawCards(1);
                return true;
            }
        }

        return false;
    }
};

SPPackage::SPPackage()
    :Package("sp")
{
    General *yangxiu = new General(this, "yangxiu", "wei", 3);
    yangxiu->addSkill(new Danlao);
    yangxiu->addSkill(new Jilei);
    yangxiu->addSkill(new JileiClear);

    related_skills.insertMulti("jilei", "#jilei-clear");

    General *sp_guanyu = new General(this, "sp_guanyu", "wei", 4);
    sp_guanyu->addSkill("wusheng");
    sp_guanyu->addSkill(new Danji);

    General *sp_pangde = new General(this, "sp_pangde", "wei", 4, true, true);
    sp_pangde->addSkill("mengjin");
    sp_pangde->addSkill("mashu");

    General *sp_sunshangxiang = new General(this, "sp_sunshangxiang", "shu", 3, false, true);
    sp_sunshangxiang->addSkill("jieyin");
    sp_sunshangxiang->addSkill("xiaoji");

    General *gongsunzan = new General(this, "gongsunzan", "qun");
    gongsunzan->addSkill(new Yicong);
    gongsunzan->addSkill(new YicongEffect);

    related_skills.insertMulti("yicong", "#yicong-effect");

    General *yuanshu = new General(this, "yuanshu", "qun");
    yuanshu->addSkill(new Yongsi);
    yuanshu->addSkill(new Weidi);
    yuanshu->addSkill(new Weidijijiang);
    yuanshu->addSkill(new Weidixueyi);
    yuanshu->addSkill(new Weidiruoyu);

    related_skills.insertMulti("weidi", "#weidijijiang");
    related_skills.insertMulti("weidi", "#weidixueyi");
    related_skills.insertMulti("weidi", "#weidiruoyu");

    General *sp_diaochan = new General(this, "sp_diaochan", "qun", 3, false, true);
    sp_diaochan->addSkill("lijian");
    sp_diaochan->addSkill("biyue");

    General *shenlvbu1 = new General(this, "shenlvbu1", "god", 8, true, true);
    shenlvbu1->addSkill("mashu");
    shenlvbu1->addSkill("wushuang");

    General *shenlvbu2 = new General(this, "shenlvbu2", "god", 4, true, true);
    shenlvbu2->addSkill("mashu");
    shenlvbu2->addSkill("wushuang");
    shenlvbu2->addSkill(new Xiuluo);
    shenlvbu2->addSkill(new Shenwei);
    shenlvbu2->addSkill(new Skill("shenji"));

    addMetaObject<JijiangCard>();
}

ADD_PACKAGE(SP);
