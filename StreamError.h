#pragma once

#include <stdexcept>

namespace IL
{
	class StreamError : public std::runtime_error
	{
	public:
		inline StreamError(const std::string& message) : std::runtime_error(message) {};
	};
}
