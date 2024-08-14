#include "../../includes.h"

SecurityManager::SecurityManager( )
{
	// todo: init security seettings
}

SecurityManager::~SecurityManager( )
{
	// Cleanup resources
}

auto SecurityManager::is_external_call( const std::string& function_name ) -> bool const
{
	return true; // wow sir
}