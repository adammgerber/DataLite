#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}

//prints prompt to user
void print_prompt() { printf("db > "); }

/* Reading input from user 
lineptr: pointer to the variable we use to point to the buffer containing the read line
if lineptr is set to NULL it is mallocated by getline even if the command fails

n: pointer to the variable we use to save the size of allocated buffer
stream: input stream to read from
return value: number of bytes read, which may be less than the size of the buffer
*/
// ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
	/* We tell getline to store the read line in input_buffer->buffer 
	and the size of the allocated buffer in input_buffer->buffer_length.
	We then store the return value in input_buffer->input_length */

	/* Buffer starts at NULL, so getline allocated enough memory to hold the line of input 
	and makes bffer point to it */
	ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0){
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}

	//ignore trailing newline
	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;

}

// function that frees the memory allocated for an instance of InputBuffer
void close_input_buffer(InputBuffer* input_buffer){
	free(input_buffer->buffer);
	free(input_buffer);
}

int main(int argc, char* argv[]){
	InputBuffer* input_buffer = new_input_buffer();
	while(true){
		print_prompt();
		read_input(input_buffer);

		//parse and execute command, otherwise print error message and continue loop
		if(strcmp(input_buffer->buffer, ".exit") == 0) {
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command '%s'\n", input_buffer->buffer);
		}
	}
}