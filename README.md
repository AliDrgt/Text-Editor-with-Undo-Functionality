# Text Editor with Undo Functionality

This project is a C++ program that implements a simple text editor. The editor allows for basic text manipulation operations such as insertion, deletion, replacement, moving lines, and undoing the last operation. The text is stored in a linked list, and the editor supports reading from and writing to a file.

## Features

- Read lines of text from a file into a linked list.
- Insert a new line of text at a specified position.
- Delete a line of text from a specified position.
- Replace a line of text at a specified position with new text.
- Move a line of text from one position to another.
- Display lines of text in pages of 10 lines each.
- Navigate through pages of text (next and previous).
- Undo the last operation performed.
- Save the current state of the text to a file.

## Usage

### Compiling the Code

To compile the code, use the following command:

```sh
g++ -o text_editor text_editor.cpp
```

### Running the Program

Run the compiled program using:

```sh
./text_editor
```

### Program Flow

1. The program prompts the user to enter the filename to load the text from.
2. The user is presented with a menu of options to manipulate the text:
   - Insert a new line
   - Delete a line
   - Replace a line
   - Move a line
   - Navigate to the next page
   - Navigate to the previous page
   - Save the text to a file
   - Undo the last operation
   - Exit the program
3. The user can perform operations by entering the corresponding number and following the prompts.

## Example

Here's an example of how the program works:

1. When prompted, enter the filename to load the text from.
   - Example input: "example.txt"
2. Choose an option from the menu by entering the corresponding number.
   - Example: To insert a new line, enter "1" and follow the prompts to enter the position and the new line of text.
3. The program performs the requested operation and displays the updated text.
4. The user can continue performing operations or choose to exit the program.

## Code Overview

### Structures

- "Node": Stores individual lines of text and a pointer to the next node.
- "undo_stack": Keeps track of operations for the undo functionality.

### Functions

- "openFile": Reads lines from a specified file and appends them to the linked list.
- "saveFile": Saves the current lines of text from the linked list to a specified file.
- "append": Adds a new node to the end of the linked list.
- "insert_n": Inserts a new node at a specified position in the linked list.
- "delete_n": Deletes a node at a specified position in the linked list.
- "replace_n": Replaces the data in a node at a specified position in the linked list.
- "undo": Reverts the last operation performed.
- "DisplayList": Displays a specified number of lines (10 lines per page) from the linked list.
- "Move": Moves a node from one position to another within the linked list.

## Built-In File Handling

- The program can read from and write to a file named "note.txt".

## Notes

- The program maintains a single linked list for storing lines of text.
- Operations are performed on the linked list, and the program provides an undo functionality to revert the last change.
- The text is displayed in pages of 10 lines each, and the user can navigate through the pages using the menu options.

