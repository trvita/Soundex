#include <soundex.hpp>

namespace soundex {
uint32_t soundex_hash(const std::string_view str) {

  if ((str.empty()) || !(std::all_of(str.begin(), str.end(), [](char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
      }))) {
    return 0;
  }

  std::string vowels{"AEOIUY"};
  std::map<char, std::string> replacements{
      {'A', "HW"}, {'1', "BFPV"}, {'2', "CGJKQSXZ"}, {'3', "DT"},
      {'4', "L"},  {'5', "MN"},   {'6', "R"}};

  std::string str_copy(str);
  std::transform(str_copy.begin(), str_copy.end(), str_copy.begin(),
                 [](char c) { return std::toupper(c); });
  auto first = str_copy[0];
  auto it = std::next(str_copy.begin());

  std::transform(it, str_copy.end(), it, [&replacements](char c) {
    auto cur = std::find_if(replacements.begin(), replacements.end(),
                            [&c](const auto &pair) {
                              return pair.second.find(c) != std::string::npos;
                            });
    return cur != replacements.end() ? cur->first : c;
  });
  str_copy.erase(std::unique(it, str_copy.end()), str_copy.end());

  str_copy.erase(std::remove_if(it, str_copy.end(),
                                [&vowels](char c) {
                                  return vowels.find(c) != std::string::npos;
                                }),
                 str_copy.end());

  str_copy[0] = first;
  str_copy.resize(4);
  std::replace_if(
      it, str_copy.end(), [](char c) { return c == '\0'; }, '0');

  uint32_t hash = 0;
  for (size_t i = 0; i < 4; ++i) {
    hash |= static_cast<uint32_t>(str_copy[i]) << (i * 8);
  }
  return hash;
}

std::string hashToString(const uint32_t hash) {
  std::string result(4, '\0');
  for (size_t i = 0; i < 4; ++i) {
    result[i] = static_cast<char>((hash >> (i * 8U)) & 0xFFU);
  }
  return result;
}
} // namespace soundex
/*При реализации алгоритма не пишите циклы, по максимуму пользуйтесь
стандартными алгоритмами: Algorithms library.

В этой части ограничтесь unconstrained версиями алгоритмов, т.е. из
пространства имен std, а не std::ranges. Алгоритм:

    Запоминается первая буква слова.
    Удаляются все вхождения h и w (за исключением первой буквы слова).
    Согласные заменяются на цифры от 1 до 6, причём похожим по звучанию буквам
   соответствуют одинаковые цифры:
        b, f, p, v → 1
        c, g, j, k, q, s, x, z → 2
        d, t → 3
        l → 4
        m, n → 5
        r → 6

    Любая последовательность одинаковых цифр сокращается до одной такой цифры.
    Удаляются все a, e, i, o, u, y (за исключением первой буквы слова).
    Заменяется первый символ буквой, запомненной на шаге 1, делая её
заглавной. Итоговая строка обрезается до первых четырёх символов. Если длина
строки меньше требуемой, недостающие символы заменяются знаком 0.

   marryhannah -> marryanna -> 5a66ya55a -> 5a6ya5a -> 565 -> M65 -> M650
*/
