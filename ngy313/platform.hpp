#ifndef NGY313_PLATFORM_HPP_
#define NGY313_PLATFORM_HPP_

#ifdef _WIN32
#define NGY313_WINDOWS
#endif

#ifdef NGY313_WINDOWS
#if defined(_MSC_VER) && (_MSC_VER >=1600)
#define NGY313_MSVC
#else
#error It is a compiler of non-correspondence.
#endif
#endif

#if defined(NGY313_WINDOWS) && defined(NGY313_MSVC)
#define NGY313_WINDOWS_VERSION
#endif

#ifdef __linux__
#define NGY313_LINUX
#endif

#ifdef NGY313_LINUX
#if defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 5)
#define NGY313_GCC
#else
#error It is a compiler of non-correspondence.
#endif
#endif

#if defined(NGY313_LINUX) && defined(NGY313_GCC)
#define NGY313_LINUX_VERSION
#endif

#endif

