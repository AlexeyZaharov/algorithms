/*Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
принадлежности данной строки множеству.

Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей
за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество; 
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству. 
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента
из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
*/

#include <iostream>
#include <string>

const size_t TABLE_INITIAL_SIZE= 8;
const size_t a = 11;
enum status {NIL, USING, DELETED} ;

template <typename T>
size_t hash(const T& str, const std::size_t& m) {
    size_t hash = 0;
    for( auto& ch : str ) {
        hash = ( hash * a + ch ) % m;
    }
    return hash;
}

template <typename T>
struct table_node {
    T str;
    int state;

    table_node() : str(""), state(status::NIL) {}
};

template <typename T>
class hash_table {
private:
    size_t _count;
    size_t _capacity;
    table_node<T>* _table;

    void rehash();

public:
    hash_table() : _count(0), _capacity(TABLE_INITIAL_SIZE) {
        _table = new table_node<T>[_capacity];
    }

    bool insert(const T& str);
    bool remove(const T& str);
    bool find(const T& str);

    void out() {
        for (size_t i = 0; i < _capacity; ++i) {
            std::cout << i << "\t\t" << _table[i].str << "\t\t" << _table[i].state << std::endl;
        }
    }

    ~hash_table() {
        delete[] _table;
    }
};


int main() {
    hash_table<std::string> table;
    while( true ) {
        char command = 0;
        std::string value;
        std::cin >> command >> value;

        if( std::cin.fail() )
        {
            break;
        }

        switch( command )
        {
            case '?':
                std::cout << ( table.find( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '+':
                std::cout << ( table.insert( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '-':
                std::cout << ( table.remove( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
        }

    }

    return 0;

}

template <typename T>
void hash_table<T>::rehash() {
    size_t new_capacity = _capacity*2;

    table_node<T>* new_table = new table_node<T>[new_capacity];

    for (size_t i = 0; i < _capacity; ++i) {
        if (_table[i].state == status::USING) {

            size_t h = hash(_table[i].str, new_capacity);
            size_t j = 0;

            while( j < new_capacity ) {
                if (new_table[h].state != status::USING) {
                    break;
                }

                h += j + 1;
                h %= new_capacity;

                ++j;
            }

            new_table[h].str = _table[i].str;
            new_table[h].state = _table[i].state;
        }
    }

    delete[] _table;
    _capacity = new_capacity;
    _table = new_table;
}

template <typename T>
bool hash_table<T>::insert(const T& str) {

    bool success = false;

    size_t h = hash(str, _capacity);
    size_t pos = -1;

    for(size_t i = 0; i < _capacity; ++i) {

        if (_table[h].str == str && _table[h].state == status::USING) {
            break;
        }

        if (_table[h].state == status::DELETED && pos == -1) {
            pos = h;
        }
        else if (_table[h].state == status::NIL) {
            if (pos != h && pos != -1) {
                h = pos;
            }

            _table[h].str = str;
            _table[h].state = status::USING;

            ++_count;
            success = true;
            break;
        }

        h += i + 1;
        h %= _capacity;
    }

    if (double(_count)/double(_capacity) >= 0.75 ) {
        rehash();
    }

    return success;
}

template <typename T>
bool hash_table<T>::remove(const T &str){
    bool success = false;
    size_t h = hash(str, _capacity);

    for(size_t i = 0; i < _capacity; ++i) {
        if (_table[h].str == str && _table[h].state == status::USING) {
            _table[h].state = status::DELETED;
            --_count;
            success = true;
            break;
        }
        else if (_table[h].state != status::NIL) {
            h += i + 1;
            h %= _capacity;
        }
        else {
            break;
        }
    }

    return success;
}

template <typename T>
bool hash_table<T>::find( const T& str ) {
    size_t i = 0;
    size_t h = hash(str, _capacity);
    while( _table[h].state != status::NIL && i < _capacity ) {
        if( _table[h].str == str && _table[h].state == status::USING){
            return true;
        }
        h += i + 1;
        h %= _capacity;
        ++i;
    }
    return false;
}
