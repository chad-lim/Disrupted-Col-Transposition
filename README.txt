Discol README

EXPECTATIONS:

- This program should follow all project requirements
- You can output in groups of N
- Backfill and encryption occurs while you still have input to encrypting
- Key sorting works properly and alphabet is considered before for Numbers
- Using -h will output help but end the program so that a user can execute again
- -t Allows you to output the table
- If the intermediate table displaying the encryption/decryption is output
	there's a new line added after it before the ciphertext / plaintext
- If the intermediate table is not displayed, then there is no new line
	character added
- WHEN DECLARING A KEY with -k, I interpreted the instructions as requiring
	NO WHITE SPACE (ex. -kflower means the key is FLOWER)
- Checking for alphanumeric and making capital and lower case depending on the
	function works properly
- Encryption is still Default
- N is set to 5 by default

BUGS:

- The only significant bug that violates the project requirements is that
	the program does not work with duplicate characters
	I managed to get it to work with duplicate characters in the key like:
	flowerr but then it wouldn't work with flower so I decided to leave it in
	a form that would only take non duplicates
