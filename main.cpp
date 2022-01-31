#include <iostream>
#include <list>
#include "My_list.cpp"


using namespace std;

template<typename T>
void print_container(T& lst) {
    cout << "{ ";
    for (auto el : lst)
        cout << el << ' ';
    cout << "}" << endl;
}

int main() {
//    My_List<char> my_list = { 1, 1, 1, 1 };
//    My_List<int> my_list = { 1.2 , 0.555 };

    My_List<int> my_list = { 1 , 2, 3, 4};
    cout << "size: " << my_list.size() << endl;
    print_container(my_list);


    my_list.pop_front();
    my_list.push_front(0);
    my_list.push_back(5);
    cout << "size: " << my_list.size() << endl;
    print_container(my_list);


    my_list.clear();
    cout << "size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.~My_List();
    cout << "size: " << my_list.size() << endl;
    print_container(my_list);
    /*
    my_list.emplace_back(222);
    my_list.emplace_front(111);
    cout << "size: " << my_list.size() << endl;
    print_container(my_list);

    for (list<int>::const_iterator it = my_list.begin(); it != my_list.end(); ++it)
        cout << *it << endl;

    //------------------------------------------------------------
    // Далее тесты для повышенного уровня сложности (оценки 9-10):
    list<int>::const_iterator it = my_list.end();
    --it; // Умеет с после последнего перемещаться на последний
    cout << *it << endl;
    ++it; // Умеет приходить из последнего на после последнего
    cout << *it << endl; // выведет пустышку в режиме Release или ошибка в режиме Debug
    ++it; // после последнего перейдёт к head (т.е. список зациклен)
    cout << *it << endl;

    //system("pause");
     */

    return 0;
}

