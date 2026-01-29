cmake_minimum_required(VERSION 3.10)
project(VectorEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список всех файлов
set(SOURCES 
    main.cpp
)

set(HEADERS
    document.h
    document_manager.h
    primitive.h
    primitive_factory.h
    view.h
)

# Исполняемый файл
add_executable(VectorEditor ${SOURCES})

# Включение текущей директории для заголовков
target_include_directories(VectorEditor PRIVATE .)

# Добавить все заголовки как зависимости
target_sources(VectorEditor PRIVATE ${HEADERS})

# Настройки для разных платформ
if(WIN32)
    message(STATUS "Building for Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32")
elseif(UNIX AND NOT APPLE) 
    message(STATUS "Building for Linux/Unix")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__linux__")
endif()

# Тестовая цель
add_custom_target(test_build
    COMMAND echo "Project builds successfully!"
    DEPENDS VectorEditor
)