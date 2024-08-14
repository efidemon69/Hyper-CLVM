#include "../../includes.h"

StackManager::StackManager( size_t stackSize ) : maxSize( stackSize )
{
    stack.reserve( stackSize );
}

StackManager::~StackManager( )
{

}

auto StackManager::push( int value ) -> void
{
    check_overflow( ); // tha was the issue
    stack.push_back( value );
}

auto StackManager::pop( ) -> int
{
    check_underflow( );
    int value = stack.back( );
    stack.pop_back( );
    return value;
}

auto StackManager::peek( size_t offset ) -> int
{
    if ( offset >= stack.size( ) )
    {
        throw std::out_of_range( "Stack peek out of range" );
    }

    return stack[ stack.size( ) - 1 - offset ];
}

auto StackManager::new_frame( ) -> void
{
    frames.push_back( stack.size( ) );
}

auto StackManager::end_frame( ) -> void
{
    if ( frames.empty( ) )
    {
        throw std::runtime_error( "No frame to end" );
    }

    size_t frameSize = frames.back( );
    frames.pop_back( );

    while ( stack.size( ) > frameSize )
    {
        stack.pop_back( );
    }
}

auto StackManager::check_overflow( ) -> void
{
    if ( stack.size( ) >= maxSize )
    {
        throw std::overflow_error( "Stack overflow" );
    }
}

auto StackManager::check_underflow( ) -> void
{
    if ( stack.empty( ) )
    {
        throw std::underflow_error( "Stack underflow" );
    }
}