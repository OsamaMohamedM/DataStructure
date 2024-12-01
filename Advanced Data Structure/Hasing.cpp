#include<bits/stdc++.h>

using namespace std;

int divisionHash(int key, int tableSize) {
    return key % tableSize;
}

int multiplicationHash(int key, int tableSize) {
    double A = 0.618033;
    double fractionalPart = key * A - int(key * A);
    return int(tableSize * fractionalPart);
}

int foldingShiftingHash(int key, int tableSize) {
    int addressSpace = log10(tableSize);
    string keyStr = to_string(key);
    long long sum = 0;

    if (addressSpace > keyStr.size()) {
        sum = key;
    } else {
        for (int i = 0; i < keyStr.size(); i += addressSpace) {
            int part = stoi(keyStr.substr(i, addressSpace));
            sum += part;
        }
    }

    return sum % addressSpace;
}

int foldingBoundaryHash(int key, int tableSize) {
    int addressSpace = log10(tableSize);
    string keyStr = to_string(key);
    long long sum = 0;

    if (addressSpace > keyStr.size()) {
        sum = key;
    } else {
        int i;
        for (i = 0; i + addressSpace < keyStr.size(); i += addressSpace) {
            int part = stoi(keyStr.substr(i, addressSpace));
            if (i == 0) {
                string tmp = keyStr.substr(i, addressSpace);
                reverse(tmp.begin(), tmp.end());
                part = stoi(tmp);
            }
            sum += part;
        }

        if (i < keyStr.size()) {
            string tmp = keyStr.substr(i);
            reverse(tmp.begin(), tmp.end());
            sum += stoi(tmp);
        }
    }

    return sum % tableSize;
}

enum State {
    Deleted = 0,
    EMPTY = 1,
    TAKEN = 2
};

class hashNode {
public:
    int value;
    State state;

    hashNode() {
        state = State::EMPTY;
    }

    hashNode(int Value) : value(Value) {
        state = State::TAKEN;
    }

    bool operator==(const hashNode &other) const {
        return value == other.value && state == other.state;
    }
};

class HashTable {
protected:
    int tableSize;
    function<int(int, int)> hashFunction;
    int elementCount = 0;

public:
    HashTable(int size, function<int(int, int)> hashFunc)
            : tableSize(size), hashFunction(hashFunc) {}

    virtual void insert(int key) = 0;

    virtual bool search(int key) = 0;

    virtual void rehash() = 0;

    virtual void remove(int key) = 0;

    virtual ~HashTable() = default;

    virtual void display() const = 0;
};

class ChainingHashTable : public HashTable {
private:
    vector<vector<hashNode>> table;

public:
    ChainingHashTable(int size, function<int(int, int)> hashFunc)
            : HashTable(size, hashFunc), table(size) {}

    double loadFactor() const {
        return double(elementCount) / tableSize;
    }

    void insert(int key) override {
        int index = hashFunction(key, tableSize);
        table[index].emplace_back(key);
        elementCount++;

        if (loadFactor() > 0.75) {
            rehash();
        }
    }

    bool search(int key) override {
        int index = hashFunction(key, tableSize);
        for (auto &value: table[index]) {
            if (value.state == TAKEN && value.value == key) return true;
        }
        return false;
    }

    void remove(int key) override {
        int index = hashFunction(key, tableSize);
        auto node = hashNode(key);
        node.state = TAKEN;
        auto it = find(table[index].begin(), table[index].end(), node);
        if (it == table[index].end())
            cout << "Key not found!" << '\n';
        else {
            table[index].erase(it);
            elementCount--;
        }
    }

    void rehash() override {
        int newSize = tableSize * 2;
        vector<vector<hashNode>> newTable(newSize);

        for (const auto &chain: table) {
            for (auto &key: chain) {
                int newIndex = hashFunction(key.value, newSize);
                newTable[newIndex].push_back(key);
            }
        }

        tableSize = newSize;
        table = newTable;
    }

    void display() const override {
        for (int i = 0; i < tableSize; ++i) {
            cout << i << ": ";
            for (auto &x: table[i]) {
                cout << x.value << " -> ";
            }
            cout << "NULL\n";
        }
    }
};


class OpenAddressingHashTable : protected HashTable {
private:
    vector<hashNode> table;
public:
    OpenAddressingHashTable(int size, function<int(int, int)> hashFunc)
            : HashTable(size, hashFunc), table(size) {}

    void insert(int key) override {
        int index = hashFunction(key, tableSize);
        while (table[index].state == State::TAKEN) {
            index = (index + 1) % tableSize;
        }
        table[index].value = key;
        table[index].state = State::TAKEN;
        elementCount++;
        if (elementCount > tableSize / 2) {
            rehash();
        }
    }

    bool search(int key) override {
        int index = hashFunction(key, tableSize);
        int start = index;
        while (table[index].state != State::EMPTY) {
            if (table[index].value == key) return true;
            index = (index + 1) % tableSize;
            if (index == start) break;
        }
        return false;
    }

    void remove(int key) override {
        int index = hashFunction(key, tableSize);
        int start = index;
        while (table[index].state != State::EMPTY) {
            if (table[index].value == key) {
                table[index].state = State::Deleted;
                elementCount--;
                return;
            }
            index = (index + 1) % tableSize;
            if (index == start) break;
        }
        cout << "Key not found!" << '\n';
    }

    void rehash() override {
        int newSize = tableSize * 2;
        vector<hashNode> newTable(newSize);

        for (auto &key: table) {
            if (key.state == State::TAKEN) {
                int newIndex = hashFunction(key.value, newSize);
                while (newTable[newIndex].state != State::EMPTY) {
                    newIndex = (newIndex + 1) % newSize;
                }
                newTable[newIndex] = key;
            }
        }

        tableSize = newSize;
        table = newTable;
    }

    void display() const override {
        for (int i = 0; i < tableSize; ++i) {
            if (table[i].state == State::TAKEN)
                cout << i << ": " << table[i].value << "\n";
        }
    }
};

class DoubleHashingHashTable : public HashTable {
private:
    vector<hashNode> table;
    function<int(int, int)> secondaryHashFunction;

public:
    DoubleHashingHashTable(int size, function<int(int, int)> hashFunc,
                           function<int(int, int)> secondaryHashFunc)
            : HashTable(size, hashFunc), table(size), secondaryHashFunction(secondaryHashFunc) {}

    void insert(int key) override {
        int index = hashFunction(key, tableSize);
        int step = secondaryHashFunction(key, tableSize);

        while (table[index].state == State::TAKEN) {
            index = (index + step) % tableSize;
        }

        table[index] = key;
        elementCount++;

        if (elementCount > tableSize / 2) {
            rehash();
        }
    }

    bool search(int key) override {
        int index = hashFunction(key, tableSize);
        int step = secondaryHashFunction(key, tableSize);
        int start = index;

        while (table[index].state != State::TAKEN) {
            if (table[index] == key) return true;
            index = (index + step) % tableSize;
            if (index == start) break;
        }

        return false;
    }

    void remove(int key) override {
        int index = hashFunction(key, tableSize);
        int step = secondaryHashFunction(key, tableSize);
        int start = index;

        while (table[index].state != State::TAKEN) {
            if (table[index] == key) {
                table[index].state = State::EMPTY;
                elementCount--;
                return;
            }
            index = (index + step) % tableSize;
            if (index == start) break;
        }

        cout << "Key not found!" << endl;
    }

    void rehash() override {
        int newSize = tableSize * 2;
        vector<hashNode> newTable(newSize);

        for (auto &key: table) {
            if (key.state != State::EMPTY) {
                int index = hashFunction(key.value, newSize);
                int step = secondaryHashFunction(key.value, newSize);
                while (newTable[index].state == State::TAKEN) {
                    index = (index + step) % newSize;
                }
                newTable[index] = key;
            }
        }

        tableSize = newSize;
        table = newTable;
    }

    void display() const {
        for (int i = 0; i < tableSize; ++i) {
            if (table[i].state == State::TAKEN)
                cout << i << ": " << table[i].value << "\n";
        }
    }
};

int main() {
    auto secondaryHash = [](int key, int tableSize) { return 1 + (key % (tableSize - 1)); };

    cout << "Chaining Method:\n";
    ChainingHashTable chainingTable(5, divisionHash);
    chainingTable.insert(10);
    chainingTable.insert(20);
    chainingTable.insert(15);
    chainingTable.insert(25);
    chainingTable.display();
    chainingTable.remove(15);
    chainingTable.display();

    cout << "\nOpen Addressing Method:\n";
    OpenAddressingHashTable openAddressingTable(5, divisionHash);
    openAddressingTable.insert(10);
    openAddressingTable.insert(20);
    openAddressingTable.insert(15);
    openAddressingTable.insert(25);
    openAddressingTable.display();
    openAddressingTable.remove(15);
    openAddressingTable.display();

    cout << "\nDouble Hashing Method:\n";
    DoubleHashingHashTable doubleHashingTable(5, divisionHash, secondaryHash);
    doubleHashingTable.insert(10);
    doubleHashingTable.insert(20);
    doubleHashingTable.insert(15);
    doubleHashingTable.insert(25);
    doubleHashingTable.display();
    doubleHashingTable.remove(15);
    doubleHashingTable.display();

    return 0;
}
