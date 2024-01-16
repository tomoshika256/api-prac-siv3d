# include <Siv3D.hpp>
void Post(int guess_num,int seed_num) {
	const URL url = U"http://tk2-242-30965.vs.sakura.ne.jp:8080/03/guessNumberHard/";
	const HashTable<String, String> headers = { { U"Content-Type", U"application/json" } };
	const std::string data = JSON{
		{ U"guess", guess_num},
		{U"seed",seed_num},
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

void Main()
{
	
	while (System::Update())
	{
		if (KeyA.down())
			Post(5,5);
		
	}
}


