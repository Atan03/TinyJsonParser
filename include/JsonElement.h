#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include "Error.h"
namespace atan{
namespace json{
    class JsonElement;
    using JsonObject = std::map<std::string, JsonElement*>;
    using JsonArray = std::vector<JsonElement*>;
    class JsonElement{
        public:
        enum class Type{
            JSON_OBJECT,
            JSON_ARRAY,
            JSON_STRING,
            JSON_NUMBER,
            JSON_BOOL,
            JSON_NULL
        };
        union Value{
            JsonObject* value_object;
            JsonArray* value_array;
            std::string* value_string;
            float value_number;
            bool value_bool;
        };
        JsonElement():JsonElement(Type::JSON_NULL){}
        JsonElement(Type type) : type_(type) {
            switch (type) {
            case Type::JSON_OBJECT:
                value_.value_object = new std::map<std::string, JsonElement*>();
                break;
            case Type::JSON_ARRAY:
                value_.value_array = new std::vector<JsonElement*>();
                break;
            case Type::JSON_STRING:
                value_.value_string = new std::string("");
                break;
            case Type::JSON_NUMBER:
                value_.value_number = 0;
                break;
            case Type::JSON_BOOL:
                value_.value_bool = false;
                break;
            case Type::JSON_NULL:
                break;
            default:
                break;
            }
        };
        JsonElement(JsonObject* value_object):type_(Type::JSON_OBJECT){value(value_object);}
        JsonElement(JsonArray* value_array): type_(Type::JSON_ARRAY){value(value_array);}
        JsonElement(std::string* value_string):type_(Type::JSON_STRING){value(value_string);}
        JsonElement(float* value_number):type_(Type::JSON_NUMBER){value(value_number);}
        JsonElement(bool* value_bool):type_(Type::JSON_BOOL){value(value_bool);}
        ~JsonElement(){
            if (type_ == Type::JSON_OBJECT) {
            JsonObject* object = value_.value_object;
            for (auto& [key, value] : *object) {
                delete value;
            }
            delete object;
            } else if (type_ == Type::JSON_ARRAY) {
            JsonArray* array = value_.value_array;
            for (auto& item : *array) {
                delete item;
            }
            delete array;
            } else if (type_ == Type::JSON_STRING) {
            std::string* val = value_.value_string;
            delete val;
            }
        }          
          Type type() { return type_; }
        void value(JsonObject* value_object){
            type_ = Type::JSON_OBJECT;
            value_.value_object = value_object;
        }
        void value(JsonArray* value_array){
            type_ = Type::JSON_ARRAY;
            value_.value_array = value_array;
        }
         void value(std::string* value_string){
            type_ = Type::JSON_STRING;
            value_.value_string= value_string;
        }      
        void value(float value_number){
            type_ = Type::JSON_NUMBER;
            value_.value_number = value_number;            
        }
        void value(bool value_bool){
            type_ = Type::JSON_BOOL;
            value_.value_bool= value_bool;      
        }
        JsonObject* AsObject(){
            if(type_ == Type::JSON_OBJECT) return value_.value_object;
            Error("Type of JsonElement isn't JsonObject!");
            return nullptr;
        }
        JsonArray* AsArray(){
            if(type_ == Type::JSON_ARRAY) return value_.value_array;
            Error("Type of JsonElement isn't ArrayObject!");
            return nullptr;
        }
        std::string* AsString(){
            if(type_ == Type::JSON_STRING) return value_.value_string;
            Error("Type of JsonElement isn't String!");
            return nullptr;
        }
        float AsNumber(){
            if(type_ == Type::JSON_NUMBER) return value_.value_number;
            Error("Type of JsonElement isn't Float!");  
            return 0.0f;          
        }
        bool AsBool(){
            if(type_ == Type::JSON_BOOL) return value_.value_bool;
            Error("Type of JsonElement isn't Bool!");   
            return false;
        }
        
        std::string Dumps() {
            std::stringstream ss;
            switch (type_) {
            case Type::JSON_OBJECT:
                ss << *(value_.value_object);
                break;
            case Type::JSON_ARRAY:
                ss << *(value_.value_array);
                break;
            case Type::JSON_STRING:
                ss << '\"' << *(value_.value_string) << '\"';
                break;
            case Type::JSON_NUMBER:
                ss << value_.value_number;
                break;
            case Type::JSON_BOOL:
                ss << (value_.value_bool == true ? "true" : "false");
                break;
            case Type::JSON_NULL:
                ss << "null";
                break;
            default:
                break;
            }
            return ss.str();
        }

        friend std::ostream& operator<<(std::ostream& os, const JsonObject& object) {
            os << "{";
            for (auto iter = object.begin(); iter != object.end(); iter++) {
            os << '\"' << iter->first << '\"' << ": " << iter->second->Dumps();
            if (iter != --object.end()) {
                os << ", ";
            }
            }
            os << "}";
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
            os << "[";
            for (size_t i = 0; i < array.size(); i++) {
            os << array[i]->Dumps();
            if (i != array.size() - 1) {
                os << ", ";
            }
            }
            os << "]";
            return os;
        }
        
        private:
        Type type_;
        Value value_;
    };
}
}