---
layout: post
title:  "static 멤버의 정의"
author: "minxdive"
categories: expression, diary
tags: [C++]
image: 
---

TMP 에 대하여 알고싶어서 ChatGPT 에게 간단한 문제를 제시받아서 풀어보았다.

템플릿 특수화로 내가 원하는 자료형이 올 경우에만 `true` 를 받도록 되어있다. 사실 저렇게 일일이 따로 특수화를 하는것은 좋다고 생각들지 않지만 지금은 그냥 넘어가자.

여기서 눈여겨 볼것은 `static` 이다. `static` 멤버는 외부에서 정의하여야 한다고 한다. 템플릿이 아닌 멤버는 내부에서 `static const` 일 경우에는 내부에서 초기화 할 수 있다.

템플릿의 경우에는 `const` 유무와 관계없이 `static` 일 경우 외부에서 정의하여야 한다.

```c++
#include <print>

// 정수형
template<typename T>
struct is_integral {
  static const bool value = false;
};
template<typename T>
const bool is_integral<T>::value;

template<>  // 템플릿 특수화
struct is_integral<int> {
  static const bool value = true;
};
// static 데이터 멤버는 외부에서 선언...
const bool is_integral<int>::value;


// 부동 소수점
template<typename T>
struct is_float_point {
  static const bool value = false;
};
template<typename T>
const bool is_float_point<T>::value;

template<>
struct is_float_point<float> {
  static const bool value = true;
};
const bool is_float_point<float>::value;

template<>
struct is_float_point<double> {
  static const bool value = true;
};
const bool is_float_point<double>::value;


int main() 
{
  std::println("{0}", is_integral<int>::value);        // true
  std::println("{0}", is_float_point<float>::value);   // true
  std::println("{0}", is_float_point<double>::value);  // true

  std::println("{0}", is_integral<float>::value);      // false

  return 0;
}
```

<br><br><br>