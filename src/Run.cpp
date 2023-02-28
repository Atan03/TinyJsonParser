#include <iostream>
#include <Scanner.h>
#include <Parser.h>
int main(){
    using namespace atan::json;
    auto source = R"(
    {
        "glossary" : {
            "testa" : true,
            "testb" : 1200
        }
    }
)";
    Scanner scanner(source);
    Parser parser(scanner);
    Scanner::JsonTokenType type;
    JsonElement* element = parser.Parse();
    std::cout << element->Dumps();
    delete element;
}
