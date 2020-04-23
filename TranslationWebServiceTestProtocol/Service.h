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
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translatedStrings;
	std::unordered_map<std::string, std::string> codeToLang;
	std::unordered_map<std::string, std::string> langToCode;

	void ReadIANA();
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

	bool LanguageExists(std::string user_input);
	std::string GetLanguageCode(std::string user_input);


};

#endif // SERVICE

