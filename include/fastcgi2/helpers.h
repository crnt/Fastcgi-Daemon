#ifndef _FASTCGI_HELPERS_H_
#define _FASTCGI_HELPERS_H_

#include <cassert>
#include <algorithm>

namespace fastcgi
{

template<typename Type, typename Clean>
class Helper
{
public:
	Helper() throw ();
	explicit Helper(Type tptr) throw ();
	
	Helper(const Helper<Type, Clean> &h) throw ();
	Helper<Type, Clean>& operator = (const Helper<Type, Clean> &h) throw ();
	
	~Helper() throw ();

	Type get() const throw ();
	Type operator -> () const throw ();
	
	Type release() throw ();
	void reset(Type tptr) throw ();

private:
	Type releaseInternal() const throw ();

private:
	mutable Type tptr_;
};

template<typename Type, typename Clean>
Helper<Type, Clean>::Helper() throw () :
	tptr_(NULL)
{
}

template<typename Type, typename Clean>
Helper<Type, Clean>::Helper(Type tptr) throw () :
	tptr_(tptr)
{
}

template<typename Type, typename Clean>
Helper<Type, Clean>::Helper(const Helper<Type, Clean> &h) throw () :
	tptr_(NULL)
{
	std::swap(tptr_, h.tptr_);
	assert(NULL == h.get());
}

template<typename Type, typename Clean> Helper<Type, Clean>&
Helper<Type, Clean>::operator = (const Helper<Type, Clean> &h) throw () {
	if (&h != this) {
		reset(h.releaseInternal());
		assert(NULL == h.get());
	}
	return *this;
}

template<typename Type, typename Clean> inline
Helper<Type, Clean>::~Helper() throw () {
	reset(NULL);
}

template<typename Type, typename Clean> Type
Helper<Type, Clean>::get() const throw () {
	return tptr_;
}

template<typename Type, typename Clean> Type
Helper<Type, Clean>::operator -> () const throw () {
	assert(NULL != tptr_);
	return tptr_;
}

template<typename Type, typename Clean> Type
Helper<Type, Clean>::release() throw () {
	return releaseInternal();
}

template<typename Type, typename Clean> void
Helper<Type, Clean>::reset(Type tptr) throw () {
	if (NULL != tptr_) {
		Clean::clean(tptr_);
	}
	tptr_ = tptr;
}

template<typename Type, typename Clean> Type
Helper<Type, Clean>::releaseInternal() const throw () {
	Type ptr = NULL;
	std::swap(ptr, tptr_);
	return ptr;
}

} // namespace fastcgi

#endif // _FASTCGI_HELPERS_H_
