// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <mutex>


const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;
Counter freq_dict;
std::mutex counter_mutex;

std::string tolower(const std::string &str);

void thread_preparation(std::string str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    if (argc == 2) {
        std::ifstream input{argv[1]};
        if (!input.is_open()) {
            std::cerr << "Failed to open file " << argv[1] << '\n';
            return EXIT_FAILURE;
        }
        count_words(input, freq_dict);

        print_topk(std::cout, freq_dict, TOPK);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
        return EXIT_SUCCESS;
    }

    unsigned int count_thread{std::thread::hardware_concurrency()};
    std::vector<std::thread> threads;

    for (int i = 1; i < argc; ++i) {
        std::string file = argv[i];

        if (count_thread > 0) {
            threads.emplace_back(thread_preparation, std::move(file));
            --count_thread;
        } else {
            thread_preparation(std::move(file));
        }  
    }

    for (auto& t : threads) {
        t.join();
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";

    return EXIT_SUCCESS;
}

void thread_preparation(std::string str) {
        Counter local_freq_dict;
        std::ifstream input{str};
        if (!input.is_open()) {
            std::cerr << "Failed to open file " << str << '\n';
            return;
        }
        count_words(input, local_freq_dict);

        counter_mutex.lock();

        for (auto& [word, count] : local_freq_dict) {
            freq_dict[word] += count;
        }

        counter_mutex.unlock();
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}