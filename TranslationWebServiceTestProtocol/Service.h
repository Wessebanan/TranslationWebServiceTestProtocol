#ifndef SERVICE
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

// Uses the IANA Language Subtag Registry OR full language names. 
// https://www.iana.org/assignments/language-subtag-registry/language-subtag-registry

class Service
{
private:
	// Mapping of language codes to mapping of (key, translation) pairs.
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translatedStrings;

	// Mappings of language codes to plain text languages and vice versa.
	std::unordered_map<std::string, std::string> codeToLang;
	std::unordered_map<std::string, std::string> langToCode;

	// Reads language codes from IANA.txt and stores them.
	void ReadIANA();

	// Reads prior entries.
	void ReadExisitingStrings();

public:

	Service();

	// Retrieve a translated string from language code and key.
	std::string Get(const std::string& lang_code, const std::string& key);	

	// Add a new entry to the 'database'.
	bool Add(const std::string& lang_code, const std::string& key, const std::string& translation);

	// Modify an existing entry in the 'database'.
	bool Modify(const std::string& lang_code, const std::string& key, const std::string& new_translation);

	// Remove an existing entry in the 'database'.
	bool Remove(const std::string& lang_code, const std::string& key);

	// Check if the given language matches either a language code or a language.
	bool LanguageExists(std::string user_input);

	// Get a language code from the user input, returns an empty string if it does not match.
	std::string GetLanguageCode(std::string user_input);
};

#endif // SERVICE

