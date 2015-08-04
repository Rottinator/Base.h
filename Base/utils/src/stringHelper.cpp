#include <cstdio>
#include <cstring>
#include <ctype.h>

namespace Base
{
	namespace Utils
	{
		char* strtrim(char* str)
		{
			size_t len = 0;
			char *frontp = str;
			char *endp = NULL;

			if (str == NULL) { return NULL; }
			if (str[0] == '\0') { return str; }

			len = strlen(str);
			endp = str + len;

			/* Move the front and back pointers to address the first non-whitespace
			* characters from each end.
			*/
			while (isspace(*frontp)) { ++frontp; }
			if (endp != frontp)
			{
				while (isspace(*(--endp)) && endp != frontp) {}
			}

			if (str + len - 1 != endp)
				*(endp + 1) = '\0';
			else if (frontp != str &&  endp == frontp)
				*str = '\0';

			/* Shift the string so that it starts at str so that if it's dynamically
			* allocated, we can still free it on the returned pointer.  Note the reuse
			* of endp to mean the front of the string buffer now.
			*/
			endp = str;
			if (frontp != str)
			{
				while (*frontp) { *endp++ = *frontp++; }
				*endp = '\0';
			}

			return str;
		}

		char* strlower(char* str)
		{
			int length = strlen(str);
			for (int i = 0; i < length; i++) {
				str[i] = tolower(str[i]);
			}

			return str;
		}
	}
}

