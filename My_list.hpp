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

    template<typename T2> My_List(const initializer_list<T2>& init_list);

    template<typename T2 = int > My_List(const size_t& size,const T2& elem = 0 );

    template<typename T2 = int > My_List( My_List<T2> another_list);

    ~My_List();

    template<typename T2> My_List<T>& operator=(const My_List<T2>& right);

    void push_back(const T& el);

    void push_front(const T& el);

    void pop_back();

    void pop_front();

    template <class... Args>
    void emplace ( const_iterator position , const Args&... args);

    template <class... Args>
    void  emplace_back (const Args&... args);

    template <class... Args>
    void  emplace_front (const Args&... args);

    void insert (const_iterator position ,const T& data);

    void erase (My_List<T>::const_iterator position);

    void clear();

    const_iterator cbegin() {
        return const_iterator(m_ptr_head, this);
    }

    const_iterator cend() {
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
