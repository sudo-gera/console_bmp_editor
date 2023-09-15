### Function

В этой задаче вам предстоит реализовать аналог класса [std::function](https://en.cppreference.com/w/cpp/utility/functional/function). Данный класс представляет из себя контейнер для хранения `CopyConstructible Callable ` объектов )

*Пример:*
```c++
void Print(int i) {
    std::cout << i << std::endl;
}

struct Printer {
    void operator(int i) {
        std::cout << i << std::endl;
    }
};

std::function<void(int)> f; // Пустой контейнер.
f = Print; // Присвоили указатель на функцию  Print.
f = [](int i) {
    std::cout << i << std::endl;
}; // Присвоили лямбда-функцию.
f = Printer{}; // Присвоили функтор.
f(); // Вызов хранимого объекта.
```



#### Детали реализации 
- Конструктор по умолчанию
- Конструктор с шаблонным параметром
- Оператор присваивания с шаблонным параметром 
- Правило `пяти`
- Оператор вызова `()`
- При попытке вызвать пустой контейнер должна бросаться ошибка  `std::bad_function_call`




### Примечания
Вам потребуется механизм [type erasure](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Type_Erasure)