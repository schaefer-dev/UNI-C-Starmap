#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "star.h"

void pass(char* test_name)
{
	printf("PASS: '%s'\n", test_name);
}

void fail(char* test_name, char* message)
{
	fprintf(stderr, "fail: '%s' with message '%s'\n", test_name, message);
}

int main(int argc, char **argv)
{
	FILE* f = fopen("test_data/validstar.txt", "r");

	struct star s;
	int res = star_read_from_file(&s, f);
	fclose(f);
	if (res != 1)
	{
		fail("test_read", "wrong result code");
		return 1;
	}
	if (s.draper != 28) {
		fail("test_read_valid_star", "wrong draper number read");
		return 1;
	}
	if (s.x < 0.994771 || s.x > 0.994773) {
		fail("test_read", "wrong x coord read");
		return 1;
	}
	if (s.y < 0.023163 || s.y > 0.023165) {
		fail("test_read", "wrong y coord read");
		return 1;
	}
	if (s.magnitude < 4.6 || s.magnitude > 4.62) {
		fail("test_read", "wrong magnitude read");
		return 1;
	}

	pass("test_read");
	return 0;
}
