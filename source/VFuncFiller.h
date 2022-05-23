#if __INTELLISENSE__ == 0
#ifndef NUM_WIDGETS
# error "NUM_WIDGETS needs to be defined!"
#else
#define TOKENPASTE2(x, y) x##y
#define TOKENPASTE(x, y) TOKENPASTE2(x, y)

# if ((__COUNTER__) / 2) < ((NUM_WIDGETS) + 1)
virtual void TOKENPASTE(filler, __COUNTER__)() {}
#  include __FILE__
# endif

#undef TOKENPASTE
#undef TOKENPASTE2

#endif
#endif