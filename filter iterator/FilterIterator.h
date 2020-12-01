#pragma once
#include <algorithm>
#include <iterator>
#include <type_traits>
template <class  T>
struct is_true   {
	constexpr bool operator()(const T& x) { return true; }
	constexpr bool operator()(const T& x) const { return true;}
};

template <class Iterator,class Predicate= typename is_true<typename std::iterator_traits<Iterator>::value_type>>
class Filter_Class final{
private:
	Iterator m_begin;
	Iterator m_end;
	Predicate  m_pred;
public:	
	template< class T>
	class filter_iterator final
	{
		Iterator current;
		std::conditional_t<std::is_const_v<T>, const Filter_Class&, Filter_Class& > parent;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using pointer = T*;
		using reference = std::remove_reference_t<T> & /*std::conditional_t < std::is_const_v<T>, const std::remove_reference_t<T>&, std::remove_reference_t<T>&>*/;
		using const_reference = const std::remove_reference_t<T>&;
	private:
		bool check_by_predicate(const  Iterator& cur)const {
			return cur != parent.m_end && !parent.m_pred(*cur);
		};
	public:
		filter_iterator(std::conditional_t<std::is_const_v<T>,const Filter_Class & ,Filter_Class & >parent, Iterator cur ) :parent(parent),current(cur) {
			while (check_by_predicate(current))
				++current;
		};
		reference operator*()  { 
			return *current;
		};
		const_reference operator*() const {
			return *current;
		};
		filter_iterator& operator++() {
			if (parent.m_begin == parent.m_end) return *this;
			do {
				++current;
			} while (check_by_predicate(current));
			return *this;
		};
		filter_iterator operator++(int) {
			filter_iterator  temp = *this;
			++(*this);
			return temp;
		};
		bool operator !=(const filter_iterator& temp) const {
			return !((*this)==temp);
		}
		bool operator ==(const filter_iterator& temp) const {
			return temp.current == current && &parent==&temp.parent;
		}
	};
	public:
		using const_filter_iterator = filter_iterator<const typename std::iterator_traits<Iterator>::value_type>;
	public:
		decltype(auto) begin(){
			return filter_iterator<typename std::iterator_traits<Iterator>::value_type>(*this,m_begin);
		};
		decltype(auto) end() {
			return filter_iterator<typename std::iterator_traits<Iterator>::value_type>(*this,m_end);
		};
		const_filter_iterator begin() const {
			return const_filter_iterator(*this, m_begin);
		};
		const_filter_iterator  end() const {
			return const_filter_iterator(*this, m_end);
		};
		const_filter_iterator cbegin() const{
			return begin();
		};
		const_filter_iterator  cend() const  {
			return end();
	};
public:
	Filter_Class(Predicate f, Iterator& x, Iterator& _end = Iterator()) :m_pred(f), m_begin(x), m_end(_end) {};
	Filter_Class(Iterator &x, Iterator& _end = Iterator()) : m_begin(x), m_end(_end) {};
};
template <class Iterator, class Predicate>
Filter_Class <Iterator, Predicate> make_filter_class(Predicate f,Iterator x, Iterator end = Iterator()) {
	return(Filter_Class<Iterator, Predicate>(f, x, end));
}
template <class Iterator>
Filter_Class < Iterator> make_filter_class( Iterator x, Iterator end = Iterator()) {
	return(Filter_Class<Iterator>(x, end));
}

