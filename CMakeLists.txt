cmake_minimum_required(VERSION 3.10)
project(cpp_task)

set(CMAKE_CXX_STANDARD 14)

file(GLOB CPP_SOURCES "*.cpp")

# Создаем словарь для отслеживания уже использованных имен
set(USED_NAMES "")

foreach(CPP_SOURCE ${CPP_SOURCES})
    # Получаем полное имя файла (с расширением)
    get_filename_component(FULL_NAME ${CPP_SOURCE} NAME)

    # Заменяем точки на подчеркивания в имени
    string(REPLACE "." "_" TARGET_NAME "${FULL_NAME}")

    # Удаляем расширение .cpp из имени цели
    string(REPLACE "_cpp" "" TARGET_NAME "${TARGET_NAME}")

    # Добавляем исполняемый файл с уникальным именем
    add_executable(${TARGET_NAME} ${CPP_SOURCE}
            bintree.cpp)
endforeach()