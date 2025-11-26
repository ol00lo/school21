#!/bin/bash

echo "=== CREATING TEST FILES ==="

echo "Line 1" > test.txt
echo "" >> test.txt
echo "Line 3" >> test.txt
echo "Line 4 with tab   " >> test.txt

printf "Normal line\n" > special.txt
printf "Line with \x01 control char\n" >> special.txt
printf "Line with \x02 control char\n" >> special.txt  
printf "Line with \x7f DEL char\n" >> special.txt
printf "Line with	tab and \x01 control\n" >> special.txt

echo "First line" > empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "Fourth line" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "" >> empty_lines.txt
echo "Last line" >> empty_lines.txt

echo "=== BASIC TESTS ==="

echo "1. Testing no flags..."
./s21_cat test.txt > my.txt
cat test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "2. Testing flag -b..."
./s21_cat -b test.txt > my.txt
cat -b test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "3. Testing flag -e..."
./s21_cat -e test.txt > my.txt
cat -e test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "4. Testing flag -n..."
./s21_cat -n test.txt > my.txt
cat -n test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "5. Testing flag -s..."
./s21_cat -s test.txt > my.txt
cat -s test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "6. Testing flag -t..."
./s21_cat -t test.txt > my.txt
cat -t test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

# echo "7. Testing flag -E..."
# ./s21_cat -E test.txt > my.txt
# cat -E test.txt > orig.txt
# diff my.txt orig.txt && echo "PASS" || echo "FAIL"
# 
# echo "8. Testing flag -T..."
# ./s21_cat -T test.txt > my.txt
# cat -T test.txt > orig.txt
# diff my.txt orig.txt && echo "PASS" || echo "FAIL"
# 
# echo "9. Testing GNU flag --number..."
# ./s21_cat --number test.txt > my.txt
# cat --number test.txt > orig.txt
# diff my.txt orig.txt && echo "PASS" || echo "FAIL"
# 
# echo "10. Testing GNU flag --squeeze-blank..."
# ./s21_cat --squeeze-blank test.txt > my.txt
# cat --squeeze-blank test.txt > orig.txt
# diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== TESTS WITH SPECIAL CHARS FILE ==="

echo "7. Testing -t with special chars..."
./s21_cat -t special.txt > my.txt
cat -t special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "8. Testing -e with special chars..."
./s21_cat -e special.txt > my.txt
cat -e special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "9. Testing -t -e with special chars..."
./s21_cat -t -e special.txt > my.txt
cat -t -e special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== TESTS WITH EMPTY LINES FILE ==="

echo "10. Testing -s with empty lines..."
./s21_cat -s empty_lines.txt > my.txt
cat -s empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "11. Testing -b with empty lines..."
./s21_cat -b empty_lines.txt > my.txt
cat -b empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "12. Testing -n with empty lines..."
./s21_cat -n empty_lines.txt > my.txt
cat -n empty_lines.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== COMBINATION TESTS ==="

echo "13. Testing -b -n..."
./s21_cat -b -n test.txt > my.txt
cat -b -n test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "14. Testing -e -n..."
./s21_cat -e -n test.txt > my.txt
cat -e -n test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "15. Testing -s -n..."
./s21_cat -s -n test.txt > my.txt
cat -s -n test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "16. Testing -t -e..."
./s21_cat -t -e test.txt > my.txt
cat -t -e test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

# echo "21. Testing -b -e -n..."
# ./s21_cat -b -e -n test.txt > my.txt
# cat -b -e -n test.txt > orig.txt
# diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "17. Testing -b -s -t..."
./s21_cat -b -s -t test.txt > my.txt
cat -b -s -t test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "18. Testing -ev..."
./s21_cat -ev test.txt > my.txt
cat -ev test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "19. Testing -bn.."
./s21_cat -bn test.txt > my.txt
cat -bn test.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

echo "=== ERROR TESTS ==="

echo "20. Testing non-existent file..."
./s21_cat nofile.txt 2> my_err.txt
cat nofile.txt 2> orig_err.txt
if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi

echo "21. Testing invalid flag..."
./s21_cat -z test.txt 2> my_err.txt
cat -z test.txt 2> orig_err.txt
if [ $? -ne 0 ]; then echo "PASS"; else echo "FAIL"; fi

echo "=== MULTIPLE FILES ==="

echo "22. Testing multiple files..."
./s21_cat test.txt special.txt > my.txt
cat test.txt special.txt > orig.txt
diff my.txt orig.txt && echo "PASS" || echo "FAIL"

rm -f test.txt special.txt empty_lines.txt my.txt orig.txt my_err.txt orig_err.txt

echo "=== END ==="