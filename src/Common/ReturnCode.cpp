#include <simpleutils/Common/ReturnCode.hpp>

namespace simpleutils::Common
{
    ReturnCode::ReturnCode(ErrorCode code) :
        m_Code(code)
    {
    }

    ReturnCode::operator bool() const
    {
        return m_Code == ErrorCode::None;
    }

    ErrorCode ReturnCode::GetCode() const
    {
        return m_Code;
    }

} // namespace simpleutils::Common
