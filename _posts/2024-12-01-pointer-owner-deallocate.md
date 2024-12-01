---
layout: post
title: "포인터 소유, 동적할당 해제"
author: "minxdive"
categories: statement, diary
tags: [C++]
image: 
---

원시(raw) 포인터의 소유권을 다른 포인터에게 이전했을때, 그 포인터는 어떻게 되는지 궁금하였다.

```c++
#include <print>    // std::print
#include <cstdio>   // printf, puts
#include <cstdint>  // uint16_t
#include <string>   // std::string

template<typename T, typename P>
class Bayern_munchen {
  T name;
  P number;
public:
  Bayern_munchen(const T& nam, const P& num)
    : name(nam), number(num) 
  { 
    std::print("Servus {1}, {0}\n", number, name);
  }
  ~Bayern_munchen()
  {
    std::print("Ciao, {0}\n", name);
  }

  Bayern_munchen& set_change_profile(const T& nam, const P& num)
  {
    name = nam;
    number = num;
    std::print("Servus {1}, {0}\n", number, name);
    return *this;
  }
  T get_name() const
  {
    return name;
  }
  P get_number() const 
  {
    return number;
  }
  void print_profile(const uint16_t& year, const std::string& country) 
  {
    std::print("FC Bayern München No. {0}, {1}, {2}, {3}\n", number, name, year, country);
  }
};

int main() 
{
  Bayern_munchen<std::string, uint16_t>* minjae = new Bayern_munchen<std::string, uint16_t>("MINJAE", 3);
  minjae->print_profile(1996, "Korea Republic");
  minjae->set_change_profile("UPAMECANO", 2);

  puts("----------------------------------------------------------------------------------------------");

  printf("Address to point to (포인터가 가리키는 주소) %p\n", minjae);
  printf("My address          (포인터의 주소)          %p\n", &minjae);

  puts("----------------------------------------------------------------------------------------------");
  
  Bayern_munchen<std::string, uint16_t>* upamecano = nullptr;

  // ----------------------------------------------------------------------------------------------

  printf("Address to point to (포인터가 가리키는 주소) %p, %p\n", minjae, upamecano);
  printf("My address          (포인터의 주소)          %p, %p\n", &minjae, &upamecano);

  // ----------------------------------------------------------------------------------------------

  upamecano = minjae;

  puts("----------------------------------------------------------------------------------------------");

  printf("Address to point to (포인터가 가리키는 주소) %p, %p\n", minjae, upamecano);
  printf("My address          (포인터의 주소)          %p, %p\n", &minjae, &upamecano);
  
  puts("----------------------------------------------------------------------------------------------");
  
  minjae = nullptr;

  // ----------------------------------------------------------------------------------------------

  printf("Address to point to (포인터가 가리키는 주소) %p, %p\n", minjae, upamecano);
  printf("My address          (포인터의 주소)          %p, %p\n", &minjae, &upamecano);

  puts("----------------------------------------------------------------------------------------------");

  upamecano->print_profile(1998, "France");
  delete upamecano;

  if (minjae != nullptr)
  {
    std::print("nullptr 가 아니라고?\n");
    delete minjae;
  }

  return 0;
}
```

![1](https://github.com/user-attachments/assets/5fd62933-5cff-4851-9e70-4f5f9ae3c919)

만약 위와 같은 코드에서 실행했다면 다음과 같은 결과가 출력된다.
`upamecano = minjae` 를 하였더니, 두 포인터가 가리키는 주소가 같아졌다. 그러나 두 포인터는 별개의 포인터니 포인터가 가지고 있는 주소는 다르다.

그 후 `minjae = nullptr` 을 하여 가리키고 있는 주소를 해제하면 이제 `minjae` 는 `NULL` 을 가리키므로 주소가 `0000000000000000` 인 것을 알 수 있다.

여기서 궁금한 것이 있었다. 지금 `minjae` 는 `{}` 가 끝나는 시점까지 살아있게 된다. 그런데, `new` 선언으로 동적할당한 포인터가 범위를 벗어나도 할당 해제되는가..?

구글에도 검색(`stackoverflow`)해보고, `copilot` 에게도 물어보았다. 답은 아니었다.

`new` 로 동적할당한 포인터가 `nullptr` 을 할당받은 후, `delete` 를 시도해도 아무일도 일어나지 않는다고 한다. 그렇기 때문에 이 원시포인터는 여전히 범위를 벗어나도 존재하며 메모리 누수가 일어난다.

만일 어떠한 함수나 지역에서 이러한 일이 발생하면 큰일이었다. 

원시 포인터를 사용할 때 이러한 것을 주의하고 신중하게 사용해야 한다.

원시 포인터를 사용한다면, 언제 할당하고 언제 정확하게 해제되는지를 알고 가야한다. 또 왜 사용하는지, 이러한 것들을 명확하게 밝히고 사용해야 누수를 방지할 수 있다.

메모리 관리에 어려움을 겪는다면 스마트 포인터 쓰면 된다... 하지만 성능을 극단적으로 중시하는 경우라면 달라질지도 모르겠다.