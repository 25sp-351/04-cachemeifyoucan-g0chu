make clean
make

cat << EOF > pieces_test_auto.txt
3, 10
6, 28
12, 50
EOF

tests=(
  "3|1 @ 3 = 10"
  "6|1 @ 6 = 28"
  "12|2 @ 6 = 56"
  "24|4 @ 6 = 112"
)

failed=0

for test in "${tests[@]}"; do
    input=$(echo "$test" | cut -d'|' -f1)
    expected=$(echo "$test" | cut -d'|' -f2)

    output=$(echo "$input" | ./rod_cut_a pieces_test_auto.txt | head -n 1)

    if [ "$output" != "$expected" ]; then
        echo "failed: input '$input' expected '$expected' but got '$output'"
        failed=1
    else
        echo "test passed for rod length $input"
    fi
done

make clean

if [ $failed -eq 0 ]; then
    echo "success"
else
    exit 1
fi


