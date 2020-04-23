#include <iostream>
#include "Service.h"

//#include <Windows.h>
//#include <stdlib.h>
//#include <signal.h>
//#include "../mongoose/mongoose/Server.h"
//#include "../mongoose/mongoose/WebController.h"
//
//
//using namespace std;
//using namespace Mongoose;
//
//class MyController : public WebController
//{
//private:
//	Service service;
//
//	
//
//public:
//	void add(Request& request, StreamResponse& response)
//	{
//
//	}
//	void get(Request& request, StreamResponse& response)
//	{
//
//	}
//	void modify(Request& request, StreamResponse& response)
//	{
//
//	}
//	void remove(Request& request, StreamResponse& response)
//	{
//
//	}
//
//	void hello(Request& request, StreamResponse& response)
//	{
//		response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
//	}
//
//	void setup()
//	{
//		// Example.
//		addRoute("GET", "/hello", MyController, hello);
//
//
//		addRoute("POST", "/add", MyController, add);
//		addRoute("GET", "/get", MyController, get);
//		addRoute("PUT", "/modify", MyController, modify);
//		addRoute("DELETE", "/remove", MyController, remove);
//	}
//};
//
//
//int main()
//{
//	MyController myController;
//	Server server(8080);
//	server.registerController(&myController);
//
//	server.start();
//
//	while (1) {
//		Sleep(10);
//	}
//}

void RunCLI(Service &service);

int main()
{
	Service service;
	RunCLI(service);
	return 0;
}

void RunCLI(Service &service)
{
	std::string input = "";
	std::string language, lang_code, key, translation;

	// Spins until the user enters 'q'.
	while (input != "q")
	{
		// Grab the user input.
		std::cout << "Add (a), get (g), modify (m), remove (r) or quit (q)?: ";
		std::cin >> input;
		std::cin.ignore();
		
		// Each option needs language and key, so they get picked up before the
		// option specific if statements (unless the user wants to exit).
		if (input != "q")
		{
			std::cout << "Language (IANA code or plain text)?: ";
			std::cin >> language;
			std::cin.ignore();

			lang_code = service.GetLanguageCode(language);

			// If the language is invalid, the loop resets.
			if (lang_code.empty())
			{
				std::cout << "Invalid language." << std::endl;

				// Removing the input to get the nice printout at the end.
				input = "";
			}
			else
			{				
				std::cout << "Key: ";
				std::cin >> key;
				std::cin.ignore();
			}
		}

		// Add
		if (input == "a")
		{
			// Get the chosen translation for the language-key pair and add to the service object.
			std::cout << "Translation string: ";
			std::getline(std::cin, translation);

			bool result = service.Add(lang_code, key, translation);
			if (result)
			{
				std::cout << "Success!" << std::endl;
			}
			else
			{
				std::cout << "Key already exists." << std::endl;
			}

		}
		// Get
		else if (input == "g")
		{
			// Get the translation corresponding to the language and key,
			// unless it does not exist.
			std::string translation = service.Get(lang_code, key);
			if (translation.empty())
			{
				std::cout << "No translation exists for key." << std::endl;
			}
			else
			{
				std::cout << "Translation: " << translation << std::endl;
			}
		}
		// Modify
		else if (input == "m")
		{
			// Similar to add, but only allow modifications.
			std::cout << "Enter new translation string: ";
			std::getline(std::cin, translation);

			bool result = service.Modify(lang_code, key, translation);
			if (!result)
			{
				std::cout << "No entry found for given key and language." << std::endl;
			}
			else
			{
				std::cout << "Success!" << std::endl;
			}
		}
		// Remove
		else if (input == "r")
		{
			// Attempts to remove an entry if it exists.
			bool result = service.Remove(lang_code, key);
			if (!result)
			{
				std::cout << "No entry found for given key and language." << std::endl;
			}
			else
			{
				std::cout << "Successfully removed." << std::endl;
			}
		}
		// Just for looks.
		std::cout << std::endl << "--------------------------------------------------------" << std::endl << std::endl;
	}
}