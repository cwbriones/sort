#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <cstddef>
#include <iostream>
#include <utility>

static const int GROWTH_FACTOR = 2;


template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

// Max heap
template <class Value>
class MaxHeap {
public:
    MaxHeap();
    MaxHeap(Value* items, size_t size);
    ~MaxHeap();
    void insert(Value value);

    Value max() const;
    Value pop_max();

    size_t size() const;
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
MaxHeap<Value>::MaxHeap(){
    data = new Value[GROWTH_FACTOR];
}

template <class Value>
MaxHeap<Value>::MaxHeap(Value* items, size_t size){
    while (data_size < size){
        data_size *= GROWTH_FACTOR;
    }
    data = new Value[GROWTH_FACTOR];
    for (int i = 0; i < size; i++){
        insert(items[i]);
    }
}

template <class Value>
inline size_t MaxHeap<Value>::parent(size_t i){
    if (i == 0){
        return MaxHeap<Value>::npos;
    }
    return (i - 1)/2;
}

template <class Value>
inline size_t MaxHeap<Value>::left(size_t i){
    int j = 2*i + 1;
    if (j >= size_){
        return MaxHeap<Value>::npos;
    }
    return j;
}

template <class Value>
inline size_t MaxHeap<Value>::right(size_t i){
    int j = 2*i + 2;
    if (j >= size_){
        return MaxHeap<Value>::npos;
    }
    return j;
}

template <class Value>
MaxHeap<Value>::~MaxHeap(){
    delete[] data;
}

template <class Value>
size_t MaxHeap<Value>::size() const {
    return size_;
}

template <class Value>
void MaxHeap<Value>::insert(Value value){
    if (++size_ > data_size){
        grow();
    }
    data[size_ - 1] = value;
    sift_up();
}

template <class Value>
void MaxHeap<Value>::grow(){
    Value* new_data = new Value[data_size * GROWTH_FACTOR];
    for (int i = 0; i < data_size; i++){
        new_data[i] = data[i];
    }
    data_size *= GROWTH_FACTOR;
    delete[] data;
    data = new_data;
}

template <class Value>
void MaxHeap<Value>::shrink(){
    if (data_size == GROWTH_FACTOR){
        return;
    }
    Value* new_data = new Value[data_size / GROWTH_FACTOR];
    for (int i = 0; i < data_size; i++){
        new_data[i] = data[i];
    }
    data_size /= GROWTH_FACTOR;
    delete[] data;
    data = new_data;
}

template <class Value>
Value MaxHeap<Value>::max() const {
    return data[0];
}

template <class Value>
Value MaxHeap<Value>::pop_max(){
    Value val = data[0];
    size_--;
    data[0] = data[size_];
    sift_down();
    if (size_ < data_size / GROWTH_FACTOR){
        shrink();
    }
    return val;
}

template <class Value>
void MaxHeap<Value>::sift_up(){
    // Check if heap property is broken
    size_t node = size_ - 1;
    while (node != 0 && data[node] > data[parent(node)]){
        swap(data[node], data[parent(node)]);
        node = parent(node);
    }
}

template <class Value>
void MaxHeap<Value>::sift_down(){
    // Check if heap property is broken
    // Iterative method makes it somewhat messy.
    size_t node = 0;
    while (node < size_){
        // If the current node has no children we are done
        if (left(node) < 0 && right(node) < 0){
            break;
        }
        else if (right(node) < 0 && left(node) < size_){
            if (data[node] < data[left(node)]){
                swap(data[node], data[left(node)]);
                node = left(node);
            } else {
                break;
            }
        }
        else if (left(node) < 0 && right(node) < size_){
            if (data[node] < data[right(node)]){
                swap(data[node], data[right(node)]);
                node = right(node);
            } else {
                break;
            }
        }
        else {
            size_t child = data[left(node)] > data[right(node)] 
                ? left(node) : right(node);
            if (data[node] < data[child]){
                swap(data[node], data[child]);
                node = child;
            } else {
                break;
            }
        }
    }
}

template <class T>
void heap_sort(T* items, size_t size){
    MaxHeap<T> heap(items, size);
    for (int i = 0; i < size; i++){
        items[size - i - 1] = heap.pop_max();
    }
}

#endif // MIN_HEAP_H_
