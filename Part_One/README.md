# Part One
This is our current main function:

```
int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = new_input_buffer();
	while(true) {
		prompt_user();
		read_input(input_buffer);

		if(strcmp(input_buffer->buffer, ".exit") == 0) {
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command %s", input_buffer->buffer);
		}
	}
}
```

What we have is an infinite while loop that prints a prompt to users, retrieves user input,
compares that input to our single command (.exit), and exits the program or gives the user an error.

## Breakdown of each part

**1) InputBuffer and new_input_buffer()**

```
typedef struct {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
}InputBuffer;

```

We create a struct called InputBuffer that stores:
  - the read line as `buffer`
  - size of that buffer as `buffer_length`
  - number of bytes read as `input_length`


```
InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}
```
Here we initialize a variable of type InputBuffer as a new instance of InputBuffer

**2) promt_user() and read_input() functions**

```
void prompt_user() {
	printf("db > ");
}
```
prompt_user doesnt need much of an explanation. DataLite will display "db > " when the program frist runs

```
void read_input(InputBuffer* input_buffer) {

	ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}

	//ignoring trailing newline
	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}
```
To understand this function, let's first explore getline() and see
how its being used in this program

From linux manpages: https://man7.org/linux/man-pages/man3/getline.3.html

`getline(char **lineptr, size_t *n, FILE *stream)`

**lineptr**
- a pointer to the variable we use to point to the buffer containing the input/read line
- if it is set to NULL, it is mallocated by getline and thus should be freed by the user, even if the command fails

**n**
- a pointer to the variable we use to save the size of the allocated buffer

**stream** 
- the input stream to read from (Reading from stdin in our case)

**return value**
- this is the number of bytes read which may be less than the size of the buffer

We tell getline to store the read line/input in `input_buffer->buffer` 

We store the size of the allocated buffer in `input_buffer->buffer_length` 

We store the return value in `input_buffer->input_length`

**3) Comparing input with our single command**

```
if(strcmp(input_buffer->buffer, ".exit") == 0) {
			close_input_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command %s", input_buffer->buffer);
		}
```

Here we compare the value of our buffer. If it equals ".exit", then we successfully exit the program.
Otherwise, we print an error message that shows our user the incorrect command they used

**4) close_input_buffer() function**

```
void close_input_buffer(InputBuffer* input_buffer) {
	free(input_buffer->buffer);
	free(input_buffer);
}
```

Here we simply deallocate memory previously allocated for input_buffer as well as the buffer element inside

That's it for this part. If you're confused about any C syntax, check out the notes below that goes over
a bunch of concepts used in this part of the program

********************************************************************
# C Review

### getline() vs getdelim()
- getline reads from a stream until newline is encountered
- getdelim reads from a stream until a delim is encountered

### strcmp()
- compares two strings
- returns 0 if two strings are equal
- returns >0 if the first non-matching character is greater (in ASCII) than the second string
- returns <0 if first non-matching character is less (in ASCII) than the second string

### Review of Standard Libraries used in this part

## Stdio.h
**variables**
size_t = unsigned int, result of sizeof()
FILE = obect type suitable for storing information for a file stream
fpos_t = object type suitable for storing any position in a file

## Stdbool.h
simpy allows us to use bool as a Boolean data type

true evaluates to 1
false evaluates to 0

## Stdlib.h
**macros:**
NULL = value of null pointer constant
EXIT_SUCCESS = value for exit function to return in case of success
EXIT_FAILURE = value for exit function to return in case of failure
**functions:**
free() = Reallocates memory previously allocated by malloc, calloc, or ralloc
exit() = causes program to terminate normally

