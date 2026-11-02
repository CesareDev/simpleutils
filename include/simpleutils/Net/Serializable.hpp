#ifndef SIMPLEUTILS_SERIALIZABLE_HPP
#define SIMPLEUTILS_SERIALIZABLE_HPP

namespace simpleutils::Net
{
    class Buffer;

    class Serializable
    {
        public:
            virtual ~Serializable() = default;

        protected:
            virtual bool Serialize(Buffer& buffer) const = 0;
            virtual bool Deserialize(Buffer& buffer) = 0;

        friend class Buffer;
    };
} // namespace simpleutils::Net


#endif // SIMPLEUTILS_SERIALIZABLE_HPP