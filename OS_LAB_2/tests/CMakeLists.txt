include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

# ��� Windows: ��������� ��������� � system
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(MyTests test_main.cpp ../src/logic.cpp)
target_link_libraries(MyTests gtest_main)

include(GoogleTest)
gtest_discover_tests(MyTests)
