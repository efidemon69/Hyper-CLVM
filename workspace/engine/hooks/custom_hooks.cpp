#include "../../includes.h"

CustomHooks::CustomHooks( ) : before_instruction_hook( nullptr ), after_instruction_hook( nullptr ), on_error_hook( nullptr ) {}

auto CustomHooks::set_before_instruction_hook( HookCallback callback ) -> void
{
    before_instruction_hook = std::move( callback );
}

auto CustomHooks::set_after_instruction_hook( HookCallback callback ) -> void 
{
    after_instruction_hook = std::move( callback );
}

auto CustomHooks::set_on_error_hook( HookCallback callback ) -> void
{
    on_error_hook = std::move( callback );
}

auto CustomHooks::call_before_instruction( ) -> void
{
    if ( before_instruction_hook )
    {
        before_instruction_hook( );
    }
}

auto CustomHooks::call_after_instruction( ) -> void 
{
    if ( after_instruction_hook ) 
    {
        after_instruction_hook( );
    }
}

auto CustomHooks::call_on_error( ) -> void 
{
    if ( on_error_hook )
    {
        on_error_hook( );
    }
}