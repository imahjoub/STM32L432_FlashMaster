///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>

class shape
{
public:
  virtual ~shape() = default;

  virtual auto draw() noexcept -> bool = 0;

protected:
  shape() = default;
};

class circle : public shape
{
public:
  circle() = default;
  ~circle() override = default;

  auto draw() noexcept -> bool { return true; }
};

static circle my_circle;

extern "C" auto AppShape_CheckCircle(void) -> bool;

auto AppShape_CheckCircle(void) -> bool
{
  return my_circle.draw();
}

// Put all of the following patches into some kind of a
// "patch.cpp" file in the same place as the startup code.
extern "C"
{
  // Patched functions.
  void        __cxa_pure_virtual  (void);
  char*       __cxa_demangle      (const char*, char*, size_t*, int*);

  void        __cxa_pure_virtual  (void)                              { }
  char*       __cxa_demangle      (const char*, char*, size_t*, int*) { return nullptr; }
}

void operator delete(void*) noexcept;
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept;
#endif

void operator delete(void*) noexcept { }
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept { }
#endif
