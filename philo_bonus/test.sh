#!/bin/bash

BINARY=./philo

# Function to run and label tests
run_test() {
	echo -e "\n[TEST] $1"
	$BINARY $2
}

echo "========================================="
echo "   ✅ TESTS WHERE PHILOSOPHERS SURVIVE"
echo "========================================="
# run_test "5 800 200 200 (no death, runs forever)" "5 800 200 200"
run_test "4 600 200 200 3 (will end with dinner over)" "4 600 200 200 3"
run_test "200 1000 100 100 2 (large group, no death)" "200 1000 100 100 2"
run_test "2 800 200 200 2 (safe small even group)" "2 800 200 200 2"

echo "========================================="
echo "   ❌ TESTS WHERE A PHILOSOPHER DIES"
echo "========================================="
run_test "5 200 100 100 (likely death)" "5 200 100 100"
run_test "3 199 100 100 (guaranteed death)" "3 199 100 100"
run_test "1 400 200 200 (one philo starves)" "1 400 200 200"
run_test "5 600 400 300 (too slow to eat)" "5 600 400 300"
run_test "5 150 100 100 (instant death)" "5 150 100 100"

echo "========================================="
echo "   🍽 TESTS WHERE 'DINNER IS OVER' SHOULD PRINT"
echo "========================================="
run_test "5 800 200 200 5" "5 800 200 200 5"
run_test "3 500 100 100 1" "3 500 100 100 1"
run_test "4 800 200 200 2" "4 800 200 200 2"
run_test "2 600 100 100 3" "2 600 100 100 3"

echo "========================================="
echo "   🚫 INVALID INPUT / VALIDATION TESTS"
echo "========================================="
run_test "No arguments" ""
run_test "Too many args" "5 800 200 200 5 1"
run_test "Empty args" "\"\" \"\" \"\" \"\""
run_test "Negative die time" "5 -800 200 200"
run_test "Non-numeric input (abc)" "5 abc 200 200"
run_test "Non-numeric input (two)" "5 800 200 two"
run_test "Special character" "5 800 200 200!"
run_test "Float input" "5 800 200 200 3.5"
run_test "Zero philosophers" "0 800 200 200"
run_test "Zero time to die" "1 0 200 200"
run_test "INT overflow" "2147483648 800 200 200"
run_test "Negative must_eat" "5 800 200 200 -5"

echo -e "\n✅ All tests executed.\n"
