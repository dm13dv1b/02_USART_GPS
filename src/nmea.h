
struct gpsdata_t {
	// time
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t hsec;

	// date
	uint8_t day;
	uint8_t month;
	uint8_t year;

	// position
	uint8_t valid;
	uint8_t rmc_valid;
	int32_t lat;
	int32_t lon;
	uint16_t alt;

	uint16_t heading;
	uint16_t speed;

	uint8_t sats;
	uint16_t hdop;
};

extern struct gpsdata_t gpsdata;

void NMEA_Parse(char *buf, uint16_t len);
