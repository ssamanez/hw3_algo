#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class HashTable {
private:
    vector<string> table;
    int size;
    int count;
    const double loadFactor = 0.8;
    const double a = (sqrt(5) - 1) / 2; // Constante para la función hash de multiplicación

    int hashFunction(const string &key) {
        unsigned long hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return int(size * fmod(hash * a, 1));
    }

    void rehash() {
        vector<string> oldTable = table;
        size = size * 2;
        table.clear();
        table.resize(size, "");
        count = 0;

        for (const string &item : oldTable) {
            if (item != "" && item != "DELETED") {
                insert(item);
            }
        }
    }

public:
    HashTable(int initialSize = 10) : size(initialSize), count(0) {
        table.resize(size, "");
    }

    void insert(const string &key) {
        if (double(count) / size >= loadFactor) {
            rehash();
        }

        int index = hashFunction(key);
        while (table[index] != "" && table[index] != "DELETED") {
            index = (index + 1) % size;
        }
        table[index] = key;
        count++;
    }

    bool search(const string &key) {
        int index = hashFunction(key);
        int start = index;

        while (table[index] != "") {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % size;
            if (index == start) {
                return false;
            }
        }
        return false;
    }

    void remove(const string &key) {
        int index = hashFunction(key);
        int start = index;

        while (table[index] != "") {
            if (table[index] == key) {
                table[index] = "DELETED"; // Marca como borrado
                count--;
                return;
            }
            index = (index + 1) % size;
            if (index == start) {
                return;
            }
        }
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == "") {
                cout << i << ": " << "empty" << endl;
            } else if (table[i] == "DELETED") {
                cout << i << ": " << "deleted" << endl;
            } else {
                cout << i << ": " << table[i] << endl;
            }
        }
    }
};

int main() {
    HashTable hashTable;

    hashTable.insert("apple");
    hashTable.insert("banana");
    hashTable.insert("orange");
    hashTable.insert("grape");
    hashTable.insert("peach");
    hashTable.insert("melon");
    hashTable.insert("berry");
    hashTable.insert("kiwi");
    hashTable.insert("plum");

    hashTable.display();

    cout << "Search 'banana': " << (hashTable.search("banana") ? "Found" : "Not Found") << endl;
    cout << "Search 'mango': " << (hashTable.search("mango") ? "Found" : "Not Found") << endl;

    hashTable.remove("banana");
    cout << "After removing 'banana':" << endl;
    hashTable.display();

    return 0;
}
