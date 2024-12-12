#pragma once

#include <string>
#include <sstream>

class JSONBuilder {
public:
    static void startObject(bool newLine = true);
    static void endObject();
    static void startArray(const std::string& key);
    static void endArray();

    template <typename T>
    static void addKeyValue(const std::string& key, const T& value);

    static void addRawValue(const std::string& value);
    static std::string build();
    static void clear();

private:
    static std::ostringstream buffer;
    static bool is_first_item;
    static size_t indent_level;
    static size_t object_depth;
    static size_t array_depth;

    static void addIndentation();
    static void addKey(const std::string& key);

    template <typename T>
    static void addValue(const T& value);

    template <>
    static void addValue<std::string>(const std::string& value) {
        buffer << "\"" << value << "\"";
    }
};

template <typename T>
void JSONBuilder::addKeyValue(const std::string& key, const T& value) {
    if (!is_first_item) buffer << ",\n";
    addIndentation();
    addKey(key);
    addValue(value);
    is_first_item = false;
}

template <typename T>
void JSONBuilder::addValue(const T& value) {
    buffer << value;
}
