#ifndef PRIMITIVE_FACTORY_H
#define PRIMITIVE_FACTORY_H

#include <memory>
#include <string>
#include "primitive.h"

class PrimitiveFactory {
public:
    enum class PrimitiveType {
        CIRCLE,
        RECTANGLE,
        LINE,
        TRIANGLE
    };
    
    static std::unique_ptr<Primitive> createPrimitive(PrimitiveType type) {
        switch (type) {
            case PrimitiveType::CIRCLE:
                return std::make_unique<Circle>(0, 0, 10, "Круг");
            case PrimitiveType::RECTANGLE:
                return std::make_unique<Rectangle>(0, 0, 20, 10, "Прямоугольник");
            case PrimitiveType::LINE:
                return std::make_unique<Line>(0, 0, 10, 10, "Линия");
            case PrimitiveType::TRIANGLE:
                return std::make_unique<Triangle>(0, 0, 10, 0, 5, 10, "Треугольник");
            default:
                throw std::invalid_argument("Неизвестный тип примитива");
        }
    }
    
    static std::unique_ptr<Primitive> createPrimitive(const std::string& typeName) {
        if (typeName == "Круг" || typeName == "круг" || typeName == "Circle" || typeName == "circle") 
            return createPrimitive(PrimitiveType::CIRCLE);
        if (typeName == "Прямоугольник" || typeName == "прямоугольник" || 
            typeName == "Rectangle" || typeName == "rectangle") 
            return createPrimitive(PrimitiveType::RECTANGLE);
        if (typeName == "Линия" || typeName == "линия" || typeName == "Line" || typeName == "line") 
            return createPrimitive(PrimitiveType::LINE);
        if (typeName == "Треугольник" || typeName == "треугольник" || 
            typeName == "Triangle" || typeName == "triangle") 
            return createPrimitive(PrimitiveType::TRIANGLE);
        
        throw std::invalid_argument("Неизвестный тип примитива: " + typeName);
    }
};

#endif // PRIMITIVE_FACTORY_H