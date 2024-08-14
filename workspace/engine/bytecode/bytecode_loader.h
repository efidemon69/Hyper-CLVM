#pragma once

class BytecodeLoader
{
public:
    static auto load_bytecode( const std::string& lua_code ) -> std::vector<unsigned char>;

private:
    //static auto compile_lua_code( const std::string& lua_code, std::vector<unsigned char>& bytecode ) -> void;
};