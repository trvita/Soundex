
add_executable(soundexUnitTests
    libsoundex/soundex.cpp
)
target_link_libraries(
    soundexUnitTests
    PRIVATE
    GTest::gtest_main
    soundex
)

include(GoogleTest)
gtest_discover_tests(soundexUnitTests)
