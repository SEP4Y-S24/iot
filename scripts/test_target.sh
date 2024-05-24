echo "Running all target tests..."

echo "Running wifi module test..."
pio test -e target_test -f "./test/target_tests/test_target_wifi"

echo "Running dht11 module test..."
pio test -e target_test -f "./test/target_tests/test_target_dht11"
