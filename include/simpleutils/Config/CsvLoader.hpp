#ifndef SIMPLEUTILS_CSVLOADER_HPP
#define SIMPLEUTILS_CSVLOADER_HPP

#include <simpleutils/Config/Loader.hpp>

namespace simpleutils::Config
{
    class CsvLoader : public Loader
    {
        public:
            CsvLoader();
            ~CsvLoader();

            bool LoadFromFile(const std::string& filePath) override;
    };
} // namespace simpleutils::Config


#endif // SIMPLEUTILS_CSVLOADER_HPP