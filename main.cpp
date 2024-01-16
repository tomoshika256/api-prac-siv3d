# include <Siv3D.hpp>
void Post() {
	const URL url = U"http://tk2-242-30965.vs.sakura.ne.jp:8080/02/hello";
	const HashTable<String, String> headers = { { U"Content-Type", U"application/json" } };
	const std::string data = JSON{
		{ U"name", U"Yamada Taro" },
	}
	.formatUTF8();
	const FilePath saveFilePath = U"post_result.json";

	if (auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), saveFilePath))
	{
		Console << U"------";
		Console << response.getStatusLine().rtrimmed();
		Console << U"status code: " << FromEnum(response.getStatusCode());
		Console << U"------";
		Console << response.getHeader().rtrimmed();
		Console << U"------";
		
		if (response.isOK())
		{
			Print << TextReader{ saveFilePath }.readAll();
		}
	}
	else
	{
		Print << U"Failed.";
	}
}

void Get()
{
	const URL url = U"http://tk2-242-30965.vs.sakura.ne.jp:8080/02/ping";
	const HashTable<String, String> headers = { { U"Authorization", U"Bearer TOKEN123456abcdef" } };
	const FilePath saveFilePath = U"auth_result.json";

	if (const auto response = SimpleHTTP::Get(url, headers, saveFilePath))
	{
		Console << U"------";
		Console << response.getStatusLine().rtrimmed();
		Console << U"status code: " << FromEnum(response.getStatusCode());
		Console << U"------";
		Console << response.getHeader().rtrimmed();
		Console << U"------";

		if (response.isOK())
		{
			Print << TextReader{ saveFilePath }.readAll();
		}
	}
	else
	{
		Print << U"Failed.";
	}
}

void Main()
{
	
	while (System::Update())
	{
		if (KeyA.down())
			Post();
		if (KeyS.down())
			Get();

	}
}


