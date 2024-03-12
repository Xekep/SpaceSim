#include "Universe.h"

int main()
{
    auto universe = std::make_unique<Universe>(640, 480, "Universe");
    universe->Run();
    return 0;
}