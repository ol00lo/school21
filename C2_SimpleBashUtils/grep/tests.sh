#!/bin/bash

echo "=== CREATING TEST FILES FOR GREP ==="

echo "hello world" > test.txt
echo "" >> test.txt
echo "HELLO WORLD" >> test.txt
echo "test line" >> test.txt
echo "another test" >> test.txt
echo "HELLO everyone" >> test.txt
echo "goodbye world" >> test.txt
echo "hello again" >> test.txt

echo "Normal line" > special.txt
echo "LINE WITH UPPERCASE" >> special.txt
echo "line with lowercase" >> special.txt
echo "Mixed Case Line" >> special.txt
echo "another normal line" >> special.txt
echo "TEST UPPERCASE" >> special.txt

echo "first line" > empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "pattern here" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "last line with pattern" >> empty_lines.txt

echo "hello" > patterns.txt
echo "test" >> patterns.txt
echo "world" >> patterns.txt

echo "=== BASIC GREP TESTS ==="

echo "1. Testing no flags (basic search)..."
./s21_grep "hello" test.txt > my.txt
grep "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "2. Testing flag -i (ignore case)..."
./s21_grep -i "hello" test.txt > my.txt
grep -i "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "3. Testing flag -v (invert match)..."
./s21_grep -v "hello" test.txt > my.txt
grep -v "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "4. Testing flag -n (line numbers)..."
./s21_grep -n "test" test.txt > my.txt
grep -n "test" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "5. Testing flag -c (count lines)..."
./s21_grep -c "hello" test.txt > my.txt
grep -c "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "6. Testing flag -l (files with matches)..."
./s21_grep -l "hello" test.txt > my.txt
grep -l "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== TESTS WITH SPECIAL CHARS FILE ==="

echo "7. Testing -i with different cases..."
./s21_grep -i "line" special.txt > my.txt
grep -i "line" special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "8. Testing -v with uppercase..."
./s21_grep -v "LINE" special.txt > my.txt
grep -v "LINE" special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "9. Testing -n -i (line numbers + ignore case)..."
./s21_grep -n -i "case" special.txt > my.txt
grep -n -i "case" special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== TESTS WITH EMPTY LINES FILE ==="

echo "10. Testing -v with empty lines search..."
./s21_grep -v "pattern" empty_lines.txt > my.txt
grep -v "pattern" empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "11. Testing -c with pattern..."
./s21_grep -c "pattern" empty_lines.txt > my.txt
grep -c "pattern" empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "12. Testing -n with pattern in empty lines file..."
./s21_grep -n "pattern" empty_lines.txt > my.txt
grep -n "pattern" empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== COMBINATION TESTS ==="

echo "13. Testing -i -v (ignore case + invert)..."
./s21_grep -i -v "hello" test.txt > my.txt
grep -i -v "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "14. Testing -n -i (line numbers + ignore case)..."
./s21_grep -n -i "hello" test.txt > my.txt
grep -n -i "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "15. Testing -c -v (count + invert)..."
./s21_grep -c -v "test" test.txt > my.txt
grep -c -v "test" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "16. Testing -l -i (files with matches + ignore case)..."
./s21_grep -l -i "hello" test.txt > my.txt
grep -l -i "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "17. Testing -e (multiple patterns)..."
./s21_grep -e "hello" -e "test" test.txt > my.txt
grep -e "hello" -e "test" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "18. Testing -e with -i..."
./s21_grep -e "hello" -e "TEST" -i test.txt > my.txt
grep -e "hello" -e "TEST" -i test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "19. Testing -iv (combined flags)..."
./s21_grep -iv "hello" test.txt > my.txt
grep -iv "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "20. Testing -in (combined flags)..."
./s21_grep -in "hello" test.txt > my.txt
grep -in "hello" test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== ERROR TESTS ==="

echo "21. Testing non-existent file..."
./s21_grep "hello" nofile.txt 2> my_err.txt
grep "hello" nofile.txt 2> orig_err.txt
if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi

echo "22. Testing invalid flag..."
./s21_grep -P "hello" test.txt 2> my_err.txt
grep -P "hello" test.txt 2> orig_err.txt
if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi

echo "23. Testing no pattern..."
./s21_grep 2> my_err.txt
grep 2> orig_err.txt
if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi

rm -f test.txt special.txt empty_lines.txt patterns.txt my.txt orig.txt my_err.txt orig_err.txt my_clean.txt orig_clean.txt

echo "=== END ==="