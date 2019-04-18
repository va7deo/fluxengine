#ifndef DECODERS_H
#define DECODERS_H

#include "bytes.h"
#include "sector.h"
#include "record.h"

class Sector;
class Fluxmap;
class FluxmapReader;
class RawRecord;
class RawBits;
class Track;

typedef std::vector<std::unique_ptr<RawRecord>> RawRecordVector;
typedef std::vector<std::unique_ptr<Sector>> SectorVector;

extern void setDecoderManualClockRate(double clockrate_us);

extern Bytes decodeFmMfm(std::vector<bool>::const_iterator start,
    std::vector<bool>::const_iterator end);

static inline Bytes decodeFmMfm(const std::vector<bool> bits)
{ return decodeFmMfm(bits.begin(), bits.end()); }

class AbstractDecoder
{
public:
    virtual ~AbstractDecoder() {}

    nanoseconds_t guessClock(Track& track) const;
    virtual nanoseconds_t guessClockImpl(Track& track) const;

    virtual void decodeToSectors(Track& track) = 0;
};

/* DEPRECATED */
class AbstractSeparatedDecoder : public AbstractDecoder
{
public:
    virtual ~AbstractSeparatedDecoder() {}

    virtual RawRecordVector extractRecords(const RawBits& rawbits) const = 0;
    virtual SectorVector decodeToSectors(const RawRecordVector& rawrecords,
            unsigned physicalTrack, unsigned physicalSide) = 0;

    void decodeToSectors(Track& track);
    void decodeToSectors(const RawBits& bitmap, Track& track);
};

/* DEPRECATED */
class AbstractSoftSectorDecoder : public AbstractSeparatedDecoder
{
public:
    virtual ~AbstractSoftSectorDecoder() {}

    RawRecordVector extractRecords(const RawBits& rawbits) const;

    virtual int recordMatcher(uint64_t fifo) const = 0;
};

/* DEPRECATED */
class AbstractHardSectorDecoder : public AbstractSeparatedDecoder
{
public:
    virtual ~AbstractHardSectorDecoder() {}

    RawRecordVector extractRecords(const RawBits& rawbits) const;
};

class AbstractStatefulDecoder : public AbstractDecoder
{
public:
    void decodeToSectors(Track& track);
    void discardRecord(FluxmapReader& fmr);
    void pushRecord(FluxmapReader& fmr, Track& track, Sector& sector);

protected:
    virtual nanoseconds_t findSector(FluxmapReader& fmr, Track& track) = 0;
    virtual void decodeSingleSector(FluxmapReader& fmr, Track& track, Sector& sector) = 0;

private:
    Fluxmap::Position _recordStart;
};

class AbstractSplitDecoder : public AbstractStatefulDecoder
{
    void decodeSingleSector(FluxmapReader& fmr, Track& track, Sector& sector) override;

    virtual nanoseconds_t findData(FluxmapReader& fmr, Track& track) = 0;
    virtual void decodeHeader(FluxmapReader& fmr, Track& track, Sector& sector) = 0;
    virtual void decodeData(FluxmapReader& fmr, Track& track, Sector& sector) = 0;
};

#endif
