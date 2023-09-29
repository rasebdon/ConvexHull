#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "quickhull.h"
#include "giftwrapping.h"
#include <memory>

// Helper functions


template <typename T>
bool lists_contain_equal_elements(const std::vector<T>& l1, const std::vector<T>& l2)
{
    if (l1.size() != l2.size()) return false;

    size_t amount = 0;
    for (T e1 : l1)
    {
        for (T e2 : l2)
        {
            if (e1 == e2)
            {
                amount++;
                break;
            }
        }
    }

    return l1.size() == amount;
}

// Tests

TEST_CASE_TEMPLATE("Construct basic convex hull", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 0),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("High floating point colinear line", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, 1),
        Vector2(1.0000001, 1.0000001),
        Vector2(2, 2),
        Vector2(2.0000001, 2.0000001),
        Vector2(3, 3),
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),        
        Vector2(3, 3),
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("High floating point not colinear line", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, 1),
        Vector2(1.0000005, 1.0000000),
        Vector2(2, 2),
        Vector2(2.0000000, 2.0000005),
        Vector2(3, 3),
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),        
        Vector2(1.0000005, 1.0000000),
        Vector2(2.0000000, 2.0000005),
        Vector2(3, 3),
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("Nearly colinear hull", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, -4.99999999999),
        Vector2(1, 0),
        Vector2(1, 4.999999999999),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("Different y levels", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, -4.5),
        Vector2(1, 0),
        Vector2(1, 4.5),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("Colinear points", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(1, 1),
        Vector2(2, 2),
        Vector2(3, 3),
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),        
        Vector2(3, 3),
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}

TEST_CASE_TEMPLATE("Duplicate points", T, quickhull, giftwrapping) 
{
    std::vector<Vector2> points = {
        Vector2(0, 0),
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 0),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::vector<Vector2> expected = {
        Vector2(0, 0),
        Vector2(1, -5),
        Vector2(1, 5),
        Vector2(2, 0)
    };

    std::unique_ptr<T> algorithm = std::make_unique<T>();

    auto calculated = algorithm->Execute(points);

    CHECK(lists_contain_equal_elements(expected, calculated));
}