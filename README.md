# SQL Doc Extractor

### usage:

compile the program:
> make

use the program:
> ./dist/sqlDocExtractor &lt;file&gt;

### context:

Originally, this program was created to extract documentation from stored procedures.
Examples can be found in the test_files folder

### how it works:

This program detects and extracts documentation one line at a time in a linked list.

Then the linked list is parsed into a binary tree.

Left children are siblings in the JSON hierarchy.

Right children are children in the JSON hierarchy.
