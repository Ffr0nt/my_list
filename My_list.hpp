//
// Created by Фёдор Захаров on 29.01.2022.
//

#ifndef MY_LIST_MY_LIST_HPP
#define MY_LIST_MY_LIST_HPP

#pragma once
#include <iostream>
#include<list>

using namespace std;

template<typename T>
class My_List{
public:

    class const_iterator;
    class iterator;

    My_List() = default;

    template<typename T2> My_List(initializer_list<T2> init_list);

    template<typename T2> My_List(size_t size, T2 elem = 0 );

    ~My_List();

    void push_back(const T& el);

    void push_front(const T& el);

    void pop_back();

    void pop_front();

     void clear();

    const_iterator cbegin(){
        return const_iterator(m_ptr_head, this);
    }

    const_iterator cend(){
        return const_iterator(nullptr, this);
    }

    My_List<T>::iterator begin(){
        return  My_List<T>::iterator (m_ptr_head, this);
    }

    My_List<T>::iterator end(){
        return My_List<T>::iterator(nullptr, this);
    }

    size_t size() const noexcept  {return m_size;};



private:
    class Element;
    Element* m_ptr_head = nullptr;
    Element* m_ptr_tail = nullptr;
    size_t m_size=0;
};


    #endif //MY_LIST_MY_LIST_HPP
