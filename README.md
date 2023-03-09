# c4
connect 4 solver

## fe/

a folder for what should be a frontend in javascript

## be/

contains code for solver, opening book maker and tester

### build makebook

```
cd be/
make book
bin/makebook book/construct
```

opening book will be in `c4book`

### build tester

```
cd be/
make test
bin/c4test < tests/[whatever test you want to test]
```

testing can be automated using `test.sh`, a bash script for testing which will append test results for every test to a `test_results.txt`

### build app + use service

```
cd be/
make solver book
bin/makebook book/construct
python3 ../service.py
```

the idea was to have the frontend send post requests to the service and have it solve on the backend.  
the frontend sends json with bitboards for red, blue and the number of moves and gets back output from the binary

## plans

letting this rot on github for people to look at because optimizations can still be done.
