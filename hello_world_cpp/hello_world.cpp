#include <stdio.h>

class Test
{
public:
    Test(const char* arg)
    {
        printf("%s_constructor\n", arg);
    }
};

static Test constructor_test("static");

extern "C" int hello2(int arg) {
    printf("Hello World! arg=%d\n", arg);
    return -arg;
}

extern "C" int test2(void) {
    return (hello2(11) == -11 && hello2(-22) == 22);
}

extern "C" int test3(int a, int b, int c) {
    printf("test3 %d %d %d\n", a, b, c);
    return a;
}
