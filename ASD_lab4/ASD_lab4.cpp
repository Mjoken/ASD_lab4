/*Задание: Задача 10. Дано N-дерево. Найти в дереве самые длинные пути без ветвлений.*/
#include "MyVector.h"
/*
Функция userInput
Проверки ввода типа int
Ввод: -
Вывод: переменная типа int
*/
int userInput()
{
    int input = 0;
    std::cin >> input;
    while (!(std::cin.good()))
    {
        std::cout << "Input error! Enter again" << std::endl;
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cin >> input;
    }
    return input;
}
/*Класс описывающий дерево*/
class Tree
{
public:
    /* Структура описывающий верщину дерева */
    struct treeNode
    {
        treeNode(int _val, unsigned int countOfSons) : data(_val), count_sons(countOfSons), father(nullptr){}
        int data;                                               // Данные в узле дерева
        unsigned int count_sons;                                // Количество ветвей исходящих от вешины (количество сыновей верщины)
        treeNode** sons = new treeNode * [count_sons];          // Массив сыновей текущей верщины
        treeNode* father;                                       // Отец текушего верщины
    };

    treeNode* rootTree = nullptr;                               // Корень дерева
    unsigned int maxWay{ 0 };                                   // Длина самого длинного пути в дереве
    Vector<int> way;                                            // Значения самого длинного пути

    /*Функция isEmpty
    Проверяет, существует ли дерево(конкретнее его корень)
    Ввод: -
    Вывод: равен ли корень нулевому указателю
    */
    bool isEmpty()
    {
        return rootTree == nullptr;
    }

    /*Функция addNode
    Создаёт узел дерева, рекурсивно, в глубину, консольный ввод
    Ввод: количество сыновей, узел дерева, высота текушего
    Вывод: -
    */
    void addNode(int count_sons = 0, treeNode* Node = nullptr, unsigned int height = 1)
    {
        unsigned int countOfSons = 0;                           // Число сыновей текущего узла
        int val = 0;                                            // Целочисленное значение
        if (isEmpty())                                          // В дереве нет корня
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "SetRoot: ";
            val = userInput();
            if (val == 0)                                       // Если значение корня нулевое, то дерево не существует
            {
                rootTree = nullptr;
            }
            else                                                // значение корня отлично от нуля
            {
                std::cout << "Enter root's number of sons: ";   
                countOfSons = userInput();
                rootTree = new treeNode(val, countOfSons);
                addNode(countOfSons, rootTree, height+1);       // Рекурсивный вызов функции построения дерева
                for (size_t i{}; i < countOfSons; i++) {
                    rootTree->sons[i]->father = rootTree;       // Указываем корень как отца его сыновей
                }
            }
        }
        else if (!isEmpty())                                    // В дереве есть корень корня
        {
            if (count_sons == 0)                                // Если у узла нет сыновей, то узел - лист дерева
            {
                Node->sons = nullptr;
            }
            else if (count_sons != 0)
            {
                for (int i{}; i < count_sons; i++)
                {
                    std::cout << "--------------------------------------------------------" << std::endl;
                    for (size_t i{}; i < height; i++) {         // Вывод количества чёрточек по глубине/высоте дерева
                        std::cout << "-";
                    }
                    
                    if (Node->father != nullptr) {              // Ввод значения сыновей
                        std::cout << "| enter " << Node->data << " son " << i + 1 << " val : "; 
                    }
                    else {                                      // Ввод значения сыновей корня
                        std::cout << "| enter root son " << i + 1 << " val : ";
                    }
                    val = userInput();
                    if (val == 0) Node->count_sons = 0;         // Если значение ноль, то считаем, что 
                    std::cout << "number of sons:";
                    if (Node->count_sons != 0) {
                        countOfSons = userInput();
                    }
                    Node->sons[i] = new treeNode(val, countOfSons);
                    Node->sons[i]->father = Node;
                    addNode(countOfSons, Node->sons[i], height+1);
                }
            }
        }
    }
  
    /*Функция print
    Печатает в консоль дерево
    Ввод: Узел и высота узла
    Вывод: -
    */
    void print(treeNode* node, unsigned int height = 0)
    {
        if (isEmpty())
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Tree don't exist" << std::endl;
        }
        else if (!isEmpty())                                  // Если значение корня нулевое, то дерево не существует
        {
            for (size_t i{}; i < height; i++) {               // Вывод количества чёрточек по глубине/высоте дерева
                std::cout << "-";
            }
            std::cout << node->data << "| sons : ";
            for (size_t i{}; i < node->count_sons; i++)
            {
                std::cout << node->sons[i]->data << ", ";     // Сыновья текущего узла
            }
            std::cout<<std::endl;

        }
        for (size_t i{}; i < node->count_sons; i++) {         // Рекурсивная печать сыновей
            print(node->sons[i], height + 1);
        }
    }
    /*
    Фукнция поиска длинейшего пути без ветвления, 
    Ввод: корень дерева или указатель на верщину, текущую длинну пути без ветвления
    Вывод: -
    */
    void longestWay(treeNode* node = nullptr, unsigned int waySize=0) {
        treeNode* cur = nullptr;                              // Указатель на верщину для перемещения по дереву
        if (isEmpty())                                        // Если значение корня нулевое, то дерево не существует
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Tree don't exist" << std::endl;
            maxWay = 0;
            std::cout << "MaxWay is: " << maxWay;
        }
        else {
            if (node->count_sons == 1 or node->count_sons == 0) {
                waySize++;                                    /* Проверяем, нет ли ветвления (т.е. у дерева либо 1 сын, либо оно лист),
                                                              добовляем 1 к длинне пути*/
            }
            if (node->count_sons!=1 and waySize>maxWay) {     // Если встретели развилку или лист, путь заканчиваеться
                cur = node;
                maxWay = waySize;                             // Если длинна пути, по которому прошли больше самого длинного, то меняем самый длинный
                waySize = 0;
                std::cout << "Tree longest way: " << way << std::endl;
                for (size_t i{}; i < way.size(); i++) {
                    way.remove(i);                            // Очищаем массив длинны пути
                }
                for (size_t i{}; i < maxWay; i++) {           // От конца пути к началу запоминаем 
                    way.pushBack(cur->data);
                    cur = cur->father;         
                }
            }
        }
        for (size_t i{}; i < node->count_sons; i++) {
            longestWay(node->sons[i], waySize);
        }
        return;
    }
};
/*end-of-class*/
int main()
{
    Tree firstTree;
    firstTree.addNode();
    firstTree.print(firstTree.rootTree);
    std::cout << "\n---------------------------------------------------" << std::endl;
    firstTree.longestWay(firstTree.rootTree);
    std::cout << "Tree longest way height: " << firstTree.maxWay << std::endl;
    std::cout << "Tree longest way: "<<firstTree.way<<std::endl;
    for (size_t i{}; i < firstTree.way.size(); i++) {
        std::cout << "Node " << i << " : " << firstTree.way[i] << std::endl;
    }
    return 0;
}