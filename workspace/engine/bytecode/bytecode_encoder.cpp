#include "../../includes.h"

BytecodeEncoderException::BytecodeEncoderException( const char* message ) : message_( message ) {}
BytecodeEncoderException::BytecodeEncoderException( const std::string& message ) : message_( message ) {}

auto BytecodeEncoderException::what( ) const noexcept -> const char* 
{
    return message_.c_str( );
}

auto BytecodeEncoder::encode( const std::string& lua_code ) -> std::vector<unsigned char>
{
    std::vector<unsigned char> bytecode;
    lua_State* L = luaL_newstate( );
    if ( !L ) throw BytecodeEncoderException( "Failed to create Lua state" );
    luaL_openlibs( L );

    try 
    {
        compile_lua_code( L, lua_code, bytecode );
    }
    catch ( ... )
    {
        lua_close( L );
        throw;
    }

    lua_close( L );
    return bytecode;
}

auto BytecodeEncoder::lua_dump_callback( lua_State* L, const void* p, size_t sz, void* ud ) -> int 
{
    auto* bytecode = static_cast< std::vector<unsigned char>* >( ud );
    bytecode->insert( bytecode->end( ), static_cast< const unsigned char* >( p ), static_cast< const unsigned char* >( p ) + sz );
    return 0;
}

auto BytecodeEncoder::compile_lua_code( lua_State* L, const std::string& lua_code, std::vector<unsigned char>& bytecode ) -> void
{
    if ( luaL_loadstring( L, lua_code.c_str( ) ) || lua_pcall( L, 0, 0, 0 ) ) 
    {
        throw BytecodeEncoderException( lua_tostring( L, -1 ) );
    }

    lua_Debug ar;
    lua_getglobal( L, "_G" );
    //lua_pushcfunction( L, lua_dump_callback ); -> todo: fix
    lua_pushlightuserdata( L, &bytecode );
    lua_dump( L, lua_dump_callback, &bytecode );
}