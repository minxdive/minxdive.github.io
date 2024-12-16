---
layout: post
title:  "SDL2 PollEvent 의 딜레이 문제"
author: "minxdive"
categories: expression, diary
tags: [C++, SDL2]
image: 
---

`SDL2` 에선 이벤트를 처리하는 함수인 `SDL_PollEvent` 함수가 있다. 그런데 이 함수의 문제로 루프처리를 할때 키보드 딜레이를 가지고 있다. 우리가 평소에 키를 꾹 눌러 입력하면 딜레이가 존재하는 것을 알 수 있다. 그런데, 우린 게임을 하는데 키 입력에 딜레이가 있기를 원하지 않는다. 게임 개발자가 딜레이를 의도하지 않은 이상 불편해질 것 이다.

```c++
while (SDL_PollEvent(&event)) {
  switch (event.type) {
  case SDL_QUIT:
    running = false;
    break;
  case SDL_KEYDOWN:
    // ...
    break;
  case SDL_KEYUP:
    // ...
    break;
  }
}
```

이렇게 `SDL_PollEvent` 에서 자신이 원하는대로 처리한다면 아마 딜레이때문에 불편을 겪은 경험이 있을 것이다. `reddit` 이나 `stackoverflow` 에서 제시한 간단한 방법은 `case` 에 `bool` 로 처리하거나, 아예 루프 바깥에서 `SDL_GetKeyboardState` 을 사용하는 방법도 있다.

나는 `bool` 의 `true`, `false` 를 판별하는 방법을 택했다.

```c++

void Game_engine::handle_event()
{
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      action_num = event.key.keysym.scancode;
      is_action = true;
      break;
    case SDL_KEYUP:
      is_action = false;
      break;
    }
  }
}

```


<br><br><br>