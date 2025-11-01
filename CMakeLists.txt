cmake_minimum_required(VERSION 3.10)
project(Lab04)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(main.exe ./main.cpp)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление тестов
enable_testing()

add_executable(tests tests/test_01.cpp)
target_link_libraries(tests  gtest_main)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)