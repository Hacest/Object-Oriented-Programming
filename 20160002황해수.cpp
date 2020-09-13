// RoomEscape.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <bangtal.h>
using namespace bangtal;

int main()
{
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);
	auto open1 = false;

	auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{
			key->pick();
			return true;
		});

	auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
	auto flowerpot_moved = false;
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (flowerpot_moved == false)
			{
				if (action == MouseAction::MOUSE_DRAG_LEFT)
				{
					flowerpot->locate(scene1, 450, 150);
					flowerpot_moved = true;
				}
				else if (action == MouseAction::MOUSE_DRAG_RIGHT)
				{
					flowerpot->locate(scene1, 650, 150);
					flowerpot_moved = true;
				}
			}
			return true;
		});

	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (open1 == true)
			{
				scene2->enter();
			}
			else if (key->isHanded())
			{
				door1->setImage("Images/문-오른쪽-열림.png");
				open1 = true;
			}
			else
			{
				showMessage("열쇠가 필요합니다");
			}

			return true;

		});

	auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool
		{
			scene1->enter();
			return true;
		});

	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270, false);
	auto open3 = false, locked3 = true;
	door3->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool
		{
			if (locked3 == true)
			{
				showMessage("문이 잠겨있다");
			}
			else if (open3 == true)
			{
				endGame();
			}
			else if (open3 == false)
			{
				door3->setImage("Images/문-오른쪽-열림.png");
				open3 = true;
			}
			return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool
		{
			showMessage("철커덕");
			locked3 = false;
			return true;
		});

	auto keypad = Object::create("Images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool
		{
			showKeypad("BANGTAL", door3);
			return true;
		});

	auto button = Object::create("Images/스위치.png", scene2, 880, 440);
	auto password = Object::create("Images/암호.png", scene2, 400, 100, false);
	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr Object, int x, int y, MouseAction action)->bool
		{
			if (lighted)
			{
				scene2->setLight(0.1f);
				lighted = false;
				password->show();
				door3->show();
			}
			else
			{
				scene2->setLight(1.0f);
				lighted = true;
				password->hide();
				door3->hide();
			}
			return true;
		});

	startGame(scene1);

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
