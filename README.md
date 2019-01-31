# Лабораторная работа №1 

- создать класс матрица (должен быть конструктор и деструктор)
- выполнить перегрузку операторов +/-/*/+=/-=/*= для матрицы (поэлементно) и скалярного значения
- выполнить перегрузку оператора () для индексации элементов матрицы
- добавить метод транспонирования матрицы
- добавить метод dot для произведения матриц
- выполнить перегрузку operator«(»). Для » данные для матрицы читаем из файла

# Лабораторная работа №2

>Выполнить с помощью libxml++ 

- 1. Курс валют. app.exe —data=daily,xml —from=USD —to=EUR 
- 2. Погода. Средняя тепература в e-окретсности точки apd —data=weather.xml —lat=.. —lon=.. —r=n-degree 
- 3. Среднее количество камер в раойне 
- 4. Количество парковочных машиномест около метро в зависимости от райна 


# Лабораторная работа No3
Реализовать бинарное дерево поиска (https://en.wikipedia.org/wiki/Binary_search_tree) в
виде контейнера, обеспеченного двунаправленным итератором. Реализация не
должна использовать ни одни из контейнеров STL.

Ниже базовый шаблон, содержащий сигнатуры методов, которые должны быть
реализованы:
```cpp
template​<class ​T, class ​Compare = std::less<T>>
class ​BST {
public​:
BST();
BST(const ​BST &);
BST& operator​=(const ​BST &);
template​<class ​InputIt>
void ​assign(InputIt first, InputIt last);
iterator begin();
const_iterator cbegin();
iterator end();
const_iterator cend();
iterator insert(const ​T &value);
iterator remove(const ​T &value);
iterator find(const ​T &value);
const_iterator find(const ​T &value) const​;
bool ​empty() const​;
size_t size() const​;
};
```
Реализация сбалансированного дерева будет плюсом.
