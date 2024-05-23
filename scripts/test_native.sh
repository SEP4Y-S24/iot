echo "Running all native tests..."

echo "Running wifi_connect_state test..."
pio test -e native_test -f "./test/native_tests/native_test_wifi_connect_state"

echo "Running ccp_protocol test..."
pio test -e native_test -f "./test/native_tests/native_test_ccp_protocol"

echo "Running alarm test..."
pio test -e native_test -f "./test/native_tests/native_test_alarm"

echo "Running message_handler test..."
pio test -e native_test -f "./test/native_tests/native_test_message_handler"

echo "Running auth_test test..."
pio test -e native_test -f "./test/native_tests/native_test_auth_state"