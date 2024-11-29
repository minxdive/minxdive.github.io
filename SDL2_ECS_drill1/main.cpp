/*
  ECS Game Programming 24/11/28

  24/11/29 Special weapon Blackhole 추가
           confin.txt 파일 추가, 메모장에서 파일을 읽어 크기 조정가능

  Dave Churchill (Memorial University) 
  Computer Science 4300 - Fall 2022 

  Churchill 교수의 강의를 보고, ECS 에 대하여 이해하고, 
  SDL2 로 게임을 만들어봅니다.
*/

#include <iostream>

#include "SDL2/SDL.h"

#include "game.h"

int main(int argc, char* argv[]) 
{
  try 
  {
    Game game = Game();
    game.start("Hello SDL2! Hello ECS!");

    return 0;
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << '\n';
    return -1;
  }
  catch (...)
  {
    std::cerr << "exception!\n";
    return -2;
  }

	return 0;
}
