#ifndef COUROUTINE_H
#define COUROUTINE_H

/**
 * @brief "Coroutine" implementation inspired by
 * https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 * 
 */

#define crBegin static int __state=0; switch(__state) { case 0:

#define crYield(x) do { __state=__LINE__; return x; \
                        case __LINE__:; } while (0)

#define crFinish }

#endif
