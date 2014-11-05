//=============================================================================
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//=============================================================================

#ifndef RAPTOR_ENABLE_REFCOUNT_HPP
#define RAPTOR_ENABLE_REFCOUNT_HPP

#include <boost/intrusive_ptr.hpp>
#include <boost/detail/atomic_count.hpp>

namespace raptor
{

  /// General purpose intrusive reference counting for objects.
  /**
   * \tparam Derived CRTP Idiom
   */
  template < typename Derived >
  class enable_refcount
  {
  public:
    typedef boost::intrusive_ptr < Derived > pointer;
    typedef boost::intrusive_ptr < Derived const > const_pointer;

    friend void intrusive_ptr_add_ref ( Derived const* p )
    {
      ++p->refcount_;
    }

    friend void intrusive_ptr_release ( Derived const* p )
    {
      if ( --p->refcount_ == 0 )
      {
        delete p;
      }
    }

  protected:
    enable_refcount() : refcount_ ( 0 ) {}
    enable_refcount ( enable_refcount const& ) : refcount_ ( 0 ) {}
    enable_refcount& operator = ( enable_refcount const& ) { return *this; }
    ~enable_refcount() {}
    void swap ( enable_refcount& ) {}

    pointer self()
    { return pointer ( static_cast < Derived* > ( this ) ); }

    const_pointer self() const
    { return const_pointer ( static_cast < Derived const* > ( this ) ); }

  private:
    mutable boost::detail::atomic_count refcount_;
  };

}

#endif

