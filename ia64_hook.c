typedef void (*PFHOOK)(void);

extern PFHOOK ski_hook_init, ski_hook, ski_hook_fini;

void hook_init(void)
{
    ski_hook_init();
}

void hook(void)
{
    ski_hook();
}

void hook_fini(void)
{
    ski_hook_fini();
}

typedef int Status;
typedef int Accesstype;
#include "std.h"
#include "types.h"
#include "ia_types.h"
Status iAexec(IAinstInfoPtr info)
{
    return info->execFn(info);
}
