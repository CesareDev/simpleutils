#ifndef SIMPLEUNIT_LOADER_HPP
#define SIMPLEUNIT_LOADER_HPP

#include <string>
#include <unordered_map>

namespace simpleutils::Config
{
    class Loader
    {
        public:
            Loader();
            virtual ~Loader();

            virtual bool LoadFromFile(const std::string& filePath) = 0;

        protected:
            std::unordered_map<std::string, std::string> m_Configs {};
    };
} // namespace simpleutils::Config


#endif // SIMPLEUNIT_LOADER_HPP