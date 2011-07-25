#ifndef NGY313_SCOPED_HANDLE_
#define NGY313_SCOPED_HANDLE_

#include <tuple>
#include <utility>
#include <boost/config.hpp>
#include <boost/call_traits.hpp>
#include <boost/operators.hpp>

namespace ngy313 {
template <typename T>
struct default_delete {
	BOOST_CONSTEXPR default_delete() = default;

  void operator ()(typename boost::call_traits<T>::param_type t) const {}

  BOOST_CONSTEXPR T null_value() const {
  	return T();
  }

  BOOST_CONSTEXPR bool null_check(
      typename boost::call_traits<T>::param_type t) const {
   	return true;
  }
};

template <typename T, typename Deleter>
class scoped_handle : boost::equality_comparable<scoped_handle<T, Deleter>>,
                      boost::less_than_comparable<scoped_handle<T, Deleter>> {
 public:
	typedef T handle;

	BOOST_CONSTEXPR scoped_handle() : data_(T(), default_delete<T>()) {}

  explicit scoped_handle(typename boost::call_traits<T>::param_type t)
      : data_(t, Deleter()) {}

  explicit scoped_handle(typename boost::call_traits<T>::param_type t,
  		                    const Deleter &deleter)
      : data_(t, deleter) {}

  ~scoped_handle() {
  	reset(std::get<1>(data_).null_value());
  }

  scoped_handle(scoped_handle &&rhs)
      : data_(rhs.release(), std::forward<Deleter>(rhs.get_deleter())) {
    swap(rhs);
  }

  scoped_handle &operator=(scoped_handle &&rhs) { 
    reset(rhs.release());
    get_deleter() = std::forward<Deleter>(rhs.get_deleter());
    return *this;
  }

  T release() {
  	const T t = get();
  	std::get<0>(data_) = std::get<1>(data_).null_value();
  	return t;
  }

  void reset(typename boost::call_traits<T>::param_type t) {
  	std::swap(std::get<0>(data_), t);
  	if (std::get<1>(data_).null_check(t)) {
  	  get_deleter()(t);
  	}
  }

  void swap(scoped_handle &rhs) {
    std::swap(data_, rhs.data_);
  }

  T get() const {
    return std::get<0>(data_);
  }

  Deleter &get_deleter() {
    return std::get<1>(data_);
  }

  const Deleter &get_deleter() const {
  	return std::get<1>(data_);
  }

  explicit operator bool() const {
  	return !get_deleter().null_check(get());
  }

  scoped_handle(const scoped_handle &) = delete;
  scoped_handle &operator=(const scoped_handle &) = delete;

 private:
  std::tuple<T, Deleter> data_;
};

template <typename T,
          typename Deleter,
          typename Handle = ngy313::scoped_handle<T, Deleter>>
bool operator ==(const Handle &lhs, const Handle &rhs) {
	return lhs.get() == rhs.get();
}

template <typename T,
          typename Deleter,
          typename Handle = ngy313::scoped_handle<T, Deleter>>
bool operator <(const Handle &lhs, const Handle &rhs) {
	return lhs.get() < rhs.get();
}
}

namespace std {
template <typename T,
          typename Deleter,
          typename Handle = ngy313::scoped_handle<T, Deleter>>
void swap(Handle &lhs, Handle &rhs) {
  lhs.swap(rhs);
}

template<typename T, typename Deleter>
struct hash<ngy313::scoped_handle<T, Deleter>>
    : std::unary_function<ngy313::scoped_handle<T, Deleter>, size_t> {

	size_t operator()(const ngy313::scoped_handle<T, Deleter>& h) const {
	  return std::hash<typename ngy313::scoped_handle<
	  		                  T,
	  		                  Deleter>::handle>()(h.get());
  }
};
}

#endif
