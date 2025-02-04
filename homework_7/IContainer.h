#pragma once


template <typename T>
class IContainer {
    public:
        IContainer() = default;
        virtual ~IContainer() noexcept = default;
        IContainer(const IContainer& other) = default;
        IContainer& operator=(const IContainer& other) = default;
        
        virtual void push_back(const T& value) = 0;
        virtual void push_back(T&& value) = 0;

        virtual const size_t size() const = 0;

        virtual void erase(size_t value) = 0;

        virtual void insert(const size_t pos, const T &value) = 0;
        virtual void insert(const size_t pos, T &&value) = 0;
};
