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

#include "libmemcached/common.h"
#include "libmemcached/options.hpp"

#include "libmemcached/csl/context.h"

const char *memcached_parse_filename(memcached_st *memc) {
  assert_msg(memc, "Invalid memcached_st");
  return memcached_array_string(memc->configure.filename);
}

size_t memcached_parse_filename_length(memcached_st *memc) {
  return memcached_array_size(memc->configure.filename);
}

static memcached_return_t _parse_file_options(memcached_st &self, memcached_array_st *real_name) {
  FILE *fp = fopen(memcached_array_string(real_name), "r");
  if (not fp) {
    memcached_string_t error_message = memcached_array_to_string(real_name);
    memcached_return_t rc = memcached_set_errno(self, errno, MEMCACHED_AT, error_message);
    return rc;
  }

  char buffer[BUFSIZ];
  memcached_return_t rc = MEMCACHED_INVALID_ARGUMENTS;
  while (fgets(buffer, sizeof(buffer), fp)) {
    size_t length = strlen(buffer);

    if (length == 1 and buffer[0] == '\n')
      continue;

    if (memcached_failed(rc = memcached_parse_configuration(&self, buffer, length)))
      break;
  }
  fclose(fp);

  return rc;
}

memcached_return_t libmemcached_check_configuration(const char *option_string, size_t length,
                                                    char *error_buffer, size_t error_buffer_size) {
  memcached_st memc, *memc_ptr;

  if (option_string == NULL or length == 0) {
    return MEMCACHED_INVALID_ARGUMENTS;
  }

  if (error_buffer and error_buffer_size) {
    error_buffer[0] = 0;
  }

  if (not(memc_ptr = memcached_create(&memc))) {
    return MEMCACHED_MEMORY_ALLOCATION_FAILURE;
  }

  memcached_return_t rc = memcached_parse_configuration(memc_ptr, option_string, length);
  if (memcached_failed(rc) and error_buffer and error_buffer_size) {
    strncpy(error_buffer, memcached_last_error_message(memc_ptr), error_buffer_size);
    error_buffer[error_buffer_size - 1] = 0;
  }

  bool has_filename = memcached_behavior_get(memc_ptr, MEMCACHED_BEHAVIOR_LOAD_FROM_FILE);
  if (memcached_success(rc) and has_filename) {
    assert_msg(memcached_parse_filename(memc_ptr), "Invalid configuration file");
    assert_msg(memcached_parse_filename_length(memc_ptr), "Invalid configuration file");
    rc = _parse_file_options(*memc_ptr, memc_ptr->configure.filename);

    if (memcached_failed(rc) and error_buffer and error_buffer_size) {
      strncpy(error_buffer, memcached_last_error_message(memc_ptr), error_buffer_size);
      error_buffer[error_buffer_size - 1] = 0;
    }
  }

  memcached_free(memc_ptr);

  return rc;
}

memcached_return_t memcached_parse_configuration(memcached_st *self, char const *option_string,
                                                 size_t length) {
  WATCHPOINT_ASSERT(self);
  if (not self) {
    return MEMCACHED_INVALID_ARGUMENTS;
  }

  memcached_return_t rc;
  Context context(option_string, length, self, rc);

  context.start();

  return rc;
}

void memcached_set_configuration_file(memcached_st *self, const char *filename,
                                      size_t filename_length) {
  assert_msg(filename, "Invalid filename");
  assert_msg(filename_length, "Invalid filename_length");
  memcached_array_free(self->configure.filename);
  self->configure.filename = memcached_strcpy(self, filename, filename_length);
}

memcached_return_t memcached_parse_configure_file(memcached_st &self, const char *filename,
                                                  size_t length) {
  if (not filename) {
    return memcached_set_error(self, MEMCACHED_INVALID_ARGUMENTS, MEMCACHED_AT);
  }

  WATCHPOINT_ASSERT(self);
  if (not length) {
    return memcached_set_error(self, MEMCACHED_INVALID_ARGUMENTS, MEMCACHED_AT);
  }

  memcached_array_st *tmp_array = memcached_strcpy(&self, filename, length);

  if (not tmp_array) {
    return memcached_set_error(self, MEMCACHED_MEMORY_ALLOCATION_FAILURE, MEMCACHED_AT);
  }

  memcached_return_t rc = memcached_parse_configure_file(self, *tmp_array);
  memcached_array_free(tmp_array);

  return rc;
}

memcached_return_t memcached_parse_configure_file(memcached_st &self,
                                                  memcached_array_st &filename) {
  WATCHPOINT_ASSERT(memcached_array_size(&filename));
  if (not memcached_array_size(&filename)) {
    return memcached_set_error(self, MEMCACHED_INVALID_ARGUMENTS, MEMCACHED_AT);
  }

  return _parse_file_options(self, &filename);
}
