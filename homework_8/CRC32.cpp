#include "CRC32.hpp"

#include <array>

// На основе старой, но хорошей реализации
// https://web.archive.org/web/20080303102530/http://c.snippets.org/snip_lister.php?fname=crc_32.c

constexpr std::array<uint32_t, 256> make_crc_table(uint32_t polynomial) {
  std::array<uint32_t, 256> table{};

  for (uint32_t i = 0; i < table.size(); ++i) {
    uint32_t remainder = i;

    for (unsigned long bit = 8; bit > 0; --bit) {
      if (remainder & 1)
        remainder = (remainder >> 1) ^ polynomial;
      else
        remainder = (remainder >> 1);
    }
    table[i] = remainder;
  }
  return table;
}

constexpr auto crc32Table = make_crc_table(0xEDB88320);

uint32_t updateCrc32(uint32_t octet, uint32_t crc) {
  return crc32Table[((crc) ^ (octet)) & 0xff] ^ ((crc) >> 8);
}

uint32_t crc32(const char *bytes, size_t bytesCount, uint32_t current) {
  for (; bytesCount; --bytesCount, ++bytes) {
    current = updateCrc32(static_cast<uint32_t>(*bytes), current);
  }
  return ~current;
}
