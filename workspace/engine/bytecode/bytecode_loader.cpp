#include "../../includes.h"

auto BytecodeLoader::load_bytecode( const std::string& lua_code ) -> std::vector<unsigned char>
{
    return BytecodeEncoder::encode( lua_code );
}