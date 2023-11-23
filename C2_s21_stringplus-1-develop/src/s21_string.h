#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define s21_size_t unsigned long
#define s21_NULL (void *)0

#define MAX_XLEN 17
#define MAX_OLEN 23

typedef struct {
  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
} specifiers;

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int width;
  int precision;
  int len_h;
  int len_l;
  int len_L;
  int emp;
} flags;

typedef struct {
  int flagEr;
  int stopFl;
  char *x;
  int size;
  int countStar;
  int countNumber;
  int countPoint;
} numFlags;

typedef struct {
  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
} specf_scan;
typedef struct {
  int star;
  int width;
  int len_h;
  int len_l;
  int len_L;
} flags_scan;

#if defined(__APPLE__) || defined(__MACH__)
#define ERRSIZE 107
static const char s[3] = ": ";
static const char errors[ERRSIZE][100] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif

#if defined(__linux__)
#define ERRSIZE 134
static const char s[2] = " ";
static const char errors[ERRSIZE][100] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};
#endif

char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strrchr(const char *str, int c);
char *s21_strerror(int errnum);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dst, const void *src, s21_size_t n);
void *s21_memmove(void *dst, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_trim(const char *src, const char *trim_chars);
int firstindex(const char *src, const char *totrim, int start);
int lastindex(const char *src, const char *totrim, int offset);

s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strtok(char *str1, const char *str2);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);
int s21_sprintf(char *str, const char *format, ...);

int searchSpecif(int *index, const char *format, specifiers *spec);
int searchFlags(int *begin, int end, const char *format, flags *fl);
int searWidPrec(int *begin, int end, const char *format, flags *fl,
                va_list *args);
void searchStar(int *begin, int index, numFlags *num, const char *format,
                char *buffer, int *value, va_list *args);
void c_func(char *str, int *result, flags fl, va_list *args);
void s_func(char *str, int *result, flags fl, va_list *args);
void n_func(int result, va_list *args);
void insertSpace(char *str, int *result, int count);
void copyChar(char *str, int *result, char ch);
void searchNumber(int *begin, int index, numFlags *fl, const char *format,
                  char *buffer);
int searchLen(int *begin, int end, const char *format, flags *fl);
void outPut(flags fl, specifiers spec);
void swFlags(flags *fl, char ch);
void swSpecif(specifiers *spec, char ch);
int checkError(int begin, int end, const char *format);
int parser(const char *format, int *index, va_list *args, flags *fl,
           specifiers *spec, int *result, char *str);
int f_e_g_func(char *str, int *result, flags *flag, va_list args, specifiers s);
int exp_func(long double *exp);
void after_dot(flags flag, char *tmp, long double right);
void before_dot(char *tmp, int sdvig, long double left);
void flag_w(flags f, char *str);
void r_doble(char *str, int round);
void prec_nzero(flags flag, char *tmp);
int plus_or_space(flags flag, char *tmp, int sdvig, long double num);
void add_e_E(char *str, long int sign_, s21_size_t len, specifiers s);
// void g_func(flags *flag, long double g);
void g_func(flags *flag, long double g, specifiers *s);
void g_zero(char *tmp, int precision);
int significant_digits(long double right);

void check_res(char *tmp, int *res);
void round_9(long double num, flags flag);

int len_of_int(long long int num);
int s21_itoa(long long int n, char *str);

int s21_atoi(const char *str);

long length_flag(long d, flags fl, va_list args);
void int_to_str(unsigned long int n, char *str);
int len_of_i(unsigned long int num);
int int_func(char *str, int *result, flags fl, specifiers spec, va_list args);
void width(char *str, int *result, flags fl, int len);
void space(char *str, int *result);
void precision(char *str, int *result, flags fl, int len, specifiers spec);

void hexadecimal(unsigned long d, char *buf, int *len, specifiers spec);
void sharp(char *str, int *result, specifiers spec);
void octal(unsigned long d, char *buf, int *len);
unsigned long unsigned_value(long d, flags fl);
void sign(char *str, int *result, long d);
int num_length(specifiers spec, long d, unsigned long u);
void flag_processing(flags *fl, specifiers spec, long d);
void reverse_str(int len, char *buf);
void percent(int *i, char *str, int *result);
unsigned long p_func(flags *fl, va_list args, specifiers *spec);

/*-----------------SCAN------------------*/

int s21_sscanf(const char *str, const char *format, ...);
void body(const char *format, const char *src, int *result, va_list *args);
int s21_isspace(char c);
int pasrer_scan(const char *format, int *index, specf_scan *spec,
                flags_scan *fl, int *stop);
void scan_i(char **src, specf_scan *spec);
void scan_d(char **src, flags_scan *flag, va_list *args, int *count,
            int *stop_scan, int *for_n);
void scan_s(char **str, va_list *args, flags_scan *flag, int *count,
            specf_scan *s, int *stop_scan, int *skip, int *for_n);
void scan_u(char **src, flags_scan *flag, va_list *args, int *count,
            int *stop_scan, int *for_n);
void scan_s(char **str, va_list *args, flags_scan *flag, int *count,
            specf_scan *s, int *stop_scan, int *skip, int *for_n);
void scan_f(char **src, va_list *args, flags_scan *flag, int *count,
            int *stop_scan, int *for_n);
void scan_n(va_list *args, flags_scan *flag, int *stop_scan, int *for_n);
void scan_hex(char **src, flags_scan *f, va_list *args, specf_scan *spec,
              int *result, int *stop_scan, int *for_n);
void skip_space(char **src);
int is_num(char c);
void get_char(char **src, char **buf, char **temp, int *len, flags_scan *f);
void conv_ubsigned(va_list *args, char *temp, flags_scan *flag);
long long int s21_con_ch_int(const char *str);
void only_hex_o(char **src, char *buf, specf_scan *spec, int *len, int *sdvig);
long long unsigned int atoi_hex(char *str, specf_scan *spec, int *sign);
void conv_hex(flags_scan *f, va_list *args, long long unsigned int *num,
              specf_scan *spec);
int is_float(char *str);
long double atoi_f(char *str);
void convert_float(long double num, void *ptr, flags_scan *f);
int s21_ischar(char *str);
void copy_string(va_list *args, flags_scan *flag, char *t1, specf_scan *s);
void convert_int(long long int num, void *ptr, flags_scan *f);
int searchwght_sc(int *begin, const char *format, flags_scan *fl);
int searchLen_scan(int *begin, const char *format, flags_scan *fl);
void swSpecif_sc(specf_scan *spec, char ch);
int searchSpecif_sc(int *index, const char *format, specf_scan *spec);
void swflags_scan(flags_scan *fl, const char *ch, int i);
int search_nomatch(const char *str, specf_scan *spec);
void divide_16_8(char *str, long long unsigned int *num, int *i, int *powd,
                 specf_scan *spec);
void elseif_16(char *str, long long unsigned int *num, int *i, int *powd);

#endif  // SRC_S21_STRING_H_
