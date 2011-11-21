-- translation for MountainPackage

return {
	["mountain"] = "山包",

	--张郃
	["zhanghe"] = "张郃",
	["qiaobian"] = "巧变",
	[":qiaobian"] = "你可以弃一张手牌来跳过自己的一个阶段（回合开始阶段和回合结束阶段除外）；若以此法跳过摸牌阶段，你从其他至多两名角色处抽取一张手牌；若以此法跳过出牌阶段，你可以将场上的一张牌移动到另一个合理的位置。\
	◆若场上所有其它角色都没有手牌，你不能通过【巧变】跳过摸牌阶段。\
	◆若场上某些角色都装备了某一类装备，你不能【巧变】这些角色身上的该类别的装备，延时锦囊同理。",
	["@qiaobian-judge"] = "你可弃１张手牌跳过判定阶段",
	["@qiaobian-draw"] = "你可弃１张手牌跳过摸牌阶段，并从其他至多两名角色手里各抽取１张牌",
	["@qiaobian-play"] = "你可弃１张手牌跳过出牌阶段，并将场上的１张牌移动到另一个合理的位置",
	["@qiaobian-discard"] = "你可弃１张手牌跳过弃牌阶段",
	
	--邓艾
	["dengai"] = "邓艾",
	["tuntian"] = "屯田",
	[":tuntian"] = "每次当你于回合外失去牌时，可进行一次判定，将非红桃结果的判定牌置于你的武将牌上，称为“田”；每有一张“田”，你计算与其他角色的距离便减1。",
	["zaoxian"] = "凿险",
	[":zaoxian"] = "<b>觉醒技</b>，回合开始阶段，若“田”的数量达到3张或更多，你须减1点体力上限，并永久获得技能【急袭】：出牌阶段，你可以把任意一张“田”当【顺手牵羊】使用。",
	["#ZaoxianWake"] = "%from 的“田”的数量达到了 %arg 个，觉醒技【凿险】被触发",
	["jixi"] = "急袭",
	[":jixi"] = "出牌阶段，你可以把任意一张“田”当【顺手牵羊】使用。",
	["field"] = "田",
	
	--刘禅
	["liushan"] = "刘禅",
	["xiangle"] = "享乐",
	[":xiangle"] = "<b>锁定技</b>，当其他玩家使用【杀】指定你为目标时，需额外弃掉一张基本牌，否则该【杀】对你无效。",
	["fangquan"] = "放权",
	[":fangquan"] = "你可跳过你的出牌阶段，若如此做，在回合结束时可弃一张手牌令一名其他角色进行一个额外的回合。",
	["ruoyu"] = "若愚",
	[":ruoyu"] = "<b>主公技</b>，<b>觉醒技</b>，回合开始阶段，若你的体力是全场最少的（或之一），你须增加1点体力上限，回复1点体力，并永久获得技能【激将】。",
	["#Xiangle"] = "%to 的锁定技<font color='yellow'><b>【享乐】</b></font>被触发， %from 必须再额外弃掉 <font color='yellow'>１</font> 张基本牌才能使此<font color='yellow'><b>【杀】</b></font>生效",
	["#Fangquan"] = "%from 使用了<font color='yellow'><b>【放权】</b></font>，%to 将获得一个额外的回合",
	["#RuoyuWake"] = "%from 的体力值（%arg）为场上最低，觉醒技<font color='yellow'><b>【若愚】</b></font>被触发",
	["@xiangle-discard"] = "你必须再弃掉一张基本牌才能使此【杀】生效",
	
	--姜维
	["jiangwei"] = "姜维",
	["tiaoxin"] = "挑衅",
	[":tiaoxin"] = "出牌阶段,你可以指定一名使用【杀】能攻击到你的角色，该角色需对你使用一张【杀】，若该角色不如此做,你弃掉他的一张牌，每回合限用一次。",
	["zhiji"] = "志继",
	[":zhiji"] = "<b>觉醒技</b>，回合开始阶段，若你没有手牌，你须回复1点体力或摸两张牌，然后减1点体力上限，并永久获得技能【观星】。",
	["zhiji:draw"] = "摸２张牌",
	["zhiji:recover"] = "回复１点体力",
	["#ZhijiWake"] = "%from 回合开始时手牌为空，觉醒技<font color='yellow'><b>【志继】</b></font>被触发",
	["@tiaoxin-slash"] = "%src 对你发动了【挑衅】，请对其使用一张【杀】，否则将被其弃一张牌",
	
	--孙策
	["sunce"] = "孙策",
	["jiang"] = "激昂",
	[":jiang"] = "每当你使用（指定目标后）或被使用（成为目标后）一张【决斗】或红色的【杀】时，你可以摸一张牌。",
	["hunzi"] = "魂姿",
	[":hunzi"] = "<b>觉醒技</b>，回合开始阶段，若你的体力为1，你须减1点体力上限，并永久获得技能【英魂】和【英姿】。",
	["zhiba"] = "制霸",
	[":zhiba"] = "<b>主公技</b>，其他吴势力角色的出牌阶段，可与你进行一次拼点，若该角色没赢，你可以获得双方拼点的牌；你的觉醒技发动后，你可以拒绝此拼点，每回合限一次。",
	["zhiba_pindian"] = "制霸（拼点）",
	[":zhiba_pindian"] = "出牌阶段，可以与主公拼点，若你没赢，主公可以获得双方拼点的牌，每回合限一次。",
	["#HunziWake"] = "%from 本回合初始体力值为<font color='yellow'><b>１</b></font>，觉醒技<font color='yellow'><b>【魂姿】</b></font>被触发",
	["#ZhibaPindianReject"] = "%from 拒绝了此次<font color='yellow'><b>【制霸】</b></font>拼点",
	["zhiba_pindian:accept"] = "接受拼点",
	["zhiba_pindian:reject"] = "拒绝拼点",

	--二张
	["erzhang"] = "张昭·张纮",
	["zhijian"] = "直谏",
	[":zhijian"] = "出牌阶段，你可以将你手牌中的一张装备牌置于一名其他角色装备区里（不得替换原装备），然后摸一张牌。",
	["guzheng"] = "固政",
	[":guzheng"] = "其他角色的弃牌阶段结束时，你可将此阶段中弃掉的一张牌从弃牌堆返回该角色手牌，若如此做，你可以获得弃牌堆里其余于此阶段中弃掉的牌。",	

	--蔡文姬
	["caiwenji"] = "蔡文姬",
	["beige"] = "悲歌",
	[":beige"] = "每当一名角色受到【杀】造成的一次伤害后，你可以弃置一张牌，并令其进行一次判定，判定结果为：\
	红桃：该角色回复1点体力；\
	方块：该角色摸两张牌；\
	梅花：伤害来源弃两张牌；\
	黑桃：伤害来源将其武将牌翻面。",
	["duanchang"] = "断肠",
	[":duanchang"] = "<b>锁定技</b>，杀死你的角色失去当前的所有技能直到游戏结束。",
	["guixiang"] = "归乡",
	[":guixiang"] = "<b>限定技</b>，游戏开始阶段，你可发动此技能，重归故里，变身为SP蔡文姬，势力变为魏。",

	--左慈
	["zuoci"] = "左慈",--·♂
	["zuocif"] = "左慈·女",--·♀
	["huashen"] = "化身",
	[":huashen"] ="游戏开始前，你可以从未登场武将中摸取两张武将牌并置于你的武将牌上，选择其中一张置于最上方并声明其中的一个技能，则视为你拥有此技能。每个回合开始前，你可以摸取两张武将牌并且选择更改技能，回合结束后你可以再次更改技能。\
	◆你不可声明<b>限定技</b>、<b>觉醒技</b>或<b>主公技</b>。",
	["xinsheng"] = "新生",
	[":xinsheng"] = "你每受到一点伤害，可以从未登场武将牌中摸取一张武将牌。",
	["#GetHuashen"] = "%from 受到了 %arg 点伤害，获得了 %arg2 张化身牌。",
	
	--武将技能台词
	["$qiaobian"] = "",
	
	["$tuntian"] = "",
	["$zaoxian"] = "",
	["$jixi"] = "",
	
	["$fangquan1"] = "一切但凭相父做主！",
	["$fangquan2"] = "孩儿愚钝！",
	["$ruoyu"] = "大智若愚，大巧若拙。",
	["$xiangle1"] = "此间乐，不思蜀。",
	["$xiangle2"] = "如此甚好，甚好！",
	
	["$tiaoxin1"] = "贼将早降，可免一死！",
	["$tiaoxin2"] = "哼，贼将莫不是怕了？",
	["$tiaoxin3"] = "敌将可破得我八阵？",
	["$zhiji"] = "今虽穷极，然先帝之志，丞相之托，维岂敢忘！",
	
	["$jiang"] = "",
	["$hunzi"] = "",
	["$zhiba"] = "",
	
	["$zhijian"] = "",
	["$guzheng"] = "",
	
	["$beige"] = "",
	["$duanchang"] = "",
	
	["$huashen"] = "",
	["$xinsheng"] = "",
	
	--阵亡台词
	["~zhanghe"] = "",
	["~dengai"] = "",
	["~liushan"] = "吾降，吾降矣！",
	["~jiangwei"] = "臣等正欲死战，陛下何故先降？",
	["~sunce"] = "",
	["~erzhang"] = "",
	["~caiwenji"] = "",
	["~zuoci"] = "",
	["~zuocif"] = "",
	
	["cv:zhanghe"] = "",
	["cv:dengai"] = "",
	["cv:liushan"] = "迷宫",
	["cv:jiangwei"] = "",
	["cv:sunce"] = "",
	["cv:erzhang"] = "",
	["cv:caiwenji"] = "",
	["cv:zuoci"] = "",
	["cv:zuocif"] = "",
}
