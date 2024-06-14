set(target_name soundexHashGroup)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(${target_name}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/csv-parser/single_include
)

target_sources(
    ${target_name}
    PRIVATE
    soundex_groupby/main.cpp
)

target_link_libraries(
    ${target_name}
    PRIVATE
    gtest
    csv
    nlohmann_json::nlohmann_json
    soundex
)