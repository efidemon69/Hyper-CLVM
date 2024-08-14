#include "../../includes.h"

MemoryManager::MemoryManager( size_t size ) : pool_size( size )
{
    // todo init
}

MemoryManager::~MemoryManager( ) 
{
    collect_garbage( );
}

auto MemoryManager::allocate( size_t size ) -> void*
{
    void* ptr = malloc( size );
    if ( ptr == nullptr )
    {
        throw std::bad_alloc( );
    }

    heap[ ptr ] = false; 
    return ptr;
}

auto MemoryManager::deallocate( void* ptr ) -> void 
{
    auto it = heap.find( ptr );
    if ( it != heap.end( ) )
    {
        heap.erase( it );
        free( ptr );
    }

    else throw std::runtime_error( "Attempt to deallocate untracked memory" );
}

auto MemoryManager::collect_garbage( ) -> void 
{
    mark_and_sweep( );
}

auto MemoryManager::mark_and_sweep( ) -> void 
{
    for ( void* root : roots )
    {
        mark( root );
    }

    sweep( );
}

auto MemoryManager::mark( void* ptr ) -> void 
{
    auto it = heap.find( ptr );
    if ( it != heap.end( ) && !it->second )
    {
        it->second = true; 
    }
}

auto MemoryManager::sweep( ) -> void 
{
    for ( auto it = heap.begin( ); it != heap.end( ); ) 
    {
        if ( !it->second )
        {
            free( it->first );
            it = heap.erase( it );
        }

        else ++it;
    }
}

auto MemoryManager::add_root( void* root ) -> void 
{
    roots.push_back( root );
}