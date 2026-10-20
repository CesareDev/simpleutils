#include <simpleutils/Config/IniLoader.hpp>

#include <fstream>
#include <algorithm>

static std::string trim(std::string str)
{
    const auto first = std::find_if_not(
        str.begin(), str.end(),
        [](unsigned char c) { return std::isspace(c); });

    if (first == str.end())
        return "";

    const auto last = std::find_if_not(
        str.rbegin(), str.rend(),
        [](unsigned char c) { return std::isspace(c); }).base();

    return std::string(first, last);
}

namespace simpleutils::Config
{
    IniLoader::IniLoader()
    {
    }

    IniLoader::~IniLoader()
    {
    }

    bool IniLoader::LoadFromFile(const std::string& filePath)
    {
        std::ifstream file(filePath);

        if (!file.is_open()) return false;

        std::string line;
        std::string currentSection;

        while (std::getline(file, line))
        {
            line = trim(line);

            // Skip empty lines and comments
            if (line.empty() || line[0] == ';' || line[0] == '#')
                continue;

            // Parse section
            if (line.front() == '[' && line.back() == ']')
            {
                currentSection = trim(
                    line.substr(1, line.size() - 2));
                continue;
            }

            // Parse key = value
            const auto pos = line.find('=');
            if (pos == std::string::npos)
                continue;

            const std::string key = trim(line.substr(0, pos));
            const std::string value = trim(line.substr(pos + 1));

            if (!key.empty())
                m_Configs[currentSection + "/" + key] = value;
        }

        return true;
    }

    std::string IniLoader::Get(const std::string& section, const std::string& entry, const std::string& defaultValue) const
    {
        const auto it = m_Configs.find(section + "/" + entry);

        if (it == m_Configs.end())
            return defaultValue;

        return it->second;
    }

    std::string IniLoader::GetString(const std::string& section, const std::string& entry, const std::string& defaultValue) const
    {
        return Get(section, entry, defaultValue);
    }

    int IniLoader::GetInt(const std::string& section, const std::string& entry, int defaultValue) const
    {
        int tmp {};
        try
        {
            tmp = std::stoi(Get(section, entry, std::to_string(defaultValue)));
        }
        catch (const std::exception& e)
        {
            return defaultValue;
        }

        return tmp;
    }

    bool IniLoader::GetBool(const std::string& section, const std::string& entry, bool defaultValue) const
    {
        std::string tmp = Get(section, entry, std::to_string(defaultValue));

        // Tranform the string to lower case to handle "True", "TRUE", etc.
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        
        if (tmp == "true" || tmp == "1") return true;

        if (tmp == "false" || tmp == "0") return false;

        return defaultValue;
    }

} // namespace simpleutils::Config
