#include <iostream>
#include "Service.h"

#include <Windows.h>
#include <stdlib.h>
#include <signal.h>
#include "../mongoose/mongoose/Server.h"
#include "../mongoose/mongoose/WebController.h"


using namespace std;
using namespace Mongoose;

class MyController : public WebController
{
private:
	Service service;

public:
	void add(Request& request, StreamResponse& response)
	{

	}
	void get(Request& request, StreamResponse& response)
	{

	}
	void modify(Request& request, StreamResponse& response)
	{

	}
	void remove(Request& request, StreamResponse& response)
	{

	}

	void hello(Request& request, StreamResponse& response)
	{
		response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
	}

	void setup()
	{
		addRoute("GET", "/hello", MyController, hello);
		addRoute("POST", "/add", MyController, add);
		addRoute("GET", "/get", MyController, get);
		addRoute("PUT", "/modify", MyController, modify);
		addRoute("DELETE", "/remove", MyController, remove);
	}
};


int main()
{
	MyController myController;
	Server server(8080);
	server.registerController(&myController);

	server.start();

	while (1) {
		Sleep(10);
	}
}

void RunCLI(Service &service);

//int main()
//{
//	Service service;
//	RunCLI(service);
//	return 0;
//}

void RunCLI(Service &service)
{
	std::string input = "";
	std::string language, lang_code, key, translation;
	while (input != "q")
	{
		std::cout << "Add (a), get (g), modify (m), remove (r) or quit (q)?: ";
		std::cin >> input;

		if (input == "q")
		{
			std::cout << "Language (IANA code or plain text)?: ";
			std::cin >> language;
			lang_code = service.GetLanguageCode(language);

			if (lang_code.empty())
			{
				std::cout << "Invalid language." << std::endl;
				continue;
			}

			std::cout << "Key: ";
			std::cin >> key;
			std::cin.ignore();
		}

		if (input == "a")
		{
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
		else if (input == "g")
		{
			std::string translation = service.Get(lang_code, key);
			if (translation.empty())
			{
				std::cout << "No translation exists for key." << std::endl;
			}
			else
			{
				std::cout << translation << std::endl;
			}
		}
		else if (input == "m")
		{
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
		else if (input == "r")
		{
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
		std::cout << std::endl << std::endl;
	}
}