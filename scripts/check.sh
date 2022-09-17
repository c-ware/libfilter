#!/bin/sh
# Run all the tests

function run_test {
    printf "Running test '%s'\n" "$1"
    $2 $1
    printf "Ran test '%s'\n" "$1"
}

run_test tests/filter_init $1
run_test tests/filter_set_rule $1
run_test tests/filter_set_input $1
run_test tests/filter_set_output $1
run_test tests/filter_match $1
