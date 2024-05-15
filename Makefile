make setup-env:
	@echo "Setting up environment..."
	cd ./scripts && chmod +x ./setup_env.sh && ./setup_env.sh

make test-native:
	@echo "Running native tests..."
	cd ./scripts && chmod +x ./test_native.sh && ./test_native.sh