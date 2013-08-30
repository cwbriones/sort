/*
 * Copyright (C) 2013 Christian Briones
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

// For size_t
#include <cstddef>

static const int GROWTH_FACTOR = 2;

template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

// Min heap
template <class Value>
class MinHeap {
public:
    MinHeap();
    MinHeap(Value* items, size_t size);
    ~MinHeap();
    void insert(Value value);

    Value min() const;
    Value pop_min();

    size_t size() const;
    bool is_empty() const;
private:
    void sift_up();
    void sift_down();
    void grow();
    void shrink();

    size_t parent(size_t i);
    size_t left(size_t i);
    size_t right(size_t i);

    Value* data = nullptr;
    size_t size_ = 0;
    size_t data_size = GROWTH_FACTOR;

    static const size_t npos = -1;
};

template <class Value>
MinHeap<Value>::MinHeap(){
    data = new Value[GROWTH_FACTOR];
}

template <class Value>
MinHeap<Value>::MinHeap(Value* items, size_t size){
    while (data_size < size){
        data_size *= GROWTH_FACTOR;
    }
    data = new Value[data_size];

    for (int i = 0; i < size; i++){
        insert(items[i]);
    }
}

template <class Value>
inline size_t MinHeap<Value>::parent(size_t i){
    if (i == 0){
        return MinHeap<Value>::npos;
    }
    return (i - 1)/2;
}

template <class Value>
inline size_t MinHeap<Value>::left(size_t i){
    int j = 2*i + 1;
    if (j >= size_){
        return MinHeap<Value>::npos;
    }
    return j;
}

template <class Value>
inline size_t MinHeap<Value>::right(size_t i){
    int j = 2*i + 2;
    if (j >= size_){
        return MinHeap<Value>::npos;
    }
    return j;
}

template <class Value>
MinHeap<Value>::~MinHeap(){
    delete[] data;
}

template <class Value>
size_t MinHeap<Value>::size() const {
    return size_;
}

template <class Value>
bool MinHeap<Value>::is_empty() const {
    return size_ == 0;
}

template <class Value>
void MinHeap<Value>::insert(Value value){
    if (++size_ > data_size){
        grow();
    }
    data[size_ - 1] = value;
    sift_up();
}

template <class Value>
void MinHeap<Value>::grow(){
    Value* new_data = new Value[data_size * GROWTH_FACTOR];
    for (int i = 0; i < size_; i++){
        new_data[i] = data[i];
    }
    data_size *= GROWTH_FACTOR;

    delete[] data;
    data = new_data;
}

template <class Value>
void MinHeap<Value>::shrink(){
    if (data_size == GROWTH_FACTOR){
        return;
    }
    Value* new_data = new Value[data_size / GROWTH_FACTOR];
    for (int i = 0; i < size_; i++){
        new_data[i] = data[i];
    }
    data_size /= GROWTH_FACTOR;
    delete[] data;
    data = new_data;
}

template <class Value>
Value MinHeap<Value>::min() const {
    return data[0];
}

template <class Value>
Value MinHeap<Value>::pop_min(){
    Value val = data[0];
    data[0] = data[--size_];
    sift_down();
    if (size_ < data_size / GROWTH_FACTOR){
        shrink();
    }
    return val;
}

template <class Value>
void MinHeap<Value>::sift_up(){
    // Check if heap property is broken
    size_t node = size_ - 1;
    while (node != 0 && data[node] < data[parent(node)]){
        swap(data[node], data[parent(node)]);
        node = parent(node);
    }
}

template <class Value>
void MinHeap<Value>::sift_down(){
    // Check if heap property is broken
    // Iterative method makes it somewhat messy.
    size_t node = 0;
    while (node < size_){
        // If the current node has no children we are done
        if (left(node) == npos && right(node) == npos){
            break;
        }
        // The current node has a child on the left
        else if (right(node) == npos){
            if (data[node] > data[left(node)]){
                swap(data[node], data[left(node)]);
                node = left(node);
            } else {
                break;
            }
        }
        // The current node has a child on the right
        else if (left(node) == npos){
            if (data[node] > data[right(node)]){
                swap(data[node], data[right(node)]);
                node = right(node);
            } else {
                break;
            }
        }
        // The current node has both children
        else {
            size_t child = data[left(node)] < data[right(node)] 
                ? left(node) : right(node);
            if (data[node] > data[child]){
                swap(data[node], data[child]);
                node = child;
            } else {
                break;
            }
        }
    }
} 

#endif // MIN_HEAP_H_
