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
/*Класс, определяющий дерево*/
class Tree
{
public:
    struct treeNode
    {
        treeNode(int _val, unsigned int countOfSons) : data(_val), count_sons(countOfSons), father(nullptr){}
        int data;                                               //данные в узле дерева
        unsigned int count_sons;                                //количество ветвей исходящих от вешины
        treeNode** sons = new treeNode * [count_sons];          //Массив сыновей
        treeNode* father;
    };

    treeNode* rootTree = nullptr;
    unsigned int maxWay{ 0 };
    Vector<int> way;

    //Функция isEmpty
    //Возвращает нулевой указатель у корня дерева
    bool isEmpty()
    {
        return rootTree == nullptr;
    }

    //Функция addNode
    //Принимает на вход количество сыновей, узел дерева
    //Функция добавляет новый узел дерева
    void addNode(int count_sons = 0, treeNode* Node = nullptr)
    {
        unsigned int countOfSons = 0;
        int val = 0;

        if (isEmpty())                                     //В дереве нет корня
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "SetRoot:\n";
            val = userInput();
            if (val == 0)                                           //Если значение равно нулю, то корня не существует 
            {
                rootTree = nullptr;
            }
            else
            {
                std::cout << "--------------------------------------------------------" << std::endl;
                std::cout << "Enter root's number of sons:";    // заявляем о многодетности
                countOfSons = userInput();
                rootTree = new treeNode(val, countOfSons);
                addNode(countOfSons, rootTree);
                for (size_t i{}; i < countOfSons; i++) {
                    rootTree->sons[i]->father = rootTree;   //Находим отца Немо
                }
            }
        }
        else if (!isEmpty())
        {
            if (count_sons == 0)
            {
                Node->sons = nullptr;
            }
            else if (count_sons != 0)
            {
                for (int i{}; i < count_sons; i++)
                {
                    std::cout << "--------------------------------------------------------" << std::endl;
                    std::cout << "Set son " << i + 1 << " val\n";
                    val = userInput();
                    if (val == 0) Node->count_sons = 0;                              //Если введен "0", считается, что сыновей у узла нет
                    std::cout << "Enter number of sons for " << i + 1 << " son";
                    if (Node->count_sons != 0) {
                        countOfSons = userInput();
                    }
                    std::cout << "--------------------------------------------------------" << std::endl;
                    Node->sons[i] = new treeNode(val, countOfSons);
                    addNode(countOfSons, Node->sons[i]);
                    Node->sons[i]->father = Node;
                }
            }
        }
    }
  
    //Функция print
    //Принимает на вход узел и его высоту
    //Функция печатает дерево на экран
    void print(treeNode* node, unsigned int height = 0)
    {
        if (isEmpty())
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Tree don't exist" << std::endl;
        }
        else if (!isEmpty())
        {
            for (size_t i{}; i < height; i++) {
                std::cout << "-";
            }
            std::cout << node->data << "| sons : ";
            for (size_t i{}; i < node->count_sons; i++)
            {
                std::cout << node->sons[i]->data << ", ";
            }
            std::cout<<std::endl;

        }
        for (size_t i{}; i < node->count_sons; i++) {
            print(node->sons[i], height + 1);
        }
    }
    /// <summary>
    /// Фукнция поиска длинейшего пути без ветвления, получает на вход корень дерева или указатель на
    /// </summary>
    /// <param name="node"></param>
    void longestWay(treeNode* node = nullptr, unsigned int waySize=0) {
        treeNode* cur = nullptr;
        if (isEmpty())
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "Tree don't exist" << std::endl;
            maxWay = 0;
            std::cout << "MaxWay is: " << maxWay;
        }
        else {
            if (node->count_sons == 1 or node->count_sons == 0) { 
                waySize++;
            if (node->count_sons!=1 and waySize>maxWay) {
                cur = node;
                maxWay = waySize;
                for (size_t i{}; i < way.size(); i++) {
                    way.remove(i);
                }
                for (size_t i{}; i < maxWay; i++) {
                    way.pushBack(cur->data);
                    cur = cur->father;         // вопросики
                }
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

//class Tree
//{
//public:
//    int val;
//    struct Node {
//        Node(int data_, Node* Bro, Node* _son, Node*) : data(data_), father(nullptr) {}
//        int data;
//        Node* father;
//        Node* son;
//        Node* brother;
//    };
//    Node* root = nullptr;
//    Tree() : root(nullptr), val() {};
//    ~Tree();
//
//
//    //Функция isEmpty
//    //Возвращает нулевой указатель у корня дерева, если дерево пусто
//    bool isEmpty()
//    {
//        return root == nullptr;
//    }
//
//    //Функция addNode
//    //Принимает на вход количество сыновей, узел дерева
//    //Функция добавляет новый узел дерева
//    void addNode(Node* Son, Node* Bro, Node* Father, Node* node = nullptr) {
//        if (isEmpty())                                     //В дереве нет корня
//            {
//                std::cout << "--------------------------------------------------------" << std::endl;
//                std::cout << "Set Root:\n";
//                val = userInput();
//                if (val == 0)                                           //Если значение равно нулю, то корня не существует 
//                {
//                    root = nullptr;
//                }
//                else
//                {
//                    std::cout << "--------------------------------------------------------" << std::endl;
//                    root = new Node(val, nullptr,  );
//                    addNode()
//                }
//            }
//        else if (!isEmpty())
//    }
//
//};
//
//Tree::~Tree()
//{
//}
