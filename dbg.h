#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#ifdef NDEBUG
#define debug(M, ...) // la macro ne correspond à rien pour éviter les bugs quand NDEBUG est défini
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d %s " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif 

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...)  fprintf(stderr, "[ERROR] (%s:%d: %s errno: %s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN]  (%s:%d: %s errno: %s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__) 

#define log_info(M, ...) fprintf(stderr, "[INFO]  (%s:%d) %s " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } //for errors

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; } //for choice

#define check_mem(A) check((A), "Out of memory.") //for memory

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
