cmake_minimum_required(VERSION 3.16)
project(textstats VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- библиотека с логикой программы ---
add_library(text_stats STATIC src/text_stats.cpp)
target_include_directories(text_stats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# --- сама программа ---
add_executable(textstats src/main.cpp)
target_link_libraries(textstats PRIVATE text_stats)

# --- тесты ---
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests tests/test_text_stats.cpp)
target_link_libraries(unit_tests PRIVATE text_stats GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

# --- интеграционный тест: запуск собранной программы на файле-примере ---
add_test(NAME cli_top
         COMMAND textstats ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/sample.txt --top 3)
set_tests_properties(cli_top PROPERTIES PASS_REGULAR_EXPRESSION "the: 4")
