---
layout: post
title:  "Vscode 에서 SDL2 사용하기"
author: "minxdive"
categories: expression, diary
tags: [C++, SDL2]
image: 
---

SDL2 를 Vscode 에서 사용하고 싶은데, 디버깅 (F5) 키를 누르고 컴파일하고 싶었는데 에러가 매번마다 발생하였다.

그래서 구글, 유튜브에 온갖 튜토리얼 글, 영상들과 Vscode 의 json 파일들을 다루는 글들을 찾아보았었다.

몇시간동안 해매고다니니 어찌어찌 결국에는 성공하였다.

이 글을 다시 찾는 미래의 나와 어쩌다가 여기에 오신 분들이 고생을 안 하셨으면 좋겠다.

`c_cpp_properties.json`, `launch.json`, `tasks.json` 를 열어보시고 경로를 반드시 확인하고 컴파일하기 바랍니다... 왜냐하면 모두 경로는 조금씩 다를수도있고, 다른 폴더에서 사용하고 싶을수도 있으니까요.

[SDL2_And_Vscode](https://github.com/minxdive/SDL2_And_Vscode.git)

<br><br><br>