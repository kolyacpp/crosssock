#ifndef __TESTCONFIG_H__
#define __TESTCONFIG_H__

#define FAIL                 \
    {                        \
        std::cout << "FAIL"; \
        exit(0);             \
    }
#define PASS                 \
    {                        \
        std::cout << "PASS"; \
        exit(0);             \
    }

#ifndef TEST_NUMBER
#define PORT 10000
#else
#define PORT (10000 + TEST_NUMBER)
#endif

#endif // __TESTCONFIG_H__