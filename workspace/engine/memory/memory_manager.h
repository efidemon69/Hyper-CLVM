#pragma once

class MemoryManager
{
public:
    explicit MemoryManager( size_t size );
    ~MemoryManager( );

    auto allocate( size_t size ) -> void*;
    auto deallocate( void* ptr ) -> void;
    auto collect_garbage( ) -> void;

private:
    auto mark_and_sweep( ) -> void;
    auto mark( void* ptr ) -> void;
    auto sweep( ) -> void;
    auto add_root( void* root ) -> void;

    std::unordered_map<void*, bool> heap;
    std::vector<void*> roots;
    size_t pool_size;
};