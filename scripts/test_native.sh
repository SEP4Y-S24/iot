echo "Running all native tests..."

echo "Running wifi_connect_state test..."
pio test -e test_wifi_connect_state -f "./test/"

echo "Running ccp_protocol test..."
pio test -e test_ccp_protocol -f "./test/"