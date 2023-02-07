# Part Two
## Breakdown of code
The goal of this part is separate meta commands with statements and add two new statements: `insert` and `select`

### What are we removing/changing? 

Recall in part one, in our main function, we had the conditional:
```
if(strcmp(input_buffer->buffer, ".exit") == 0) {
    close_input_buffer(input_buffer);
    exit(EXIT_SUCCESS);
  } else {
    printf("Unrecognized command %s", input_buffer->buffer);
}
```
Instead of comparing our input to a single `.exit` meta-command, we're going to
change the conditional to look for a "." character as the first character in the input buffer as such:

`if(input_buffer->buffer[0] == '.') {`

This allows us to do two things: 
1- allow for more meta commands should we choose to add more in the future
2- allows us to separate meta comands from statements 

Also, if you're still confused about what meta commands are, they're basically any Non-SQL command, and in this case it is any command that starts with a "."

Now that we have an idea of what we're going to do, lets take a look at the final main function for this part:

### Main Function

```
int main(int argc, char* argv[]) {
	InputBuffer* input_buffer = new_input_buffer();
	while(true) {
		prompt_user();
		read_input(input_buffer);

		if(input_buffer->buffer[0] == '.') {
			switch (do_meta_command(input_buffer)) {
				case (META_COMMAND_SUCCESS):
					continue;
				case(META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s'\n", input_buffer->buffer);
					continue;
			}
		}
		Statement statement;
		switch(prepare_statement(input_buffer, &statement)) {
			case (PREPARE_SUCCESS):
				break;
			case(PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
				continue;
		}

		execute_statement(&statement);
		printf("Executed.\n");
	}
}
``` 
### Functions 

You'll notice we have 3 new functions: 

 1 - do_meta_command(): This handles our meta commands  
 
 2 - prepare_statement(): This converts our line of input into an internal representation of a statement 
 
 3 - execute_statement(): Here we pass the result of our prepare_statement() function. This will also eventually become our virtual machine 
 
 2 of our functions return enums indicating success or failure, lets define both: 
 -Our first one if for our meta commands: 
 
 ```
 typedef enum {
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND,
}MetaCommandResult;

 ```
 ```
 MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
	if (strcmp(input_buffer->buffer, ".exit") == 0) {
		exit(EXIT_SUCCESS);
	} else {
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}
 ```
This function acts as a wrapper and takes our previous functionality and leaves some room for future meta commandswe might want to add. It also utilizes the eum we just defined

-Our second enums are for our statements:
```
typedef enum {
	PREPARE_SUCCESS, 
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;
```
```
typedef enum {
	STATEMENT_INSERT, 
	STATEMENT_SELECT
} StatementType;
```
```
typedef struct {
	StatementType type;
} Statement;
```
So what's going on here? 
Well the first enum here is used for error checking, just like in `MetaCommandResult`

The second enum is for detecting which statement we're using in our input, 

Then we have a struct, `Statement`, that holds a variable of type `StatementType` 

Now lets see how these are used in our `prepare_statement()` function: 

```
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
	// strncmp is used because we follow string with data
	if (strncmp(input_buffer->buffer, "insert",6) == 0) {
		statement->type = STATEMENT_INSERT;
		return PREPARE_SUCCESS;
	}
	if (strcmp(input_buffer->buffer, "select")==0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}
```
Our function takes in user input as a parameter and compares it to statements `insert` and `select`. If there is a match, it returns `PREPARE_SUCCESS`, otherwise it returns `PREPARE_UNRECOGNIZED_STATEMENT`. These correlate to print statements defined in our main function

Lastly, we have the `execute_command()` function:

```
void execute_statement(Statement* statement) {
	switch (statement->type) {
		case(STATEMENT_INSERT):
			printf("This is where we would do an insert.\n");
			break;
		case(STATEMENT_SELECT):
			printf("This is where we would do a select");
			break;
		
	}
}
```
We use this function to return placeholder values(for now) based on whether the user uses `insert` or `select` keywords

That's it for this part. We created functionality that separates meta commands and statements, added 3 main functions that handles meta commands, another that prepares our statement for processing later as well as defined enums for these different enums and success/errors that may occur.


