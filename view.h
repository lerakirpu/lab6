#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>

class View {
public:
    static void displayHeader() {
        std::cout << "ВЕКТОРНЫЙ ГРАФИЧЕСКИЙ РЕДАКТОР" << std::endl;
    }
    
    static void displayMenu() {
        std::cout << "\n═════════════ МЕНЮ ═════════════" << std::endl;
        std::cout << "1. Создать новый документ" << std::endl;
        std::cout << "2. Импортировать документ из файла" << std::endl;
        std::cout << "3. Экспортировать документ в файл" << std::endl;
        std::cout << "4. Создать графический примитив" << std::endl;
        std::cout << "5. Удалить графический примитив" << std::endl;
        std::cout << "6. Показать все документы" << std::endl;
        std::cout << "7. Переключить активный документ" << std::endl;
        std::cout << "8. Отрисовать активный документ" << std::endl;
        std::cout << "9. Показать информацию о документе" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "═══════════════════════════════" << std::endl;
        std::cout << "Выбор: ";
    }
    
    static void displayPrimitiveTypes() {
        std::cout << "\nВыберите тип примитива:" << std::endl;
        std::cout << "1. Круг" << std::endl;
        std::cout << "2. Прямоугольник" << std::endl;
        std::cout << "3. Линия" << std::endl;
        std::cout << "4. Треугольник" << std::endl;
        std::cout << "Выбор: ";
    }
    
    static void displayMessage(const std::string& message) {
        std::cout << message << std::endl;
    }
    
    static void displaySuccess(const std::string& message) {
        std::cout << message << std::endl;
    }
    
    static void displayError(const std::string& message) {
        std::cerr << "ОШИБКА: " << message << std::endl;
    }
    
    static void displaySeparator() {
        std::cout << "────────────────────────────────" << std::endl;
    }
};

#endif