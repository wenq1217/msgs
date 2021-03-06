return {
	["impasse_fight"] = "绝境之战",

	["silue"] = "思略",
	[":silue"] = "锁定技，摸牌阶段，你始终摸X张牌，X为你当前的体力值；进入狂暴状态后，摸牌阶段始终从其他存活角色那各摸一张牌。",
	["kedi"] = "克敌",
	[":kedi"] = "你每受到一点伤害可以摸X张牌，X为你当前体力值；进入狂暴状态后，你每受到一点伤害可以摸X张牌，X为场上存活的角色数。",
	["jishi"] = "济世",
	[":jishi"] = "锁定技，回合开始阶段，若你的手牌不大于X，你可以从除你以外每名角色那获得一张手牌，若目标角色无手牌，则失去一点体力，X为你当前体力值；进入狂暴状态后，\
	若目标角色无手牌，则失去两点体力，X为存活的角色数与你当前体力上限之和。你的手牌上限至多为存活的角色数。",
	["daji"] = "大吉",
	[":daji"] = "锁定技，回合结束阶段，你可以摸X张牌，X为你当前体力值；进入狂暴状态后，X为存活的角色数，你获得额外技能效果：你的回合外，当你的手牌不大于存活的角色数时：\
	若你成为锦囊牌的唯一目标，则该锦囊对你无效。你每次受到的伤害始终为1。",

	["guzhan"] = "孤战",
	[":guzhan"] = "锁定技，当你没装备武器时，你获得技能【咆哮】；当装备武器时，你失去技能【咆哮】。",
	["jizhan"] = "激战",
	[":jizhan"] = "锁定技，出牌阶段，你每对其他角色造成一点伤害可回复一点体力；当手牌小于存活的角色数时，你可以立即摸一张牌。",
	["duduan"] = "独断",
	[":duduan"] = " 锁定技，你不能成为延时类锦囊的目标。",

	["#Baozou"] = "%from 进入狂暴状态，拥有无视防具效果",
	["#BaozouOver"] = "%from 的狂暴状态消失，【绝境之战】事件被触发，每名角色开始进行判定",
	["#Jishi"] = "%from 的锁定技【济世】被触发",
	["#DajiSpec"] = "%from 的锁定技【大吉】被触发",
	["#DajiAvoid"] = "%to 的锁定技【大吉】被触发，%from 对 %to 使用的锦囊 %arg 无效",
	["#PaoxiaoLose"] = "%from 失去了技能【咆哮】",

	["@frantic"] = "狂暴",
}