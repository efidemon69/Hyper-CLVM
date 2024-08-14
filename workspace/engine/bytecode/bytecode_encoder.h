#pragma once

class BytecodeEncoderException : public std::exception 
{
public:
    explicit BytecodeEncoderException( const char* message );
    explicit BytecodeEncoderException( const std::string& message );
    auto what( ) const noexcept -> const char* override;

private:
    std::string message_;
};

class BytecodeEncoder
{
public:
    static auto encode( const std::string& lua_code ) -> std::vector<unsigned char>;
private:
    static auto lua_dump_callback( lua_State* L, const void* p, size_t sz, void* ud ) -> int;
    static auto compile_lua_code( lua_State* L, const std::string& lua_code, std::vector<unsigned char>& bytecode ) -> void;
};