#ifndef UTILS_H
#define UTILS_H
#include <string>


class Utils {
public:
    static std::string toLower(const std::string& str);
    static bool isSubsting(const std::string& str, const std::string& substring, bool caseSensitive = true);

private:
    static char toLowerChar(char c);
};

#endif //UTILS_H
