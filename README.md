## Disrupted Columnar Transposition

### Usage
* Usage: 
```
discol [-e | -d] -k<String> -t -b -<N> -h < somefile.txt
```

* Flags:
```
-e for Encryption (default)
-d for Decryption
-k<string> for the key string (MUST NOT include a space between -k and the key string)
-t to output the intermediate table to stderr
-b to backfill (default is not to backfill)
-<N> to output in groups of N characters (default is N=5, MUST NOT include a space and do not put the <>)
-h for outputting a brief help message, describing the flags and program
```

### Expectations
* Duplicate characters in the key string is not supported
* Alpha-numeric characters are accepted in the key string, prioritizing the alphabet before numbers
* Both encryption and decryption will output in blocks based on N
* Some file (.txt) must be input to the program via stdin for the program to function


