
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct EntityBlueprint
{
    std::string name;
    std::vector<std::string> componentNames;
};

struct FileReader
{
    private:
        std::ifstream& file;
        char nextChar;
        bool hasNext;
    public:
        FileReader(std::ifstream& f) : file(f), hasNext(false)
        {
            advance();
        }

        char next()
        {
            char current = nextChar;
            advance();
            return current;
        }

        char peek() const
        {
            return nextChar;
        }

        bool isEOF() const
        {
            return !hasNext;
        }

        bool expect(char c)
        {
            if (nextChar == c)
            {
                next();
                return true;
            } else return false; 

        }

        void skipWhitespace() {
            while (hasNext && std::isspace(nextChar)) {
                advance();
            }
        }


    private:
        void advance()
        {
            if (file.get(nextChar))
            {
                hasNext = true;
            } else
            {
                hasNext = false;
            }
        }

};


int main()
{
    std::ifstream jsonFile("test.json");
    
    if (!jsonFile.is_open())
    {
        std::cerr << "Error opening the file";
        return 1;
    }
    
    FileReader reader{jsonFile};

    
    reader.skipWhitespace();
    if (!reader.expect('{'))
    {
        std::cerr << "FactoryJsonLoader: Did not expect '" << reader.peek() << "'";
        return -1;
    }


    jsonFile.close();

    

    return 0;
}