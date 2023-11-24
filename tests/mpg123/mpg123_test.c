#include <assert.h>
//#include <stdio.h>
#include <stdlib.h>

#include <mpg123.h>

int main(int argc, char **argv)
{
	assert(argc >= 2);

//	FILE* file = fopen(argv[1], "rb");
//	assert(file);
//
//	int result = fseek(file, 0, SEEK_END);
//	assert(result == 0);
//
//	long filesize = ftell(file);
//	assert(filesize > 0);
//
//	result = fseek(file, 0, SEEK_SET);
//	assert(result == 0);
//
//	char* data = malloc(filesize);
//	assert(data);
//
//	size_t bytesread = fread(data, 1, filesize, file);
//	assert(filesize == bytesread);
//
//	result = fclose(file);
//	assert(result == 0);

	int result = mpg123_init();
	assert(result == MPG123_OK);

	mpg123_handle* handle = mpg123_new(NULL, NULL);
	assert(handle);

	result = mpg123_param(handle, MPG123_VERBOSE, 4, 0.);
	assert(result == MPG123_OK);

//	result = mpg123_param(handle, MPG123_ADD_FLAGS, MPG123_QUIET, 1.);
//	assert(result == MPG123_OK);

	result = mpg123_open(handle, argv[1]);
	assert(result == MPG123_OK);

	long rate;
	int channels;
	int encoding;

	result = mpg123_getformat(handle, &rate, &channels, &encoding);
	assert(result == MPG123_OK);

	size_t buffersize = 1024 * 1024;
	void* buffer = malloc(buffersize);
	assert(buffer);

	while (result != MPG123_DONE)
	{
		size_t decodedbytes;
		result = mpg123_read(handle, buffer, buffersize, &decodedbytes);
		assert(result == MPG123_OK || result == MPG123_DONE);
	}

	free(buffer);

	result = mpg123_close(handle);
	assert(result == MPG123_OK);

	mpg123_delete(handle);
	mpg123_exit();

	return 0;
}
