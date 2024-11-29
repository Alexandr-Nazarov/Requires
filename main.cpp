#include <iostream>
#include <list>
#include <vector>
//Функция может принимать любой контейнер, для которого реализован метод insert()
// и любое количество объектов для вставки. При этом, eсли для этого контейнера реализован метод reserve(),
// то прежде, чем вставлять, эффективнее зарезервировать нужный объем памяти

template <typename T>
constexpr bool haveInsert = requires(T t) { t.get().insert(t.get().begin(), 33); };

template <typename T>
constexpr bool haveReserve = requires(T t) { t.get().reserve(33); };

template<typename T, typename... Args>
void f(T&& t, Args&&... x) {

	if constexpr (haveReserve< T>) {

		t.get().reserve(sizeof...(x));
	}

	if constexpr (haveInsert<T>) {
		(t.get().insert(t.get().begin(), x), ...);
	}

}

int main(){

	std::vector<int> v;


	f(std::ref(v), 1, 3, 4, 0, 3);

	__asm nop

	std::list<int> l;
	f(std::ref(l), 1, 3, 4, 0, 3);
}