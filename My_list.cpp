//
// Created by Фёдор Захаров on 29.01.2022.
//

#include "My_list.hpp"

#pragma once


template<typename T>
class My_List<T>::const_iterator{
public:
    const_iterator();

    const_iterator(Element* const ptr_el, const My_List* const ptr_mylist): m_ptr_el(ptr_el), m_ptr_mylist(ptr_mylist){};

    const T& operator * () const noexcept {return  m_ptr_el->m_data;}

    const T* operator -> () const noexcept {return &(m_ptr_el->m_data);}

    bool operator == (const const_iterator& iter) const noexcept{
        return ((m_ptr_mylist == iter.m_ptr_mylist) && (m_ptr_el == iter.m_ptr_el));
    }

    bool operator != (const const_iterator& iter) const noexcept{
        return !(*this == iter);
    }

    const_iterator& operator ++ () {
        if(m_ptr_el){
            m_ptr_el = m_ptr_el->m_ptr_next;
        }
        else{
            throw runtime_error("Cannot increment end list iterator");
        }
        return *this;
    }

    const_iterator& operator -- () {
        if(m_ptr_el){
            m_ptr_el = m_ptr_el->m_ptr_prev;
        }
        else{
            throw runtime_error("Cannot decrement end list iterator");
        }
        return *this;
    }

public:
    Element* m_ptr_el = nullptr;
    const My_List * const m_ptr_mylist;
};

template<typename T>
class My_List<T>::iterator : public My_List<T>::const_iterator{
public:
    iterator() = default;

    iterator(Element* const ptr_el, const My_List* const ptr_mylist): const_iterator(ptr_el, ptr_mylist){};

    T& operator * () const noexcept {return  const_iterator::m_ptr_el->m_data;}

    T* operator -> () const noexcept {return &(const_iterator::m_ptr_el->m_data);}
};

template<typename T>
void My_List<T>::push_back(const T& el)
{
    if (m_size == 0)
    {
        Element * ptr_elem = new Element(el, nullptr, nullptr);
        m_ptr_head = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    else
    {
        Element * ptr_elem = new Element(el, m_ptr_tail, nullptr);
        m_ptr_tail->m_ptr_next = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    ++ m_size;
}


template<typename T>
void My_List<T>::push_front(const T& el){
    if (m_size == 0)
    {
        Element * ptr_elem = new Element(el, nullptr, nullptr);
        m_ptr_head = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    else
    {
        Element * ptr_elem = new Element(el, nullptr, m_ptr_head);
        m_ptr_head->m_ptr_prev = ptr_elem;
        m_ptr_head = ptr_elem;
    }
    ++ m_size;
}

template<typename T>
void My_List<T>::pop_front(){
    if (m_size == 0)
    {
        throw runtime_error("U can't decries size of list by pop_front, it is already 0!");
    }
    else
    {
        m_ptr_head = m_ptr_head->m_ptr_next;
        (*m_ptr_head->m_ptr_prev).~Element();
        (*m_ptr_head).m_ptr_prev = nullptr;
    }
    -- m_size;
}

template<typename T>
void My_List<T>::pop_back(){
    if (m_size == 0)
    {
        throw runtime_error("U can't decries size of list by pop_back, it is already 0!");
    }
    else
    {
        m_ptr_tail = m_ptr_tail->m_ptr_prev;
        (*m_ptr_tail->m_ptr_next).~Element();
        (*m_ptr_tail).m_ptr_next = nullptr;
    }
    -- m_size;
}

template<typename T>
template<typename T2>
My_List<T>::My_List(initializer_list<T2> init_list){
    typedef typename initializer_list<T2>::const_iterator c_iter;


    for (c_iter c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
        (*this).push_back (*c_it);
    }
}

template<typename T>
class My_List<T>::Element{
public:
    Element(const T& data, Element* ptr_prev = nullptr, Element* ptr_next = nullptr)
            :m_data(data), m_ptr_prev(ptr_prev), m_ptr_next(ptr_next){}

    Element()=delete;

public:
    T m_data;
    Element* m_ptr_prev;
    Element* m_ptr_next;
};
