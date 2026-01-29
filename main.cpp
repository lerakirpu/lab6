#include <iostream>
#include <memory>
#include <limits>
#include "document_manager.h"
#include "primitive_factory.h"
#include "view.h"

class Controller {
private:
    DocumentManager docManager;
    
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    int getIntInput() {
        int value;
        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            View::displayError("Неверный ввод. Введите число:");
        }
        std::cin.ignore();
        return value;
    }
    
public:
    
    void handleNewDocument() {
        std::string name;
        View::displayMessage("Введите название документа (или Enter для значения по умолчанию):");
        std::getline(std::cin, name);
        
        docManager.createDocument(name);
        View::displaySuccess("Документ создан успешно");
    }
    
    void handleImportDocument() {
        if (!docManager.hasActiveDocument()) {
            View::displayMessage("Нет активного документа. Создаю новый...");
            docManager.createDocument("Импортированный_документ");
        }
        
        std::string filename;
        View::displayMessage("Введите имя файла для импорта:");
        std::getline(std::cin, filename);
        
        if (docManager.getActiveDocument()->importFromFile(filename)) {
            View::displaySuccess("Документ импортирован успешно");
        } else {
            View::displayError("Ошибка импорта");
        }
    }
    
    void handleExportDocument() {
        if (!docManager.hasActiveDocument()) {
            View::displayError("Нет активного документа");
            return;
        }
        
        std::string filename;
        View::displayMessage("Введите имя файла для экспорта:");
        std::getline(std::cin, filename);
        
        if (docManager.getActiveDocument()->exportToFile(filename)) {
            View::displaySuccess("Документ экспортирован успешно");
        } else {
            View::displayError("Ошибка экспорта");
        }
    }
    
    void handleCreatePrimitive() {
        if (!docManager.hasActiveDocument()) {
            View::displayError("Нет активного документа. Создаю новый...");
            docManager.createDocument();
        }
        
        View::displayPrimitiveTypes();
        int choice = getIntInput();
        
        try {
            std::unique_ptr<Primitive> primitive;
            switch (choice) {
                case 1: primitive = PrimitiveFactory::createPrimitive("Круг"); break;
                case 2: primitive = PrimitiveFactory::createPrimitive("Прямоугольник"); break;
                case 3: primitive = PrimitiveFactory::createPrimitive("Линия"); break;
                case 4: primitive = PrimitiveFactory::createPrimitive("Треугольник"); break;
                default: 
                    View::displayError("Неверный выбор");
                    return;
            }
            
            docManager.getActiveDocument()->addPrimitive(std::move(primitive));
            View::displaySuccess("Примитив добавлен в документ");
            
        } catch (const std::exception& e) {
            View::displayError(e.what());
        }
    }
    
    void handleDeletePrimitive() {
        if (!docManager.hasActiveDocument()) {
            View::displayError("Нет активного документа");
            return;
        }
        
        auto* doc = docManager.getActiveDocument();
        if (doc->getPrimitiveCount() == 0) {
            View::displayError("В документе нет примитивов");
            return;
        }
        
        doc->printInfo();
        View::displayMessage("Введите индекс примитива для удаления:");
        size_t index = getIntInput();
        
        if (doc->removePrimitive(index)) {
            View::displaySuccess("Примитив удален");
        } else {
            View::displayError("Неверный индекс");
        }
    }
    
    void handleListDocuments() {
        docManager.listDocuments();
    }
    
    void handleSwitchDocument() {
        if (docManager.getDocumentCount() == 0) {
            View::displayError("Нет доступных документов");
            return;
        }
        
        docManager.listDocuments();
        View::displayMessage("Введите ID документа для переключения:");
        int id = getIntInput();
        
        if (docManager.setActiveDocument(id)) {
            View::displaySuccess("Документ активирован");
        }
    }
    
    void handleRenderDocument() {
        if (!docManager.hasActiveDocument()) {
            View::displayError("Нет активного документа");
            return;
        }
        
        docManager.getActiveDocument()->render();
    }
    
    void handleShowDocumentInfo() {
        if (!docManager.hasActiveDocument()) {
            View::displayError("Нет активного документа");
            return;
        }
        
        docManager.getActiveDocument()->printInfo();
    }
    
    void run() {
        View::displayHeader();
        View::displayMessage("Демонстрация архитектуры MVC для векторного графического редактора");
        
        int choice;
        do {
            View::displayMenu();
            choice = getIntInput();
            View::displaySeparator();
            
            switch (choice) {
                case 1: handleNewDocument(); break;
                case 2: handleImportDocument(); break;
                case 3: handleExportDocument(); break;
                case 4: handleCreatePrimitive(); break;
                case 5: handleDeletePrimitive(); break;
                case 6: handleListDocuments(); break;
                case 7: handleSwitchDocument(); break;
                case 8: handleRenderDocument(); break;
                case 9: handleShowDocumentInfo(); break;
                case 0: View::displayMessage; break;
                default: View::displayError("Неверная опция"); break;
            }
            
        } while (choice != 0);
    }
};

int main() {
    Controller controller;
    controller.run();
    return 0;
}