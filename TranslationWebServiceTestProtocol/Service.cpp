#include "Service.h"

constexpr uint8_t LANG_CODE_START = 8;
constexpr uint8_t LANGUAGE_START = 13;


void Service::ReadIANA()
{
	std::ifstream IANA;
	IANA.open("IANA.txt");

	std::string line, lang_code, language;

	while (std::getline(IANA, line))
	{
		// Checks if the beginning of the line matches "Subtag" 
		// as that marks a line with a language code.
		if (line.substr(0, 6).compare("Subtag") == 0)
		{
			// Grab the language code from the end of "Subtag: " to the end of the line.
			lang_code = line.substr(LANG_CODE_START, line.length() - LANG_CODE_START);

			// The language in plain text is always the next line.
			std::getline(IANA, line);

			// Grab the language from the end of "Description: " to the end of the line.
			language = line.substr(LANGUAGE_START, line.length() - LANGUAGE_START);

			// Map the code to the language and vice versa.
			this->codeToLang[lang_code] = language;
			this->langToCode[language] = lang_code;
		}
	}
	IANA.close();
}

void Service::ReadExisitingStrings()
{
	std::ifstream existing_strings;
	existing_strings.open("TranslatedStrings.txt");

	std::string lang_code, key, translation;

	/*
		The format within the file is:

		language code
		key
		translation

		The loop reads them in that order until the end of the file
		and maps them in memory.
	*/
	while (std::getline(existing_strings, lang_code))
	{
		std::getline(existing_strings, key);
		std::getline(existing_strings, translation);

		this->translatedStrings[lang_code][key] = translation;
	}
}

Service::Service()
{
	this->ReadIANA();
	this->ReadExisitingStrings();
}

std::string Service::Get(const std::string& lang_code, const std::string& key)
{
	return this->translatedStrings[lang_code][key];
}

bool Service::Add(const std::string& lang_code, const std::string& key, const std::string& translation)
{
	bool added = false;	

	// Checks that the given key for the given language does not already exist.
	if (this->translatedStrings[lang_code].find(key) == this->translatedStrings[lang_code].end())
	{
		// Adds the translation to the mapping.
		this->translatedStrings[lang_code][key] = translation;

		// Writes the information to file.
		std::ofstream translated_string_file;
		translated_string_file.open("TranslatedStrings.txt", std::ofstream::out | std::ofstream::app);
		translated_string_file << lang_code << std::endl;
		translated_string_file << key << std::endl;
		translated_string_file << translation << std::endl;
		translated_string_file.close();

		added = true;
	}

	return added;
}

bool Service::Modify(const std::string& lang_code, const std::string& key, const std::string& new_translation)
{
	bool exists = false;

	// Checks that there is a translation for the key, if so it changes the contents.
	if (this->translatedStrings[lang_code].find(key) != this->translatedStrings[lang_code].end())
	{
		this->translatedStrings[lang_code][key] = new_translation;
		exists = true;
	}	

	return exists;
}

bool Service::Remove(const std::string& lang_code, const std::string& key)
{
	// Attempts to erase the element at (lang_code, key), erase returns the number
	// of elements deleted (0 or 1) which can be converted to a boolean to show if
	// the operation was a success.
	uint8_t number_erased = this->translatedStrings[lang_code].erase(key);
	return bool(number_erased);
}

bool Service::LanguageExists(std::string user_input)
{
	bool exists = false;

	// Checks both language mappings to see if the given user input matches a language.
	if (this->codeToLang.find(user_input) != this->codeToLang.end() && this->langToCode.find(user_input) != this->langToCode.end())
	{
		exists = true;
	}
	return exists;
}

std::string Service::GetLanguageCode(std::string user_input)
{
	std::string language_code = "";

	// Checks if the user input either matches a code or a language, and returns the code.
	if (this->codeToLang.find(user_input) != this->codeToLang.end())
	{
		language_code = user_input;
	}
	else if (this->langToCode.find(user_input) != this->langToCode.end())
	{
		language_code = this->langToCode[user_input];
	}
	return language_code;
}
