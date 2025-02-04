#pragma once

#include "IContainer.h"

template <typename T>
class IVector : public IContainer<T>
{
public:
    IVector() = default;

    explicit IVector(const size_t real_size) : IContainer<T>(), real_size{real_size}, def_value{} {
        m_region = new T[real_size];
        for (size_t i{0}; i < real_size; ++i) {
            m_region[i] = def_value;
        }
        logical_size = real_size;
    };

    explicit IVector(const size_t real_size, const T def_value) : IContainer<T>(), real_size{real_size}, def_value{def_value} {
        m_region = new T[real_size];
        for (size_t i{0}; i < real_size; ++i) {
            m_region[i] = def_value;
        }
        logical_size = real_size;
    };

    IVector(const IVector &other) {
        this->logical_size = other.logical_size;
        this->real_size = other.real_size;
        this->def_value = other.def_value;

        this->m_region = new T[this->real_size];

        for (size_t i{0}; i < logical_size; ++i) {
            this->m_region[i] = other.m_region[i];
        }

        std::cout<<"Copy constructor"<<std::endl;
    };
    
    IVector &operator=(const IVector &other) {
        if (this == &other) return *this;

        delete[] this->m_region;

        this->logical_size = other.logical_size;
        this->real_size = other.real_size;
        this->def_value = other.def_value;

        this->m_region = new T[this->real_size];

        for (size_t i{0}; i < logical_size; ++i) {
            this->m_region[i] = other.m_region[i];
        }

        std::cout<<"Assignment copy operator"<<std::endl;

        return *this;        
    };

    IVector(IVector &&other) noexcept {
        this->logical_size = other.logical_size;
        this->real_size = other.real_size;
        this->def_value = other.def_value;
        this->m_region = other.m_region;

        other.def_value = T{};
        other.logical_size = 0;
        other.real_size = 0;
        other.m_region = nullptr;

        std::cout<<"Move constructor"<<std::endl;   
    };

    IVector &operator=(IVector &&other) noexcept {
        
        if (this == &other) return *this;

        delete[] this->m_region;

        this->m_region = other.m_region;
        this->logical_size = other.logical_size;
        this->real_size = other.real_size;
        this->def_value = other.def_value;
        
        other.def_value = T{};
        other.logical_size = 0;
        other.real_size = 0;
        other.m_region = nullptr;

        std::cout<<"Move assignment operator"<<std::endl;  

        return *this;  
    };
    
    void push_back(const T &value) override
    {
        push_back_impl(value);
    };
    
    void push_back(T &&value) override
    {
        push_back_impl(std::move(value));
    };
    
    void capacity(size_t custom){
        if (custom <= real_size) return;
        T* new_region = new T[custom];
        for (size_t i{0}; i < logical_size; ++i) {
            new_region[i] = std::move(m_region[i]);
        };
        delete[] m_region;
        m_region = new_region;
        real_size = custom;     
    }

    void insert(const size_t pos, const T &value) override
    {
        insert_impl(pos, value);
    };
    
    void insert(const size_t pos, T &&value) override
    {
        insert_impl(pos, std::move(value));
    };

 
    void erase(size_t index) override
    {   
        if (index >= logical_size) return; 

        for (size_t i = index; i < logical_size - 1; ++i) {
            m_region[i] = std::move(m_region[i + 1]); 
        }

        logical_size--; 
    };
         
    void resize(size_t size){
        if (size == logical_size) return;

        if (size > real_size) {
            capacity(size);
            for (size_t i{logical_size}; i < size; ++i) {
                m_region[i] = def_value;
            };
            logical_size = size;
              
        } else if (size > logical_size) {
            for (size_t i{logical_size}; i < size; ++i) {
                m_region[i] = def_value;
            };
            logical_size = size;
        } else {
            for (size_t i{size}; i < logical_size; ++i) {
                m_region[i] = def_value;
            };
            logical_size = size;
        }
    }

    const size_t size() const override {
        return getSize();
    }
    
    const size_t get_real_size() const {
        return getReal_Size();
    }
    
    const T& at(const size_t & pos) const {
        if (pos >= logical_size) throw std::out_of_range("Index out of range");

        return m_region[pos];
    }
    
    const T &operator[](const size_t & pos) const {
        return m_region[pos];
    }

    T& at(const size_t & pos) {
        if (pos >= logical_size) throw std::out_of_range("Index out of range");

        return m_region[pos];
    }
    
    T &operator[](const size_t & pos) {
        return m_region[pos];
    }

    void check() const {
        for (size_t i{0}; i < logical_size; ++i) {
            std::cout<<m_region[i]<<" ";
        }    
        std::cout<<std::endl;    
    }

    bool error = false;

    ~IVector() noexcept override {
        delete[] m_region;
    };

private:
    size_t logical_size{};
    size_t real_size{};
    T def_value{};
    T *m_region{nullptr};
    
    template <typename U>
    void push_back_impl(U&& value)
    {
        try
        {   
            if (real_size <= logical_size) {
                T *new_region = new T[static_cast<size_t>(std::ceil((logical_size + 1) * 1.5))];

                for (size_t i{0}; i < logical_size; ++i)
                {
                    new_region[i] = std::move(m_region[i]);
                }

                new_region[logical_size] = std::forward<U>(value);

                delete[] m_region;
                m_region = new_region;
                logical_size += 1;
                real_size = static_cast<size_t>(std::ceil((logical_size) * 1.5));                
            } else {
                m_region[logical_size] = std::forward<U>(value);
                logical_size += 1;
            }
        }
        catch (...) // Использую исходя из специфики code style на работе - могу отлавливать исключения только через bool значения
        {
            error = true;
        }
    }

    template <typename U>
    void insert_impl(const size_t& pos, U&& value)
    {   
        try {
            if (pos > logical_size) return;
                
            if (real_size == logical_size) {
                capacity(static_cast<size_t>(std::ceil((logical_size + 1) * 1.5)));
            }

            
            for (size_t i{logical_size}; i > pos; --i) {
                m_region[i] = std::move(m_region[i - 1]); 
            } 

            m_region[pos] = std::forward<U>(value);
            logical_size += 1;  
        
        } catch (...) {
            error = true;
        }           
    };

    const size_t getSize() const {
        return logical_size;
    }

    const size_t getReal_Size() const {
        return real_size;
    }
};