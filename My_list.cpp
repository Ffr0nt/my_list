//
// Created by Фёдор Захаров on 29.01.2022.
//

#include "My_list.hpp"

#pragma once
//-----------------------------------------|classes|--------------------------------------------

template<typename T>
class My_List<T>::const_iterator{
public:
    const_iterator();

//
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
//        if(this == m_ptr_mylist->end()){
//            m_ptr_el =  m_ptr_mylist->m_ptr_tail;
//        }
        else{
            throw runtime_error("Cannot decrement end list iterator");
        }
        return *this;
    }

    const_iterator& advance(int amount){
        if (amount > 0) {
            for (int i = 0; i < amount; ++i) {
                ++(*this);
            }
        }
        if (amount < 0) {
            for (int i = 0; i > amount; --i) {
                --(*this);
            }
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

//----------------------------------|constructors + destructors|----------------------------------


template<typename T>
template<typename T2>
My_List<T>::My_List(initializer_list<T2> init_list){
    typedef typename initializer_list<T2>::const_iterator c_iter;


    for (c_iter c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
        (*this).push_back (*c_it);
    }
}

template<typename T>
My_List<T>::~My_List(){ (*this).clear(); }

template<typename T>
template<typename T2>
My_List<T>::My_List(size_t size, T2 elem ){

    for (int i =0; m_size < size ; i ++){
        (*this).push_front( T(elem) );
    }

}


template<typename T>
template<typename T2>
My_List<T>::My_List(const My_List<T2> another_list){
    typedef typename My_List<T2>::const_iterator c_iter;

    for (c_iter c_it = another_list.cbegin(); c_it != another_list.cend(); ++c_it){
        (*this).push_front( T(*c_it) );
    }
}

//----------------------------------------|list methods|---------------------------------------------

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
    if (m_size == 1)
    {
        (*m_ptr_tail).~Element();
        m_ptr_tail = nullptr;
        m_ptr_head = nullptr;
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
    if (m_size == 1)
    {
        (*m_ptr_tail).~Element();
        m_ptr_tail = nullptr;
        m_ptr_head = nullptr;
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
void My_List<T>::erase(My_List<T>::const_iterator position){
    if (position == this->cbegin()){this->pop_front(); return;}

    if (position == this->cend()){this->pop_back(); return;}

    auto next = position.m_ptr_el->m_ptr_next;
    auto prev = position.m_ptr_el->m_ptr_prev;

    position.m_ptr_el->m_ptr_next->m_ptr_prev = prev;
    position.m_ptr_el->m_ptr_prev->m_ptr_next = next;
    (*m_ptr_tail).~Element();


    -- m_size;
}

template<typename T>
template<class... Args>
void My_List<T>::emplace_front(const Args&... args) {
    if (m_size == 0)
    {
        T  data =  T ( args... );
        Element * ptr_elem = new Element(data ,nullptr,nullptr);
        m_ptr_head = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    else
    {
        T  data =  T (args...);
        Element * ptr_elem = new  Element( data ,nullptr, m_ptr_head);

        m_ptr_head->m_ptr_prev = ptr_elem;
        m_ptr_head = ptr_elem;
    }
    ++ m_size;
}

template<typename T>
template<class... Args>
void My_List<T>::emplace(My_List::const_iterator position, const Args &... args) {

if (position == this->begin()){
    T  data =  T (args...);
    this->push_front(data);
}
else {
    if (position == this->cend()) {
        T data = T(args...);
        this->push_back(data);
    }
    else{
    if ((position != this->cend()) & (position != this->begin())) {
        T data = T(args...);
        Element *ptr_elem = new Element(data, position.m_ptr_el->m_ptr_prev, position.m_ptr_el);
        position.m_ptr_el->m_ptr_prev = ptr_elem;
        position.m_ptr_el->m_ptr_prev->m_ptr_prev->m_ptr_next = ptr_elem;

        ++m_size;
    }

    }
}
}

template<typename T>
template<class... Args>
void My_List<T>::emplace_back(const Args &... args) {
    if (m_size == 0)
    {
        T  data =  T ( args... );
        Element * ptr_elem = new Element(data ,nullptr,nullptr);
        m_ptr_head = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    else
    {
        T  data =  T ( args... );
        Element * ptr_elem = new Element(data, m_ptr_tail, nullptr);
        m_ptr_tail->m_ptr_next = ptr_elem;
        m_ptr_tail = ptr_elem;
    }
    ++ m_size;
}

template<typename T>
void  My_List<T>::insert (My_List::const_iterator position, const T& data){

    if (position == this->begin()){
        this->push_front(data);
    }
    else {
        if (position == this->cend()) {
            this->push_back(data);
        }
        else{
            if ((position != this->cend()) & (position != this->begin())) {
                Element *ptr_elem = new Element(data, position.m_ptr_el->m_ptr_prev, position.m_ptr_el);
                position.m_ptr_el->m_ptr_prev = ptr_elem;
                position.m_ptr_el->m_ptr_prev->m_ptr_prev->m_ptr_next = ptr_elem;

                ++m_size;
            }

        }
    }
}

template<typename T>
void My_List<T>::clear(){
    for (int i =0; m_size > 0 ; i ++){
        (*this).pop_front();
    }
}

template<typename T>
template<typename T2>
My_List<T>& My_List<T>::operator=(My_List<T2> right){

    typedef typename My_List<T>::const_iterator c_iter_1;
    typedef typename My_List<T2>::const_iterator c_iter_2;

    if (m_size >  right.size()) {
        for (int i = m_size; i < right.size(); --i) {(*this).pop_back();}
    }

    if (m_size <  right.size()) {
        c_iter_2 c_it_2 = right.cbegin();
        c_it_2.advance(m_size);

        for (int i = m_size; i < right.size(); ++i) {
            (*this).push_back(c_it_2());
            c_it_2++;
        }
    }

    c_iter_1 c_it_1 = (this)->cbegin();
    c_iter_2 c_it_2 = right.cbegin();

    for (; c_it_2 != right.cend();  ++c_it_1, ++c_it_2){
        c_it_1() = c_it_2();
    }

    return this;
}








