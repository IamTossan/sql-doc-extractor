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

This program detects and extracts documentation in a linked list.

Then the linked list is parsed into nodes.

Nodes are put together in a linked list fashion.

Any node can also have children which is also a linked list of nodes.