#!/bin/bash

_program="./RPN"
YELLOW=$'\033[33m'
PASS=$'\033[1;32mPASS\033[0m'
FAIL=$'\033[31mFAIL\033[0m'

# "expression" "expected result"	(for error tests, put "YELLOW" as expected value)
tests=(
    # fun cases
    "7 7 * -7 +"		"42"
    "5 1 2 + 4 * + 3 -"	"14"
    "2 3 *"				"6"
	"**+-/*"			$YELLOW
	"+-*"				$YELLOW
	"-7-7*-7-"			"56"
	"-7-7--7-"			"7"
	"-7-7+-7-"			"-7"
	"-7-7-7--7---"		$YELLOW
	"-7-7- 7*  7-*"		$YELLOW #-294 if there is no space
	
	# --- Basic correct cases ---
	"1 -1 *"			"-1"
	"1 1 /"				"1"
    "3 4 +"            "7"
    "3 -4 *"           "-12"
    "-3 -4 *"          "12"
    "5 1 2 + 4 * + 3 -" "14"
    "2 3 * 4 +"        "10"
    "2 3 4 + *"        "14"

    # --- Whitespace & parsing quirks ---
    "  3	4   +"       	"7"
    " -3	-4  +"       	"-7"
    "1  	 2	3   +  *"	"5"
    "3 4 5 +*     "         "27"
    "3 4 5e0+ *     "         $YELLOW

    # --- Large doubles ---
    "1$(printf '0%.0s' {1..308}) 1$(printf '0%.0s' {1..308}) +" $YELLOW  # Overflow to infinity -> isfinite() fail
    "1$(printf '0%.0s' {1..308}) 2 /" "5e+307"  # still finite
    # parser sets fail
	"999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 1*10*10*1*"	$YELLOW
	# calculation overflow
	"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 100*10*10*100*"	$YELLOW


    # --- Division by zero ---
    "3 0 /"             $YELLOW
    "5 5 - 5 5 - /"     $YELLOW
    "0 0 /"             $YELLOW

    # --- Not enough operands ---
    "+"                $YELLOW
    "3 +"              $YELLOW
    "3 4 + +"          $YELLOW

    # --- Leftover stack items ---
    "3 4 5 +"          $YELLOW
    "2 3"              $YELLOW

    # --- Invalid tokens ---
    "a b +"            $YELLOW
    "3 ? 4 +"          $YELLOW
    "3 4 5 ^"          $YELLOW  # unsupported op
    "3 4 +"             "7"      # recheck that valid still passes

    # --- Mixed tricky negatives ---
    "-2 -3 /"          "0.666667"  # negative / negative -> positive
    "-2 3 /"           "-0.666667"
    "2 -3 /"           "-0.666667"

    # 1. Empty input
    ""                          $YELLOW

    # 2. Only whitespace
    "      "                    $YELLOW
    "\t\t\t"                    $YELLOW

    # 3. Lone minus sign (might be parsed as operator without operands)
    "-"                         $YELLOW

    # 4. Lone decimal point
    "."                         $YELLOW

    # 5. Dangling negative sign before space
    "- "                        $YELLOW

    # 8. Massive number that can't fit in double
    "999999999999999999999999999999999999999999999999"  $YELLOW

    # 9. Repeated operators without enough operands
    "+ + +"                     $YELLOW

    # 10. Non-UTF-8 garbage bytes (possible parsing fail if using `std::string` directly)
    $'\xff\xfe\xfd'             $YELLOW

    # 11. Very long token (heap allocation stress / leak potential)
    "$(printf '9%.0s' {1..10000})"   $YELLOW

    # 12. Excessively many numbers without operators (stack growth)
    "$(printf '1 %.0s' {1..10000})"   $YELLOW

    # 13. Division by zero hidden in whitespace
    "3\t0\t/"                   $YELLOW

    # 14. Float edge-case: INF literal
    "INF 2 +"                   $YELLOW

    # 15. Float edge-case: NAN literal
    "NAN 2 +"                   $YELLOW

    # 16. Negative infinity creation
    "-1e308 1e308 *"             $YELLOW

    # 17. Very deep valid stack then pop too much
    "$(printf '1 %.0s' {1..100}) $(printf '+ %.0s' {1..99}) +"  $YELLOW

    # 18. Number followed by invalid symbol without space
    "3x 4 +"                    $YELLOW

    # 19. Huge exponent notation overflow
    "1e9999 1 +"                 $YELLOW

)

echo -e "\n-------- test case loop --------\n" 
for ((i=0; i<${#tests[@]}; i+=2)); do
    input="${tests[i]}"
    expected="${tests[i+1]}"
    output=$($_program "$input")

    if [[ "$expected" == $YELLOW ]]; then
        if [[ "$output" == *"$YELLOW"* ]]; then
            echo "$PASS (yellow error): '$input' => $output"
        else
            echo "$FAIL (yellow error): '$input'
    		=> got '$output', expected yellow text"
        fi
    else
        if [[ $output == $expected ]]; then
            echo "$PASS: '$input' => $output"
        else
            echo "$FAIL: '$input'
    		=> got '$output', expected '$expected'"
        fi
    fi
done

echo -e "\n-------- test program argument count --------\n"
# test no arguments
output=$($_program)

if [[ "$output" == *"$YELLOW"* ]]; then
    echo "$PASS (yellow error): '' => $output"
else
    echo "$FAIL (yellow error): ''
    => got '$output', expected yellow text"
fi

# test too many arguments
output=$($_program "3 4 +" 7 "-")

if [[ "$output" == *"$YELLOW"* ]]; then
    echo "$PASS (yellow error): '"3 4 +" 7 "-"' => $output"
else
    echo "$FAIL (yellow error): '"3 4 +" 7 "-"'
    => got '$output', expected yellow text"
fi

# test too many arguments
output=$($_program $input)

if [[ "$output" == *"$YELLOW"* ]]; then
    echo "$PASS (yellow error): '"3" 7 +' => $output"
else
    echo "$FAIL (yellow error): '"3" 7 +'
    => got '$output', expected yellow text"
fi
