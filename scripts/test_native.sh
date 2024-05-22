echo "Running all native tests..."

echo "Running wifi_connect_state test..."
pio test -e test_wifi_connect_state -f "./test/"

echo "Running ccp_protocol test..."
pio test -e test_ccp_protocol -f "./test/"

echo "Running alarm test..."
pio test -e test_alarm -f "./test/"

echo "Running message_handler test..."
pio test -e test_message_handler -f "./test/"

echo "Running auth_test test..."
pio test -e test_auth_state -f "./test/"