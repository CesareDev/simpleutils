#ifndef SIMPLEUTILS_INILOADER_HPP
#define SIMPLEUTILS_INILOADER_HPP

#include <simpleutils/Config/Loader.hpp>

namespace simpleutils::Config
{
    class IniLoader : public Loader
    {
        public:
            IniLoader();
            ~IniLoader();

            bool LoadFromFile(const std::string& filePath) override;
            std::string Get(const std::string& section, const std::string& entry, const std::string& defaultValue = "") const;
            std::string GetString(const std::string& section, const std::string& entry, const std::string& defaultValue = "") const;
            int GetInt(const std::string& section, const std::string& entry, int defaultValue = 0) const;
            bool GetBool(const std::string& section, const std::string& entry, bool defaultValue = false) const;
    };
} // namespace simpleutils::Config


#endif // SIMPLEUTILS_INILOADER_HPP