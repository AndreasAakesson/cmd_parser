# cmd_parser

An object oriented way to handle command line parsing.


## Usage
Create a command:

```
// Create the command function.
cmd_parser::CommandFunc func = [](cmd_parser::CommandArg argz) {
 // Your function here. 
 // Also possible to capture values => [&myValue]
 // myValue.doSomething(argz);
};

// Create the command.
// command name, function to execute, help text and required number of arguments.
Command default_cmd("default", func, "This is the default (fallback) command.", 1);
```

Command Parser:

```
// Initialize command parser with default (fallback) command.
CommandParser parser(default_cmd);

// Add more commands to the parser.
parser.add(anotherCommand);

// Parse user input.
parser.exec(argc, argv); // alt. parser.exec(vector<string>)
```



## Example
`make` will build `command_parser.o` and `example`.

Show usage:

```
$ ./example

USAGE:

	guess		Guess the secret word! (HINT: It's 'chicken')

	none		A command with no required arguments.

	many		A command with 3 required arguments

Default: 
	default		This is the default (fallback) command.
```

Default command:	

```
$ ./example test
Default command executed with argument: test
```

Default command:	

```
$ ./example test
Default command executed with argument: test
```

No required arguments:

```
$ ./example none
I don't care about your arguments.
```

Three required arguments:

```
$ ./example many one two three
Arguments: one	two	three

# Too few arguments will show usage for "many"
$ ./example many one two
many		A command with 3 required arguments
```