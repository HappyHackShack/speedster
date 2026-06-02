#include <unistd.h>

#include "_config.h"
#include "objects/all.h"
#include "primitives/all.h"
#include "shapes/all.h"
#include "screen.h"
#include "vector3.h"

#define ROUNDING_ERROR 0.00001

bool close_to(float a, float b)
{
    return (abs(a - b) < ROUNDING_ERROR);
}

void assert(float val, float expected)
{
    if (close_to(val, expected))
        std::cout << UC_TICK;
    else
        std::cout << UC_CROSS;
}

void v3_assert(float val, float expected)
{
    std::cout << "  ";
    assert(val, expected);
    std::cout << std::endl;
}

void v3_assert(Vector3 &v, float x, float y, float z)
{
    std::cout << "  ";
    assert(v.x, x);
    assert(v.y, y);
    assert(v.z, z);
    std::cout << std::endl;
}

void v3_assert_cam(Vector3 &v, float x, float y, float z)
{
    std::cout << "  ";
    assert(v.cam_rel_x, x);
    assert(v.cam_rel_y, y);
    assert(v.cam_rel_z, z);
    std::cout << std::endl;
}

void v3_assert_scrn(Vector3 &v, float sx, float sy)
{
    std::cout << "  ";
    assert(round(v.scrn.x), round(sx));
    assert(round(v.scrn.y), round(sy));
    std::cout << std::endl;
}

void run_object_tests()
{
    std::println("{}Running Object Tests{}", ANSI_YELLOW, ANSI_END);
    Vector3 p1{10, 10, 0}, p2{20, 20, 5}, p3{20, 20, 0}, p4{10, 20, 0};

    // Tree
    Tree tree{&p1, 12};
    std::println("Tree has ");
    for (auto prim : tree.primitives)
    {
        std::print(" ");
        for (auto poly : prim->polygons)
            for (auto tri : poly->triangles)
                tri->print();
    }

    // House
    House hse{&p1, 12};
    std::println("Hse has ");
    for (auto prim : hse.primitives)
    {
        std::print(" ");
        for (auto poly : prim->polygons)
            for (auto tri : poly->triangles)
                tri->print();
    }
}

void run_primitive_tests()
{
    std::println("{}Running Primitive Tests{}", ANSI_YELLOW, ANSI_END);
    Vector3 p1{10, 10, 0}, p2{20, 20, 5}, p3{20, 20, 0}, p4{10, 20, 0};

    // Cone
    Cone cone{&p1, 9.0, 5.0, 4, COL_WOOD};
    std::println("Cone.4 has {} polygons with {} vertices", cone.polygons.size(), cone.vertices.size());
    for (auto poly : cone.polygons)
        for (auto tri : poly->triangles)
            tri->print();
    Cone cone8{&p1, 9.0, 5.0, 8, COL_WOOD};
    std::println("Cone.8 has {} polygons with {} vertices", cone8.polygons.size(), cone8.vertices.size());

    // Cuboid
    Cuboid cube{&p1, &p2, COL_WALL};
    std::println("Cuboid has {} polygons with {} vertices", cube.polygons.size(), cube.vertices.size());
    for (auto poly : cube.polygons)
    {
        // std::println();
        for (auto tri : poly->triangles)
            tri->print();
    }

    // Cylinder
    Cylinder cyl{&p1, 9.0, 5.0, 4, COL_WOOD};
    std::println("Cyl.4 has {} polygons with {} vertices", cyl.polygons.size(), cyl.vertices.size());
    for (auto poly : cyl.polygons)
        for (auto tri : poly->triangles)
            tri->print();
    Cone cyl8{&p1, 9.0, 5.0, 8, COL_WOOD};
    std::println("Cyl.8 has {} polygons with {} vertices", cyl8.polygons.size(), cyl8.vertices.size());
}

void run_polygon_tests()
{
    std::println("{}Running Polygon Tests{}", ANSI_YELLOW, ANSI_END);

    Vector3 p1{1, 1, 0}, p2{2, 1, 0}, p3{2, 2, 0}, p4{1, 2, 0};

    Polygon poly3{3, (Point3 *[]){&p1, &p2, &p3}, COL_WOOD};
    std::println("Poly.3 has {} triangles:", poly3.triangles.size());
    for (auto t : poly3.triangles)
        t->print();
    Polygon poly4{4, (Point3 *[]){&p1, &p2, &p3, &p4}, COL_WOOD};
    std::println("Poly.4 has {} triangles:", poly4.triangles.size());
    for (auto t : poly4.triangles)
        t->print();
}

void run_triangle_tests()
{
    std::println("{}Running Triangle Tests{}", ANSI_YELLOW, ANSI_END);
}

void run_vector3_tests()
{
    std::println("{}Running Vector3 Tests{}", ANSI_YELLOW, ANSI_END);
    Vector3 v123{1, 2, 3}, v246, v654{6, 5, 4}, v777, v34t{3, 4, 12};

    // Creation and printing
    std::cout << ANSI_CYAN << "Create " << ANSI_END;
    std::cout << "Vec123 is ";
    v123.print();
    v3_assert(v123, 1, 2, 3);

    std::cout << ANSI_CYAN << "Length " << ANSI_END;
    float l = v34t.len();
    std::cout << "Len is " << l;
    v3_assert(l, 13);

    std::cout << ANSI_CYAN << "Assignment " << ANSI_END;
    v777 = v123;
    std::cout << "Vec777 is ";
    v777.print();
    v3_assert(v777, 1, 2, 3);

    std::cout << ANSI_CYAN << "Translate " << ANSI_END;
    v777.translate(v654);
    std::cout << "Vec777 is ";
    v777.print();
    v3_assert(v777, 7, 7, 7);

    std::cout << ANSI_CYAN << "Translate_R " << ANSI_END;
    v777.translate_r(v654);
    std::cout << "Vec777 is ";
    v777.print();
    v3_assert(v777, 1, 2, 3);

    std::cout << ANSI_CYAN << "Op Addition " << ANSI_END;
    v777 = v123 + v654;
    std::cout << "Vec777 is ";
    v777.print();
    v3_assert(v777, 7, 7, 7);

    std::cout << ANSI_CYAN << "Op Subtraction " << ANSI_END;
    v777 = v654 - v123;
    std::cout << "Vec777 is ";
    v777.print();
    v3_assert(v777, 5, 3, 1);

    std::cout << ANSI_CYAN << "Op Multiplication " << ANSI_END;
    v246 = v123 * 2;
    std::cout << " Vec246 is ";
    v246.print();
    v3_assert(v246, 2, 4, 6);

    std::cout << ANSI_CYAN << "Op Division " << ANSI_END;
    v123 = v246 / 2;
    std::cout << " Vec123 is ";
    v123.print();
    v3_assert(v123, 1, 2, 3);

    std::cout << ANSI_CYAN << "Dot-Prod " << ANSI_END;
    float dp = v246.dot_prod(v123);
    std::cout << "vec123 ● vec246 = " << dp;
    v3_assert(dp, 28);

    Vector3 v123a;
    std::cout << ANSI_CYAN << "Rotate-Z ccw-90 " << ANSI_END;
    v123a = v123;
    v123a.rotate_about_z(M_PI_2f);
    std::cout << "vec123 ⟲ ";
    v123a.print();
    v3_assert(v123a, -2, 1, 3);

    std::cout << ANSI_CYAN << "Rotate-Z ccw-180 " << ANSI_END;
    v123a = v123;
    v123a.rotate_about_z(M_PIf);
    std::cout << "vec123 ⟲ ";
    v123a.print();
    v3_assert(v123a, -1, -2, 3);

    std::cout << ANSI_CYAN << "Rotate-Z cw-90 " << ANSI_END;
    v123a = v123;
    v123a.rotate_about_z(-M_PI_2f);
    std::cout << "vec123 ⟳ ";
    v123a.print();
    v3_assert(v123a, 2, -1, 3);

    std::cout << ANSI_CYAN << "Rotate-Z cw-180 " << ANSI_END;
    v123a = v123;
    v123a.rotate_about_z(-M_PIf);
    std::cout << "vec123 ⟳ ";
    v123a.print();
    v3_assert(v123a, -1, -2, 3);

    std::cout << ANSI_CYAN << "Camera 1 " << ANSI_END;
    v246.calc_cam_rel(v123, -M_PI_2f);
    std::cout << "vec246 ";
    v246.print_cam();
    v3_assert_cam(v246, -2, 1, 3);

    Vector3 tl{-10, 20, 5};
    Vector3 tr{10, 20, 5};
    Vector3 bl{-10, 20, -5};
    Vector3 br{10, 20, -5};
    tl.project_2d();
    tr.project_2d();
    bl.project_2d();
    br.project_2d();
    std::cout << ANSI_CYAN << "Project TL " << ANSI_END;
    std::cout << "TL ";
    tl.print_scrn();
    v3_assert_scrn(tl, 320, 240);
    std::cout << ANSI_CYAN << "Project TR " << ANSI_END;
    std::cout << "TR ";
    tr.print_scrn();
    v3_assert_scrn(tr, 960, 240);
    std::cout << ANSI_CYAN << "Project BL " << ANSI_END;
    std::cout << "BL ";
    bl.print_scrn();
    v3_assert_scrn(bl, 320, 560);
    std::cout << ANSI_CYAN << "Project BR " << ANSI_END;
    std::cout << "BR ";
    br.print_scrn();
    v3_assert_scrn(br, 960, 560);

    // Vector3 tgt1{-10, 0.1, 5}, tgt2{10, 0.1, 5}, tgt3{-10, 0.1, -5}, tgt4{10, 0.1, -5};
    // tgt1.project_2d(v123);
    // tgt1.print_scrn();
    // tgt2.project_2d(v123);
    // tgt2.print_scrn();
    // tgt3.project_2d(v123);
    // tgt3.print_scrn();
    // tgt4.project_2d(v123);
    // tgt4.print_scrn();
    Vector3 btl{-10, -20, 5};
    Vector3 btr{10, -20, 5};
    Vector3 bbl{-10, -20, -5};
    Vector3 bbr{10, -20, -5};
    btl.project_2d();
    btr.project_2d();
    bbl.project_2d();
    bbr.project_2d();
    std::cout << ANSI_CYAN << "Project -TL " << ANSI_END;
    std::cout << "-TL ";
    btl.print_scrn();
    v3_assert_scrn(btl, -63360, -31600);
    std::cout << ANSI_CYAN << "Project -TR " << ANSI_END;
    std::cout << "-TR ";
    btr.print_scrn();
    v3_assert_scrn(btr, 64640, -31600);
    std::cout << ANSI_CYAN << "Project -BL " << ANSI_END;
    std::cout << "-BL ";
    bbl.print_scrn();
    v3_assert_scrn(bbl, -63360, 32400);
    std::cout << ANSI_CYAN << "Project -BR " << ANSI_END;
    std::cout << "-BR ";
    bbr.print_scrn();
    v3_assert_scrn(bbr, 64640, 32400);
}

void run_screen_tests()
{
    std::println("{}Running Screen Tests{}", ANSI_YELLOW, ANSI_END);
    GfxScreen screen;
    screen.clear();

    // Basic Lines
    SDL_FPoint p1a{10, 10}, p1b{100, 10}, p2a{20, 20}, p2b{90, 20};
    screen.draw_line(p1a, p1b, COL_LEAVES);
    screen.draw_line(p2a, p2b, COL_WOOD);

    // Basic Triangles
    SDL_FPoint t1{125, 25}, t2{200, 75}, t3{125, 125};
    screen.draw_triangle(t1, t2, t3, COL_CLEAR, COL_WOOD);
    t1.x += 100;
    t2.x += 100;
    t3.x += 100;
    screen.draw_triangle(t1, t2, t3, COL_LEAVES, COL_CLEAR);
    t1.x += 100;
    t2.x += 100;
    t3.x += 100;
    screen.draw_triangle(t1, t2, t3, COL_WALL, COL_LEAVES);

    // Basic Quadrilaterals
    SDL_FPoint q1{125, 200}, q2{200, 225}, q3{200, 275}, q4{125, 325};
    screen.draw_quad(q1, q2, q3, q4, COL_CLEAR, COL_LEAVES);
    q1.x += 100;
    q2.x += 100;
    q3.x += 100;
    q4.x += 100;
    screen.draw_quad(q1, q2, q3, q4, COL_LEAVES, COL_CLEAR);
    q1.x += 100;
    q2.x += 100;
    q3.x += 100;
    q4.x += 100;
    screen.draw_quad(q1, q2, q3, q4, COL_SLATE, COL_ROOF);
    
    screen.testing_text();
    //
    screen.update();
    sleep(5);
}

char menu()
{
    char ch;
    std::cout << "\n*************** Testing Menu ***************\n";
    std::cout << "v" << ") run Vector3 tests\n";
    std::cout << "t" << ") run Triangle tests\n";
    std::cout << "y" << ") run Polygon tests\n";
    std::cout << "p" << ") run Primitive tests\n";
    std::cout << "o" << ") run Object tests\n";
    std::cout << "s" << ") run Screen tests\n";
    std::cout << "A" << ") run All tests\n";
    std::cout << "q" << ") Quit\n";
    std::cout << "Selection: ";
    // std::cout
    std::cin >> ch;
    std::cin.ignore();
    return ch;
}

int main(int argc, char *argv[])
{
    // std::println("{}{}{}", ANSI_BOX_TL, std::string(34,'-'), ANSI_BOX_TR);
    std::println("{} {}Welcome to the Speedster Testing{} {}", "|", ANSI_MAGENTA, ANSI_END, "|");
    // std::println("{}{}{}", ANSI_BOX_BL, std::string(34,'-'), ANSI_BOX_BR);
    for (;;)
    {
        switch (menu())
        {
        case 'v':
            run_vector3_tests();
            break;
        case 't':
            run_triangle_tests();
            break;
        case 'y':
            run_polygon_tests();
            break;
        case 'p':
            run_primitive_tests();
            break;
        case 'o':
            run_object_tests();
            break;
        case 's':
            run_screen_tests();
            break;
        case 'A':
            std::println("Running ALL Tests ...");
            run_vector3_tests();
            run_triangle_tests();
            run_polygon_tests();
            run_primitive_tests();
            run_object_tests();
            break;
        case 'q':
            return 0;
        }
    }
}
