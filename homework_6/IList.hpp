#pragma once

#include "IContainer.h"


template <typename T>
class IList : public IContainer<T>
{
public:
    IList () = default;

    struct Node {
        Node* next{nullptr};
        Node* prev{nullptr};
        T data{};
    };

    IList(const IList& other) {
        this->real_size = other.real_size;
        this->def_value = other.def_value;
        this->m_first = nullptr;
        this->m_last = nullptr;

        Node* prev_node = nullptr;

        for (auto it = other.begin(); it != other.end(); ++it) {
            Node* current = it.getNode();
            Node* new_node = new Node{};
            new_node->data = current->data;
            new_node->next = nullptr;
            new_node->prev = prev_node;

            if (prev_node) {
                prev_node->next = new_node;
            } else {
                this->m_first = new_node;
            }

            prev_node = new_node;
        };

        this->m_last = prev_node;

        std::cout<<"Copy constructor"<<std::endl;
    };

    IList& operator=(const IList& other) {
        if (this == &other) return *this;

        Node* current = this->m_first;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        this->real_size = other.real_size;
        this->def_value = other.def_value;
        this->m_first = nullptr;
        this->m_last = nullptr;

        Node* prev_node = nullptr;

        for (auto it = other.begin(); it != other.end(); ++it) {
            Node* current = it.getNode();
            Node* new_node = new Node{};
            new_node->data = current->data;
            new_node->next = nullptr;
            new_node->prev = prev_node;

            if (prev_node) {
                prev_node->next = new_node;
            } else {
                this->m_first = new_node;
            }

            prev_node = new_node;
        };

        this->m_last = prev_node;

        std::cout<<"Assignment copy operator"<<std::endl;
        
        return *this;       
    };

    struct iterator {
        public:
            explicit iterator(Node* current): current{current} {};

            iterator& operator++() {
                if (current) current = current->next;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                if (current) current = current->next;
                return tmp;
            }


            iterator& operator--() {
                if (current) current = current->prev;
                return *this;
            }

            iterator operator--(int) {
                iterator tmp = *this;
                if (current) current = current->prev;
                return tmp;
            }

            T& operator*() const {
                return current->data;
            }   

            T& operator[](const size_t index) {
                if (!current) throw std::out_of_range("Iterator is invalid");

                Node* tmp = current;

                for (size_t i{0}; i < index; i++) {
                    if (tmp == nullptr) throw std::out_of_range("Index out of range");
                    tmp = tmp->next;
                }

                if (tmp == nullptr) throw std::out_of_range("Index out of range");

                return tmp->data;
            }

            bool operator!=(const iterator& other) const {
                return current != other.current;
            }   

            Node* getNode() {
                return getNode_impl();
            }

        private:
            Node* current{nullptr};

            Node* getNode_impl() {
                return current;
            }
    };

    iterator begin() const {
        return iterator(m_first);
    }

    iterator end() const {
        return iterator(nullptr);
    }

    void push_back(const T& value) override {
        push_back_impl(value);
    };

    void push_back(T&& value) override {
        push_back_impl(std::move(value));
    };

    void insert(const size_t pos, const T &value) override {
        insert_impl(pos, value);
    };

    void insert(const size_t pos, T &&value) override {
        insert_impl(pos, std::move(value));
    };

    void erase(size_t value) {
        if (value >= real_size) throw std::out_of_range("Index out of range");


        iterator it = begin();
        for (size_t i{0}; i < value; ++i) {
            ++it;
        }

        Node* to_delnode = it.getNode();

        if (!to_delnode) throw std::out_of_range("Error delete");

        if (to_delnode->prev) {
            to_delnode->prev->next = to_delnode->next;
        } else {
            m_first = to_delnode->next;
        }

        if (to_delnode->next) {
            to_delnode->next->prev = to_delnode->prev;
        } else {
            m_last = to_delnode->prev;
        }

        delete to_delnode;
        --real_size;
    };

    bool error = false;

    const size_t size() const {
        return getSize();
    };

    ~IList() override {
        Node* current = m_first;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        m_first = m_last = nullptr;
        real_size = 0;
    };

private:
    size_t real_size{};
    T def_value{};
    Node* m_first{nullptr};
    Node* m_last{nullptr};
    
    template <typename U>
    void push_back_impl(U&& value) {
        try {
            Node* new_node = new Node{};
            new_node->prev = m_last;  
            new_node->data = std::forward<U>(value); 

            if (m_last) {
                m_last->next = new_node;    
            } else {
                new_node->next = nullptr;
                m_first = new_node;
            }

            real_size += 1;
            m_last = new_node;
        } catch (...) {
            error = true;
        }
    }

    template <typename U>
    void insert_impl(const size_t& pos, U&& value) {
        if (pos > real_size) throw std::out_of_range("Index out of range");
        if (pos == real_size) {
            push_back(std::forward<U>(value));
            return;
        }


        iterator it = begin();
        for (size_t i = 0; i < pos; ++i) {
            ++it;
        }

        Node* insert_node = it.getNode();
        if (!insert_node) throw std::out_of_range("Invalid insert position");

        Node* new_node = new Node{};
        new_node->data = std::forward<U>(value);

        if (insert_node->prev) {
            new_node->prev = insert_node->prev;
            new_node->next = insert_node;
            insert_node->prev->next = new_node;
            insert_node->prev = new_node;
        } else {
            new_node->next = insert_node;
            insert_node->prev = new_node;
            m_first = new_node;
        }

        if (!new_node->next) m_last = new_node;

        ++real_size;
    }

    const size_t getSize() const {
        return real_size;
    }

};