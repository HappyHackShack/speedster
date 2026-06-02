#include "_config.h"
#include "primitives/all.h"
#include "objects/all.h"
#include "engine/vector3.h"
#include "engine/screen.h"
#include "engine/triangle.h"
#include "engine/reality.h"
#include "engine/world.h"

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
