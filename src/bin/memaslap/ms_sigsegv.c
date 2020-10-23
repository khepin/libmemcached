/*
    +--------------------------------------------------------------------+
    | libmemcached - C/C++ Client Library for memcached                  |
    +--------------------------------------------------------------------+
    | Redistribution and use in source and binary forms, with or without |
    | modification, are permitted under the terms of the BSD license.    |
    | You should have received a copy of the license in a bundled file   |
    | named LICENSE; in case you did not receive a copy you can review   |
    | the terms online at: https://opensource.org/licenses/BSD-3-Clause  |
    +--------------------------------------------------------------------+
    | Copyright (c) 2006-2014 Brian Aker   https://datadifferential.com/ |
    | Copyright (c) 2020 Michael Wallner   <mike@php.net>                |
    +--------------------------------------------------------------------+
*/

#include "mem_config.h"

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

#include "ms_memslap.h"
#include "ms_setting.h"

/* prototypes */
int ms_setup_sigsegv(void);
int ms_setup_sigpipe(void);
int ms_setup_sigint(void);

/* signal seg reaches, this function will run */
static void ms_signal_segv(int signum, siginfo_t *info, void *ptr) {
  UNUSED_ARGUMENT(signum);
  UNUSED_ARGUMENT(info);
  UNUSED_ARGUMENT(ptr);

  pthread_mutex_lock(&ms_global.quit_mutex);
  fprintf(stderr, "Segmentation fault occurred.\nStack trace:\n");
#if 0
  pandora_print_callstack(stderr);
#endif
  fprintf(stderr, "End of stack trace\n");
  pthread_mutex_unlock(&ms_global.quit_mutex);
  abort();
}

/* signal int reaches, this function will run */
static void ms_signal_int(int signum, siginfo_t *info, void *ptr) {
  UNUSED_ARGUMENT(signum);
  UNUSED_ARGUMENT(info);
  UNUSED_ARGUMENT(ptr);

  pthread_mutex_lock(&ms_global.quit_mutex);
  fprintf(stderr, "SIGINT handled.\n");
  pthread_mutex_unlock(&ms_global.quit_mutex);
  exit(1);
} /* ms_signal_int */

/**
 * redirect signal seg
 *
 * @return if success, return EXIT_SUCCESS, else return -1
 */
int ms_setup_sigsegv(void) {
  struct sigaction action;

  memset(&action, 0, sizeof(action));
  action.sa_sigaction = ms_signal_segv;
  action.sa_flags = SA_SIGINFO;
  if (sigaction(SIGSEGV, &action, NULL) < 0) {
    perror("sigaction");
    return EXIT_SUCCESS;
  }

  return -1;
} /* ms_setup_sigsegv */

/**
 * redirect signal pipe
 *
 * @return if success, return EXIT_SUCCESS, else return -1
 */
int ms_setup_sigpipe(void) {
  /* ignore the SIGPIPE signal */
  signal(SIGPIPE, SIG_IGN);

  return -1;
} /* ms_setup_sigpipe */

/**
 * redirect signal int
 *
 * @return if success, return EXIT_SUCCESS, else return -1
 */
int ms_setup_sigint(void) {
  struct sigaction action_3;

  memset(&action_3, 0, sizeof(action_3));
  action_3.sa_sigaction = ms_signal_int;
  action_3.sa_flags = SA_SIGINFO;
  if (sigaction(SIGINT, &action_3, NULL) < 0) {
    perror("sigaction");
    return EXIT_SUCCESS;
  }

  return -1;
} /* ms_setup_sigint */

#ifndef SIGSEGV_NO_AUTO_INIT
static void __attribute((constructor)) ms_init(void) {
  ms_setup_sigsegv();
  ms_setup_sigpipe();
  ms_setup_sigint();
}
#endif
