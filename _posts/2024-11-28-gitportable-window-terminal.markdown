---
layout: post
title:  "Git Portable 을 사용, 윈도우 터미널에 추가해보자"
author: "minxdive"
categories: statement
tags: [Git, Windows Terminal]
image: 
---

많은 분들이 사용하는 Github 와 Git 인데요, Git 을 Portable ("thumbdrive edition") 즉 무설치로 받아서 사용해보겠습니다.

![1](https://github.com/user-attachments/assets/7e52dc09-2831-4042-b763-4264a5d7e726)

저는 64 비트 환경이라 64 비트를 받았습니다.

다운받고 압축을 풀면, PortableGit 폴더가 있고, 그 안에 Git 의 폴더와 파일들이 존재하는것을 알 수 있습니다. 자신이 원하는 곳에 PortableGit 폴더를 배치합니다. 저는 그냥 C 에 두었습니다.

이제 환경 변수를 설정해야 합니다.

![2](https://github.com/user-attachments/assets/620ebaa7-31a3-4c80-a1b4-ba10e2ed85f1)

실행(`Window + R`) 에서 `sysdm.cpl` 을 입력합니다.

![3](https://github.com/user-attachments/assets/6b2d2ae8-7a2f-4823-84c5-e68448bf512d)

이제 고급 -> 환경 변수를 클릭합니다.

![4](https://github.com/user-attachments/assets/ce4dd5a0-c36e-4316-8e6f-e851509b1a58)

시스템 변수를 내리시면 `Path` 가 있습니다. 더블클릭 해줍니다.

![5](https://github.com/user-attachments/assets/5cd98662-a8ec-40b2-928e-9416a0f1f18d)

새로 만들기를 하시고, 자신이 설정한 Git 폴더안의 cmd 폴더로 경로를 설정하시면 되겠습니다.

![6](https://github.com/user-attachments/assets/3e098e32-a918-407e-b526-caf3ffefcc9d)
![7](https://github.com/user-attachments/assets/bf9da762-c962-41e4-a2c8-178b4d5cef1c)

Powershell, cmd 모두 `git -v` 을 입력해보니 잘 출력됨을 알 수 있습니다.

마지막으로, Windows Terminal 에서 Git 을 추가하여 사용해보겠습니다.

터미널에서 설정에 들어가시고 왼쪽을 보시면 프로필 항목이 있습니다.

![8](https://github.com/user-attachments/assets/69f2ef3a-194f-463a-8cb5-39e4a3c5fe9f)

새 프로필 추가를 클릭합니다. 

그리고, 새 빈 프로필을 클릭합니다.

![9](https://github.com/user-attachments/assets/033530be-f309-4391-b6b9-fd4e8a4c08f1)

이런식으로 새로운 프로필이 생성되었습니다. 명령줄 항목을 클릭하고, 찾아보기를 클릭합니다.

다운받았던 Git 폴더에 bin 폴더가 있습니다.

![10](https://github.com/user-attachments/assets/69d80e5c-75c0-4c92-a780-7cc17d2e5866)

bash 를 선택합니다.

이제 터미널에서 Git 을 사용할 수 있습니다. 저는 추가로 이름, 아이콘도 설정하였습니다. 

모두 마치셨다면, 저장을 클릭합니다.

윈도우 터미널에서 새 탭으로 열기를 클릭하면, 우리가 추가한 프로필이 나타납니다.

![11](https://github.com/user-attachments/assets/051cb88d-ecd2-4b97-b2d7-1338d95c451c)

저는 Git-bash 로 추가하였습니다.

자신이 추가한 Git 을 클릭하시면, 

![12](https://github.com/user-attachments/assets/41409f7e-f9b7-45ee-af68-d824dcfb9d8d)

정상적으로 Git 이 실행됨을 알 수 있습니다.

<br><br><br>