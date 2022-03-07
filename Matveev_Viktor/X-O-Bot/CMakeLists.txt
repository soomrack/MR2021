# CMakeList.txt: проект CMake для X_O_Improved; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)


add_library (Bot_Strategy Bot_Strategy.cpp)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (X_O_Improved "X_O_Improved.cpp" "X_O_Improved.h" "Bot_Strategy.h")
target_link_libraries(X_O_Improved PUBLIC Bot_Strategy)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
