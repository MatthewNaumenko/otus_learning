#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

std::vector<char> global_result;
std::atomic_bool found{false};

void selection(const size_t& id_thread, const size_t& first, const size_t& last, 
              const uint32_t originalCrc32, std::vector<char>& result_thread) {
    for (size_t high = first; high < last && !found; ++high) {
        for (uint16_t  low = 0; low <= 0xFFFF && !found; ++low) {
            uint32_t i = (static_cast<uint32_t>(high) << 16) | low;
            replaceLastFourBytes(result_thread, uint32_t(i));
            // Вычисляем CRC32 текущего вектора result
            uint32_t currentCrc32 = crc32(result_thread.data() + result_thread.size() - 4, 4, originalCrc32);

            if (currentCrc32 == originalCrc32) {
              if (!found) {
                  std::cout << "Success\n";
                  global_result = result_thread;
                  found =  true;
              }
              return;
            }
        }
    }
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
   * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */
  size_t maxVal = 0xFFFF;

  size_t hardware_concurrency{1};

  if (std::thread::hardware_concurrency() != 0) {
      hardware_concurrency = static_cast<int>(std::thread::hardware_concurrency());
  } 

  const size_t step_maxVal = maxVal / hardware_concurrency;

  std::vector<std::thread> threads;
  size_t step_first{0};
  size_t step_last = step_maxVal;
  
  for (size_t i = 0; i < hardware_concurrency; ++i) {
      std::cout <<"Thread:" << i << " " << step_first << " " << step_last <<std::endl;
      threads.emplace_back(selection, i, step_first, step_last, originalCrc32, std::ref(result));
      step_first = step_last;   
      step_last = std::min(step_last + step_maxVal, maxVal);
  }

  for (auto& t : threads) {
        t.join();
  }

  return global_result;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
