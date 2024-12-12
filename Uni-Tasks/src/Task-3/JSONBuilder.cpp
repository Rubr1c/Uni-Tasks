#include "JSONBuilder.h"

std::ostringstream JSONBuilder::buffer;
bool JSONBuilder::is_first_item = true;
size_t JSONBuilder::indent_level = 0;
size_t JSONBuilder::object_depth = 0;
size_t JSONBuilder::array_depth = 0;

void JSONBuilder::startObject(bool newLine) {
    if (!is_first_item) buffer << ",\n";
    if (newLine) addIndentation();
    buffer << "{";
    if (newLine) buffer << "\n";
    indent_level += 2;  
    is_first_item = true;
    object_depth++;
}

void JSONBuilder::endObject() {
    indent_level -= 2; 
    buffer << "\n";
    addIndentation();
    buffer << "}";
    is_first_item = false;
    object_depth--;
}

void JSONBuilder::startArray(const std::string& key) {
    if (!is_first_item) buffer << ",\n";
    addIndentation();
    buffer << "\"" << key << "\": [\n";
    indent_level += 2;
    is_first_item = true;
    array_depth++;
}

void JSONBuilder::endArray() {
    buffer << "\n";
    indent_level -= 2;  
    addIndentation();
    buffer << "]";
    is_first_item = false;
    array_depth--;
}


void JSONBuilder::addRawValue(const std::string& value) {
    if (!is_first_item) buffer << ",\n";
    addIndentation();
    buffer << value;
    is_first_item = false;
}

std::string JSONBuilder::build() {
    return buffer.str();
}

void JSONBuilder::clear() {
    buffer.str("");
    buffer.clear();
    is_first_item = true;
    indent_level = 0;
    object_depth = 0;
    array_depth = 0;
}

void JSONBuilder::addIndentation() {
    buffer << std::string(indent_level, ' ');
}

void JSONBuilder::addKey(const std::string& key) {
    buffer << "\"" << key << "\": ";
}