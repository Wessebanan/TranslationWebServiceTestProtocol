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
		if (line.substr(0, 6).compare("Subtag") == 0)
		{
			lang_code = line.substr(LANG_CODE_START, line.length() - LANG_CODE_START);
			std::getline(IANA, line);
			language = line.substr(LANGUAGE_START, line.length() - LANGUAGE_START);

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

	if (this->translatedStrings[lang_code].find(key) == this->translatedStrings[lang_code].end())
	{
		this->translatedStrings[lang_code][key] = translation;

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

	if (this->translatedStrings[lang_code].find(key) != this->translatedStrings[lang_code].end())
	{
		this->translatedStrings[lang_code][key] = new_translation;
		exists = true;
	}	

	return exists;
}

bool Service::Remove(const std::string& lang_code, const std::string& key)
{
	uint8_t number_erased = this->translatedStrings[lang_code].erase(key);
	return bool(number_erased);
}

bool Service::LanguageExists(std::string user_input)
{
	bool exists = false;
	if (this->codeToLang.find(user_input) != this->codeToLang.end() && this->langToCode.find(user_input) != this->langToCode.end())
	{
		exists = true;
	}
	return exists;
}

std::string Service::GetLanguageCode(std::string user_input)
{
	std::string language_code = "";
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
