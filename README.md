# IPMT

IPMT (**I**ndexed **P**attern **M**atching **T**ool) is a tool for exact pattern matching using indexing and compression.
- In _index_ mode, creates a compressed index for the given file.
- In _search_ mode, searches for the given pattern using a pre-processed index.

## Indexing Algorithms
- Suffix Array

## Compression Algorithms
- LZ77

## How to use
Run `make` to compile.

Run `./bin/ipmt --help` for supported options.

## Results
`doc/report.pdf` (in portuguese) contains details and limitations of the implementation.
