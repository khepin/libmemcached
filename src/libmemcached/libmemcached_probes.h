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
    | Copyright (c) 2020-2021 Michael Wallner        https://awesome.co/ |
    +--------------------------------------------------------------------+
*/

#pragma once

/*
 * This file contains the definition of the various probes supported by
 * libmemcached. Currently it only support DTRACE, but just create an
 * implementation of the following macros to create your own sort of
 * probing :)
 */

#ifdef HAVE_DTRACE
/*
 * Create the DTrace probes on the system using it (to support both Solaris
 * and MacOS X
 */
#  include "libmemcached/dtrace_probes.h"

#else
/*
 * Provide dummy macros so that we don't need to clutter the code with
 * ifdefs when we want to use the probes.
 */

#  define LIBMEMCACHED_MEMCACHED_ADD_END()
#  define LIBMEMCACHED_MEMCACHED_ADD_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_ADD_START()
#  define LIBMEMCACHED_MEMCACHED_ADD_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_CONNECT_END()
#  define LIBMEMCACHED_MEMCACHED_CONNECT_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_CONNECT_START()
#  define LIBMEMCACHED_MEMCACHED_CONNECT_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_END()
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_START()
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_WITH_INITIAL_END()
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_WITH_INITIAL_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_WITH_INITIAL_START()
#  define LIBMEMCACHED_MEMCACHED_DECREMENT_WITH_INITIAL_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DELETE_END()
#  define LIBMEMCACHED_MEMCACHED_DELETE_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_DELETE_START()
#  define LIBMEMCACHED_MEMCACHED_DELETE_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_FLUSH_END()
#  define LIBMEMCACHED_MEMCACHED_FLUSH_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_FLUSH_START()
#  define LIBMEMCACHED_MEMCACHED_FLUSH_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_GET_END()
#  define LIBMEMCACHED_MEMCACHED_GET_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_GET_START()
#  define LIBMEMCACHED_MEMCACHED_GET_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_TOUCH_END()
#  define LIBMEMCACHED_MEMCACHED_TOUCH_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_TOUCH_START()
#  define LIBMEMCACHED_MEMCACHED_TOUCH_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_END()
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_START()
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_WITH_INITIAL_END()
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_WITH_INITIAL_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_WITH_INITIAL_START()
#  define LIBMEMCACHED_MEMCACHED_INCREMENT_WITH_INITIAL_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_MGET_END()
#  define LIBMEMCACHED_MEMCACHED_MGET_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_MGET_START()
#  define LIBMEMCACHED_MEMCACHED_MGET_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_REPLACE_END()
#  define LIBMEMCACHED_MEMCACHED_REPLACE_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_REPLACE_START()
#  define LIBMEMCACHED_MEMCACHED_REPLACE_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_SERVER_ADD_END()
#  define LIBMEMCACHED_MEMCACHED_SERVER_ADD_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_SERVER_ADD_START()
#  define LIBMEMCACHED_MEMCACHED_SERVER_ADD_START_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_SET_END()
#  define LIBMEMCACHED_MEMCACHED_SET_END_ENABLED() (0)
#  define LIBMEMCACHED_MEMCACHED_SET_START()
#  define LIBMEMCACHED_MEMCACHED_SET_START_ENABLED() (0)

#endif
