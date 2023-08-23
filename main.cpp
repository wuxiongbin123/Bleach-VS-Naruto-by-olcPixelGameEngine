#define OLC_PGE_APPLICATION

#include "engine.h"
int main()
{
    Example demo;
    if (demo.Construct(1024, 576,1, 1))// ������64 : 1, �ֱ���16 ��10
        demo.Start();
    return 0;
}

