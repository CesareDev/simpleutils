#ifndef SIMPLEUTILS_JSONLOADER_HPP
#define SIMPLEUTILS_JSONLOADER_HPP

#include <simpleutils/Config/Loader.hpp>

namespace simpleutils::Config
{
    class JsonLoader : public Loader
    {
        public:
            JsonLoader();
            ~JsonLoader();

            bool LoadFromFile(const std::string& filePath) override;
    };
} // namespace simpleutils::Config


#endif // SIMPLEUTILS_JSONLOADER_HPP