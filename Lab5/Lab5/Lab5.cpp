#include <iostream> // Подключение библиотеки для ввода-вывода
using namespace std; // Использование пространства имён std для упрощения синтаксиса

// Структура, представляющая узел бинарного дерева
struct TreeNode {
    int key;              // Ключ узла
    int frequency;        // Частота появления данного ключа (для подсчёта дубликатов)
    TreeNode* left;       // Указатель на левое поддерево
    TreeNode* right;      // Указатель на правое поддерево
};

// Класс для работы с бинарным деревом
class BinaryTree {
private:
    TreeNode* root; // Указатель на корень дерева

    // Вспомогательная функция для вставки элемента в дерево
    void insertKey(int value, TreeNode** current);

    // Вспомогательная функция для отображения дерева
    void displayTree(TreeNode* current, int depth);

    // Вспомогательная функция для очистки памяти дерева
    void clearTree(TreeNode* current);

public:
    // Конструктор, инициализирующий дерево пустым
    BinaryTree() : root(nullptr) {}

    // Метод для добавления нового элемента в дерево
    void addElement(int value);

    // Метод для поиска элемента в дереве
    bool searchElement(int value);

    // Метод для отображения дерева на консоли
    void printTree();

    // Метод для прямого обхода дерева (PreOrder)
    void preOrderTraversal(TreeNode* current);

    // Метод для симметричного обхода дерева (InOrder)
    void inOrderTraversal(TreeNode* current);

    // Метод для обратного обхода дерева (PostOrder)
    void postOrderTraversal(TreeNode* current);

    // Метод для вычисления высоты дерева
    int calculateHeight(TreeNode* current);

    // Метод для получения указателя на корень дерева
    TreeNode* getRoot() { return root; }

    // Метод для очистки дерева (освобождение памяти)
    void clear() { clearTree(root); root = nullptr; }
};

// Основная функция программы
int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для работы с русским языком

    BinaryTree tree; // Создание объекта бинарного дерева
    int action, value; // Переменные для хранения действия пользователя и значения узла

    // Бесконечный цикл для реализации меню
    while (true) {
        // Вывод меню действий
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Найти элемент\n";
        cout << "3. Вывести дерево\n";
        cout << "4. Прямой обход\n";
        cout << "5. Симметричный обход\n";
        cout << "6. Обратный обход\n";
        cout << "7. Высота дерева\n";
        cout << "8. Очистить дерево\n";
        cout << "9. Выйти\n";
        cout << "Ваш выбор: ";
        cin >> action; // Ввод действия пользователя

        // Обработка действия пользователя
        switch (action) {
        case 1: // Добавление элемента
            cout << "Введите значение: ";
            cin >> value;
            tree.addElement(value);
            break;
        case 2: // Поиск элемента
            cout << "Введите значение для поиска: ";
            cin >> value;
            if (tree.searchElement(value))
                cout << "Элемент найден.\n";
            else
                cout << "Элемент не найден.\n";
            break;
        case 3: // Вывод дерева
            cout << "Дерево:\n";
            tree.printTree();
            break;
        case 4: // Прямой обход дерева
            cout << "Прямой обход: ";
            tree.preOrderTraversal(tree.getRoot());
            cout << endl;
            break;
        case 5: // Симметричный обход дерева
            cout << "Симметричный обход: ";
            tree.inOrderTraversal(tree.getRoot());
            cout << endl;
            break;
        case 6: // Обратный обход дерева
            cout << "Обратный обход: ";
            tree.postOrderTraversal(tree.getRoot());
            cout << endl;
            break;
        case 7: // Вычисление высоты дерева
            cout << "Высота дерева: " << tree.calculateHeight(tree.getRoot()) << endl;
            break;
        case 8: // Очистка дерева
            tree.clear();
            cout << "Дерево очищено.\n";
            break;
        case 9: // Завершение программы
            tree.clear(); // Очистка памяти перед выходом
            cout << "Программа завершена.\n";
            return 0;
        default: // Обработка неверного выбора
            cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
}

// Реализация методов класса BinaryTree

// Вставка элемента в дерево
void BinaryTree::insertKey(int value, TreeNode** current) {
    if (*current == nullptr) { // Если текущий узел пуст, создаём новый
        *current = new TreeNode{ value, 1, nullptr, nullptr };
    }
    else if (value < (*current)->key) { // Если значение меньше, идём в левое поддерево
        insertKey(value, &((*current)->left));
    }
    else if (value > (*current)->key) { // Если больше, идём в правое поддерево
        insertKey(value, &((*current)->right));
    }
    else { // Если равны, увеличиваем счётчик частоты
        (*current)->frequency++;
    }
}

// Добавление элемента в дерево (публичный метод)
void BinaryTree::addElement(int value) {
    insertKey(value, &root); // Вызываем рекурсивную функцию для вставки
}

// Поиск элемента в дереве
bool BinaryTree::searchElement(int value) {
    TreeNode* current = root; // Начинаем поиск с корня
    while (current != nullptr) {
        if (value == current->key) { // Если нашли значение, возвращаем true
            return true;
        }
        else if (value < current->key) { // Если меньше, идём в левое поддерево
            current = current->left;
        }
        else { // Если больше, идём в правое поддерево
            current = current->right;
        }
    }
    return false; // Если узел не найден
}

// Рекурсивный вывод дерева
void BinaryTree::displayTree(TreeNode* current, int depth) {
    if (current != nullptr) { // Если узел не пуст
        displayTree(current->right, depth + 1); // Выводим правое поддерево
        for (int i = 0; i < depth; ++i) cout << "   "; // Отступы для отображения уровня
        cout << current->key << " (" << current->frequency << ")" << endl; // Печатаем ключ текущего узла и его частоту
        displayTree(current->left, depth + 1); // Выводим левое поддерево
    }
}

// Вывод дерева (публичный метод)
void BinaryTree::printTree() {
    displayTree(root, 0); // Вызываем рекурсивную функцию
}

// Прямой обход дерева
void BinaryTree::preOrderTraversal(TreeNode* current) {
    if (current != nullptr) {
        cout << current->key << " "; // Печатаем ключ
        preOrderTraversal(current->left); // Рекурсивный обход левого поддерева
        preOrderTraversal(current->right); // Рекурсивный обход правого поддерева
    }
}

// Симметричный обход дерева
void BinaryTree::inOrderTraversal(TreeNode* current) {
    if (current != nullptr) {
        inOrderTraversal(current->left); // Рекурсивный обход левого поддерева
        cout << current->key << " "; // Печатаем ключ
        inOrderTraversal(current->right); // Рекурсивный обход правого поддерева
    }
}

// Обратный обход дерева
void BinaryTree::postOrderTraversal(TreeNode* current) {
    if (current != nullptr) {
        // Обход левого поддерева
        postOrderTraversal(current->left);

        // Обход правого поддерева
        postOrderTraversal(current->right);

        // Обработка текущего узла
        cout << current->key << " ";
    }
}

// Вычисление высоты дерева
int BinaryTree::calculateHeight(TreeNode* current) {
    if (current == nullptr) return 0; // Если узел пуст, высота 0
    int leftHeight = calculateHeight(current->left); // Высота левого поддерева
    int rightHeight = calculateHeight(current->right); // Высота правого поддерева
    return 1 + max(leftHeight, rightHeight); // Высота текущего узла
}

// Очистка памяти дерева (рекурсивно)
void BinaryTree::clearTree(TreeNode* current) {
    if (current != nullptr) {
        clearTree(current->left); // Очистка левого поддерева
        clearTree(current->right); // Очистка правого поддерева
        delete current; // Удаление текущего узла
    }
}
