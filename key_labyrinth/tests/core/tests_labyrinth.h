#ifndef KeyLabyrinth_tests_core_tests_labyrinth_h
#define KeyLabyrinth_tests_core_tests_labyrinth_h

#include <core/labyrinth.h>

namespace KeyLabyrinth {

class LabyrinthTests {
public:
    void execute();
private:
    void basic_tests();
    void test_write_read();

    Labyrinth make_labyrinth() const;
};

}

#endif
