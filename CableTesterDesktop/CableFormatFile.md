// File format is Binary
// File extension ".cbl"

uint8_t connectorsCcount
// Array of all connectors
ConnectorCT_t[connectorsCcount] {
		Connector{
			uint8_t id;
			uint8_t pinCount;
			char name[100];
			uint8_t isLeft;
			uint32_t color;
			uint8_t[pinCount];
		}
	}
// Cable
CableCT_t {
	uint32_t color
	char name[100]
	uint8_t wiresCount
	// Array of wires
	WireCT_t wires[wiresCount] {
		uint8_t leftConnectorId;
		uint8_t rightConnectorId;
		uint8_t leftPin;
		uint8_t rightPin;
		uint32_t color;
		uint32_t color2;
	}
	uint8_t cablesCount
	// Recursical Array of cables
	CableCT_t[cablesCount]
}