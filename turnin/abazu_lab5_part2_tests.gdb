# Test file for Lab5_usingATMega1284


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly,
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below

# Test sequence from init: 0x00 => PORTC: 0x07
test "PINA: 0x00 => PORTC = 0x07\n"
set state = init
setPINA 0x00
continue 2
expectPORTC 0x07
expect state waitA
checkResult

# ---------------------------------------------------------

# Test sequence from init: 0x00, 0x03, 0x03, 0x00 => PORTC: 0x00
test "PINA: 0x00, 0x03, 0x00 => PORTC = 0x00\n"
set state = init
setPINA 0x00
continue 2
printPORTC
setPINA 0x03
continue 2
printPORTC
setPINA 0x03
continue 2
setPINA 0x00
continue 2
printPORTC
expectPORTC 0x00
expect state waitA
checkResult

# Test sequence from waitA: 0x00, 0x01 => PORTC: 0x01
test "PINA: 0x00 0x01 0x01 0x01\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 0
continue 2
printPORTC
setPINA 0x01
continue 2
printPORTC
setPINA 0x01
continue 2
printPORTC
setPINA 0x01
continue 2
expectPORTC 0x01
expect state waitInc
checkResult

# ---------------------------------------------------------

# Test sequence from waitA: 0x00, 0x01 2 times, 0x00, 0x01 => PORTC: 0x02
test "PINA: 0x00 0x01 0x01 0x00, 0x01 => PORTC: 0x02\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 0
continue 2
printPORTC
setPINA 0x01
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
printPORTC
setPINA 0x01
continue 2
printPORTC
expectPORTC 0x02
expect state waitInc
checkResult

# Test sequence from waitA(c = 0x03): 0x01, 0x00, 0x01, 0x01, 0x03 => PORTC: 0x00
test "PINA: 0x01, 0x00, 0x01, 0x01, 0x03 => PORTC: 0x00\n"
set state = waitA
set counter::tmpC = 0x03
continue 2
setPINA 0x01
continue 2
printPORTC
setPINA 0x00
continue 2
setPINA 0x01
continue 2
printPORTC
setPINA 0x03
continue 2
printPORTC
expectPORTC 0x00
expect state reset
checkResult

# ---------------------------------------------------------

# Test sequence from waitA: 0x00, 0x01 2 times, 0x00, 0x01 => PORTC: 0x04
test "PINA: 0x00 0x02 0x02 0x00, 0x02 => PORTC: 0x04\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 5
continue 2
printPORTC
setPINA 0x02
continue 2
setPINA 0x02
continue 2
printPORTC
setPINA 0x00
continue 2
printPORTC
setPINA 0x02
continue 2
printPORTC
expectPORTC 0x03
expect state waitDec
checkResult

# Test sequence from waitA: 0x00, 0x01 2 times, 0x00, 0x01 => PORTC: 0x00
test "PINA: 0x00 0x02 0x02 0x03, 0x03 => PORTC: 0x00\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 5
continue 2
printPORTC
setPINA 0x02
continue 2
setPINA 0x02
continue 2
printPORTC
continue 2
setPINA 0x03
continue 2
printPORTC
continue 2
setPINA 0x03
continue 2
expectPORTC 0x00
expect state reset
checkResult

# ---------------------------------------------------------

# Test sequence from waitA: 0x00, 0x01 2 times, 0x00, 0x01 => PORTC: 0x07
test "PINA: 0x00 0x01 0x01 0x00, 0x01 => PORTC: 0x07\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 7
continue 2
printPORTC
setPINA 0x01
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
printPORTC
setPINA 0x01
continue 2
printPORTC
expectPORTC 0x07
expect state waitInc
checkResult

# Test sequence from waitA: 0x00, 0x01 2 times, 0x00, 0x01 => PORTC: 0x00
test "PINA: 0x00 0x02 0x02 0x00, 0x02 => PORTC: 0x00\n"
set state = waitA
setPINA 0x00
set counter::tmpC = 0
continue 2
printPORTC
setPINA 0x02
continue 2
setPINA 0x02
continue 2
printPORTC
setPINA 0x00
continue 2
printPORTC
setPINA 0x02
continue 2
printPORTC
expectPORTC 0x00
expect state waitDec
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
