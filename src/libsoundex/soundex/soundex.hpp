#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
namespace soundex {
[[nodiscard]] uint32_t soundex_hash(const std::string_view str);
[[nodiscard]] std::string hashToString(const uint32_t hash);
} // namespace soundex
