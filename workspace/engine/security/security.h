#pragma once

class SecurityManager
{
public:
	explicit SecurityManager( );
	~SecurityManager( );

	auto is_external_call( const std::string& function_name ) -> bool const;
};