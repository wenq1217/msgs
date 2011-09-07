#include "huangjin-package.h"
#include "standard.h"
#include "skill.h"
#include "wind.h"
#include "client.h"
#include "carditem.h"
#include "engine.h"
#include "standard-skillcards.h"

class Rengong: public PhaseChangeSkill{
public:
    Rengong():PhaseChangeSkill("rengong"){
    }

    virtual bool onPhaseChange(ServerPlayer *zhangliang) const{
        Room *room = zhangliang->getRoom();

        if(zhangliang->getPhase() != Player::Draw)
            return false;

        QList<ServerPlayer *> players = room->getOtherPlayers(zhangliang);
        foreach(ServerPlayer *p, players){
            if(p->isKongcheng())
                players.removeOne(p);
        }

        if(players.isEmpty() || !zhangliang->askForSkillInvoke(objectName()))
            return false;

        room->playSkillEffect(objectName());

        ServerPlayer *rengonger = room->askForPlayerChosen(zhangliang, players, objectName());
        QList<int> handcards = rengonger->handCards();
        room->fillAG(handcards);

        const int card_length = handcards.length();

        while(handcards.length ()-card_length == 0){
            int card_id = room->askForAG(zhangliang, handcards, false, objectName());
            handcards.removeOne(card_id);
            room->moveCardTo(Sanguosha->getCard(card_id), zhangliang, Player::Hand, false);
        }

        room->broadcastInvoke("clearAG");

        return true;
    }
};

class Shishi: public TriggerSkill{
public:
    Shishi():TriggerSkill("shishi"){
        events << Death;

        frequency = Frequent;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        DamageStar damage = data.value<DamageStar>();
        ServerPlayer *killer = damage ? damage->from : NULL;
        Room *room = player->getRoom ();

        int nheal = 0;
        if(killer && killer->hasSkill("shishi"))
            nheal = killer->getMaxHP() - killer->getHp();

        if(nheal > 0 && room->askForSkillInvoke(killer, objectName())){
            RecoverStruct recover;
            recover.who = killer;
            recover.recover = nheal;
            room->recover(killer, recover);
            room->playSkillEffect(objectName());
        }

        return false;
    }
};

class Feiyan: public TriggerSkill{
public:
    Feiyan():TriggerSkill("feiyan"){
        events << CardEffected;
        frequency = Frequent;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        CardEffectStruct effect = data.value<CardEffectStruct>();
        ServerPlayer *zhangyan = room->findPlayerBySkillName(objectName());
        if(effect.card == NULL || !effect.card->inherits("Slash")|| effect.from == zhangyan || zhangyan->getPhase() != Player::NotActive)
            return false;

        if(zhangyan->inMyAttackRange(effect.from))
            if(zhangyan->askForSkillInvoke(objectName())){
                const Card *slash = room->askForCard(zhangyan, "slash", "@feiyan-slash:" + effect.from->objectName());
                if(slash){
                    zhangyan->drawCards(1);

                    CardUseStruct use;
                    use.card = slash;
                    use.from = zhangyan;
                    use.to << effect.from;
                    room->useCard(use);
                }
            }

        return false;
    }
};

class Zhenhuo: public TriggerSkill{
public:
    Zhenhuo():TriggerSkill("zhenhuo"){
        events << SlashMissed;
    }

    virtual int getPriority() const{
        return 2;
    }

    virtual bool trigger(TriggerEvent, ServerPlayer *zhangbao, QVariant &data) const{
        Room *room = zhangbao->getRoom();
        SlashEffectStruct effect = data.value<SlashEffectStruct>();

        if(!zhangbao->askForSkillInvoke(objectName()))
            return false;

        JudgeStruct judge;
        judge.pattern = QRegExp("(.*):(heart):(.*)");
        judge.good = false;
        judge.reason = "zhenhuo";
        judge.who = effect.to;

        room->judge(judge);

        if(judge.isBad()){
            QList<ServerPlayer *> players = room->getAlivePlayers(), enemies;
            foreach(ServerPlayer *player, players){
                if(effect.to->inMyAttackRange(player))
                    enemies << player;
            }

            ServerPlayer *enemy = room->askForPlayerChosen(zhangbao, enemies, "zhenhuo");

            DamageStruct damage;
            damage.card = NULL;
            damage.from = zhangbao;
            damage.to = enemy;
            damage.nature = DamageStruct::Fire;
            if(damage.from->hasSkill("jueqing")){
                LogMessage log;
                log.type = "#Jueqing";
                log.from = damage.from;
                log.to << damage.to;
                log.arg = QString::number(1);
                room->sendLog(log);
                room->playSkillEffect("jueqing");
                room->loseHp(damage.to, 1);
            }else{
                room->damage(damage);
            }
        }

        return false;
    }
};

class Heiyan: public ProhibitSkill{
public:
    Heiyan():ProhibitSkill("heiyan"){

    }

    virtual bool isProhibited(const Player *from, const Player *to, const Card *card) const{
        return (card->inherits("Duel")||card->inherits("Slash")) && card->isBlack();
    }
};

GuishuCard::GuishuCard(){
    target_fixed = true;
}

void GuishuCard::use(Room *room, ServerPlayer *zhangbao, const QList<ServerPlayer *> &targets) const{

}

class GuishuViewAsSkill:public OneCardViewAsSkill{
public:
    GuishuViewAsSkill():OneCardViewAsSkill(""){

    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return false;
    }

    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const{
        return  pattern == "@guishu";
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return to_select->getFilteredCard()->isRed();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        GuishuCard *card = new GuishuCard;
        card->addSubcard(card_item->getFilteredCard());

        return card;
    }
};

class Guishu: public TriggerSkill{
public:
    Guishu():TriggerSkill("guishu"){
        view_as_skill = new GuishuViewAsSkill;

        events << AskForRetrial;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        if(!TriggerSkill::triggerable(target))
            return false;

        if(target->isKongcheng()){
            bool has_red = false;
            int i;
            for(i=0; i<4; i++){
                const EquipCard *equip = target->getEquip(i);
                if(equip && equip->isRed()){
                    has_red = true;
                    break;
                }
            }

            return has_red;
        }else
            return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        JudgeStar judge = data.value<JudgeStar>();

        QStringList prompt_list;
        prompt_list << "@guishu-card" << judge->who->objectName()
                << "" << judge->reason << judge->card->getEffectIdString();
        QString prompt = prompt_list.join(":");

        player->tag["Judge"] = data;
        const Card *card = room->askForCard(player, "@guishu", prompt);

        if(card){
            player->obtainCard(judge->card);

            judge->card = Sanguosha->getCard(card->getEffectiveId());
            room->moveCardTo(judge->card, NULL, Player::Special);

            LogMessage log;
            log.type = "$ChangedJudge";
            log.from = player;
            log.to << judge->who;
            log.card_str = card->getEffectIdString();
            room->sendLog(log);

            room->sendJudgeResult(judge);
        }

        return false;
    }
};

WeichengCard::WeichengCard(){
    once = true;
    will_throw = false;
}

bool WeichengCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const{
    return targets.isEmpty() && !to_select->isKongcheng() && to_select != Self;
}

void WeichengCard::use(Room *room, ServerPlayer *zhangmancheng, const QList<ServerPlayer *> &targets) const{
    bool success = zhangmancheng->pindian(targets.first(), "weicheng", this);

    if(success){
        QString choice = room->askForChoice(zhangmancheng, "weicheng", "skipdraw+skipplay");
        if(choice == "skipdraw"){
            targets.first()->setFlags("weicheng_skipdraw");

            LogMessage log;
            log.type = "#WeichengSkipdraw";
            log.from = zhangmancheng;
            log.to << targets.first();

            room->sendLog(log);
        }else if(choice == "skipplay"){
            targets.first()->setFlags("weicheng_skipplay");

            LogMessage log;
            log.type = "#WeichengSkipplay";
            log.from = zhangmancheng;
            log.to << targets.first();

            room->sendLog(log);
        }
    }
}

class WeichengViewAsSkill: public OneCardViewAsSkill{
public:
    WeichengViewAsSkill():OneCardViewAsSkill("weicheng"){
        default_choice = "skipdraw";
    }

    virtual bool isEnabledAtPlay(const Player *player) const{
        return !player->hasUsed("WeichengCard") && !player->isKongcheng();
    }

    virtual bool viewFilter(const CardItem *to_select) const{
        return !to_select->isEquipped();
    }

    virtual const Card *viewAs(CardItem *card_item) const{
        Card *card = new WeichengCard;
        card->addSubcard(card_item->getFilteredCard());
        return card;
    }
};

class Weicheng: public PhaseChangeSkill{
public:
    Weicheng():PhaseChangeSkill("weicheng"){
        view_as_skill = new WeichengViewAsSkill;
    }

    virtual int getPriority() const{
        return 3;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        Room *room = target->getRoom();

        LogMessage log;
        log.type = "#WeichengClear";
        log.from = target;

        if(target->getPhase() == Player::Draw && target->hasFlag("weicheng_skipdraw"))
            return true;
        else if(target->getPhase() == Player::Play && target->hasFlag("weicheng_skipplay"))
            return true;
        else if(target->getPhase() == Player::Finish){
            if(target->hasFlag("weicheng_skipdraw")){
                room->setPlayerFlag(target, "-weicheng_skipdraw");
                room->sendLog(log);
            }else if(target->hasFlag("weicheng_skipplay")){
                room->setPlayerFlag(target, "-weicheng_skipplay");
                room->sendLog(log);
            }
        }

        return false;
    }
};

class HuangjinBaonue: public TriggerSkill{
public:
    HuangjinBaonue():TriggerSkill("huangjin_baonue"){
        events << Predamage;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.card && damage.card->inherits("Slash") &&
            damage.to->isWounded() && player->askForSkillInvoke(objectName()))
        {
            Room *room = damage.to->getRoom();

            LogMessage log;
            log.type = "#HuangjinBaonueEffect";
            log.from = player;
            log.to << damage.to;
            log.arg = QString::number(damage.damage);
            log.arg2 = QString::number(damage.damage + 1);
            room->sendLog(log);

            damage.damage ++;
            data = QVariant::fromValue(damage);
        }

        return false;
    }
};

class Jieliang: public TriggerSkill{
public:
    Jieliang():TriggerSkill("jieliang"){
        events << SlashHit;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        SlashEffectStruct effect = data.value<SlashEffectStruct>();
        int card_num = 2 + qMin(player->getMark("@struggle"),3);
        if(player->hasFlag("luoyi"))
            card_num++;
        if(effect.drank)
            card_num++;


        if(!effect.to->isNude() && player->askForSkillInvoke(objectName(), data)){
            while(card_num > 0 && !effect.to->isNude()){
                int card_id = room->askForCardChosen(player, effect.to, "he", objectName());
                if(room->getCardPlace(card_id) == Player::Hand)
                    room->moveCardTo(Sanguosha->getCard(card_id), player, Player::Hand, false);
                else
                    room->obtainCard(player, card_id);
                card_num--;
            }

            return true;
        }

        return false;
    }
};

class Duoma: public PhaseChangeSkill{
public:
    Duoma():PhaseChangeSkill("duoma"){
    }

    virtual bool onPhaseChange(ServerPlayer *peiyuanshao) const{
        Room *room = peiyuanshao->getRoom();

        if(peiyuanshao->getPhase() != Player::Draw)
            return false;

        QList<ServerPlayer *> players = room->getOtherPlayers(peiyuanshao);
        foreach(ServerPlayer *p, players){
            if(!p->hasEquip())
                players.removeOne(p);
        }

        if(players.isEmpty() || !peiyuanshao->askForSkillInvoke(objectName()))
            return false;

        ServerPlayer *target = room->askForPlayerChosen(peiyuanshao, players, objectName());
        QList<int> equip_ids;
        QList<const Card *> equips = target->getEquips();
        foreach(const Card *c,equips)
            equip_ids << c->getId();

        room->fillAG(equip_ids);
        const int card_length = equip_ids.length();

        while(equip_ids.length ()-card_length == 0){
            int card_id = room->askForAG(peiyuanshao, equip_ids, false, objectName());
            equip_ids.removeOne(card_id);
            const Card *card = Sanguosha->getCard(card_id);
            peiyuanshao->obtainCard(card);
            peiyuanshao->drawCards(1);
            room->playSkillEffect(objectName());
        }

        room->broadcastInvoke("clearAG");

        return true;
    }
};

class Pengdao: public TriggerSkill{
public:
    Pengdao():TriggerSkill("pengdao"){
        events << SlashMissed << Predamage;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        if(event == SlashMissed){
            SlashEffectStruct effect = data.value<SlashEffectStruct>();
            if(effect.to->hasSkill("kongcheng") && effect.to->isKongcheng())
                return false;

            const Card *card = room->askForCard(player, "slash", "@pengdao-slash");
            if(card){
                // if player is drank, unset his flag
                player->gainMark("@pengdaoslash", 1);
                if(player->hasFlag("drank"))
                    room->setPlayerFlag(player, "-drank");

                CardUseStruct use;
                use.card = card;
                use.from = player;
                use.to << effect.to;
                room->useCard(use, false);
            }else{
                if(player->getMark("@pengdaoslash") > 0){
                    LogMessage log;
                    log.type = "#PengdaoMiss";
                    log.from = player;
                    log.to << effect.to;
                    room->sendLog(log);

                    player->loseMark("@pengdaoslash", player->getMark("@pengdaoslash"));
                }
            }
        }else if(event == Predamage){
            DamageStruct damage = data.value<DamageStruct>();
            if(damage.card && damage.card->inherits("Slash") && player->getMark("@pengdaoslash") > 0){
                Room *room = damage.to->getRoom();

                LogMessage log;
                log.type = "#PengdaoEffect";
                log.from = player;
                log.to << damage.to;
                log.arg = QString::number(damage.damage);
                log.arg2 = QString::number(damage.damage + player->getMark("@pengdaoslash"));
                room->sendLog(log);

                damage.damage = damage.damage + player->getMark("@pengdaoslash");
                data = QVariant::fromValue(damage);

                player->loseMark("@pengdaoslash", player->getMark("@pengdaoslash"));
            }
        }
        return false;
    }
};

class Chixie: public TriggerSkill{
public:
    Chixie():TriggerSkill("chixie"){

    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        return false;
    }
};

class Mabi: public TriggerSkill{
public:
    Mabi():TriggerSkill("mabi"){
        events << Predamage;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return target->hasSkill(objectName());
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        Room *room = player->getRoom();
        DamageStruct damage = data.value<DamageStruct>();
        if(damage.card && damage.card->inherits("Slash") && player->askForSkillInvoke(objectName()))
        {
            damage.to->setFlags("mabi");

            LogMessage log;
            log.type = "#MabiSkipdraw";
            log.from = player;
            log.to << damage.to;

            room->sendLog(log);

            return true;
        }

        return false;
    }
};

class MabiSkip: public PhaseChangeSkill{
public:
    MabiSkip():PhaseChangeSkill("#mabi"){
    }

    virtual int getPriority() const{
        return 3;
    }

    virtual bool triggerable(const ServerPlayer *target) const{
        return true;
    }

    virtual bool onPhaseChange(ServerPlayer *target) const{
        Room *room = target->getRoom();

        LogMessage log;
        log.type = "#MabiClear";
        log.from = target;

        if(target->getPhase() == Player::Draw && target->hasFlag("mabi"))
            return true;
        else if(target->getPhase() == Player::Finish && target->hasFlag("mabi")){
            room->setPlayerFlag(target, "-mabi");
            room->sendLog(log);
        }

        return false;
    }
};

class Xiuzhen: public TriggerSkill{
public:
    Xiuzhen():TriggerSkill("xiuzhen"){
        events << Damaged;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *xianyuji, QVariant &data) const{
        Room *room = xianyuji->getRoom();
        DamageStruct damage = data.value<DamageStruct>();
        ServerPlayer *source = damage.from;
        int nDamage = damage.damage;

        if(source && xianyuji->askForSkillInvoke(objectName()))
            while(nDamage > 0){
                room->playSkillEffect(objectName());

                JudgeStruct judge;
                judge.pattern = QRegExp("(.*):(.*):(.*)");
                judge.good = false;
                judge.who = source;
                judge.reason = objectName();

                room->judge(judge);

                switch(judge.card->getSuit()){
                case Card::Heart:{
                        RecoverStruct recover;
                        recover.who = xianyuji;
                        room->recover(xianyuji, recover);

                        break;
                    }

                case Card::Diamond:{
                        xianyuji->drawCards(1);
                        source->drawCards(1);

                        break;
                    }

                case Card::Club:{
                        if(source && source->isAlive() && source->getHandcardNum() > 0)
                            room->askForDiscard(source, "xiuzhen", 1, false, false);

                        break;
                    }

                case Card::Spade:{
                        if(source && source->isAlive()){
                            DamageStruct damage;
                            damage.card = NULL;
                            damage.from = xianyuji;
                            damage.to = source;
                            damage.nature = DamageStruct::Thunder;

                            room->damage(damage);
                        }

                        break;
                    }

                default:
                    break;
                }

                nDamage--;
            }

        return false;
    }
};

class Huoqi: public TriggerSkill{
public:
    Huoqi():TriggerSkill("huoqi"){
        events << CardLost << PhaseChange;
        default_choice = "huoqipindian";
    }

    void perform(ServerPlayer *xiannanhua) const{
        Room *room = xiannanhua->getRoom();
        QString result = room->askForChoice(xiannanhua, objectName(), "huoqirecover+huoqipindian");
        QList<ServerPlayer *> all_players = room->getAllPlayers(),pindian_players;
        if(result == "huoqirecover"){
            RecoverStruct recover;
            recover.who = xiannanhua;
            room->recover(xiannanhua, recover);
            room->playSkillEffect(objectName());
        }else if(result == "huoqipindian"){
            foreach(ServerPlayer *p, all_players)
                if(!p->isKongcheng())
                    pindian_players << p;
            room->playSkillEffect(objectName());
        }
    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *xiannanhua, QVariant &data) const{
        if(xiannanhua->getPhase() != Player::Discard)
            return false;

        if(event == CardLost){
            CardMoveStar move = data.value<CardMoveStar>();
            if(move->to_place == Player::DiscardedPile){
                xiannanhua->addMark("huoqi");
                if(xiannanhua->getMark("huoqi") == 2){
                    if(xiannanhua->askForSkillInvoke(objectName()))
                        perform(xiannanhua);
                }
            }
        }else if(event == PhaseChange){
            xiannanhua->setMark("huoqi", 0);
        }

        return false;
    }
};

class Tianbian: public TriggerSkill{
public:
    Tianbian():TriggerSkill("tianbian"){

    }

    virtual bool trigger(TriggerEvent event, ServerPlayer *xiannanhua, QVariant &data) const{
        return false;
    }
};

HuangjinPackage::HuangjinPackage()
    :Package("huangjin")
{
    General *zhangliang, *zhangyan, *zhangbao, *zhangmancheng, *chengzhiyuan, *guanhai, *peiyuanshao, *zhoucang,
    *mayuanyi, *xianyuji, *xiannanhua;

    zhangliang = new General(this, "zhangliang", "qun");
    zhangliang->addSkill(new Rengong);
    zhangliang->addSkill(new Shishi);

    zhangyan = new General(this, "zhangyan", "qun");
    zhangyan->addSkill(new Feiyan);

    zhangbao = new General(this, "zhangbao", "qun", 3);
    zhangbao->addSkill(new Zhenhuo);
    zhangbao->addSkill(new Heiyan);
    zhangbao->addSkill(new Guishu);

    zhangmancheng = new General(this, "zhangmancheng", "qun");
    zhangmancheng->addSkill(new Weicheng);

    chengzhiyuan = new General(this, "chengzhiyuan", "qun");
    chengzhiyuan->addSkill(new HuangjinBaonue);

    guanhai = new General(this, "guanhai", "qun");
    guanhai->addSkill(new Jieliang);

    peiyuanshao = new General(this, "peiyuanshao", "qun");
    peiyuanshao->addSkill(new Duoma);

    zhoucang = new General(this, "zhoucang", "qun");
    zhoucang->addSkill(new Pengdao);
    zhoucang->addSkill(new Chixie);

    mayuanyi = new General(this, "mayuanyi", "qun");

    xianyuji = new General(this, "xianyuji", "god", 3);
    xianyuji->addSkill(new Mabi);
    xianyuji->addSkill(new MabiSkip);
    xianyuji->addSkill(new Xiuzhen);

    related_skills.insertMulti("mabi", "#mabi");

    xiannanhua = new General(this, "xiannanhua", "god", 3);
    xiannanhua->addSkill(new Huoqi);
    xiannanhua->addSkill(new Tianbian);

    addMetaObject<GuishuCard>();
    addMetaObject<WeichengCard>();
}

ADD_PACKAGE(Huangjin)
