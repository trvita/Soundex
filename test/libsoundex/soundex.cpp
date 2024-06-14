#include <gtest/gtest.h>
#include <soundex.hpp>
using namespace soundex;

TEST(soundex, soundex_A000_Test) {
  uint32_t expected = 808464449;
  EXPECT_EQ(soundex_hash("Aioyea"), expected);
  EXPECT_EQ(soundex_hash("A"), expected);
  EXPECT_EQ(soundex_hash("Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), expected);
  EXPECT_EQ(soundex_hash("Ahhhwwwhwhw"), expected);
  EXPECT_EQ(soundex_hash("Ahoyway"), expected);
}
TEST(soundex, soundex_B456_Test) {
  uint32_t expected = 909456450;
  EXPECT_EQ(soundex_hash("Bolllyneworry"), expected);
  EXPECT_EQ(soundex_hash("Blmr"), expected);
  EXPECT_EQ(soundex_hash("Bhlwnyr"), expected);
}
TEST(soundex, soundex_Z123_Test) {
  uint32_t expected = 858927450;
  EXPECT_EQ(soundex_hash("Zpjt"), expected);
  EXPECT_EQ(soundex_hash("Zpcd"), expected);
  EXPECT_EQ(soundex_hash("Zvgt"), expected);
  EXPECT_EQ(soundex_hash("Zbxd"), expected);
  EXPECT_EQ(soundex_hash("Zpkt"), expected);
  EXPECT_EQ(soundex_hash("Zfsd"), expected);

  EXPECT_EQ(soundex_hash("Zoffywhaqedeooy"), expected);
  EXPECT_EQ(soundex_hash("Zeeebuuuuzotaaa"), expected);
}
TEST(soundex, soundex_INVALID_Test) {
  uint32_t expected = 0;
  EXPECT_EQ(soundex_hash(""), expected);
  EXPECT_EQ(soundex_hash("123456789"), expected);
  EXPECT_EQ(soundex_hash("PASODJ,.dm34nds781.-=-5435/*,.//.,"), expected);
  EXPECT_EQ(soundex_hash("русскиесимволы临摹图画"), expected);
}
TEST(soundex, soundex_BIGSTRING_Test) {
  uint32_t expected = 808464449;
  std::string str{};
  for (int i = 0; i < 2049; i++) {
    str += 'a';
  }
  std::cout << str << '\n';
  EXPECT_EQ(soundex_hash(str), expected);
}

TEST(soundex, soundex_hashToString_Test) {
  uint32_t hash = 808464449;
  std::string expected = "A000";
  EXPECT_EQ(hashToString(hash), expected);
  hash = 875770434;
  expected = "B234";
  EXPECT_EQ(hashToString(hash), expected);
  hash = 808858699;
  expected = "K460";
  EXPECT_EQ(hashToString(hash), expected);
  hash = 808792408;
  expected = "X150";
  EXPECT_EQ(hashToString(hash), expected);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
