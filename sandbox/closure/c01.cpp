       
typedef int ptrdiff_t;
typedef unsigned int size_t;
namespace std {
  using ::ptrdiff_t;
  using ::size_t;
}
       
namespace std {
  namespace rel_ops
  {
    template <class _Tp>
      inline bool
      operator!=(const _Tp& __x, const _Tp& __y)
      { return !(__x == __y); }
    template <class _Tp>
      inline bool
      operator>(const _Tp& __x, const _Tp& __y)
      { return __y < __x; }
    template <class _Tp>
      inline bool
      operator<=(const _Tp& __x, const _Tp& __y)
      { return !(__y < __x); }
    template <class _Tp>
      inline bool
      operator>=(const _Tp& __x, const _Tp& __y)
      { return !(__x < __y); }
  }
}
       


       
namespace std {
  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)
    {
     
      _Tp __tmp = (__a);
      __a = (__b);
      __b = (__tmp);
    }
  template<typename _Tp, size_t _Nm>
    inline void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])
    {
      for (size_t __n = 0; __n < _Nm; ++__n)
 swap(__a[__n], __b[__n]);
    }
}
namespace std {
  template<class _T1, class _T2>
    struct pair
    {
      typedef _T1 first_type;
      typedef _T2 second_type;
      _T1 first;
      _T2 second;
      pair()
      : first(), second() { }
      pair(const _T1& __a, const _T2& __b)
      : first(__a), second(__b) { }
      template<class _U1, class _U2>
        pair(const pair<_U1, _U2>& __p)
 : first(__p.first),
   second(__p.second) { }
    };
  template<class _T1, class _T2>
    inline bool
    operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first == __y.first && __x.second == __y.second; }
  template<class _T1, class _T2>
    inline bool
    operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first < __y.first
      || (!(__y.first < __x.first) && __x.second < __y.second); }
  template<class _T1, class _T2>
    inline bool
    operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y); }
  template<class _T1, class _T2>
    inline bool
    operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x; }
  template<class _T1, class _T2>
    inline bool
    operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x); }
  template<class _T1, class _T2>
    inline bool
    operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y); }
  template<class _T1, class _T2>
    inline pair<_T1, _T2>
    make_pair(_T1 __x, _T2 __y)
    { return pair<_T1, _T2>(__x, __y); }
}
extern "C" {
extern "C" {
}
extern "C" {
}
extern "C" {
typedef signed char __int8_t ;
typedef unsigned char __uint8_t ;
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;

}
typedef void *_LOCK_T;
extern "C"
{
void __cygwin_lock_init(_LOCK_T *);
void __cygwin_lock_init_recursive(_LOCK_T *);
void __cygwin_lock_fini(_LOCK_T *);
void __cygwin_lock_lock(_LOCK_T *);
int __cygwin_lock_trylock(_LOCK_T *);
void __cygwin_lock_unlock(_LOCK_T *);
}
typedef long _off_t;
typedef short __dev_t;
typedef unsigned short __uid_t;
typedef unsigned short __gid_t;
__extension__ typedef long long _off64_t;
typedef long _fpos_t;
typedef _off64_t _fpos64_t;
typedef int _ssize_t;
typedef unsigned int wint_t;
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;
typedef _LOCK_T _flock_t;
typedef void *_iconv_t;
typedef long int __off_t;
typedef int __pid_t;
__extension__ typedef long long int __loff_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long clock_t;
typedef long time_t;
struct timespec {
  time_t tv_sec;
  long tv_nsec;
};
struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};
typedef long daddr_t;
typedef char * caddr_t;

typedef int pid_t;
typedef _ssize_t ssize_t;
typedef unsigned short nlink_t;
typedef long fd_mask;
typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
typedef unsigned long clockid_t;
typedef unsigned long timer_t;
typedef unsigned long useconds_t;
typedef long suseconds_t;
extern "C"
{
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long uint_least64_t;
typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef int intptr_t;
typedef unsigned int uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
extern "C" {
static __inline unsigned short
bswap_16 (unsigned short __x)
{
  return (__x >> 8) | (__x << 8);
}
static __inline unsigned int
bswap_32 (unsigned int __x)
{
  return (bswap_16 (__x & 0xffff) << 16) | (bswap_16 (__x >> 16));
}
static __inline unsigned long long
bswap_64 (unsigned long long __x)
{
  return (((unsigned long long) bswap_32 (__x & 0xffffffffull)) << 32) | (bswap_32 (__x >> 32));
}
}
typedef struct timespec timespec_t;
typedef struct timespec timestruc_t;
typedef _off64_t off_t;
typedef __loff_t loff_t;
typedef short __dev16_t;
typedef unsigned long __dev32_t;
typedef __dev32_t dev_t;
typedef long blksize_t;
typedef long __blkcnt32_t;
typedef long long __blkcnt64_t;
typedef __blkcnt64_t blkcnt_t;
typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;
typedef unsigned short __uid16_t;
typedef unsigned long __uid32_t;
typedef __uid32_t uid_t;
typedef unsigned short __gid16_t;
typedef unsigned long __gid32_t;
typedef __gid32_t gid_t;
typedef unsigned long __ino32_t;
typedef unsigned long long __ino64_t;
typedef __ino64_t ino_t;
typedef unsigned long id_t;
struct flock {
 short l_type;
 short l_whence;
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
};
typedef long long key_t;
typedef unsigned long vm_offset_t;
typedef unsigned long vm_size_t;
typedef void *vm_object_t;
typedef unsigned char u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
typedef __int32_t register_t;
typedef char *addr_t;
typedef unsigned mode_t;
typedef struct __pthread_t {char __dummy;} *pthread_t;
typedef struct __pthread_mutex_t {char __dummy;} *pthread_mutex_t;
typedef struct __pthread_key_t {char __dummy;} *pthread_key_t;
typedef struct __pthread_attr_t {char __dummy;} *pthread_attr_t;
typedef struct __pthread_mutexattr_t {char __dummy;} *pthread_mutexattr_t;
typedef struct __pthread_condattr_t {char __dummy;} *pthread_condattr_t;
typedef struct __pthread_cond_t {char __dummy;} *pthread_cond_t;
typedef struct
{
  pthread_mutex_t mutex;
  int state;
}
pthread_once_t;
typedef struct __pthread_rwlock_t {char __dummy;} *pthread_rwlock_t;
typedef struct __pthread_rwlockattr_t {char __dummy;} *pthread_rwlockattr_t;
}
extern char **environ;
void __attribute__((__cdecl__)) _exit (int __status ) __attribute__ ((noreturn));
int __attribute__((__cdecl__)) access (const char *__path, int __amode );
unsigned __attribute__((__cdecl__)) alarm (unsigned __secs );
int __attribute__((__cdecl__)) chdir (const char *__path );
int __attribute__((__cdecl__)) chmod (const char *__path, mode_t __mode );
int __attribute__((__cdecl__)) chown (const char *__path, uid_t __owner, gid_t __group );
int __attribute__((__cdecl__)) chroot (const char *__path );
int __attribute__((__cdecl__)) close (int __fildes );
size_t __attribute__((__cdecl__)) confstr (int __name, char *__buf, size_t __len);
char * __attribute__((__cdecl__)) ctermid (char *__s );
char * __attribute__((__cdecl__)) cuserid (char *__s );
int __attribute__((__cdecl__)) daemon (int nochdir, int noclose);
int __attribute__((__cdecl__)) dup (int __fildes );
int __attribute__((__cdecl__)) dup2 (int __fildes, int __fildes2 );
int __attribute__((__cdecl__)) dup3 (int __fildes, int __fildes2, int flags);
int __attribute__((__cdecl__)) eaccess (const char *__path, int __mode);
void __attribute__((__cdecl__)) endusershell (void);
int __attribute__((__cdecl__)) euidaccess (const char *__path, int __mode);
int __attribute__((__cdecl__)) execl (const char *__path, const char *, ... );
int __attribute__((__cdecl__)) execle (const char *__path, const char *, ... );
int __attribute__((__cdecl__)) execlp (const char *__file, const char *, ... );
int __attribute__((__cdecl__)) execv (const char *__path, char * const __argv[] );
int __attribute__((__cdecl__)) execve (const char *__path, char * const __argv[], char * const __envp[] );
int __attribute__((__cdecl__)) execvp (const char *__file, char * const __argv[] );
int __attribute__((__cdecl__)) execvpe (const char *__file, char * const __argv[], char * const __envp[] );
int __attribute__((__cdecl__)) faccessat (int __dirfd, const char *__path, int __mode, int __flags);
int __attribute__((__cdecl__)) fchdir (int __fildes);
int __attribute__((__cdecl__)) fchmod (int __fildes, mode_t __mode );
int __attribute__((__cdecl__)) fchown (int __fildes, uid_t __owner, gid_t __group );
int __attribute__((__cdecl__)) fchownat (int __dirfd, const char *__path, uid_t __owner, gid_t __group, int __flags);
int __attribute__((__cdecl__)) fexecve (int __fd, char * const __argv[], char * const __envp[] );
pid_t __attribute__((__cdecl__)) fork (void );
long __attribute__((__cdecl__)) fpathconf (int __fd, int __name );
int __attribute__((__cdecl__)) fsync (int __fd);
int __attribute__((__cdecl__)) fdatasync (int __fd);
char * __attribute__((__cdecl__)) getcwd (char *__buf, size_t __size );
int __attribute__((__cdecl__)) getdomainname (char *__name, size_t __len);
gid_t __attribute__((__cdecl__)) getegid (void );
uid_t __attribute__((__cdecl__)) geteuid (void );
gid_t __attribute__((__cdecl__)) getgid (void );
int __attribute__((__cdecl__)) getgroups (int __gidsetsize, gid_t __grouplist[] );
long __attribute__((__cdecl__)) gethostid (void);
char * __attribute__((__cdecl__)) getlogin (void );
int __attribute__((__cdecl__)) getlogin_r (char *name, size_t namesize);
char * __attribute__((__cdecl__)) getpass (const char *__prompt);
int __attribute__((__cdecl__)) getpagesize (void);
int __attribute__((__cdecl__)) getpeereid (int, uid_t *, gid_t *);
pid_t __attribute__((__cdecl__)) getpgid (pid_t);
pid_t __attribute__((__cdecl__)) getpgrp (void );
pid_t __attribute__((__cdecl__)) getpid (void );
pid_t __attribute__((__cdecl__)) getppid (void );
pid_t __attribute__((__cdecl__)) getsid (pid_t);
uid_t __attribute__((__cdecl__)) getuid (void );
char * __attribute__((__cdecl__)) getusershell (void);
char * __attribute__((__cdecl__)) getwd (char *__buf );
int __attribute__((__cdecl__)) iruserok (unsigned long raddr, int superuser, const char *ruser, const char *luser);
int __attribute__((__cdecl__)) isatty (int __fildes );
int __attribute__((__cdecl__)) lchown (const char *__path, uid_t __owner, gid_t __group );
int __attribute__((__cdecl__)) link (const char *__path1, const char *__path2 );
int __attribute__((__cdecl__)) linkat (int __dirfd1, const char *__path1, int __dirfd2, const char *__path2, int __flags );
int __attribute__((__cdecl__)) nice (int __nice_value );
off_t __attribute__((__cdecl__)) lseek (int __fildes, off_t __offset, int __whence );
int __attribute__((__cdecl__)) lockf (int __fd, int __cmd, off_t __len);
long __attribute__((__cdecl__)) pathconf (const char *__path, int __name );
int __attribute__((__cdecl__)) pause (void );
int __attribute__((__cdecl__)) pthread_atfork (void (*)(void), void (*)(void), void (*)(void));
int __attribute__((__cdecl__)) pipe (int __fildes[2] );
int __attribute__((__cdecl__)) pipe2 (int __fildes[2], int flags);
ssize_t __attribute__((__cdecl__)) pread (int __fd, void *__buf, size_t __nbytes, off_t __offset);
ssize_t __attribute__((__cdecl__)) pwrite (int __fd, const void *__buf, size_t __nbytes, off_t __offset);
_ssize_t __attribute__((__cdecl__)) read (int __fd, void *__buf, size_t __nbyte );
int __attribute__((__cdecl__)) rresvport (int *__alport);
int __attribute__((__cdecl__)) revoke (char *__path);
int __attribute__((__cdecl__)) rmdir (const char *__path );
int __attribute__((__cdecl__)) ruserok (const char *rhost, int superuser, const char *ruser, const char *luser);
void * __attribute__((__cdecl__)) sbrk (ptrdiff_t __incr);
int __attribute__((__cdecl__)) setegid (gid_t __gid );
int __attribute__((__cdecl__)) seteuid (uid_t __uid );
int __attribute__((__cdecl__)) setgid (gid_t __gid );
int __attribute__((__cdecl__)) setgroups (int ngroups, const gid_t *grouplist );
int __attribute__((__cdecl__)) setpgid (pid_t __pid, pid_t __pgid );
int __attribute__((__cdecl__)) setpgrp (void );
int __attribute__((__cdecl__)) setregid (gid_t __rgid, gid_t __egid);
int __attribute__((__cdecl__)) setreuid (uid_t __ruid, uid_t __euid);
pid_t __attribute__((__cdecl__)) setsid (void );
int __attribute__((__cdecl__)) setuid (uid_t __uid );
void __attribute__((__cdecl__)) setusershell (void);
unsigned __attribute__((__cdecl__)) sleep (unsigned int __seconds );
void __attribute__((__cdecl__)) swab (const void *, void *, ssize_t);
long __attribute__((__cdecl__)) sysconf (int __name );
pid_t __attribute__((__cdecl__)) tcgetpgrp (int __fildes );
int __attribute__((__cdecl__)) tcsetpgrp (int __fildes, pid_t __pgrp_id );
char * __attribute__((__cdecl__)) ttyname (int __fildes );
int __attribute__((__cdecl__)) ttyname_r (int, char *, size_t);
int __attribute__((__cdecl__)) unlink (const char *__path );
int __attribute__((__cdecl__)) usleep (useconds_t __useconds);
int __attribute__((__cdecl__)) vhangup (void );
_ssize_t __attribute__((__cdecl__)) write (int __fd, const void *__buf, size_t __nbyte );
extern "C" {
extern int __attribute__((dllimport)) opterr;
extern int __attribute__((dllimport)) optind;
extern int __attribute__((dllimport)) optopt;
extern int __attribute__((dllimport)) optreset;
extern char __attribute__((dllimport)) *optarg;
int getopt (int, char * const *, const char *);
}
pid_t __attribute__((__cdecl__)) vfork (void );
int __attribute__((__cdecl__)) ftruncate (int __fd, off_t __length);
int __attribute__((__cdecl__)) truncate (const char *, off_t __length);
int __attribute__((__cdecl__)) getdtablesize (void);
int __attribute__((__cdecl__)) setdtablesize (int);
useconds_t __attribute__((__cdecl__)) ualarm (useconds_t __useconds, useconds_t __interval);
 int __attribute__((__cdecl__)) gethostname (char *__name, size_t __len);
char * __attribute__((__cdecl__)) mktemp (char *);
void __attribute__((__cdecl__)) sync (void);
ssize_t __attribute__((__cdecl__)) readlink (const char *__path, char *__buf, size_t __buflen);
ssize_t __attribute__((__cdecl__)) readlinkat (int __dirfd1, const char *__path, char *__buf, size_t __buflen);
int __attribute__((__cdecl__)) symlink (const char *__name1, const char *__name2);
int __attribute__((__cdecl__)) symlinkat (const char *, int, const char *);
int __attribute__((__cdecl__)) unlinkat (int, const char *, int);
}
       
namespace boost{
   __extension__ typedef long long long_long_type;
   __extension__ typedef unsigned long long ulong_long_type;
}
namespace mpl_ { namespace aux {} }
namespace boost { namespace mpl { using namespace mpl_;
namespace aux { using namespace mpl_::aux; }
}}
namespace mpl_ {
template< int N > struct int_;
}
namespace boost { namespace mpl { using ::mpl_::int_; } }
namespace mpl_ {
struct integral_c_tag { static const int value = 0; };
}
namespace boost { namespace mpl { using ::mpl_::integral_c_tag; } }
namespace mpl_ {
template< int N >
struct int_
{
    static const int value = N;
    typedef int_ type;
    typedef int value_type;
    typedef integral_c_tag tag;
    typedef mpl_::int_< static_cast<int>((value + 1)) > next;
    typedef mpl_::int_< static_cast<int>((value - 1)) > prior;
    operator int() const { return static_cast<int>(this->value); }
};
template< int N >
int const mpl_::int_< N >::value;
}
namespace boost { namespace mpl { namespace aux {
template< typename F > struct template_arity;
}}}
namespace mpl_ {
template< bool C_ > struct bool_;
typedef bool_<true> true_;
typedef bool_<false> false_;
}
namespace boost { namespace mpl { using ::mpl_::bool_; } }
namespace boost { namespace mpl { using ::mpl_::true_; } }
namespace boost { namespace mpl { using ::mpl_::false_; } }
namespace mpl_ {
template< bool C_ > struct bool_
{
    static const bool value = C_;
    typedef integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};
template< bool C_ >
bool const bool_<C_>::value;
}
namespace mpl_ {
template< typename T, T N > struct integral_c;
}
namespace boost { namespace mpl { using ::mpl_::integral_c; } }
namespace mpl_ {
template< typename T, T N >
struct integral_c
{
    static const T value = N;
    typedef integral_c type;
    typedef T value_type;
    typedef integral_c_tag tag;
    typedef integral_c< T, static_cast<T>((value + 1)) > next;
    typedef integral_c< T, static_cast<T>((value - 1)) > prior;
    operator T() const { return static_cast<T>(this->value); }
};
template< typename T, T N >
T const integral_c< T, N >::value;
}
namespace mpl_ {
template< bool C >
struct integral_c<bool, C>
{
    static const bool value = C;
    typedef integral_c_tag tag;
    typedef integral_c type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};
}
namespace boost{
template <class T, T val>
struct integral_constant : public mpl::integral_c<T, val>
{
   typedef integral_constant<T,val> type;
};
template<> struct integral_constant<bool,true> : public mpl::true_
{
   typedef integral_constant<bool,true> type;
};
template<> struct integral_constant<bool,false> : public mpl::false_
{
   typedef integral_constant<bool,false> type;
};
typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;
}
namespace boost {
template< typename T > struct is_lvalue_reference : public ::boost::integral_constant<bool,false> { public: };
template< typename T > struct is_lvalue_reference< T& > : public ::boost::integral_constant<bool,true> { public: };
}
namespace boost {
template< typename T > struct is_rvalue_reference : public ::boost::integral_constant<bool,false> { public: };
}
namespace boost {
namespace type_traits {
typedef char yes_type;
struct no_type
{
   char padding[8];
};
}
}
namespace boost {
namespace type_traits {
template <bool b1, bool b2, bool b3 = false, bool b4 = false, bool b5 = false, bool b6 = false, bool b7 = false>
struct ice_or;
template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_or
{
    static const bool value = true;
};
template <>
struct ice_or<false, false, false, false, false, false, false>
{
    static const bool value = false;
};
}
}
namespace boost {
namespace type_traits {
template <bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true, bool b6 = true, bool b7 = true>
struct ice_and;
template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_and
{
    static const bool value = false;
};
template <>
struct ice_and<true, true, true, true, true, true, true>
{
    static const bool value = true;
};
}
}
namespace boost {
namespace type_traits {
template <bool b>
struct ice_not
{
    static const bool value = true;
};
template <>
struct ice_not<true>
{
    static const bool value = false;
};
}
}
namespace boost {
namespace type_traits {
template <int b1, int b2>
struct ice_eq
{
    static const bool value = (b1 == b2);
};
template <int b1, int b2>
struct ice_ne
{
    static const bool value = (b1 != b2);
};
template <int b1, int b2> bool const ice_eq<b1,b2>::value;
template <int b1, int b2> bool const ice_ne<b1,b2>::value;
}
}
namespace boost {
namespace detail {
template <typename T>
struct is_reference_impl
{
   static const bool value = (::boost::type_traits::ice_or< ::boost::is_lvalue_reference<T>::value, ::boost::is_rvalue_reference<T>::value >::value);
};
}
template< typename T > struct is_reference : public ::boost::integral_constant<bool,::boost::detail::is_reference_impl<T>::value> { public: };
}
namespace boost {
namespace type_traits {
struct false_result
{
    template <typename T> struct result_
    {
        static const bool value = false;
    };
};
}}
namespace boost {
namespace type_traits {
template <class R>
struct is_function_ptr_helper
{
    static const bool value = false;
};
template <class R >
struct is_function_ptr_helper<R (*)()> { static const bool value = true; };
template <class R >
struct is_function_ptr_helper<R (*)( ...)> { static const bool value = true; };
template <class R , class T0>
struct is_function_ptr_helper<R (*)( T0)> { static const bool value = true; };
template <class R , class T0>
struct is_function_ptr_helper<R (*)( T0 ...)> { static const bool value = true; };
template <class R , class T0 , class T1>
struct is_function_ptr_helper<R (*)( T0 , T1)> { static const bool value = true; };
template <class R , class T0 , class T1>
struct is_function_ptr_helper<R (*)( T0 , T1 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24)> { static const bool value = true; };
template <class R , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_function_ptr_helper<R (*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...)> { static const bool value = true; };
}
}
namespace boost {
namespace detail {
template<bool is_ref = true>
struct is_function_chooser
    : public ::boost::type_traits::false_result
{
};
template <>
struct is_function_chooser<false>
{
    template< typename T > struct result_
        : public ::boost::type_traits::is_function_ptr_helper<T*>
    {
    };
};
template <typename T>
struct is_function_impl
    : public is_function_chooser< ::boost::is_reference<T>::value >
        ::template result_<T>
{
};
}
template< typename T > struct is_function : public ::boost::integral_constant<bool,::boost::detail::is_function_impl<T>::value> { public: };
}
namespace boost
{
  template <bool B, class T = void>
  struct enable_if_c {
    typedef T type;
  };
  template <class T>
  struct enable_if_c<false, T> {};
  template <class Cond, class T = void>
  struct enable_if : public enable_if_c<Cond::value, T> {};
  template <bool B, class T>
  struct lazy_enable_if_c {
    typedef typename T::type type;
  };
  template <class T>
  struct lazy_enable_if_c<false, T> {};
  template <class Cond, class T>
  struct lazy_enable_if : public lazy_enable_if_c<Cond::value, T> {};
  template <bool B, class T = void>
  struct disable_if_c {
    typedef T type;
  };
  template <class T>
  struct disable_if_c<true, T> {};
  template <class Cond, class T = void>
  struct disable_if : public disable_if_c<Cond::value, T> {};
  template <bool B, class T>
  struct lazy_disable_if_c {
    typedef typename T::type type;
  };
  template <class T>
  struct lazy_disable_if_c<true, T> {};
  template <class Cond, class T>
  struct lazy_disable_if : public lazy_disable_if_c<Cond::value, T> {};
}
namespace boost { namespace type_of {
    template<typename T>
        typename enable_if<is_function<T>, T&>::type
        ensure_obj(T&);
    template<typename T>
        typename disable_if<is_function<T>, T&>::type
        ensure_obj(const T&);
}}
namespace boost { namespace scope_exit { namespace aux {
    template<int Dummy = 0>
    struct declared
    {
        void* value;
        static int const cmp2 = 0;
        friend void operator>(int, declared const&) {}
    };
    struct undeclared { declared<> dummy[2]; };
    template<int> struct resolve;
    template<>
    struct resolve<sizeof(declared<>)>
    {
        static const int cmp1 = 0;
    };
    template<>
    struct resolve<sizeof(undeclared)>
    {
        template<int>
        struct cmp1
        {
            static int const cmp2 = 0;
        };
    };
} } }
extern boost::scope_exit::aux::undeclared boost_scope_exit_args;
namespace boost { namespace scope_exit { namespace aux {
typedef void (*ref_tag)(int&);
typedef void (*val_tag)(int );
template<class T, class Tag> struct member;
template<class T>
struct member<T,ref_tag>
{
    T& value;
};
template<class T>
struct member<T,val_tag>
{
    T value;
};
template<class T> inline T& deref(T* p, ref_tag) { return *p; }
template<class T> inline T& deref(T& r, val_tag) { return r; }
template<class T>
struct wrapper
{
    typedef T type;
};
template<class T> wrapper<T> wrap(T&);
} } }

namespace boost {
template< typename T > struct remove_pointer { public: typedef T type; };
template< typename T > struct remove_pointer<T*> { public: typedef T type; };
template< typename T > struct remove_pointer<T* const> { public: typedef T type; };
template< typename T > struct remove_pointer<T* volatile> { public: typedef T type; };
template< typename T > struct remove_pointer<T* const volatile> { public: typedef T type; };
}













namespace boost {
namespace detail{
template <class T>
struct remove_rvalue_ref
{
   typedef T type;
};
}
template< typename T > struct remove_reference { public: typedef typename boost::detail::remove_rvalue_ref<T>::type type; };
template< typename T > struct remove_reference<T&> { public: typedef T type; };
}
namespace boost {
namespace detail {
template <typename T>
struct add_pointer_impl
{
    typedef typename remove_reference<T>::type no_ref_type;
    typedef no_ref_type* type;
};
}
template< typename T > struct add_pointer { public: typedef typename boost::detail::add_pointer_impl<T>::type type; };
}
namespace boost {
namespace detail {
template<typename Function> struct function_traits_helper;
template<typename R>
struct function_traits_helper<R (*)(void)>
{
  static const unsigned arity = 0;
  typedef R result_type;
};
template<typename R, typename T1>
struct function_traits_helper<R (*)(T1)>
{
  static const unsigned arity = 1;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T1 argument_type;
};
template<typename R, typename T1, typename T2>
struct function_traits_helper<R (*)(T1, T2)>
{
  static const unsigned arity = 2;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
};
template<typename R, typename T1, typename T2, typename T3>
struct function_traits_helper<R (*)(T1, T2, T3)>
{
  static const unsigned arity = 3;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4>
struct function_traits_helper<R (*)(T1, T2, T3, T4)>
{
  static const unsigned arity = 4;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5)>
{
  static const unsigned arity = 5;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6)>
{
  static const unsigned arity = 6;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7)>
{
  static const unsigned arity = 7;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8)>
{
  static const unsigned arity = 8;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
{
  static const unsigned arity = 9;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
};
template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9,
         typename T10>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
{
  static const unsigned arity = 10;
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
  typedef T10 arg10_type;
};
}
template<typename Function>
struct function_traits :
  public boost::detail::function_traits_helper<typename boost::add_pointer<Function>::type>
{
};
}
       
namespace boost {
template< typename T > struct is_integral : public ::boost::integral_constant<bool,false> { public: };
template<> struct is_integral< unsigned char > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned char const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned char volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned char const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< unsigned short > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned short const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned short volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned short const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< unsigned int > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned int const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned int volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned int const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< unsigned long > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned long const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned long volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< unsigned long const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< signed char > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed char const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed char volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed char const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< signed short > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed short const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed short volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed short const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< signed int > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed int const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed int volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed int const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< signed long > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed long const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed long volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< signed long const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< bool > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< bool const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< bool volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< bool const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< char > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< char const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< char volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< char const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< wchar_t > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< wchar_t const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< wchar_t volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< wchar_t const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< ::boost::ulong_long_type > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::ulong_long_type const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::ulong_long_type volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::ulong_long_type const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_integral< ::boost::long_long_type > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::long_long_type const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::long_long_type volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_integral< ::boost::long_long_type const volatile > : public ::boost::integral_constant<bool,true> { public: };
}
namespace boost {
template< typename T > struct is_float : public ::boost::integral_constant<bool,false> { public: };
template<> struct is_float< float > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< float const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< float volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< float const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_float< double > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< double const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< double volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< double const volatile > : public ::boost::integral_constant<bool,true> { public: };
template<> struct is_float< long double > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< long double const > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< long double volatile > : public ::boost::integral_constant<bool,true> { public: }; template<> struct is_float< long double const volatile > : public ::boost::integral_constant<bool,true> { public: };
}
namespace boost {
namespace detail {
template< typename T >
struct is_arithmetic_impl
{
    static const bool value = (::boost::type_traits::ice_or< ::boost::is_integral<T>::value, ::boost::is_float<T>::value >::value);
};
}
template< typename T > struct is_arithmetic : public ::boost::integral_constant<bool,::boost::detail::is_arithmetic_impl<T>::value> { public: };
}
namespace boost {
template< typename T, typename U > struct is_same : public ::boost::integral_constant<bool,false> { public: };
template< typename T > struct is_same< T,T > : public ::boost::integral_constant<bool,true> { public: };
}
namespace boost {
namespace detail {
template <typename T> struct cv_traits_imp {};
template <typename T>
struct cv_traits_imp<T*>
{
    static const bool is_const = false;
    static const bool is_volatile = false;
    typedef T unqualified_type;
};
template <typename T>
struct cv_traits_imp<const T*>
{
    static const bool is_const = true;
    static const bool is_volatile = false;
    typedef T unqualified_type;
};
template <typename T>
struct cv_traits_imp<volatile T*>
{
    static const bool is_const = false;
    static const bool is_volatile = true;
    typedef T unqualified_type;
};
template <typename T>
struct cv_traits_imp<const volatile T*>
{
    static const bool is_const = true;
    static const bool is_volatile = true;
    typedef T unqualified_type;
};
}
}
namespace boost {
namespace detail{
template <class T>
struct is_volatile_rval_filter
{
   static const bool value = ::boost::detail::cv_traits_imp<T*>::is_volatile;
};
}
template< typename T > struct is_volatile : public ::boost::integral_constant<bool,::boost::detail::is_volatile_rval_filter<T>::value> { public: };
template< typename T > struct is_volatile< T& > : public ::boost::integral_constant<bool,false> { public: };
}
namespace boost {
template< typename T > struct is_enum : public ::boost::integral_constant<bool,__is_enum(T)> { public: };
}
namespace boost {
namespace type_traits {
template <typename T>
struct is_mem_fun_pointer_impl
{
    static const bool value = false;
};
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)() > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)( ...) > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)() const > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)() volatile > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)() const volatile > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)( ...) const > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)( ...) volatile > { static const bool value = true; };
template <class R, class T >
struct is_mem_fun_pointer_impl<R (T::*)( ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0) > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0 ...) > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0) const > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0) volatile > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0) const volatile > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0 ...) const > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0>
struct is_mem_fun_pointer_impl<R (T::*)( T0 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1) > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 ...) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24) const volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) const > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) volatile > { static const bool value = true; };
template <class R, class T , class T0 , class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 , class T16 , class T17 , class T18 , class T19 , class T20 , class T21 , class T22 , class T23 , class T24>
struct is_mem_fun_pointer_impl<R (T::*)( T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 ...) const volatile > { static const bool value = true; };
}
}
       
namespace boost {
namespace detail{
template <class T>
struct rvalue_ref_filter_rem_cv
{
   typedef typename boost::detail::cv_traits_imp<T*>::unqualified_type type;
};
}
template< typename T > struct remove_cv { public: typedef typename boost::detail::rvalue_ref_filter_rem_cv<T>::type type; };
template< typename T > struct remove_cv<T&> { public: typedef T& type; };
template< typename T, std::size_t N > struct remove_cv<T const[N]> { public: typedef T type[N]; };
template< typename T, std::size_t N > struct remove_cv<T volatile[N]> { public: typedef T type[N]; };
template< typename T, std::size_t N > struct remove_cv<T const volatile[N]> { public: typedef T type[N]; };
}
namespace boost {
template< typename T > struct is_member_function_pointer : public ::boost::integral_constant<bool,::boost::type_traits::is_mem_fun_pointer_impl<typename remove_cv<T>::type>::value> { public: };
}
namespace boost {
template< typename T > struct is_member_pointer : public ::boost::integral_constant<bool,::boost::is_member_function_pointer<T>::value> { public: };
template< typename T, typename U > struct is_member_pointer< U T::* > : public ::boost::integral_constant<bool,true> { public: };
template< typename T, typename U > struct is_member_pointer< U T::*const > : public ::boost::integral_constant<bool,true> { public: };
template< typename T, typename U > struct is_member_pointer< U T::*volatile > : public ::boost::integral_constant<bool,true> { public: };
template< typename T, typename U > struct is_member_pointer< U T::*const volatile > : public ::boost::integral_constant<bool,true> { public: };
}
namespace boost {
namespace detail {
template< typename T > struct is_pointer_helper
{
    static const bool value = false;
};
template< typename T > struct is_pointer_helper<T*> { static const bool value = true; };
template< typename T >
struct is_pointer_impl
{
    static const bool value = (::boost::type_traits::ice_and< ::boost::detail::is_pointer_helper<typename remove_cv<T>::type>::value , ::boost::type_traits::ice_not< ::boost::is_member_pointer<T>::value >::value >::value);
};
}
template< typename T > struct is_pointer : public ::boost::integral_constant<bool,::boost::detail::is_pointer_impl<T>::value> { public: };
}
namespace boost{
namespace detail{
template <typename T, bool small_>
struct ct_imp2
{
   typedef const T& param_type;
};
template <typename T>
struct ct_imp2<T, true>
{
   typedef const T param_type;
};
template <typename T, bool isp, bool b1, bool b2>
struct ct_imp
{
   typedef const T& param_type;
};
template <typename T, bool isp, bool b2>
struct ct_imp<T, isp, true, b2>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};
template <typename T, bool isp, bool b1>
struct ct_imp<T, isp, b1, true>
{
   typedef typename ct_imp2<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
};
template <typename T, bool b1, bool b2>
struct ct_imp<T, true, b1, b2>
{
   typedef const T param_type;
};
}
template <typename T>
struct call_traits
{
public:
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef typename boost::detail::ct_imp<
      T,
      ::boost::is_pointer<T>::value,
      ::boost::is_arithmetic<T>::value,
      ::boost::is_enum<T>::value
   >::param_type param_type;
};
template <typename T>
struct call_traits<T&>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;
};
template <typename T, std::size_t N>
struct call_traits<T [N]>
{
private:
   typedef T array_type[N];
public:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};
template <typename T, std::size_t N>
struct call_traits<const T [N]>
{
private:
   typedef const T array_type[N];
public:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};
}
namespace boost { namespace local { namespace aux {
template<typename F, size_t defaults = 0>
class function {
};
template<
    typename R
   
   
>
class function<
      R ()
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()() const { return call0_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0
>
class function<
      R ( A0)
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call0_(object_ , a0); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0
>
class function<
      R ( A0)
    , 1
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type); typedef R (*call_ptr1)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call0_(object_ , a0); } inline R operator()() const { return call1_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1
>
class function<
      R ( A0 , A1)
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call0_(object_ , a0 , a1); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1
>
class function<
      R ( A0 , A1)
    , 1
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call0_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call1_(object_ , a0); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1
>
class function<
      R ( A0 , A1)
    , 2
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type); typedef R (*call_ptr2)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call0_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call1_(object_ , a0); } inline R operator()() const { return call2_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2
>
class function<
      R ( A0 , A1 , A2)
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call0_(object_ , a0 , a1 , a2); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2
>
class function<
      R ( A0 , A1 , A2)
    , 1
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call0_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call1_(object_ , a0 , a1); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2
>
class function<
      R ( A0 , A1 , A2)
    , 2
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call0_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call1_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call2_(object_ , a0); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2
>
class function<
      R ( A0 , A1 , A2)
    , 3
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type); typedef R (*call_ptr3)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call0_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call1_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call2_(object_ , a0); } inline R operator()() const { return call3_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3
>
class function<
      R ( A0 , A1 , A2 , A3)
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call0_(object_ , a0 , a1 , a2 , a3); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3
>
class function<
      R ( A0 , A1 , A2 , A3)
    , 1
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call0_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call1_(object_ , a0 , a1 , a2); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3
>
class function<
      R ( A0 , A1 , A2 , A3)
    , 2
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call0_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call1_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call2_(object_ , a0 , a1); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3
>
class function<
      R ( A0 , A1 , A2 , A3)
    , 3
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr3)(object_ptr , typename ::boost::call_traits< A0 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call0_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call1_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call2_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call3_(object_ , a0); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3
>
class function<
      R ( A0 , A1 , A2 , A3)
    , 4
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr3)(object_ptr , typename ::boost::call_traits< A0 >::param_type); typedef R (*call_ptr4)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3 , call_ptr4 call4
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3; call4_ = call4;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call0_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call1_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call2_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call3_(object_ , a0); } inline R operator()() const { return call4_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_; call_ptr4 call4_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 0
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0
    ) {
        object_ = object;
        call0_ = call0;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); }
private:
    object_ptr object_;
    call_ptr0 call0_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 1
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call1_(object_ , a0 , a1 , a2 , a3); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 2
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call1_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call2_(object_ , a0 , a1 , a2); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 3
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr3)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call1_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call2_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call3_(object_ , a0 , a1); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 4
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr3)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr4)(object_ptr , typename ::boost::call_traits< A0 >::param_type);
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3 , call_ptr4 call4
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3; call4_ = call4;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call1_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call2_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call3_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call4_(object_ , a0); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_; call_ptr4 call4_;
    void* unused_;
};
template<
    typename R
    ,
    typename A0 , typename A1 , typename A2 , typename A3 , typename A4
>
class function<
      R ( A0 , A1 , A2 , A3 , A4)
    , 5
> {
    typedef void* object_ptr;
    typedef R (*call_ptr0)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type , typename ::boost::call_traits< A4 >::param_type); typedef R (*call_ptr1)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type , typename ::boost::call_traits< A3 >::param_type); typedef R (*call_ptr2)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type , typename ::boost::call_traits< A2 >::param_type); typedef R (*call_ptr3)(object_ptr , typename ::boost::call_traits< A0 >::param_type , typename ::boost::call_traits< A1 >::param_type); typedef R (*call_ptr4)(object_ptr , typename ::boost::call_traits< A0 >::param_type); typedef R (*call_ptr5)(object_ptr );
public:
    inline void boost_closure_auxXinit_callX(
        object_ptr object,
        call_ptr0 call0 , call_ptr1 call1 , call_ptr2 call2 , call_ptr3 call3 , call_ptr4 call4 , call_ptr5 call5
    ) {
        object_ = object;
        call0_ = call0; call1_ = call1; call2_ = call2; call3_ = call3; call4_ = call4; call5_ = call5;
        unused_ = 0;
    }
    inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3 , typename ::boost::call_traits< A4 >::param_type a4) const { return call0_(object_ , a0 , a1 , a2 , a3 , a4); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2 , typename ::boost::call_traits< A3 >::param_type a3) const { return call1_(object_ , a0 , a1 , a2 , a3); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1 , typename ::boost::call_traits< A2 >::param_type a2) const { return call2_(object_ , a0 , a1 , a2); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0 , typename ::boost::call_traits< A1 >::param_type a1) const { return call3_(object_ , a0 , a1); } inline R operator()( typename ::boost::call_traits< A0 >::param_type a0) const { return call4_(object_ , a0); } inline R operator()() const { return call5_(object_ ); }
private:
    object_ptr object_;
    call_ptr0 call0_; call_ptr1 call1_; call_ptr2 call2_; call_ptr3 call3_; call_ptr4 call4_; call_ptr5 call5_;
    void* unused_;
};
}}}
namespace boost { namespace local { namespace aux {
template<typename T> struct add_pointed_const { typedef T type; };
template<typename T> struct add_pointed_const<T*> { typedef T const* type; };
template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };
template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };
template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };
}}}
namespace boost {
template< typename T > struct add_const { public: typedef T const type; };
template< typename T > struct add_const<T&> { public: typedef T& type; };
}
namespace boost { namespace mpl { namespace aux {
template< typename T > struct nested_type_wknd
    : T::type
{
};
}}}
namespace mpl_ {
struct void_;
}
namespace boost { namespace mpl { using ::mpl_::void_; } }
namespace mpl_ {
struct na
{
    typedef na type;
    enum { value = 0 };
};
}
namespace boost { namespace mpl { using ::mpl_::na; } }
namespace boost { namespace mpl {
template< typename T >
struct is_na
    : false_
{
};
template<>
struct is_na<na>
    : true_
{
};
template< typename T >
struct is_not_na
    : true_
{
};
template<>
struct is_not_na<na>
    : false_
{
};
template< typename T, typename U > struct if_na
{
    typedef T type;
};
template< typename U > struct if_na<na,U>
{
    typedef U type;
};
}}
namespace boost { namespace mpl {
template<
      typename T = na
    , typename Tag = void_
    , typename Arity = int_< aux::template_arity<T>::value >
    >
struct lambda;
}}
namespace boost { namespace mpl {
namespace aux {
template< long C_ >
struct not_impl
    : bool_<!C_>
{
};
}
template<
      typename T = na
    >
struct not_
    : aux::not_impl<
          ::boost::mpl::aux::nested_type_wknd<T>::value
        >
{
   
};
template<> struct not_< na > { template< typename T1 , typename T2 =na , typename T3 =na , typename T4 =na , typename T5 =na > struct apply : not_< T1 > { }; }; template< typename Tag > struct lambda< not_< na > , Tag , int_<-1> > { typedef false_ is_le; typedef not_< na > result_; typedef not_< na > type; }; namespace aux { template< typename T1 > struct template_arity< not_< T1 > > : int_<1> { }; template<> struct template_arity< not_< na > > : int_<-1> { }; }
}}
namespace boost { namespace mpl { namespace aux {
template< typename T > struct value_type_wknd
{
    typedef typename T::value_type type;
};
}}}
namespace boost { namespace mpl { namespace aux {
typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];
template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};
template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};
template< long n > struct weighted_tag
{
    typedef char (&type)[n];
};
}}}
       
namespace mpl_ {
struct failed {};
template< bool C > struct assert { typedef void* type; };
template<> struct assert<false> { typedef assert type; };
template< bool C >
int assertion_failed( typename assert<C>::type );
template< bool C >
struct assertion
{
    static int failed( assert<false> );
};
template<>
struct assertion<true>
{
    static int failed( void* );
};
struct assert_
{
    template< typename T1, typename T2 = na, typename T3 = na, typename T4 = na > struct types {};
    static assert_ const arg;
    enum relations { equal = 1, not_equal, greater, greater_equal, less, less_equal };
};
boost::mpl::aux::weighted_tag<1>::type operator==( assert_, assert_ );
boost::mpl::aux::weighted_tag<2>::type operator!=( assert_, assert_ );
boost::mpl::aux::weighted_tag<3>::type operator>( assert_, assert_ );
boost::mpl::aux::weighted_tag<4>::type operator>=( assert_, assert_ );
boost::mpl::aux::weighted_tag<5>::type operator<( assert_, assert_ );
boost::mpl::aux::weighted_tag<6>::type operator<=( assert_, assert_ );
template< assert_::relations r, long x, long y > struct assert_relation {};
template< bool > struct assert_arg_pred_impl { typedef int type; };
template<> struct assert_arg_pred_impl<true> { typedef void* type; };
template< typename P > struct assert_arg_pred
{
    typedef typename P::type p_type;
    typedef typename assert_arg_pred_impl< p_type::value >::type type;
};
template< typename P > struct assert_arg_pred_not
{
    typedef typename P::type p_type;
    enum { p = !p_type::value };
    typedef typename assert_arg_pred_impl<p>::type type;
};
template< typename Pred >
failed ************ (Pred::************
      assert_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type )
    );
template< typename Pred >
failed ************ (boost::mpl::not_<Pred>::************
      assert_not_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type )
    );
template< typename Pred >
assert<false>
assert_arg( void (*)(Pred), typename assert_arg_pred_not<Pred>::type );
template< typename Pred >
assert<false>
assert_not_arg( void (*)(Pred), typename assert_arg_pred<Pred>::type );
}
extern boost::scope_exit::aux::undeclared boost_closure_auxXargsX;
       
       
namespace std {
  void
  __throw_bad_exception(void) __attribute__((__noreturn__));
  void
  __throw_bad_alloc(void) __attribute__((__noreturn__));
  void
  __throw_bad_cast(void) __attribute__((__noreturn__));
  void
  __throw_bad_typeid(void) __attribute__((__noreturn__));
  void
  __throw_logic_error(const char*) __attribute__((__noreturn__));
  void
  __throw_domain_error(const char*) __attribute__((__noreturn__));
  void
  __throw_invalid_argument(const char*) __attribute__((__noreturn__));
  void
  __throw_length_error(const char*) __attribute__((__noreturn__));
  void
  __throw_out_of_range(const char*) __attribute__((__noreturn__));
  void
  __throw_runtime_error(const char*) __attribute__((__noreturn__));
  void
  __throw_range_error(const char*) __attribute__((__noreturn__));
  void
  __throw_overflow_error(const char*) __attribute__((__noreturn__));
  void
  __throw_underflow_error(const char*) __attribute__((__noreturn__));
  void
  __throw_ios_failure(const char*) __attribute__((__noreturn__));
  void
  __throw_system_error(int) __attribute__((__noreturn__));
  void
  __throw_future_error(int) __attribute__((__noreturn__));
  void
  __throw_bad_function_call() __attribute__((__noreturn__));
}
       
namespace __gnu_cxx {
  template<typename _Iterator, typename _Container>
    class __normal_iterator;
}
namespace std {
  struct __true_type { };
  struct __false_type { };
  template<bool>
    struct __truth_type
    { typedef __false_type __type; };
  template<>
    struct __truth_type<true>
    { typedef __true_type __type; };
  template<class _Sp, class _Tp>
    struct __traitor
    {
      enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
      typedef typename __truth_type<__value>::__type __type;
    };
  template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_void
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_void<void>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_integer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_integer<bool>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_floating
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_floating<float>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_floating<double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_floating<long double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_pointer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Tp>
    struct __is_pointer<_Tp*>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_normal_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Iterator, typename _Container>
    struct __is_normal_iterator< __gnu_cxx::__normal_iterator<_Iterator,
             _Container> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_arithmetic
    : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
    { };
  template<typename _Tp>
    struct __is_fundamental
    : public __traitor<__is_void<_Tp>, __is_arithmetic<_Tp> >
    { };
  template<typename _Tp>
    struct __is_scalar
    : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
    { };
  template<typename _Tp>
    struct __is_char
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_char<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_char<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_byte
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_byte<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_byte<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_byte<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_move_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Tp>
    class __is_iterator_helper
    {
      typedef char __one;
      typedef struct { char __arr[2]; } __two;
      template<typename _Up>
        struct _Wrap_type
 { };
      template<typename _Up>
        static __one __test(_Wrap_type<typename _Up::iterator_category>*);
      template<typename _Up>
        static __two __test(...);
    public:
      static const bool __value = (sizeof(__test<_Tp>(0)) == 1
       || __is_pointer<_Tp>::__value);
    };
  template<typename _Tp>
    struct __is_iterator
    {
      enum { __value = __is_iterator_helper<_Tp>::__value };
      typedef typename __truth_type<__value>::__type __type;
    };
}
       
namespace __gnu_cxx {
  template<bool, typename>
    struct __enable_if
    { };
  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };
  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct __conditional_type
    { typedef _Iftrue __type; };
  template<typename _Iftrue, typename _Iffalse>
    struct __conditional_type<false, _Iftrue, _Iffalse>
    { typedef _Iffalse __type; };
  template<typename _Tp>
    struct __add_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
    public:
      typedef typename __if_type::__type __type;
    };
  template<>
    struct __add_unsigned<char>
    { typedef unsigned char __type; };
  template<>
    struct __add_unsigned<signed char>
    { typedef unsigned char __type; };
  template<>
    struct __add_unsigned<short>
    { typedef unsigned short __type; };
  template<>
    struct __add_unsigned<int>
    { typedef unsigned int __type; };
  template<>
    struct __add_unsigned<long>
    { typedef unsigned long __type; };
  template<>
    struct __add_unsigned<long long>
    { typedef unsigned long long __type; };
  template<>
    struct __add_unsigned<bool>;
  template<>
    struct __add_unsigned<wchar_t>;
  template<typename _Tp>
    struct __remove_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
    public:
      typedef typename __if_type::__type __type;
    };
  template<>
    struct __remove_unsigned<char>
    { typedef signed char __type; };
  template<>
    struct __remove_unsigned<unsigned char>
    { typedef signed char __type; };
  template<>
    struct __remove_unsigned<unsigned short>
    { typedef short __type; };
  template<>
    struct __remove_unsigned<unsigned int>
    { typedef int __type; };
  template<>
    struct __remove_unsigned<unsigned long>
    { typedef long __type; };
  template<>
    struct __remove_unsigned<unsigned long long>
    { typedef long long __type; };
  template<>
    struct __remove_unsigned<bool>;
  template<>
    struct __remove_unsigned<wchar_t>;
  template<typename _Type>
    inline bool
    __is_null_pointer(_Type* __ptr)
    { return __ptr == 0; }
  template<typename _Type>
    inline bool
    __is_null_pointer(_Type)
    { return false; }
  template<typename _Tp, bool = std::__is_integer<_Tp>::__value>
    struct __promote
    { typedef double __type; };
  template<typename _Tp>
    struct __promote<_Tp, false>
    { typedef _Tp __type; };
  template<typename _Tp, typename _Up>
    struct __promote_2
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;
    public:
      typedef __typeof__(__type1() + __type2()) __type;
    };
  template<typename _Tp, typename _Up, typename _Vp>
    struct __promote_3
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;
      typedef typename __promote<_Vp>::__type __type3;
    public:
      typedef __typeof__(__type1() + __type2() + __type3()) __type;
    };
  template<typename _Tp, typename _Up, typename _Vp, typename _Wp>
    struct __promote_4
    {
    private:
      typedef typename __promote<_Tp>::__type __type1;
      typedef typename __promote<_Up>::__type __type2;
      typedef typename __promote<_Vp>::__type __type3;
      typedef typename __promote<_Wp>::__type __type4;
    public:
      typedef __typeof__(__type1() + __type2() + __type3() + __type4()) __type;
    };
}
       
namespace __gnu_cxx {
  template<typename _Value>
    struct __numeric_traits_integer
    {
      static const _Value __min = (((_Value)(-1) < 0) ? (_Value)1 << (sizeof(_Value) * 8 - ((_Value)(-1) < 0)) : (_Value)0);
      static const _Value __max = (((_Value)(-1) < 0) ? (((((_Value)1 << ((sizeof(_Value) * 8 - ((_Value)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(_Value)0);
      static const bool __is_signed = ((_Value)(-1) < 0);
      static const int __digits = (sizeof(_Value) * 8 - ((_Value)(-1) < 0));
    };
  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__min;
  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__max;
  template<typename _Value>
    const bool __numeric_traits_integer<_Value>::__is_signed;
  template<typename _Value>
    const int __numeric_traits_integer<_Value>::__digits;
  template<typename _Value>
    struct __numeric_traits_floating
    {
      static const int __max_digits10 = (2 + (std::__are_same<_Value, float>::__value ? 24 : std::__are_same<_Value, double>::__value ? 53 : 64) * 3010 / 10000);
      static const bool __is_signed = true;
      static const int __digits10 = (std::__are_same<_Value, float>::__value ? 6 : std::__are_same<_Value, double>::__value ? 15 : 18);
      static const int __max_exponent10 = (std::__are_same<_Value, float>::__value ? 38 : std::__are_same<_Value, double>::__value ? 308 : 4932);
    };
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_digits10;
  template<typename _Value>
    const bool __numeric_traits_floating<_Value>::__is_signed;
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__digits10;
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_exponent10;
  template<typename _Value>
    struct __numeric_traits
    : public __conditional_type<std::__is_integer<_Value>::__value,
    __numeric_traits_integer<_Value>,
    __numeric_traits_floating<_Value> >::__type
    { };
}
       
       
namespace std {
  struct input_iterator_tag { };
  struct output_iterator_tag { };
  struct forward_iterator_tag : public input_iterator_tag { };
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
      typedef _Category iterator_category;
      typedef _Tp value_type;
      typedef _Distance difference_type;
      typedef _Pointer pointer;
      typedef _Reference reference;
    };
  template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type value_type;
      typedef typename _Iterator::difference_type difference_type;
      typedef typename _Iterator::pointer pointer;
      typedef typename _Iterator::reference reference;
    };
  template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef _Tp& reference;
    };
  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef const _Tp* pointer;
      typedef const _Tp& reference;
    };
  template<typename _Iter>
    inline typename iterator_traits<_Iter>::iterator_category
    __iterator_category(const _Iter&)
    { return typename iterator_traits<_Iter>::iterator_category(); }
}
       
namespace std {
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag)
    {
     
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last)
 {
   ++__first;
   ++__n;
 }
      return __n;
    }
  template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {
     
      return __last - __first;
    }
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
      return std::__distance(__first, __last,
        std::__iterator_category(__first));
    }
  template<typename _InputIterator, typename _Distance>
    inline void
    __advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
    {
     
      while (__n--)
 ++__i;
    }
  template<typename _BidirectionalIterator, typename _Distance>
    inline void
    __advance(_BidirectionalIterator& __i, _Distance __n,
       bidirectional_iterator_tag)
    {
     
      if (__n > 0)
        while (__n--)
   ++__i;
      else
        while (__n++)
   --__i;
    }
  template<typename _RandomAccessIterator, typename _Distance>
    inline void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {
     
      __i += __n;
    }
  template<typename _InputIterator, typename _Distance>
    inline void
    advance(_InputIterator& __i, _Distance __n)
    {
      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }
}
namespace std {
  template<typename _Iterator>
    class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
        typename iterator_traits<_Iterator>::value_type,
        typename iterator_traits<_Iterator>::difference_type,
        typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;
      typedef iterator_traits<_Iterator> __traits_type;
    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::pointer pointer;
      typedef typename __traits_type::reference reference;
      reverse_iterator() : current() { }
      explicit
      reverse_iterator(iterator_type __x) : current(__x) { }
      reverse_iterator(const reverse_iterator& __x)
      : current(__x.current) { }
      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
 : current(__x.base()) { }
      iterator_type
      base() const
      { return current; }
      reference
      operator*() const
      {
 _Iterator __tmp = current;
 return *--__tmp;
      }
      pointer
      operator->() const
      { return &(operator*()); }
      reverse_iterator&
      operator++()
      {
 --current;
 return *this;
      }
      reverse_iterator
      operator++(int)
      {
 reverse_iterator __tmp = *this;
 --current;
 return __tmp;
      }
      reverse_iterator&
      operator--()
      {
 ++current;
 return *this;
      }
      reverse_iterator
      operator--(int)
      {
 reverse_iterator __tmp = *this;
 ++current;
 return __tmp;
      }
      reverse_iterator
      operator+(difference_type __n) const
      { return reverse_iterator(current - __n); }
      reverse_iterator&
      operator+=(difference_type __n)
      {
 current -= __n;
 return *this;
      }
      reverse_iterator
      operator-(difference_type __n) const
      { return reverse_iterator(current + __n); }
      reverse_iterator&
      operator-=(difference_type __n)
      {
 current += __n;
 return *this;
      }
      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };
  template<typename _Iterator>
    inline bool
    operator==(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }
  template<typename _Iterator>
    inline bool
    operator<(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }
  template<typename _Iterator>
    inline bool
    operator!=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }
  template<typename _Iterator>
    inline bool
    operator>(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y < __x; }
  template<typename _Iterator>
    inline bool
    operator<=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }
  template<typename _Iterator>
    inline bool
    operator>=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }
  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }
  template<typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
       const reverse_iterator<_Iterator>& __x)
    { return reverse_iterator<_Iterator>(__x.base() - __n); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline typename reverse_iterator<_IteratorL>::difference_type
    operator-(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y.base() - __x.base(); }
  template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
    public:
      typedef _Container container_type;
      explicit
      back_insert_iterator(_Container& __x) : container(&__x) { }
      back_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_back(__value);
 return *this;
      }
      back_insert_iterator&
      operator*()
      { return *this; }
      back_insert_iterator&
      operator++()
      { return *this; }
      back_insert_iterator
      operator++(int)
      { return *this; }
    };
  template<typename _Container>
    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }
  template<typename _Container>
    class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
    public:
      typedef _Container container_type;
      explicit front_insert_iterator(_Container& __x) : container(&__x) { }
      front_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 container->push_front(__value);
 return *this;
      }
      front_insert_iterator&
      operator*()
      { return *this; }
      front_insert_iterator&
      operator++()
      { return *this; }
      front_insert_iterator
      operator++(int)
      { return *this; }
    };
  template<typename _Container>
    inline front_insert_iterator<_Container>
    front_inserter(_Container& __x)
    { return front_insert_iterator<_Container>(__x); }
  template<typename _Container>
    class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;
    public:
      typedef _Container container_type;
      insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(&__x), iter(__i) {}
      insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
 iter = container->insert(iter, __value);
 ++iter;
 return *this;
      }
      insert_iterator&
      operator*()
      { return *this; }
      insert_iterator&
      operator++()
      { return *this; }
      insert_iterator&
      operator++(int)
      { return *this; }
    };
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
      typename _Container::iterator(__i));
    }
}
namespace __gnu_cxx {
  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
      _Iterator _M_current;
      typedef iterator_traits<_Iterator> __traits_type;
    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type value_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::reference reference;
      typedef typename __traits_type::pointer pointer;
      __normal_iterator() : _M_current(_Iterator()) { }
      explicit
      __normal_iterator(const _Iterator& __i) : _M_current(__i) { }
      template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter,
     typename __enable_if<
              (std::__are_same<_Iter, typename _Container::pointer>::__value),
        _Container>::__type>& __i)
        : _M_current(__i.base()) { }
      reference
      operator*() const
      { return *_M_current; }
      pointer
      operator->() const
      { return _M_current; }
      __normal_iterator&
      operator++()
      {
 ++_M_current;
 return *this;
      }
      __normal_iterator
      operator++(int)
      { return __normal_iterator(_M_current++); }
      __normal_iterator&
      operator--()
      {
 --_M_current;
 return *this;
      }
      __normal_iterator
      operator--(int)
      { return __normal_iterator(_M_current--); }
      reference
      operator[](const difference_type& __n) const
      { return _M_current[__n]; }
      __normal_iterator&
      operator+=(const difference_type& __n)
      { _M_current += __n; return *this; }
      __normal_iterator
      operator+(const difference_type& __n) const
      { return __normal_iterator(_M_current + __n); }
      __normal_iterator&
      operator-=(const difference_type& __n)
      { _M_current -= __n; return *this; }
      __normal_iterator
      operator-(const difference_type& __n) const
      { return __normal_iterator(_M_current - __n); }
      const _Iterator&
      base() const
      { return _M_current; }
    };
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() == __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() == __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() != __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() != __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() < __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() < __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() > __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() > __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() <= __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() <= __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() >= __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() >= __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline typename __normal_iterator<_IteratorL, _Container>::difference_type
    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
    { return __lhs.base() - __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    { return __lhs.base() - __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline __normal_iterator<_Iterator, _Container>
    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
       __n, const __normal_iterator<_Iterator, _Container>& __i)
    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }
}
namespace std
{
  namespace __debug { }
}
namespace __gnu_debug
{
  using namespace std::__debug;
}
namespace std {
  template<bool _BoolType>
    struct __iter_swap
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          typedef typename iterator_traits<_ForwardIterator1>::value_type
            _ValueType1;
          _ValueType1 __tmp = (*__a);
          *__a = (*__b);
          *__b = (__tmp);
 }
    };
  template<>
    struct __iter_swap<true>
    {
      template<typename _ForwardIterator1, typename _ForwardIterator2>
        static void
        iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
        {
          swap(*__a, *__b);
        }
    };
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {
      typedef typename iterator_traits<_ForwardIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator2>::value_type
 _ValueType2;
     
     
     
     
      typedef typename iterator_traits<_ForwardIterator1>::reference
 _ReferenceType1;
      typedef typename iterator_traits<_ForwardIterator2>::reference
 _ReferenceType2;
      std::__iter_swap<__are_same<_ValueType1, _ValueType2>::__value
 && __are_same<_ValueType1&, _ReferenceType1>::__value
 && __are_same<_ValueType2&, _ReferenceType2>::__value>::
 iter_swap(__a, __b);
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator2
    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
  _ForwardIterator2 __first2)
    {
     
     
      ;
      for (; __first1 != __last1; ++__first1, ++__first2)
 std::iter_swap(__first1, __first2);
      return __first2;
    }
  template<typename _Tp>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {
     
      if (__b < __a)
 return __b;
      return __a;
    }
  template<typename _Tp>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b)
    {
     
      if (__a < __b)
 return __b;
      return __a;
    }
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      if (__comp(__b, __a))
 return __b;
      return __a;
    }
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      if (__comp(__a, __b))
 return __b;
      return __a;
    }
  template<typename _Iterator, bool _HasBase>
    struct _Iter_base
    {
      typedef _Iterator iterator_type;
      static iterator_type
      _S_base(_Iterator __it)
      { return __it; }
    };
  template<typename _Iterator>
    struct _Iter_base<_Iterator, true>
    {
      typedef typename _Iterator::iterator_type iterator_type;
      static iterator_type
      _S_base(_Iterator __it)
      { return __it.base(); }
    };
  template<typename _Iterator>
    struct _Niter_base
    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
    { };
  template<typename _Iterator>
    inline typename _Niter_base<_Iterator>::iterator_type
    __niter_base(_Iterator __it)
    { return std::_Niter_base<_Iterator>::_S_base(__it); }
  template<typename _Iterator>
    struct _Miter_base
    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
    { };
  template<typename _Iterator>
    inline typename _Miter_base<_Iterator>::iterator_type
    __miter_base(_Iterator __it)
    { return std::_Miter_base<_Iterator>::_S_base(__it); }
  template<bool, bool, typename>
    struct __copy_move
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   for (; __first != __last; ++__result, ++__first)
     *__result = *__first;
   return __result;
 }
    };
  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   typedef typename iterator_traits<_II>::difference_type _Distance;
   for(_Distance __n = __last - __first; __n > 0; --__n)
     {
       *__result = *__first;
       ++__first;
       ++__result;
     }
   return __result;
 }
    };
  template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
   return __result + _Num;
 }
    };
  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
      typedef typename iterator_traits<_II>::iterator_category _Category;
      const bool __simple = (__is_pod(_ValueTypeI)
                      && __is_pointer<_II>::__value
                      && __is_pointer<_OI>::__value
        && __are_same<_ValueTypeI, _ValueTypeO>::__value);
      return std::__copy_move<_IsMove, __simple,
                       _Category>::__copy_m(__first, __last, __result);
    }
  template<typename _CharT>
    struct char_traits;
  template<typename _CharT, typename _Traits>
    class istreambuf_iterator;
  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator;
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(_CharT*, _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(const _CharT*, const _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
     istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);
  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a2(_II __first, _II __last, _OI __result)
    {
      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
          std::__niter_base(__last),
          std::__niter_base(__result)));
    }
  template<typename _II, typename _OI>
    inline _OI
    copy(_II __first, _II __last, _OI __result)
    {
     
     
      ;
      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
  template<bool, bool, typename>
    struct __copy_move_backward
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   while (__first != __last)
     *--__result = *--__last;
   return __result;
 }
    };
  template<>
    struct __copy_move_backward<false, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   typename iterator_traits<_BI1>::difference_type __n;
   for (__n = __last - __first; __n > 0; --__n)
     *--__result = *--__last;
   return __result;
 }
    };
  template<bool _IsMove>
    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
   return __result - _Num;
 }
    };
  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
      typedef typename iterator_traits<_BI1>::iterator_category _Category;
      const bool __simple = (__is_pod(_ValueType1)
                      && __is_pointer<_BI1>::__value
                      && __is_pointer<_BI2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);
      return std::__copy_move_backward<_IsMove, __simple,
                                _Category>::__copy_move_b(__first,
         __last,
         __result);
    }
  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      return _BI2(std::__copy_move_backward_a<_IsMove>
    (std::__niter_base(__first), std::__niter_base(__last),
     std::__niter_base(__result)));
    }
  template<typename _BI1, typename _BI2>
    inline _BI2
    copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {
     
     
     
      ;
      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
       const _Tp& __value)
    {
      for (; __first != __last; ++__first)
 *__first = __value;
    }
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __first != __last; ++__first)
 *__first = __tmp;
    }
  template<typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
    {
      const _Tp __tmp = __c;
      __builtin_memset(__first, static_cast<unsigned char>(__tmp),
         __last - __first);
    }
  template<typename _ForwardIterator, typename _Tp>
    inline void
    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {
     
      ;
      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
      __value);
    }
  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      for (; __n > 0; --__n, ++__first)
 *__first = __value;
      return __first;
    }
  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __n > 0; --__n, ++__first)
 *__first = __tmp;
      return __first;
    }
  template<typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
    {
      std::__fill_a(__first, __first + __n, __c);
      return __first + __n;
    }
  template<typename _OI, typename _Size, typename _Tp>
    inline _OI
    fill_n(_OI __first, _Size __n, const _Tp& __value)
    {
     
      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
    }
  template<bool _BoolType>
    struct __equal
    {
      template<typename _II1, typename _II2>
        static bool
        equal(_II1 __first1, _II1 __last1, _II2 __first2)
        {
   for (; __first1 != __last1; ++__first1, ++__first2)
     if (!(*__first1 == *__first2))
       return false;
   return true;
 }
    };
  template<>
    struct __equal<true>
    {
      template<typename _Tp>
        static bool
        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
        {
   return !__builtin_memcmp(__first1, __first2, sizeof(_Tp)
       * (__last1 - __first1));
 }
    };
  template<typename _II1, typename _II2>
    inline bool
    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple = (__is_integer<_ValueType1>::__value
                      && __is_pointer<_II1>::__value
                      && __is_pointer<_II2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);
      return std::__equal<__simple>::equal(__first1, __last1, __first2);
    }
  template<typename, typename>
    struct __lc_rai
    {
      template<typename _II1, typename _II2>
        static _II1
        __newlast1(_II1, _II1 __last1, _II2, _II2)
        { return __last1; }
      template<typename _II>
        static bool
        __cnd2(_II __first, _II __last)
        { return __first != __last; }
    };
  template<>
    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
    {
      template<typename _RAI1, typename _RAI2>
        static _RAI1
        __newlast1(_RAI1 __first1, _RAI1 __last1,
     _RAI2 __first2, _RAI2 __last2)
        {
   const typename iterator_traits<_RAI1>::difference_type
     __diff1 = __last1 - __first1;
   const typename iterator_traits<_RAI2>::difference_type
     __diff2 = __last2 - __first2;
   return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
 }
      template<typename _RAI>
        static bool
        __cnd2(_RAI, _RAI)
        { return true; }
    };
  template<bool _BoolType>
    struct __lexicographical_compare
    {
      template<typename _II1, typename _II2>
        static bool __lc(_II1, _II1, _II2, _II2);
    };
  template<bool _BoolType>
    template<typename _II1, typename _II2>
      bool
      __lexicographical_compare<_BoolType>::
      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
      {
 typedef typename iterator_traits<_II1>::iterator_category _Category1;
 typedef typename iterator_traits<_II2>::iterator_category _Category2;
 typedef std::__lc_rai<_Category1, _Category2> __rai_type;
 __last1 = __rai_type::__newlast1(__first1, __last1,
      __first2, __last2);
 for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
      ++__first1, ++__first2)
   {
     if (*__first1 < *__first2)
       return true;
     if (*__first2 < *__first1)
       return false;
   }
 return __first1 == __last1 && __first2 != __last2;
      }
  template<>
    struct __lexicographical_compare<true>
    {
      template<typename _Tp, typename _Up>
        static bool
        __lc(const _Tp* __first1, const _Tp* __last1,
      const _Up* __first2, const _Up* __last2)
 {
   const size_t __len1 = __last1 - __first1;
   const size_t __len2 = __last2 - __first2;
   const int __result = __builtin_memcmp(__first1, __first2,
      std::min(__len1, __len2));
   return __result != 0 ? __result < 0 : __len1 < __len2;
 }
    };
  template<typename _II1, typename _II2>
    inline bool
    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
      _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple =
 (__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
  && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
  && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
  && __is_pointer<_II1>::__value
  && __is_pointer<_II2>::__value);
      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
           __first2, __last2);
    }
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (*__middle < __val)
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else
     __len = __half;
 }
      return __first;
    }
  template<typename _Size>
    inline _Size
    __lg(_Size __n)
    {
      _Size __k;
      for (__k = 0; __n != 0; __n >>= 1)
 ++__k;
      return __k - 1;
    }
  inline int
  __lg(int __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }
  inline long
  __lg(long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }
  inline long long
  __lg(long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }
}
namespace std {
  template<typename _II1, typename _II2>
    inline bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {
     
     
     
      ;
      return std::__equal_aux(std::__niter_base(__first1),
         std::__niter_base(__last1),
         std::__niter_base(__first2));
    }
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    inline bool
    equal(_IIter1 __first1, _IIter1 __last1,
   _IIter2 __first2, _BinaryPredicate __binary_pred)
    {
     
     
      ;
      for (; __first1 != __last1; ++__first1, ++__first2)
 if (!bool(__binary_pred(*__first1, *__first2)))
   return false;
      return true;
    }
  template<typename _II1, typename _II2>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
     
     
     
     
      ;
      ;
      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
      std::__niter_base(__last1),
      std::__niter_base(__first2),
      std::__niter_base(__last2));
    }
  template<typename _II1, typename _II2, typename _Compare>
    bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2, _Compare __comp)
    {
      typedef typename iterator_traits<_II1>::iterator_category _Category1;
      typedef typename iterator_traits<_II2>::iterator_category _Category2;
      typedef std::__lc_rai<_Category1, _Category2> __rai_type;
     
     
      ;
      ;
      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
    ++__first1, ++__first2)
 {
   if (__comp(*__first1, *__first2))
     return true;
   if (__comp(*__first2, *__first1))
     return false;
 }
      return __first1 == __last1 && __first2 != __last2;
    }
  template<typename _InputIterator1, typename _InputIterator2>
    pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2)
    {
     
     
     
      ;
      while (__first1 != __last1 && *__first1 == *__first2)
        {
   ++__first1;
   ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
     
     
      ;
      while (__first1 != __last1 && bool(__binary_pred(*__first1, *__first2)))
        {
   ++__first1;
   ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }
}
       
       
extern "C" {
typedef unsigned long __ULong;
struct _reent;
struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};
struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};
struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];
 __ULong _fntypes;
 __ULong _is_cxa;
};
struct _atexit {
 struct _atexit *_next;
 int _ind;
 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
struct __sbuf {
 unsigned char *_base;
 int _size;
};
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;
  void * _cookie;
  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, int);
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, int);
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);
  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;
  unsigned char _ubuf[3];
  unsigned char _nbuf[1];
  struct __sbuf _lb;
  int _blksize;
  int _offset;
  struct _reent *_data;
  _flock_t _lock;
  _mbstate_t _mbstate;
  int _flags2;
};
struct __sFILE64 {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;
  struct _reent *_data;
  void * _cookie;
  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, int);
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, int);
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);
  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;
  unsigned char _ubuf[3];
  unsigned char _nbuf[1];
  struct __sbuf _lb;
  int _blksize;
  int _flags2;
  _off64_t _offset;
  _fpos64_t (__attribute__((__cdecl__)) * _seek64) (struct _reent *, void *, _fpos64_t, int);
  _flock_t _lock;
  _mbstate_t _mbstate;
};
typedef struct __sFILE64 __FILE;
struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;
};
struct _reent
{
  int _errno;
  __FILE *_stdin, *_stdout, *_stderr;
  int _inc;
  char _emergency[25];
  int _current_category;
  const char *_current_locale;
  int __sdidinit;
  void (__attribute__((__cdecl__)) * __cleanup) (struct _reent *);
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;
  int _cvtlen;
  char *_cvtbuf;
  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;
      struct
        {
          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;
  struct _atexit *_atexit;
  struct _atexit _atexit0;
  void (**(_sig_func))(int);
  struct _glue __sglue;
  __FILE __sf[3];
};
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;
void _reclaim_reent (struct _reent *);
  struct _reent * __attribute__((__cdecl__)) __getreent (void);
}
extern "C" {
char *mkdtemp (char *);
}
extern "C"
{
const char *getprogname (void);
void setprogname (const char *);
char *realpath (const char *, char *);
char *canonicalize_file_name (const char *);
int unsetenv (const char *);
char *initstate (unsigned seed, char *state, size_t size);
long random (void);
char *setstate (const char *state);
void srandom (unsigned);
char *ptsname (int);
int grantpt (int);
int unlockpt (int);
int posix_openpt (int);
int posix_memalign (void **, size_t, size_t);
extern void * memalign (size_t, size_t);
extern void * valloc (size_t);
}
extern "C" {
typedef struct
{
  int quot;
  int rem;
} div_t;
typedef struct
{
  long quot;
  long rem;
} ldiv_t;
typedef struct
{
  long long int quot;
  long long int rem;
} lldiv_t;
int __attribute__((__cdecl__)) __locale_mb_cur_max (void);
void __attribute__((__cdecl__)) abort (void) __attribute__ ((noreturn));
int __attribute__((__cdecl__)) abs (int);
int __attribute__((__cdecl__)) atexit (void (*__func)(void));
double __attribute__((__cdecl__)) atof (const char *__nptr);
float __attribute__((__cdecl__)) atoff (const char *__nptr);
int __attribute__((__cdecl__)) atoi (const char *__nptr);
int __attribute__((__cdecl__)) _atoi_r (struct _reent *, const char *__nptr);
long __attribute__((__cdecl__)) atol (const char *__nptr);
long __attribute__((__cdecl__)) _atol_r (struct _reent *, const char *__nptr);
void * __attribute__((__cdecl__)) bsearch (const void * __key, const void * __base, size_t __nmemb, size_t __size, int (__attribute__((__cdecl__)) * _compar) (const void *, const void *));
void * __attribute__((__cdecl__)) calloc (size_t __nmemb, size_t __size) __attribute__ ((nothrow));
div_t __attribute__((__cdecl__)) div (int __numer, int __denom);
void __attribute__((__cdecl__)) exit (int __status) __attribute__ ((noreturn));
void __attribute__((__cdecl__)) free (void *) __attribute__ ((nothrow));
char * __attribute__((__cdecl__)) getenv (const char *__string);
char * __attribute__((__cdecl__)) _getenv_r (struct _reent *, const char *__string);
char * __attribute__((__cdecl__)) _findenv (const char *, int *);
char * __attribute__((__cdecl__)) _findenv_r (struct _reent *, const char *, int *);
extern char *suboptarg;
int __attribute__((__cdecl__)) getsubopt (char **, char * const *, char **);
long __attribute__((__cdecl__)) labs (long);
ldiv_t __attribute__((__cdecl__)) ldiv (long __numer, long __denom);
void * __attribute__((__cdecl__)) malloc (size_t __size) __attribute__ ((nothrow));
int __attribute__((__cdecl__)) mblen (const char *, size_t);
int __attribute__((__cdecl__)) _mblen_r (struct _reent *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) mbtowc (wchar_t *, const char *, size_t);
int __attribute__((__cdecl__)) _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) wctomb (char *, wchar_t);
int __attribute__((__cdecl__)) _wctomb_r (struct _reent *, char *, wchar_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) mbstowcs (wchar_t *, const char *, size_t);
size_t __attribute__((__cdecl__)) _mbstowcs_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) wcstombs (char *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) _wcstombs_r (struct _reent *, char *, const wchar_t *, size_t, _mbstate_t *);
char * __attribute__((__cdecl__)) mkdtemp (char *);
int __attribute__((__cdecl__)) mkostemp (char *, int);
int __attribute__((__cdecl__)) mkostemps (char *, int, int);
int __attribute__((__cdecl__)) mkstemp (char *);
int __attribute__((__cdecl__)) mkstemps (char *, int);
char * __attribute__((__cdecl__)) mktemp (char *) __attribute__ ((__warning__ ("the use of `mktemp' is dangerous; use `mkstemp' instead")));
char * __attribute__((__cdecl__)) _mkdtemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkostemp_r (struct _reent *, char *, int);
int __attribute__((__cdecl__)) _mkostemps_r (struct _reent *, char *, int, int);
int __attribute__((__cdecl__)) _mkstemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkstemps_r (struct _reent *, char *, int);
char * __attribute__((__cdecl__)) _mktemp_r (struct _reent *, char *) __attribute__ ((__warning__ ("the use of `mktemp' is dangerous; use `mkstemp' instead")));
void __attribute__((__cdecl__)) qsort (void * __base, size_t __nmemb, size_t __size, int(*_compar)(const void *, const void *));
int __attribute__((__cdecl__)) rand (void);
void * __attribute__((__cdecl__)) realloc (void * __r, size_t __size) __attribute__ ((nothrow));
void * __attribute__((__cdecl__)) reallocf (void * __r, size_t __size);
void __attribute__((__cdecl__)) srand (unsigned __seed);
double __attribute__((__cdecl__)) strtod (const char *__n, char **__end_PTR);
double __attribute__((__cdecl__)) _strtod_r (struct _reent *,const char *__n, char **__end_PTR);
float __attribute__((__cdecl__)) strtof (const char *__n, char **__end_PTR);
long __attribute__((__cdecl__)) strtol (const char *__n, char **__end_PTR, int __base);
long __attribute__((__cdecl__)) _strtol_r (struct _reent *,const char *__n, char **__end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) strtoul (const char *__n, char **__end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) _strtoul_r (struct _reent *,const char *__n, char **__end_PTR, int __base);
int __attribute__((__cdecl__)) system (const char *__string);
long __attribute__((__cdecl__)) a64l (const char *__input);
char * __attribute__((__cdecl__)) l64a (long __input);
char * __attribute__((__cdecl__)) _l64a_r (struct _reent *,long __input);
int __attribute__((__cdecl__)) on_exit (void (*__func)(int, void *),void * __arg);
void __attribute__((__cdecl__)) _Exit (int __status) __attribute__ ((noreturn));
int __attribute__((__cdecl__)) putenv (char *__string);
int __attribute__((__cdecl__)) _putenv_r (struct _reent *, char *__string);
void * __attribute__((__cdecl__)) _reallocf_r (struct _reent *, void *, size_t);
int __attribute__((__cdecl__)) setenv (const char *__string, const char *__value, int __overwrite);
int __attribute__((__cdecl__)) _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);
char * __attribute__((__cdecl__)) gcvt (double,int,char *);
char * __attribute__((__cdecl__)) gcvtf (float,int,char *);
char * __attribute__((__cdecl__)) fcvt (double,int,int *,int *);
char * __attribute__((__cdecl__)) fcvtf (float,int,int *,int *);
char * __attribute__((__cdecl__)) ecvt (double,int,int *,int *);
char * __attribute__((__cdecl__)) ecvtbuf (double, int, int*, int*, char *);
char * __attribute__((__cdecl__)) fcvtbuf (double, int, int*, int*, char *);
char * __attribute__((__cdecl__)) ecvtf (float,int,int *,int *);
char * __attribute__((__cdecl__)) dtoa (double, int, int, int *, int*, char**);
int __attribute__((__cdecl__)) rand_r (unsigned *__seed);
double __attribute__((__cdecl__)) drand48 (void);
double __attribute__((__cdecl__)) _drand48_r (struct _reent *);
double __attribute__((__cdecl__)) erand48 (unsigned short [3]);
double __attribute__((__cdecl__)) _erand48_r (struct _reent *, unsigned short [3]);
long __attribute__((__cdecl__)) jrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _jrand48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) lcong48 (unsigned short [7]);
void __attribute__((__cdecl__)) _lcong48_r (struct _reent *, unsigned short [7]);
long __attribute__((__cdecl__)) lrand48 (void);
long __attribute__((__cdecl__)) _lrand48_r (struct _reent *);
long __attribute__((__cdecl__)) mrand48 (void);
long __attribute__((__cdecl__)) _mrand48_r (struct _reent *);
long __attribute__((__cdecl__)) nrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _nrand48_r (struct _reent *, unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) seed48 (unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) _seed48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) srand48 (long);
void __attribute__((__cdecl__)) _srand48_r (struct _reent *, long);
long long __attribute__((__cdecl__)) atoll (const char *__nptr);
long long __attribute__((__cdecl__)) _atoll_r (struct _reent *, const char *__nptr);
long long __attribute__((__cdecl__)) llabs (long long);
lldiv_t __attribute__((__cdecl__)) lldiv (long long __numer, long long __denom);
long long __attribute__((__cdecl__)) strtoll (const char *__n, char **__end_PTR, int __base);
long long __attribute__((__cdecl__)) _strtoll_r (struct _reent *, const char *__n, char **__end_PTR, int __base);
unsigned long long __attribute__((__cdecl__)) strtoull (const char *__n, char **__end_PTR, int __base);
unsigned long long __attribute__((__cdecl__)) _strtoull_r (struct _reent *, const char *__n, char **__end_PTR, int __base);
char * __attribute__((__cdecl__)) _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);
int __attribute__((__cdecl__)) _system_r (struct _reent *, const char *);
void __attribute__((__cdecl__)) __eprintf (const char *, const char *, unsigned int, const char *);
}
namespace std {
  using ::div_t;
  using ::ldiv_t;
  using ::abort;
  using ::abs;
  using ::atexit;
  using ::atof;
  using ::atoi;
  using ::atol;
  using ::bsearch;
  using ::calloc;
  using ::div;
  using ::exit;
  using ::free;
  using ::getenv;
  using ::labs;
  using ::ldiv;
  using ::malloc;
  using ::mblen;
  using ::mbstowcs;
  using ::mbtowc;
  using ::qsort;
  using ::rand;
  using ::realloc;
  using ::srand;
  using ::strtod;
  using ::strtol;
  using ::strtoul;
  using ::system;
  using ::wcstombs;
  using ::wctomb;
  inline long
  abs(long __i) { return labs(__i); }
  inline ldiv_t
  div(long __i, long __j) { return ldiv(__i, __j); }
}
       
       
namespace std {
  template<typename _FIter, typename _Tp>
    bool
    binary_search(_FIter, _FIter, const _Tp&);
  template<typename _FIter, typename _Tp, typename _Compare>
    bool
    binary_search(_FIter, _FIter, const _Tp&, _Compare);
  template<typename _IIter, typename _OIter>
    _OIter
    copy(_IIter, _IIter, _OIter);
  template<typename _BIter1, typename _BIter2>
    _BIter2
    copy_backward(_BIter1, _BIter1, _BIter2);
  template<typename _FIter, typename _Tp>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&);
  template<typename _FIter, typename _Tp, typename _Compare>
    pair<_FIter, _FIter>
    equal_range(_FIter, _FIter, const _Tp&, _Compare);
  template<typename _FIter, typename _Tp>
    void
    fill(_FIter, _FIter, const _Tp&);
  template<typename _OIter, typename _Size, typename _Tp>
    _OIter
    fill_n(_OIter, _Size, const _Tp&);
  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2);
  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_end(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);
  template<typename _IIter1, typename _IIter2>
    bool
    includes(_IIter1, _IIter1, _IIter2, _IIter2);
  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool
    includes(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);
  template<typename _BIter>
    void
    inplace_merge(_BIter, _BIter, _BIter);
  template<typename _BIter, typename _Compare>
    void
    inplace_merge(_BIter, _BIter, _BIter, _Compare);
  template<typename _FIter1, typename _FIter2>
    void
    iter_swap(_FIter1, _FIter2);
  template<typename _FIter, typename _Tp>
    _FIter
    lower_bound(_FIter, _FIter, const _Tp&);
  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter
    lower_bound(_FIter, _FIter, const _Tp&, _Compare);
  template<typename _RAIter>
    void
    make_heap(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    make_heap(_RAIter, _RAIter, _Compare);
  template<typename _Tp>
    const _Tp&
    max(const _Tp&, const _Tp&);
  template<typename _Tp, typename _Compare>
    const _Tp&
    max(const _Tp&, const _Tp&, _Compare);
  template<typename _Tp>
    const _Tp&
    min(const _Tp&, const _Tp&);
  template<typename _Tp, typename _Compare>
    const _Tp&
    min(const _Tp&, const _Tp&, _Compare);
  template<typename _BIter>
    bool
    next_permutation(_BIter, _BIter);
  template<typename _BIter, typename _Compare>
    bool
    next_permutation(_BIter, _BIter, _Compare);
  template<typename _IIter, typename _RAIter>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter);
  template<typename _IIter, typename _RAIter, typename _Compare>
    _RAIter
    partial_sort_copy(_IIter, _IIter, _RAIter, _RAIter, _Compare);
  template<typename _RAIter>
    void
    pop_heap(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    pop_heap(_RAIter, _RAIter, _Compare);
  template<typename _BIter>
    bool
    prev_permutation(_BIter, _BIter);
  template<typename _BIter, typename _Compare>
    bool
    prev_permutation(_BIter, _BIter, _Compare);
  template<typename _RAIter>
    void
    push_heap(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    push_heap(_RAIter, _RAIter, _Compare);
  template<typename _FIter, typename _Tp>
    _FIter
    remove(_FIter, _FIter, const _Tp&);
  template<typename _FIter, typename _Predicate>
    _FIter
    remove_if(_FIter, _FIter, _Predicate);
  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter
    remove_copy(_IIter, _IIter, _OIter, const _Tp&);
  template<typename _IIter, typename _OIter, typename _Predicate>
    _OIter
    remove_copy_if(_IIter, _IIter, _OIter, _Predicate);
  template<typename _IIter, typename _OIter, typename _Tp>
    _OIter
    replace_copy(_IIter, _IIter, _OIter, const _Tp&, const _Tp&);
  template<typename _Iter, typename _OIter, typename _Predicate, typename _Tp>
    _OIter
    replace_copy_if(_Iter, _Iter, _OIter, _Predicate, const _Tp&);
  template<typename _BIter>
    void
    reverse(_BIter, _BIter);
  template<typename _BIter, typename _OIter>
    _OIter
    reverse_copy(_BIter, _BIter, _OIter);
  template<typename _FIter>
    void
    rotate(_FIter, _FIter, _FIter);
  template<typename _FIter, typename _OIter>
    _OIter
    rotate_copy(_FIter, _FIter, _FIter, _OIter);
  template<typename _RAIter>
    void
    sort_heap(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    sort_heap(_RAIter, _RAIter, _Compare);
  template<typename _BIter, typename _Predicate>
    _BIter
    stable_partition(_BIter, _BIter, _Predicate);
  template<typename _Tp>
    void
    swap(_Tp&, _Tp&);
  template<typename _Tp, size_t _Nm>
    void
    swap(_Tp (&)[_Nm], _Tp (&)[_Nm]);
  template<typename _FIter1, typename _FIter2>
    _FIter2
    swap_ranges(_FIter1, _FIter1, _FIter2);
  template<typename _FIter>
    _FIter
    unique(_FIter, _FIter);
  template<typename _FIter, typename _BinaryPredicate>
    _FIter
    unique(_FIter, _FIter, _BinaryPredicate);
  template<typename _FIter, typename _Tp>
    _FIter
    upper_bound(_FIter, _FIter, const _Tp&);
  template<typename _FIter, typename _Tp, typename _Compare>
    _FIter
    upper_bound(_FIter, _FIter, const _Tp&, _Compare);
}
namespace std {
  template<typename _FIter>
    _FIter
    adjacent_find(_FIter, _FIter);
  template<typename _FIter, typename _BinaryPredicate>
    _FIter
    adjacent_find(_FIter, _FIter, _BinaryPredicate);
  template<typename _IIter, typename _Tp>
    typename iterator_traits<_IIter>::difference_type
    count(_IIter, _IIter, const _Tp&);
  template<typename _IIter, typename _Predicate>
    typename iterator_traits<_IIter>::difference_type
    count_if(_IIter, _IIter, _Predicate);
  template<typename _IIter1, typename _IIter2>
    bool
    equal(_IIter1, _IIter1, _IIter2);
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    bool
    equal(_IIter1, _IIter1, _IIter2, _BinaryPredicate);
  template<typename _IIter, typename _Tp>
    _IIter
    find(_IIter, _IIter, const _Tp&);
  template<typename _FIter1, typename _FIter2>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2);
  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    find_first_of(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);
  template<typename _IIter, typename _Predicate>
    _IIter
    find_if(_IIter, _IIter, _Predicate);
  template<typename _IIter, typename _Funct>
    _Funct
    for_each(_IIter, _IIter, _Funct);
  template<typename _FIter, typename _Generator>
    void
    generate(_FIter, _FIter, _Generator);
  template<typename _OIter, typename _Size, typename _Generator>
    _OIter
    generate_n(_OIter, _Size, _Generator);
  template<typename _IIter1, typename _IIter2>
    bool
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2);
  template<typename _IIter1, typename _IIter2, typename _Compare>
    bool
    lexicographical_compare(_IIter1, _IIter1, _IIter2, _IIter2, _Compare);
  template<typename _FIter>
    _FIter
    max_element(_FIter, _FIter);
  template<typename _FIter, typename _Compare>
    _FIter
    max_element(_FIter, _FIter, _Compare);
  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    merge(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);
  template<typename _FIter>
    _FIter
    min_element(_FIter, _FIter);
  template<typename _FIter, typename _Compare>
    _FIter
    min_element(_FIter, _FIter, _Compare);
  template<typename _IIter1, typename _IIter2>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2);
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    pair<_IIter1, _IIter2>
    mismatch(_IIter1, _IIter1, _IIter2, _BinaryPredicate);
  template<typename _RAIter>
    void
    nth_element(_RAIter, _RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    nth_element(_RAIter, _RAIter, _RAIter, _Compare);
  template<typename _RAIter>
    void
    partial_sort(_RAIter, _RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    partial_sort(_RAIter, _RAIter, _RAIter, _Compare);
  template<typename _BIter, typename _Predicate>
    _BIter
    partition(_BIter, _BIter, _Predicate);
  template<typename _RAIter>
    void
    random_shuffle(_RAIter, _RAIter);
  template<typename _RAIter, typename _Generator>
    void
    random_shuffle(_RAIter, _RAIter,
     _Generator&);
  template<typename _FIter, typename _Tp>
    void
    replace(_FIter, _FIter, const _Tp&, const _Tp&);
  template<typename _FIter, typename _Predicate, typename _Tp>
    void
    replace_if(_FIter, _FIter, _Predicate, const _Tp&);
  template<typename _FIter1, typename _FIter2>
    _FIter1
    search(_FIter1, _FIter1, _FIter2, _FIter2);
  template<typename _FIter1, typename _FIter2, typename _BinaryPredicate>
    _FIter1
    search(_FIter1, _FIter1, _FIter2, _FIter2, _BinaryPredicate);
  template<typename _FIter, typename _Size, typename _Tp>
    _FIter
    search_n(_FIter, _FIter, _Size, const _Tp&);
  template<typename _FIter, typename _Size, typename _Tp,
    typename _BinaryPredicate>
    _FIter
    search_n(_FIter, _FIter, _Size, const _Tp&, _BinaryPredicate);
  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);
  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_intersection(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);
  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_symmetric_difference(_IIter1, _IIter1, _IIter2, _IIter2,
        _OIter, _Compare);
  template<typename _IIter1, typename _IIter2, typename _OIter>
    _OIter
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _Compare>
    _OIter
    set_union(_IIter1, _IIter1, _IIter2, _IIter2, _OIter, _Compare);
  template<typename _RAIter>
    void
    sort(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    sort(_RAIter, _RAIter, _Compare);
  template<typename _RAIter>
    void
    stable_sort(_RAIter, _RAIter);
  template<typename _RAIter, typename _Compare>
    void
    stable_sort(_RAIter, _RAIter, _Compare);
  template<typename _IIter, typename _OIter, typename _UnaryOperation>
    _OIter
    transform(_IIter, _IIter, _OIter, _UnaryOperation);
  template<typename _IIter1, typename _IIter2, typename _OIter,
    typename _BinaryOperation>
    _OIter
    transform(_IIter1, _IIter1, _IIter2, _OIter, _BinaryOperation);
  template<typename _IIter, typename _OIter>
    _OIter
    unique_copy(_IIter, _IIter, _OIter);
  template<typename _IIter, typename _OIter, typename _BinaryPredicate>
    _OIter
    unique_copy(_IIter, _IIter, _OIter, _BinaryPredicate);
}
namespace std {
  template<typename _RandomAccessIterator, typename _Distance>
    _Distance
    __is_heap_until(_RandomAccessIterator __first, _Distance __n)
    {
      _Distance __parent = 0;
      for (_Distance __child = 1; __child < __n; ++__child)
 {
   if (__first[__parent] < __first[__child])
     return __child;
   if ((__child & 1) == 0)
     ++__parent;
 }
      return __n;
    }
  template<typename _RandomAccessIterator, typename _Distance,
    typename _Compare>
    _Distance
    __is_heap_until(_RandomAccessIterator __first, _Distance __n,
      _Compare __comp)
    {
      _Distance __parent = 0;
      for (_Distance __child = 1; __child < __n; ++__child)
 {
   if (__comp(__first[__parent], __first[__child]))
     return __child;
   if ((__child & 1) == 0)
     ++__parent;
 }
      return __n;
    }
  template<typename _RandomAccessIterator, typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Distance __n)
    { return std::__is_heap_until(__first, __n) == __n; }
  template<typename _RandomAccessIterator, typename _Compare,
    typename _Distance>
    inline bool
    __is_heap(_RandomAccessIterator __first, _Compare __comp, _Distance __n)
    { return std::__is_heap_until(__first, __n, __comp) == __n; }
  template<typename _RandomAccessIterator>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    { return std::__is_heap(__first, std::distance(__first, __last)); }
  template<typename _RandomAccessIterator, typename _Compare>
    inline bool
    __is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    { return std::__is_heap(__first, __comp, std::distance(__first, __last)); }
  template<typename _RandomAccessIterator, typename _Distance, typename _Tp>
    void
    __push_heap(_RandomAccessIterator __first,
  _Distance __holeIndex, _Distance __topIndex, _Tp __value)
    {
      _Distance __parent = (__holeIndex - 1) / 2;
      while (__holeIndex > __topIndex && *(__first + __parent) < __value)
 {
   *(__first + __holeIndex) = (*(__first + __parent));
   __holeIndex = __parent;
   __parent = (__holeIndex - 1) / 2;
 }
      *(__first + __holeIndex) = (__value);
    }
  template<typename _RandomAccessIterator>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;
     
     
      ;
      ;
      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
         _DistanceType(0), (__value));
    }
  template<typename _RandomAccessIterator, typename _Distance, typename _Tp,
    typename _Compare>
    void
    __push_heap(_RandomAccessIterator __first, _Distance __holeIndex,
  _Distance __topIndex, _Tp __value, _Compare __comp)
    {
      _Distance __parent = (__holeIndex - 1) / 2;
      while (__holeIndex > __topIndex
      && __comp(*(__first + __parent), __value))
 {
   *(__first + __holeIndex) = (*(__first + __parent));
   __holeIndex = __parent;
   __parent = (__holeIndex - 1) / 2;
 }
      *(__first + __holeIndex) = (__value);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;
     
      ;
      ;
      _ValueType __value = (*(__last - 1));
      std::__push_heap(__first, _DistanceType((__last - __first) - 1),
         _DistanceType(0), (__value), __comp);
    }
  template<typename _RandomAccessIterator, typename _Distance, typename _Tp>
    void
    __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
    _Distance __len, _Tp __value)
    {
      const _Distance __topIndex = __holeIndex;
      _Distance __secondChild = __holeIndex;
      while (__secondChild < (__len - 1) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   if (*(__first + __secondChild) < *(__first + (__secondChild - 1)))
     __secondChild--;
   *(__first + __holeIndex) = (*(__first + __secondChild));
   __holeIndex = __secondChild;
 }
      if ((__len & 1) == 0 && __secondChild == (__len - 2) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   *(__first + __holeIndex) = (*(__first + (__secondChild - 1)));
   __holeIndex = __secondChild - 1;
 }
      std::__push_heap(__first, __holeIndex, __topIndex,
         (__value));
    }
  template<typename _RandomAccessIterator>
    inline void
    __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
        _RandomAccessIterator __result)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
      _ValueType __value = (*__result);
      *__result = (*__first);
      std::__adjust_heap(__first, _DistanceType(0),
    _DistanceType(__last - __first),
    (__value));
    }
  template<typename _RandomAccessIterator>
    inline void
    pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      --__last;
      std::__pop_heap(__first, __last, __last);
    }
  template<typename _RandomAccessIterator, typename _Distance,
    typename _Tp, typename _Compare>
    void
    __adjust_heap(_RandomAccessIterator __first, _Distance __holeIndex,
    _Distance __len, _Tp __value, _Compare __comp)
    {
      const _Distance __topIndex = __holeIndex;
      _Distance __secondChild = __holeIndex;
      while (__secondChild < (__len - 1) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   if (__comp(*(__first + __secondChild),
       *(__first + (__secondChild - 1))))
     __secondChild--;
   *(__first + __holeIndex) = (*(__first + __secondChild));
   __holeIndex = __secondChild;
 }
      if ((__len & 1) == 0 && __secondChild == (__len - 2) / 2)
 {
   __secondChild = 2 * (__secondChild + 1);
   *(__first + __holeIndex) = (*(__first + (__secondChild - 1)));
   __holeIndex = __secondChild - 1;
 }
      std::__push_heap(__first, __holeIndex, __topIndex,
         (__value), __comp);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
        _RandomAccessIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
      _ValueType __value = (*__result);
      *__result = (*__first);
      std::__adjust_heap(__first, _DistanceType(0),
    _DistanceType(__last - __first),
    (__value), __comp);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    pop_heap(_RandomAccessIterator __first,
      _RandomAccessIterator __last, _Compare __comp)
    {
     
      ;
      ;
      --__last;
      std::__pop_heap(__first, __last, __last, __comp);
    }
  template<typename _RandomAccessIterator>
    void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;
     
     
      ;
      if (__last - __first < 2)
 return;
      const _DistanceType __len = __last - __first;
      _DistanceType __parent = (__len - 2) / 2;
      while (true)
 {
   _ValueType __value = (*(__first + __parent));
   std::__adjust_heap(__first, __parent, __len, (__value));
   if (__parent == 0)
     return;
   __parent--;
 }
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    make_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
   _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
   _DistanceType;
     
      ;
      if (__last - __first < 2)
 return;
      const _DistanceType __len = __last - __first;
      _DistanceType __parent = (__len - 2) / 2;
      while (true)
 {
   _ValueType __value = (*(__first + __parent));
   std::__adjust_heap(__first, __parent, __len, (__value),
        __comp);
   if (__parent == 0)
     return;
   __parent--;
 }
    }
  template<typename _RandomAccessIterator>
    void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
     
     
      ;
      ;
      while (__last - __first > 1)
 {
   --__last;
   std::__pop_heap(__first, __last, __last);
 }
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Compare __comp)
    {
     
      ;
      ;
      while (__last - __first > 1)
 {
   --__last;
   std::__pop_heap(__first, __last, __last, __comp);
 }
    }
}
       
       
       
#pragma GCC visibility push(default)
extern "C++" {
namespace std
{
  class exception
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();
    virtual const char* what() const throw();
  };
  class bad_exception : public exception
  {
  public:
    bad_exception() throw() { }
    virtual ~bad_exception() throw();
    virtual const char* what() const throw();
  };
  typedef void (*terminate_handler) ();
  typedef void (*unexpected_handler) ();
  terminate_handler set_terminate(terminate_handler) throw();
  void terminate() throw() __attribute__ ((__noreturn__));
  unexpected_handler set_unexpected(unexpected_handler) throw();
  void unexpected() __attribute__ ((__noreturn__));
  bool uncaught_exception() throw() __attribute__ ((__pure__));
}
namespace __gnu_cxx {
  void __verbose_terminate_handler();
}
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
extern "C++" {
namespace std
{
  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }
    virtual ~bad_alloc() throw();
    virtual const char* what() const throw();
  };
  struct nothrow_t { };
  extern const nothrow_t nothrow;
  typedef void (*new_handler)();
  new_handler set_new_handler(new_handler) throw();
}
void* operator new(std::size_t) throw (std::bad_alloc);
void* operator new[](std::size_t) throw (std::bad_alloc);
void operator delete(void*) throw();
void operator delete[](void*) throw();
void* operator new(std::size_t, const std::nothrow_t&) throw();
void* operator new[](std::size_t, const std::nothrow_t&) throw();
void operator delete(void*, const std::nothrow_t&) throw();
void operator delete[](void*, const std::nothrow_t&) throw();
inline void* operator new(std::size_t, void* __p) throw() { return __p; }
inline void* operator new[](std::size_t, void* __p) throw() { return __p; }
inline void operator delete (void*, void*) throw() { }
inline void operator delete[](void*, void*) throw() { }
}
#pragma GCC visibility pop
namespace std {
  template<typename _T1, typename _T2>
    inline void
    _Construct(_T1* __p, const _T2& __value)
    {
      ::new(static_cast<void*>(__p)) _T1((__value));
    }
  template<typename _Tp>
    inline void
    _Destroy(_Tp* __pointer)
    { __pointer->~_Tp(); }
  template<bool>
    struct _Destroy_aux
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator __first, _ForwardIterator __last)
 {
   for (; __first != __last; ++__first)
     std::_Destroy(&*__first);
 }
    };
  template<>
    struct _Destroy_aux<true>
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator, _ForwardIterator) { }
    };
  template<typename _ForwardIterator>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
 __destroy(__first, __last);
    }
  template <typename _Tp> class allocator;
  template<typename _ForwardIterator, typename _Allocator>
    void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      _Allocator& __alloc)
    {
      for (; __first != __last; ++__first)
 __alloc.destroy(&*__first);
    }
  template<typename _ForwardIterator, typename _Tp>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      allocator<_Tp>&)
    {
      _Destroy(__first, __last);
    }
}
namespace std {
  template<bool>
    struct __uninitialized_copy
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        uninitialized_copy(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result)
        {
   _ForwardIterator __cur = __result;
   try
     {
       for (; __first != __last; ++__first, ++__cur)
  std::_Construct(&*__cur, *__first);
       return __cur;
     }
   catch(...)
     {
       std::_Destroy(__result, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_copy<true>
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        uninitialized_copy(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result)
        { return std::copy(__first, __last, __result); }
    };
  template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator __first, _InputIterator __last,
         _ForwardIterator __result)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType2;
      return std::__uninitialized_copy<(__is_pod(_ValueType1)
     && __is_pod(_ValueType2))>::
 uninitialized_copy(__first, __last, __result);
    }
  template<bool>
    struct __uninitialized_fill
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        uninitialized_fill(_ForwardIterator __first,
      _ForwardIterator __last, const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __cur != __last; ++__cur)
  std::_Construct(&*__cur, __x);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_fill<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        uninitialized_fill(_ForwardIterator __first,
      _ForwardIterator __last, const _Tp& __x)
        { std::fill(__first, __last, __x); }
    };
  template<typename _ForwardIterator, typename _Tp>
    inline void
    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last,
         const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      std::__uninitialized_fill<__is_pod(_ValueType)>::
 uninitialized_fill(__first, __last, __x);
    }
  template<bool>
    struct __uninitialized_construct_range_dispatch
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __ucr(_ForwardIterator __first, _ForwardIterator __last,
       _Tp& __value)
        {
   if(__first == __last)
     return;
   _ForwardIterator __cur = __first;
   try
     {
       std::_Construct(&*__first, (__value));
       _ForwardIterator __prev = __cur;
       ++__cur;
       for(; __cur != __last; ++__cur, ++__prev)
  std::_Construct(&*__cur, (*__prev));
       __value = (*__prev);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_construct_range_dispatch<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __ucr(_ForwardIterator, _ForwardIterator, _Tp&) { }
    };
  template<typename _ForwardIterator, typename _Tp>
    inline void
    __uninitialized_construct_range(_ForwardIterator __first,
        _ForwardIterator __last,
        _Tp& __value)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      std::__uninitialized_construct_range_dispatch<
        __has_trivial_constructor(_ValueType)>::
   __ucr(__first, __last, __value);
    }
  template<bool>
    struct __uninitialized_fill_n
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        uninitialized_fill_n(_ForwardIterator __first, _Size __n,
        const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __n > 0; --__n, ++__cur)
  std::_Construct(&*__cur, __x);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_fill_n<true>
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        uninitialized_fill_n(_ForwardIterator __first, _Size __n,
        const _Tp& __x)
        { std::fill_n(__first, __n, __x); }
    };
  template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline void
    uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      std::__uninitialized_fill_n<__is_pod(_ValueType)>::
 uninitialized_fill_n(__first, __n, __x);
    }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __result;
      try
 {
   for (; __first != __last; ++__first, ++__cur)
     __alloc.construct(&*__cur, *__first);
   return __cur;
 }
      catch(...)
 {
   std::_Destroy(__result, __cur, __alloc);
   throw;
 }
    }
  template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, allocator<_Tp>&)
    { return std::uninitialized_copy(__first, __last, __result); }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a((__first),
      (__last),
      __result, __alloc);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Allocator>
    void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   for (; __cur != __last; ++__cur)
     __alloc.construct(&*__cur, __x);
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Tp, typename _Tp2>
    inline void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill(__first, __last, __x); }
  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Allocator>
    void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   for (; __n > 0; --__n, ++__cur)
     __alloc.construct(&*__cur, __x);
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Tp2>
    inline void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill_n(__first, __n, __x); }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_copy_move(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_copy_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_move_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_copy(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_move_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_copy_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Tp, typename _InputIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_fill_move(_ForwardIterator __result, _ForwardIterator __mid,
         const _Tp& __x, _InputIterator __first,
         _InputIterator __last, _Allocator& __alloc)
    {
      std::__uninitialized_fill_a(__result, __mid, __x, __alloc);
      try
 {
   return std::__uninitialized_move_a(__first, __last, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _InputIterator, typename _ForwardIterator, typename _Tp,
    typename _Allocator>
    inline void
    __uninitialized_move_fill(_InputIterator __first1, _InputIterator __last1,
         _ForwardIterator __first2,
         _ForwardIterator __last2, const _Tp& __x,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid2 = std::__uninitialized_move_a(__first1, __last1,
           __first2,
           __alloc);
      try
 {
   std::__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__first2, __mid2, __alloc);
   throw;
 }
    }
}
namespace std {
  template<typename _Tp>
    pair<_Tp*, ptrdiff_t>
    get_temporary_buffer(ptrdiff_t __len)
    {
      const ptrdiff_t __max =
 __gnu_cxx::__numeric_traits<ptrdiff_t>::__max / sizeof(_Tp);
      if (__len > __max)
 __len = __max;
      while (__len > 0)
 {
   _Tp* __tmp = static_cast<_Tp*>(::operator new(__len * sizeof(_Tp),
       std::nothrow));
   if (__tmp != 0)
     return std::pair<_Tp*, ptrdiff_t>(__tmp, __len);
   __len /= 2;
 }
      return std::pair<_Tp*, ptrdiff_t>(static_cast<_Tp*>(0), 0);
    }
  template<typename _Tp>
    inline void
    return_temporary_buffer(_Tp* __p)
    { ::operator delete(__p, std::nothrow); }
  template<typename _ForwardIterator, typename _Tp>
    class _Temporary_buffer
    {
     
    public:
      typedef _Tp value_type;
      typedef value_type* pointer;
      typedef pointer iterator;
      typedef ptrdiff_t size_type;
    protected:
      size_type _M_original_len;
      size_type _M_len;
      pointer _M_buffer;
    public:
      size_type
      size() const
      { return _M_len; }
      size_type
      requested_size() const
      { return _M_original_len; }
      iterator
      begin()
      { return _M_buffer; }
      iterator
      end()
      { return _M_buffer + _M_len; }
      _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last);
      ~_Temporary_buffer()
      {
 std::_Destroy(_M_buffer, _M_buffer + _M_len);
 std::return_temporary_buffer(_M_buffer);
      }
    private:
      _Temporary_buffer(const _Temporary_buffer&);
      void
      operator=(const _Temporary_buffer&);
    };
  template<typename _ForwardIterator, typename _Tp>
    _Temporary_buffer<_ForwardIterator, _Tp>::
    _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last)
    : _M_original_len(std::distance(__first, __last)),
      _M_len(0), _M_buffer(0)
    {
      try
 {
   std::pair<pointer, size_type> __p(std::get_temporary_buffer<
         value_type>(_M_original_len));
   _M_buffer = __p.first;
   _M_len = __p.second;
   if(_M_buffer)
     std::__uninitialized_construct_range(_M_buffer, _M_buffer + _M_len,
       *__first);
 }
      catch(...)
 {
   std::return_temporary_buffer(_M_buffer);
   _M_buffer = 0;
   _M_len = 0;
   throw;
 }
    }
}
namespace std {
  template<typename _Iterator>
    void
    __move_median_first(_Iterator __a, _Iterator __b, _Iterator __c)
    {
     
      if (*__a < *__b)
 {
   if (*__b < *__c)
     std::iter_swap(__a, __b);
   else if (*__a < *__c)
     std::iter_swap(__a, __c);
 }
      else if (*__a < *__c)
 return;
      else if (*__b < *__c)
 std::iter_swap(__a, __c);
      else
 std::iter_swap(__a, __b);
    }
  template<typename _Iterator, typename _Compare>
    void
    __move_median_first(_Iterator __a, _Iterator __b, _Iterator __c,
   _Compare __comp)
    {
     
      if (__comp(*__a, *__b))
 {
   if (__comp(*__b, *__c))
     std::iter_swap(__a, __b);
   else if (__comp(*__a, *__c))
     std::iter_swap(__a, __c);
 }
      else if (__comp(*__a, *__c))
 return;
      else if (__comp(*__b, *__c))
 std::iter_swap(__a, __c);
      else
 std::iter_swap(__a, __b);
    }
  template<typename _InputIterator, typename _Tp>
    inline _InputIterator
    __find(_InputIterator __first, _InputIterator __last,
    const _Tp& __val, input_iterator_tag)
    {
      while (__first != __last && !(*__first == __val))
 ++__first;
      return __first;
    }
  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    __find_if(_InputIterator __first, _InputIterator __last,
       _Predicate __pred, input_iterator_tag)
    {
      while (__first != __last && !bool(__pred(*__first)))
 ++__first;
      return __first;
    }
  template<typename _RandomAccessIterator, typename _Tp>
    _RandomAccessIterator
    __find(_RandomAccessIterator __first, _RandomAccessIterator __last,
    const _Tp& __val, random_access_iterator_tag)
    {
      typename iterator_traits<_RandomAccessIterator>::difference_type
 __trip_count = (__last - __first) >> 2;
      for (; __trip_count > 0; --__trip_count)
 {
   if (*__first == __val)
     return __first;
   ++__first;
   if (*__first == __val)
     return __first;
   ++__first;
   if (*__first == __val)
     return __first;
   ++__first;
   if (*__first == __val)
     return __first;
   ++__first;
 }
      switch (__last - __first)
 {
 case 3:
   if (*__first == __val)
     return __first;
   ++__first;
 case 2:
   if (*__first == __val)
     return __first;
   ++__first;
 case 1:
   if (*__first == __val)
     return __first;
   ++__first;
 case 0:
 default:
   return __last;
 }
    }
  template<typename _RandomAccessIterator, typename _Predicate>
    _RandomAccessIterator
    __find_if(_RandomAccessIterator __first, _RandomAccessIterator __last,
       _Predicate __pred, random_access_iterator_tag)
    {
      typename iterator_traits<_RandomAccessIterator>::difference_type
 __trip_count = (__last - __first) >> 2;
      for (; __trip_count > 0; --__trip_count)
 {
   if (__pred(*__first))
     return __first;
   ++__first;
   if (__pred(*__first))
     return __first;
   ++__first;
   if (__pred(*__first))
     return __first;
   ++__first;
   if (__pred(*__first))
     return __first;
   ++__first;
 }
      switch (__last - __first)
 {
 case 3:
   if (__pred(*__first))
     return __first;
   ++__first;
 case 2:
   if (__pred(*__first))
     return __first;
   ++__first;
 case 1:
   if (__pred(*__first))
     return __first;
   ++__first;
 case 0:
 default:
   return __last;
 }
    }
  template<typename _ForwardIterator, typename _Integer, typename _Tp>
    _ForwardIterator
    __search_n(_ForwardIterator __first, _ForwardIterator __last,
        _Integer __count, const _Tp& __val,
        std::forward_iterator_tag)
    {
      __first = std::find(__first, __last, __val);
      while (__first != __last)
 {
   typename iterator_traits<_ForwardIterator>::difference_type
     __n = __count;
   _ForwardIterator __i = __first;
   ++__i;
   while (__i != __last && __n != 1 && *__i == __val)
     {
       ++__i;
       --__n;
     }
   if (__n == 1)
     return __first;
   if (__i == __last)
     return __last;
   __first = std::find(++__i, __last, __val);
 }
      return __last;
    }
  template<typename _RandomAccessIter, typename _Integer, typename _Tp>
    _RandomAccessIter
    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
        _Integer __count, const _Tp& __val,
        std::random_access_iterator_tag)
    {
      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
 _DistanceType;
      _DistanceType __tailSize = __last - __first;
      const _DistanceType __pattSize = __count;
      if (__tailSize < __pattSize)
        return __last;
      const _DistanceType __skipOffset = __pattSize - 1;
      _RandomAccessIter __lookAhead = __first + __skipOffset;
      __tailSize -= __pattSize;
      while (1)
 {
   while (!(*__lookAhead == __val))
     {
       if (__tailSize < __pattSize)
  return __last;
       __lookAhead += __pattSize;
       __tailSize -= __pattSize;
     }
   _DistanceType __remainder = __skipOffset;
   for (_RandomAccessIter __backTrack = __lookAhead - 1;
        *__backTrack == __val; --__backTrack)
     {
       if (--__remainder == 0)
  return (__lookAhead - __skipOffset);
     }
   if (__remainder > __tailSize)
     return __last;
   __lookAhead += __remainder;
   __tailSize -= __remainder;
 }
    }
  template<typename _ForwardIterator, typename _Integer, typename _Tp,
           typename _BinaryPredicate>
    _ForwardIterator
    __search_n(_ForwardIterator __first, _ForwardIterator __last,
        _Integer __count, const _Tp& __val,
        _BinaryPredicate __binary_pred, std::forward_iterator_tag)
    {
      while (__first != __last && !bool(__binary_pred(*__first, __val)))
        ++__first;
      while (__first != __last)
 {
   typename iterator_traits<_ForwardIterator>::difference_type
     __n = __count;
   _ForwardIterator __i = __first;
   ++__i;
   while (__i != __last && __n != 1 && bool(__binary_pred(*__i, __val)))
     {
       ++__i;
       --__n;
     }
   if (__n == 1)
     return __first;
   if (__i == __last)
     return __last;
   __first = ++__i;
   while (__first != __last
   && !bool(__binary_pred(*__first, __val)))
     ++__first;
 }
      return __last;
    }
  template<typename _RandomAccessIter, typename _Integer, typename _Tp,
    typename _BinaryPredicate>
    _RandomAccessIter
    __search_n(_RandomAccessIter __first, _RandomAccessIter __last,
        _Integer __count, const _Tp& __val,
        _BinaryPredicate __binary_pred, std::random_access_iterator_tag)
    {
      typedef typename std::iterator_traits<_RandomAccessIter>::difference_type
 _DistanceType;
      _DistanceType __tailSize = __last - __first;
      const _DistanceType __pattSize = __count;
      if (__tailSize < __pattSize)
        return __last;
      const _DistanceType __skipOffset = __pattSize - 1;
      _RandomAccessIter __lookAhead = __first + __skipOffset;
      __tailSize -= __pattSize;
      while (1)
 {
   while (!bool(__binary_pred(*__lookAhead, __val)))
     {
       if (__tailSize < __pattSize)
  return __last;
       __lookAhead += __pattSize;
       __tailSize -= __pattSize;
     }
   _DistanceType __remainder = __skipOffset;
   for (_RandomAccessIter __backTrack = __lookAhead - 1;
        __binary_pred(*__backTrack, __val); --__backTrack)
     {
       if (--__remainder == 0)
  return (__lookAhead - __skipOffset);
     }
   if (__remainder > __tailSize)
     return __last;
   __lookAhead += __remainder;
   __tailSize -= __remainder;
 }
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1
    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
        _ForwardIterator2 __first2, _ForwardIterator2 __last2,
        forward_iterator_tag, forward_iterator_tag)
    {
      if (__first2 == __last2)
 return __last1;
      else
 {
   _ForwardIterator1 __result = __last1;
   while (1)
     {
       _ForwardIterator1 __new_result
  = std::search(__first1, __last1, __first2, __last2);
       if (__new_result == __last1)
  return __result;
       else
  {
    __result = __new_result;
    __first1 = __new_result;
    ++__first1;
  }
     }
 }
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    _ForwardIterator1
    __find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
        _ForwardIterator2 __first2, _ForwardIterator2 __last2,
        forward_iterator_tag, forward_iterator_tag,
        _BinaryPredicate __comp)
    {
      if (__first2 == __last2)
 return __last1;
      else
 {
   _ForwardIterator1 __result = __last1;
   while (1)
     {
       _ForwardIterator1 __new_result
  = std::search(__first1, __last1, __first2,
      __last2, __comp);
       if (__new_result == __last1)
  return __result;
       else
  {
    __result = __new_result;
    __first1 = __new_result;
    ++__first1;
  }
     }
 }
    }
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2>
    _BidirectionalIterator1
    __find_end(_BidirectionalIterator1 __first1,
        _BidirectionalIterator1 __last1,
        _BidirectionalIterator2 __first2,
        _BidirectionalIterator2 __last2,
        bidirectional_iterator_tag, bidirectional_iterator_tag)
    {
     
     
      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;
      _RevIterator1 __rlast1(__first1);
      _RevIterator2 __rlast2(__first2);
      _RevIterator1 __rresult = std::search(_RevIterator1(__last1),
             __rlast1,
             _RevIterator2(__last2),
             __rlast2);
      if (__rresult == __rlast1)
 return __last1;
      else
 {
   _BidirectionalIterator1 __result = __rresult.base();
   std::advance(__result, -std::distance(__first2, __last2));
   return __result;
 }
    }
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _BinaryPredicate>
    _BidirectionalIterator1
    __find_end(_BidirectionalIterator1 __first1,
        _BidirectionalIterator1 __last1,
        _BidirectionalIterator2 __first2,
        _BidirectionalIterator2 __last2,
        bidirectional_iterator_tag, bidirectional_iterator_tag,
        _BinaryPredicate __comp)
    {
     
     
      typedef reverse_iterator<_BidirectionalIterator1> _RevIterator1;
      typedef reverse_iterator<_BidirectionalIterator2> _RevIterator2;
      _RevIterator1 __rlast1(__first1);
      _RevIterator2 __rlast2(__first2);
      _RevIterator1 __rresult = std::search(_RevIterator1(__last1), __rlast1,
         _RevIterator2(__last2), __rlast2,
         __comp);
      if (__rresult == __rlast1)
 return __last1;
      else
 {
   _BidirectionalIterator1 __result = __rresult.base();
   std::advance(__result, -std::distance(__first2, __last2));
   return __result;
 }
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
     
     
     
      ;
      ;
      return std::__find_end(__first1, __last1, __first2, __last2,
        std::__iterator_category(__first1),
        std::__iterator_category(__first2));
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    inline _ForwardIterator1
    find_end(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
      _ForwardIterator2 __first2, _ForwardIterator2 __last2,
      _BinaryPredicate __comp)
    {
     
     
     
      ;
      ;
      return std::__find_end(__first1, __last1, __first2, __last2,
        std::__iterator_category(__first1),
        std::__iterator_category(__first2),
        __comp);
    }
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    _OutputIterator
    remove_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result, const _Tp& __value)
    {
     
     
     
      ;
      for (; __first != __last; ++__first)
 if (!(*__first == __value))
   {
     *__result = *__first;
     ++__result;
   }
      return __result;
    }
  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate>
    _OutputIterator
    remove_copy_if(_InputIterator __first, _InputIterator __last,
     _OutputIterator __result, _Predicate __pred)
    {
     
     
     
      ;
      for (; __first != __last; ++__first)
 if (!bool(__pred(*__first)))
   {
     *__result = *__first;
     ++__result;
   }
      return __result;
    }
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    remove(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __value)
    {
     
     
      ;
      __first = std::find(__first, __last, __value);
      if(__first == __last)
        return __first;
      _ForwardIterator __result = __first;
      ++__first;
      for(; __first != __last; ++__first)
        if(!(*__first == __value))
          {
            *__result = (*__first);
            ++__result;
          }
      return __result;
    }
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    remove_if(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {
     
     
      ;
      __first = std::find_if(__first, __last, __pred);
      if(__first == __last)
        return __first;
      _ForwardIterator __result = __first;
      ++__first;
      for(; __first != __last; ++__first)
        if(!bool(__pred(*__first)))
          {
            *__result = (*__first);
            ++__result;
          }
      return __result;
    }
  template<typename _ForwardIterator>
    _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last)
    {
     
     
      ;
      __first = std::adjacent_find(__first, __last);
      if (__first == __last)
 return __last;
      _ForwardIterator __dest = __first;
      ++__first;
      while (++__first != __last)
 if (!(*__dest == *__first))
   *++__dest = (*__first);
      return ++__dest;
    }
  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    unique(_ForwardIterator __first, _ForwardIterator __last,
           _BinaryPredicate __binary_pred)
    {
     
     
      ;
      __first = std::adjacent_find(__first, __last, __binary_pred);
      if (__first == __last)
 return __last;
      _ForwardIterator __dest = __first;
      ++__first;
      while (++__first != __last)
 if (!bool(__binary_pred(*__dest, *__first)))
   *++__dest = (*__first);
      return ++__dest;
    }
  template<typename _ForwardIterator, typename _OutputIterator>
    _OutputIterator
    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
    _OutputIterator __result,
    forward_iterator_tag, output_iterator_tag)
    {
      _ForwardIterator __next = __first;
      *__result = *__first;
      while (++__next != __last)
 if (!(*__first == *__next))
   {
     __first = __next;
     *++__result = *__first;
   }
      return ++__result;
    }
  template<typename _InputIterator, typename _OutputIterator>
    _OutputIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _OutputIterator __result,
    input_iterator_tag, output_iterator_tag)
    {
      typename iterator_traits<_InputIterator>::value_type __value = *__first;
      *__result = __value;
      while (++__first != __last)
 if (!(__value == *__first))
   {
     __value = *__first;
     *++__result = __value;
   }
      return ++__result;
    }
  template<typename _InputIterator, typename _ForwardIterator>
    _ForwardIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _ForwardIterator __result,
    input_iterator_tag, forward_iterator_tag)
    {
      *__result = *__first;
      while (++__first != __last)
 if (!(*__result == *__first))
   *++__result = *__first;
      return ++__result;
    }
  template<typename _ForwardIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_ForwardIterator __first, _ForwardIterator __last,
    _OutputIterator __result, _BinaryPredicate __binary_pred,
    forward_iterator_tag, output_iterator_tag)
    {
     
      _ForwardIterator __next = __first;
      *__result = *__first;
      while (++__next != __last)
 if (!bool(__binary_pred(*__first, *__next)))
   {
     __first = __next;
     *++__result = *__first;
   }
      return ++__result;
    }
  template<typename _InputIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    _OutputIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _OutputIterator __result, _BinaryPredicate __binary_pred,
    input_iterator_tag, output_iterator_tag)
    {
     
      typename iterator_traits<_InputIterator>::value_type __value = *__first;
      *__result = __value;
      while (++__first != __last)
 if (!bool(__binary_pred(__value, *__first)))
   {
     __value = *__first;
     *++__result = __value;
   }
      return ++__result;
    }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _BinaryPredicate>
    _ForwardIterator
    __unique_copy(_InputIterator __first, _InputIterator __last,
    _ForwardIterator __result, _BinaryPredicate __binary_pred,
    input_iterator_tag, forward_iterator_tag)
    {
     
      *__result = *__first;
      while (++__first != __last)
 if (!bool(__binary_pred(*__result, *__first)))
   *++__result = *__first;
      return ++__result;
    }
  template<typename _BidirectionalIterator>
    void
    __reverse(_BidirectionalIterator __first, _BidirectionalIterator __last,
       bidirectional_iterator_tag)
    {
      while (true)
 if (__first == __last || __first == --__last)
   return;
 else
   {
     std::iter_swap(__first, __last);
     ++__first;
   }
    }
  template<typename _RandomAccessIterator>
    void
    __reverse(_RandomAccessIterator __first, _RandomAccessIterator __last,
       random_access_iterator_tag)
    {
      if (__first == __last)
 return;
      --__last;
      while (__first < __last)
 {
   std::iter_swap(__first, __last);
   ++__first;
   --__last;
 }
    }
  template<typename _BidirectionalIterator>
    inline void
    reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
    {
     
      ;
      std::__reverse(__first, __last, std::__iterator_category(__first));
    }
  template<typename _BidirectionalIterator, typename _OutputIterator>
    _OutputIterator
    reverse_copy(_BidirectionalIterator __first, _BidirectionalIterator __last,
   _OutputIterator __result)
    {
     
     
      ;
      while (__first != __last)
 {
   --__last;
   *__result = *__last;
   ++__result;
 }
      return __result;
    }
  template<typename _EuclideanRingElement>
    _EuclideanRingElement
    __gcd(_EuclideanRingElement __m, _EuclideanRingElement __n)
    {
      while (__n != 0)
 {
   _EuclideanRingElement __t = __m % __n;
   __m = __n;
   __n = __t;
 }
      return __m;
    }
  template<typename _ForwardIterator>
    void
    __rotate(_ForwardIterator __first,
      _ForwardIterator __middle,
      _ForwardIterator __last,
      forward_iterator_tag)
    {
      if (__first == __middle || __last == __middle)
 return;
      _ForwardIterator __first2 = __middle;
      do
 {
   std::iter_swap(__first, __first2);
   ++__first;
   ++__first2;
   if (__first == __middle)
     __middle = __first2;
 }
      while (__first2 != __last);
      __first2 = __middle;
      while (__first2 != __last)
 {
   std::iter_swap(__first, __first2);
   ++__first;
   ++__first2;
   if (__first == __middle)
     __middle = __first2;
   else if (__first2 == __last)
     __first2 = __middle;
 }
    }
  template<typename _BidirectionalIterator>
    void
    __rotate(_BidirectionalIterator __first,
      _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
       bidirectional_iterator_tag)
    {
     
      if (__first == __middle || __last == __middle)
 return;
      std::__reverse(__first, __middle, bidirectional_iterator_tag());
      std::__reverse(__middle, __last, bidirectional_iterator_tag());
      while (__first != __middle && __middle != __last)
 {
   std::iter_swap(__first, --__last);
   ++__first;
 }
      if (__first == __middle)
 std::__reverse(__middle, __last, bidirectional_iterator_tag());
      else
 std::__reverse(__first, __middle, bidirectional_iterator_tag());
    }
  template<typename _RandomAccessIterator>
    void
    __rotate(_RandomAccessIterator __first,
      _RandomAccessIterator __middle,
      _RandomAccessIterator __last,
      random_access_iterator_tag)
    {
     
      if (__first == __middle || __last == __middle)
 return;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _Distance;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      _Distance __n = __last - __first;
      _Distance __k = __middle - __first;
      if (__k == __n - __k)
 {
   std::swap_ranges(__first, __middle, __middle);
   return;
 }
      _RandomAccessIterator __p = __first;
      for (;;)
 {
   if (__k < __n - __k)
     {
       if (__is_pod(_ValueType) && __k == 1)
  {
    _ValueType __t = (*__p);
    std::copy(__p + 1, __p + __n, __p);
    *(__p + __n - 1) = (__t);
    return;
  }
       _RandomAccessIterator __q = __p + __k;
       for (_Distance __i = 0; __i < __n - __k; ++ __i)
  {
    std::iter_swap(__p, __q);
    ++__p;
    ++__q;
  }
       __n %= __k;
       if (__n == 0)
  return;
       std::swap(__n, __k);
       __k = __n - __k;
     }
   else
     {
       __k = __n - __k;
       if (__is_pod(_ValueType) && __k == 1)
  {
    _ValueType __t = (*(__p + __n - 1));
    std::copy_backward(__p, __p + __n - 1, __p + __n);
    *__p = (__t);
    return;
  }
       _RandomAccessIterator __q = __p + __n;
       __p = __q - __k;
       for (_Distance __i = 0; __i < __n - __k; ++ __i)
  {
    --__p;
    --__q;
    std::iter_swap(__p, __q);
  }
       __n %= __k;
       if (__n == 0)
  return;
       std::swap(__n, __k);
     }
 }
    }
  template<typename _ForwardIterator>
    inline void
    rotate(_ForwardIterator __first, _ForwardIterator __middle,
    _ForwardIterator __last)
    {
     
      ;
      ;
      typedef typename iterator_traits<_ForwardIterator>::iterator_category
 _IterType;
      std::__rotate(__first, __middle, __last, _IterType());
    }
  template<typename _ForwardIterator, typename _OutputIterator>
    _OutputIterator
    rotate_copy(_ForwardIterator __first, _ForwardIterator __middle,
                _ForwardIterator __last, _OutputIterator __result)
    {
     
     
      ;
      ;
      return std::copy(__first, __middle,
                       std::copy(__middle, __last, __result));
    }
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    __partition(_ForwardIterator __first, _ForwardIterator __last,
  _Predicate __pred, forward_iterator_tag)
    {
      if (__first == __last)
 return __first;
      while (__pred(*__first))
 if (++__first == __last)
   return __first;
      _ForwardIterator __next = __first;
      while (++__next != __last)
 if (__pred(*__next))
   {
     std::iter_swap(__first, __next);
     ++__first;
   }
      return __first;
    }
  template<typename _BidirectionalIterator, typename _Predicate>
    _BidirectionalIterator
    __partition(_BidirectionalIterator __first, _BidirectionalIterator __last,
  _Predicate __pred, bidirectional_iterator_tag)
    {
      while (true)
 {
   while (true)
     if (__first == __last)
       return __first;
     else if (__pred(*__first))
       ++__first;
     else
       break;
   --__last;
   while (true)
     if (__first == __last)
       return __first;
     else if (!bool(__pred(*__last)))
       --__last;
     else
       break;
   std::iter_swap(__first, __last);
   ++__first;
 }
    }
  template<typename _ForwardIterator, typename _Predicate, typename _Distance>
    _ForwardIterator
    __inplace_stable_partition(_ForwardIterator __first,
          _ForwardIterator __last,
          _Predicate __pred, _Distance __len)
    {
      if (__len == 1)
 return __pred(*__first) ? __last : __first;
      _ForwardIterator __middle = __first;
      std::advance(__middle, __len / 2);
      _ForwardIterator __begin = std::__inplace_stable_partition(__first,
         __middle,
         __pred,
         __len / 2);
      _ForwardIterator __end = std::__inplace_stable_partition(__middle, __last,
              __pred,
              __len
              - __len / 2);
      std::rotate(__begin, __middle, __end);
      std::advance(__begin, std::distance(__middle, __end));
      return __begin;
    }
  template<typename _ForwardIterator, typename _Pointer, typename _Predicate,
    typename _Distance>
    _ForwardIterator
    __stable_partition_adaptive(_ForwardIterator __first,
    _ForwardIterator __last,
    _Predicate __pred, _Distance __len,
    _Pointer __buffer,
    _Distance __buffer_size)
    {
      if (__len <= __buffer_size)
 {
   _ForwardIterator __result1 = __first;
   _Pointer __result2 = __buffer;
   for (; __first != __last; ++__first)
     if (__pred(*__first))
       {
  *__result1 = (*__first);
  ++__result1;
       }
     else
       {
  *__result2 = (*__first);
  ++__result2;
       }
   std::copy(__buffer, __result2, __result1);
   return __result1;
 }
      else
 {
   _ForwardIterator __middle = __first;
   std::advance(__middle, __len / 2);
   _ForwardIterator __begin =
     std::__stable_partition_adaptive(__first, __middle, __pred,
          __len / 2, __buffer,
          __buffer_size);
   _ForwardIterator __end =
     std::__stable_partition_adaptive(__middle, __last, __pred,
          __len - __len / 2,
          __buffer, __buffer_size);
   std::rotate(__begin, __middle, __end);
   std::advance(__begin, std::distance(__middle, __end));
   return __begin;
 }
    }
  template<typename _ForwardIterator, typename _Predicate>
    _ForwardIterator
    stable_partition(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {
     
     
      ;
      if (__first == __last)
 return __first;
      else
 {
   typedef typename iterator_traits<_ForwardIterator>::value_type
     _ValueType;
   typedef typename iterator_traits<_ForwardIterator>::difference_type
     _DistanceType;
   _Temporary_buffer<_ForwardIterator, _ValueType> __buf(__first,
        __last);
 if (__buf.size() > 0)
   return
     std::__stable_partition_adaptive(__first, __last, __pred,
       _DistanceType(__buf.requested_size()),
       __buf.begin(),
       _DistanceType(__buf.size()));
 else
   return
     std::__inplace_stable_partition(__first, __last, __pred,
      _DistanceType(__buf.requested_size()));
 }
    }
  template<typename _RandomAccessIterator>
    void
    __heap_select(_RandomAccessIterator __first,
    _RandomAccessIterator __middle,
    _RandomAccessIterator __last)
    {
      std::make_heap(__first, __middle);
      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
 if (*__i < *__first)
   std::__pop_heap(__first, __middle, __i);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __heap_select(_RandomAccessIterator __first,
    _RandomAccessIterator __middle,
    _RandomAccessIterator __last, _Compare __comp)
    {
      std::make_heap(__first, __middle, __comp);
      for (_RandomAccessIterator __i = __middle; __i < __last; ++__i)
 if (__comp(*__i, *__first))
   std::__pop_heap(__first, __middle, __i, __comp);
    }
  template<typename _InputIterator, typename _RandomAccessIterator>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
        _RandomAccessIterator __result_first,
        _RandomAccessIterator __result_last)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
     
     
     
     
      ;
      ;
      if (__result_first == __result_last)
 return __result_last;
      _RandomAccessIterator __result_real_last = __result_first;
      while(__first != __last && __result_real_last != __result_last)
 {
   *__result_real_last = *__first;
   ++__result_real_last;
   ++__first;
 }
      std::make_heap(__result_first, __result_real_last);
      while (__first != __last)
 {
   if (*__first < *__result_first)
     std::__adjust_heap(__result_first, _DistanceType(0),
          _DistanceType(__result_real_last
          - __result_first),
          _InputValueType(*__first));
   ++__first;
 }
      std::sort_heap(__result_first, __result_real_last);
      return __result_real_last;
    }
  template<typename _InputIterator, typename _RandomAccessIterator, typename _Compare>
    _RandomAccessIterator
    partial_sort_copy(_InputIterator __first, _InputIterator __last,
        _RandomAccessIterator __result_first,
        _RandomAccessIterator __result_last,
        _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _InputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _OutputValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
     
     
     
     
     
      ;
      ;
      if (__result_first == __result_last)
 return __result_last;
      _RandomAccessIterator __result_real_last = __result_first;
      while(__first != __last && __result_real_last != __result_last)
 {
   *__result_real_last = *__first;
   ++__result_real_last;
   ++__first;
 }
      std::make_heap(__result_first, __result_real_last, __comp);
      while (__first != __last)
 {
   if (__comp(*__first, *__result_first))
     std::__adjust_heap(__result_first, _DistanceType(0),
          _DistanceType(__result_real_last
          - __result_first),
          _InputValueType(*__first),
          __comp);
   ++__first;
 }
      std::sort_heap(__result_first, __result_real_last, __comp);
      return __result_real_last;
    }
  template<typename _RandomAccessIterator>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
 __val = (*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__val < *__next)
 {
   *__last = (*__next);
   __last = __next;
   --__next;
 }
      *__last = (__val);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last,
         _Compare __comp)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
 __val = (*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__comp(__val, *__next))
 {
   *__last = (*__next);
   __last = __next;
   --__next;
 }
      *__last = (__val);
    }
  template<typename _RandomAccessIterator>
    void
    __insertion_sort(_RandomAccessIterator __first,
       _RandomAccessIterator __last)
    {
      if (__first == __last)
 return;
      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
 {
   if (*__i < *__first)
     {
       typename iterator_traits<_RandomAccessIterator>::value_type
  __val = (*__i);
       std::copy_backward(__first, __i, __i + 1);
       *__first = (__val);
     }
   else
     std::__unguarded_linear_insert(__i);
 }
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __insertion_sort(_RandomAccessIterator __first,
       _RandomAccessIterator __last, _Compare __comp)
    {
      if (__first == __last) return;
      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
 {
   if (__comp(*__i, *__first))
     {
       typename iterator_traits<_RandomAccessIterator>::value_type
  __val = (*__i);
       std::copy_backward(__first, __i, __i + 1);
       *__first = (__val);
     }
   else
     std::__unguarded_linear_insert(__i, __comp);
 }
    }
  template<typename _RandomAccessIterator>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
          _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
 std::__unguarded_linear_insert(__i);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
          _RandomAccessIterator __last, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
 std::__unguarded_linear_insert(__i, __comp);
    }
  enum { _S_threshold = 16 };
  template<typename _RandomAccessIterator>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last)
    {
      if (__last - __first > int(_S_threshold))
 {
   std::__insertion_sort(__first, __first + int(_S_threshold));
   std::__unguarded_insertion_sort(__first + int(_S_threshold), __last);
 }
      else
 std::__insertion_sort(__first, __last);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first > int(_S_threshold))
 {
   std::__insertion_sort(__first, __first + int(_S_threshold), __comp);
   std::__unguarded_insertion_sort(__first + int(_S_threshold), __last,
       __comp);
 }
      else
 std::__insertion_sort(__first, __last, __comp);
    }
  template<typename _RandomAccessIterator, typename _Tp>
    _RandomAccessIterator
    __unguarded_partition(_RandomAccessIterator __first,
     _RandomAccessIterator __last, const _Tp& __pivot)
    {
      while (true)
 {
   while (*__first < __pivot)
     ++__first;
   --__last;
   while (__pivot < *__last)
     --__last;
   if (!(__first < __last))
     return __first;
   std::iter_swap(__first, __last);
   ++__first;
 }
    }
  template<typename _RandomAccessIterator, typename _Tp, typename _Compare>
    _RandomAccessIterator
    __unguarded_partition(_RandomAccessIterator __first,
     _RandomAccessIterator __last,
     const _Tp& __pivot, _Compare __comp)
    {
      while (true)
 {
   while (__comp(*__first, __pivot))
     ++__first;
   --__last;
   while (__comp(__pivot, *__last))
     --__last;
   if (!(__first < __last))
     return __first;
   std::iter_swap(__first, __last);
   ++__first;
 }
    }
  template<typename _RandomAccessIterator>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
    _RandomAccessIterator __last)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_first(__first, __mid, (__last - 1));
      return std::__unguarded_partition(__first + 1, __last, *__first);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
    _RandomAccessIterator __last, _Compare __comp)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_first(__first, __mid, (__last - 1), __comp);
      return std::__unguarded_partition(__first + 1, __last, *__first, __comp);
    }
  template<typename _RandomAccessIterator, typename _Size>
    void
    __introsort_loop(_RandomAccessIterator __first,
       _RandomAccessIterator __last,
       _Size __depth_limit)
    {
      while (__last - __first > int(_S_threshold))
 {
   if (__depth_limit == 0)
     {
       std::partial_sort(__first, __last, __last);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last);
   std::__introsort_loop(__cut, __last, __depth_limit);
   __last = __cut;
 }
    }
  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introsort_loop(_RandomAccessIterator __first,
       _RandomAccessIterator __last,
       _Size __depth_limit, _Compare __comp)
    {
      while (__last - __first > int(_S_threshold))
 {
   if (__depth_limit == 0)
     {
       std::partial_sort(__first, __last, __last, __comp);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last, __comp);
   std::__introsort_loop(__cut, __last, __depth_limit, __comp);
   __last = __cut;
 }
    }
  template<typename _RandomAccessIterator, typename _Size>
    void
    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
    _RandomAccessIterator __last, _Size __depth_limit)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      while (__last - __first > 3)
 {
   if (__depth_limit == 0)
     {
       std::__heap_select(__first, __nth + 1, __last);
       std::iter_swap(__first, __nth);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last);
   if (__cut <= __nth)
     __first = __cut;
   else
     __last = __cut;
 }
      std::__insertion_sort(__first, __last);
    }
  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introselect(_RandomAccessIterator __first, _RandomAccessIterator __nth,
    _RandomAccessIterator __last, _Size __depth_limit,
    _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      while (__last - __first > 3)
 {
   if (__depth_limit == 0)
     {
       std::__heap_select(__first, __nth + 1, __last, __comp);
       std::iter_swap(__first, __nth);
       return;
     }
   --__depth_limit;
   _RandomAccessIterator __cut =
     std::__unguarded_partition_pivot(__first, __last, __comp);
   if (__cut <= __nth)
     __first = __cut;
   else
     __last = __cut;
 }
      std::__insertion_sort(__first, __last, __comp);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (__comp(*__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else
     __len = __half;
 }
      return __first;
    }
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (__val < *__middle)
     __len = __half;
   else
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
 }
      return __first;
    }
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (__comp(__val, *__middle))
     __len = __half;
   else
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
 }
      return __first;
    }
  template<typename _ForwardIterator, typename _Tp>
    pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
     
      ;
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle, __left, __right;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (*__middle < __val)
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else if (__val < *__middle)
     __len = __half;
   else
     {
       __left = std::lower_bound(__first, __middle, __val);
       std::advance(__first, __len);
       __right = std::upper_bound(++__middle, __first, __val);
       return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
     }
 }
      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val,
  _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
     
     
     
      ;
      ;
      _DistanceType __len = std::distance(__first, __last);
      _DistanceType __half;
      _ForwardIterator __middle, __left, __right;
      while (__len > 0)
 {
   __half = __len >> 1;
   __middle = __first;
   std::advance(__middle, __half);
   if (__comp(*__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else if (__comp(__val, *__middle))
     __len = __half;
   else
     {
       __left = std::lower_bound(__first, __middle, __val, __comp);
       std::advance(__first, __len);
       __right = std::upper_bound(++__middle, __first, __val, __comp);
       return pair<_ForwardIterator, _ForwardIterator>(__left, __right);
     }
 }
      return pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }
  template<typename _ForwardIterator, typename _Tp>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      _ForwardIterator __i = std::lower_bound(__first, __last, __val);
      return __i != __last && !(__val < *__i);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      _ForwardIterator __i = std::lower_bound(__first, __last, __val, __comp);
      return __i != __last && !bool(__comp(__val, *__i));
    }
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _BidirectionalIterator3>
    _BidirectionalIterator3
    __merge_backward(_BidirectionalIterator1 __first1,
       _BidirectionalIterator1 __last1,
       _BidirectionalIterator2 __first2,
       _BidirectionalIterator2 __last2,
       _BidirectionalIterator3 __result)
    {
      if (__first1 == __last1)
 return std::copy_backward(__first2, __last2, __result);
      if (__first2 == __last2)
 return std::copy_backward(__first1, __last1, __result);
      --__last1;
      --__last2;
      while (true)
 {
   if (*__last2 < *__last1)
     {
       *--__result = *__last1;
       if (__first1 == __last1)
  return std::copy_backward(__first2, ++__last2, __result);
       --__last1;
     }
   else
     {
       *--__result = *__last2;
       if (__first2 == __last2)
  return std::copy_backward(__first1, ++__last1, __result);
       --__last2;
     }
 }
    }
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _BidirectionalIterator3, typename _Compare>
    _BidirectionalIterator3
    __merge_backward(_BidirectionalIterator1 __first1,
       _BidirectionalIterator1 __last1,
       _BidirectionalIterator2 __first2,
       _BidirectionalIterator2 __last2,
       _BidirectionalIterator3 __result,
       _Compare __comp)
    {
      if (__first1 == __last1)
 return std::copy_backward(__first2, __last2, __result);
      if (__first2 == __last2)
 return std::copy_backward(__first1, __last1, __result);
      --__last1;
      --__last2;
      while (true)
 {
   if (__comp(*__last2, *__last1))
     {
       *--__result = *__last1;
       if (__first1 == __last1)
  return std::copy_backward(__first2, ++__last2, __result);
       --__last1;
     }
   else
     {
       *--__result = *__last2;
       if (__first2 == __last2)
  return std::copy_backward(__first1, ++__last1, __result);
       --__last2;
     }
 }
    }
  template<typename _BidirectionalIterator1, typename _BidirectionalIterator2,
    typename _Distance>
    _BidirectionalIterator1
    __rotate_adaptive(_BidirectionalIterator1 __first,
        _BidirectionalIterator1 __middle,
        _BidirectionalIterator1 __last,
        _Distance __len1, _Distance __len2,
        _BidirectionalIterator2 __buffer,
        _Distance __buffer_size)
    {
      _BidirectionalIterator2 __buffer_end;
      if (__len1 > __len2 && __len2 <= __buffer_size)
 {
   __buffer_end = std::copy(__middle, __last, __buffer);
   std::copy_backward(__first, __middle, __last);
   return std::copy(__buffer, __buffer_end, __first);
 }
      else if (__len1 <= __buffer_size)
 {
   __buffer_end = std::copy(__first, __middle, __buffer);
   std::copy(__middle, __last, __first);
   return std::copy_backward(__buffer, __buffer_end, __last);
 }
      else
 {
   std::rotate(__first, __middle, __last);
   std::advance(__first, std::distance(__middle, __last));
   return __first;
 }
    }
  template<typename _BidirectionalIterator, typename _Distance,
    typename _Pointer>
    void
    __merge_adaptive(_BidirectionalIterator __first,
                     _BidirectionalIterator __middle,
       _BidirectionalIterator __last,
       _Distance __len1, _Distance __len2,
       _Pointer __buffer, _Distance __buffer_size)
    {
      if (__len1 <= __len2 && __len1 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__first, __middle, __buffer);
   std::merge((__buffer),
    (__buffer_end),
    (__middle),
    (__last),
    __first);
 }
      else if (__len2 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__middle, __last, __buffer);
   std::__merge_backward((__first),
    (__middle),
    (__buffer),
    (__buffer_end),
    __last);
 }
      else
 {
   _BidirectionalIterator __first_cut = __first;
   _BidirectionalIterator __second_cut = __middle;
   _Distance __len11 = 0;
   _Distance __len22 = 0;
   if (__len1 > __len2)
     {
       __len11 = __len1 / 2;
       std::advance(__first_cut, __len11);
       __second_cut = std::lower_bound(__middle, __last,
           *__first_cut);
       __len22 = std::distance(__middle, __second_cut);
     }
   else
     {
       __len22 = __len2 / 2;
       std::advance(__second_cut, __len22);
       __first_cut = std::upper_bound(__first, __middle,
          *__second_cut);
       __len11 = std::distance(__first, __first_cut);
     }
   _BidirectionalIterator __new_middle =
     std::__rotate_adaptive(__first_cut, __middle, __second_cut,
       __len1 - __len11, __len22, __buffer,
       __buffer_size);
   std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
    __len22, __buffer, __buffer_size);
   std::__merge_adaptive(__new_middle, __second_cut, __last,
    __len1 - __len11,
    __len2 - __len22, __buffer, __buffer_size);
 }
    }
  template<typename _BidirectionalIterator, typename _Distance,
    typename _Pointer, typename _Compare>
    void
    __merge_adaptive(_BidirectionalIterator __first,
                     _BidirectionalIterator __middle,
       _BidirectionalIterator __last,
       _Distance __len1, _Distance __len2,
       _Pointer __buffer, _Distance __buffer_size,
       _Compare __comp)
    {
      if (__len1 <= __len2 && __len1 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__first, __middle, __buffer);
   std::merge((__buffer),
    (__buffer_end),
    (__middle),
    (__last),
    __first, __comp);
 }
      else if (__len2 <= __buffer_size)
 {
   _Pointer __buffer_end = std::copy(__middle, __last, __buffer);
   std::__merge_backward((__first),
    (__middle),
    (__buffer),
    (__buffer_end),
    __last,__comp);
 }
      else
 {
   _BidirectionalIterator __first_cut = __first;
   _BidirectionalIterator __second_cut = __middle;
   _Distance __len11 = 0;
   _Distance __len22 = 0;
   if (__len1 > __len2)
     {
       __len11 = __len1 / 2;
       std::advance(__first_cut, __len11);
       __second_cut = std::lower_bound(__middle, __last, *__first_cut,
           __comp);
       __len22 = std::distance(__middle, __second_cut);
     }
   else
     {
       __len22 = __len2 / 2;
       std::advance(__second_cut, __len22);
       __first_cut = std::upper_bound(__first, __middle, *__second_cut,
          __comp);
       __len11 = std::distance(__first, __first_cut);
     }
   _BidirectionalIterator __new_middle =
     std::__rotate_adaptive(__first_cut, __middle, __second_cut,
       __len1 - __len11, __len22, __buffer,
       __buffer_size);
   std::__merge_adaptive(__first, __first_cut, __new_middle, __len11,
    __len22, __buffer, __buffer_size, __comp);
   std::__merge_adaptive(__new_middle, __second_cut, __last,
    __len1 - __len11,
    __len2 - __len22, __buffer,
    __buffer_size, __comp);
 }
    }
  template<typename _BidirectionalIterator, typename _Distance>
    void
    __merge_without_buffer(_BidirectionalIterator __first,
      _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
      _Distance __len1, _Distance __len2)
    {
      if (__len1 == 0 || __len2 == 0)
 return;
      if (__len1 + __len2 == 2)
 {
   if (*__middle < *__first)
     std::iter_swap(__first, __middle);
   return;
 }
      _BidirectionalIterator __first_cut = __first;
      _BidirectionalIterator __second_cut = __middle;
      _Distance __len11 = 0;
      _Distance __len22 = 0;
      if (__len1 > __len2)
 {
   __len11 = __len1 / 2;
   std::advance(__first_cut, __len11);
   __second_cut = std::lower_bound(__middle, __last, *__first_cut);
   __len22 = std::distance(__middle, __second_cut);
 }
      else
 {
   __len22 = __len2 / 2;
   std::advance(__second_cut, __len22);
   __first_cut = std::upper_bound(__first, __middle, *__second_cut);
   __len11 = std::distance(__first, __first_cut);
 }
      std::rotate(__first_cut, __middle, __second_cut);
      _BidirectionalIterator __new_middle = __first_cut;
      std::advance(__new_middle, std::distance(__middle, __second_cut));
      std::__merge_without_buffer(__first, __first_cut, __new_middle,
      __len11, __len22);
      std::__merge_without_buffer(__new_middle, __second_cut, __last,
      __len1 - __len11, __len2 - __len22);
    }
  template<typename _BidirectionalIterator, typename _Distance,
    typename _Compare>
    void
    __merge_without_buffer(_BidirectionalIterator __first,
                           _BidirectionalIterator __middle,
      _BidirectionalIterator __last,
      _Distance __len1, _Distance __len2,
      _Compare __comp)
    {
      if (__len1 == 0 || __len2 == 0)
 return;
      if (__len1 + __len2 == 2)
 {
   if (__comp(*__middle, *__first))
     std::iter_swap(__first, __middle);
   return;
 }
      _BidirectionalIterator __first_cut = __first;
      _BidirectionalIterator __second_cut = __middle;
      _Distance __len11 = 0;
      _Distance __len22 = 0;
      if (__len1 > __len2)
 {
   __len11 = __len1 / 2;
   std::advance(__first_cut, __len11);
   __second_cut = std::lower_bound(__middle, __last, *__first_cut,
       __comp);
   __len22 = std::distance(__middle, __second_cut);
 }
      else
 {
   __len22 = __len2 / 2;
   std::advance(__second_cut, __len22);
   __first_cut = std::upper_bound(__first, __middle, *__second_cut,
      __comp);
   __len11 = std::distance(__first, __first_cut);
 }
      std::rotate(__first_cut, __middle, __second_cut);
      _BidirectionalIterator __new_middle = __first_cut;
      std::advance(__new_middle, std::distance(__middle, __second_cut));
      std::__merge_without_buffer(__first, __first_cut, __new_middle,
      __len11, __len22, __comp);
      std::__merge_without_buffer(__new_middle, __second_cut, __last,
      __len1 - __len11, __len2 - __len22, __comp);
    }
  template<typename _BidirectionalIterator>
    void
    inplace_merge(_BidirectionalIterator __first,
    _BidirectionalIterator __middle,
    _BidirectionalIterator __last)
    {
      typedef typename iterator_traits<_BidirectionalIterator>::value_type
          _ValueType;
      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
          _DistanceType;
     
     
      ;
      ;
      if (__first == __middle || __middle == __last)
 return;
      _DistanceType __len1 = std::distance(__first, __middle);
      _DistanceType __len2 = std::distance(__middle, __last);
      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
          __last);
      if (__buf.begin() == 0)
 std::__merge_without_buffer(__first, __middle, __last, __len1, __len2);
      else
 std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
         __buf.begin(), _DistanceType(__buf.size()));
    }
  template<typename _BidirectionalIterator, typename _Compare>
    void
    inplace_merge(_BidirectionalIterator __first,
    _BidirectionalIterator __middle,
    _BidirectionalIterator __last,
    _Compare __comp)
    {
      typedef typename iterator_traits<_BidirectionalIterator>::value_type
          _ValueType;
      typedef typename iterator_traits<_BidirectionalIterator>::difference_type
          _DistanceType;
     
     
      ;
      ;
      if (__first == __middle || __middle == __last)
 return;
      const _DistanceType __len1 = std::distance(__first, __middle);
      const _DistanceType __len2 = std::distance(__middle, __last);
      _Temporary_buffer<_BidirectionalIterator, _ValueType> __buf(__first,
          __last);
      if (__buf.begin() == 0)
 std::__merge_without_buffer(__first, __middle, __last, __len1,
        __len2, __comp);
      else
 std::__merge_adaptive(__first, __middle, __last, __len1, __len2,
         __buf.begin(), _DistanceType(__buf.size()),
         __comp);
    }
  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
    typename _Distance>
    void
    __merge_sort_loop(_RandomAccessIterator1 __first,
        _RandomAccessIterator1 __last,
        _RandomAccessIterator2 __result,
        _Distance __step_size)
    {
      const _Distance __two_step = 2 * __step_size;
      while (__last - __first >= __two_step)
 {
   __result = std::merge(
   (__first),
   (__first + __step_size),
   (__first + __step_size),
   (__first + __two_step),
   __result);
   __first += __two_step;
 }
      __step_size = std::min(_Distance(__last - __first), __step_size);
      std::merge((__first),
       (__first + __step_size),
       (__first + __step_size),
       (__last),
       __result);
    }
  template<typename _RandomAccessIterator1, typename _RandomAccessIterator2,
    typename _Distance, typename _Compare>
    void
    __merge_sort_loop(_RandomAccessIterator1 __first,
        _RandomAccessIterator1 __last,
        _RandomAccessIterator2 __result, _Distance __step_size,
        _Compare __comp)
    {
      const _Distance __two_step = 2 * __step_size;
      while (__last - __first >= __two_step)
 {
   __result = std::merge(
   (__first),
   (__first + __step_size),
   (__first + __step_size),
   (__first + __two_step),
   __result, __comp);
   __first += __two_step;
 }
      __step_size = std::min(_Distance(__last - __first), __step_size);
      std::merge((__first),
       (__first + __step_size),
       (__first + __step_size),
       (__last),
       __result, __comp);
    }
  template<typename _RandomAccessIterator, typename _Distance>
    void
    __chunk_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
      _Distance __chunk_size)
    {
      while (__last - __first >= __chunk_size)
 {
   std::__insertion_sort(__first, __first + __chunk_size);
   __first += __chunk_size;
 }
      std::__insertion_sort(__first, __last);
    }
  template<typename _RandomAccessIterator, typename _Distance,
    typename _Compare>
    void
    __chunk_insertion_sort(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
      _Distance __chunk_size, _Compare __comp)
    {
      while (__last - __first >= __chunk_size)
 {
   std::__insertion_sort(__first, __first + __chunk_size, __comp);
   __first += __chunk_size;
 }
      std::__insertion_sort(__first, __last, __comp);
    }
  enum { _S_chunk_size = 7 };
  template<typename _RandomAccessIterator, typename _Pointer>
    void
    __merge_sort_with_buffer(_RandomAccessIterator __first,
        _RandomAccessIterator __last,
                             _Pointer __buffer)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _Distance;
      const _Distance __len = __last - __first;
      const _Pointer __buffer_last = __buffer + __len;
      _Distance __step_size = _S_chunk_size;
      std::__chunk_insertion_sort(__first, __last, __step_size);
      while (__step_size < __len)
 {
   std::__merge_sort_loop(__first, __last, __buffer, __step_size);
   __step_size *= 2;
   std::__merge_sort_loop(__buffer, __buffer_last, __first, __step_size);
   __step_size *= 2;
 }
    }
  template<typename _RandomAccessIterator, typename _Pointer, typename _Compare>
    void
    __merge_sort_with_buffer(_RandomAccessIterator __first,
        _RandomAccessIterator __last,
                             _Pointer __buffer, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _Distance;
      const _Distance __len = __last - __first;
      const _Pointer __buffer_last = __buffer + __len;
      _Distance __step_size = _S_chunk_size;
      std::__chunk_insertion_sort(__first, __last, __step_size, __comp);
      while (__step_size < __len)
 {
   std::__merge_sort_loop(__first, __last, __buffer,
     __step_size, __comp);
   __step_size *= 2;
   std::__merge_sort_loop(__buffer, __buffer_last, __first,
     __step_size, __comp);
   __step_size *= 2;
 }
    }
  template<typename _RandomAccessIterator, typename _Pointer,
    typename _Distance>
    void
    __stable_sort_adaptive(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
                           _Pointer __buffer, _Distance __buffer_size)
    {
      const _Distance __len = (__last - __first + 1) / 2;
      const _RandomAccessIterator __middle = __first + __len;
      if (__len > __buffer_size)
 {
   std::__stable_sort_adaptive(__first, __middle,
          __buffer, __buffer_size);
   std::__stable_sort_adaptive(__middle, __last,
          __buffer, __buffer_size);
 }
      else
 {
   std::__merge_sort_with_buffer(__first, __middle, __buffer);
   std::__merge_sort_with_buffer(__middle, __last, __buffer);
 }
      std::__merge_adaptive(__first, __middle, __last,
       _Distance(__middle - __first),
       _Distance(__last - __middle),
       __buffer, __buffer_size);
    }
  template<typename _RandomAccessIterator, typename _Pointer,
    typename _Distance, typename _Compare>
    void
    __stable_sort_adaptive(_RandomAccessIterator __first,
      _RandomAccessIterator __last,
                           _Pointer __buffer, _Distance __buffer_size,
                           _Compare __comp)
    {
      const _Distance __len = (__last - __first + 1) / 2;
      const _RandomAccessIterator __middle = __first + __len;
      if (__len > __buffer_size)
 {
   std::__stable_sort_adaptive(__first, __middle, __buffer,
          __buffer_size, __comp);
   std::__stable_sort_adaptive(__middle, __last, __buffer,
          __buffer_size, __comp);
 }
      else
 {
   std::__merge_sort_with_buffer(__first, __middle, __buffer, __comp);
   std::__merge_sort_with_buffer(__middle, __last, __buffer, __comp);
 }
      std::__merge_adaptive(__first, __middle, __last,
       _Distance(__middle - __first),
       _Distance(__last - __middle),
       __buffer, __buffer_size,
       __comp);
    }
  template<typename _RandomAccessIterator>
    void
    __inplace_stable_sort(_RandomAccessIterator __first,
     _RandomAccessIterator __last)
    {
      if (__last - __first < 15)
 {
   std::__insertion_sort(__first, __last);
   return;
 }
      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
      std::__inplace_stable_sort(__first, __middle);
      std::__inplace_stable_sort(__middle, __last);
      std::__merge_without_buffer(__first, __middle, __last,
      __middle - __first,
      __last - __middle);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __inplace_stable_sort(_RandomAccessIterator __first,
     _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first < 15)
 {
   std::__insertion_sort(__first, __last, __comp);
   return;
 }
      _RandomAccessIterator __middle = __first + (__last - __first) / 2;
      std::__inplace_stable_sort(__first, __middle, __comp);
      std::__inplace_stable_sort(__middle, __last, __comp);
      std::__merge_without_buffer(__first, __middle, __last,
      __middle - __first,
      __last - __middle,
      __comp);
    }
  template<typename _InputIterator1, typename _InputIterator2>
    bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (*__first2 < *__first1)
   return false;
 else if(*__first1 < *__first2)
   ++__first1;
 else
   ++__first1, ++__first2;
      return __first2 == __last2;
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _Compare>
    bool
    includes(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _InputIterator2 __last2,
      _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(*__first2, *__first1))
   return false;
 else if(__comp(*__first1, *__first2))
   ++__first1;
 else
   ++__first1, ++__first2;
      return __first2 == __last2;
    }
  template<typename _BidirectionalIterator>
    bool
    next_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last)
    {
     
     
      ;
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;
      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (*__i < *__ii)
     {
       _BidirectionalIterator __j = __last;
       while (!(*__i < *--__j))
  {}
       std::iter_swap(__i, __j);
       std::reverse(__ii, __last);
       return true;
     }
   if (__i == __first)
     {
       std::reverse(__first, __last);
       return false;
     }
 }
    }
  template<typename _BidirectionalIterator, typename _Compare>
    bool
    next_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last, _Compare __comp)
    {
     
     
      ;
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;
      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (__comp(*__i, *__ii))
     {
       _BidirectionalIterator __j = __last;
       while (!bool(__comp(*__i, *--__j)))
  {}
       std::iter_swap(__i, __j);
       std::reverse(__ii, __last);
       return true;
     }
   if (__i == __first)
     {
       std::reverse(__first, __last);
       return false;
     }
 }
    }
  template<typename _BidirectionalIterator>
    bool
    prev_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last)
    {
     
     
      ;
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;
      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (*__ii < *__i)
     {
       _BidirectionalIterator __j = __last;
       while (!(*--__j < *__i))
  {}
       std::iter_swap(__i, __j);
       std::reverse(__ii, __last);
       return true;
     }
   if (__i == __first)
     {
       std::reverse(__first, __last);
       return false;
     }
 }
    }
  template<typename _BidirectionalIterator, typename _Compare>
    bool
    prev_permutation(_BidirectionalIterator __first,
       _BidirectionalIterator __last, _Compare __comp)
    {
     
     
      ;
      if (__first == __last)
 return false;
      _BidirectionalIterator __i = __first;
      ++__i;
      if (__i == __last)
 return false;
      __i = __last;
      --__i;
      for(;;)
 {
   _BidirectionalIterator __ii = __i;
   --__i;
   if (__comp(*__ii, *__i))
     {
       _BidirectionalIterator __j = __last;
       while (!bool(__comp(*--__j, *__i)))
  {}
       std::iter_swap(__i, __j);
       std::reverse(__ii, __last);
       return true;
     }
   if (__i == __first)
     {
       std::reverse(__first, __last);
       return false;
     }
 }
    }
  template<typename _InputIterator, typename _OutputIterator, typename _Tp>
    _OutputIterator
    replace_copy(_InputIterator __first, _InputIterator __last,
   _OutputIterator __result,
   const _Tp& __old_value, const _Tp& __new_value)
    {
     
     
     
      ;
      for (; __first != __last; ++__first, ++__result)
 if (*__first == __old_value)
   *__result = __new_value;
 else
   *__result = *__first;
      return __result;
    }
  template<typename _InputIterator, typename _OutputIterator,
    typename _Predicate, typename _Tp>
    _OutputIterator
    replace_copy_if(_InputIterator __first, _InputIterator __last,
      _OutputIterator __result,
      _Predicate __pred, const _Tp& __new_value)
    {
     
     
     
      ;
      for (; __first != __last; ++__first, ++__result)
 if (__pred(*__first))
   *__result = __new_value;
 else
   *__result = *__first;
      return __result;
    }
}
namespace std {
  template<typename _InputIterator, typename _Function>
    _Function
    for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    {
     
      ;
      for (; __first != __last; ++__first)
 __f(*__first);
      return (__f);
    }
  template<typename _InputIterator, typename _Tp>
    inline _InputIterator
    find(_InputIterator __first, _InputIterator __last,
  const _Tp& __val)
    {
     
     
      ;
      return std::__find(__first, __last, __val,
           std::__iterator_category(__first));
    }
  template<typename _InputIterator, typename _Predicate>
    inline _InputIterator
    find_if(_InputIterator __first, _InputIterator __last,
     _Predicate __pred)
    {
     
     
      ;
      return std::__find_if(__first, __last, __pred,
       std::__iterator_category(__first));
    }
  template<typename _InputIterator, typename _ForwardIterator>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
    _ForwardIterator __first2, _ForwardIterator __last2)
    {
     
     
     
      ;
      ;
      for (; __first1 != __last1; ++__first1)
 for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
   if (*__first1 == *__iter)
     return __first1;
      return __last1;
    }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _BinaryPredicate>
    _InputIterator
    find_first_of(_InputIterator __first1, _InputIterator __last1,
    _ForwardIterator __first2, _ForwardIterator __last2,
    _BinaryPredicate __comp)
    {
     
     
     
      ;
      ;
      for (; __first1 != __last1; ++__first1)
 for (_ForwardIterator __iter = __first2; __iter != __last2; ++__iter)
   if (__comp(*__first1, *__iter))
     return __first1;
      return __last1;
    }
  template<typename _ForwardIterator>
    _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last)
    {
     
     
      ;
      if (__first == __last)
 return __last;
      _ForwardIterator __next = __first;
      while(++__next != __last)
 {
   if (*__first == *__next)
     return __first;
   __first = __next;
 }
      return __last;
    }
  template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator
    adjacent_find(_ForwardIterator __first, _ForwardIterator __last,
    _BinaryPredicate __binary_pred)
    {
     
     
      ;
      if (__first == __last)
 return __last;
      _ForwardIterator __next = __first;
      while(++__next != __last)
 {
   if (__binary_pred(*__first, *__next))
     return __first;
   __first = __next;
 }
      return __last;
    }
  template<typename _InputIterator, typename _Tp>
    typename iterator_traits<_InputIterator>::difference_type
    count(_InputIterator __first, _InputIterator __last, const _Tp& __value)
    {
     
     
      ;
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      for (; __first != __last; ++__first)
 if (*__first == __value)
   ++__n;
      return __n;
    }
  template<typename _InputIterator, typename _Predicate>
    typename iterator_traits<_InputIterator>::difference_type
    count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
    {
     
     
      ;
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      for (; __first != __last; ++__first)
 if (__pred(*__first))
   ++__n;
      return __n;
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2)
    {
     
     
     
      ;
      ;
      if (__first1 == __last1 || __first2 == __last2)
 return __first1;
      _ForwardIterator2 __p1(__first2);
      if (++__p1 == __last2)
 return std::find(__first1, __last1, *__first2);
      _ForwardIterator2 __p;
      _ForwardIterator1 __current = __first1;
      for (;;)
 {
   __first1 = std::find(__first1, __last1, *__first2);
   if (__first1 == __last1)
     return __last1;
   __p = __p1;
   __current = __first1;
   if (++__current == __last1)
     return __last1;
   while (*__current == *__p)
     {
       if (++__p == __last2)
  return __first1;
       if (++__current == __last1)
  return __last1;
     }
   ++__first1;
 }
      return __first1;
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2,
    typename _BinaryPredicate>
    _ForwardIterator1
    search(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
    _ForwardIterator2 __first2, _ForwardIterator2 __last2,
    _BinaryPredicate __predicate)
    {
     
     
     
      ;
      ;
      if (__first1 == __last1 || __first2 == __last2)
 return __first1;
      _ForwardIterator2 __p1(__first2);
      if (++__p1 == __last2)
 {
   while (__first1 != __last1
   && !bool(__predicate(*__first1, *__first2)))
     ++__first1;
   return __first1;
 }
      _ForwardIterator2 __p;
      _ForwardIterator1 __current = __first1;
      for (;;)
 {
   while (__first1 != __last1
   && !bool(__predicate(*__first1, *__first2)))
     ++__first1;
   if (__first1 == __last1)
     return __last1;
   __p = __p1;
   __current = __first1;
   if (++__current == __last1)
     return __last1;
   while (__predicate(*__current, *__p))
     {
       if (++__p == __last2)
  return __first1;
       if (++__current == __last1)
  return __last1;
     }
   ++__first1;
 }
      return __first1;
    }
  template<typename _ForwardIterator, typename _Integer, typename _Tp>
    _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
      _Integer __count, const _Tp& __val)
    {
     
     
      ;
      if (__count <= 0)
 return __first;
      if (__count == 1)
 return std::find(__first, __last, __val);
      return std::__search_n(__first, __last, __count, __val,
        std::__iterator_category(__first));
    }
  template<typename _ForwardIterator, typename _Integer, typename _Tp,
           typename _BinaryPredicate>
    _ForwardIterator
    search_n(_ForwardIterator __first, _ForwardIterator __last,
      _Integer __count, const _Tp& __val,
      _BinaryPredicate __binary_pred)
    {
     
     
      ;
      if (__count <= 0)
 return __first;
      if (__count == 1)
 {
   while (__first != __last && !bool(__binary_pred(*__first, __val)))
     ++__first;
   return __first;
 }
      return std::__search_n(__first, __last, __count, __val, __binary_pred,
        std::__iterator_category(__first));
    }
  template<typename _InputIterator, typename _OutputIterator,
    typename _UnaryOperation>
    _OutputIterator
    transform(_InputIterator __first, _InputIterator __last,
       _OutputIterator __result, _UnaryOperation __unary_op)
    {
     
     
      ;
      for (; __first != __last; ++__first, ++__result)
 *__result = __unary_op(*__first);
      return __result;
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _BinaryOperation>
    _OutputIterator
    transform(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _OutputIterator __result,
       _BinaryOperation __binary_op)
    {
     
     
     
      ;
      for (; __first1 != __last1; ++__first1, ++__first2, ++__result)
 *__result = __binary_op(*__first1, *__first2);
      return __result;
    }
  template<typename _ForwardIterator, typename _Tp>
    void
    replace(_ForwardIterator __first, _ForwardIterator __last,
     const _Tp& __old_value, const _Tp& __new_value)
    {
     
     
     
      ;
      for (; __first != __last; ++__first)
 if (*__first == __old_value)
   *__first = __new_value;
    }
  template<typename _ForwardIterator, typename _Predicate, typename _Tp>
    void
    replace_if(_ForwardIterator __first, _ForwardIterator __last,
        _Predicate __pred, const _Tp& __new_value)
    {
     
     
     
      ;
      for (; __first != __last; ++__first)
 if (__pred(*__first))
   *__first = __new_value;
    }
  template<typename _ForwardIterator, typename _Generator>
    void
    generate(_ForwardIterator __first, _ForwardIterator __last,
      _Generator __gen)
    {
     
     
      ;
      for (; __first != __last; ++__first)
 *__first = __gen();
    }
  template<typename _OutputIterator, typename _Size, typename _Generator>
    _OutputIterator
    generate_n(_OutputIterator __first, _Size __n, _Generator __gen)
    {
     
      for (; __n > 0; --__n, ++__first)
 *__first = __gen();
      return __first;
    }
  template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result)
    {
     
     
     
      ;
      if (__first == __last)
 return __result;
      return std::__unique_copy(__first, __last, __result,
    std::__iterator_category(__first),
    std::__iterator_category(__result));
    }
  template<typename _InputIterator, typename _OutputIterator,
    typename _BinaryPredicate>
    inline _OutputIterator
    unique_copy(_InputIterator __first, _InputIterator __last,
  _OutputIterator __result,
  _BinaryPredicate __binary_pred)
    {
     
     
      ;
      if (__first == __last)
 return __result;
      return std::__unique_copy(__first, __last, __result, __binary_pred,
    std::__iterator_category(__first),
    std::__iterator_category(__result));
    }
  template<typename _RandomAccessIterator>
    inline void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
     
      ;
      if (__first != __last)
 for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
   std::iter_swap(__i, __first + (std::rand() % ((__i - __first) + 1)));
    }
  template<typename _RandomAccessIterator, typename _RandomNumberGenerator>
    void
    random_shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
     _RandomNumberGenerator& __rand)
    {
     
      ;
      if (__first == __last)
 return;
      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
 std::iter_swap(__i, __first + __rand((__i - __first) + 1));
    }
  template<typename _ForwardIterator, typename _Predicate>
    inline _ForwardIterator
    partition(_ForwardIterator __first, _ForwardIterator __last,
       _Predicate __pred)
    {
     
     
      ;
      return std::__partition(__first, __last, __pred,
         std::__iterator_category(__first));
    }
  template<typename _RandomAccessIterator>
    inline void
    partial_sort(_RandomAccessIterator __first,
   _RandomAccessIterator __middle,
   _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      std::__heap_select(__first, __middle, __last);
      std::sort_heap(__first, __middle);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    partial_sort(_RandomAccessIterator __first,
   _RandomAccessIterator __middle,
   _RandomAccessIterator __last,
   _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      std::__heap_select(__first, __middle, __last, __comp);
      std::sort_heap(__first, __middle, __comp);
    }
  template<typename _RandomAccessIterator>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
  _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      if (__first == __last || __nth == __last)
 return;
      std::__introselect(__first, __nth, __last,
    std::__lg(__last - __first) * 2);
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    nth_element(_RandomAccessIterator __first, _RandomAccessIterator __nth,
  _RandomAccessIterator __last, _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      ;
      if (__first == __last || __nth == __last)
 return;
      std::__introselect(__first, __nth, __last,
    std::__lg(__last - __first) * 2, __comp);
    }
  template<typename _RandomAccessIterator>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      if (__first != __last)
 {
   std::__introsort_loop(__first, __last,
    std::__lg(__last - __first) * 2);
   std::__final_insertion_sort(__first, __last);
 }
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
     
     
      ;
      if (__first != __last)
 {
   std::__introsort_loop(__first, __last,
    std::__lg(__last - __first) * 2, __comp);
   std::__final_insertion_sort(__first, __last, __comp);
 }
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
   _InputIterator2 __first2, _InputIterator2 __last2,
   _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (*__first2 < *__first1)
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
     }
   ++__result;
 }
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
          __result));
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    merge(_InputIterator1 __first1, _InputIterator1 __last1,
   _InputIterator2 __first2, _InputIterator2 __last2,
   _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(*__first2, *__first1))
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
     }
   ++__result;
 }
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
          __result));
    }
  template<typename _RandomAccessIterator>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
     
     
      ;
      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
         __last);
      if (__buf.begin() == 0)
 std::__inplace_stable_sort(__first, __last);
      else
 std::__stable_sort_adaptive(__first, __last, __buf.begin(),
        _DistanceType(__buf.size()));
    }
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    stable_sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
  _Compare __comp)
    {
      typedef typename iterator_traits<_RandomAccessIterator>::value_type
 _ValueType;
      typedef typename iterator_traits<_RandomAccessIterator>::difference_type
 _DistanceType;
     
     
      ;
      _Temporary_buffer<_RandomAccessIterator, _ValueType> __buf(__first,
         __last);
      if (__buf.begin() == 0)
 std::__inplace_stable_sort(__first, __last, __comp);
      else
 std::__stable_sort_adaptive(__first, __last, __buf.begin(),
        _DistanceType(__buf.size()), __comp);
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (*__first1 < *__first2)
     {
       *__result = *__first1;
       ++__first1;
     }
   else if (*__first2 < *__first1)
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
       ++__first2;
     }
   ++__result;
 }
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
          __result));
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_union(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 {
   if (__comp(*__first1, *__first2))
     {
       *__result = *__first1;
       ++__first1;
     }
   else if (__comp(*__first2, *__first1))
     {
       *__result = *__first2;
       ++__first2;
     }
   else
     {
       *__result = *__first1;
       ++__first1;
       ++__first2;
     }
   ++__result;
 }
      return std::copy(__first2, __last2, std::copy(__first1, __last1,
          __result));
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (*__first1 < *__first2)
   ++__first1;
 else if (*__first2 < *__first1)
   ++__first2;
 else
   {
     *__result = *__first1;
     ++__first1;
     ++__first2;
     ++__result;
   }
      return __result;
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_intersection(_InputIterator1 __first1, _InputIterator1 __last1,
       _InputIterator2 __first2, _InputIterator2 __last2,
       _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(*__first1, *__first2))
   ++__first1;
 else if (__comp(*__first2, *__first1))
   ++__first2;
 else
   {
     *__result = *__first1;
     ++__first1;
     ++__first2;
     ++__result;
   }
      return __result;
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (*__first1 < *__first2)
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (*__first2 < *__first1)
   ++__first2;
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first1, __last1, __result);
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_difference(_InputIterator1 __first1, _InputIterator1 __last1,
     _InputIterator2 __first2, _InputIterator2 __last2,
     _OutputIterator __result, _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(*__first1, *__first2))
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (__comp(*__first2, *__first1))
   ++__first2;
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first1, __last1, __result);
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator>
    _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _InputIterator2 __last2,
        _OutputIterator __result)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (*__first1 < *__first2)
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (*__first2 < *__first1)
   {
     *__result = *__first2;
     ++__first2;
     ++__result;
   }
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first2, __last2, std::copy(__first1,
          __last1, __result));
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _OutputIterator, typename _Compare>
    _OutputIterator
    set_symmetric_difference(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _InputIterator2 __last2,
        _OutputIterator __result,
        _Compare __comp)
    {
      typedef typename iterator_traits<_InputIterator1>::value_type
 _ValueType1;
      typedef typename iterator_traits<_InputIterator2>::value_type
 _ValueType2;
     
     
     
     
     
     
      ;
      ;
      while (__first1 != __last1 && __first2 != __last2)
 if (__comp(*__first1, *__first2))
   {
     *__result = *__first1;
     ++__first1;
     ++__result;
   }
 else if (__comp(*__first2, *__first1))
   {
     *__result = *__first2;
     ++__first2;
     ++__result;
   }
 else
   {
     ++__first1;
     ++__first2;
   }
      return std::copy(__first2, __last2,
         std::copy(__first1, __last1, __result));
    }
  template<typename _ForwardIterator>
    _ForwardIterator
    min_element(_ForwardIterator __first, _ForwardIterator __last)
    {
     
     
      ;
      if (__first == __last)
 return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (*__first < *__result)
   __result = __first;
      return __result;
    }
  template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator
    min_element(_ForwardIterator __first, _ForwardIterator __last,
  _Compare __comp)
    {
     
     
      ;
      if (__first == __last)
 return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (__comp(*__first, *__result))
   __result = __first;
      return __result;
    }
  template<typename _ForwardIterator>
    _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last)
    {
     
     
      ;
      if (__first == __last)
 return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (*__result < *__first)
   __result = __first;
      return __result;
    }
  template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator
    max_element(_ForwardIterator __first, _ForwardIterator __last,
  _Compare __comp)
    {
     
     
      ;
      if (__first == __last) return __first;
      _ForwardIterator __result = __first;
      while (++__first != __last)
 if (__comp(*__result, *__first))
   __result = __first;
      return __result;
    }
}
       
       
       
       
       
namespace std {
  template<typename _Alloc>
    class allocator;
  template<class _CharT>
    struct char_traits;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
    class basic_string;
  template<> struct char_traits<char>;
  typedef basic_string<char> string;
  template<> struct char_traits<wchar_t>;
  typedef basic_string<wchar_t> wstring;
}
       
       
       
typedef __builtin_va_list __gnuc_va_list;
extern "C" {
struct tm;
typedef _mbstate_t mbstate_t;
wint_t __attribute__((__cdecl__)) btowc (int);
int __attribute__((__cdecl__)) wctob (wint_t);
size_t __attribute__((__cdecl__)) mbrlen (const char * , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) mbrtowc (wchar_t * , const char * , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _mbrtowc_r (struct _reent *, wchar_t * , const char * , size_t, mbstate_t *);
int __attribute__((__cdecl__)) mbsinit (const mbstate_t *);
size_t __attribute__((__cdecl__)) mbsnrtowcs (wchar_t * , const char ** , size_t, size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _mbsnrtowcs_r (struct _reent *, wchar_t * , const char ** , size_t, size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) mbsrtowcs (wchar_t * , const char ** , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _mbsrtowcs_r (struct _reent *, wchar_t * , const char ** , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) wcrtomb (char * , wchar_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _wcrtomb_r (struct _reent *, char * , wchar_t, mbstate_t *);
size_t __attribute__((__cdecl__)) wcsnrtombs (char * , const wchar_t ** , size_t, size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _wcsnrtombs_r (struct _reent *, char * , const wchar_t ** , size_t, size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) wcsrtombs (char * , const wchar_t ** , size_t, mbstate_t *);
size_t __attribute__((__cdecl__)) _wcsrtombs_r (struct _reent *, char * , const wchar_t ** , size_t, mbstate_t *);
int __attribute__((__cdecl__)) wcscasecmp (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcscat (wchar_t * , const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcschr (const wchar_t *, wchar_t);
int __attribute__((__cdecl__)) wcscmp (const wchar_t *, const wchar_t *);
int __attribute__((__cdecl__)) wcscoll (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcscpy (wchar_t * , const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcpcpy (wchar_t * , const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcsdup (const wchar_t *);
wchar_t *__attribute__((__cdecl__)) _wcsdup_r (struct _reent *, const wchar_t * );
size_t __attribute__((__cdecl__)) wcscspn (const wchar_t *, const wchar_t *);
size_t __attribute__((__cdecl__)) wcsftime (wchar_t *, size_t, const wchar_t *, const struct tm *);
size_t __attribute__((__cdecl__)) wcslcat (wchar_t *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) wcslcpy (wchar_t *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) wcslen (const wchar_t *);
int __attribute__((__cdecl__)) wcsncasecmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wcsncat (wchar_t * , const wchar_t * , size_t);
int __attribute__((__cdecl__)) wcsncmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wcsncpy (wchar_t * , const wchar_t * , size_t);
wchar_t *__attribute__((__cdecl__)) wcpncpy (wchar_t * , const wchar_t * , size_t);
size_t __attribute__((__cdecl__)) wcsnlen (const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wcspbrk (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcsrchr (const wchar_t *, wchar_t);
size_t __attribute__((__cdecl__)) wcsspn (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcsstr (const wchar_t *, const wchar_t *);
wchar_t *__attribute__((__cdecl__)) wcstok (wchar_t *, const wchar_t *, wchar_t **);
double __attribute__((__cdecl__)) wcstod (const wchar_t *, wchar_t **);
double __attribute__((__cdecl__)) _wcstod_r (struct _reent *, const wchar_t *, wchar_t **);
float __attribute__((__cdecl__)) wcstof (const wchar_t *, wchar_t **);
float __attribute__((__cdecl__)) _wcstof_r (struct _reent *, const wchar_t *, wchar_t **);
int __attribute__((__cdecl__)) wcswidth (const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) wcsxfrm (wchar_t *, const wchar_t *, size_t);
int __attribute__((__cdecl__)) wcwidth (const wchar_t);
wchar_t *__attribute__((__cdecl__)) wmemchr (const wchar_t *, wchar_t, size_t);
int __attribute__((__cdecl__)) wmemcmp (const wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wmemcpy (wchar_t * , const wchar_t * , size_t);
wchar_t *__attribute__((__cdecl__)) wmemmove (wchar_t *, const wchar_t *, size_t);
wchar_t *__attribute__((__cdecl__)) wmemset (wchar_t *, wchar_t, size_t);
long __attribute__((__cdecl__)) wcstol (const wchar_t *, wchar_t **, int);
long long __attribute__((__cdecl__)) wcstoll (const wchar_t *, wchar_t **, int);
unsigned long __attribute__((__cdecl__)) wcstoul (const wchar_t *, wchar_t **, int);
unsigned long long __attribute__((__cdecl__)) wcstoull (const wchar_t *, wchar_t **, int);
long __attribute__((__cdecl__)) _wcstol_r (struct _reent *, const wchar_t *, wchar_t **, int);
long long __attribute__((__cdecl__)) _wcstoll_r (struct _reent *, const wchar_t *, wchar_t **, int);
unsigned long __attribute__((__cdecl__)) _wcstoul_r (struct _reent *, const wchar_t *, wchar_t **, int);
unsigned long long __attribute__((__cdecl__)) _wcstoull_r (struct _reent *, const wchar_t *, wchar_t **, int);
wint_t __attribute__((__cdecl__)) fgetwc (__FILE *);
wchar_t *__attribute__((__cdecl__)) fgetws (wchar_t *, int, __FILE *);
wint_t __attribute__((__cdecl__)) fputwc (wchar_t, __FILE *);
int __attribute__((__cdecl__)) fputws (const wchar_t *, __FILE *);
int __attribute__((__cdecl__)) fwide (__FILE *, int);
wint_t __attribute__((__cdecl__)) getwc (__FILE *);
wint_t __attribute__((__cdecl__)) getwchar (void);
wint_t __attribute__((__cdecl__)) putwc (wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) putwchar (wchar_t);
wint_t __attribute__((__cdecl__)) ungetwc (wint_t wc, __FILE *);
wint_t __attribute__((__cdecl__)) _fgetwc_r (struct _reent *, __FILE *);
wchar_t *__attribute__((__cdecl__)) _fgetws_r (struct _reent *, wchar_t *, int, __FILE *);
wint_t __attribute__((__cdecl__)) _fputwc_r (struct _reent *, wchar_t, __FILE *);
int __attribute__((__cdecl__)) _fputws_r (struct _reent *, const wchar_t *, __FILE *);
int __attribute__((__cdecl__)) _fwide_r (struct _reent *, __FILE *, int);
wint_t __attribute__((__cdecl__)) _getwc_r (struct _reent *, __FILE *);
wint_t __attribute__((__cdecl__)) _getwchar_r (struct _reent *ptr);
wint_t __attribute__((__cdecl__)) _putwc_r (struct _reent *, wchar_t, __FILE *);
wint_t __attribute__((__cdecl__)) _putwchar_r (struct _reent *, wchar_t);
wint_t __attribute__((__cdecl__)) _ungetwc_r (struct _reent *, wint_t wc, __FILE *);
__FILE *__attribute__((__cdecl__)) open_wmemstream (wchar_t **, size_t *);
__FILE *__attribute__((__cdecl__)) _open_wmemstream_r (struct _reent *, wchar_t **, size_t *);
int __attribute__((__cdecl__)) fwprintf (__FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) swprintf (wchar_t *, size_t, const wchar_t *, ...);
int __attribute__((__cdecl__)) vfwprintf (__FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) vswprintf (wchar_t *, size_t, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) vwprintf (const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) wprintf (const wchar_t *, ...);
int __attribute__((__cdecl__)) _fwprintf_r (struct _reent *, __FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _swprintf_r (struct _reent *, wchar_t *, size_t, const wchar_t *, ...);
int __attribute__((__cdecl__)) _vfwprintf_r (struct _reent *, __FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vswprintf_r (struct _reent *, wchar_t *, size_t, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vwprintf_r (struct _reent *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _wprintf_r (struct _reent *, const wchar_t *, ...);
int __attribute__((__cdecl__)) fwscanf (__FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) swscanf (const wchar_t *, const wchar_t *, ...);
int __attribute__((__cdecl__)) vfwscanf (__FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) vswscanf (const wchar_t *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) vwscanf (const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) wscanf (const wchar_t *, ...);
int __attribute__((__cdecl__)) _fwscanf_r (struct _reent *, __FILE *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _swscanf_r (struct _reent *, const wchar_t *, const wchar_t *, ...);
int __attribute__((__cdecl__)) _vfwscanf_r (struct _reent *, __FILE *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vswscanf_r (struct _reent *, const wchar_t *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _vwscanf_r (struct _reent *, const wchar_t *, __gnuc_va_list);
int __attribute__((__cdecl__)) _wscanf_r (struct _reent *, const wchar_t *, ...);
}
namespace std {
  using ::mbstate_t;
}
namespace std {
  using ::wint_t;
  using ::btowc;
  using ::fgetwc;
  using ::fgetws;
  using ::fputwc;
  using ::fputws;
  using ::fwide;
  using ::fwprintf;
  using ::fwscanf;
  using ::getwc;
  using ::getwchar;
  using ::mbrlen;
  using ::mbrtowc;
  using ::mbsinit;
  using ::mbsrtowcs;
  using ::putwc;
  using ::putwchar;
  using ::swprintf;
  using ::swscanf;
  using ::ungetwc;
  using ::vfwprintf;
  using ::vfwscanf;
  using ::vswprintf;
  using ::vswscanf;
  using ::vwprintf;
  using ::vwscanf;
  using ::wcrtomb;
  using ::wcscat;
  using ::wcscmp;
  using ::wcscoll;
  using ::wcscpy;
  using ::wcscspn;
  using ::wcsftime;
  using ::wcslen;
  using ::wcsncat;
  using ::wcsncmp;
  using ::wcsncpy;
  using ::wcsrtombs;
  using ::wcsspn;
  using ::wcstod;
  using ::wcstof;
  using ::wcstok;
  using ::wcstol;
  using ::wcstoul;
  using ::wcsxfrm;
  using ::wctob;
  using ::wmemcmp;
  using ::wmemcpy;
  using ::wmemmove;
  using ::wmemset;
  using ::wprintf;
  using ::wscanf;
  using ::wcschr;
  using ::wcspbrk;
  using ::wcsrchr;
  using ::wcsstr;
  using ::wmemchr;
  inline wchar_t*
  wcschr(wchar_t* __p, wchar_t __c)
  { return wcschr(const_cast<const wchar_t*>(__p), __c); }
  inline wchar_t*
  wcspbrk(wchar_t* __s1, const wchar_t* __s2)
  { return wcspbrk(const_cast<const wchar_t*>(__s1), __s2); }
  inline wchar_t*
  wcsrchr(wchar_t* __p, wchar_t __c)
  { return wcsrchr(const_cast<const wchar_t*>(__p), __c); }
  inline wchar_t*
  wcsstr(wchar_t* __s1, const wchar_t* __s2)
  { return wcsstr(const_cast<const wchar_t*>(__s1), __s2); }
  inline wchar_t*
  wmemchr(wchar_t* __p, wchar_t __c, size_t __n)
  { return wmemchr(const_cast<const wchar_t*>(__p), __c, __n); }
}
namespace std {
  typedef long long streamoff;
  typedef ptrdiff_t streamsize;
  template<typename _StateT>
    class fpos
    {
    private:
      streamoff _M_off;
      _StateT _M_state;
    public:
      fpos()
      : _M_off(0), _M_state() { }
      fpos(streamoff __off)
      : _M_off(__off), _M_state() { }
      operator streamoff() const { return _M_off; }
      void
      state(_StateT __st)
      { _M_state = __st; }
      _StateT
      state() const
      { return _M_state; }
      fpos&
      operator+=(streamoff __off)
      {
 _M_off += __off;
 return *this;
      }
      fpos&
      operator-=(streamoff __off)
      {
 _M_off -= __off;
 return *this;
      }
      fpos
      operator+(streamoff __off) const
      {
 fpos __pos(*this);
 __pos += __off;
 return __pos;
      }
      fpos
      operator-(streamoff __off) const
      {
 fpos __pos(*this);
 __pos -= __off;
 return __pos;
      }
      streamoff
      operator-(const fpos& __other) const
      { return _M_off - __other._M_off; }
    };
  template<typename _StateT>
    inline bool
    operator==(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) == streamoff(__rhs); }
  template<typename _StateT>
    inline bool
    operator!=(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) != streamoff(__rhs); }
  typedef fpos<mbstate_t> streampos;
  typedef fpos<mbstate_t> wstreampos;
}
namespace std {
  class ios_base;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ios;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_streambuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_istream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ostream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_iostream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
     typename _Alloc = allocator<_CharT> >
    class basic_stringbuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_istringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_ostringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_stringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_filebuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ifstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ofstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_fstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class istreambuf_iterator;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class ostreambuf_iterator;
  typedef basic_ios<char> ios;
  typedef basic_streambuf<char> streambuf;
  typedef basic_istream<char> istream;
  typedef basic_ostream<char> ostream;
  typedef basic_iostream<char> iostream;
  typedef basic_stringbuf<char> stringbuf;
  typedef basic_istringstream<char> istringstream;
  typedef basic_ostringstream<char> ostringstream;
  typedef basic_stringstream<char> stringstream;
  typedef basic_filebuf<char> filebuf;
  typedef basic_ifstream<char> ifstream;
  typedef basic_ofstream<char> ofstream;
  typedef basic_fstream<char> fstream;
  typedef basic_ios<wchar_t> wios;
  typedef basic_streambuf<wchar_t> wstreambuf;
  typedef basic_istream<wchar_t> wistream;
  typedef basic_ostream<wchar_t> wostream;
  typedef basic_iostream<wchar_t> wiostream;
  typedef basic_stringbuf<wchar_t> wstringbuf;
  typedef basic_istringstream<wchar_t> wistringstream;
  typedef basic_ostringstream<wchar_t> wostringstream;
  typedef basic_stringstream<wchar_t> wstringstream;
  typedef basic_filebuf<wchar_t> wfilebuf;
  typedef basic_ifstream<wchar_t> wifstream;
  typedef basic_ofstream<wchar_t> wofstream;
  typedef basic_fstream<wchar_t> wfstream;
}
       
       
       
namespace __gnu_cxx {
  template<typename _CharT>
    struct _Char_types
    {
      typedef unsigned long int_type;
      typedef std::streampos pos_type;
      typedef std::streamoff off_type;
      typedef std::mbstate_t state_type;
    };
  template<typename _CharT>
    struct char_traits
    {
      typedef _CharT char_type;
      typedef typename _Char_types<_CharT>::int_type int_type;
      typedef typename _Char_types<_CharT>::pos_type pos_type;
      typedef typename _Char_types<_CharT>::off_type off_type;
      typedef typename _Char_types<_CharT>::state_type state_type;
      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }
      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }
      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, std::size_t __n);
      static std::size_t
      length(const char_type* __s);
      static const char_type*
      find(const char_type* __s, std::size_t __n, const char_type& __a);
      static char_type*
      move(char_type* __s1, const char_type* __s2, std::size_t __n);
      static char_type*
      copy(char_type* __s1, const char_type* __s2, std::size_t __n);
      static char_type*
      assign(char_type* __s, std::size_t __n, char_type __a);
      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }
      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(__c); }
      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }
      static int_type
      eof()
      { return static_cast<int_type>((-1)); }
      static int_type
      not_eof(const int_type& __c)
      { return !eq_int_type(__c, eof()) ? __c : to_int_type(char_type()); }
    };
  template<typename _CharT>
    int
    char_traits<_CharT>::
    compare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
 if (lt(__s1[__i], __s2[__i]))
   return -1;
 else if (lt(__s2[__i], __s1[__i]))
   return 1;
      return 0;
    }
  template<typename _CharT>
    std::size_t
    char_traits<_CharT>::
    length(const char_type* __p)
    {
      std::size_t __i = 0;
      while (!eq(__p[__i], char_type()))
        ++__i;
      return __i;
    }
  template<typename _CharT>
    const typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    find(const char_type* __s, std::size_t __n, const char_type& __a)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
        if (eq(__s[__i], __a))
          return __s + __i;
      return 0;
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    move(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      return static_cast<_CharT*>(__builtin_memmove(__s1, __s2,
          __n * sizeof(char_type)));
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    copy(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      std::copy(__s2, __s2 + __n, __s1);
      return __s1;
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    assign(char_type* __s, std::size_t __n, char_type __a)
    {
      std::fill_n(__s, __n, __a);
      return __s;
    }
}
namespace std {
  template<class _CharT>
    struct char_traits : public __gnu_cxx::char_traits<_CharT>
    { };
  template<>
    struct char_traits<char>
    {
      typedef char char_type;
      typedef int int_type;
      typedef streampos pos_type;
      typedef streamoff off_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }
      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }
      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return __builtin_memcmp(__s1, __s2, __n); }
      static size_t
      length(const char_type* __s)
      { return __builtin_strlen(__s); }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return static_cast<const char_type*>(__builtin_memchr(__s, __a, __n)); }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n)); }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n)); }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return static_cast<char_type*>(__builtin_memset(__s, __a, __n)); }
      static char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }
      static int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(static_cast<unsigned char>(__c)); }
      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }
      static int_type
      eof()
      { return static_cast<int_type>((-1)); }
      static int_type
      not_eof(const int_type& __c)
      { return (__c == eof()) ? 0 : __c; }
  };
  template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t char_type;
      typedef wint_t int_type;
      typedef streamoff off_type;
      typedef wstreampos pos_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }
      static bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }
      static bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcmp(__s1, __s2, __n); }
      static size_t
      length(const char_type* __s)
      { return wcslen(__s); }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return wmemchr(__s, __a, __n); }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemmove(__s1, __s2, __n); }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcpy(__s1, __s2, __n); }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return wmemset(__s, __a, __n); }
      static char_type
      to_char_type(const int_type& __c)
      { return char_type(__c); }
      static int_type
      to_int_type(const char_type& __c)
      { return int_type(__c); }
      static bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }
      static int_type
      eof()
      { return static_cast<int_type>(((wint_t)-1)); }
      static int_type
      not_eof(const int_type& __c)
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };
}
       
       
       
extern "C" {
struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_n_cs_precedes;
  char int_n_sep_by_space;
  char int_n_sign_posn;
  char int_p_cs_precedes;
  char int_p_sep_by_space;
  char int_p_sign_posn;
};
char *__attribute__((__cdecl__)) setlocale (int category, const char *locale);
struct lconv *__attribute__((__cdecl__)) localeconv (void);
struct _reent;
char *__attribute__((__cdecl__)) _setlocale_r (struct _reent *, int category, const char *locale);
struct lconv *__attribute__((__cdecl__)) _localeconv_r (struct _reent *);
}
namespace std {
  using ::lconv;
  using ::setlocale;
  using ::localeconv;
}
       
namespace std {
  typedef int* __c_locale;
  inline int
  __convert_from_v(const __c_locale&, char* __out,
     const int __size __attribute__((__unused__)),
     const char* __fmt, ...)
  {
    char* __old = std::setlocale(4, __null);
    char* __sav = __null;
    if (__builtin_strcmp(__old, "C"))
      {
 const size_t __len = __builtin_strlen(__old) + 1;
 __sav = new char[__len];
 __builtin_memcpy(__sav, __old, __len);
 std::setlocale(4, "C");
      }
    __builtin_va_list __args;
    __builtin_va_start(__args, __fmt);
    const int __ret = __builtin_vsprintf(__out, __fmt, __args);
    __builtin_va_end(__args);
    if (__sav)
      {
 std::setlocale(4, __sav);
 delete [] __sav;
      }
    return __ret;
  }
}
       
extern "C" {
int __attribute__((__cdecl__)) isalnum (int __c);
int __attribute__((__cdecl__)) isalpha (int __c);
int __attribute__((__cdecl__)) iscntrl (int __c);
int __attribute__((__cdecl__)) isdigit (int __c);
int __attribute__((__cdecl__)) isgraph (int __c);
int __attribute__((__cdecl__)) islower (int __c);
int __attribute__((__cdecl__)) isprint (int __c);
int __attribute__((__cdecl__)) ispunct (int __c);
int __attribute__((__cdecl__)) isspace (int __c);
int __attribute__((__cdecl__)) isupper (int __c);
int __attribute__((__cdecl__)) isxdigit (int __c);
int __attribute__((__cdecl__)) tolower (int __c);
int __attribute__((__cdecl__)) toupper (int __c);
int __attribute__((__cdecl__)) isblank (int __c);
int __attribute__((__cdecl__)) isascii (int __c);
int __attribute__((__cdecl__)) toascii (int __c);
extern __attribute__((dllimport)) char *__ctype_ptr__;
extern __attribute__((dllimport)) const char _ctype_[];
}
namespace std {
  using ::isalnum;
  using ::isalpha;
  using ::iscntrl;
  using ::isdigit;
  using ::isgraph;
  using ::islower;
  using ::isprint;
  using ::ispunct;
  using ::isspace;
  using ::isupper;
  using ::isxdigit;
  using ::tolower;
  using ::toupper;
}
namespace std {
  class locale;
  template<typename _Facet>
    bool
    has_facet(const locale&) throw();
  template<typename _Facet>
    const _Facet&
    use_facet(const locale&);
  template<typename _CharT>
    bool
    isspace(_CharT, const locale&);
  template<typename _CharT>
    bool
    isprint(_CharT, const locale&);
  template<typename _CharT>
    bool
    iscntrl(_CharT, const locale&);
  template<typename _CharT>
    bool
    isupper(_CharT, const locale&);
  template<typename _CharT>
    bool
    islower(_CharT, const locale&);
  template<typename _CharT>
    bool
    isalpha(_CharT, const locale&);
  template<typename _CharT>
    bool
    isdigit(_CharT, const locale&);
  template<typename _CharT>
    bool
    ispunct(_CharT, const locale&);
  template<typename _CharT>
    bool
    isxdigit(_CharT, const locale&);
  template<typename _CharT>
    bool
    isalnum(_CharT, const locale&);
  template<typename _CharT>
    bool
    isgraph(_CharT, const locale&);
  template<typename _CharT>
    _CharT
    toupper(_CharT, const locale&);
  template<typename _CharT>
    _CharT
    tolower(_CharT, const locale&);
  class ctype_base;
  template<typename _CharT>
    class ctype;
  template<> class ctype<char>;
  template<> class ctype<wchar_t>;
  template<typename _CharT>
    class ctype_byname;
  class codecvt_base;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt;
  template<> class codecvt<char, char, mbstate_t>;
  template<> class codecvt<wchar_t, char, mbstate_t>;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt_byname;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class num_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class num_put;

  template<typename _CharT> class numpunct;
  template<typename _CharT> class numpunct_byname;
  template<typename _CharT>
    class collate;
  template<typename _CharT> class
    collate_byname;
  class time_base;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get_byname;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put_byname;
  class money_base;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class money_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class money_put;

  template<typename _CharT, bool _Intl = false>
    class moneypunct;
  template<typename _CharT, bool _Intl = false>
    class moneypunct_byname;
  class messages_base;
  template<typename _CharT>
    class messages;
  template<typename _CharT>
    class messages_byname;
}
       
#pragma GCC visibility push(default)
extern "C" {
typedef unsigned long sigset_t;
extern "C" {
struct _fpstate
{
  unsigned long cw;
  unsigned long sw;
  unsigned long tag;
  unsigned long ipoff;
  unsigned long cssel;
  unsigned long dataoff;
  unsigned long datasel;
  unsigned char _st[80];
  unsigned long nxst;
};
struct ucontext
{
  unsigned long cr2;
  unsigned long dr0;
  unsigned long dr1;
  unsigned long dr2;
  unsigned long dr3;
  unsigned long dr6;
  unsigned long dr7;
  struct _fpstate fpstate;
  unsigned long gs;
  unsigned long fs;
  unsigned long es;
  unsigned long ds;
  unsigned long edi;
  unsigned long esi;
  unsigned long ebx;
  unsigned long edx;
  unsigned long ecx;
  unsigned long eax;
  unsigned long ebp;
  unsigned long eip;
  unsigned long cs;
  unsigned long eflags;
  unsigned long esp;
  unsigned long ss;
  unsigned char _internal;
  unsigned long oldmask;
};
typedef union sigval
{
  int sival_int;
  void *sival_ptr;
} sigval_t;
typedef struct sigevent
{
  sigval_t sigev_value;
  int sigev_signo;
  int sigev_notify;
  void (*sigev_notify_function) (sigval_t);
  pthread_attr_t *sigev_notify_attributes;
} sigevent_t;
#pragma pack(push,4)
struct _sigcommune
{
  __uint32_t _si_code;
  void *_si_read_handle;
  void *_si_write_handle;
  void *_si_process_handle;
  __extension__ union
  {
    int _si_fd;
    void *_si_pipe_fhandler;
    char *_si_str;
  };
};
typedef struct
{
  int si_signo;
  int si_code;
  pid_t si_pid;
  uid_t si_uid;
  int si_errno;
  __extension__ union
  {
    __uint32_t __pad[32];
    struct _sigcommune _si_commune;
    __extension__ union
    {
      struct
      {
 union
 {
   struct
   {
     timer_t si_tid;
     unsigned int si_overrun;
   };
   sigval_t si_sigval;
   sigval_t si_value;
 };
      };
    };
    __extension__ struct
    {
      int si_status;
      clock_t si_utime;
      clock_t si_stime;
    };
    void *si_addr;
  };
} siginfo_t;
#pragma pack(pop)
enum
{
  SI_USER = 0,
  SI_ASYNCIO = 2,
  SI_MESGQ,
  SI_TIMER,
  SI_QUEUE,
  SI_KERNEL,
  ILL_ILLOPC,
  ILL_ILLOPN,
  ILL_ILLADR,
  ILL_ILLTRP,
  ILL_PRVOPC,
  ILL_PRVREG,
  ILL_COPROC,
  ILL_BADSTK,
  FPE_INTDIV,
  FPE_INTOVF,
  FPE_FLTDIV,
  FPE_FLTOVF,
  FPE_FLTUND,
  FPE_FLTRES,
  FPE_FLTINV,
  FPE_FLTSUB,
  SEGV_MAPERR,
  SEGV_ACCERR,
  BUS_ADRALN,
  BUS_ADRERR,
  BUS_OBJERR,
  CLD_EXITED,
  CLD_KILLED,
  CLD_DUMPED,
  CLD_TRAPPED,
  CLD_STOPPED,
  CLD_CONTINUED
};
enum
{
  SIGEV_SIGNAL = 0,
  SIGEV_NONE,
  SIGEV_THREAD
};
typedef void (*_sig_func_ptr)(int);
struct sigaction
{
  __extension__ union
  {
    _sig_func_ptr sa_handler;
    void (*sa_sigaction) ( int, siginfo_t *, void * );
  };
  sigset_t sa_mask;
  int sa_flags;
};
int sigwait (const sigset_t *, int *);
int sigwaitinfo (const sigset_t *, siginfo_t *);
int sighold (int);
int sigignore (int);
int sigrelse (int);
_sig_func_ptr sigset (int, _sig_func_ptr);
int sigqueue(pid_t, int, const union sigval);
int siginterrupt (int, int);
extern const char __attribute__((dllimport)) *sys_sigabbrev[];
}
int __attribute__((__cdecl__)) sigprocmask (int how, const sigset_t *set, sigset_t *oset);
int __attribute__((__cdecl__)) pthread_sigmask (int how, const sigset_t *set, sigset_t *oset);
int __attribute__((__cdecl__)) kill (pid_t, int);
int __attribute__((__cdecl__)) killpg (pid_t, int);
int __attribute__((__cdecl__)) sigaction (int, const struct sigaction *, struct sigaction *);
int __attribute__((__cdecl__)) sigaddset (sigset_t *, const int);
int __attribute__((__cdecl__)) sigdelset (sigset_t *, const int);
int __attribute__((__cdecl__)) sigismember (const sigset_t *, int);
int __attribute__((__cdecl__)) sigfillset (sigset_t *);
int __attribute__((__cdecl__)) sigemptyset (sigset_t *);
int __attribute__((__cdecl__)) sigpending (sigset_t *);
int __attribute__((__cdecl__)) sigsuspend (const sigset_t *);
int __attribute__((__cdecl__)) sigpause (int);
int __attribute__((__cdecl__)) pthread_kill (pthread_t thread, int sig);
int __attribute__((__cdecl__)) sigwaitinfo (const sigset_t *set, siginfo_t *info);
int __attribute__((__cdecl__)) sigtimedwait (const sigset_t *set, siginfo_t *info, const struct timespec *timeout);
int __attribute__((__cdecl__)) sigwait (const sigset_t *set, int *sig);
int __attribute__((__cdecl__)) sigqueue (pid_t pid, int signo, const union sigval value);
}
extern "C" {
typedef int sig_atomic_t;
typedef _sig_func_ptr sig_t;
typedef _sig_func_ptr sighandler_t;
struct _reent;
_sig_func_ptr __attribute__((__cdecl__)) _signal_r (struct _reent *, int, _sig_func_ptr);
int __attribute__((__cdecl__)) _raise_r (struct _reent *, int);
_sig_func_ptr __attribute__((__cdecl__)) signal (int, _sig_func_ptr);
int __attribute__((__cdecl__)) raise (int);
}
extern "C" {
struct sched_param {
  int sched_priority;
};
}
extern "C" {
int sched_setparam(
  pid_t __pid,
  const struct sched_param *__param
);
int sched_getparam(
  pid_t __pid,
  struct sched_param *__param
);
int sched_setscheduler(
  pid_t __pid,
  int __policy,
  const struct sched_param *__param
);
int sched_getscheduler(
  pid_t __pid
);
int sched_get_priority_max(
  int __policy
);
int sched_get_priority_min(
  int __policy
);
int sched_rr_get_interval(
  pid_t __pid,
  struct timespec *__interval
);
int sched_yield( void );
}
extern "C"
{
int pthread_attr_destroy (pthread_attr_t *);
int pthread_attr_getdetachstate (const pthread_attr_t *, int *);
int pthread_attr_getinheritsched (const pthread_attr_t *, int *);
int pthread_attr_getschedparam (const pthread_attr_t *, struct sched_param *);
int pthread_attr_getschedpolicy (const pthread_attr_t *, int *);
int pthread_attr_getscope (const pthread_attr_t *, int *);
int pthread_attr_init (pthread_attr_t *);
int pthread_attr_setdetachstate (pthread_attr_t *, int);
int pthread_attr_setinheritsched (pthread_attr_t *, int);
int pthread_attr_setschedparam (pthread_attr_t *, const struct sched_param *);
int pthread_attr_setschedpolicy (pthread_attr_t *, int);
int pthread_attr_setscope (pthread_attr_t *, int);
int pthread_attr_getstacksize (const pthread_attr_t *, size_t *);
int pthread_attr_setstacksize (pthread_attr_t *, size_t);
int pthread_cancel (pthread_t);
typedef void (*__cleanup_routine_type) (void *);
typedef struct _pthread_cleanup_handler
{
  __cleanup_routine_type function;
  void *arg;
  struct _pthread_cleanup_handler *next;
} __pthread_cleanup_handler;
void _pthread_cleanup_push (__pthread_cleanup_handler *handler);
void _pthread_cleanup_pop (int execute);
int pthread_cond_broadcast (pthread_cond_t *);
int pthread_cond_destroy (pthread_cond_t *);
int pthread_cond_init (pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_signal (pthread_cond_t *);
int pthread_cond_timedwait (pthread_cond_t *,
       pthread_mutex_t *, const struct timespec *);
int pthread_cond_wait (pthread_cond_t *, pthread_mutex_t *);
int pthread_condattr_destroy (pthread_condattr_t *);
int pthread_condattr_getpshared (const pthread_condattr_t *, int *);
int pthread_condattr_init (pthread_condattr_t *);
int pthread_condattr_setpshared (pthread_condattr_t *, int);
int pthread_create (pthread_t *, const pthread_attr_t *,
      void *(*)(void *), void *);
int pthread_detach (pthread_t);
int pthread_equal (pthread_t, pthread_t);
void pthread_exit (void *);
int pthread_getschedparam (pthread_t, int *, struct sched_param *);
void *pthread_getspecific (pthread_key_t);
int pthread_join (pthread_t, void **);
int pthread_key_create (pthread_key_t *, void (*)(void *));
int pthread_key_delete (pthread_key_t);
int pthread_mutex_destroy (pthread_mutex_t *);
int pthread_mutex_getprioceiling (const pthread_mutex_t *, int *);
int pthread_mutex_init (pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock (pthread_mutex_t *);
int pthread_mutex_setprioceiling (pthread_mutex_t *, int, int *);
int pthread_mutex_trylock (pthread_mutex_t *);
int pthread_mutex_unlock (pthread_mutex_t *);
int pthread_mutexattr_destroy (pthread_mutexattr_t *);
int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_getpshared (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_gettype (const pthread_mutexattr_t *, int *);
int pthread_mutexattr_init (pthread_mutexattr_t *);
int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *, int);
int pthread_mutexattr_setprotocol (pthread_mutexattr_t *, int);
int pthread_mutexattr_setpshared (pthread_mutexattr_t *, int);
int pthread_mutexattr_settype (pthread_mutexattr_t *, int);
int pthread_rwlock_destroy (pthread_rwlock_t *rwlock);
int pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock (pthread_rwlock_t *rwlock);
int pthread_rwlockattr_init (pthread_rwlockattr_t *rwlockattr);
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr,
       int *pshared);
int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared);
int pthread_rwlockattr_destroy (pthread_rwlockattr_t *rwlockattr);
int pthread_once (pthread_once_t *, void (*)(void));
int pthread_getconcurrency (void);
int pthread_setconcurrency (int);
pthread_t pthread_self (void);
int pthread_setcancelstate (int, int *);
int pthread_setcanceltype (int, int *);
int pthread_setschedparam (pthread_t, int, const struct sched_param *);
int pthread_setspecific (pthread_key_t, const void *);
void pthread_testcancel (void);
int pthread_suspend (pthread_t);
int pthread_continue (pthread_t);
int pthread_yield (void);
}
typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;

























static inline int
__gthread_active_p (void)
{
  return 1;
}
static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
    void *__args)
{
  return pthread_create (__threadid, __null, __func, __args);
}
static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return pthread_join (__threadid, __value_ptr);
}
static inline int
__gthread_detach (__gthread_t __threadid)
{
  return pthread_detach (__threadid);
}
static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return pthread_equal (__t1, __t2);
}
static inline __gthread_t
__gthread_self (void)
{
  return pthread_self ();
}
static inline int
__gthread_yield (void)
{
  return sched_yield ();
}
static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (__gthread_active_p ())
    return pthread_once (__once, __func);
  else
    return -1;
}
static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return pthread_key_create (__key, __dtor);
}
static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return pthread_key_delete (__key);
}
static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return pthread_getspecific (__key);
}
static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return pthread_setspecific (__key, __ptr);
}
static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_destroy (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_lock (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_trylock (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return pthread_mutex_unlock (__mutex);
  else
    return 0;
}
static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_lock (__mutex);
}
static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_trylock (__mutex);
}
static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_unlock (__mutex);
}
static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return pthread_cond_broadcast (__cond);
}
static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return pthread_cond_signal (__cond);
}
static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return pthread_cond_wait (__cond, __mutex);
}
static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
     const __gthread_time_t *__abs_timeout)
{
  return pthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}
static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
          __gthread_recursive_mutex_t *__mutex)
{
  return __gthread_cond_wait (__cond, __mutex);
}
static inline int
__gthread_cond_timedwait_recursive (__gthread_cond_t *__cond,
        __gthread_recursive_mutex_t *__mutex,
        const __gthread_time_t *__abs_timeout)
{
  return __gthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}
static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  return pthread_cond_destroy (__cond);
}
#pragma GCC visibility pop
typedef int _Atomic_word;
namespace __gnu_cxx {
  static inline _Atomic_word
  __exchange_and_add(volatile _Atomic_word* __mem, int __val)
  { return __sync_fetch_and_add(__mem, __val); }
  static inline void
  __atomic_add(volatile _Atomic_word* __mem, int __val)
  { __sync_fetch_and_add(__mem, __val); }
  static inline _Atomic_word
  __exchange_and_add_single(_Atomic_word* __mem, int __val)
  {
    _Atomic_word __result = *__mem;
    *__mem += __val;
    return __result;
  }
  static inline void
  __atomic_add_single(_Atomic_word* __mem, int __val)
  { *__mem += __val; }
  static inline _Atomic_word
  __attribute__ ((__unused__))
  __exchange_and_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      return __exchange_and_add(__mem, __val);
    else
      return __exchange_and_add_single(__mem, __val);
  }
  static inline void
  __attribute__ ((__unused__))
  __atomic_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      __atomic_add(__mem, __val);
    else
      __atomic_add_single(__mem, __val);
  }
}
       
       
namespace __gnu_cxx {
  using std::size_t;
  using std::ptrdiff_t;
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;
      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };
      new_allocator() throw() { }
      new_allocator(const new_allocator&) throw() { }
      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) throw() { }
      ~new_allocator() throw() { }
      pointer
      address(reference __x) const { return &__x; }
      const_pointer
      address(const_reference __x) const { return &__x; }
      pointer
      allocate(size_type __n, const void* = 0)
      {
 if (__n > this->max_size())
   std::__throw_bad_alloc();
 return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }
      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }
      size_type
      max_size() const throw()
      { return size_t(-1) / sizeof(_Tp); }
      void
      construct(pointer __p, const _Tp& __val)
      { ::new((void *)__p) _Tp(__val); }
      void
      destroy(pointer __p) { __p->~_Tp(); }
    };
  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }
  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }
}
namespace std {
  template<typename _Tp>
    class allocator;
  template<>
    class allocator<void>
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef void* pointer;
      typedef const void* const_pointer;
      typedef void value_type;
      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
    };
  template<typename _Tp>
    class allocator: public __gnu_cxx::new_allocator<_Tp>
    {
   public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;
      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
      allocator() throw() { }
      allocator(const allocator& __a) throw()
      : __gnu_cxx::new_allocator<_Tp>(__a) { }
      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }
      ~allocator() throw() { }
    };
  template<typename _T1, typename _T2>
    inline bool
    operator==(const allocator<_T1>&, const allocator<_T2>&)
    { return true; }
  template<typename _Tp>
    inline bool
    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
    { return true; }
  template<typename _T1, typename _T2>
    inline bool
    operator!=(const allocator<_T1>&, const allocator<_T2>&)
    { return false; }
  template<typename _Tp>
    inline bool
    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
    { return false; }
  extern template class allocator<char>;
  extern template class allocator<wchar_t>;
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_swap
    { static void _S_do_it(_Alloc&, _Alloc&) { } };
  template<typename _Alloc>
    struct __alloc_swap<_Alloc, false>
    {
      static void
      _S_do_it(_Alloc& __one, _Alloc& __two)
      {
 if (__one != __two)
   swap(__one, __two);
      }
    };
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_neq
    {
      static bool
      _S_do_it(const _Alloc&, const _Alloc&)
      { return false; }
    };
  template<typename _Alloc>
    struct __alloc_neq<_Alloc, false>
    {
      static bool
      _S_do_it(const _Alloc& __one, const _Alloc& __two)
      { return __one != __two; }
    };
}
       
       
#pragma GCC visibility push(default)
namespace __cxxabiv1
{
  class __forced_unwind
  {
    virtual ~__forced_unwind() throw();
    virtual void __pure_dummy() = 0;
  };
}
#pragma GCC visibility pop
namespace std {
  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& __out,
      const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      const streamsize __put = __out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
 __out.setstate(__ios_base::badbit);
    }
  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& __out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      const _CharT __c = __out.fill();
      for (; __n > 0; --__n)
 {
   const typename _Traits::int_type __put = __out.rdbuf()->sputc(__c);
   if (_Traits::eq_int_type(__put, _Traits::eof()))
     {
       __out.setstate(__ios_base::badbit);
       break;
     }
 }
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& __out,
       const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      typename __ostream_type::sentry __cerb(__out);
      if (__cerb)
 {
   try
     {
       const streamsize __w = __out.width();
       if (__w > __n)
  {
    const bool __left = ((__out.flags()
     & __ios_base::adjustfield)
           == __ios_base::left);
    if (!__left)
      __ostream_fill(__out, __w - __n);
    if (__out.good())
      __ostream_write(__out, __s, __n);
    if (__left && __out.good())
      __ostream_fill(__out, __w - __n);
  }
       else
  __ostream_write(__out, __s, __n);
       __out.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(__ios_base::badbit); }
 }
      return __out;
    }
  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);
  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
          streamsize);
}
namespace std {
  template<typename _Arg, typename _Result>
    struct unary_function
    {
      typedef _Arg argument_type;
      typedef _Result result_type;
    };
  template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {
      typedef _Arg1 first_argument_type;
      typedef _Arg2 second_argument_type;
      typedef _Result result_type;
    };
  template<typename _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x + __y; }
    };
  template<typename _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x - __y; }
    };
  template<typename _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x * __y; }
    };
  template<typename _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x / __y; }
    };
  template<typename _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x % __y; }
    };
  template<typename _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return -__x; }
    };
  template<typename _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x == __y; }
    };
  template<typename _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x != __y; }
    };
  template<typename _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };
  template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };
  template<typename _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x >= __y; }
    };
  template<typename _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x <= __y; }
    };
  template<typename _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x && __y; }
    };
  template<typename _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x || __y; }
    };
  template<typename _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
      bool
      operator()(const _Tp& __x) const
      { return !__x; }
    };
  template<typename _Tp>
    struct bit_and : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x & __y; }
    };
  template<typename _Tp>
    struct bit_or : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x | __y; }
    };
  template<typename _Tp>
    struct bit_xor : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x ^ __y; }
    };
  template<typename _Predicate>
    class unary_negate
    : public unary_function<typename _Predicate::argument_type, bool>
    {
    protected:
      _Predicate _M_pred;
    public:
      explicit
      unary_negate(const _Predicate& __x) : _M_pred(__x) { }
      bool
      operator()(const typename _Predicate::argument_type& __x) const
      { return !_M_pred(__x); }
    };
  template<typename _Predicate>
    inline unary_negate<_Predicate>
    not1(const _Predicate& __pred)
    { return unary_negate<_Predicate>(__pred); }
  template<typename _Predicate>
    class binary_negate
    : public binary_function<typename _Predicate::first_argument_type,
        typename _Predicate::second_argument_type, bool>
    {
    protected:
      _Predicate _M_pred;
    public:
      explicit
      binary_negate(const _Predicate& __x) : _M_pred(__x) { }
      bool
      operator()(const typename _Predicate::first_argument_type& __x,
   const typename _Predicate::second_argument_type& __y) const
      { return !_M_pred(__x, __y); }
    };
  template<typename _Predicate>
    inline binary_negate<_Predicate>
    not2(const _Predicate& __pred)
    { return binary_negate<_Predicate>(__pred); }
  template<typename _Arg, typename _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg);
    public:
      pointer_to_unary_function() { }
      explicit
      pointer_to_unary_function(_Result (*__x)(_Arg))
      : _M_ptr(__x) { }
      _Result
      operator()(_Arg __x) const
      { return _M_ptr(__x); }
    };
  template<typename _Arg, typename _Result>
    inline pointer_to_unary_function<_Arg, _Result>
    ptr_fun(_Result (*__x)(_Arg))
    { return pointer_to_unary_function<_Arg, _Result>(__x); }
  template<typename _Arg1, typename _Arg2, typename _Result>
    class pointer_to_binary_function
    : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg1, _Arg2);
    public:
      pointer_to_binary_function() { }
      explicit
      pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) { }
      _Result
      operator()(_Arg1 __x, _Arg2 __y) const
      { return _M_ptr(__x, __y); }
    };
  template<typename _Arg1, typename _Arg2, typename _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result>
    ptr_fun(_Result (*__x)(_Arg1, _Arg2))
    { return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__x); }
  template<typename _Tp>
    struct _Identity : public unary_function<_Tp,_Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }
      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };
  template<typename _Pair>
    struct _Select1st : public unary_function<_Pair,
           typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }
      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
    };
  template<typename _Pair>
    struct _Select2nd : public unary_function<_Pair,
           typename _Pair::second_type>
    {
      typename _Pair::second_type&
      operator()(_Pair& __x) const
      { return __x.second; }
      const typename _Pair::second_type&
      operator()(const _Pair& __x) const
      { return __x.second; }
    };
  template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)();
    };
  template<typename _Ret, typename _Tp>
    class const_mem_fun_t : public unary_function<const _Tp*, _Ret>
    {
    public:
      explicit
      const_mem_fun_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp* __p) const
      { return (__p->*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)() const;
    };
  template<typename _Ret, typename _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      mem_fun_ref_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp& __r) const
      { return (__r.*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)();
  };
  template<typename _Ret, typename _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp& __r) const
      { return (__r.*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)() const;
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_t : public binary_function<_Tp*, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp*, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };
  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline const_mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)())
    { return mem_fun_ref_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_ref_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }
}
namespace std {
  template<typename _Operation>
    class binder1st
    : public unary_function<typename _Operation::second_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::first_argument_type value;
    public:
      binder1st(const _Operation& __x,
  const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) { }
      typename _Operation::result_type
      operator()(const typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
      typename _Operation::result_type
      operator()(typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
    } ;
  template<typename _Operation, typename _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::first_argument_type _Arg1_type;
      return binder1st<_Operation>(__fn, _Arg1_type(__x));
    }
  template<typename _Operation>
    class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::second_argument_type value;
    public:
      binder2nd(const _Operation& __x,
  const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) { }
      typename _Operation::result_type
      operator()(const typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
      typename _Operation::result_type
      operator()(typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
    } ;
  template<typename _Operation, typename _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::second_argument_type _Arg2_type;
      return binder2nd<_Operation>(__fn, _Arg2_type(__x));
    }
}
       
namespace std {
  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_string
    {
      typedef typename _Alloc::template rebind<_CharT>::other _CharT_alloc_type;
    public:
      typedef _Traits traits_type;
      typedef typename _Traits::char_type value_type;
      typedef _Alloc allocator_type;
      typedef typename _CharT_alloc_type::size_type size_type;
      typedef typename _CharT_alloc_type::difference_type difference_type;
      typedef typename _CharT_alloc_type::reference reference;
      typedef typename _CharT_alloc_type::const_reference const_reference;
      typedef typename _CharT_alloc_type::pointer pointer;
      typedef typename _CharT_alloc_type::const_pointer const_pointer;
      typedef __gnu_cxx::__normal_iterator<pointer, basic_string> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, basic_string>
                                                            const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
    private:
      struct _Rep_base
      {
 size_type _M_length;
 size_type _M_capacity;
 _Atomic_word _M_refcount;
      };
      struct _Rep : _Rep_base
      {
 typedef typename _Alloc::template rebind<char>::other _Raw_bytes_alloc;
 static const size_type _S_max_size;
 static const _CharT _S_terminal;
        static size_type _S_empty_rep_storage[];
        static _Rep&
        _S_empty_rep()
        {
   void* __p = reinterpret_cast<void*>(&_S_empty_rep_storage);
   return *reinterpret_cast<_Rep*>(__p);
 }
        bool
 _M_is_leaked() const
        { return this->_M_refcount < 0; }
        bool
 _M_is_shared() const
        { return this->_M_refcount > 0; }
        void
 _M_set_leaked()
        { this->_M_refcount = -1; }
        void
 _M_set_sharable()
        { this->_M_refcount = 0; }
 void
 _M_set_length_and_sharable(size_type __n)
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
     {
       this->_M_set_sharable();
       this->_M_length = __n;
       traits_type::assign(this->_M_refdata()[__n], _S_terminal);
     }
 }
 _CharT*
 _M_refdata() throw()
 { return reinterpret_cast<_CharT*>(this + 1); }
 _CharT*
 _M_grab(const _Alloc& __alloc1, const _Alloc& __alloc2)
 {
   return (!_M_is_leaked() && __alloc1 == __alloc2)
           ? _M_refcopy() : _M_clone(__alloc1);
 }
 static _Rep*
 _S_create(size_type, size_type, const _Alloc&);
 void
 _M_dispose(const _Alloc& __a)
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
     if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount,
             -1) <= 0)
       _M_destroy(__a);
 }
 void
 _M_destroy(const _Alloc&) throw();
 _CharT*
 _M_refcopy() throw()
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
            __gnu_cxx::__atomic_add_dispatch(&this->_M_refcount, 1);
   return _M_refdata();
 }
 _CharT*
 _M_clone(const _Alloc&, size_type __res = 0);
      };
      struct _Alloc_hider : _Alloc
      {
 _Alloc_hider(_CharT* __dat, const _Alloc& __a)
 : _Alloc(__a), _M_p(__dat) { }
 _CharT* _M_p;
      };
    public:
      static const size_type npos = static_cast<size_type>(-1);
    private:
      mutable _Alloc_hider _M_dataplus;
      _CharT*
      _M_data() const
      { return _M_dataplus._M_p; }
      _CharT*
      _M_data(_CharT* __p)
      { return (_M_dataplus._M_p = __p); }
      _Rep*
      _M_rep() const
      { return &((reinterpret_cast<_Rep*> (_M_data()))[-1]); }
      iterator
      _M_ibegin() const
      { return iterator(_M_data()); }
      iterator
      _M_iend() const
      { return iterator(_M_data() + this->size()); }
      void
      _M_leak()
      {
 if (!_M_rep()->_M_is_leaked())
   _M_leak_hard();
      }
      size_type
      _M_check(size_type __pos, const char* __s) const
      {
 if (__pos > this->size())
   __throw_out_of_range((__s));
 return __pos;
      }
      void
      _M_check_length(size_type __n1, size_type __n2, const char* __s) const
      {
 if (this->max_size() - (this->size() - __n1) < __n2)
   __throw_length_error((__s));
      }
      size_type
      _M_limit(size_type __pos, size_type __off) const
      {
 const bool __testoff = __off < this->size() - __pos;
 return __testoff ? __off : this->size() - __pos;
      }
      bool
      _M_disjunct(const _CharT* __s) const
      {
 return (less<const _CharT*>()(__s, _M_data())
  || less<const _CharT*>()(_M_data() + this->size(), __s));
      }
      static void
      _M_copy(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::copy(__d, __s, __n);
      }
      static void
      _M_move(_CharT* __d, const _CharT* __s, size_type __n)
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::move(__d, __s, __n);
      }
      static void
      _M_assign(_CharT* __d, size_type __n, _CharT __c)
      {
 if (__n == 1)
   traits_type::assign(*__d, __c);
 else
   traits_type::assign(__d, __n, __c);
      }
      template<class _Iterator>
        static void
        _S_copy_chars(_CharT* __p, _Iterator __k1, _Iterator __k2)
        {
   for (; __k1 != __k2; ++__k1, ++__p)
     traits_type::assign(*__p, *__k1);
 }
      static void
      _S_copy_chars(_CharT* __p, iterator __k1, iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }
      static void
      _S_copy_chars(_CharT* __p, const_iterator __k1, const_iterator __k2)
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }
      static void
      _S_copy_chars(_CharT* __p, _CharT* __k1, _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }
      static void
      _S_copy_chars(_CharT* __p, const _CharT* __k1, const _CharT* __k2)
      { _M_copy(__p, __k1, __k2 - __k1); }
      static int
      _S_compare(size_type __n1, size_type __n2)
      {
 const difference_type __d = difference_type(__n1 - __n2);
 if (__d > __gnu_cxx::__numeric_traits<int>::__max)
   return __gnu_cxx::__numeric_traits<int>::__max;
 else if (__d < __gnu_cxx::__numeric_traits<int>::__min)
   return __gnu_cxx::__numeric_traits<int>::__min;
 else
   return int(__d);
      }
      void
      _M_mutate(size_type __pos, size_type __len1, size_type __len2);
      void
      _M_leak_hard();
      static _Rep&
      _S_empty_rep()
      { return _Rep::_S_empty_rep(); }
    public:
      basic_string()
      : _M_dataplus(_S_empty_rep()._M_refdata(), _Alloc()) { }
      explicit
      basic_string(const _Alloc& __a);
      basic_string(const basic_string& __str);
      basic_string(const basic_string& __str, size_type __pos,
     size_type __n = npos);
      basic_string(const basic_string& __str, size_type __pos,
     size_type __n, const _Alloc& __a);
      basic_string(const _CharT* __s, size_type __n,
     const _Alloc& __a = _Alloc());
      basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());
      basic_string(size_type __n, _CharT __c, const _Alloc& __a = _Alloc());
      template<class _InputIterator>
        basic_string(_InputIterator __beg, _InputIterator __end,
       const _Alloc& __a = _Alloc());
      ~basic_string()
      { _M_rep()->_M_dispose(this->get_allocator()); }
      basic_string&
      operator=(const basic_string& __str)
      { return this->assign(__str); }
      basic_string&
      operator=(const _CharT* __s)
      { return this->assign(__s); }
      basic_string&
      operator=(_CharT __c)
      {
 this->assign(1, __c);
 return *this;
      }
      iterator
      begin()
      {
 _M_leak();
 return iterator(_M_data());
      }
      const_iterator
      begin() const
      { return const_iterator(_M_data()); }
      iterator
      end()
      {
 _M_leak();
 return iterator(_M_data() + this->size());
      }
      const_iterator
      end() const
      { return const_iterator(_M_data() + this->size()); }
      reverse_iterator
      rbegin()
      { return reverse_iterator(this->end()); }
      const_reverse_iterator
      rbegin() const
      { return const_reverse_iterator(this->end()); }
      reverse_iterator
      rend()
      { return reverse_iterator(this->begin()); }
      const_reverse_iterator
      rend() const
      { return const_reverse_iterator(this->begin()); }
    public:
      size_type
      size() const
      { return _M_rep()->_M_length; }
      size_type
      length() const
      { return _M_rep()->_M_length; }
      size_type
      max_size() const
      { return _Rep::_S_max_size; }
      void
      resize(size_type __n, _CharT __c);
      void
      resize(size_type __n)
      { this->resize(__n, _CharT()); }
      size_type
      capacity() const
      { return _M_rep()->_M_capacity; }
      void
      reserve(size_type __res_arg = 0);
      void
      clear()
      { _M_mutate(0, this->size(), 0); }
      bool
      empty() const
      { return this->size() == 0; }
      const_reference
      operator[] (size_type __pos) const
      {
 ;
 return _M_data()[__pos];
      }
      reference
      operator[](size_type __pos)
      {
 ;
 ;
 _M_leak();
 return _M_data()[__pos];
      }
      const_reference
      at(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range(("basic_string::at"));
 return _M_data()[__n];
      }
      reference
      at(size_type __n)
      {
 if (__n >= size())
   __throw_out_of_range(("basic_string::at"));
 _M_leak();
 return _M_data()[__n];
      }
      basic_string&
      operator+=(const basic_string& __str)
      { return this->append(__str); }
      basic_string&
      operator+=(const _CharT* __s)
      { return this->append(__s); }
      basic_string&
      operator+=(_CharT __c)
      {
 this->push_back(__c);
 return *this;
      }
      basic_string&
      append(const basic_string& __str);
      basic_string&
      append(const basic_string& __str, size_type __pos, size_type __n);
      basic_string&
      append(const _CharT* __s, size_type __n);
      basic_string&
      append(const _CharT* __s)
      {
 ;
 return this->append(__s, traits_type::length(__s));
      }
      basic_string&
      append(size_type __n, _CharT __c);
      template<class _InputIterator>
        basic_string&
        append(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_iend(), _M_iend(), __first, __last); }
      void
      push_back(_CharT __c)
      {
 const size_type __len = 1 + this->size();
 if (__len > this->capacity() || _M_rep()->_M_is_shared())
   this->reserve(__len);
 traits_type::assign(_M_data()[this->size()], __c);
 _M_rep()->_M_set_length_and_sharable(__len);
      }
      basic_string&
      assign(const basic_string& __str);
      basic_string&
      assign(const basic_string& __str, size_type __pos, size_type __n)
      { return this->assign(__str._M_data()
       + __str._M_check(__pos, "basic_string::assign"),
       __str._M_limit(__pos, __n)); }
      basic_string&
      assign(const _CharT* __s, size_type __n);
      basic_string&
      assign(const _CharT* __s)
      {
 ;
 return this->assign(__s, traits_type::length(__s));
      }
      basic_string&
      assign(size_type __n, _CharT __c)
      { return _M_replace_aux(size_type(0), this->size(), __n, __c); }
      template<class _InputIterator>
        basic_string&
        assign(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_ibegin(), _M_iend(), __first, __last); }
      void
      insert(iterator __p, size_type __n, _CharT __c)
      { this->replace(__p, __p, __n, __c); }
      template<class _InputIterator>
        void
        insert(iterator __p, _InputIterator __beg, _InputIterator __end)
        { this->replace(__p, __p, __beg, __end); }
      basic_string&
      insert(size_type __pos1, const basic_string& __str)
      { return this->insert(__pos1, __str, size_type(0), __str.size()); }
      basic_string&
      insert(size_type __pos1, const basic_string& __str,
      size_type __pos2, size_type __n)
      { return this->insert(__pos1, __str._M_data()
       + __str._M_check(__pos2, "basic_string::insert"),
       __str._M_limit(__pos2, __n)); }
      basic_string&
      insert(size_type __pos, const _CharT* __s, size_type __n);
      basic_string&
      insert(size_type __pos, const _CharT* __s)
      {
 ;
 return this->insert(__pos, __s, traits_type::length(__s));
      }
      basic_string&
      insert(size_type __pos, size_type __n, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::insert"),
         size_type(0), __n, __c); }
      iterator
      insert(iterator __p, _CharT __c)
      {
 ;
 const size_type __pos = __p - _M_ibegin();
 _M_replace_aux(__pos, size_type(0), size_type(1), __c);
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
      basic_string&
      erase(size_type __pos = 0, size_type __n = npos)
      {
 _M_mutate(_M_check(__pos, "basic_string::erase"),
    _M_limit(__pos, __n), size_type(0));
 return *this;
      }
      iterator
      erase(iterator __position)
      {
 ;
 const size_type __pos = __position - _M_ibegin();
 _M_mutate(__pos, size_type(1), size_type(0));
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
      iterator
      erase(iterator __first, iterator __last);
      basic_string&
      replace(size_type __pos, size_type __n, const basic_string& __str)
      { return this->replace(__pos, __n, __str._M_data(), __str.size()); }
      basic_string&
      replace(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2)
      { return this->replace(__pos1, __n1, __str._M_data()
        + __str._M_check(__pos2, "basic_string::replace"),
        __str._M_limit(__pos2, __n2)); }
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2);
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s)
      {
 ;
 return this->replace(__pos, __n1, __s, traits_type::length(__s));
      }
      basic_string&
      replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::replace"),
         _M_limit(__pos, __n1), __n2, __c); }
      basic_string&
      replace(iterator __i1, iterator __i2, const basic_string& __str)
      { return this->replace(__i1, __i2, __str._M_data(), __str.size()); }
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s, size_type __n)
      {
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1, __s, __n);
      }
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s)
      {
 ;
 return this->replace(__i1, __i2, __s, traits_type::length(__s));
      }
      basic_string&
      replace(iterator __i1, iterator __i2, size_type __n, _CharT __c)
      {
 ;
 return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __c);
      }
      template<class _InputIterator>
        basic_string&
        replace(iterator __i1, iterator __i2,
  _InputIterator __k1, _InputIterator __k2)
        {
   ;
   ;
   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   return _M_replace_dispatch(__i1, __i2, __k1, __k2, _Integral());
 }
      basic_string&
      replace(iterator __i1, iterator __i2, _CharT* __k1, _CharT* __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2,
       const _CharT* __k1, const _CharT* __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2, iterator __k1, iterator __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2,
       const_iterator __k1, const_iterator __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
    private:
      template<class _Integer>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _Integer __n,
       _Integer __val, __true_type)
        { return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __val); }
      template<class _InputIterator>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
       _InputIterator __k2, __false_type);
      basic_string&
      _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
       _CharT __c);
      basic_string&
      _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
        size_type __n2);
      template<class _InIterator>
        static _CharT*
        _S_construct_aux(_InIterator __beg, _InIterator __end,
    const _Alloc& __a, __false_type)
 {
          typedef typename iterator_traits<_InIterator>::iterator_category _Tag;
          return _S_construct(__beg, __end, __a, _Tag());
 }
      template<class _Integer>
        static _CharT*
        _S_construct_aux(_Integer __beg, _Integer __end,
    const _Alloc& __a, __true_type)
        { return _S_construct_aux_2(static_cast<size_type>(__beg),
        __end, __a); }
      static _CharT*
      _S_construct_aux_2(size_type __req, _CharT __c, const _Alloc& __a)
      { return _S_construct(__req, __c, __a); }
      template<class _InIterator>
        static _CharT*
        _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a)
 {
   typedef typename std::__is_integer<_InIterator>::__type _Integral;
   return _S_construct_aux(__beg, __end, __a, _Integral());
        }
      template<class _InIterator>
        static _CharT*
         _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
        input_iterator_tag);
      template<class _FwdIterator>
        static _CharT*
        _S_construct(_FwdIterator __beg, _FwdIterator __end, const _Alloc& __a,
       forward_iterator_tag);
      static _CharT*
      _S_construct(size_type __req, _CharT __c, const _Alloc& __a);
    public:
      size_type
      copy(_CharT* __s, size_type __n, size_type __pos = 0) const;
      void
      swap(basic_string& __s);
      const _CharT*
      c_str() const
      { return _M_data(); }
      const _CharT*
      data() const
      { return _M_data(); }
      allocator_type
      get_allocator() const
      { return _M_dataplus; }
      size_type
      find(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find(const basic_string& __str, size_type __pos = 0) const
      { return this->find(__str.data(), __pos, __str.size()); }
      size_type
      find(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find(__s, __pos, traits_type::length(__s));
      }
      size_type
      find(_CharT __c, size_type __pos = 0) const;
      size_type
      rfind(const basic_string& __str, size_type __pos = npos) const
      { return this->rfind(__str.data(), __pos, __str.size()); }
      size_type
      rfind(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      rfind(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->rfind(__s, __pos, traits_type::length(__s));
      }
      size_type
      rfind(_CharT __c, size_type __pos = npos) const;
      size_type
      find_first_of(const basic_string& __str, size_type __pos = 0) const
      { return this->find_first_of(__str.data(), __pos, __str.size()); }
      size_type
      find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find_first_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_first_of(_CharT __c, size_type __pos = 0) const
      { return this->find(__c, __pos); }
      size_type
      find_last_of(const basic_string& __str, size_type __pos = npos) const
      { return this->find_last_of(__str.data(), __pos, __str.size()); }
      size_type
      find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find_last_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_last_of(_CharT __c, size_type __pos = npos) const
      { return this->rfind(__c, __pos); }
      size_type
      find_first_not_of(const basic_string& __str, size_type __pos = 0) const
      { return this->find_first_not_of(__str.data(), __pos, __str.size()); }
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos,
   size_type __n) const;
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_not_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_first_not_of(_CharT __c, size_type __pos = 0) const;
      size_type
      find_last_not_of(const basic_string& __str, size_type __pos = npos) const
      { return this->find_last_not_of(__str.data(), __pos, __str.size()); }
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos,
         size_type __n) const;
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_not_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_last_not_of(_CharT __c, size_type __pos = npos) const;
      basic_string
      substr(size_type __pos = 0, size_type __n = npos) const
      { return basic_string(*this,
       _M_check(__pos, "basic_string::substr"), __n); }
      int
      compare(const basic_string& __str) const
      {
 const size_type __size = this->size();
 const size_type __osize = __str.size();
 const size_type __len = std::min(__size, __osize);
 int __r = traits_type::compare(_M_data(), __str.data(), __len);
 if (!__r)
   __r = _S_compare(__size, __osize);
 return __r;
      }
      int
      compare(size_type __pos, size_type __n, const basic_string& __str) const;
      int
      compare(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2) const;
      int
      compare(const _CharT* __s) const;
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s) const;
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2) const;
  };
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT,_Traits,_Alloc>& __rhs);
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Alloc>& __rhs);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
      const _CharT* __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs, _CharT __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str(__lhs);
      __str.append(__size_type(1), __rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) == 0; }
  template<typename _CharT>
    inline
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, bool>::__type
    operator==(const basic_string<_CharT>& __lhs,
        const basic_string<_CharT>& __rhs)
    { return (__lhs.size() == __rhs.size()
       && !std::char_traits<_CharT>::compare(__lhs.data(), __rhs.data(),
          __lhs.size())); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) == 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) == 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const _CharT* __lhs,
      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline void
    swap(basic_string<_CharT, _Traits, _Alloc>& __lhs,
  basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { __lhs.swap(__rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Alloc>& __str);
  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __is, basic_string<char>& __str);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        const basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      return __ostream_insert(__os, __str.data(), __str.size());
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str)
    { return getline(__is, __str, __is.widen('\n')); }
  template<>
    basic_istream<char>&
    getline(basic_istream<char>& __in, basic_string<char>& __str,
     char __delim);
  template<>
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>& __in, basic_string<wchar_t>& __str,
     wchar_t __delim);
}
       
namespace std {
  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_max_size = (((npos - sizeof(_Rep_base))/sizeof(_CharT)) - 1) / 4;
  template<typename _CharT, typename _Traits, typename _Alloc>
    const _CharT
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_terminal = _CharT();
  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::npos;
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::_Rep::_S_empty_rep_storage[
    (sizeof(_Rep_base) + sizeof(_CharT) + sizeof(size_type) - 1) /
      sizeof(size_type)];
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     input_iterator_tag)
      {
 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();
 _CharT __buf[128];
 size_type __len = 0;
 while (__beg != __end && __len < sizeof(__buf) / sizeof(_CharT))
   {
     __buf[__len++] = *__beg;
     ++__beg;
   }
 _Rep* __r = _Rep::_S_create(__len, size_type(0), __a);
 _M_copy(__r->_M_refdata(), __buf, __len);
 try
   {
     while (__beg != __end)
       {
  if (__len == __r->_M_capacity)
    {
      _Rep* __another = _Rep::_S_create(__len + 1, __len, __a);
      _M_copy(__another->_M_refdata(), __r->_M_refdata(), __len);
      __r->_M_destroy(__a);
      __r = __another;
    }
  __r->_M_refdata()[__len++] = *__beg;
  ++__beg;
       }
   }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__len);
 return __r->_M_refdata();
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template <typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     forward_iterator_tag)
      {
 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();
 if (__gnu_cxx::__is_null_pointer(__beg) && __beg != __end)
   __throw_logic_error(("basic_string::_S_construct NULL not valid"));
 const size_type __dnew = static_cast<size_type>(std::distance(__beg,
              __end));
 _Rep* __r = _Rep::_S_create(__dnew, size_type(0), __a);
 try
   { _S_copy_chars(__r->_M_refdata(), __beg, __end); }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__dnew);
 return __r->_M_refdata();
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::
    _S_construct(size_type __n, _CharT __c, const _Alloc& __a)
    {
      if (__n == 0 && __a == _Alloc())
 return _S_empty_rep()._M_refdata();
      _Rep* __r = _Rep::_S_create(__n, size_type(0), __a);
      if (__n)
 _M_assign(__r->_M_refdata(), __n, __c);
      __r->_M_set_length_and_sharable(__n);
      return __r->_M_refdata();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str)
    : _M_dataplus(__str._M_rep()->_M_grab(_Alloc(__str.get_allocator()),
       __str.get_allocator()),
    __str.get_allocator())
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _Alloc& __a)
    : _M_dataplus(_S_construct(size_type(), _CharT(), __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos, size_type __n)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, _Alloc()), _Alloc())
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos,
   size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s + __n, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s ? __s + traits_type::length(__s) :
          __s + npos, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(size_type __n, _CharT __c, const _Alloc& __a)
    : _M_dataplus(_S_construct(__n, __c, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(_InputIterator __beg, _InputIterator __end, const _Alloc& __a)
    : _M_dataplus(_S_construct(__beg, __end, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const basic_string& __str)
    {
      if (_M_rep() != __str._M_rep())
 {
   const allocator_type __a = this->get_allocator();
   _CharT* __tmp = __str._M_rep()->_M_grab(__a, __str.get_allocator());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const _CharT* __s, size_type __n)
    {
      ;
      _M_check_length(this->size(), __n, "basic_string::assign");
      if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
 return _M_replace_safe(size_type(0), this->size(), __s, __n);
      else
 {
   const size_type __pos = __s - _M_data();
   if (__pos >= __n)
     _M_copy(_M_data(), __s, __n);
   else if (__pos)
     _M_move(_M_data(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__n);
   return *this;
 }
     }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(size_type __n, _CharT __c)
    {
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_assign(_M_data() + this->size(), __n, __c);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const _CharT* __s, size_type __n)
    {
      ;
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     {
       if (_M_disjunct(__s))
  this->reserve(__len);
       else
  {
    const size_type __off = __s - _M_data();
    this->reserve(__len);
    __s = _M_data() + __off;
  }
     }
   _M_copy(_M_data() + this->size(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str)
    {
      const size_type __size = __str.size();
      if (__size)
 {
   const size_type __len = __size + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data(), __size);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str, size_type __pos, size_type __n)
    {
      __str._M_check(__pos, "basic_string::append");
      __n = __str._M_limit(__pos, __n);
      if (__n)
 {
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data() + __pos, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     insert(size_type __pos, const _CharT* __s, size_type __n)
     {
       ;
       _M_check(__pos, "basic_string::insert");
       _M_check_length(size_type(0), __n, "basic_string::insert");
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, size_type(0), __s, __n);
       else
         {
           const size_type __off = __s - _M_data();
           _M_mutate(__pos, 0, __n);
           __s = _M_data() + __off;
           _CharT* __p = _M_data() + __pos;
           if (__s + __n <= __p)
             _M_copy(__p, __s, __n);
           else if (__s >= __p)
             _M_copy(__p, __s + __n, __n);
           else
             {
        const size_type __nleft = __p - __s;
               _M_copy(__p, __s, __nleft);
               _M_copy(__p + __nleft, __p + __n, __n - __nleft);
             }
           return *this;
         }
     }
   template<typename _CharT, typename _Traits, typename _Alloc>
     typename basic_string<_CharT, _Traits, _Alloc>::iterator
     basic_string<_CharT, _Traits, _Alloc>::
     erase(iterator __first, iterator __last)
     {
       ;
       const size_type __size = __last - __first;
       if (__size)
  {
    const size_type __pos = __first - _M_ibegin();
    _M_mutate(__pos, __size, size_type(0));
    _M_rep()->_M_set_leaked();
    return iterator(_M_data() + __pos);
  }
       else
  return __first;
     }
   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     replace(size_type __pos, size_type __n1, const _CharT* __s,
      size_type __n2)
     {
       ;
       _M_check(__pos, "basic_string::replace");
       __n1 = _M_limit(__pos, __n1);
       _M_check_length(__n1, __n2, "basic_string::replace");
       bool __left;
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, __n1, __s, __n2);
       else if ((__left = __s + __n2 <= _M_data() + __pos)
  || _M_data() + __pos + __n1 <= __s)
  {
    size_type __off = __s - _M_data();
    __left ? __off : (__off += __n2 - __n1);
    _M_mutate(__pos, __n1, __n2);
    _M_copy(_M_data() + __pos, _M_data() + __off, __n2);
    return *this;
  }
       else
  {
    const basic_string __tmp(__s, __n2);
    return _M_replace_safe(__pos, __n1, __tmp._M_data(), __n2);
  }
     }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_destroy(const _Alloc& __a) throw ()
    {
      const size_type __size = sizeof(_Rep_base) +
                        (this->_M_capacity + 1) * sizeof(_CharT);
      _Raw_bytes_alloc(__a).deallocate(reinterpret_cast<char*>(this), __size);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_leak_hard()
    {
      if (_M_rep() == &_S_empty_rep())
 return;
      if (_M_rep()->_M_is_shared())
 _M_mutate(0, 0, 0);
      _M_rep()->_M_set_leaked();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_mutate(size_type __pos, size_type __len1, size_type __len2)
    {
      const size_type __old_size = this->size();
      const size_type __new_size = __old_size + __len2 - __len1;
      const size_type __how_much = __old_size - __pos - __len1;
      if (__new_size > this->capacity() || _M_rep()->_M_is_shared())
 {
   const allocator_type __a = get_allocator();
   _Rep* __r = _Rep::_S_create(__new_size, this->capacity(), __a);
   if (__pos)
     _M_copy(__r->_M_refdata(), _M_data(), __pos);
   if (__how_much)
     _M_copy(__r->_M_refdata() + __pos + __len2,
      _M_data() + __pos + __len1, __how_much);
   _M_rep()->_M_dispose(__a);
   _M_data(__r->_M_refdata());
 }
      else if (__how_much && __len1 != __len2)
 {
   _M_move(_M_data() + __pos + __len2,
    _M_data() + __pos + __len1, __how_much);
 }
      _M_rep()->_M_set_length_and_sharable(__new_size);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    reserve(size_type __res)
    {
      if (__res != this->capacity() || _M_rep()->_M_is_shared())
        {
   if (__res < this->size())
     __res = this->size();
   const allocator_type __a = get_allocator();
   _CharT* __tmp = _M_rep()->_M_clone(__a, __res - this->size());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
        }
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    swap(basic_string& __s)
    {
      if (_M_rep()->_M_is_leaked())
 _M_rep()->_M_set_sharable();
      if (__s._M_rep()->_M_is_leaked())
 __s._M_rep()->_M_set_sharable();
      if (this->get_allocator() == __s.get_allocator())
 {
   _CharT* __tmp = _M_data();
   _M_data(__s._M_data());
   __s._M_data(__tmp);
 }
      else
 {
   const basic_string __tmp1(_M_ibegin(), _M_iend(),
        __s.get_allocator());
   const basic_string __tmp2(__s._M_ibegin(), __s._M_iend(),
        this->get_allocator());
   *this = __tmp2;
   __s = __tmp1;
 }
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::_Rep*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _S_create(size_type __capacity, size_type __old_capacity,
       const _Alloc& __alloc)
    {
      if (__capacity > _S_max_size)
 __throw_length_error(("basic_string::_S_create"));
      const size_type __pagesize = 4096;
      const size_type __malloc_header_size = 4 * sizeof(void*);
      if (__capacity > __old_capacity && __capacity < 2 * __old_capacity)
 __capacity = 2 * __old_capacity;
      size_type __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
      const size_type __adj_size = __size + __malloc_header_size;
      if (__adj_size > __pagesize && __capacity > __old_capacity)
 {
   const size_type __extra = __pagesize - __adj_size % __pagesize;
   __capacity += __extra / sizeof(_CharT);
   if (__capacity > _S_max_size)
     __capacity = _S_max_size;
   __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
 }
      void* __place = _Raw_bytes_alloc(__alloc).allocate(__size);
      _Rep *__p = new (__place) _Rep;
      __p->_M_capacity = __capacity;
      __p->_M_set_sharable();
      return __p;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_clone(const _Alloc& __alloc, size_type __res)
    {
      const size_type __requested_cap = this->_M_length + __res;
      _Rep* __r = _Rep::_S_create(__requested_cap, this->_M_capacity,
      __alloc);
      if (this->_M_length)
 _M_copy(__r->_M_refdata(), _M_refdata(), this->_M_length);
      __r->_M_set_length_and_sharable(this->_M_length);
      return __r->_M_refdata();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    resize(size_type __n, _CharT __c)
    {
      const size_type __size = this->size();
      _M_check_length(__size, __n, "basic_string::resize");
      if (__size < __n)
 this->append(__n - __size, __c);
      else if (__n < __size)
 this->erase(__n);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
      basic_string<_CharT, _Traits, _Alloc>&
      basic_string<_CharT, _Traits, _Alloc>::
      _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
     _InputIterator __k2, __false_type)
      {
 const basic_string __s(__k1, __k2);
 const size_type __n1 = __i2 - __i1;
 _M_check_length(__n1, __s.size(), "basic_string::_M_replace_dispatch");
 return _M_replace_safe(__i1 - _M_ibegin(), __n1, __s._M_data(),
          __s.size());
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
     _CharT __c)
    {
      _M_check_length(__n1, __n2, "basic_string::_M_replace_aux");
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_assign(_M_data() + __pos1, __n2, __c);
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
      size_type __n2)
    {
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_copy(_M_data() + __pos1, __s, __n2);
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      ;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      const __size_type __len = _Traits::length(__lhs);
      __string_type __str;
      __str.reserve(__len + __rhs.size());
      __str.append(__lhs, __len);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str;
      const __size_type __len = __rhs.size();
      __str.reserve(__len + 1);
      __str.append(__size_type(1), __lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    copy(_CharT* __s, size_type __n, size_type __pos) const
    {
      _M_check(__pos, "basic_string::copy");
      __n = _M_limit(__pos, __n);
      ;
      if (__n)
 _M_copy(__s, _M_data() + __pos, __n);
      return __n;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      const _CharT* __data = _M_data();
      if (__n == 0)
 return __pos <= __size ? __pos : npos;
      if (__n <= __size)
 {
   for (; __pos <= __size - __n; ++__pos)
     if (traits_type::eq(__data[__pos], __s[0])
  && traits_type::compare(__data + __pos + 1,
     __s + 1, __n - 1) == 0)
       return __pos;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(_CharT __c, size_type __pos) const
    {
      size_type __ret = npos;
      const size_type __size = this->size();
      if (__pos < __size)
 {
   const _CharT* __data = _M_data();
   const size_type __n = __size - __pos;
   const _CharT* __p = traits_type::find(__data + __pos, __n, __c);
   if (__p)
     __ret = __p - __data;
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      if (__n <= __size)
 {
   __pos = std::min(size_type(__size - __n), __pos);
   const _CharT* __data = _M_data();
   do
     {
       if (traits_type::compare(__data + __pos, __s, __n) == 0)
  return __pos;
     }
   while (__pos-- > 0);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   for (++__size; __size-- > 0; )
     if (traits_type::eq(_M_data()[__size], __c))
       return __size;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __n && __pos < this->size(); ++__pos)
 {
   const _CharT* __p = traits_type::find(__s, __n, _M_data()[__pos]);
   if (__p)
     return __pos;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size && __n)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size-- != 0);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::find(__s, __n, _M_data()[__pos]))
   return __pos;
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(_CharT __c, size_type __pos) const
    {
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::eq(_M_data()[__pos], __c))
   return __pos;
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(_CharT __c, size_type __pos) const
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::eq(_M_data()[__size], __c))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n, const basic_string& __str) const
    {
      _M_check(__pos, "basic_string::compare");
      __n = _M_limit(__pos, __n);
      const size_type __osize = __str.size();
      const size_type __len = std::min(__n, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __str.data(), __len);
      if (!__r)
 __r = _S_compare(__n, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos1, size_type __n1, const basic_string& __str,
     size_type __pos2, size_type __n2) const
    {
      _M_check(__pos1, "basic_string::compare");
      __str._M_check(__pos2, "basic_string::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos1,
         __str.data() + __pos2, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(const _CharT* __s) const
    {
      ;
      const size_type __size = this->size();
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__size, __osize);
      int __r = traits_type::compare(_M_data(), __s, __len);
      if (!__r)
 __r = _S_compare(__size, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__n1, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s,
     size_type __n2) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in,
        basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      typedef ctype<_CharT> __ctype_type;
      typedef typename __ctype_type::ctype_base __ctype_base;
      __size_type __extracted = 0;
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {
       __str.erase();
       _CharT __buf[128];
       __size_type __len = 0;
       const streamsize __w = __in.width();
       const __size_type __n = __w > 0 ? static_cast<__size_type>(__w)
                                : __str.max_size();
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();
       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(__ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    if (__len == sizeof(__buf) / sizeof(_CharT))
      {
        __str.append(__buf, sizeof(__buf) / sizeof(_CharT));
        __len = 0;
      }
    __buf[__len++] = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       __str.append(__buf, __len);
       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {
       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __in,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      __size_type __extracted = 0;
      const __size_type __n = __str.max_size();
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, true);
      if (__cerb)
 {
   try
     {
       __str.erase();
       const __int_type __idelim = _Traits::to_int_type(__delim);
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();
       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !_Traits::eq_int_type(__c, __idelim))
  {
    __str += _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       else if (_Traits::eq_int_type(__c, __idelim))
  {
    ++__extracted;
    __in.rdbuf()->sbumpc();
  }
       else
  __err |= __ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {
       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  extern template class basic_string<char>;
  extern template
    basic_istream<char>&
    operator>>(basic_istream<char>&, string&);
  extern template
    basic_ostream<char>&
    operator<<(basic_ostream<char>&, const string&);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&, char);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&);
  extern template class basic_string<wchar_t>;
  extern template
    basic_istream<wchar_t>&
    operator>>(basic_istream<wchar_t>&, wstring&);
  extern template
    basic_ostream<wchar_t>&
    operator<<(basic_ostream<wchar_t>&, const wstring&);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&, wchar_t);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&);
}
namespace std {
  class locale
  {
  public:
    typedef int category;
    class facet;
    class id;
    class _Impl;
    friend class facet;
    friend class _Impl;
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Cache>
      friend struct __use_cache;
    static const category none = 0;
    static const category ctype = 1L << 0;
    static const category numeric = 1L << 1;
    static const category collate = 1L << 2;
    static const category time = 1L << 3;
    static const category monetary = 1L << 4;
    static const category messages = 1L << 5;
    static const category all = (ctype | numeric | collate |
        time | monetary | messages);
    locale() throw();
    locale(const locale& __other) throw();
    explicit
    locale(const char* __s);
    locale(const locale& __base, const char* __s, category __cat);
    locale(const locale& __base, const locale& __add, category __cat);
    template<typename _Facet>
      locale(const locale& __other, _Facet* __f);
    ~locale() throw();
    const locale&
    operator=(const locale& __other) throw();
    template<typename _Facet>
      locale
      combine(const locale& __other) const;
    string
    name() const;
    bool
    operator==(const locale& __other) const throw();
    bool
    operator!=(const locale& __other) const throw()
    { return !(this->operator==(__other)); }
    template<typename _Char, typename _Traits, typename _Alloc>
      bool
      operator()(const basic_string<_Char, _Traits, _Alloc>& __s1,
   const basic_string<_Char, _Traits, _Alloc>& __s2) const;
    static locale
    global(const locale&);
    static const locale&
    classic();
  private:
    _Impl* _M_impl;
    static _Impl* _S_classic;
    static _Impl* _S_global;
    static const char* const* const _S_categories;
    enum { _S_categories_size = 6 + 0 };
    static __gthread_once_t _S_once;
    explicit
    locale(_Impl*) throw();
    static void
    _S_initialize();
    static void
    _S_initialize_once() throw();
    static category
    _S_normalize_category(category);
    void
    _M_coalesce(const locale& __base, const locale& __add, category __cat);
  };
  class locale::facet
  {
  private:
    friend class locale;
    friend class locale::_Impl;
    mutable _Atomic_word _M_refcount;
    static __c_locale _S_c_locale;
    static const char _S_c_name[2];
    static __gthread_once_t _S_once;
    static void
    _S_initialize_once();
  protected:
    explicit
    facet(size_t __refs = 0) throw() : _M_refcount(__refs ? 1 : 0)
    { }
    virtual
    ~facet();
    static void
    _S_create_c_locale(__c_locale& __cloc, const char* __s,
         __c_locale __old = 0);
    static __c_locale
    _S_clone_c_locale(__c_locale& __cloc) throw();
    static void
    _S_destroy_c_locale(__c_locale& __cloc);
    static __c_locale
    _S_lc_ctype_c_locale(__c_locale __cloc, const char* __s);
    static __c_locale
    _S_get_c_locale();
    __attribute__ ((__const__)) static const char*
    _S_get_c_name() throw();
  private:
    void
    _M_add_reference() const throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
    void
    _M_remove_reference() const throw()
    {
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
   try
     { delete this; }
   catch(...)
     { }
 }
    }
    facet(const facet&);
    facet&
    operator=(const facet&);
  };
  class locale::id
  {
  private:
    friend class locale;
    friend class locale::_Impl;
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    mutable size_t _M_index;
    static _Atomic_word _S_refcount;
    void
    operator=(const id&);
    id(const id&);
  public:
    id() { }
    size_t
    _M_id() const throw();
  };
  class locale::_Impl
  {
  public:
    friend class locale;
    friend class locale::facet;
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Cache>
      friend struct __use_cache;
  private:
    _Atomic_word _M_refcount;
    const facet** _M_facets;
    size_t _M_facets_size;
    const facet** _M_caches;
    char** _M_names;
    static const locale::id* const _S_id_ctype[];
    static const locale::id* const _S_id_numeric[];
    static const locale::id* const _S_id_collate[];
    static const locale::id* const _S_id_time[];
    static const locale::id* const _S_id_monetary[];
    static const locale::id* const _S_id_messages[];
    static const locale::id* const* const _S_facet_categories[];
    void
    _M_add_reference() throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
    void
    _M_remove_reference() throw()
    {
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
   try
     { delete this; }
   catch(...)
     { }
 }
    }
    _Impl(const _Impl&, size_t);
    _Impl(const char*, size_t);
    _Impl(size_t) throw();
   ~_Impl() throw();
    _Impl(const _Impl&);
    void
    operator=(const _Impl&);
    bool
    _M_check_same_name()
    {
      bool __ret = true;
      if (_M_names[1])
 for (size_t __i = 0; __ret && __i < _S_categories_size - 1; ++__i)
   __ret = __builtin_strcmp(_M_names[__i], _M_names[__i + 1]) == 0;
      return __ret;
    }
    void
    _M_replace_categories(const _Impl*, category);
    void
    _M_replace_category(const _Impl*, const locale::id* const*);
    void
    _M_replace_facet(const _Impl*, const locale::id*);
    void
    _M_install_facet(const locale::id*, const facet*);
    template<typename _Facet>
      void
      _M_init_facet(_Facet* __facet)
      { _M_install_facet(&_Facet::id, __facet); }
    void
    _M_install_cache(const facet*, size_t);
  };
  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw();
  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc);
  template<typename _CharT>
    class collate : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
    protected:
      __c_locale _M_c_locale_collate;
    public:
      static locale::id id;
      explicit
      collate(size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_get_c_locale())
      { }
      explicit
      collate(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_clone_c_locale(__cloc))
      { }
      int
      compare(const _CharT* __lo1, const _CharT* __hi1,
       const _CharT* __lo2, const _CharT* __hi2) const
      { return this->do_compare(__lo1, __hi1, __lo2, __hi2); }
      string_type
      transform(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_transform(__lo, __hi); }
      long
      hash(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_hash(__lo, __hi); }
      int
      _M_compare(const _CharT*, const _CharT*) const throw();
      size_t
      _M_transform(_CharT*, const _CharT*, size_t) const throw();
  protected:
      virtual
      ~collate()
      { _S_destroy_c_locale(_M_c_locale_collate); }
      virtual int
      do_compare(const _CharT* __lo1, const _CharT* __hi1,
   const _CharT* __lo2, const _CharT* __hi2) const;
      virtual string_type
      do_transform(const _CharT* __lo, const _CharT* __hi) const;
      virtual long
      do_hash(const _CharT* __lo, const _CharT* __hi) const;
    };
  template<typename _CharT>
    locale::id collate<_CharT>::id;
  template<>
    int
    collate<char>::_M_compare(const char*, const char*) const throw();
  template<>
    size_t
    collate<char>::_M_transform(char*, const char*, size_t) const throw();
  template<>
    int
    collate<wchar_t>::_M_compare(const wchar_t*, const wchar_t*) const throw();
  template<>
    size_t
    collate<wchar_t>::_M_transform(wchar_t*, const wchar_t*, size_t) const throw();
  template<typename _CharT>
    class collate_byname : public collate<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      explicit
      collate_byname(const char* __s, size_t __refs = 0)
      : collate<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     this->_S_destroy_c_locale(this->_M_c_locale_collate);
     this->_S_create_c_locale(this->_M_c_locale_collate, __s);
   }
      }
    protected:
      virtual
      ~collate_byname() { }
    };
}
       
namespace std {
  template<typename _Facet>
    locale::
    locale(const locale& __other, _Facet* __f)
    {
      _M_impl = new _Impl(*__other._M_impl, 1);
      try
 { _M_impl->_M_install_facet(&_Facet::id, __f); }
      catch(...)
 {
   _M_impl->_M_remove_reference();
   throw;
 }
      delete [] _M_impl->_M_names[0];
      _M_impl->_M_names[0] = 0;
    }
  template<typename _Facet>
    locale
    locale::
    combine(const locale& __other) const
    {
      _Impl* __tmp = new _Impl(*_M_impl, 1);
      try
 {
   __tmp->_M_replace_facet(__other._M_impl, &_Facet::id);
 }
      catch(...)
 {
   __tmp->_M_remove_reference();
   throw;
 }
      return locale(__tmp);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    bool
    locale::
    operator()(const basic_string<_CharT, _Traits, _Alloc>& __s1,
        const basic_string<_CharT, _Traits, _Alloc>& __s2) const
    {
      typedef std::collate<_CharT> __collate_type;
      const __collate_type& __collate = use_facet<__collate_type>(*this);
      return (__collate.compare(__s1.data(), __s1.data() + __s1.length(),
    __s2.data(), __s2.data() + __s2.length()) < 0);
    }
  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw()
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      return (__i < __loc._M_impl->_M_facets_size
       && dynamic_cast<const _Facet*>(__facets[__i]));
    }
  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc)
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      if (__i >= __loc._M_impl->_M_facets_size || !__facets[__i])
        __throw_bad_cast();
      return dynamic_cast<const _Facet&>(*__facets[__i]);
    }
  template<typename _CharT>
    int
    collate<_CharT>::_M_compare(const _CharT*, const _CharT*) const throw ()
    { return 0; }
  template<typename _CharT>
    size_t
    collate<_CharT>::_M_transform(_CharT*, const _CharT*, size_t) const throw ()
    { return 0; }
  template<typename _CharT>
    int
    collate<_CharT>::
    do_compare(const _CharT* __lo1, const _CharT* __hi1,
        const _CharT* __lo2, const _CharT* __hi2) const
    {
      const string_type __one(__lo1, __hi1);
      const string_type __two(__lo2, __hi2);
      const _CharT* __p = __one.c_str();
      const _CharT* __pend = __one.data() + __one.length();
      const _CharT* __q = __two.c_str();
      const _CharT* __qend = __two.data() + __two.length();
      for (;;)
 {
   const int __res = _M_compare(__p, __q);
   if (__res)
     return __res;
   __p += char_traits<_CharT>::length(__p);
   __q += char_traits<_CharT>::length(__q);
   if (__p == __pend && __q == __qend)
     return 0;
   else if (__p == __pend)
     return -1;
   else if (__q == __qend)
     return 1;
   __p++;
   __q++;
 }
    }
  template<typename _CharT>
    typename collate<_CharT>::string_type
    collate<_CharT>::
    do_transform(const _CharT* __lo, const _CharT* __hi) const
    {
      string_type __ret;
      const string_type __str(__lo, __hi);
      const _CharT* __p = __str.c_str();
      const _CharT* __pend = __str.data() + __str.length();
      size_t __len = (__hi - __lo) * 2;
      _CharT* __c = new _CharT[__len];
      try
 {
   for (;;)
     {
       size_t __res = _M_transform(__c, __p, __len);
       if (__res >= __len)
  {
    __len = __res + 1;
    delete [] __c, __c = 0;
    __c = new _CharT[__len];
    __res = _M_transform(__c, __p, __len);
  }
       __ret.append(__c, __res);
       __p += char_traits<_CharT>::length(__p);
       if (__p == __pend)
  break;
       __p++;
       __ret.push_back(_CharT());
     }
 }
      catch(...)
 {
   delete [] __c;
   throw;
 }
      delete [] __c;
      return __ret;
    }
  template<typename _CharT>
    long
    collate<_CharT>::
    do_hash(const _CharT* __lo, const _CharT* __hi) const
    {
      unsigned long __val = 0;
      for (; __lo < __hi; ++__lo)
 __val =
   *__lo + ((__val << 7)
     | (__val >> (__gnu_cxx::__numeric_traits<unsigned long>::
    __digits - 7)));
      return static_cast<long>(__val);
    }
  extern template class collate<char>;
  extern template class collate_byname<char>;
  extern template
    const collate<char>&
    use_facet<collate<char> >(const locale&);
  extern template
    bool
    has_facet<collate<char> >(const locale&);
  extern template class collate<wchar_t>;
  extern template class collate_byname<wchar_t>;
  extern template
    const collate<wchar_t>&
    use_facet<collate<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<collate<wchar_t> >(const locale&);
}
namespace std {
  enum _Ios_Fmtflags
    {
      _S_boolalpha = 1L << 0,
      _S_dec = 1L << 1,
      _S_fixed = 1L << 2,
      _S_hex = 1L << 3,
      _S_internal = 1L << 4,
      _S_left = 1L << 5,
      _S_oct = 1L << 6,
      _S_right = 1L << 7,
      _S_scientific = 1L << 8,
      _S_showbase = 1L << 9,
      _S_showpoint = 1L << 10,
      _S_showpos = 1L << 11,
      _S_skipws = 1L << 12,
      _S_unitbuf = 1L << 13,
      _S_uppercase = 1L << 14,
      _S_adjustfield = _S_left | _S_right | _S_internal,
      _S_basefield = _S_dec | _S_oct | _S_hex,
      _S_floatfield = _S_scientific | _S_fixed,
      _S_ios_fmtflags_end = 1L << 16
    };
  inline _Ios_Fmtflags
  operator&(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline _Ios_Fmtflags
  operator|(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline _Ios_Fmtflags
  operator^(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline _Ios_Fmtflags&
  operator|=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a | __b; }
  inline _Ios_Fmtflags&
  operator&=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a & __b; }
  inline _Ios_Fmtflags&
  operator^=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a ^ __b; }
  inline _Ios_Fmtflags
  operator~(_Ios_Fmtflags __a)
  { return _Ios_Fmtflags(~static_cast<int>(__a)); }
  enum _Ios_Openmode
    {
      _S_app = 1L << 0,
      _S_ate = 1L << 1,
      _S_bin = 1L << 2,
      _S_in = 1L << 3,
      _S_out = 1L << 4,
      _S_trunc = 1L << 5,
      _S_ios_openmode_end = 1L << 16
    };
  inline _Ios_Openmode
  operator&(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline _Ios_Openmode
  operator|(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline _Ios_Openmode
  operator^(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline _Ios_Openmode&
  operator|=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a | __b; }
  inline _Ios_Openmode&
  operator&=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a & __b; }
  inline _Ios_Openmode&
  operator^=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a ^ __b; }
  inline _Ios_Openmode
  operator~(_Ios_Openmode __a)
  { return _Ios_Openmode(~static_cast<int>(__a)); }
  enum _Ios_Iostate
    {
      _S_goodbit = 0,
      _S_badbit = 1L << 0,
      _S_eofbit = 1L << 1,
      _S_failbit = 1L << 2,
      _S_ios_iostate_end = 1L << 16
    };
  inline _Ios_Iostate
  operator&(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline _Ios_Iostate
  operator|(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline _Ios_Iostate
  operator^(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline _Ios_Iostate&
  operator|=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a | __b; }
  inline _Ios_Iostate&
  operator&=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a & __b; }
  inline _Ios_Iostate&
  operator^=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a ^ __b; }
  inline _Ios_Iostate
  operator~(_Ios_Iostate __a)
  { return _Ios_Iostate(~static_cast<int>(__a)); }
  enum _Ios_Seekdir
    {
      _S_beg = 0,
      _S_cur = 1,
      _S_end = 2,
      _S_ios_seekdir_end = 1L << 16
    };
  class ios_base
  {
  public:
    class failure : public exception
    {
    public:
      explicit
      failure(const string& __str) throw();
      virtual
      ~failure() throw();
      virtual const char*
      what() const throw();
    private:
      string _M_msg;
    };
    typedef _Ios_Fmtflags fmtflags;
    static const fmtflags boolalpha = _S_boolalpha;
    static const fmtflags dec = _S_dec;
    static const fmtflags fixed = _S_fixed;
    static const fmtflags hex = _S_hex;
    static const fmtflags internal = _S_internal;
    static const fmtflags left = _S_left;
    static const fmtflags oct = _S_oct;
    static const fmtflags right = _S_right;
    static const fmtflags scientific = _S_scientific;
    static const fmtflags showbase = _S_showbase;
    static const fmtflags showpoint = _S_showpoint;
    static const fmtflags showpos = _S_showpos;
    static const fmtflags skipws = _S_skipws;
    static const fmtflags unitbuf = _S_unitbuf;
    static const fmtflags uppercase = _S_uppercase;
    static const fmtflags adjustfield = _S_adjustfield;
    static const fmtflags basefield = _S_basefield;
    static const fmtflags floatfield = _S_floatfield;
    typedef _Ios_Iostate iostate;
    static const iostate badbit = _S_badbit;
    static const iostate eofbit = _S_eofbit;
    static const iostate failbit = _S_failbit;
    static const iostate goodbit = _S_goodbit;
    typedef _Ios_Openmode openmode;
    static const openmode app = _S_app;
    static const openmode ate = _S_ate;
    static const openmode binary = _S_bin;
    static const openmode in = _S_in;
    static const openmode out = _S_out;
    static const openmode trunc = _S_trunc;
    typedef _Ios_Seekdir seekdir;
    static const seekdir beg = _S_beg;
    static const seekdir cur = _S_cur;
    static const seekdir end = _S_end;
    typedef int io_state;
    typedef int open_mode;
    typedef int seek_dir;
    typedef std::streampos streampos;
    typedef std::streamoff streamoff;
    enum event
    {
      erase_event,
      imbue_event,
      copyfmt_event
    };
    typedef void (*event_callback) (event, ios_base&, int);
    void
    register_callback(event_callback __fn, int __index);
  protected:
    streamsize _M_precision;
    streamsize _M_width;
    fmtflags _M_flags;
    iostate _M_exception;
    iostate _M_streambuf_state;
    struct _Callback_list
    {
      _Callback_list* _M_next;
      ios_base::event_callback _M_fn;
      int _M_index;
      _Atomic_word _M_refcount;
      _Callback_list(ios_base::event_callback __fn, int __index,
       _Callback_list* __cb)
      : _M_next(__cb), _M_fn(__fn), _M_index(__index), _M_refcount(0) { }
      void
      _M_add_reference() { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
      int
      _M_remove_reference()
      { return __gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1); }
    };
     _Callback_list* _M_callbacks;
    void
    _M_call_callbacks(event __ev) throw();
    void
    _M_dispose_callbacks(void) throw();
    struct _Words
    {
      void* _M_pword;
      long _M_iword;
      _Words() : _M_pword(0), _M_iword(0) { }
    };
    _Words _M_word_zero;
    enum { _S_local_word_size = 8 };
    _Words _M_local_word[_S_local_word_size];
    int _M_word_size;
    _Words* _M_word;
    _Words&
    _M_grow_words(int __index, bool __iword);
    locale _M_ios_locale;
    void
    _M_init() throw();
  public:
    class Init
    {
      friend class ios_base;
    public:
      Init();
      ~Init();
    private:
      static _Atomic_word _S_refcount;
      static bool _S_synced_with_stdio;
    };
    fmtflags
    flags() const
    { return _M_flags; }
    fmtflags
    flags(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags = __fmtfl;
      return __old;
    }
    fmtflags
    setf(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags |= __fmtfl;
      return __old;
    }
    fmtflags
    setf(fmtflags __fmtfl, fmtflags __mask)
    {
      fmtflags __old = _M_flags;
      _M_flags &= ~__mask;
      _M_flags |= (__fmtfl & __mask);
      return __old;
    }
    void
    unsetf(fmtflags __mask)
    { _M_flags &= ~__mask; }
    streamsize
    precision() const
    { return _M_precision; }
    streamsize
    precision(streamsize __prec)
    {
      streamsize __old = _M_precision;
      _M_precision = __prec;
      return __old;
    }
    streamsize
    width() const
    { return _M_width; }
    streamsize
    width(streamsize __wide)
    {
      streamsize __old = _M_width;
      _M_width = __wide;
      return __old;
    }
    static bool
    sync_with_stdio(bool __sync = true);
    locale
    imbue(const locale& __loc) throw();
    locale
    getloc() const
    { return _M_ios_locale; }
    const locale&
    _M_getloc() const
    { return _M_ios_locale; }
    static int
    xalloc() throw();
    long&
    iword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, true);
      return __word._M_iword;
    }
    void*&
    pword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, false);
      return __word._M_pword;
    }
    virtual ~ios_base();
  protected:
    ios_base() throw ();
  private:
    ios_base(const ios_base&);
    ios_base&
    operator=(const ios_base&);
  };
  inline ios_base&
  boolalpha(ios_base& __base)
  {
    __base.setf(ios_base::boolalpha);
    return __base;
  }
  inline ios_base&
  noboolalpha(ios_base& __base)
  {
    __base.unsetf(ios_base::boolalpha);
    return __base;
  }
  inline ios_base&
  showbase(ios_base& __base)
  {
    __base.setf(ios_base::showbase);
    return __base;
  }
  inline ios_base&
  noshowbase(ios_base& __base)
  {
    __base.unsetf(ios_base::showbase);
    return __base;
  }
  inline ios_base&
  showpoint(ios_base& __base)
  {
    __base.setf(ios_base::showpoint);
    return __base;
  }
  inline ios_base&
  noshowpoint(ios_base& __base)
  {
    __base.unsetf(ios_base::showpoint);
    return __base;
  }
  inline ios_base&
  showpos(ios_base& __base)
  {
    __base.setf(ios_base::showpos);
    return __base;
  }
  inline ios_base&
  noshowpos(ios_base& __base)
  {
    __base.unsetf(ios_base::showpos);
    return __base;
  }
  inline ios_base&
  skipws(ios_base& __base)
  {
    __base.setf(ios_base::skipws);
    return __base;
  }
  inline ios_base&
  noskipws(ios_base& __base)
  {
    __base.unsetf(ios_base::skipws);
    return __base;
  }
  inline ios_base&
  uppercase(ios_base& __base)
  {
    __base.setf(ios_base::uppercase);
    return __base;
  }
  inline ios_base&
  nouppercase(ios_base& __base)
  {
    __base.unsetf(ios_base::uppercase);
    return __base;
  }
  inline ios_base&
  unitbuf(ios_base& __base)
  {
     __base.setf(ios_base::unitbuf);
     return __base;
  }
  inline ios_base&
  nounitbuf(ios_base& __base)
  {
     __base.unsetf(ios_base::unitbuf);
     return __base;
  }
  inline ios_base&
  internal(ios_base& __base)
  {
     __base.setf(ios_base::internal, ios_base::adjustfield);
     return __base;
  }
  inline ios_base&
  left(ios_base& __base)
  {
    __base.setf(ios_base::left, ios_base::adjustfield);
    return __base;
  }
  inline ios_base&
  right(ios_base& __base)
  {
    __base.setf(ios_base::right, ios_base::adjustfield);
    return __base;
  }
  inline ios_base&
  dec(ios_base& __base)
  {
    __base.setf(ios_base::dec, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  hex(ios_base& __base)
  {
    __base.setf(ios_base::hex, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  oct(ios_base& __base)
  {
    __base.setf(ios_base::oct, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  fixed(ios_base& __base)
  {
    __base.setf(ios_base::fixed, ios_base::floatfield);
    return __base;
  }
  inline ios_base&
  scientific(ios_base& __base)
  {
    __base.setf(ios_base::scientific, ios_base::floatfield);
    return __base;
  }
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>*,
     basic_streambuf<_CharT, _Traits>*, bool&);
  template<typename _CharT, typename _Traits>
    class basic_streambuf
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename traits_type::int_type int_type;
      typedef typename traits_type::pos_type pos_type;
      typedef typename traits_type::off_type off_type;
      typedef basic_streambuf<char_type, traits_type> __streambuf_type;
      friend class basic_ios<char_type, traits_type>;
      friend class basic_istream<char_type, traits_type>;
      friend class basic_ostream<char_type, traits_type>;
      friend class istreambuf_iterator<char_type, traits_type>;
      friend class ostreambuf_iterator<char_type, traits_type>;
      friend streamsize
      __copy_streambufs_eof<>(__streambuf_type*, __streambuf_type*, bool&);
      template<bool _IsMove, typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
        __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);
      template<typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
      istreambuf_iterator<_CharT2> >::__type
        find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);
      template<typename _CharT2, typename _Traits2>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&, _CharT2*);
      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&,
     basic_string<_CharT2, _Traits2, _Alloc>&);
      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        getline(basic_istream<_CharT2, _Traits2>&,
  basic_string<_CharT2, _Traits2, _Alloc>&, _CharT2);
    protected:
      char_type* _M_in_beg;
      char_type* _M_in_cur;
      char_type* _M_in_end;
      char_type* _M_out_beg;
      char_type* _M_out_cur;
      char_type* _M_out_end;
      locale _M_buf_locale;
  public:
      virtual
      ~basic_streambuf()
      { }
      locale
      pubimbue(const locale &__loc)
      {
 locale __tmp(this->getloc());
 this->imbue(__loc);
 _M_buf_locale = __loc;
 return __tmp;
      }
      locale
      getloc() const
      { return _M_buf_locale; }
      __streambuf_type*
      pubsetbuf(char_type* __s, streamsize __n)
      { return this->setbuf(__s, __n); }
      pos_type
      pubseekoff(off_type __off, ios_base::seekdir __way,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekoff(__off, __way, __mode); }
      pos_type
      pubseekpos(pos_type __sp,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekpos(__sp, __mode); }
      int
      pubsync() { return this->sync(); }
      streamsize
      in_avail()
      {
 const streamsize __ret = this->egptr() - this->gptr();
 return __ret ? __ret : this->showmanyc();
      }
      int_type
      snextc()
      {
 int_type __ret = traits_type::eof();
 if (__builtin_expect(!traits_type::eq_int_type(this->sbumpc(),
             __ret), true))
   __ret = this->sgetc();
 return __ret;
      }
      int_type
      sbumpc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 else
   __ret = this->uflow();
 return __ret;
      }
      int_type
      sgetc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   __ret = traits_type::to_int_type(*this->gptr());
 else
   __ret = this->underflow();
 return __ret;
      }
      streamsize
      sgetn(char_type* __s, streamsize __n)
      { return this->xsgetn(__s, __n); }
      int_type
      sputbackc(char_type __c)
      {
 int_type __ret;
 const bool __testpos = this->eback() < this->gptr();
 if (__builtin_expect(!__testpos ||
        !traits_type::eq(__c, this->gptr()[-1]), false))
   __ret = this->pbackfail(traits_type::to_int_type(__c));
 else
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 return __ret;
      }
      int_type
      sungetc()
      {
 int_type __ret;
 if (__builtin_expect(this->eback() < this->gptr(), true))
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 else
   __ret = this->pbackfail();
 return __ret;
      }
      int_type
      sputc(char_type __c)
      {
 int_type __ret;
 if (__builtin_expect(this->pptr() < this->epptr(), true))
   {
     *this->pptr() = __c;
     this->pbump(1);
     __ret = traits_type::to_int_type(__c);
   }
 else
   __ret = this->overflow(traits_type::to_int_type(__c));
 return __ret;
      }
      streamsize
      sputn(const char_type* __s, streamsize __n)
      { return this->xsputn(__s, __n); }
    protected:
      basic_streambuf()
      : _M_in_beg(0), _M_in_cur(0), _M_in_end(0),
      _M_out_beg(0), _M_out_cur(0), _M_out_end(0),
      _M_buf_locale(locale())
      { }
      char_type*
      eback() const { return _M_in_beg; }
      char_type*
      gptr() const { return _M_in_cur; }
      char_type*
      egptr() const { return _M_in_end; }
      void
      gbump(int __n) { _M_in_cur += __n; }
      void
      setg(char_type* __gbeg, char_type* __gnext, char_type* __gend)
      {
 _M_in_beg = __gbeg;
 _M_in_cur = __gnext;
 _M_in_end = __gend;
      }
      char_type*
      pbase() const { return _M_out_beg; }
      char_type*
      pptr() const { return _M_out_cur; }
      char_type*
      epptr() const { return _M_out_end; }
      void
      pbump(int __n) { _M_out_cur += __n; }
      void
      setp(char_type* __pbeg, char_type* __pend)
      {
 _M_out_beg = _M_out_cur = __pbeg;
 _M_out_end = __pend;
      }
      virtual void
      imbue(const locale&)
      { }
      virtual basic_streambuf<char_type,_Traits>*
      setbuf(char_type*, streamsize)
      { return this; }
      virtual pos_type
      seekoff(off_type, ios_base::seekdir,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
      virtual pos_type
      seekpos(pos_type,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
      virtual int
      sync() { return 0; }
      virtual streamsize
      showmanyc() { return 0; }
      virtual streamsize
      xsgetn(char_type* __s, streamsize __n);
      virtual int_type
      underflow()
      { return traits_type::eof(); }
      virtual int_type
      uflow()
      {
 int_type __ret = traits_type::eof();
 const bool __testeof = traits_type::eq_int_type(this->underflow(),
       __ret);
 if (!__testeof)
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 return __ret;
      }
      virtual int_type
      pbackfail(int_type = traits_type::eof())
      { return traits_type::eof(); }
      virtual streamsize
      xsputn(const char_type* __s, streamsize __n);
      virtual int_type
      overflow(int_type = traits_type::eof())
      { return traits_type::eof(); }
    public:
      void
      stossc()
      {
 if (this->gptr() < this->egptr())
   this->gbump(1);
 else
   this->uflow();
      }
    private:
      basic_streambuf(const __streambuf_type& __sb)
      : _M_in_beg(__sb._M_in_beg), _M_in_cur(__sb._M_in_cur),
      _M_in_end(__sb._M_in_end), _M_out_beg(__sb._M_out_beg),
      _M_out_cur(__sb._M_out_cur), _M_out_end(__sb._M_out_cur),
      _M_buf_locale(__sb._M_buf_locale)
      { }
      __streambuf_type&
      operator=(const __streambuf_type&) { return *this; };
    };
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>* __sbin,
     basic_streambuf<char>* __sbout, bool& __ineof);
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>* __sbin,
     basic_streambuf<wchar_t>* __sbout, bool& __ineof);
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsgetn(char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->egptr() - this->gptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(__s, this->gptr(), __len);
       __ret += __len;
       __s += __len;
       this->gbump(__len);
     }
   if (__ret < __n)
     {
       const int_type __c = this->uflow();
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    traits_type::assign(*__s++, traits_type::to_char_type(__c));
    ++__ret;
  }
       else
  break;
     }
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsputn(const char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->epptr() - this->pptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(this->pptr(), __s, __len);
       __ret += __len;
       __s += __len;
       this->pbump(__len);
     }
   if (__ret < __n)
     {
       int_type __c = this->overflow(traits_type::to_int_type(*__s));
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    ++__ret;
    ++__s;
  }
       else
  break;
     }
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>* __sbin,
     basic_streambuf<_CharT, _Traits>* __sbout,
     bool& __ineof)
    {
      streamsize __ret = 0;
      __ineof = true;
      typename _Traits::int_type __c = __sbin->sgetc();
      while (!_Traits::eq_int_type(__c, _Traits::eof()))
 {
   __c = __sbout->sputc(_Traits::to_char_type(__c));
   if (_Traits::eq_int_type(__c, _Traits::eof()))
     {
       __ineof = false;
       break;
     }
   ++__ret;
   __c = __sbin->snextc();
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    inline streamsize
    __copy_streambufs(basic_streambuf<_CharT, _Traits>* __sbin,
        basic_streambuf<_CharT, _Traits>* __sbout)
    {
      bool __ineof;
      return __copy_streambufs_eof(__sbin, __sbout, __ineof);
    }
  extern template class basic_streambuf<char>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<char>*,
        basic_streambuf<char>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>*,
     basic_streambuf<char>*, bool&);
  extern template class basic_streambuf<wchar_t>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<wchar_t>*,
        basic_streambuf<wchar_t>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>*,
     basic_streambuf<wchar_t>*, bool&);
}
       
       
       
extern "C" {
typedef int wctype_t;
typedef int wctrans_t;
int __attribute__((__cdecl__)) iswalpha (wint_t);
int __attribute__((__cdecl__)) iswalnum (wint_t);
int __attribute__((__cdecl__)) iswblank (wint_t);
int __attribute__((__cdecl__)) iswcntrl (wint_t);
int __attribute__((__cdecl__)) iswctype (wint_t, wctype_t);
int __attribute__((__cdecl__)) iswdigit (wint_t);
int __attribute__((__cdecl__)) iswgraph (wint_t);
int __attribute__((__cdecl__)) iswlower (wint_t);
int __attribute__((__cdecl__)) iswprint (wint_t);
int __attribute__((__cdecl__)) iswpunct (wint_t);
int __attribute__((__cdecl__)) iswspace (wint_t);
int __attribute__((__cdecl__)) iswupper (wint_t);
int __attribute__((__cdecl__)) iswxdigit (wint_t);
wint_t __attribute__((__cdecl__)) towctrans (wint_t, wctrans_t);
wint_t __attribute__((__cdecl__)) towupper (wint_t);
wint_t __attribute__((__cdecl__)) towlower (wint_t);
wctrans_t __attribute__((__cdecl__)) wctrans (const char *);
wctype_t __attribute__((__cdecl__)) wctype (const char *);
}
namespace std {
  using ::wctrans_t;
  using ::wctype_t;
  using ::wint_t;
  using ::iswalnum;
  using ::iswalpha;
  using ::iswblank;
  using ::iswcntrl;
  using ::iswctype;
  using ::iswdigit;
  using ::iswgraph;
  using ::iswlower;
  using ::iswprint;
  using ::iswpunct;
  using ::iswspace;
  using ::iswupper;
  using ::iswxdigit;
  using ::towctrans;
  using ::towlower;
  using ::towupper;
  using ::wctrans;
  using ::wctype;
}
       
namespace std {
  struct ctype_base
  {
    typedef const int* __to_type;
    typedef char mask;
    static const mask upper = 01;
    static const mask lower = 02;
    static const mask alpha = 01 | 02;
    static const mask digit = 04;
    static const mask xdigit = 0100 | 04;
    static const mask space = 010;
    static const mask print = 020 | 01 | 02 | 04 | 0200;
    static const mask graph = 020 | 01 | 02 | 04;
    static const mask cntrl = 040;
    static const mask punct = 020;
    static const mask alnum = 01 | 02 | 04;
  };
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    class istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT, typename _Traits::off_type,
        _CharT*, _CharT&>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename _Traits::int_type int_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_istream<_CharT, _Traits> istream_type;
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);
      template<bool _IsMove, typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
 __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
               istreambuf_iterator<_CharT2> >::__type
 find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);
    private:
      mutable streambuf_type* _M_sbuf;
      mutable int_type _M_c;
    public:
      istreambuf_iterator() throw()
      : _M_sbuf(0), _M_c(traits_type::eof()) { }
      istreambuf_iterator(istream_type& __s) throw()
      : _M_sbuf(__s.rdbuf()), _M_c(traits_type::eof()) { }
      istreambuf_iterator(streambuf_type* __s) throw()
      : _M_sbuf(__s), _M_c(traits_type::eof()) { }
      char_type
      operator*() const
      {
 return traits_type::to_char_type(_M_get());
      }
      istreambuf_iterator&
      operator++()
      {
 ;
 if (_M_sbuf)
   {
     _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return *this;
      }
      istreambuf_iterator
      operator++(int)
      {
 ;
 istreambuf_iterator __old = *this;
 if (_M_sbuf)
   {
     __old._M_c = _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return __old;
      }
      bool
      equal(const istreambuf_iterator& __b) const
      { return _M_at_eof() == __b._M_at_eof(); }
    private:
      int_type
      _M_get() const
      {
 const int_type __eof = traits_type::eof();
 int_type __ret = __eof;
 if (_M_sbuf)
   {
     if (!traits_type::eq_int_type(_M_c, __eof))
       __ret = _M_c;
     else if (!traits_type::eq_int_type((__ret = _M_sbuf->sgetc()),
            __eof))
       _M_c = __ret;
     else
       _M_sbuf = 0;
   }
 return __ret;
      }
      bool
      _M_at_eof() const
      {
 const int_type __eof = traits_type::eof();
 return traits_type::eq_int_type(_M_get(), __eof);
      }
    };
  template<typename _CharT, typename _Traits>
    inline bool
    operator==(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return __a.equal(__b); }
  template<typename _CharT, typename _Traits>
    inline bool
    operator!=(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return !__a.equal(__b); }
  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_ostream<_CharT, _Traits> ostream_type;
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);
    private:
      streambuf_type* _M_sbuf;
      bool _M_failed;
    public:
      ostreambuf_iterator(ostream_type& __s) throw ()
      : _M_sbuf(__s.rdbuf()), _M_failed(!_M_sbuf) { }
      ostreambuf_iterator(streambuf_type* __s) throw ()
      : _M_sbuf(__s), _M_failed(!_M_sbuf) { }
      ostreambuf_iterator&
      operator=(_CharT __c)
      {
 if (!_M_failed &&
     _Traits::eq_int_type(_M_sbuf->sputc(__c), _Traits::eof()))
   _M_failed = true;
 return *this;
      }
      ostreambuf_iterator&
      operator*()
      { return *this; }
      ostreambuf_iterator&
      operator++(int)
      { return *this; }
      ostreambuf_iterator&
      operator++()
      { return *this; }
      bool
      failed() const throw()
      { return _M_failed; }
      ostreambuf_iterator&
      _M_put(const _CharT* __ws, streamsize __len)
      {
 if (__builtin_expect(!_M_failed, true)
     && __builtin_expect(this->_M_sbuf->sputn(__ws, __len) != __len,
    false))
   _M_failed = true;
 return *this;
      }
    };
  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                           ostreambuf_iterator<_CharT> >::__type
    copy(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last,
  ostreambuf_iterator<_CharT> __result)
    {
      if (__first._M_sbuf && !__last._M_sbuf && !__result._M_failed)
 {
   bool __ineof;
   __copy_streambufs_eof(__first._M_sbuf, __result._M_sbuf, __ineof);
   if (!__ineof)
     __result._M_failed = true;
 }
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(_CharT* __first, _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(const _CharT* __first, const _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT> __first,
     istreambuf_iterator<_CharT> __last, _CharT* __result)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;
      if (__first._M_sbuf && !__last._M_sbuf)
 {
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof()))
     {
       const streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    traits_type::copy(__result, __sb->gptr(), __n);
    __sb->gbump(__n);
    __result += __n;
    __c = __sb->underflow();
  }
       else
  {
    *__result++ = traits_type::to_char_type(__c);
    __c = __sb->snextc();
  }
     }
 }
      return __result;
    }
  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
          istreambuf_iterator<_CharT> >::__type
    find(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last, const _CharT& __val)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;
      if (__first._M_sbuf && !__last._M_sbuf)
 {
   const int_type __ival = traits_type::to_int_type(__val);
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof())
   && !traits_type::eq_int_type(__c, __ival))
     {
       streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    const _CharT* __p = traits_type::find(__sb->gptr(),
       __n, __val);
    if (__p)
      __n = __p - __sb->gptr();
    __sb->gbump(__n);
    __c = __sb->sgetc();
  }
       else
  __c = __sb->snextc();
     }
   if (!traits_type::eq_int_type(__c, traits_type::eof()))
     __first._M_c = __c;
   else
     __first._M_sbuf = 0;
 }
      return __first;
    }
}
namespace std {
  template<typename _Tp>
    void
    __convert_to_v(const char*, _Tp&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, float&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, double&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, long double&, ios_base::iostate&,
     const __c_locale&) throw();
  template<typename _CharT, typename _Traits>
    struct __pad
    {
      static void
      _S_pad(ios_base& __io, _CharT __fill, _CharT* __news,
      const _CharT* __olds, streamsize __newlen, streamsize __oldlen);
    };
  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last);
  template<typename _CharT>
    inline
    ostreambuf_iterator<_CharT>
    __write(ostreambuf_iterator<_CharT> __s, const _CharT* __ws, int __len)
    {
      __s._M_put(__ws, __len);
      return __s;
    }
  template<typename _CharT, typename _OutIter>
    inline
    _OutIter
    __write(_OutIter __s, const _CharT* __ws, int __len)
    {
      for (int __j = 0; __j < __len; __j++, ++__s)
 *__s = __ws[__j];
      return __s;
    }
  template<typename _CharT>
    class __ctype_abstract_base : public locale::facet, public ctype_base
    {
    public:
      typedef _CharT char_type;
      bool
      is(mask __m, char_type __c) const
      { return this->do_is(__m, __c); }
      const char_type*
      is(const char_type *__lo, const char_type *__hi, mask *__vec) const
      { return this->do_is(__lo, __hi, __vec); }
      const char_type*
      scan_is(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_is(__m, __lo, __hi); }
      const char_type*
      scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_not(__m, __lo, __hi); }
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
      char_type
      widen(char __c) const
      { return this->do_widen(__c); }
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      { return this->do_widen(__lo, __hi, __to); }
      char
      narrow(char_type __c, char __dfault) const
      { return this->do_narrow(__c, __dfault); }
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
       char __dfault, char *__to) const
      { return this->do_narrow(__lo, __hi, __dfault, __to); }
    protected:
      explicit
      __ctype_abstract_base(size_t __refs = 0): facet(__refs) { }
      virtual
      ~__ctype_abstract_base() { }
      virtual bool
      do_is(mask __m, char_type __c) const = 0;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi,
     mask* __vec) const = 0;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo,
   const char_type* __hi) const = 0;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const = 0;
      virtual char_type
      do_toupper(char_type) const = 0;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const = 0;
      virtual char_type
      do_tolower(char_type) const = 0;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const = 0;
      virtual char_type
      do_widen(char) const = 0;
      virtual const char*
      do_widen(const char* __lo, const char* __hi,
        char_type* __dest) const = 0;
      virtual char
      do_narrow(char_type, char __dfault) const = 0;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __dest) const = 0;
    };
  template<typename _CharT>
    class ctype : public __ctype_abstract_base<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef typename __ctype_abstract_base<_CharT>::mask mask;
      static locale::id id;
      explicit
      ctype(size_t __refs = 0) : __ctype_abstract_base<_CharT>(__refs) { }
   protected:
      virtual
      ~ctype();
      virtual bool
      do_is(mask __m, char_type __c) const;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;
      virtual char_type
      do_toupper(char_type __c) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type __c) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char __c) const;
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;
      virtual char
      do_narrow(char_type, char __dfault) const;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __dest) const;
    };
  template<typename _CharT>
    locale::id ctype<_CharT>::id;
  template<>
    class ctype<char> : public locale::facet, public ctype_base
    {
    public:
      typedef char char_type;
    protected:
      __c_locale _M_c_locale_ctype;
      bool _M_del;
      __to_type _M_toupper;
      __to_type _M_tolower;
      const mask* _M_table;
      mutable char _M_widen_ok;
      mutable char _M_widen[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow_ok;
    public:
      static locale::id id;
      static const size_t table_size = 1 + static_cast<unsigned char>(-1);
      explicit
      ctype(const mask* __table = 0, bool __del = false, size_t __refs = 0);
      explicit
      ctype(__c_locale __cloc, const mask* __table = 0, bool __del = false,
     size_t __refs = 0);
      inline bool
      is(mask __m, char __c) const;
      inline const char*
      is(const char* __lo, const char* __hi, mask* __vec) const;
      inline const char*
      scan_is(mask __m, const char* __lo, const char* __hi) const;
      inline const char*
      scan_not(mask __m, const char* __lo, const char* __hi) const;
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
      char_type
      widen(char __c) const
      {
 if (_M_widen_ok)
   return _M_widen[static_cast<unsigned char>(__c)];
 this->_M_widen_init();
 return this->do_widen(__c);
      }
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      {
 if (_M_widen_ok == 1)
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_widen_ok)
   _M_widen_init();
 return this->do_widen(__lo, __hi, __to);
      }
      char
      narrow(char_type __c, char __dfault) const
      {
 if (_M_narrow[static_cast<unsigned char>(__c)])
   return _M_narrow[static_cast<unsigned char>(__c)];
 const char __t = do_narrow(__c, __dfault);
 if (__t != __dfault)
   _M_narrow[static_cast<unsigned char>(__c)] = __t;
 return __t;
      }
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
      char __dfault, char *__to) const
      {
 if (__builtin_expect(_M_narrow_ok == 1, true))
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_narrow_ok)
   _M_narrow_init();
 return this->do_narrow(__lo, __hi, __dfault, __to);
      }
      const mask*
      table() const throw()
      { return _M_table; }
      static const mask*
      classic_table() throw();
    protected:
      virtual
      ~ctype();
      virtual char_type
      do_toupper(char_type) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char __c) const
      { return __c; }
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const
      {
 __builtin_memcpy(__dest, __lo, __hi - __lo);
 return __hi;
      }
      virtual char
      do_narrow(char_type __c, char) const
      { return __c; }
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char, char* __dest) const
      {
 __builtin_memcpy(__dest, __lo, __hi - __lo);
 return __hi;
      }
    private:
      void _M_narrow_init() const;
      void _M_widen_init() const;
    };
  template<>
    class ctype<wchar_t> : public __ctype_abstract_base<wchar_t>
    {
    public:
      typedef wchar_t char_type;
      typedef wctype_t __wmask_type;
    protected:
      __c_locale _M_c_locale_ctype;
      bool _M_narrow_ok;
      char _M_narrow[128];
      wint_t _M_widen[1 + static_cast<unsigned char>(-1)];
      mask _M_bit[16];
      __wmask_type _M_wmask[16];
    public:
      static locale::id id;
      explicit
      ctype(size_t __refs = 0);
      explicit
      ctype(__c_locale __cloc, size_t __refs = 0);
    protected:
      __wmask_type
      _M_convert_to_wmask(const mask __m) const throw();
      virtual
      ~ctype();
      virtual bool
      do_is(mask __m, char_type __c) const;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;
      virtual char_type
      do_toupper(char_type) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char) const;
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;
      virtual char
      do_narrow(char_type, char __dfault) const;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __dest) const;
      void
      _M_initialize_ctype() throw();
    };
  template<typename _CharT>
    class ctype_byname : public ctype<_CharT>
    {
    public:
      typedef typename ctype<_CharT>::mask mask;
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname() { };
    };
  template<>
    class ctype_byname<char> : public ctype<char>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname();
    };
  template<>
    class ctype_byname<wchar_t> : public ctype<wchar_t>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname();
    };
}
namespace std {
  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return _M_table[static_cast<unsigned char>(__c)] & __m; }
  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    return __high;
  }
  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && !this->is(__m, *__low))
      ++__low;
    return __low;
  }
  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && this->is(__m, *__low) != 0)
      ++__low;
    return __low;
  }
}
namespace std {
  class __num_base
  {
  public:
    enum
      {
        _S_ominus,
        _S_oplus,
        _S_ox,
        _S_oX,
        _S_odigits,
        _S_odigits_end = _S_odigits + 16,
        _S_oudigits = _S_odigits_end,
        _S_oudigits_end = _S_oudigits + 16,
        _S_oe = _S_odigits + 14,
        _S_oE = _S_oudigits + 14,
 _S_oend = _S_oudigits_end
      };
    static const char* _S_atoms_out;
    static const char* _S_atoms_in;
    enum
    {
      _S_iminus,
      _S_iplus,
      _S_ix,
      _S_iX,
      _S_izero,
      _S_ie = _S_izero + 14,
      _S_iE = _S_izero + 20,
      _S_iend = 26
    };
    static void
    _S_format_float(const ios_base& __io, char* __fptr, char __mod) throw();
  };
  template<typename _CharT>
    struct __numpunct_cache : public locale::facet
    {
      const char* _M_grouping;
      size_t _M_grouping_size;
      bool _M_use_grouping;
      const _CharT* _M_truename;
      size_t _M_truename_size;
      const _CharT* _M_falsename;
      size_t _M_falsename_size;
      _CharT _M_decimal_point;
      _CharT _M_thousands_sep;
      _CharT _M_atoms_out[__num_base::_S_oend];
      _CharT _M_atoms_in[__num_base::_S_iend];
      bool _M_allocated;
      __numpunct_cache(size_t __refs = 0) : facet(__refs),
      _M_grouping(__null), _M_grouping_size(0), _M_use_grouping(false),
      _M_truename(__null), _M_truename_size(0), _M_falsename(__null),
      _M_falsename_size(0), _M_decimal_point(_CharT()),
      _M_thousands_sep(_CharT()), _M_allocated(false)
      { }
      ~__numpunct_cache();
      void
      _M_cache(const locale& __loc);
    private:
      __numpunct_cache&
      operator=(const __numpunct_cache&);
      explicit
      __numpunct_cache(const __numpunct_cache&);
    };
  template<typename _CharT>
    __numpunct_cache<_CharT>::~__numpunct_cache()
    {
      if (_M_allocated)
 {
   delete [] _M_grouping;
   delete [] _M_truename;
   delete [] _M_falsename;
 }
    }
  template<typename _CharT>
    class numpunct : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      typedef __numpunct_cache<_CharT> __cache_type;
    protected:
      __cache_type* _M_data;
    public:
      static locale::id id;
      explicit
      numpunct(size_t __refs = 0) : facet(__refs), _M_data(__null)
      { _M_initialize_numpunct(); }
      explicit
      numpunct(__cache_type* __cache, size_t __refs = 0)
      : facet(__refs), _M_data(__cache)
      { _M_initialize_numpunct(); }
      explicit
      numpunct(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_data(__null)
      { _M_initialize_numpunct(__cloc); }
      char_type
      decimal_point() const
      { return this->do_decimal_point(); }
      char_type
      thousands_sep() const
      { return this->do_thousands_sep(); }
      string
      grouping() const
      { return this->do_grouping(); }
      string_type
      truename() const
      { return this->do_truename(); }
      string_type
      falsename() const
      { return this->do_falsename(); }
    protected:
      virtual
      ~numpunct();
      virtual char_type
      do_decimal_point() const
      { return _M_data->_M_decimal_point; }
      virtual char_type
      do_thousands_sep() const
      { return _M_data->_M_thousands_sep; }
      virtual string
      do_grouping() const
      { return _M_data->_M_grouping; }
      virtual string_type
      do_truename() const
      { return _M_data->_M_truename; }
      virtual string_type
      do_falsename() const
      { return _M_data->_M_falsename; }
      void
      _M_initialize_numpunct(__c_locale __cloc = __null);
    };
  template<typename _CharT>
    locale::id numpunct<_CharT>::id;
  template<>
    numpunct<char>::~numpunct();
  template<>
    void
    numpunct<char>::_M_initialize_numpunct(__c_locale __cloc);
  template<>
    numpunct<wchar_t>::~numpunct();
  template<>
    void
    numpunct<wchar_t>::_M_initialize_numpunct(__c_locale __cloc);
  template<typename _CharT>
    class numpunct_byname : public numpunct<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      explicit
      numpunct_byname(const char* __s, size_t __refs = 0)
      : numpunct<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     __c_locale __tmp;
     this->_S_create_c_locale(__tmp, __s);
     this->_M_initialize_numpunct(__tmp);
     this->_S_destroy_c_locale(__tmp);
   }
      }
    protected:
      virtual
      ~numpunct_byname() { }
    };

  template<typename _CharT, typename _InIter>
    class num_get : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef _InIter iter_type;
      static locale::id id;
      explicit
      num_get(size_t __refs = 0) : facet(__refs) { }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, bool& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned short& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned int& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, float& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, void*& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
    protected:
      virtual ~num_get() { }
      iter_type
      _M_extract_float(iter_type, iter_type, ios_base&, ios_base::iostate&,
         string&) const;
      template<typename _ValueT>
        iter_type
        _M_extract_int(iter_type, iter_type, ios_base&, ios_base::iostate&,
         _ValueT&) const;
      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, int>::__type
        _M_find(const _CharT2*, size_t __len, _CharT2 __c) const
        {
   int __ret = -1;
   if (__len <= 10)
     {
       if (__c >= _CharT2('0') && __c < _CharT2(_CharT2('0') + __len))
  __ret = __c - _CharT2('0');
     }
   else
     {
       if (__c >= _CharT2('0') && __c <= _CharT2('9'))
  __ret = __c - _CharT2('0');
       else if (__c >= _CharT2('a') && __c <= _CharT2('f'))
  __ret = 10 + (__c - _CharT2('a'));
       else if (__c >= _CharT2('A') && __c <= _CharT2('F'))
  __ret = 10 + (__c - _CharT2('A'));
     }
   return __ret;
 }
      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<!__is_char<_CharT2>::__value,
          int>::__type
        _M_find(const _CharT2* __zero, size_t __len, _CharT2 __c) const
        {
   int __ret = -1;
   const char_type* __q = char_traits<_CharT2>::find(__zero, __len, __c);
   if (__q)
     {
       __ret = __q - __zero;
       if (__ret > 15)
  __ret -= 6;
     }
   return __ret;
 }
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, bool&) const;
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned short& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned int& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
      float&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
      double&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
      long double&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate& __err,
      void*&) const;
    };
  template<typename _CharT, typename _InIter>
    locale::id num_get<_CharT, _InIter>::id;
  template<typename _CharT, typename _OutIter>
    class num_put : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef _OutIter iter_type;
      static locale::id id;
      explicit
      num_put(size_t __refs = 0) : facet(__refs) { }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, bool __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, long __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
   unsigned long __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, long long __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
   unsigned long long __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill, double __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
   long double __v) const
      { return this->do_put(__s, __f, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __f, char_type __fill,
   const void* __v) const
      { return this->do_put(__s, __f, __fill, __v); }
    protected:
      template<typename _ValueT>
        iter_type
        _M_insert_float(iter_type, ios_base& __io, char_type __fill,
   char __mod, _ValueT __v) const;
      void
      _M_group_float(const char* __grouping, size_t __grouping_size,
       char_type __sep, const char_type* __p, char_type* __new,
       char_type* __cs, int& __len) const;
      template<typename _ValueT>
        iter_type
        _M_insert_int(iter_type, ios_base& __io, char_type __fill,
        _ValueT __v) const;
      void
      _M_group_int(const char* __grouping, size_t __grouping_size,
     char_type __sep, ios_base& __io, char_type* __new,
     char_type* __cs, int& __len) const;
      void
      _M_pad(char_type __fill, streamsize __w, ios_base& __io,
      char_type* __new, const char_type* __cs, int& __len) const;
      virtual
      ~num_put() { };
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, bool __v) const;
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, double __v) const;
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, long double __v) const;
      virtual iter_type
      do_put(iter_type, ios_base&, char_type __fill, const void* __v) const;
    };
  template <typename _CharT, typename _OutIter>
    locale::id num_put<_CharT, _OutIter>::id;

  template<typename _CharT>
    inline bool
    isspace(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::space, __c); }
  template<typename _CharT>
    inline bool
    isprint(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::print, __c); }
  template<typename _CharT>
    inline bool
    iscntrl(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::cntrl, __c); }
  template<typename _CharT>
    inline bool
    isupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::upper, __c); }
  template<typename _CharT>
    inline bool
    islower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::lower, __c); }
  template<typename _CharT>
    inline bool
    isalpha(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alpha, __c); }
  template<typename _CharT>
    inline bool
    isdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::digit, __c); }
  template<typename _CharT>
    inline bool
    ispunct(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::punct, __c); }
  template<typename _CharT>
    inline bool
    isxdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::xdigit, __c); }
  template<typename _CharT>
    inline bool
    isalnum(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alnum, __c); }
  template<typename _CharT>
    inline bool
    isgraph(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::graph, __c); }
  template<typename _CharT>
    inline _CharT
    toupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).toupper(__c); }
  template<typename _CharT>
    inline _CharT
    tolower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).tolower(__c); }
}
       
namespace std {
  template<typename _Facet>
    struct __use_cache
    {
      const _Facet*
      operator() (const locale& __loc) const;
    };
  template<typename _CharT>
    struct __use_cache<__numpunct_cache<_CharT> >
    {
      const __numpunct_cache<_CharT>*
      operator() (const locale& __loc) const
      {
 const size_t __i = numpunct<_CharT>::id._M_id();
 const locale::facet** __caches = __loc._M_impl->_M_caches;
 if (!__caches[__i])
   {
     __numpunct_cache<_CharT>* __tmp = __null;
     try
       {
  __tmp = new __numpunct_cache<_CharT>;
  __tmp->_M_cache(__loc);
       }
     catch(...)
       {
  delete __tmp;
  throw;
       }
     __loc._M_impl->_M_install_cache(__tmp, __i);
   }
 return static_cast<const __numpunct_cache<_CharT>*>(__caches[__i]);
      }
    };
  template<typename _CharT>
    void
    __numpunct_cache<_CharT>::_M_cache(const locale& __loc)
    {
      _M_allocated = true;
      const numpunct<_CharT>& __np = use_facet<numpunct<_CharT> >(__loc);
      char* __grouping = 0;
      _CharT* __truename = 0;
      _CharT* __falsename = 0;
      try
 {
   _M_grouping_size = __np.grouping().size();
   __grouping = new char[_M_grouping_size];
   __np.grouping().copy(__grouping, _M_grouping_size);
   _M_grouping = __grouping;
   _M_use_grouping = (_M_grouping_size
        && static_cast<signed char>(_M_grouping[0]) > 0
        && (_M_grouping[0]
     != __gnu_cxx::__numeric_traits<char>::__max));
   _M_truename_size = __np.truename().size();
   __truename = new _CharT[_M_truename_size];
   __np.truename().copy(__truename, _M_truename_size);
   _M_truename = __truename;
   _M_falsename_size = __np.falsename().size();
   __falsename = new _CharT[_M_falsename_size];
   __np.falsename().copy(__falsename, _M_falsename_size);
   _M_falsename = __falsename;
   _M_decimal_point = __np.decimal_point();
   _M_thousands_sep = __np.thousands_sep();
   const ctype<_CharT>& __ct = use_facet<ctype<_CharT> >(__loc);
   __ct.widen(__num_base::_S_atoms_out,
       __num_base::_S_atoms_out
       + __num_base::_S_oend, _M_atoms_out);
   __ct.widen(__num_base::_S_atoms_in,
       __num_base::_S_atoms_in
       + __num_base::_S_iend, _M_atoms_in);
 }
      catch(...)
 {
   delete [] __grouping;
   delete [] __truename;
   delete [] __falsename;
   throw;
 }
    }
  __attribute__ ((__pure__)) bool
  __verify_grouping(const char* __grouping, size_t __grouping_size,
      const string& __grouping_tmp) throw ();

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    _M_extract_float(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, string& __xtrc) const
    {
      typedef char_traits<_CharT> __traits_type;
      typedef __numpunct_cache<_CharT> __cache_type;
      __use_cache<__cache_type> __uc;
      const locale& __loc = __io._M_getloc();
      const __cache_type* __lc = __uc(__loc);
      const _CharT* __lit = __lc->_M_atoms_in;
      char_type __c = char_type();
      bool __testeof = __beg == __end;
      if (!__testeof)
 {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
     {
       __xtrc += __plus ? '+' : '-';
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 }
      bool __found_mantissa = false;
      int __sep_pos = 0;
      while (!__testeof)
 {
   if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       || __c == __lc->_M_decimal_point)
     break;
   else if (__c == __lit[__num_base::_S_izero])
     {
       if (!__found_mantissa)
  {
    __xtrc += '0';
    __found_mantissa = true;
  }
       ++__sep_pos;
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
   else
     break;
 }
      bool __found_dec = false;
      bool __found_sci = false;
      string __found_grouping;
      if (__lc->_M_use_grouping)
 __found_grouping.reserve(32);
      const char_type* __lit_zero = __lit + __num_base::_S_izero;
      if (!__lc->_M_allocated)
 while (!__testeof)
   {
     const int __digit = _M_find(__lit_zero, 10, __c);
     if (__digit != -1)
       {
  __xtrc += '0' + __digit;
  __found_mantissa = true;
       }
     else if (__c == __lc->_M_decimal_point
       && !__found_dec && !__found_sci)
       {
  __xtrc += '.';
  __found_dec = true;
       }
     else if ((__c == __lit[__num_base::_S_ie]
        || __c == __lit[__num_base::_S_iE])
       && !__found_sci && __found_mantissa)
       {
  __xtrc += 'e';
  __found_sci = true;
  if (++__beg != __end)
    {
      __c = *__beg;
      const bool __plus = __c == __lit[__num_base::_S_iplus];
      if (__plus || __c == __lit[__num_base::_S_iminus])
        __xtrc += __plus ? '+' : '-';
      else
        continue;
    }
  else
    {
      __testeof = true;
      break;
    }
       }
     else
       break;
     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }
      else
 while (!__testeof)
   {
     if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       {
  if (!__found_dec && !__found_sci)
    {
      if (__sep_pos)
        {
   __found_grouping += static_cast<char>(__sep_pos);
   __sep_pos = 0;
        }
      else
        {
   __xtrc.clear();
   break;
        }
    }
  else
    break;
       }
     else if (__c == __lc->_M_decimal_point)
       {
  if (!__found_dec && !__found_sci)
    {
      if (__found_grouping.size())
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += '.';
      __found_dec = true;
    }
  else
    break;
       }
     else
       {
  const char_type* __q =
    __traits_type::find(__lit_zero, 10, __c);
  if (__q)
    {
      __xtrc += '0' + (__q - __lit_zero);
      __found_mantissa = true;
      ++__sep_pos;
    }
  else if ((__c == __lit[__num_base::_S_ie]
     || __c == __lit[__num_base::_S_iE])
    && !__found_sci && __found_mantissa)
    {
      if (__found_grouping.size() && !__found_dec)
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += 'e';
      __found_sci = true;
      if (++__beg != __end)
        {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping
     && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
        __xtrc += __plus ? '+' : '-';
   else
     continue;
        }
      else
        {
   __testeof = true;
   break;
        }
    }
  else
    break;
       }
     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }
      if (__found_grouping.size())
        {
   if (!__found_dec && !__found_sci)
     __found_grouping += static_cast<char>(__sep_pos);
          if (!std::__verify_grouping(__lc->_M_grouping,
          __lc->_M_grouping_size,
          __found_grouping))
     __err = ios_base::failbit;
        }
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    template<typename _ValueT>
      _InIter
      num_get<_CharT, _InIter>::
      _M_extract_int(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, _ValueT& __v) const
      {
        typedef char_traits<_CharT> __traits_type;
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_in;
 char_type __c = char_type();
 const ios_base::fmtflags __basefield = __io.flags()
                                        & ios_base::basefield;
 const bool __oct = __basefield == ios_base::oct;
 int __base = __oct ? 8 : (__basefield == ios_base::hex ? 16 : 10);
 bool __testeof = __beg == __end;
 bool __negative = false;
 if (!__testeof)
   {
     __c = *__beg;
     __negative = __c == __lit[__num_base::_S_iminus];
     if ((__negative || __c == __lit[__num_base::_S_iplus])
  && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  && !(__c == __lc->_M_decimal_point))
       {
  if (++__beg != __end)
    __c = *__beg;
  else
    __testeof = true;
       }
   }
 bool __found_zero = false;
 int __sep_pos = 0;
 while (!__testeof)
   {
     if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  || __c == __lc->_M_decimal_point)
       break;
     else if (__c == __lit[__num_base::_S_izero]
       && (!__found_zero || __base == 10))
       {
  __found_zero = true;
  ++__sep_pos;
  if (__basefield == 0)
    __base = 8;
  if (__base == 8)
    __sep_pos = 0;
       }
     else if (__found_zero
       && (__c == __lit[__num_base::_S_ix]
    || __c == __lit[__num_base::_S_iX]))
       {
  if (__basefield == 0)
    __base = 16;
  if (__base == 16)
    {
      __found_zero = false;
      __sep_pos = 0;
    }
  else
    break;
       }
     else
       break;
     if (++__beg != __end)
       {
  __c = *__beg;
  if (!__found_zero)
    break;
       }
     else
       __testeof = true;
   }
 const size_t __len = (__base == 16 ? __num_base::_S_iend
         - __num_base::_S_izero : __base);
 string __found_grouping;
 if (__lc->_M_use_grouping)
   __found_grouping.reserve(32);
 bool __testfail = false;
 bool __testoverflow = false;
 const __unsigned_type __max =
   (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
   ? -__gnu_cxx::__numeric_traits<_ValueT>::__min
   : __gnu_cxx::__numeric_traits<_ValueT>::__max;
 const __unsigned_type __smax = __max / __base;
 __unsigned_type __result = 0;
 int __digit = 0;
 const char_type* __lit_zero = __lit + __num_base::_S_izero;
 if (!__lc->_M_allocated)
   while (!__testeof)
     {
       __digit = _M_find(__lit_zero, __len, __c);
       if (__digit == -1)
  break;
       if (__result > __smax)
  __testoverflow = true;
       else
  {
    __result *= __base;
    __testoverflow |= __result > __max - __digit;
    __result += __digit;
    ++__sep_pos;
  }
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 else
   while (!__testeof)
     {
       if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  {
    if (__sep_pos)
      {
        __found_grouping += static_cast<char>(__sep_pos);
        __sep_pos = 0;
      }
    else
      {
        __testfail = true;
        break;
      }
  }
       else if (__c == __lc->_M_decimal_point)
  break;
       else
  {
    const char_type* __q =
      __traits_type::find(__lit_zero, __len, __c);
    if (!__q)
      break;
    __digit = __q - __lit_zero;
    if (__digit > 15)
      __digit -= 6;
    if (__result > __smax)
      __testoverflow = true;
    else
      {
        __result *= __base;
        __testoverflow |= __result > __max - __digit;
        __result += __digit;
        ++__sep_pos;
      }
  }
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 if (__found_grouping.size())
   {
     __found_grouping += static_cast<char>(__sep_pos);
     if (!std::__verify_grouping(__lc->_M_grouping,
     __lc->_M_grouping_size,
     __found_grouping))
       __err = ios_base::failbit;
   }
 if ((!__sep_pos && !__found_zero && !__found_grouping.size())
     || __testfail)
   {
     __v = 0;
     __err = ios_base::failbit;
   }
 else if (__testoverflow)
   {
     if (__negative
  && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__min;
     else
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__max;
     __err = ios_base::failbit;
   }
 else
   __v = __negative ? -__result : __result;
 if (__testeof)
   __err |= ios_base::eofbit;
 return __beg;
      }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, bool& __v) const
    {
      if (!(__io.flags() & ios_base::boolalpha))
        {
   long __l = -1;
          __beg = _M_extract_int(__beg, __end, __io, __err, __l);
   if (__l == 0 || __l == 1)
     __v = bool(__l);
   else
     {
       __v = true;
       __err = ios_base::failbit;
       if (__beg == __end)
  __err |= ios_base::eofbit;
     }
        }
      else
        {
   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);
   bool __testf = true;
   bool __testt = true;
   bool __donef = __lc->_M_falsename_size == 0;
   bool __donet = __lc->_M_truename_size == 0;
   bool __testeof = false;
   size_t __n = 0;
   while (!__donef || !__donet)
     {
       if (__beg == __end)
  {
    __testeof = true;
    break;
  }
       const char_type __c = *__beg;
       if (!__donef)
  __testf = __c == __lc->_M_falsename[__n];
       if (!__testf && __donet)
  break;
       if (!__donet)
  __testt = __c == __lc->_M_truename[__n];
       if (!__testt && __donef)
  break;
       if (!__testt && !__testf)
  break;
       ++__n;
       ++__beg;
       __donef = !__testf || __n >= __lc->_M_falsename_size;
       __donet = !__testt || __n >= __lc->_M_truename_size;
     }
   if (__testf && __n == __lc->_M_falsename_size && __n)
     {
       __v = false;
       if (__testt && __n == __lc->_M_truename_size)
  __err = ios_base::failbit;
       else
  __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else if (__testt && __n == __lc->_M_truename_size && __n)
     {
       __v = true;
       __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else
     {
       __v = false;
       __err = ios_base::failbit;
       if (__testeof)
  __err |= ios_base::eofbit;
     }
 }
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
    ios_base::iostate& __err, float& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, long double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, void*& __v) const
    {
      typedef ios_base::fmtflags fmtflags;
      const fmtflags __fmt = __io.flags();
      __io.flags((__fmt & ~ios_base::basefield) | ios_base::hex);
      typedef __gnu_cxx::__conditional_type<(sizeof(void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;
      _UIntPtrType __ul;
      __beg = _M_extract_int(__beg, __end, __io, __err, __ul);
      __io.flags(__fmt);
      __v = reinterpret_cast<void*>(__ul);
      return __beg;
    }
  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_pad(_CharT __fill, streamsize __w, ios_base& __io,
    _CharT* __new, const _CharT* __cs, int& __len) const
    {
      __pad<_CharT, char_traits<_CharT> >::_S_pad(__io, __fill, __new,
        __cs, __w, __len);
      __len = static_cast<int>(__w);
    }

  template<typename _CharT, typename _ValueT>
    int
    __int_to_char(_CharT* __bufend, _ValueT __v, const _CharT* __lit,
    ios_base::fmtflags __flags, bool __dec)
    {
      _CharT* __buf = __bufend;
      if (__builtin_expect(__dec, true))
 {
   do
     {
       *--__buf = __lit[(__v % 10) + __num_base::_S_odigits];
       __v /= 10;
     }
   while (__v != 0);
 }
      else if ((__flags & ios_base::basefield) == ios_base::oct)
 {
   do
     {
       *--__buf = __lit[(__v & 0x7) + __num_base::_S_odigits];
       __v >>= 3;
     }
   while (__v != 0);
 }
      else
 {
   const bool __uppercase = __flags & ios_base::uppercase;
   const int __case_offset = __uppercase ? __num_base::_S_oudigits
                                         : __num_base::_S_odigits;
   do
     {
       *--__buf = __lit[(__v & 0xf) + __case_offset];
       __v >>= 4;
     }
   while (__v != 0);
 }
      return __bufend - __buf;
    }

  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_int(const char* __grouping, size_t __grouping_size, _CharT __sep,
   ios_base&, _CharT* __new, _CharT* __cs, int& __len) const
    {
      _CharT* __p = std::__add_grouping(__new, __sep, __grouping,
     __grouping_size, __cs, __cs + __len);
      __len = __p - __new;
    }
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_int(_OutIter __s, ios_base& __io, _CharT __fill,
      _ValueT __v) const
      {
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_out;
 const ios_base::fmtflags __flags = __io.flags();
 const int __ilen = 5 * sizeof(_ValueT);
 _CharT* __cs = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __ilen));
 const ios_base::fmtflags __basefield = __flags & ios_base::basefield;
 const bool __dec = (__basefield != ios_base::oct
       && __basefield != ios_base::hex);
 const __unsigned_type __u = ((__v > 0 || !__dec)
         ? __unsigned_type(__v)
         : -__unsigned_type(__v));
  int __len = __int_to_char(__cs + __ilen, __u, __lit, __flags, __dec);
 __cs += __ilen - __len;
 if (__lc->_M_use_grouping)
   {
     _CharT* __cs2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * (__len + 1)
          * 2));
     _M_group_int(__lc->_M_grouping, __lc->_M_grouping_size,
    __lc->_M_thousands_sep, __io, __cs2 + 2, __cs, __len);
     __cs = __cs2 + 2;
   }
 if (__builtin_expect(__dec, true))
   {
     if (__v >= 0)
       {
  if (bool(__flags & ios_base::showpos)
      && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
    *--__cs = __lit[__num_base::_S_oplus], ++__len;
       }
     else
       *--__cs = __lit[__num_base::_S_ominus], ++__len;
   }
 else if (bool(__flags & ios_base::showbase) && __v)
   {
     if (__basefield == ios_base::oct)
       *--__cs = __lit[__num_base::_S_odigits], ++__len;
     else
       {
  const bool __uppercase = __flags & ios_base::uppercase;
  *--__cs = __lit[__num_base::_S_ox + __uppercase];
  *--__cs = __lit[__num_base::_S_odigits];
  __len += 2;
       }
   }
 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __cs3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __cs3, __cs, __len);
     __cs = __cs3;
   }
 __io.width(0);
 return std::__write(__s, __cs, __len);
      }
  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_float(const char* __grouping, size_t __grouping_size,
     _CharT __sep, const _CharT* __p, _CharT* __new,
     _CharT* __cs, int& __len) const
    {
      const int __declen = __p ? __p - __cs : __len;
      _CharT* __p2 = std::__add_grouping(__new, __sep, __grouping,
      __grouping_size,
      __cs, __cs + __declen);
      int __newlen = __p2 - __new;
      if (__p)
 {
   char_traits<_CharT>::copy(__p2, __p, __len - __declen);
   __newlen += __len - __declen;
 }
      __len = __newlen;
    }
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_float(_OutIter __s, ios_base& __io, _CharT __fill, char __mod,
         _ValueT __v) const
      {
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const streamsize __prec = __io.precision() < 0 ? 6 : __io.precision();
 const int __max_digits =
   __gnu_cxx::__numeric_traits<_ValueT>::__digits10;
 int __len;
 char __fbuf[16];
 __num_base::_S_format_float(__io, __fbuf, __mod);
 const bool __fixed = __io.flags() & ios_base::fixed;
 const int __max_exp =
   __gnu_cxx::__numeric_traits<_ValueT>::__max_exponent10;
 const int __cs_size = __fixed ? __max_exp + __prec + 4
                               : __max_digits * 2 + __prec;
 char* __cs = static_cast<char*>(__builtin_alloca(__cs_size));
 __len = std::__convert_from_v(_S_get_c_locale(), __cs, 0, __fbuf,
          __prec, __v);
 const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);
 _CharT* __ws = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __len));
 __ctype.widen(__cs, __cs + __len, __ws);
 _CharT* __wp = 0;
 const char* __p = char_traits<char>::find(__cs, __len, '.');
 if (__p)
   {
     __wp = __ws + (__p - __cs);
     *__wp = __lc->_M_decimal_point;
   }
 if (__lc->_M_use_grouping
     && (__wp || __len < 3 || (__cs[1] <= '9' && __cs[2] <= '9'
          && __cs[1] >= '0' && __cs[2] >= '0')))
   {
     _CharT* __ws2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __len * 2));
     streamsize __off = 0;
     if (__cs[0] == '-' || __cs[0] == '+')
       {
  __off = 1;
  __ws2[0] = __ws[0];
  __len -= 1;
       }
     _M_group_float(__lc->_M_grouping, __lc->_M_grouping_size,
      __lc->_M_thousands_sep, __wp, __ws2 + __off,
      __ws + __off, __len);
     __len += __off;
     __ws = __ws2;
   }
 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __ws3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __ws3, __ws, __len);
     __ws = __ws3;
   }
 __io.width(0);
 return std::__write(__s, __ws, __len);
      }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      if ((__flags & ios_base::boolalpha) == 0)
        {
          const long __l = __v;
          __s = _M_insert_int(__s, __io, __fill, __l);
        }
      else
        {
   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);
   const _CharT* __name = __v ? __lc->_M_truename
                              : __lc->_M_falsename;
   int __len = __v ? __lc->_M_truename_size
                   : __lc->_M_falsename_size;
   const streamsize __w = __io.width();
   if (__w > static_cast<streamsize>(__len))
     {
       const streamsize __plen = __w - __len;
       _CharT* __ps
  = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
       * __plen));
       char_traits<_CharT>::assign(__ps, __plen, __fill);
       __io.width(0);
       if ((__flags & ios_base::adjustfield) == ios_base::left)
  {
    __s = std::__write(__s, __name, __len);
    __s = std::__write(__s, __ps, __plen);
  }
       else
  {
    __s = std::__write(__s, __ps, __plen);
    __s = std::__write(__s, __name, __len);
  }
       return __s;
     }
   __io.width(0);
   __s = std::__write(__s, __name, __len);
 }
      return __s;
    }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
    { return _M_insert_float(__s, __io, __fill, char(), __v); }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
    long double __v) const
    { return _M_insert_float(__s, __io, __fill, 'L', __v); }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
           const void* __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      const ios_base::fmtflags __fmt = ~(ios_base::basefield
      | ios_base::uppercase);
      __io.flags((__flags & __fmt) | (ios_base::hex | ios_base::showbase));
      typedef __gnu_cxx::__conditional_type<(sizeof(const void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;
      __s = _M_insert_int(__s, __io, __fill,
     reinterpret_cast<_UIntPtrType>(__v));
      __io.flags(__flags);
      return __s;
    }

  template<typename _CharT, typename _Traits>
    void
    __pad<_CharT, _Traits>::_S_pad(ios_base& __io, _CharT __fill,
       _CharT* __news, const _CharT* __olds,
       streamsize __newlen, streamsize __oldlen)
    {
      const size_t __plen = static_cast<size_t>(__newlen - __oldlen);
      const ios_base::fmtflags __adjust = __io.flags() & ios_base::adjustfield;
      if (__adjust == ios_base::left)
 {
   _Traits::copy(__news, __olds, __oldlen);
   _Traits::assign(__news + __oldlen, __plen, __fill);
   return;
 }
      size_t __mod = 0;
      if (__adjust == ios_base::internal)
 {
          const locale& __loc = __io._M_getloc();
   const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);
   if (__ctype.widen('-') == __olds[0]
       || __ctype.widen('+') == __olds[0])
     {
       __news[0] = __olds[0];
       __mod = 1;
       ++__news;
     }
   else if (__ctype.widen('0') == __olds[0]
     && __oldlen > 1
     && (__ctype.widen('x') == __olds[1]
         || __ctype.widen('X') == __olds[1]))
     {
       __news[0] = __olds[0];
       __news[1] = __olds[1];
       __mod = 2;
       __news += 2;
     }
 }
      _Traits::assign(__news, __plen, __fill);
      _Traits::copy(__news + __plen, __olds + __mod, __oldlen - __mod);
    }
  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last)
    {
      size_t __idx = 0;
      size_t __ctr = 0;
      while (__last - __first > __gbeg[__idx]
      && static_cast<signed char>(__gbeg[__idx]) > 0
      && __gbeg[__idx] != __gnu_cxx::__numeric_traits<char>::__max)
 {
   __last -= __gbeg[__idx];
   __idx < __gsize - 1 ? ++__idx : ++__ctr;
 }
      while (__first != __last)
 *__s++ = *__first++;
      while (__ctr--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }
      while (__idx--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }
      return __s;
    }
  extern template class numpunct<char>;
  extern template class numpunct_byname<char>;
  extern template class num_get<char>;
  extern template class num_put<char>;
  extern template class ctype_byname<char>;
  extern template
    const ctype<char>&
    use_facet<ctype<char> >(const locale&);
  extern template
    const numpunct<char>&
    use_facet<numpunct<char> >(const locale&);
  extern template
    const num_put<char>&
    use_facet<num_put<char> >(const locale&);
  extern template
    const num_get<char>&
    use_facet<num_get<char> >(const locale&);
  extern template
    bool
    has_facet<ctype<char> >(const locale&);
  extern template
    bool
    has_facet<numpunct<char> >(const locale&);
  extern template
    bool
    has_facet<num_put<char> >(const locale&);
  extern template
    bool
    has_facet<num_get<char> >(const locale&);
  extern template class numpunct<wchar_t>;
  extern template class numpunct_byname<wchar_t>;
  extern template class num_get<wchar_t>;
  extern template class num_put<wchar_t>;
  extern template class ctype_byname<wchar_t>;
  extern template
    const ctype<wchar_t>&
    use_facet<ctype<wchar_t> >(const locale&);
  extern template
    const numpunct<wchar_t>&
    use_facet<numpunct<wchar_t> >(const locale&);
  extern template
    const num_put<wchar_t>&
    use_facet<num_put<wchar_t> >(const locale&);
  extern template
    const num_get<wchar_t>&
    use_facet<num_get<wchar_t> >(const locale&);
 extern template
    bool
    has_facet<ctype<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<numpunct<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<num_put<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<num_get<wchar_t> >(const locale&);
}
namespace std {
  template<typename _Facet>
    inline const _Facet&
    __check_facet(const _Facet* __f)
    {
      if (!__f)
 __throw_bad_cast();
      return *__f;
    }
  template<typename _CharT, typename _Traits>
    class basic_ios : public ios_base
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef ctype<_CharT> __ctype_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
           __num_put_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
           __num_get_type;
    protected:
      basic_ostream<_CharT, _Traits>* _M_tie;
      mutable char_type _M_fill;
      mutable bool _M_fill_init;
      basic_streambuf<_CharT, _Traits>* _M_streambuf;
      const __ctype_type* _M_ctype;
      const __num_put_type* _M_num_put;
      const __num_get_type* _M_num_get;
    public:
      operator void*() const
      { return this->fail() ? 0 : const_cast<basic_ios*>(this); }
      bool
      operator!() const
      { return this->fail(); }
      iostate
      rdstate() const
      { return _M_streambuf_state; }
      void
      clear(iostate __state = goodbit);
      void
      setstate(iostate __state)
      { this->clear(this->rdstate() | __state); }
      void
      _M_setstate(iostate __state)
      {
 _M_streambuf_state |= __state;
 if (this->exceptions() & __state)
   throw;
      }
      bool
      good() const
      { return this->rdstate() == 0; }
      bool
      eof() const
      { return (this->rdstate() & eofbit) != 0; }
      bool
      fail() const
      { return (this->rdstate() & (badbit | failbit)) != 0; }
      bool
      bad() const
      { return (this->rdstate() & badbit) != 0; }
      iostate
      exceptions() const
      { return _M_exception; }
      void
      exceptions(iostate __except)
      {
        _M_exception = __except;
        this->clear(_M_streambuf_state);
      }
      explicit
      basic_ios(basic_streambuf<_CharT, _Traits>* __sb)
      : ios_base(), _M_tie(0), _M_fill(), _M_fill_init(false), _M_streambuf(0),
 _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { this->init(__sb); }
      virtual
      ~basic_ios() { }
      basic_ostream<_CharT, _Traits>*
      tie() const
      { return _M_tie; }
      basic_ostream<_CharT, _Traits>*
      tie(basic_ostream<_CharT, _Traits>* __tiestr)
      {
        basic_ostream<_CharT, _Traits>* __old = _M_tie;
        _M_tie = __tiestr;
        return __old;
      }
      basic_streambuf<_CharT, _Traits>*
      rdbuf() const
      { return _M_streambuf; }
      basic_streambuf<_CharT, _Traits>*
      rdbuf(basic_streambuf<_CharT, _Traits>* __sb);
      basic_ios&
      copyfmt(const basic_ios& __rhs);
      char_type
      fill() const
      {
 if (!_M_fill_init)
   {
     _M_fill = this->widen(' ');
     _M_fill_init = true;
   }
 return _M_fill;
      }
      char_type
      fill(char_type __ch)
      {
 char_type __old = this->fill();
 _M_fill = __ch;
 return __old;
      }
      locale
      imbue(const locale& __loc);
      char
      narrow(char_type __c, char __dfault) const
      { return __check_facet(_M_ctype).narrow(__c, __dfault); }
      char_type
      widen(char __c) const
      { return __check_facet(_M_ctype).widen(__c); }
    protected:
      basic_ios()
      : ios_base(), _M_tie(0), _M_fill(char_type()), _M_fill_init(false),
 _M_streambuf(0), _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { }
      void
      init(basic_streambuf<_CharT, _Traits>* __sb);
      void
      _M_cache_locale(const locale& __loc);
    };
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::clear(iostate __state)
    {
      if (this->rdbuf())
 _M_streambuf_state = __state;
      else
   _M_streambuf_state = __state | badbit;
      if (this->exceptions() & this->rdstate())
 __throw_ios_failure(("basic_ios::clear"));
    }
  template<typename _CharT, typename _Traits>
    basic_streambuf<_CharT, _Traits>*
    basic_ios<_CharT, _Traits>::rdbuf(basic_streambuf<_CharT, _Traits>* __sb)
    {
      basic_streambuf<_CharT, _Traits>* __old = _M_streambuf;
      _M_streambuf = __sb;
      this->clear();
      return __old;
    }
  template<typename _CharT, typename _Traits>
    basic_ios<_CharT, _Traits>&
    basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
    {
      if (this != &__rhs)
 {
   _Words* __words = (__rhs._M_word_size <= _S_local_word_size) ?
                      _M_local_word : new _Words[__rhs._M_word_size];
   _Callback_list* __cb = __rhs._M_callbacks;
   if (__cb)
     __cb->_M_add_reference();
   _M_call_callbacks(erase_event);
   if (_M_word != _M_local_word)
     {
       delete [] _M_word;
       _M_word = 0;
     }
   _M_dispose_callbacks();
   _M_callbacks = __cb;
   for (int __i = 0; __i < __rhs._M_word_size; ++__i)
     __words[__i] = __rhs._M_word[__i];
   _M_word = __words;
   _M_word_size = __rhs._M_word_size;
   this->flags(__rhs.flags());
   this->width(__rhs.width());
   this->precision(__rhs.precision());
   this->tie(__rhs.tie());
   this->fill(__rhs.fill());
   _M_ios_locale = __rhs.getloc();
   _M_cache_locale(_M_ios_locale);
   _M_call_callbacks(copyfmt_event);
   this->exceptions(__rhs.exceptions());
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    locale
    basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
    {
      locale __old(this->getloc());
      ios_base::imbue(__loc);
      _M_cache_locale(__loc);
      if (this->rdbuf() != 0)
 this->rdbuf()->pubimbue(__loc);
      return __old;
    }
  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::init(basic_streambuf<_CharT, _Traits>* __sb)
    {
      ios_base::_M_init();
      _M_cache_locale(_M_ios_locale);
      _M_fill = _CharT();
      _M_fill_init = false;
      _M_tie = 0;
      _M_exception = goodbit;
      _M_streambuf = __sb;
      _M_streambuf_state = __sb ? goodbit : badbit;
    }
  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::_M_cache_locale(const locale& __loc)
    {
      if (__builtin_expect(has_facet<__ctype_type>(__loc), true))
 _M_ctype = &use_facet<__ctype_type>(__loc);
      else
 _M_ctype = 0;
      if (__builtin_expect(has_facet<__num_put_type>(__loc), true))
 _M_num_put = &use_facet<__num_put_type>(__loc);
      else
 _M_num_put = 0;
      if (__builtin_expect(has_facet<__num_get_type>(__loc), true))
 _M_num_get = &use_facet<__num_get_type>(__loc);
      else
 _M_num_get = 0;
    }
  extern template class basic_ios<char>;
  extern template class basic_ios<wchar_t>;
}
namespace std {
  template<typename _CharT, typename _Traits>
    class basic_ostream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
             __num_put_type;
      typedef ctype<_CharT> __ctype_type;
      explicit
      basic_ostream(__streambuf_type* __sb)
      { this->init(__sb); }
      virtual
      ~basic_ostream() { }
      class sentry;
      friend class sentry;
      __ostream_type&
      operator<<(__ostream_type& (*__pf)(__ostream_type&))
      {
 return __pf(*this);
      }
      __ostream_type&
      operator<<(__ios_type& (*__pf)(__ios_type&))
      {
 __pf(*this);
 return *this;
      }
      __ostream_type&
      operator<<(ios_base& (*__pf) (ios_base&))
      {
 __pf(*this);
 return *this;
      }
      __ostream_type&
      operator<<(long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(unsigned long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(bool __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(short __n);
      __ostream_type&
      operator<<(unsigned short __n)
      {
 return _M_insert(static_cast<unsigned long>(__n));
      }
      __ostream_type&
      operator<<(int __n);
      __ostream_type&
      operator<<(unsigned int __n)
      {
 return _M_insert(static_cast<unsigned long>(__n));
      }
      __ostream_type&
      operator<<(long long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(unsigned long long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(double __f)
      { return _M_insert(__f); }
      __ostream_type&
      operator<<(float __f)
      {
 return _M_insert(static_cast<double>(__f));
      }
      __ostream_type&
      operator<<(long double __f)
      { return _M_insert(__f); }
      __ostream_type&
      operator<<(const void* __p)
      { return _M_insert(__p); }
      __ostream_type&
      operator<<(__streambuf_type* __sb);
      __ostream_type&
      put(char_type __c);
      void
      _M_write(const char_type* __s, streamsize __n)
      {
 const streamsize __put = this->rdbuf()->sputn(__s, __n);
 if (__put != __n)
   this->setstate(ios_base::badbit);
      }
      __ostream_type&
      write(const char_type* __s, streamsize __n);
      __ostream_type&
      flush();
      pos_type
      tellp();
      __ostream_type&
      seekp(pos_type);
       __ostream_type&
      seekp(off_type, ios_base::seekdir);
    protected:
      basic_ostream()
      { this->init(0); }
      template<typename _ValueT>
        __ostream_type&
        _M_insert(_ValueT __v);
    };
  template <typename _CharT, typename _Traits>
    class basic_ostream<_CharT, _Traits>::sentry
    {
      bool _M_ok;
      basic_ostream<_CharT, _Traits>& _M_os;
    public:
      explicit
      sentry(basic_ostream<_CharT, _Traits>& __os);
      ~sentry()
      {
 if (bool(_M_os.flags() & ios_base::unitbuf) && !uncaught_exception())
   {
     if (_M_os.rdbuf() && _M_os.rdbuf()->pubsync() == -1)
       _M_os.setstate(ios_base::badbit);
   }
      }
      operator bool() const
      { return _M_ok; }
    };
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, _CharT __c)
    { return __ostream_insert(__out, &__c, 1); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, char __c)
    { return (__out << __out.widen(__c)); }
  template <class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, char __c)
    { return __ostream_insert(__out, &__c, 1); }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, signed char __c)
    { return (__out << static_cast<char>(__c)); }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, unsigned char __c)
    { return (__out << static_cast<char>(__c)); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const _CharT* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits> &
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s);
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const signed char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
  template<class _Traits>
    inline basic_ostream<char, _Traits> &
    operator<<(basic_ostream<char, _Traits>& __out, const unsigned char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    endl(basic_ostream<_CharT, _Traits>& __os)
    { return flush(__os.put(__os.widen('\n'))); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    ends(basic_ostream<_CharT, _Traits>& __os)
    { return __os.put(_CharT()); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    flush(basic_ostream<_CharT, _Traits>& __os)
    { return __os.flush(); }
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>::sentry::
    sentry(basic_ostream<_CharT, _Traits>& __os)
    : _M_ok(false), _M_os(__os)
    {
      if (__os.tie() && __os.good())
 __os.tie()->flush();
      if (__os.good())
 _M_ok = true;
      else
 __os.setstate(ios_base::failbit);
    }
  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::
      _M_insert(_ValueT __v)
      {
 sentry __cerb(*this);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_put_type& __np = __check_facet(this->_M_num_put);
  if (__np.put(*this, *this, this->fill(), __v).failed())
    __err |= ios_base::badbit;
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(short __n)
    {
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned short>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(int __n)
    {
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned int>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(__streambuf_type* __sbin)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this);
      if (__cerb && __sbin)
 {
   try
     {
       if (!__copy_streambufs(__sbin, this->rdbuf()))
  __err |= ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbin)
 __err |= ios_base::badbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    put(char_type __c)
    {
      sentry __cerb(*this);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __put = this->rdbuf()->sputc(__c);
       if (traits_type::eq_int_type(__put, traits_type::eof()))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    write(const _CharT* __s, streamsize __n)
    {
      sentry __cerb(*this);
      if (__cerb)
 {
   try
     { _M_write(__s, __n); }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    flush()
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (this->rdbuf() && this->rdbuf()->pubsync() == -1)
     __err |= ios_base::badbit;
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_ostream<_CharT, _Traits>::pos_type
    basic_ostream<_CharT, _Traits>::
    tellp()
    {
      pos_type __ret = pos_type(-1);
      try
 {
   if (!this->fail())
     __ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(pos_type __pos)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekpos(__pos,
            ios_base::out);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(off_type __off, ios_base::seekdir __dir)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
            ios_base::out);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 {
   const size_t __clen = char_traits<char>::length(__s);
   try
     {
       struct __ptr_guard
       {
  _CharT *__p;
  __ptr_guard (_CharT *__ip): __p(__ip) { }
  ~__ptr_guard() { delete[] __p; }
  _CharT* __get() { return __p; }
       } __pg (new _CharT[__clen]);
       _CharT *__ws = __pg.__get();
       for (size_t __i = 0; __i < __clen; ++__i)
  __ws[__i] = __out.widen(__s[__i]);
       __ostream_insert(__out, __ws, __clen);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(ios_base::badbit); }
 }
      return __out;
    }
  extern template class basic_ostream<char>;
  extern template ostream& endl(ostream&);
  extern template ostream& ends(ostream&);
  extern template ostream& flush(ostream&);
  extern template ostream& operator<<(ostream&, char);
  extern template ostream& operator<<(ostream&, unsigned char);
  extern template ostream& operator<<(ostream&, signed char);
  extern template ostream& operator<<(ostream&, const char*);
  extern template ostream& operator<<(ostream&, const unsigned char*);
  extern template ostream& operator<<(ostream&, const signed char*);
  extern template ostream& ostream::_M_insert(long);
  extern template ostream& ostream::_M_insert(unsigned long);
  extern template ostream& ostream::_M_insert(bool);
  extern template ostream& ostream::_M_insert(long long);
  extern template ostream& ostream::_M_insert(unsigned long long);
  extern template ostream& ostream::_M_insert(double);
  extern template ostream& ostream::_M_insert(long double);
  extern template ostream& ostream::_M_insert(const void*);
  extern template class basic_ostream<wchar_t>;
  extern template wostream& endl(wostream&);
  extern template wostream& ends(wostream&);
  extern template wostream& flush(wostream&);
  extern template wostream& operator<<(wostream&, wchar_t);
  extern template wostream& operator<<(wostream&, char);
  extern template wostream& operator<<(wostream&, const wchar_t*);
  extern template wostream& operator<<(wostream&, const char*);
  extern template wostream& wostream::_M_insert(long);
  extern template wostream& wostream::_M_insert(unsigned long);
  extern template wostream& wostream::_M_insert(bool);
  extern template wostream& wostream::_M_insert(long long);
  extern template wostream& wostream::_M_insert(unsigned long long);
  extern template wostream& wostream::_M_insert(double);
  extern template wostream& wostream::_M_insert(long double);
  extern template wostream& wostream::_M_insert(const void*);
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    class basic_istream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
        __num_get_type;
      typedef ctype<_CharT> __ctype_type;
    protected:
      streamsize _M_gcount;
    public:
      explicit
      basic_istream(__streambuf_type* __sb)
      : _M_gcount(streamsize(0))
      { this->init(__sb); }
      virtual
      ~basic_istream()
      { _M_gcount = streamsize(0); }
      class sentry;
      friend class sentry;
      __istream_type&
      operator>>(__istream_type& (*__pf)(__istream_type&))
      { return __pf(*this); }
      __istream_type&
      operator>>(__ios_type& (*__pf)(__ios_type&))
      {
 __pf(*this);
 return *this;
      }
      __istream_type&
      operator>>(ios_base& (*__pf)(ios_base&))
      {
 __pf(*this);
 return *this;
      }
      __istream_type&
      operator>>(bool& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(short& __n);
      __istream_type&
      operator>>(unsigned short& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(int& __n);
      __istream_type&
      operator>>(unsigned int& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(unsigned long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(long long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(unsigned long long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(float& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(double& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(long double& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(void*& __p)
      { return _M_extract(__p); }
      __istream_type&
      operator>>(__streambuf_type* __sb);
      streamsize
      gcount() const
      { return _M_gcount; }
      int_type
      get();
      __istream_type&
      get(char_type& __c);
      __istream_type&
      get(char_type* __s, streamsize __n, char_type __delim);
      __istream_type&
      get(char_type* __s, streamsize __n)
      { return this->get(__s, __n, this->widen('\n')); }
      __istream_type&
      get(__streambuf_type& __sb, char_type __delim);
      __istream_type&
      get(__streambuf_type& __sb)
      { return this->get(__sb, this->widen('\n')); }
      __istream_type&
      getline(char_type* __s, streamsize __n, char_type __delim);
      __istream_type&
      getline(char_type* __s, streamsize __n)
      { return this->getline(__s, __n, this->widen('\n')); }
      __istream_type&
      ignore();
      __istream_type&
      ignore(streamsize __n);
      __istream_type&
      ignore(streamsize __n, int_type __delim);
      int_type
      peek();
      __istream_type&
      read(char_type* __s, streamsize __n);
      streamsize
      readsome(char_type* __s, streamsize __n);
      __istream_type&
      putback(char_type __c);
      __istream_type&
      unget();
      int
      sync();
      pos_type
      tellg();
      __istream_type&
      seekg(pos_type);
      __istream_type&
      seekg(off_type, ios_base::seekdir);
    protected:
      basic_istream()
      : _M_gcount(streamsize(0))
      { this->init(0); }
      template<typename _ValueT>
        __istream_type&
        _M_extract(_ValueT& __v);
    };
  template<>
    basic_istream<char>&
    basic_istream<char>::
    getline(char_type* __s, streamsize __n, char_type __delim);
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n);
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n, int_type __delim);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    getline(char_type* __s, streamsize __n, char_type __delim);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n, int_type __delim);
  template<typename _CharT, typename _Traits>
    class basic_istream<_CharT, _Traits>::sentry
    {
      bool _M_ok;
    public:
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::__ctype_type __ctype_type;
      typedef typename _Traits::int_type __int_type;
      explicit
      sentry(basic_istream<_CharT, _Traits>& __is, bool __noskipws = false);
      operator bool() const
      { return _M_ok; }
    };
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c);
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s);
  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __in, char* __s);
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
  template<typename _CharT, typename _Traits>
    class basic_iostream
    : public basic_istream<_CharT, _Traits>,
      public basic_ostream<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      explicit
      basic_iostream(basic_streambuf<_CharT, _Traits>* __sb)
      : __istream_type(__sb), __ostream_type(__sb) { }
      virtual
      ~basic_iostream() { }
    protected:
      basic_iostream()
      : __istream_type(), __ostream_type() { }
    };
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __is);
}
       
namespace std {
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>::sentry::
    sentry(basic_istream<_CharT, _Traits>& __in, bool __noskip) : _M_ok(false)
    {
      ios_base::iostate __err = ios_base::goodbit;
      if (__in.good())
 {
   if (__in.tie())
     __in.tie()->flush();
   if (!__noskip && bool(__in.flags() & ios_base::skipws))
     {
       const __int_type __eof = traits_type::eof();
       __streambuf_type* __sb = __in.rdbuf();
       __int_type __c = __sb->sgetc();
       const __ctype_type& __ct = __check_facet(__in._M_ctype);
       while (!traits_type::eq_int_type(__c, __eof)
       && __ct.is(ctype_base::space,
    traits_type::to_char_type(__c)))
  __c = __sb->snextc();
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
 }
      if (__in.good() && __err == ios_base::goodbit)
 _M_ok = true;
      else
 {
   __err |= ios_base::failbit;
   __in.setstate(__err);
 }
    }
  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_istream<_CharT, _Traits>&
      basic_istream<_CharT, _Traits>::
      _M_extract(_ValueT& __v)
      {
 sentry __cerb(*this, false);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_get_type& __ng = __check_facet(this->_M_num_get);
  __ng.get(*this, 0, *this, __err, __v);
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(short& __n)
    {
      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);
       if (__l < __gnu_cxx::__numeric_traits<short>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<short>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__max;
  }
       else
  __n = short(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(int& __n)
    {
      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);
       if (__l < __gnu_cxx::__numeric_traits<int>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<int>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__max;
  }
       else
  __n = int(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(__streambuf_type* __sbout)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, false);
      if (__cerb && __sbout)
 {
   try
     {
       bool __ineof;
       if (!__copy_streambufs_eof(this->rdbuf(), __sbout, __ineof))
  __err |= ios_base::failbit;
       if (__ineof)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::failbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbout)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    get(void)
    {
      const int_type __eof = traits_type::eof();
      int_type __c = __eof;
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       __c = this->rdbuf()->sbumpc();
       if (!traits_type::eq_int_type(__c, __eof))
  _M_gcount = 1;
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return __c;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type& __c)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __cb = this->rdbuf()->sbumpc();
       if (!traits_type::eq_int_type(__cb, traits_type::eof()))
  {
    _M_gcount = 1;
    __c = traits_type::to_char_type(__cb);
  }
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       int_type __c = __sb->sgetc();
       while (_M_gcount + 1 < __n
       && !traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim))
  {
    *__s++ = traits_type::to_char_type(__c);
    ++_M_gcount;
    __c = __sb->snextc();
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(__streambuf_type& __sb, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __this_sb = this->rdbuf();
       int_type __c = __this_sb->sgetc();
       char_type __c2 = traits_type::to_char_type(__c);
       while (!traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim)
       && !traits_type::eq_int_type(__sb.sputc(__c2), __eof))
  {
    ++_M_gcount;
    __c = __this_sb->snextc();
    __c2 = traits_type::to_char_type(__c);
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    getline(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
        {
          try
            {
              const int_type __idelim = traits_type::to_int_type(__delim);
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
              while (_M_gcount + 1 < __n
                     && !traits_type::eq_int_type(__c, __eof)
                     && !traits_type::eq_int_type(__c, __idelim))
                {
                  *__s++ = traits_type::to_char_type(__c);
                  __c = __sb->snextc();
                  ++_M_gcount;
                }
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
              else
                {
                  if (traits_type::eq_int_type(__c, __idelim))
                    {
                      __sb->sbumpc();
                      ++_M_gcount;
                    }
                  else
                    __err |= ios_base::failbit;
                }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
        }
      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
        __err |= ios_base::failbit;
      if (__err)
        this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(void)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (traits_type::eq_int_type(__sb->sbumpc(), __eof))
  __err |= ios_base::eofbit;
       else
  _M_gcount = 1;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }
       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;
       if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n, int_type __delim)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof)
    && !traits_type::eq_int_type(__c, __delim))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof)
        && !traits_type::eq_int_type(__c, __delim))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }
       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
       else if (traits_type::eq_int_type(__c, __delim))
  {
    if (_M_gcount
        < __gnu_cxx::__numeric_traits<streamsize>::__max)
      ++_M_gcount;
    __sb->sbumpc();
  }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    peek(void)
    {
      int_type __c = traits_type::eof();
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __c = this->rdbuf()->sgetc();
       if (traits_type::eq_int_type(__c, traits_type::eof()))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __c;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    read(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       _M_gcount = this->rdbuf()->sgetn(__s, __n);
       if (_M_gcount != __n)
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    basic_istream<_CharT, _Traits>::
    readsome(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const streamsize __num = this->rdbuf()->in_avail();
       if (__num > 0)
  _M_gcount = this->rdbuf()->sgetn(__s, std::min(__num, __n));
       else if (__num == -1)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return _M_gcount;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    putback(char_type __c)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sputbackc(__c), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    unget(void)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sungetc(), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    int
    basic_istream<_CharT, _Traits>::
    sync(void)
    {
      int __ret = -1;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __streambuf_type* __sb = this->rdbuf();
       if (__sb)
  {
    if (__sb->pubsync() == -1)
      __err |= ios_base::badbit;
    else
      __ret = 0;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::pos_type
    basic_istream<_CharT, _Traits>::
    tellg(void)
    {
      pos_type __ret = pos_type(-1);
      try
 {
   if (!this->fail())
     __ret = this->rdbuf()->pubseekoff(0, ios_base::cur,
           ios_base::in);
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(pos_type __pos)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekpos(__pos,
            ios_base::in);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(off_type __off, ios_base::seekdir __dir)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
            ios_base::in);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::int_type __int_type;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const __int_type __cb = __in.rdbuf()->sbumpc();
       if (!_Traits::eq_int_type(__cb, _Traits::eof()))
  __c = _Traits::to_char_type(__cb);
       else
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
   if (__err)
     __in.setstate(__err);
 }
      return __in;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename _Traits::int_type int_type;
      typedef _CharT char_type;
      typedef ctype<_CharT> __ctype_type;
      streamsize __extracted = 0;
      ios_base::iostate __err = ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {
       streamsize __num = __in.width();
       if (__num <= 0)
  __num = __gnu_cxx::__numeric_traits<streamsize>::__max;
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const int_type __eof = _Traits::eof();
       __streambuf_type* __sb = __in.rdbuf();
       int_type __c = __sb->sgetc();
       while (__extracted < __num - 1
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    *__s++ = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __sb->snextc();
  }
       if (_Traits::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
       *__s = char_type();
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
 }
      if (!__extracted)
 __err |= ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __in)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename __istream_type::int_type __int_type;
      typedef ctype<_CharT> __ctype_type;
      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
      const __int_type __eof = _Traits::eof();
      __streambuf_type* __sb = __in.rdbuf();
      __int_type __c = __sb->sgetc();
      while (!_Traits::eq_int_type(__c, __eof)
      && __ct.is(ctype_base::space, _Traits::to_char_type(__c)))
 __c = __sb->snextc();
       if (_Traits::eq_int_type(__c, __eof))
  __in.setstate(ios_base::eofbit);
      return __in;
    }
  extern template class basic_istream<char>;
  extern template istream& ws(istream&);
  extern template istream& operator>>(istream&, char&);
  extern template istream& operator>>(istream&, char*);
  extern template istream& operator>>(istream&, unsigned char&);
  extern template istream& operator>>(istream&, signed char&);
  extern template istream& operator>>(istream&, unsigned char*);
  extern template istream& operator>>(istream&, signed char*);
  extern template istream& istream::_M_extract(unsigned short&);
  extern template istream& istream::_M_extract(unsigned int&);
  extern template istream& istream::_M_extract(long&);
  extern template istream& istream::_M_extract(unsigned long&);
  extern template istream& istream::_M_extract(bool&);
  extern template istream& istream::_M_extract(long long&);
  extern template istream& istream::_M_extract(unsigned long long&);
  extern template istream& istream::_M_extract(float&);
  extern template istream& istream::_M_extract(double&);
  extern template istream& istream::_M_extract(long double&);
  extern template istream& istream::_M_extract(void*&);
  extern template class basic_iostream<char>;
  extern template class basic_istream<wchar_t>;
  extern template wistream& ws(wistream&);
  extern template wistream& operator>>(wistream&, wchar_t&);
  extern template wistream& operator>>(wistream&, wchar_t*);
  extern template wistream& wistream::_M_extract(unsigned short&);
  extern template wistream& wistream::_M_extract(unsigned int&);
  extern template wistream& wistream::_M_extract(long&);
  extern template wistream& wistream::_M_extract(unsigned long&);
  extern template wistream& wistream::_M_extract(bool&);
  extern template wistream& wistream::_M_extract(long long&);
  extern template wistream& wistream::_M_extract(unsigned long long&);
  extern template wistream& wistream::_M_extract(float&);
  extern template wistream& wistream::_M_extract(double&);
  extern template wistream& wistream::_M_extract(long double&);
  extern template wistream& wistream::_M_extract(void*&);
  extern template class basic_iostream<wchar_t>;
}
namespace std {
  extern istream cin;
  extern ostream cout;
  extern ostream cerr;
  extern ostream clog;
  extern wistream wcin;
  extern wostream wcout;
  extern wostream wcerr;
  extern wostream wclog;
  static ios_base::Init __ioinit;
}
       
extern "C" {
void __attribute__((__cdecl__)) __assert (const char *, int, const char *) __attribute__ ((__noreturn__));
void __attribute__((__cdecl__)) __assert_func (const char *, int, const char *, const char *) __attribute__ ((__noreturn__));
}
int main() {
    int sum = 0, factor = 10;
    void (*ERROR_missing_result_type_before_the_local_function_parameter_macro_id10)(); typedef void (*boost_closure_auxXdeduce_result_tagX10X)( int ERROR_missing_result_type_before_the_local_function_parameter_macro_id10 ) ; typedef __typeof__(boost::type_of::ensure_obj(::boost::scope_exit::aux::wrap( ::boost::scope_exit::aux::deref( ERROR_missing_result_type_before_the_local_function_parameter_macro_id10, (boost_closure_auxXdeduce_result_tagX10X)0 ) ))) boost_closure_auxXdeduce_result_wrapX10X ; typedef boost_closure_auxXdeduce_result_wrapX10X::type boost_closure_auxXdeduce_result_captureX10X ; struct boost_closure_auxXdeduce_result_paramsX10X { typedef boost_closure_auxXdeduce_result_captureX10X function_ptr; }; typedef ::boost::remove_pointer< boost_closure_auxXdeduce_result_paramsX10X::function_ptr >::type boost_closure_auxXdeduce_result_function_typeX10X ; typedef ::boost::function_traits< boost_closure_auxXdeduce_result_function_typeX10X >::result_type boost_closure_auxXresult_typeX10X ; typedef void (*boost_se_tag_0_10)(int & sum); typedef void (*boost_se_tag_1_10)(int factor); typedef __typeof__(boost::type_of::ensure_obj(boost::scope_exit::aux::wrap( boost::scope_exit::aux::deref(& sum, (boost_se_tag_0_10)0)))) boost_se_wrapped_t_0_10; typedef boost_se_wrapped_t_0_10::type boost_se_capture_t_0_10; typedef __typeof__(boost::type_of::ensure_obj(boost::scope_exit::aux::wrap( boost::scope_exit::aux::deref(factor, (boost_se_tag_1_10)0)))) boost_se_wrapped_t_1_10; typedef boost_se_wrapped_t_1_10::type boost_se_capture_t_1_10; struct boost_se_params_t_10 { typedef boost_se_capture_t_0_10 boost_se_param_t_0_10; typedef boost_se_capture_t_1_10 boost_se_param_t_1_10; boost::function_traits< void ( ::boost::scope_exit::aux::member< boost_se_param_t_0_10 , boost_se_tag_0_10 > ) >::arg1_type boost_se_param_0_10; boost::function_traits< void ( ::boost::scope_exit::aux::member< boost_se_param_t_1_10 , boost_se_tag_1_10 > ) >::arg1_type boost_se_param_1_10; } boost_closure_auxXparamsX10X = { { boost::scope_exit::aux::deref(& sum, (boost_se_tag_0_10)0) } , { boost::scope_exit::aux::deref(factor, (boost_se_tag_1_10)0) } }; ::boost::scope_exit::aux::declared< boost::scope_exit::aux::resolve< sizeof(boost_closure_auxXargsX) >::cmp1<0>::cmp2 > boost_closure_auxXargsX; boost_closure_auxXargsX.value = &boost_closure_auxXparamsX10X; class boost_closure_auxXfunctorX10X { typedef boost_closure_auxXresult_typeX10X (boost_closure_auxXfunction_typeX) ( int num ); typedef boost::function_traits< void ( ::boost::local::aux::function< boost_closure_auxXfunction_typeX , 0 > ) >::arg1_type boost_closure_auxXfunctor_typeX ; typedef ::boost::add_const< boost_se_params_t_10:: boost_se_param_t_0_10 >::type factorXtypeof_typeXboost_closure_auxX ; typedef boost_se_params_t_10:: boost_se_param_t_1_10 & sumXtypeof_typeXboost_closure_auxX ; public: inline explicit boost_closure_auxXfunctorX10X( void* bind_params) : boost_closure_auxXbindX0X ( static_cast< boost_se_params_t_10* >(bind_params)-> boost_se_param_0_10.value ) , boost_closure_auxXbindX1X ( static_cast< boost_se_params_t_10* >(bind_params)-> boost_se_param_1_10.value ) { } inline boost_closure_auxXresult_typeX10X operator()( ::boost::call_traits< ::boost::function_traits< boost_closure_auxXfunction_typeX >::arg1_type >::param_type arg1 ) const { return boost_closure_auxXbodyX( boost_closure_auxXbindX0X , boost_closure_auxXbindX1X , arg1 ); } inline static boost_closure_auxXresult_typeX10X boost_closure_auxXcallX0X( void* object , ::boost::call_traits< ::boost::function_traits< boost_closure_auxXfunction_typeX >::arg1_type >::param_type arg1 ) { return static_cast< boost_closure_auxXfunctorX10X* >( object)->operator()( arg1 ); } inline static void boost_closure_auxXinit_callX( void* object, boost_closure_auxXfunctor_typeX& functor) { functor.boost_closure_auxXinit_callX(object, &boost_closure_auxXcallX0X ); } private: ::boost::add_const< boost_se_params_t_10:: boost_se_param_t_0_10 >::type & boost_closure_auxXbindX0X ; boost_se_params_t_10:: boost_se_param_t_1_10 & boost_closure_auxXbindX1X ; boost::scope_exit::aux::undeclared boost_closure_auxXargsX; inline boost_closure_auxXresult_typeX10X boost_closure_auxXbodyX( ::boost::add_const< boost_se_params_t_10:: boost_se_param_t_0_10 >::type factor , boost_se_params_t_10:: boost_se_param_t_1_10 & sum , int num ) const {
        sum += factor * num;
        std::cout << "Summed: " << sum << std::endl;
    } public: boost_closure_auxXfunctor_typeX boost_closure_auxXnon_recursiveX; } boost_closure_auxXaddX(boost_closure_auxXargsX.value); __typeof__(boost::type_of::ensure_obj(boost_closure_auxXaddX. boost_closure_auxXnon_recursiveX)) add; boost_closure_auxXaddX.boost_closure_auxXinit_callX( &boost_closure_auxXaddX, add);
    add(1);
    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add);
    ((sum == 60) ? (void)0 : __assert_func ("02.cpp", 20, __PRETTY_FUNCTION__, "sum == 60"));
    return 0;
}
