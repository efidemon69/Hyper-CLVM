#include "workspace/includes.h"

auto start::main( ) -> int
{
    CLVM vm( 1024 * 1024, 1024 );
    lua_State* L = luaL_newstate( );
    luaL_openlibs( L );

    const std::string lua_code = R"( print("clvm in 2034 is real?!!!") )";
    BytecodeEncoder encoder;
    std::vector<unsigned char> bytecode;

    try
    {
        bytecode = encoder.encode( lua_code );
        std::string bytecode_str( bytecode.begin( ), bytecode.end( ) );
        vm.load_bytecode( bytecode_str );
        vm.execute( );
    }
    catch ( const std::exception& e )
    {
        std::cout << "Error: " << e.what( ) << std::endl;
    }

    return 0;
}

auto DllMain( HMODULE hmod, DWORD reason, LPVOID res ) -> bool APIENTRY
{
    UNREFERENCED_PARAMETER( hmod );
    UNREFERENCED_PARAMETER( res );

    if ( reason == 0x1 )
    {
        start::main( );
    }
}