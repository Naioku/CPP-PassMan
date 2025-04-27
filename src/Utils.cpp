#include "Utils.h"

#include <ranges>
#include <unordered_map>

char Utils::toLowerChar(const char c)
{
    static const std::unordered_map<char, char> polishMap = {
        {'Ą', 'ą'}, {'Ć', 'ć'}, {'Ę', 'ę'}, {'Ł', 'ł'},
        {'Ń', 'ń'}, {'Ó', 'ó'}, {'Ś', 'ś'}, {'Ź', 'ź'}, {'Ż', 'ż'}
    };

    if (const auto it = polishMap.find(c); it != polishMap.end())
        return it->second;

    return std::tolower(static_cast<unsigned char>(c));
}

std::string Utils::toLower(const std::string& str)
{
    auto view = str | std::views::transform(toLowerChar);
    return {view.begin(), view.end()};
}

bool Utils::isSubsting(const std::string& str, const std::string& substring, const bool caseSensitive)
{
    std::string originalStr;
    std::string prefixStr;

    if (!caseSensitive)
    {
        originalStr = toLower(originalStr);
        prefixStr = toLower(prefixStr);
    }
    else
    {
        originalStr = str;
        prefixStr = substring;
    }

    return originalStr.find(prefixStr) != std::string::npos;
}
