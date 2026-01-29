#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <memory>
#include <vector>
#include <algorithm>
#include "document.h"

class DocumentManager {
private:
    std::vector<std::unique_ptr<Document>> documents;
    Document* activeDocument = nullptr;
    
public:
    // Создание нового документа
    Document* createDocument(const std::string& name = "") {
        auto doc = std::make_unique<Document>(name);
        auto* docPtr = doc.get();
        documents.push_back(std::move(doc));
        activeDocument = docPtr;
        
        std::cout << "★ Документ #" << docPtr->getId() << " теперь активен" << std::endl;
        return docPtr;
    }
    
    // Удаление документа по ID
    bool removeDocument(int id) {
        auto it = std::find_if(documents.begin(), documents.end(),
            [id](const auto& doc) { return doc->getId() == id; });
            
        if (it != documents.end()) {
            std::cout << "🗑 Удаление документа #" << id << std::endl;
            
            if (activeDocument == it->get()) {
                activeDocument = nullptr;
                std::cout << "⚠ Активный документ удален" << std::endl;
            }
            
            documents.erase(it);
            return true;
        }
        std::cout << "! Документ #" << id << " не найден" << std::endl;
        return false;
    }
    
    // Установка активного документа
    bool setActiveDocument(int id) {
        for (const auto& doc : documents) {
            if (doc->getId() == id) {
                activeDocument = doc.get();
                std::cout << "★ Активирован документ #" << id << std::endl;
                return true;
            }
        }
        std::cout << "! Документ #" << id << " не найден" << std::endl;
        return false;
    }
    
    // Получение активного документа
    Document* getActiveDocument() const {
        if (!activeDocument) {
            std::cout << "Нет активного документа!" << std::endl;
        }
        return activeDocument;
    }
    
    // Получение документа по ID
    Document* getDocument(int id) const {
        for (const auto& doc : documents) {
            if (doc->getId() == id) {
                return doc.get();
            }
        }
        return nullptr;
    }
    
    // Вывод списка документов
    void listDocuments() const {
        std::cout << "\n════════ Список документов ════════" << std::endl;
        if (documents.empty()) {
            std::cout << "Нет документов" << std::endl;
        } else {
            for (const auto& doc : documents) {
                std::cout << "Документ #" << doc->getId() 
                          << ": \"" << doc->getName() << "\"";
                if (doc.get() == activeDocument) {
                    std::cout << " [АКТИВНЫЙ]";
                }
                std::cout << " (" << doc->getPrimitiveCount() << " примитивов)";
                std::cout << std::endl;
            }
        }
        std::cout << "═══════════════════════════════════" << std::endl;
    }
    
    // Количество документов
    size_t getDocumentCount() const {
        return documents.size();
    }
    
    // Проверка наличия активного документа
    bool hasActiveDocument() const {
        return activeDocument != nullptr;
    }
};

#endif // DOCUMENT_MANAGER_H