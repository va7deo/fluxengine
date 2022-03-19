#include "globals.h"
#include "decoders/decoders.h"
#include "agat.h"
#include "crc.h"
#include "fluxmap.h"
#include "decoders/fluxmapreader.h"
#include "sector.h"
#include "bytes.h"
#include "fmt/format.h"
#include <string.h>

/*
 * data:    X  X  X  X   X  X  X  X   X  -  -  X   -  X  -  X   -  X  X  -   X  -  X  -  = 0xff956a
 * flux:   01 01 01 01  01 01 01 01  01 00 10 01  00 01 00 01  00 01 01 00  01 00 01 00  = 0x555549111444
 * 
 * data:    X  X  X  X   X  X  X  X   -  X  X  -   X  -  X  -   X  -  -  X   -  X  -  X  = 0xff6a95
 * flux:   01 01 01 01  01 01 01 01  00 01 01 00  01 00 01 00  01 00 10 01  00 01 00 01  = 0x555514444911
 * 
 * Each pattern is prefixed with this one:
 *
 * data:    -  -   -  X   -  -   X  - = 12
 * flux:   10 10  10 01  00 10  01 00 = a924
 * magic:  10 00  10 01  00 10  01 00 = 8924
 *            ^
 */

static const uint64_t SECTOR_ID = 0x8924555549111444;
static const FluxPattern SECTOR_PATTERN(64, SECTOR_ID);

static const uint64_t DATA_ID = 0x8924555514444911;
static const FluxPattern DATA_PATTERN(64, DATA_ID);

static const FluxMatchers ALL_PATTERNS = {
	&SECTOR_PATTERN,
	&DATA_PATTERN
};

class AgatDecoder : public AbstractDecoder
{
public:
	AgatDecoder(const DecoderProto& config):
		AbstractDecoder(config)
	{}

    nanoseconds_t advanceToNextRecord() override
	{
		return seekToPattern(ALL_PATTERNS);
	}

    void decodeSectorRecord() override
	{
		if (readRaw64() != SECTOR_ID)
			return;

		auto bytes = decodeFmMfm(readRawBits(64)).slice(0, 4);
		if (bytes[3] != 0x5a)
			return;

		_sector->logicalTrack = bytes[1] >> 1;
		_sector->logicalSector = bytes[2];
		_sector->logicalSide = bytes[1] & 1;
		_sector->status = Sector::DATA_MISSING; /* unintuitive but correct */
	}

	void decodeDataRecord() override
	{
		if (readRaw64() != DATA_ID)
			return;

		Bytes bytes = decodeFmMfm(readRawBits((AGAT_SECTOR_SIZE+2)*16)).slice(0, AGAT_SECTOR_SIZE+2);

		if (bytes[AGAT_SECTOR_SIZE+1] != 0x5a)
			return;

		_sector->data = bytes.slice(0, AGAT_SECTOR_SIZE);
		uint8_t wantChecksum = bytes[AGAT_SECTOR_SIZE];
		uint8_t gotChecksum = agatChecksum(_sector->data);
		_sector->status = (wantChecksum = gotChecksum) ? Sector::OK : Sector::BAD_CHECKSUM;
	}
};

std::unique_ptr<AbstractDecoder> createAgatDecoder(const DecoderProto& config)
{
	return std::unique_ptr<AbstractDecoder>(new AgatDecoder(config));
}



