#include "_config.h"
#include "vector3.h"
#include "screen.h"
#include "triangle.h"
#include "primitives/all.h"
#include "objects/all.h"
#include "reality.h"
#include "world.h"

int main()
{
    World world;
    world.load_level("level0.txt");
    world.triangle_vertex_split();
    GfxScreen screen{};
    screen.update();
    Reality reality{screen, world};
    reality.loop();
    return 0;
}
