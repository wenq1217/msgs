-- translation for SP Package

return {
	["sp"] = "SP",
	["sp_cards"] = "SP",
	
	--SP银月枪
	["sp_moonspear"] = "SP银月枪", 
	[":sp_moonspear"] = "你的回合外，若打出了一张黑色的牌，你可以立即指定攻击范围内的一名角色打出一张【闪】，否则受到你对其造成的1点伤害", 
	["@moon-spear-jink"] = "受SP银月枪的影响，你必须打出一张【闪】", 
	
	--杨修
	["yangxiu"] = "杨修", 
	["jilei"] = "鸡肋",
	[":jilei"] = "当你受到伤害时，说出一种牌的类别（基本牌、锦囊牌、装备牌）对你造成伤害的角色不能使用、打出或弃置该类别的手牌直到回合结束。\
	◆弃牌阶段，若仅剩鸡肋牌且手牌超限，此角色需展示其手牌。\
	◆例：若“鸡肋”了装备牌，目标角色2体力，手牌为两张【闪】和三张装备牌，弃牌阶段时此角色必须把两张【闪】弃掉，然后展示这三张装备牌，结束其回合。",
	["danlao"] = "啖酪", 
	[":danlao"] = "当一个锦囊指定了包括你在内的多个目标，你可以立即摸一张牌，若如此做，该锦囊对你无效。",
	["jilei:basic"] = "基本牌", 
	["jilei:equip"] = "装备牌", 
	["jilei:trick"] = "锦囊牌",
	["#Jilei"] = "%from <font color='yellow'><b>【鸡肋】</b></font>了 %to 的 %arg ", 
	["#JileiClear"] = "%from 的<font color='yellow'><b>【鸡肋】</b></font>效果消失",
	["#DanlaoAvoid"] = "%from 发动了技能<font color='yellow'><b>【啖酪】</b></font>，跳过了锦囊 %arg 对他的结算",
	
	--SP关羽
	["sp_guanyu"] = "SP关羽",
	["danji"] = "单骑",
	[":danji"] = "<b>觉醒技</b>，回合开始阶段，若你的手牌数大于你当前的体力值，且本局主公为曹操时，你须减1点体力上限并永久获得技能“马术”。",
	["#DanjiWake"] = "%from 的手牌数（%arg）多于体力值（%arg2）且本局主公为曹操，觉醒技<font color='yellow'><b>【单骑】</b></font>被触发",
	
	--SP蔡文姬
	["sp_caiwenji"] = "SP蔡文姬",
	
	--SP庞德
	["sp_pangde"] = "SP庞德",
	
	--SP孙尚香
	["sp_sunshangxiang"] = "SP孙尚香",
	
	--公孙瓒
	["gongsunzan"] = "公孙瓒", 
	["yicong"] = "义从", 
	[":yicong"] = "<b>锁定技</b>，只要你的体力值大于2点，你计算与其他角色的距离时，始终-1；只要你的体力值为2点或更低，其他角色计算与你的距离时，始终+1。",
	["#YicongAttack"] = "%from 的锁定技<font color='yellow'><b>【义从】</b></font>被触发，与其它角色计算距离时始终<font color='yellow'><b> -1</b></font>",--，%arg
	["#YicongDefend"] = "%from 的锁定技<font color='yellow'><b>【义从】</b></font>被触发，其它角色与之计算距离时始终<font color='yellow'><b> +1</b></font>",--，%arg
	
	--袁术
	["yuanshu"] = "袁术",
	["yongsi"] = "庸肆",
	[":yongsi"] = "<b>锁定技</b>，摸牌阶段，你额外摸X张牌，X为场上现存势力数。弃牌阶段，你需要弃掉至少等同于场上现存势力数的牌（不足则全弃）。",
	["weidi"] = "伪帝",
	[":weidi"] = "<b>锁定技</b>，你视为拥有当前主公的主公技。",
	["#YongsiGood"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，额外摸了 %arg 张牌",
	["#YongsiBad"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，必须弃掉至少 %arg 张牌",
	["#YongsiWorst"] = "%from 的锁定技<font color='yellow'><b>【庸肆】</b></font>被触发，弃掉了所有的装备和手牌（共 %arg 张）",
	
	--SP貂蝉
	["sp_diaochan"] = "SP貂蝉",
	["xuwei"] = "续尾",
	[":xuwei"] = "狗尾续貂，变身为原版貂蝉，每回合限一次。",
	
	--SP马超
	["sp_machao"] = "SP马超",
	
	--虎牢关 神·吕布
	["shenlvbu1"] = "最强神话",
	["shenlvbu2"] = "暴怒的战神",
	["xiuluo"] = "修罗",
	[":xiuluo"] = "回合开始阶段，你可以弃一张手牌来弃置你判定区里的一张延时类锦囊（必须花色相同）。",	
	["shenwei"] = "神威",
	[":shenwei"] = "<b>锁定技</b>，摸牌阶段，你额外摸两张牌；你的手牌上限+2。",	
	["shenji"] = "神戟",
	[":shenji"] = "没装备武器时，你使用的杀可指定至多3名角色为目标。",	
	["@xiuluo"] = "请弃掉一张与指定判定牌花色相同的手牌来将此判定牌弃置",

	["#Reforming"] = "%from 进入重整状态",
	["#ReformingRecover"] = "%from 在重整状态中<font color='#98fb98'><b>回复了 1 点体力</b></font>",
	["#ReformingRevive"] = "%from 重整完毕，回到战场",
	["draw_1v3"] = "重整摸牌",
	["weapon_recast"] = "武器重铸",
	["hulaopass"] = "虎牢关模式",
	
	--杨修
	["$jilei"] = "食之无味，弃之可惜。",
	["$jilei1"] = "食之无肉，弃之有味。",
	["$jilei2"] = "曹公之意，我已了然。",
	["$danlao"] = "一人一口，分而食之。",
	["$danlao1"] = "我喜欢～",
	["$danlao2"] = "来来，一人一口～",
	
	--SP关羽
	["$danji"] = "",
	
	--SP庞德（同原庞德）	
	--SP蔡文姬（同原蔡文姬）	
	--SP孙尚香（同原孙尚香）
	
	--公孙瓒
	["$yicong1"] = "冲啊！",
	["$yicong2"] = "众将听令，摆好阵势，御敌！",
	
	--袁术
	["$yongsi1"] = "玉玺在手，天下我有！",
	["$yongsi2"] = "大汉天下已半入我手！",
	["$weidi1"] = "我才是皇帝！",
	["$weidi2"] = "你们都得听我的号令！",
	
	--SP马超（同原马超）
	--SP貂蝉（同原貂蝉）
	
	--虎牢关 神·吕布
	["$xiuluo"] = "神挡杀神，佛挡杀佛！",
	["$shenwei"] = "挡我者死！",
	["$shenji"] = "神挡杀神，佛挡杀佛！",
	
	--武将阵亡台词	
	["~yangxiu"] = "我故自已死之晚也。",
	["~sp_guanyu"] = "什么？此地名叫麦城？",
	["~sp_pangde"] = "四面都是水，我命休矣……",
	["~sp_caiwenji"] = "",
	["~sp_sunshangxiang"] = "不，还不可以死……",
	["~gongsunzan"] = "我军将败，我已无颜苟活于世。",
	["~yuanshu"] = "可恶，就差一步了……",
	["~sp_machao"] = "（马蹄声）",
	["~sp_diaochan"] = "父亲大人，对不起……",
	["~shenlvbu1"] = "看我杀你们个片甲不留！",
	["~shenlvbu2"] = "呃，不可能！",
}
