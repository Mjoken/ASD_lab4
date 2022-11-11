/*Задание: Задача 10. Дано N-дерево. Найти в дереве самые длинные пути без ветвлений.*/
/*максРазмер : целое
началоМаксВетви: узел
gleb pidor
проц максВетвь(узел : Узел, началоВетви: Узел, текРазмер: целое)
  в зависимости от степени узла «узел»
    если 0:
      если текРазмер > максРазмер
        максРазмер = текРазмер
        началоМаксВетви = началоВетви
    если 1: максВетвь(единственныйCын, началоВетви, текРазмер + 1)
    если 2+:
      для всех сыновей
        максВетвь(сын, сын, 1)

максВетвь(корень, корень, 1)*/
#include "MyVector.h"

int userInput()
{
    int input = 0;
    std::cout << "Input value(int) or 0 for leaf: ";
    std::cin >> input;
    while (!(std::cin.good()))
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cin >> input;
    }
    return input;
}
//class Tree
//{
//public:
//    struct treeNode
//    {
//        treeNode(int _val, int countOfSons) : data(_val), count_sons(countOfSons), father(nullptr){}
//        int data;                                               //данные в узле дерева
//        int count_sons;                                         //количество ветвей исходящих от вешины
//        treeNode** sons = new treeNode * [count_sons];          //Выделение памяти под сыновей
//        treeNode* father;
//    };
//
//    treeNode* rootTree = nullptr;
//    unsigned int maxWay{ 0 };
//    Vector<int> way;
//
//    //Функция isEmpty
//    //Возвращает нулевой указатель у корня дерева
//    bool isEmpty()
//    {
//        return rootTree == nullptr;
//    }
//
//    //Функция addNode
//    //Принимает на вход количество сыновей, узел дерева
//    //Функция добавляет новый узел дерева
//    void addNode(int count_sons = 0, treeNode* Node = nullptr)
//    {
//        int countOfSons = 0;
//        int val = 0;
//
//        if (isEmpty() or !Node)                                     //В дереве нет корня
//        {
//            std::cout << "--------------------------------------------------------" << std::endl;
//            std::cout << "SetRoot:\n";
//            val = userInput();
//            if (val == 0)                                           //Если значение равно нулю, то корня не существует 
//            {
//                rootTree = nullptr;
//            }
//            else
//            {
//                std::cout << "--------------------------------------------------------" << std::endl;
//                std::cout << "Enter root's number of sons:";    // заявляем о многодетности
//                countOfSons = userInput();
//                rootTree = new treeNode(val, countOfSons);
//                addNode(countOfSons, rootTree);
//                for (size_t i{}; i < countOfSons; i++) {
//                    rootTree->sons[i]->father = rootTree;   //Находим отца Немо
//                }
//            }
//        }
//        else if (Node)
//        {
//            if (count_sons == 0)
//            {
//                Node->sons = nullptr;
//            }
//            else if (count_sons != 0)
//            {
//                for (int i{}; i < count_sons; i++)
//                {
//                    std::cout << "--------------------------------------------------------" << std::endl;
//                    std::cout << "Set son " << i + 1 << " val\n";
//                    val = userInput();
//                    if (val == 0) Node->count_sons = 0;                              //Если введен "0", считается, что сыновей у узла нет
//                    std::cout << "Enter number of sons for " << i + 1 << " son";
//                    if (Node->count_sons != 0) {
//                        countOfSons = userInput();
//                    }
//                    std::cout << "--------------------------------------------------------" << std::endl;
//                    Node->sons[i] = new treeNode(val, countOfSons);
//                    addNode(countOfSons, Node->sons[i]);
//                    Node->sons[i]->father = Node;
//                }
//            }
//        }
//    }
//  
//    //Функция print
//    //Принимает на вход узел и его высоту
//    //Функция печатает дерево на экран
//    void print(treeNode* node, int height = 0)
//    {
//        if (isEmpty())
//        {
//            std::cout << "--------------------------------------------------------" << std::endl;
//            std::cout << "Tree don't exist" << std::endl;
//        }
//        else if (node->sons != nullptr or node->count_sons != 0)
//        {
//            std::cout << "--------------------------------------------------------" << std::endl;
//            std::cout << height + 1 << " - level node: " << node->data << std::endl;
//
//            for (int i{}; i < node->count_sons; i++)
//            {
//                std::cout << "Son " << i + 1 << ": " << node->sons[i]->data << std::endl;
//                height++;
//                print(node->sons[i], height);
//            }
//        }
//        else if (node->sons == nullptr)
//        {
//            std::cout << "--------------------------------------------------------" << std::endl;
//            std::cout << "NULL" << std::endl;
//        }
//    }
//    void longestWay(unsigned int counter = 0, treeNode* node = nullptr) {
//        treeNode* cur = nullptr;
//        int waySize = 0;
//        if (isEmpty())
//        {
//            std::cout << "--------------------------------------------------------" << std::endl;
//            std::cout << "Tree don't exist" << std::endl;
//            maxWay = 0;
//            std::cout << "MaxWay is: " << maxWay;
//        }
//        else {
//            if (node->count_sons == 1 or node->count_sons == 0) { 
//                waySize++;
//            if (node->sons == nullptr and waySize>maxWay) {
//                cur = node;
//                maxWay = waySize;
//                for (size_t i{}; i < way.size(); i++) {
//                    way.remove(i);
//                }
//                for (size_t i{}; i < maxWay; i++) {
//                    way.pushBack(cur->data);
//                    cur = node->father;
//                }
//            }
//            }
//        }
//        return;
//    }
//};
//int main()
//{
//    Tree firstTree;
//    firstTree.addNode();
//    firstTree.print(firstTree.rootTree);
//    std::cout << "\n---------------------------------------------------" << std::endl;
//    firstTree.longestWay(0 ,firstTree.rootTree);
//    std::cout << "Tree longest way height: " << firstTree.maxWay << std::endl;
//    std::cout << "Tree longest way: "<<firstTree.way<<std::endl;
//    /*for (size_t i{}; i < firstTree.way.size(); i++) {
//        std::cout << "Node " << i << " : " << firstTree.way[i] << std::endl;
//    }*/
//    return 0;
//}#include "pch.h"

class Tree
{
public:
    unsigned int sons_num;
    int val;
    struct Node {
        Node(int data_, unsigned int sNum_) : data(data_), sNum(sNum_), father(nullptr) {}
        int data;
        Node* father;
        unsigned int sNum;
        Node** sons = new Node * [sNum];
    };
    Node* root = nullptr;
    Tree() : root(nullptr), sons_num(), val() {};
    ~Tree();


    //Функция isEmpty
    //Возвращает нулевой указатель у корня дерева, если дерево пусто
    bool isEmpty()
    {
        return root == nullptr;
    }

    //Функция addNode
    //Принимает на вход количество сыновей, узел дерева
    //Функция добавляет новый узел дерева
    void addNode(int snum = 0, Node* node = nullptr) {
        if (isEmpty() or node == nullptr)                                     //В дереве нет корня
            {
                std::cout << "--------------------------------------------------------" << std::endl;
                std::cout << "SetRoot:\n";
                val = userInput();
                if (val == 0)                                           //Если значение равно нулю, то корня не существует 
                {
                    root = nullptr;
                }
                else
                {
                    std::cout << "--------------------------------------------------------" << std::endl;
                    std::cout << "Enter root's number of sons:";    // заявляем о многодетности
                    sons_num = userInput();
                    root = new Node(val, sons_num);
                    addNode(sons_num, root);
                    for (size_t i{}; i < sons_num; i++) {
                        root->sons[i]->father = root;   //Находим отца Немо
                    }
                }
            }
        else if (!isEmpty() or node!=)
    }

};

Tree::~Tree()
{
}



int main() {

    return 0;
}