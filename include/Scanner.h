#pragma once
#include <string>
#include <iostream>
namespace atan {
namespace json {
    class Scanner {
        public:
            Scanner(std::string source):source_(source), current_(0){};
            enum class JsonTokenType{
                BEGIN_OBJECT, ///< {
                END_OBJECT, ///< }
                VALUE_SEPARATOR, ///< ,
                NAME_SEPARATOR, ///< :

                VALUE_STRING, ///<"string"
                VALUE_NUMBER, ///< 1,2,3, 2e10,

                LITERAL_TRUE, /// true
                LITERAL_FALSE, /// false
                LITERAL_NULL, /// null

                BEGIN_ARRAY, ///<[
                END_ARRAY, ///<[


                END_OF_SOURCE ///< EOF
            };
            
            friend std::ostream& operator<<(std::ostream& os, const JsonTokenType& type) {
                switch (type) {
                case JsonTokenType::BEGIN_ARRAY:
                    os << "[";
                    break;
                case JsonTokenType::END_ARRAY:
                    os << "]";
                    break;
                case JsonTokenType::BEGIN_OBJECT:
                    os << "{";
                    break;
                case JsonTokenType::END_OBJECT:
                    os << "}";
                    break;
                case JsonTokenType::NAME_SEPARATOR:
                    os << ":";
                    break;
                case JsonTokenType::VALUE_SEPARATOR:
                    os << ",";
                    break;
                case JsonTokenType::VALUE_NUMBER:
                    os << "number";
                    break;
                case JsonTokenType::VALUE_STRING:
                    os << "string";
                    break;
                case JsonTokenType::LITERAL_TRUE:
                    os << "true";
                    break;
                case JsonTokenType::LITERAL_FALSE:
                    os << "false";
                    break;
                case JsonTokenType::LITERAL_NULL:
                    os << "null";
                    break;
                case JsonTokenType::END_OF_SOURCE:
                    os << "EOF";
                    break;
                default:
                    break;
                }
                return os;
            }
            JsonTokenType Scan();
            std::string GetValueString(){return value_string_;}
            float GetValueNumber(){return value_number_;}
            void Rollback();
        private:
            char Advance();
            bool IsAtEnd();
            void ScanTrue();
            void ScanFalse();
            void ScanNull();
            void ScanString();
            void ScanNumber();
            bool IsDigit(char c);
            char Peek();
            char PeekNext();
            std::string source_; ///json<source
            size_t current_;    ///current handler pos
            size_t prev_pos_;   /// prev handler pos
            std::string value_string_;
            float value_number_;
    };
}  // namespace json
}  // namespace atan
