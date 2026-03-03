
#ifndef ERRORS_SYSTEM
#define ERRORS_SYSTEM

#ifdef __linux__
#define EPERM 1
#define ENOENT 2
#define ESRCH 3
#define EINTR 4
#define EIO 5
#define ENXIO 6
#define E2BIG 7
#define ENOEXEC 8
#define EBADF 9
#define ECHILD 10
#define EAGAIN 11
#define ENOMEM 12
#define EACCES 13
#define EFAULT 14
#define ENOTBLK 15
#define EBUSY 16
#define EEXIST 17
#define EXDEV 18
#define ENODEV 19
#define ENOTDIR 20
#define EISDIR 21
#define EINVAL 22
#define ENFILE 23
#define EMFILE 24
#define ENOTTY 25
#define ETXTBSY 26
#define EFBIG 27
#define ENOSPC 28
#define ESPIPE 29
#define EROFS 30
#define EMLINK 31
#define EPIPE 32
#define EDOM 33
#define ERANGE 34
#define EDEADLK 35
#define ENAMETOOLONG 36
#define ENOLCK 37
#define ENOSYS 38
#define ENOTEMPTY 39
#define ELOOP 40
#define ENOMSG 42
#define EIDRM 43
#define ECHRNG 44
#define EL2NSYNC 45
#define EL3HLT 46
#define EL3RST 47
#define ELNRNG 48
#define EUNATCH 49
#define ENOCSI 50
#define EL2HLT 51
#define EBADE 52
#define EBADR 53
#define EXFULL 54
#define ENOANO 55
#define EBADRQC 56
#define EBADSLT 57
#define EBFONT 59
#define ENOSTR 60
#define ENODATA 61
#define ETIME 62
#define ENOSR 63
#define ENONET 64
#define ENOPKG 65
#define EREMOTE 66
#define ENOLINK 67
#define EADV 68
#define ESRMNT 69
#define ECOMM 70
#define EPROTO 71
#define EMULTIHOP 72
#define EDOTDOT 73
#define EBADMSG 74
#define EOVERFLOW 75
#define ENOTUNIQ 76
#define EBADFD 77
#define EREMCHG 78
#define ELIBACC 79
#define ELIBBAD 80
#define ELIBSCN 81
#define ELIBMAX 82
#define ELIBEXEC 83
#define EILSEQ 84
#define ERESTART 85
#define ESTRPIPE 86
#define EUSERS 87
#define ENOTSOCK 88
#define EDESTADDRREQ 89
#define EMSGSIZE 90
#define EPROTOTYPE 91
#define ENOPROTOOPT 92
#define EPROTONOSUPPORT 93
#define ESOCKTNOSUPPORT 94
#define EOPNOTSUPP 95
#define EPFNOSUPPORT 96
#define EAFNOSUPPORT 97
#define EADDRINUSE 98
#define EADDRNOTAVAIL 99
#define ENETDOWN 100
#define ENETUNREACH 101
#define ENETRESET 102
#define ECONNABORTED 103
#define ECONNRESET 104
#define ENOBUFS 105
#define EISCONN 106
#define ENOTCONN 107
#define ESHUTDOWN 108
#define ETOOMANYREFS 109
#define ETIMEDOUT 110
#define ECONNREFUSED 111
#define EHOSTDOWN 112
#define EHOSTUNREACH 113
#define EALREADY 114
#define EINPROGRESS 115
#define ESTALE 116
#define EUCLEAN 117
#define ENOTNAM 118
#define ENAVAIL 119
#define EISNAM 120
#define EREMOTEIO 121
#define EDQUOT 122
#define ENOMEDIUM 123
#define EMEDIUMTYPE 124
#define ECANCELED 125
#define ENOKEY 126
#define EKEYEXPIRED 127
#define EKEYREVOKED 128
#define EKEYREJECTED 129
#define EOWNERDEAD 130
#define ENOTRECOVERABLE 131
#define ERFKILL 132
#define EHWPOISON 133
#define ERRORS_LIST                                     \
  {"Success",                                           \
   "Operation not permitted",                           \
   "No such file or directory",                         \
   "No such process",                                   \
   "Interrupted system call",                           \
   "Input/output error",                                \
   "No such device or address",                         \
   "Argument list too long",                            \
   "Exec format error",                                 \
   "Bad file descriptor",                               \
   "No child processes",                                \
   "Resource temporarily unavailable",                  \
   "Cannot allocate memory",                            \
   "Permission denied",                                 \
   "Bad address",                                       \
   "Block device required",                             \
   "Device or resource busy",                           \
   "File exists",                                       \
   "Invalid cross-device link",                         \
   "No such device",                                    \
   "Not a directory",                                   \
   "Is a directory",                                    \
   "Invalid argument",                                  \
   "Too many open files in system",                     \
   "Too many open files",                               \
   "Inappropriate ioctl for device",                    \
   "Text file busy",                                    \
   "File too large",                                    \
   "No space left on device",                           \
   "Illegal seek",                                      \
   "Read-only file system",                             \
   "Too many links",                                    \
   "Broken pipe",                                       \
   "Numerical argument out of domain",                  \
   "Numerical result out of range",                     \
   "Resource deadlock avoided",                         \
   "File name too long",                                \
   "No locks available",                                \
   "Function not implemented",                          \
   "Directory not empty",                               \
   "Too many levels of symbolic links",                 \
   "Unknown error 41",                                  \
   "No message of desired type",                        \
   "Identifier removed",                                \
   "Channel number out of range",                       \
   "Level 2 not synchronized",                          \
   "Level 3 halted",                                    \
   "Level 3 reset",                                     \
   "Link number out of range",                          \
   "Protocol driver not attached",                      \
   "No CSI structure available",                        \
   "Level 2 halted",                                    \
   "Invalid exchange",                                  \
   "Invalid request descriptor",                        \
   "Exchange full",                                     \
   "No anode",                                          \
   "Invalid request code",                              \
   "Invalid slot",                                      \
   "Unknown error 58",                                  \
   "Bad font file format",                              \
   "Device not a stream",                               \
   "No data available",                                 \
   "Timer expired",                                     \
   "Out of streams resources",                          \
   "Machine is not on the network",                     \
   "Package not installed",                             \
   "Object is remote",                                  \
   "Link has been severed",                             \
   "Advertise error",                                   \
   "Srmount error",                                     \
   "Communication error on send",                       \
   "Protocol error",                                    \
   "Multihop attempted",                                \
   "RFS specific error",                                \
   "Bad message",                                       \
   "Value too large for defined data type",             \
   "Name not unique on network",                        \
   "File descriptor in bad state",                      \
   "Remote address changed",                            \
   "Can not access a needed shared library",            \
   "Accessing a corrupted shared library",              \
   ".lib section in a.out corrupted",                   \
   "Attempting to link in too many shared libraries",   \
   "Cannot exec a shared library directly",             \
   "Invalid or incomplete multibyte or wide character", \
   "Interrupted system call should be restarted",       \
   "Streams pipe error",                                \
   "Too many users",                                    \
   "Socket operation on non-socket",                    \
   "Destination address required",                      \
   "Message too long",                                  \
   "Protocol wrong type for socket",                    \
   "Protocol not available",                            \
   "Protocol not supported",                            \
   "Socket type not supported",                         \
   "Operation not supported",                           \
   "Protocol family not supported",                     \
   "Address family not supported by protocol",          \
   "Address already in use",                            \
   "Cannot assign requested address",                   \
   "Network is down",                                   \
   "Network is unreachable",                            \
   "Network dropped connection on reset",               \
   "Software caused connection abort",                  \
   "Connection reset by peer",                          \
   "No buffer space available",                         \
   "Transport endpoint is already connected",           \
   "Transport endpoint is not connected",               \
   "Cannot send after transport endpoint shutdown",     \
   "Too many references: cannot splice",                \
   "Connection timed out",                              \
   "Connection refused",                                \
   "Host is down",                                      \
   "No route to host",                                  \
   "Operation already in progress",                     \
   "Operation now in progress",                         \
   "Stale file handle",                                 \
   "Structure needs cleaning",                          \
   "Not a XENIX named type file",                       \
   "No XENIX semaphores available",                     \
   "Is a named type file",                              \
   "Remote I/O error",                                  \
   "Disk quota exceeded",                               \
   "No medium found",                                   \
   "Wrong medium type",                                 \
   "Operation canceled",                                \
   "Required key not available",                        \
   "Key has expired",                                   \
   "Key has been revoked",                              \
   "Key was rejected by service",                       \
   "Owner died",                                        \
   "State not recoverable",                             \
   "Operation not possible due to RF-kill",             \
   "Memory page has hardware error"}

#elif __MACH__ || __APPLE__
#define EPERM 1
#define ENOENT 2
#define ESRCH 3
#define EINTR 4
#define EIO 5
#define ENXIO 6
#define E2BIG 7
#define ENOEXEC 8
#define EBADF 9
#define ECHILD 10
#define EDEADLK 11
#define ENOMEM 12
#define EACCES 13
#define EFAULT 14
#define ENOTBLK 15
#define EBUSY 16
#define EEXIST 17
#define EXDEV 18
#define ENODEV 19
#define ENOTDIR 20
#define EISDIR 21
#define EINVAL 22
#define ENFILE 23
#define EMFILE 24
#define ENOTTY 25
#define ETXTBSY 26
#define EFBIG 27
#define ENOSPC 28
#define ESPIPE 29
#define EROFS 30
#define EMLINK 31
#define EPIPE 32
#define EDOM 33
#define ERANGE 34
#define EAGAIN 35
#define EINPROGRESS 36
#define EALREADY 37
#define ENOTSOCK 38
#define EDESTADDRREQ 39
#define EMSGSIZE 40
#define EPROTOTYPE 41
#define ENOPROTOOPT 42
#define EPROTONOSUPPORT 43
#define ESOCKTNOSUPPORT 44
#define ENOTSUP 45
#define EPFNOSUPPORT 46
#define EAFNOSUPPORT 47
#define EADDRINUSE 48
#define EADDRNOTAVAIL 49
#define ENETDOWN 50
#define ENETUNREACH 51
#define ENETRESET 52
#define ECONNABORTED 53
#define ECONNRESET 54
#define ENOBUFS 55
#define EISCONN 56
#define ENOTCONN 57
#define ESHUTDOWN 58
#define ETOOMANYREFS 59
#define ETIMEDOUT 60
#define ECONNREFUSED 61
#define ELOOP 62
#define ENAMETOOLONG 63
#define EHOSTDOWN 64
#define EHOSTUNREACH 65
#define ENOTEMPTY 66
#define EPROCLIM 67
#define EUSERS 68
#define EDQUOT 69
#define ESTALE 70
#define EREMOTE 71
#define EBADRPC 72
#define ERPCMISMATCH 73
#define EPROGUNAVAIL 74
#define EPROGMISMATCH 75
#define EPROCUNAVAIL 76
#define ENOLCK 77
#define ENOSYS 78
#define EFTYPE 79
#define EAUTH 80
#define ENEEDAUTH 81
#define EPWROFF 82
#define EDEVERR 83
#define EOVERFLOW 84
#define EBADEXEC 85
#define EBADARCH 86
#define ESHLIBVERS 87
#define EBADMACHO 88
#define ECANCELED 89
#define EIDRM 90
#define ENOMSG 91
#define EILSEQ 92
#define ENOATTR 93
#define EBADMSG 94
#define EMULTIHOP 95
#define ENODATA 96
#define ENOLINK 97
#define ENOSR 98
#define ENOSTR 99
#define EPROTO 100
#define ETIME 101
#define EOPNOTSUPP 102
#define ENOPOLICY 103
#define ENOTRECOVERABLE 104
#define EOWNERDEAD 105
#define EQFULL 106

#define ERRORS_LIST                                   \
  {"Undefined error: 0",                              \
   "Operation not permitted",                         \
   "No such file or directory",                       \
   "No such process",                                 \
   "Interrupted system call",                         \
   "Input/output error",                              \
   "Device not configured",                           \
   "Argument list too long",                          \
   "Exec format error",                               \
   "Bad file descriptor",                             \
   "No child processes",                              \
   "Resource deadlock avoided",                       \
   "Cannot allocate memory",                          \
   "Permission denied",                               \
   "Bad address",                                     \
   "Block device required",                           \
   "Resource busy",                                   \
   "File exists",                                     \
   "Cross-device link",                               \
   "Operation not supported by device",               \
   "Not a directory",                                 \
   "Is a directory",                                  \
   "Invalid argument",                                \
   "Too many open files in system",                   \
   "Too many open files",                             \
   "Inappropriate ioctl for device",                  \
   "Text file busy",                                  \
   "File too large",                                  \
   "No space left on device",                         \
   "Illegal seek",                                    \
   "Read-only file system",                           \
   "Too many links",                                  \
   "Broken pipe",                                     \
   "Numerical argument out of domain",                \
   "Result too large",                                \
   "Resource temporarily unavailable",                \
   "Operation now in progress",                       \
   "Operation already in progress",                   \
   "Socket operation on non-socket",                  \
   "Destination address required",                    \
   "Message too long",                                \
   "Protocol wrong type for socket",                  \
   "Protocol not available",                          \
   "Protocol not supported",                          \
   "Socket type not supported",                       \
   "Operation not supported",                         \
   "Protocol family not supported",                   \
   "Address family not supported by protocol family", \
   "Address already in use",                          \
   "Can't assign requested address",                  \
   "Network is down",                                 \
   "Network is unreachable",                          \
   "Network dropped connection on reset",             \
   "Software caused connection abort",                \
   "Connection reset by peer",                        \
   "No buffer space available",                       \
   "Socket is already connected",                     \
   "Socket is not connected",                         \
   "Can't send after socket shutdown",                \
   "Too many references: can't splice",               \
   "Operation timed out",                             \
   "Connection refused",                              \
   "Too many levels of symbolic links",               \
   "File name too long",                              \
   "Host is down",                                    \
   "No route to host",                                \
   "Directory not empty",                             \
   "Too many processes",                              \
   "Too many users",                                  \
   "Disc quota exceeded",                             \
   "Stale NFS file handle",                           \
   "Too many levels of remote in path",               \
   "RPC struct is bad",                               \
   "RPC version wrong",                               \
   "RPC prog. not avail",                             \
   "Program version wrong",                           \
   "Bad procedure for program",                       \
   "No locks available",                              \
   "Function not implemented",                        \
   "Inappropriate file type or format",               \
   "Authentication error",                            \
   "Need authenticator",                              \
   "Device power is off",                             \
   "Device error",                                    \
   "Value too large to be stored in data type",       \
   "Bad executable (or shared library)",              \
   "Bad CPU type in executable",                      \
   "Shared library version mismatch",                 \
   "Malformed Mach-o file",                           \
   "Operation canceled",                              \
   "Identifier removed",                              \
   "No message of desired type",                      \
   "Illegal byte sequence",                           \
   "Attribute not found",                             \
   "Bad message",                                     \
   "EMULTIHOP (Reserved)",                            \
   "No message available on STREAM",                  \
   "ENOLINK (Reserved)",                              \
   "No STREAM resources",                             \
   "Not a STREAM",                                    \
   "Protocol error",                                  \
   "STREAM ioctl timeout",                            \
   "Operation not supported on socket",               \
   "Policy not found",                                \
   "State not recoverable",                           \
   "Previous owner died",                             \
   "Interface output queue is full",                  \
   "Capabilities insufficient"}
#endif

#endif
