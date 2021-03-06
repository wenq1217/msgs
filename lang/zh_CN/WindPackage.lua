-- translation for WindPackage

return {
	["wind"] = "风包",

	--夏侯渊
	["xiahouyuan"] = "夏侯渊",
	["shensu"] = "神速",
	[":shensu"] = "你可以分别作出下列选择：\
	1、跳过该回合的判定阶段和摸牌阶段，\
	2、跳过该回合出牌阶段并弃一张装备牌，\
	你每做出上述之一项选择，视为对任意一名角色使用一张【杀】。",
	["@shensu1"] = "跳过该回合的判定阶段和摸牌阶段，视为对任意一名角色使用一张【杀】", 
	["@shensu2"] = "跳过该回合出牌阶段并弃一张装备牌，视为对任意一名角色使用一张【杀】",
	
	--曹仁
	["caoren"] = "曹仁",
	["jushou"] = "据守", 
	[":jushou"] = "回合结束阶段，你可以选择摸三张牌，若如此做，将你的武将翻面。", 
	["jushou:yes"] = "你可以摸三张牌，若如此做，将你的武将翻面",
	
	--黄忠
	["huangzhong"] = "黄忠", 
	["liegong"] = "烈弓", 
	[":liegong"] = "出牌阶段，以下两种情况，你可以令你使用的【杀】不可被闪避：\
	1、目标角色的手牌数大于或等于你的体力值。\
	2、目标角色的手牌数小于或等于你的攻击范围。\
	◆攻击范围计算只和武器有关，与+1马、-1马均无关。",
	["liegong:yes"] = "你可以使此【杀】不可被闪避",
	
	--魏延
	["weiyan"] = "魏延", 
	["kuanggu"] = "狂骨", 
	[":kuanggu"] = "<b>锁定技</b>，任何时候，你每对与你距离1以内的一名角色造成1点伤害，你回复1点体力。",
	["#KuangguRecover"] = "%from 的锁定技<font color='yellow'><b>【狂骨】</b></font>被触发，回复了 %arg 点体力",
	
	--周泰
	["zhoutai"] = "周泰",
	["buqu"] = "不屈", 
	[":buqu"] = "任何时候，当你的体力被扣减到0或更低时，每扣减1点体力：从牌堆亮出一张牌放在你的武将牌上，若该牌的点数与你已有的不屈牌中的任何一张牌都不同，你可以不死，此牌亮出的时刻为你的濒死状态。", 
	["buqu:alive"] = "我还想活！",
	["buqu:dead"] = "我不想活了……",
	
	--小乔
	["xiaoqiao"] = "小乔",
	["hongyan"] = "红颜",
	["tianxiang"] = "天香",
	[":hongyan"] = "<b>锁定技</b>，你的黑桃牌均视为红桃花色。",	
	[":tianxiang"] = "每当你受到伤害时，你可以弃一张红桃手牌来转移此伤害给任意一名角色，然后该角色摸X张牌；X为该角色当前已损失的体力值。",
	["#HongyanJudge"] = "%from 的锁定技<font color='yellow'><b>【红颜】</b></font>被触发， 判定牌由黑桃变成了红桃",
	["@@tianxiang-card"] = "请弃一张红桃手牌来转移此伤害",
	
	--张角
	["zhangjiao"] = "张角", 
	["guidao"] = "鬼道", 
	["leiji"] = "雷击", 
	["huangtian"] = "黄天",
	["huangtianv"] = "黄天",
	[":huangtianv"] = "出牌阶段，你可以给主公一张【闪】或【闪电】。",
	[":guidao"] = "在任意一名角色的判定牌生效前，你可以用自己的一张黑色牌替换之。",
	[":leiji"] = "每当你使用或打出一张【闪】时（在结算前）可令任意一名角色判定，若为【黑桃】，你对该角色造成2点雷电伤害。", 
	[":huangtian"] = "<b>主公技</b>，群雄角色可在他们各自的回合里给你一张【闪】或【闪电】。", 
	["@guidao-card"] = "请使用【鬼道】修改 %src 的 %arg 判定",
	["@leiji"] = "令任意一名角色判定，若结果为【黑桃】，你对该角色造成2点雷电伤害",

	--于吉
	["yuji"] = "于吉",
	["guhuo"] = "蛊惑",
	["guhuo_pile"] = "蛊惑牌",
	[":guhuo"] = "当你需要使用或打出一张基本牌或非延时类锦囊牌时，你可以声明并将一张手牌扣于桌上。若无人质疑，则该牌按你所述之牌来用。若有人质疑，则亮出验明：若为真，质疑者各失去1点体力；若为假，质疑者各摸一张牌，除非被质疑的牌花色是红桃且为真（仍可用），否则无论真假，该牌都作废，弃置之。",
	["#Guhuo"] = "%from 发动了技能<font color='yellow'><b>【蛊惑】</b></font>，声明对 %to 使用 <font color='yellow'><b>%arg</b></font>",
	["#GuhuoNoTarget"] = "%from 发动了<font color='yellow'><b>【蛊惑】</b></font>，声明使用的是 <font color='yellow'><b>%arg</b></font>",
	["#GuhuoCannotQuestion"] = "%from 的体力不合理（%arg 点），无法质疑<font color='yellow'><b>【蛊惑】</b></font>",
	["#GuhuoQuery"] = "%from 表示 %arg",
	["guhuo:question"] = "质疑",
	["guhuo:noquestion"] = "不质疑",
	["question"] = "<font color='yellow'><b>质疑</b></font>",
	["noquestion"] = "<font color='yellow'><b>不质疑</b></font>",	
	["$GuhuoResult"] = "%from 用来<font color='yellow'><b>【蛊惑】</b></font>的牌是 <font color='yellow'><b>%card</b></font>",
	["guhuo-saveself"] = "自救蛊惑",
	["guhuo-saveself:peach"] = "桃子",
	["guhuo-saveself:analeptic"] = "酒",
	
	--武将技能配音
	["$shensu1"] = "吾善于千里袭人。", 
	["$shensu2"] = "取汝首级犹如探囊取物。", 
	
	["$jushou1"] = "我先休息一会。", 
	["$jushou2"] = "尽管来吧！",
	
	["$liegong1"] = "中！",
	["$liegong2"] = "百步穿杨！", 
	
	["$kuanggu1"] = "我会怕你吗？",
	["$kuanggu2"] = "真是美味呀！",
	
	["$hongyan"] = "（红颜）",
	["$tianxiang1"] = "接着哦～",
	["$tianxiang2"] = "替我挡着～",

	["$buqu1"] = "我绝不会倒下！",
	["$buqu2"] = "还不到！", 

	["$leiji1"] = "雷公助我！",
	["$leiji2"] = "以我之真气，合天地之造化。",
	["$guidao1"] = "哼哼哼～", 
	["$guidao2"] = "天下大势，为我所控。",
	["$huangtian1"] = "苍天已死，黄天当立。", 
	["$huangtian2"] = "岁在甲子，天下大吉。",

	["$guhuo1"] = "你信吗？",
	["$guhuo2"] = "猜猜看呐～",	
	
	--武将阵亡台词
	["~caoren"] = "实在是守不住了……",
	["~xiahouyuan"] = "竟然比我还……快……",
	["~huangzhong"] = "不得不服老了……",
	["~weiyan"] = "谁敢杀我！呃啊……",
	["~zhoutai"] = "已经尽力了……",
	["~xiaoqiao"] = "公瑾，我先走一步。",
	["~zhangjiao"] = "黄天…也死了……",
	["~yuji"] = "竟然…被猜到了…",
}
