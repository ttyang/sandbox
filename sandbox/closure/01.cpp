
#define IF_1(then_, else_) then_
#define IF_0(then_, else_) else_
#define IF(cond, then_, else_) IF_ ## cond (then_, else_)

IF(1, true, false)
IF(0, true, false)

