#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <stdexcept>
#include <initializer_list>
#include <memory>    // For std::uninitialized_copy and std::destroy
#include <utility>   // For std::move and std::forward
#include <iterator>  // For std::distance

template <typename T>
class MyVector {
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t new_capacity) {
        // Handle the case where new_capacity is smaller than current size
        if (new_capacity < m_size) {
            new_capacity = m_size;
        }

        // 1. Allocate a new buffer of raw memory
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        // 2. Move or copy existing elements to the new buffer
        // Using std::uninitialized_move for efficiency and exception safety
        if (m_data) {
            try {
                std::uninitialized_copy(std::make_move_iterator(m_data), std::make_move_iterator(m_data + m_size), new_data);
            } catch (...) {
                // If an exception occurs during construction, clean up the new buffer
                ::operator delete(new_data);
                throw;
            }

            // 3. Destroy the old elements and deallocate the old buffer
            std::destroy(m_data, m_data + m_size);
            ::operator delete(m_data);
        }

        m_data = new_data;
        m_capacity = new_capacity;
    }

public:
    // --- Constructors and Destructor ---
    MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Constructor with initial size
    explicit MyVector(size_t size) : m_size(size), m_capacity(size) {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        // Construct the objects using default constructor
        std::uninitialized_default_construct(m_data, m_data + m_size);
    }

    // Constructor with initial size and value
    MyVector(size_t size, const T& value) : m_size(size), m_capacity(size) {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        // Construct the objects using copy constructor
        std::uninitialized_fill(m_data, m_data + m_size, value);
    }

    // Initializer list constructor
    MyVector(std::initializer_list<T> init) : m_size(init.size()), m_capacity(init.size()) {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        std::uninitialized_copy(init.begin(), init.end(), m_data);
    }

    // Copy constructor
    MyVector(const MyVector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));
        std::uninitialized_copy(other.m_data, other.m_data + other.m_size, m_data);
    }

    // Move constructor
    MyVector(MyVector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Destructor
    ~MyVector() {
        // Call destructors for all constructed objects
        std::destroy(m_data, m_data + m_size);
        // Deallocate the raw memory buffer
        ::operator delete(m_data);
    }

    // --- Assignment Operators ---
    // Copy assignment operator
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector temp = other;         // Use copy constructor for strong exception safety
            *this = std::move(temp);       // Use move assignment
        }
        return *this;
    }

    // Move assignment operator
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            // Clean up existing resources
            std::destroy(m_data, m_data + m_size);
            ::operator delete(m_data);

            // Steal other's resources
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            // Nullify other's state
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // --- Element Access ---
    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    T& at(size_t index) {
        if (index >= m_size) { throw std::out_of_range("Index out of bounds"); }
        return m_data[index];
    }
    const T& at(size_t index) const {
        if (index >= m_size) { throw std::out_of_range("Index out of bounds"); }
        return m_data[index];
    }

    // --- Capacity ---
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }

    // --- Modifiers ---
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            reallocate(new_capacity);
        }
        // Use placement new to construct the object in the next available slot
        new (m_data + m_size) T(value);
        m_size++;
    }

    void pop_back() {
        if (m_size > 0) {
            // Explicitly call the destructor of the last element
            m_size--;
            m_data[m_size].~T(); 
        } else {
            throw std::out_of_range("Cannot pop from an empty vector");
        }
    }

    void clear() {
        // Call destructors for all constructed elements
        std::destroy(m_data, m_data + m_size);
        m_size = 0;
    }

    // --- Iterators ---
    T* begin() { return m_data; }
    const T* begin() const { return m_data; }
    T* end() { return m_data + m_size; }
    const T* end() const { return m_data + m_size; }
};

#endif // MY_VECTOR_HPP

