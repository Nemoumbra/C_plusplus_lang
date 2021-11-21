#include <iostream>
#include <cstring>

class String {
private:
    char * string;
    int len;
    int capacity;
public:
    String(const char * str) {
        int p = -1;
        while (str[++p]);
        //p == number of symbols before '\n'
        capacity = 2 * p;
        len = p;
        string = new char[capacity];
        memcpy(string, str, len);
    }
    String(unsigned int count, char c) {
        capacity = 2 * count;
        len = count;
        string = new char[capacity];
        memset(string, c, count);
    }
    String(int size = 16) {
        len = 0;
        capacity = size;
        string = new char[size];
    }
    String(const String& str) {
        string = new char[str.capacity];
        len = str.len;
        capacity = str.capacity;
        memcpy(string, str.string, len);
    }

    String& operator=(const String& str) {
        if (this == &str) {
            return *this;
        }
        if (str.len > capacity) {
            delete[] string;
            capacity = str.capacity;
            string = new char[capacity];
        }
        len = str.len;
        memcpy(string, str.string, len);
        return *this;
    }

    char& operator[](unsigned int index) {
        return string[index];
    }
    const char& operator[](unsigned int index) const {
        return string[index];
    }

    unsigned int length() const{
        return len;
    }
    void push_back(char c) {
        // _ _ _ _;_ _ _ _ _ _ _ _ _
        //   len  ; capacity - len
        len++;
        if (len > capacity) { // actually len == capacity + 1
            capacity *= 2;
            char* temp = new char[capacity];
            memcpy(temp, string, len - 1);
            delete[] string;
            string = temp;
        }
        string[len - 1] = c;
    }
    void pop_back() {
        len--;
        if (len < capacity / 4) {
            capacity /= 2;
            char* temp = new char[capacity];
            memcpy(temp, string, len);
            delete[] string;
            string = temp;
        }
    }

    char& front() {
        return string[0];
    }
    const char& front() const {
        return string[0];
    }

    char& back() {
        return string[len - 1];
    }
    const char& back() const {
        return string[len - 1];
    }

    String& operator+=(char c) {
        push_back(c);
        return *this;
    }
    String& operator+=(const String& str) {
        if (len + str.len > capacity) {
            capacity = 2 * (len + str.len);
            char* temp = new char[capacity];
            memcpy(temp, string, len);
            delete[] string;
            string = temp;
        }
        memcpy(string + len, str.string, str.len);
        len += str.len;
        return *this;
    }

    bool operator==(const String& str) const{
        if (str.len - len) {
            return false;
        }
        return memcmp(string, str.string, len) == 0;
    }

    unsigned int find(const String& substr) const{
        if (substr.len == 0) {
            return 0;
        }
        bool found_one = false;
        unsigned int res = 0;
        int i, j;
        for (i = 0, j = 0; (i < len) && (j < substr.len); ) {
            if (found_one) {
                if (string[i] == substr.string[j]) {
                    ++i;
                    ++j;
                } else {
                    found_one = false;
                    i = res + 1;
                    j = 0;
                }
            } else {
                if (string[i] == substr.string[j]) {
                    res = i;
                    found_one = true;
                    ++j;
                }
                ++i;
            }
        }
        if (i == len && j < substr.len) {
            return len;
        }
        return found_one ? res : len;
    }
    unsigned int rfind(const String& substr) const {
        if (substr.len == 0) {
            return len;
        }
        bool found_one = false;
        unsigned int res = 0;
        int i, j;
        for (i = len - 1, j = substr.len - 1; (i >= 0) && (j >= 0); ) {
            if (found_one) {
                if (string[i] == substr.string[j]) {
                    --i;
                    --j;
                } else {
                    found_one = false;
                    i = res - 1;
                    j = substr.len - 1;
                }
            } else {
                if (string[i] == substr.string[j]) {
                    res = i;
                    found_one = true;
                    --j;
                }
                --i;
            }
        }
        if (i == -1 && j >= 0) {
            return len;
        }
        return found_one ? (res - substr.len + 1) : len;
    }

    String substr(unsigned int start, unsigned int count) const {
        String temp(count);
        memcpy(temp.string, string + start, count);
        temp.len = count;
        return temp;
    }

    bool empty() const {
        return len == 0;
    }
    void clear(bool release_all = false) {
        len = 0;
        delete[] string;
        if (!release_all) {
            string = new char[1];
            capacity = 1;
        } else {
            capacity = 0;
        }
    }
    ~String() {
        clear(true);
    }
};

std::istream& operator>>(std::istream& stream, String& str) {
    char c;
    str.clear();
    while (!stream.eof()) {
        stream.get(c);
        if (stream.fail() || isspace(c)) {
            break;
        }
        str.push_back(c);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const String& str) {
    for (unsigned int i = 0; i < str.length(); ++i) {
        stream << str[i];
    }
    return stream;
}

String operator+(const String& str1, const String& str2) {
    String temp(str1);
    temp += str2;
    return temp;
}
String operator+(char c, const String& str) {
    String temp(1, c);
    temp += str;
    return temp;
}
String operator+(const String& str, char c) {
    String temp(str);
    temp += c;
    return temp;
}
