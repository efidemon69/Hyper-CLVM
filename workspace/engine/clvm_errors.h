#pragma once

enum class CLVMErrorCode
{
    MEMORY_ALLOCATION_FAILED,
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    BYTECODE_LOAD_FAILED,
    BYTECODE_EXECUTION_FAILED,
    UNKNOWN_ERROR,
    NIGGA_CODE
};

class CLVMException : public std::runtime_error 
{
public:
    CLVMException( const std::string& message, CLVMErrorCode code ) : std::runtime_error( message ), errorCode( code ) {}

    CLVMErrorCode get_error_code( ) const 
    {
        return errorCode;
    }

private:
    CLVMErrorCode errorCode;
};

class CLVMMemoryException : public CLVMException
{
public:
    CLVMMemoryException( const std::string& message ) : CLVMException( message, CLVMErrorCode::MEMORY_ALLOCATION_FAILED ) {}
};

class CLVMStackOverflowException : public CLVMException
{
public:
    CLVMStackOverflowException( const std::string& message ) : CLVMException( message, CLVMErrorCode::STACK_OVERFLOW ) {}
};

class CLVMStackUnderflowException : public CLVMException 
{
public:
    CLVMStackUnderflowException( const std::string& message ) : CLVMException( message, CLVMErrorCode::STACK_UNDERFLOW ) {}
};

class CLVMBytecodeLoadException : public CLVMException 
{
public:
    CLVMBytecodeLoadException( const std::string& message ) : CLVMException( message, CLVMErrorCode::BYTECODE_LOAD_FAILED ) {}
};

class CLVMBytecodeExecutionException : public CLVMException
{
public:
    CLVMBytecodeExecutionException( const std::string& message ) : CLVMException( message, CLVMErrorCode::BYTECODE_EXECUTION_FAILED ) {}
};

inline const char* error_code_to_string( CLVMErrorCode code )
{
    switch ( code )
    {
        case CLVMErrorCode::MEMORY_ALLOCATION_FAILED: return "Memory allocation failed";
        case CLVMErrorCode::STACK_OVERFLOW: return "Stack overflow";
        case CLVMErrorCode::STACK_UNDERFLOW: return "Stack underflow";
        case CLVMErrorCode::BYTECODE_LOAD_FAILED: return "Bytecode load failed";
        case CLVMErrorCode::BYTECODE_EXECUTION_FAILED: return "Bytecode execution failed";
        case CLVMErrorCode::UNKNOWN_ERROR: return "Unknown error";
        default: return "Invalid error code";
    }
}