// File format is Binary, little-endian, no padding
// File extension ".cbl"
// Name = uint16_t length + UTF-8 bytes (no trailing zero)

char magic[4] = "CTBL"
uint16_t version = 2
uint8_t connectorsCount
// Array of all connectors
Connector[connectorsCount] {
	uint8_t id;
	uint8_t pinCount;
	Name name;
	uint8_t isLeft;
	uint32_t color;              // reserved
	uint8_t testerPins[pinCount]; // slot pin (1..60) for each connector pin, 0 = not assigned
}
// Main cable
Cable {
	uint32_t color
	Name name
	uint8_t wiresCount
	// Array of wires
	Wire wires[wiresCount] {
		uint8_t leftConnectorId;   // 0 = not connected
		uint8_t rightConnectorId;  // 0 = not connected
		uint8_t leftPin;
		uint8_t rightPin;
		uint32_t color;
		uint32_t color2;           // 0xffffffff = none
	}
	uint8_t cablesCount
	// Recursive array of cables
	Cable cables[cablesCount]
}
