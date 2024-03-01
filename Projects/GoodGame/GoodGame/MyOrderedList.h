#pragma once
#include <forward_list>

template <class LMNOP> class MyOrderedList {
public:
	MyOrderedList(bool (*gT)(LMNOP t1, LMNOP t2));
		
	void addInSequence(LMNOP o);
	void removeFromSequence(LMNOP o);

	auto getIteratorStart();
	auto getIteratorEnd();

private:
	bool (*greaterThan)(LMNOP t1, LMNOP t2);
	std::forward_list<LMNOP> data;
};




template<class LMNOP> MyOrderedList<LMNOP>::MyOrderedList(bool(*gT)(LMNOP t1, LMNOP t2)) {
	data = std::forward_list<LMNOP>();
	greaterThan = gT;
}
template<class LMNOP> void MyOrderedList<LMNOP>::addInSequence(LMNOP o) {
	auto i = data.begin();
	auto j = data.before_begin();

	while (i != data.end()) {
		if (greaterThan(*i, o)) {
			data.insert_after(j, o);
			return;
		}
		i++;
		j++;
	}
	data.insert_after(j, o);
	return;
}
template<class LMNOP> void MyOrderedList<LMNOP>::removeFromSequence(LMNOP o) {
	data.remove(o);
}
template<class LMNOP> auto MyOrderedList<LMNOP>::getIteratorStart() {
	return data.begin();
}
template<class LMNOP> auto MyOrderedList<LMNOP>::getIteratorEnd() {
	return data.end();
}