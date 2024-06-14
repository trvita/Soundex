
add_library(soundex
    soundex/soundex.cpp
    soundex/soundex.hpp
)
target_include_directories(soundex
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/soundex
)