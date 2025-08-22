#include "types.h"

#if !defined(STRING_H)

uint32 string_length(const char *s);
boolean string_equal(const char *string_left, const char *string_right);

#endif


#if defined(STRING_IMPLEMENTATION)

uint32 string_length(const char *s)
{
  const char *sc = s;
  while (*sc != '\0') sc++;
  return (uint32) (sc - s);
}

boolean string_equal(const char *string_left, const char *string_right)
{
  while (*string_left != '\0' && *string_right != '\0') {
    if (*string_left++ != *string_right++) return FALSE;
  }

  return *string_left == '\0' && *string_right == '\0';
}

#endif /* STRING_IMPLEMENTATION */
