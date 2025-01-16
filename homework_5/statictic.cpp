#include "statictic.h"

void Stat_min::statistic(const std::vector<int> &m_nembers) const {
    int min{m_nembers[0]};
    
    for (const int& i : m_nembers) {
        if (i < min) {
            min = i;
        }
    }

    std::cout << "min = " << min << std::endl; 
}

void Stat_max::statistic(const std::vector<int> &m_nembers) const {
    
    int max = *std::max_element(m_nembers.begin(), m_nembers.end());

    std::cout << "max = " << max << std::endl; 
}

void Stat_mean::statistic(const std::vector<int> &m_nembers) const {

    double sum{0.0};

    for (const int& i : m_nembers) {
        sum += i;
    }

    std::cout << "mean = " << sum / static_cast<double>(m_nembers.size()) << std::endl; 
}

void Stat_std::statistic(const std::vector<int> &m_nembers) const {

    double sum_std{0.0};
    double sum{0.0};
    const size_t n{m_nembers.size()};

    for (const int& i : m_nembers) {
        sum += i;
    }

    sum = sum / static_cast<double>(m_nembers.size());

    for (const int& i : m_nembers) {
        sum_std += std::pow((i - sum), 2);
    }

    double std_dev = std::sqrt(sum_std / static_cast<double>(n));

    std::cout << "std = " << std_dev << std::endl; 
}


bool input_stream(std::vector<int>& numbers) {
    std::string inputline;
    int num;

    std::cout << "Array push:" << '\n';

    std::getline(std::cin, inputline);
    std::istringstream stream(inputline);

    while (stream >> num) {
        numbers.push_back(num);
    }

    if (numbers.empty()) {
        std::cout << "Vector Empty" << std::endl; 
        return false;
    }
    return true;
}

int main() {

    std::vector<int> numbers;

    if (!input_stream(numbers)) {
        return 1;
    }

    std::vector<IStatistics*> i_statictic;
    i_statictic.push_back(new Stat_min());
    i_statictic.push_back(new Stat_max());
    i_statictic.push_back(new Stat_mean());
    i_statictic.push_back(new Stat_std());

    for (const IStatistics* stat: i_statictic) {
        stat -> statistic(numbers);
    }

    for (const IStatistics* stat: i_statictic) {
        delete stat;
    }

    return 0;
}

