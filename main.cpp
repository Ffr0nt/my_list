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

template<typename T>
void print_lst_test(T& lst) {
    cout << "{ ";
    int i = 0;
    for (auto el : lst) {
        if (i != 0)  cout << " , ";
        el.print();
        i ++;
    }
    cout << "}" << endl;
}

class Test_Class{
public:
    Test_Class(int a, double b): m_a(a), m_b(b){};

    void print (){
        cout << m_a << '_' << m_b;
    }
private:
        int m_a;
        double m_b;
    };

int NUM = 3;

void test_1(){
    My_List<int> my_list_0 = { 1 , 2, 3, 4};
    My_List<char> my_list_1 = { 1, 1, 1, 1 };
    My_List<int> my_list_2 = { 1.2 , 5.555 };
    My_List<int> my_list_3(5);
    My_List<int> my_list_4(5,9);

    cout << "my_list_0 size: " << my_list_0.size() << endl;
    print_container(my_list_0);

    cout << "my_list_1 size: " << my_list_1.size() << endl;
    print_container(my_list_1);

    cout << "my_list_2 size: " << my_list_2.size() << endl;
    print_container(my_list_2);

    cout << "my_list_3 size: " << my_list_3.size() << endl;
    print_container(my_list_3);

    cout << "my_list_4 size: " << my_list_4.size() << endl;
    print_container(my_list_4);
}

void test_2(){
    My_List<int> my_list_0 = { 1 , 2, 3, 4};
    My_List<int> my_list_1 = { 9 , 8, 7, 6, 5, 4, 3 , 2};
    My_List<int> my_list_2 = {};

    My_List<int> my_list_3(my_list_0);
    cout << "My_List<int> my_list_3(my_list_0); size: " << my_list_3.size() << endl;
    print_container(my_list_3);

    my_list_2 = my_list_0;
    cout << "small = big; size: " << my_list_2.size() << endl;
    print_container(my_list_2);

    my_list_1 = my_list_2;
    cout << "big = small; size: " << my_list_1.size() << endl;
    print_container(my_list_1);

    my_list_0.clear();
    cout << "my_list_0.clear(); size: " << my_list_0.size() << endl;
    print_container(my_list_0);
}

void test_3(){
    My_List<int> my_list = { 1 , 2, 3, 4};

    cout << "size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.pop_back();
    cout << "pop_back(); size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.pop_front();
    cout << "pop_front(); size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.push_front(0);
    cout << "push_front(0); size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.push_back(5);
    cout << "push_back(5); size: " << my_list.size() << endl;
    print_container(my_list);

    my_list.erase(++my_list.cbegin());
    cout << "erase(++my_list.cbegin()) " << my_list.size() << endl;
    print_container(my_list);
}

void test_4(){
    My_List<Test_Class> my_list = { Test_Class (2, 2.2)};

    my_list.emplace_front(1, 1.1);
    cout << "emplace_front(2, 2.2); size: " << my_list.size() << endl;
    print_lst_test(my_list);

    my_list.emplace_back(3, 3.3);
    cout << "emplace_back(3, 3.3); " << my_list.size() << endl;
    print_lst_test(my_list);

    my_list.emplace( my_list.cbegin(),4,4.4 );
    cout << "emplace( my_list.cbegin(),4,4.4 ); " << my_list.size() << endl;
    print_lst_test(my_list);

    my_list.emplace( my_list.cend(),5,5.5 );
    cout << "emplace( my_list.cend(),5,5.5 ); " << my_list.size() << endl;
    print_lst_test(my_list);

    my_list.emplace(++ my_list.cbegin(),6,6.6 );
    cout << "emplace(++ my_list.cbegin(),6,6.6 ); " << my_list.size() << endl;
    print_lst_test(my_list);

    my_list.insert( my_list.cend(), Test_Class(7,7.7 ) );
    cout << endl<< "insert( my_list.cend(),66 ); " << my_list.size() << endl;
    print_lst_test(my_list);

}

void test_5(){
    My_List<int> my_list = { 1 , 2, 3, 4, 5 };
    for (My_List<int>::const_iterator it = my_list.begin(); it != my_list.end(); ++it) cout << *it << ' ';

    auto it = my_list.cbegin().advance(4);
    cout << endl << *it;

    auto it_2 =  (my_list.cbegin().advance(4)).advance(- 3);
    cout << endl << *it_2;


}

int main() {

//    for (list<int>::const_iterator it = my_list.begin(); it != my_list.end(); ++it)
//        cout << *it << endl;
    switch (NUM) {
        case 1:
            test_1();
            break;
        case 2:
            test_2();
            break;
        case 3:
            test_3();
            break;
        case 4:
            test_4();
            break;
        case 5:
            test_5();
            break;
        default:
            throw runtime_error("What the .....???");
    }
    //    system("pause");

    //------------------------------------------------------------
    // Далее тесты для повышенного уровня сложности (оценки 9-10):
//    list<int>::const_iterator it = my_list.end();
//    --it; // Умеет с после последнего перемещаться на последний
//    cout << *it << endl;
//    ++it; // Умеет приходить из последнего на после последнего
//    cout << *it << endl; // выведет пустышку в режиме Release или ошибка в режиме Debug
//    ++it; // после последнего перейдёт к head (т.е. список зациклен)
//    cout << *it << endl;

    return 0;
}

