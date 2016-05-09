#include <iostream>

#define CPPUNIT_ASSERT(condition) \
    if( !(condition) ) { \
        std::cout << "assertion failed Expression: " << #condition << std::endl; \
        std::cout << "file: " << __FILE__ << ", line: " << __LINE__ << std::endl; \
    }
