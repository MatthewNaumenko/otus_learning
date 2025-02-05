#include "IO.hpp"

#include <array>
#include <fstream>

template <class Stream>
Stream openFile(const char *path) {
  Stream s(path, std::ios::binary);

  if (!s.is_open()) {
    throw std::runtime_error("Can't open file");
  }
  return s;
}

std::vector<char> readFromFile(const char *path) {
  auto in = openFile<std::ifstream>(path);

  std::vector<char> data;
  std::array<char, 4096> buffer{};
  std::streamsize bytes{1};

  while (bytes > 0) {
    in.read(buffer.data(), buffer.size());
    bytes = in.gcount();
    data.insert(data.end(), buffer.data(), buffer.data() + bytes);
  }
  return data;
}

void writeToFile(const char *path, const std::vector<char> &data) {
  openFile<std::ofstream>(path).write(
      data.data(), static_cast<std::streamsize>(data.size()));
}
