#include "../../includes.h"

CLVM::CLVM( size_t memoryPoolSize, size_t stackSize ) : bytecode( nullptr ), bytecode_size( 0 ), memoryManager( memoryPoolSize ), stackManager( stackSize )
{
    dispatcher = std::make_unique<InstructionDispatcher>( nullptr );
}

CLVM::~CLVM( )
{
    if ( bytecode ) memoryManager.deallocate( bytecode );
}

auto CLVM::load_bytecode( const std::string& lua_code ) -> void
{
    try
    {
        auto bytecode_vector = BytecodeLoader::load_bytecode( lua_code );
        bytecode_size = bytecode_vector.size( );

        if ( bytecode_size == 0 )
        {
            throw CLVMBytecodeLoadException( "Failed to load bytecode." );
        }

        bytecode = new unsigned char[ bytecode_size ];
        std::memcpy( bytecode, bytecode_vector.data( ), bytecode_size );

        dispatcher = std::make_unique<InstructionDispatcher>( bytecode );
    }
    catch ( const std::exception& e ) 
    {
        throw CLVMBytecodeLoadException( "Error loading bytecode: " + std::string( e.what( ) ) );
    }
}

auto CLVM::execute( ) -> void
{
    if ( !bytecode || bytecode_size == 0 ) 
    {
        throw std::runtime_error( "No bytecode loaded" );
    }

    try
    {
        dispatcher->run( );
        memoryManager.collect_garbage( );
    }
    catch ( const std::exception& e )
    {
        throw CLVMBytecodeExecutionException( "Bytecode execution failed: " + std::string( e.what( ) ) );
    }
}