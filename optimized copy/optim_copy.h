#pragma once
#include <algorithm>
#include <iterator>
#include <type_traits>
#include<vector>
namespace copy {
	template<class Iterator>
	struct Is_Contiguous {
		static constexpr bool value= std::is_pointer_v<Iterator>|| 
			std::is_same_v<Iterator, typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>;
	};
	template<class InputIterator, class OutputIterator>
	struct Is_Same_Value
	{
		static constexpr bool value = std::is_same_v<typename  std::iterator_traits<InputIterator>::value_type,typename std::iterator_traits<OutputIterator>::value_type>;
	};
	template<class InputIterator, class OutputIterator>
	typename std::enable_if_t< Is_Contiguous<InputIterator>::value && Is_Contiguous<OutputIterator>::value&& Is_Same_Value<InputIterator,OutputIterator>::value,
	OutputIterator> copy(InputIterator first, InputIterator last, OutputIterator result) {
		if (first == last) return result;
		const std::ptrdiff_t num = std::distance(first,last);
		typename std::iterator_traits<OutputIterator>::pointer _first = &*first;
		typename std::iterator_traits<OutputIterator>::pointer	_result = &*result;
		memmove(_result, _first, (num) * sizeof(decltype(*first)));
		return result ;
	};
	template<class InputIterator, class OutputIterator>
	typename std::enable_if_t<!(Is_Contiguous<InputIterator>::value&& Is_Contiguous<OutputIterator>::value&& Is_Same_Value<InputIterator, OutputIterator>::value),
	OutputIterator> copy(InputIterator first, InputIterator last, OutputIterator result) {
		while (first != last) {
			*result = *first;
			++result; ++first;
		}
		return result;
	};

};