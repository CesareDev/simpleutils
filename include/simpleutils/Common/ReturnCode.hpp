#ifndef SIMPLEUTILS_RETURNCODE_HPP
#define SIMPLEUTILS_RETURNCODE_HPP

namespace simpleutils::Common
{
    enum class ErrorCode
    {
        None = 0,
        Unknown,
        InvalidArgument,
        InvalidState,
        NotInitialized,
        AlreadyInitialized,
        NotSupported,

        // Resources
        ResourceUnavailable,
        ResourceExhausted,
        PermissionDenied,

        // IO
        FileNotFound,
        FileAlreadyOpen,
        FileNotOpen,
        ReadFailed,
        WriteFailed,
        EndOfFile,

        // Network
        InvalidAddress,
        AddressInUse,
        ConnectionFailed,
        ConnectionClosed,
        ConnectionRefused,
        ConnectionReset,
        NetworkUnreachable,
        Timeout,

        // Threading
        ThreadCreationFailed,
        ThreadAlreadyRunning,
        ThreadNotRunning,
        ThreadPoolStopped,

        // Parsing
        InvalidFormat,
        ParseFailed
    };

    class ReturnCode
    {
        public:
            ReturnCode(ErrorCode code = ErrorCode::None);

            explicit operator bool() const;

            ErrorCode GetCode() const;

        private:
            ErrorCode m_Code {};
    };
} // namespace simpleutils::Common

#endif // SIMPLEUTILS_RETURNCODE_HPP