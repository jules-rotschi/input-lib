#pragma once

namespace IL
{
	template <typename Char, typename String>
	class Printer
	{
	public:
		virtual ~Printer() = default;

		virtual void Print(Char c) const = 0;
		virtual void Print(const String& str) const = 0;
		virtual void BreakLine() const = 0;
	};
}
