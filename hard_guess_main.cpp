# include <Siv3D.hpp>
#include <iostream>
#include <string>
void Post(int guess_num, int seed_num) {
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
	int guess_num=-1;
	int seed_num;
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	TextEditState te;
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	while (System::Update())
	{
		
		SimpleGUI::TextBox(te, Vec2{ 100, 140 });
		font(U"設定値は{}"_fmt(guess_num)).draw(64, Vec2{ 20, 20 }, ColorF{ 0.2, 0.4, 0.8 });
		if (te.text.isEmpty()==0&&KeyEnter.down())
			guess_num = Parse<int>(te.text);
		/*
		* seed_num = 1;
		if (KeyA.down())
			Post(guess_num, seed_num);
		*/
		
	}




}
