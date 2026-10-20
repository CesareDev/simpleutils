#ifndef SIMPLEUTILS_XMLLOADER_HPP
#define SIMPLEUTILS_XMLLOADER_HPP

#include <simpleutils/Config/Loader.hpp>

namespace simpleutils::Config
{
    class XmlLoader : public Loader
    {
        public:
            XmlLoader();
            ~XmlLoader();

            bool LoadFromFile(const std::string& filePath) override;
    };
} // namespace simpleutils::Config


#endif // SIMPLEUTILS_XMLLOADER_HPP