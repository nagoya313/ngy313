#ifndef NGY313_PLATFORM_HPP_
#define NGY313_PLATFORM_HPP_

#if defined(_WIN32)
#if !(defined(_MSC_VER) && (_MSC_VER >= 1600))
#error It is a compiler of non-correspondence.
#endif
#define _WIN32_DCOM
#define _WIN32_WINNT 0x501
#define NOMINMAX
#elif defined(__linux__)
#if !(defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 6))
#error It is a compiler of non-correspondence.
#endif
#else
#error It is an environment that does not correspond.
#endif

#endif

