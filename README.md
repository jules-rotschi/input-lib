# Input Lib

A small C++ library for scanning user inputs with error handling in console applications.

## C++ standard

This library is made for C++20. It is not compatible with earlier standards.

## Features

- Scanning an entire line to get the full string
- Scanning a specific type (such as `int` or `double`, or even custom types)
- Handling potential stream errors
- Handling data type error
- Validating input with rules that you define and handling validation errors
- Handling different types of string for inputs error messages (such as wide strings (`std::wstring`) for UTF-8 characters).

## Getting started

Copy `Input.h`, `Printer.h` and `StreamError` to your project. Include `Input.h` in the file you want to use the library features.

In your own code, implement the `Printer` class according to your needs.

Initialize a printer (your own implementation class) and an input scanner.

Then, you can use the functions `LineInput` and `Input` to handle user inputs.

## Example

As the library is designed to handle different types of string, here are two different examples : one for normal strings (`std::string`), and anotherone for wide strings that allow UTF-8 characters display.

### Normal strings

1. Printer implementation :

<code>
class Printer : public IL::Printer<char, std::string>
{
	void Print(char c) const override
	{
		std::cout << c;
	}

	void Print(const std::string& str) const override
	{
		std::cout << str;
	}

	void BreakLine() const override
	{
		std::cout << '\n';
	}
};
</code>

2. Handling inputs :

<code>
Printer printer;

std::string name;
int age = 0;

IL::InputScanner<char, std::string, std::istream> scanner(&printer, std::cin, "Stream error...", "Invalid input. Please retry.");

scanner.LineInput("What is your name ?", name, []([[maybe_unused]] const std::string& _) { return true; }, "");
scanner.Input<int>("How old are you ?", age, [](int ageInput) { return ageInput >= 0 && ageInput < 150; }, "Age should be positive and under 150.");

std::cout << "Hey " << name << ", you are " << age << " years old !" << std::endl;
</code>

### Wide strings

1. Printer implementation :

<code>
class FrenchPrinter : public IL::Printer<wchar_t, std::wstring>
{
	void Print(wchar_t c) const override
	{
		std::wcout << c;
	}

	void Print(const std::wstring& str) const override
	{
		std::wcout << str;
	}

	void BreakLine() const override
	{
		std::wcout << L'\n';
	}
};
</code>

2. Setting up console for UTF-16 (which includes UTF-8) :

<code>
_setmode(_fileno(stdin), _O_U16TEXT);
_setmode(_fileno(stdout), _O_U16TEXT);
</code>

3. Handling inputs :

<code>
FrenchPrinter frenchPrinter;

std::wstring frenchName;
int frenchAge = 0;

IL::InputScanner<wchar_t, std::wstring, std::wistream> frenchScanner(&frenchPrinter, std::wcin, "Erreur de flux...", L"Entrée invalide. Réessayez.");

frenchScanner.LineInput(L"Quel est ton nom ?", frenchName, []([[maybe_unused]] const std::wstring& _) { return true; }, L"");
frenchScanner.Input<int>(L"Quel âge as-tu ?", frenchAge, [](int ageInput) { return ageInput >= 0 && ageInput < 150; }, L"L'âge doit être compris entre 0 et 150.");

std::wcout << L"Salut " << frenchName << L", tu as " << frenchAge << L" ans !" << std::endl;
</code>