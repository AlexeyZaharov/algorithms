#include <iostream>
#include <string>

const size_t TABLE_INITIAL_SIZE= 8;
const size_t a = 11;
enum status {NIL, USING, DELETED} ;

size_t hash(const std::string& str, const std::size_t& m) {
    size_t hash = 0;
    for( auto& ch : str ) {
        hash = ( hash * a + ch ) % m;
    }
    return hash;
}

struct table_node {
    std::string str;
    int state;

    table_node() : str(""), state(status::NIL) {}
};

class hash_table {
private:
    size_t _count;
    size_t _capacity;
    table_node* _table;

    void rehash();

public:
    hash_table() : _count(0), _capacity(TABLE_INITIAL_SIZE) {
        _table = new table_node[_capacity];
    }

    bool insert(const std::string& str);
    bool remove(const std::string& str);
    bool find(const std::string& str);

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
    hash_table table;
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

        table.out();

    }

    return 0;

}

void hash_table::rehash() {
    size_t new_capacity = _capacity*2;

    table_node* new_table = new table_node[new_capacity];

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

bool hash_table::insert(const std::string& str) {

    bool success = false;
    size_t h = hash(str, _capacity);

    for(size_t i = 0; i < _capacity; ++i) {

        if (_table[h].str == str && _table[h].state == status::USING) {
            break;
        }

        if (_table[h].state == status::USING) {
                h += i + 1;
                h %= _capacity;
            }
        else {
            _table[h].str = str;
            _table[h].state = status::USING;

            ++_count;
            success = true;
            break;
        }
    }

    if (double(_count)/double(_capacity) >= 0.75 ) {
        rehash();
    }

    return success;
}

bool hash_table::remove(const std::string &str){
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

bool hash_table::find( const std::string &str ) {
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
