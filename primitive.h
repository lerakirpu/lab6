#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include <string>
#include <iostream>
#include <stdexcept>

// Базовый абстрактный класс для всех графических примитивов
class Primitive {
public:
    virtual ~Primitive() = default;
    
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
    virtual std::unique_ptr<Primitive> clone() const = 0;
    virtual std::string getName() const = 0;  // Русское название
};

// Конкретные примитивы
class Circle : public Primitive {
private:
    double x, y, radius;
    std::string name;
    
public:
    Circle(double x = 0, double y = 0, double radius = 10, 
           std::string name = "Круг") 
        : x(x), y(y), radius(radius), name(name) {}
    
    void draw() const override {
        std::cout << "Рисую " << name << " в точке (" << x << ", " << y 
                  << ") с радиусом " << radius << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
    
    std::string getName() const override {
        return name;
    }
    
    std::unique_ptr<Primitive> clone() const override {
        return std::make_unique<Circle>(*this);
    }
};

class Rectangle : public Primitive {
private:
    double x, y, width, height;
    std::string name;
    
public:
    Rectangle(double x = 0, double y = 0, double width = 20, double height = 10,
              std::string name = "Прямоугольник")
        : x(x), y(y), width(width), height(height), name(name) {}
    
    void draw() const override {
        std::cout << "Рисую " << name << " в точке (" << x << ", " << y 
                  << ") размером " << width << "x" << height << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
    
    std::string getName() const override {
        return name;
    }
    
    std::unique_ptr<Primitive> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
};

class Line : public Primitive {
private:
    double x1, y1, x2, y2;
    std::string name;
    
public:
    Line(double x1 = 0, double y1 = 0, double x2 = 10, double y2 = 10,
         std::string name = "Линия")
        : x1(x1), y1(y1), x2(x2), y2(y2), name(name) {}
    
    void draw() const override {
        std::cout << "Рисую " << name << " из (" << x1 << ", " << y1 
                  << ") в (" << x2 << ", " << y2 << ")" << std::endl;
    }
    
    std::string getType() const override {
        return "Line";
    }
    
    std::string getName() const override {
        return name;
    }
    
    std::unique_ptr<Primitive> clone() const override {
        return std::make_unique<Line>(*this);
    }
};

class Triangle : public Primitive {
private:
    double x1, y1, x2, y2, x3, y3;
    std::string name;
    
public:
    Triangle(double x1 = 0, double y1 = 0, double x2 = 10, double y2 = 0, 
             double x3 = 5, double y3 = 10, std::string name = "Треугольник")
        : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), name(name) {}
    
    void draw() const override {
        std::cout << "Рисую " << name << " с точками (" 
                  << x1 << ", " << y1 << "), (" 
                  << x2 << ", " << y2 << "), (" 
                  << x3 << ", " << y3 << ")" << std::endl;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
    
    std::string getName() const override {
        return name;
    }
    
    std::unique_ptr<Primitive> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
};

#endif // PRIMITIVE_H