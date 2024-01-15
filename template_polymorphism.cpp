#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <algorithm>

// Dummy struct describing a square.
struct Square {
    double size;
};

// Dummy struct describing a rectangle.
struct Rectangle {
    double height;
    double width;
};

// Visitor for polygon type name. We need '()' operator overloads to be able to use std::visit later.
struct TypeNameVisitor {
    std::string operator()(const Square& square) const {
        return "square";
    }

    std::string operator()(const Rectangle& rectangle) const {
        return "rectangle";
    }
};

// Function returning polygon typename as an std::string. Polygon is here described as an std::variant<Square, Rectangle>.
std::string type_name(const std::variant<Square, Rectangle>& polygon) {
    return std::visit(TypeNameVisitor{ }, polygon);
}

// Visitor for polygon area. We need '()' operator overloads to be able to use std::visit later.
struct AreaVisitor {
    double operator()(const Square& square) const {
        return square.size * square.size;
    }

    double operator()(const Rectangle& rectangle) const {
        return rectangle.height * rectangle.width;
    }
};

// Function returning polygon area as a double. Polygon is here described as an std::variant<Square, Rectangle>.
double area(const std::variant<Square, Rectangle>& polygon) {
    return std::visit(AreaVisitor{ }, polygon);
}

// Helper static factory to build polygons (variants) more easily.
struct PolygonFactory {
    static std::variant<Square, Rectangle> makeSquare(const double size) {
        return std::variant<Square, Rectangle>{ Square{ size } };
    }

    static std::variant<Square, Rectangle> makeRectangle(const double height, const double width) {
        return std::variant<Square, Rectangle>{ Rectangle{ height, width } };
    }
};

// Helper function that builds polygons of the example as an std::vector of std::variant.
std::vector<std::variant<Square, Rectangle>> build_polygons() {
    return std::vector<std::variant<Square, Rectangle>>{
        PolygonFactory::makeSquare(2), PolygonFactory::makeRectangle(3, 4)
    };
}

// Helper function that displays polygon description on in the prompt.
void print_description(const std::variant<Square, Rectangle>& polygon) {
    std::cout << "Polygon is a " << type_name(polygon) << " with area " << area(polygon) << " m2.\n";
}

int main(int argc, char *argv[]) {
    const auto polygons = build_polygons();
    std::for_each(polygons.begin(), polygons.end(), print_description);
    return 0;
}
