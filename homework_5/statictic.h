#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <cmath>    

class IStatistics {
    public:

        IStatistics() = default;
        virtual ~IStatistics() = default;
        virtual void statistic(const std::vector<int> &m_nembers) const = 0;
};

class Stat_min : public IStatistics {
    public:
        void statistic(const std::vector<int> &m_nembers) const override;
};

class Stat_max : public IStatistics {
    public:
        void statistic(const std::vector<int> &m_nembers) const override;
};

class Stat_mean : public IStatistics {
    public:
        void statistic(const std::vector<int> &m_nembers) const override;
};

class Stat_std : public IStatistics {
    public:
        void statistic(const std::vector<int> &m_nembers) const override;
};
