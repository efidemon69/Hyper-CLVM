#pragma once

class StackManager
{
public:
    explicit StackManager( size_t stackSize );
    ~StackManager( );

    auto push( int value ) -> void;
    auto pop( ) -> int;
    auto peek( size_t offset = 0 ) -> int;

    auto new_frame( ) -> void;
    auto end_frame( ) -> void;

private:
    std::vector<int> stack;
    std::vector<size_t> frames;
    size_t maxSize;

    auto check_overflow( ) -> void;
    auto check_underflow( ) -> void;
};