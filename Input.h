#pragma once

#include <string>
#include <functional>

#include "Printer.h"
#include "StreamError.h"

namespace IL
{
	template <typename Char, typename String, typename InputStream>
	class InputScanner
	{
	public:
		InputScanner(const Printer<Char, String>* const printer, InputStream& inputStream, const std::string& streamErrorMessage, const String& invalidInputErrorMessage)
			: m_Printer(printer), m_InputStream(inputStream), m_StreamErrorMessage(streamErrorMessage), m_InvalidInputErrorMessage(invalidInputErrorMessage) {}

		void LineInput(const String& questionString, String& outVar, const std::function<bool(const String&)>& validate, const String& predicateString)
		{
			if (!questionString.empty())
			{
				m_Printer->Print(questionString);
				m_Printer->BreakLine();
			}

			std::getline(m_InputStream, outVar);

			while (!validate(outVar))
			{
				if (m_InputStream.eof())
				{
					throw StreamError(m_StreamErrorMessage);
				}
				else if (m_InputStream.fail())
				{
					m_Printer->Print(m_InvalidInputErrorMessage);
					m_Printer->BreakLine();
					m_InputStream.clear();
					m_InputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
				{
					m_Printer->Print(predicateString);
					m_Printer->BreakLine();
				}

				std::getline(m_InputStream, outVar);
			}
		}

		template <typename T>
		void Input(const String& questionString, T& outVar, const std::function<bool(T)>& validate, const String& predicateString)
		{
			if (!questionString.empty())
			{
				m_Printer->Print(questionString);
				m_Printer->BreakLine();
			}

			while (!(m_InputStream >> outVar) || !validate(outVar))
			{
				if (m_InputStream.eof())
				{
					throw StreamError(m_StreamErrorMessage);
				}
				else if (m_InputStream.fail())
				{
					m_Printer->Print(m_InvalidInputErrorMessage);
					m_Printer->BreakLine();
					m_InputStream.clear();
					m_InputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				else
				{
					m_Printer->Print(predicateString);
					m_Printer->BreakLine();
					m_InputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}

			m_InputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	private:
		const Printer<Char, String>* const m_Printer;

		InputStream& m_InputStream;

		std::string m_StreamErrorMessage;
		String m_InvalidInputErrorMessage;
	};
}

