#include <string>

class Serializable
{
public:
    virtual std::string toString() const = 0;
};
