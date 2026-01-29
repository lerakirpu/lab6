#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "primitive.h"

class Document {
private:
    std::vector<std::unique_ptr<Primitive>> primitives;
    std::string name;
    static int documentCounter;
    int id;
    
public:
    Document(const std::string& docName = "") 
        : name(docName.empty() ? "Документ_" + std::to_string(++documentCounter) : docName),
          id(documentCounter) {
        std::cout << "✓ Создан документ #" << id << " \"" << name << "\"" << std::endl;
    }
    
    ~Document() {
        std::cout << "✗ Удален документ #" << id << std::endl;
    }
    
    // Добавление примитива
    void addPrimitive(std::unique_ptr<Primitive> primitive) {
        if (primitive) {
            primitives.push_back(std::move(primitive));
            std::cout << "+ Добавлен " << primitives.back()->getName() 
                      << " в документ #" << id << std::endl;
        }
    }
    
    // Удаление примитива по индексу
    bool removePrimitive(size_t index) {
        if (index < primitives.size()) {
            std::string name = primitives[index]->getName();
            primitives.erase(primitives.begin() + index);
            std::cout << "- Удален " << name << " по индексу " << index 
                      << " из документа #" << id << std::endl;
            return true;
        }
        std::cout << "! Ошибка: индекс " << index << " выходит за границы" << std::endl;
        return false;
    }
    
    // Импорт из файла
    bool importFromFile(const std::string& filename) {
        std::cout << "↓ Импорт документа #" << id << " из файла: " 
                  << filename << std::endl;
        // Имитация импорта - добавляем тестовые примитивы
        addPrimitive(std::make_unique<Circle>(5, 5, 8, "Импортированный круг"));
        addPrimitive(std::make_unique<Rectangle>(10, 10, 15, 7, "Импортированный прямоугольник"));
        std::cout << "  Импортировано " << primitives.size() << " примитивов" << std::endl;
        return true;
    }
    
    // Экспорт в файл
    bool exportToFile(const std::string& filename) const {
        std::cout << "↑ Экспорт документа #" << id << " в файл: " 
                  << filename << std::endl;
        std::cout << "  Содержит " << primitives.size() << " примитивов:" << std::endl;
        for (size_t i = 0; i < primitives.size(); ++i) {
            std::cout << "    [" << i << "] " << primitives[i]->getName() << std::endl;
        }
        std::cout << "  Экспорт завершен успешно" << std::endl;
        return true;
    }
    
    // Очистка документа
    void clear() {
        primitives.clear();
        std::cout << "× Очищен документ #" << id << std::endl;
    }
    
    // Получение информации
    void printInfo() const {
        std::cout << "\n════════ Документ #" << id << " ════════" << std::endl;
        std::cout << "Название: " << name << std::endl;
        std::cout << "Количество примитивов: " << primitives.size() << std::endl;
        
        if (primitives.empty()) {
            std::cout << "  (нет примитивов)" << std::endl;
        } else {
            for (size_t i = 0; i < primitives.size(); ++i) {
                std::cout << "  [" << i << "] " << primitives[i]->getName() << std::endl;
            }
        }
        std::cout << "═══════════════════════════════════" << std::endl;
    }
    
    // Отрисовка всех примитивов
    void render() const {
        std::cout << "\nОтрисовка документа #" << id << ":" << std::endl;
        std::cout << "┌─────────────────────────────────┐" << std::endl;
        if (primitives.empty()) {
            std::cout << "│   Документ пуст               │" << std::endl;
        } else {
            for (const auto& primitive : primitives) {
                primitive->draw();
            }
        }
        std::cout << "└─────────────────────────────────┘" << std::endl;
    }
    
    // Геттеры
    int getId() const { return id; }
    const std::string& getName() const { return name; }
    size_t getPrimitiveCount() const { return primitives.size(); }
    
    // Получение примитива
    const Primitive* getPrimitive(size_t index) const {
        if (index < primitives.size()) return primitives[index].get();
        return nullptr;
    }
};

// Инициализация статической переменной
int Document::documentCounter = 0;

#endif // DOCUMENT_H