#ifndef BOOTLOADER_SLOTS_EXAM_MODE_H
#define BOOTLOADER_SLOTS_EXAM_MODE_H

extern "C" {
    #include <stdint.h>
  }

namespace Bootloader {
namespace ExamMode {

static const uint32_t SlotAExamModeBufferStartBefore16 = 0x90001000;
static const uint32_t SlotAExamModeBufferEndBefore16 = 0x90003000;

static const uint32_t SlotAExamModeBufferStartEpsilon16 = 0x903f0000;
static const uint32_t SlotAExamModeBufferEndEpsilon16 = 0x90400000;

static const uint32_t SlotAExamModeBufferStartEpsilon22 = 0x903f0400;
static const uint32_t SlotAExamModeBufferEndEpsilon22 = 0x90400000;

static const uint32_t SlotBExamModeBufferStartBeforeEpsilon16 = 0x90401000;
static const uint32_t SlotBExamModeBufferEndBeforeEpsilon16 = 0x90403000;

static const uint32_t SlotBExamModeBufferStartEpsilon16 = 0x907f0000;
static const uint32_t SlotBExamModeBufferEndEpsilon16 = 0x90800000;

static const uint32_t SlotBExamModeBufferStartEpsilon22 = 0x907f0400;
static const uint32_t SlotBExamModeBufferEndEpsilon22 = 0x90800000;

static const uint32_t SlotKhiExamModeBufferStart = 0x90181000;
static const uint32_t SlotKhiExamModeBufferEnd = 0x90183000;

class SlotsExamMode{
  public:
    static uint8_t FetchSlotExamMode(const char* version, const char* Slot);
    static uint8_t FetchSlotAExamMode(const char* version);
    static uint8_t FetchSlotBExamMode(const char* version);
    static uint8_t FetchSlotKhiExamMode(const char* version);

    static uint32_t getSlotAStartExamAddress(int ExamVersion);
    static uint32_t getSlotAEndExamAddress(int ExamVersion);
    static uint32_t getSlotBStartExamAddress(int ExamVersion);
    static uint32_t getSlotBEndExamAddress(int ExamVersion);
    static uint32_t getSlotKhiStartExamAddress();
    static uint32_t getSlotKhiEndExamAddress();

    static uint8_t examFetch15(uint32_t start, uint32_t end);
    static uint8_t examFetch1718(uint32_t start, uint32_t end);
    static uint8_t examFetch16(uint32_t start, uint32_t end);
    static uint8_t examFetch19(uint32_t start, uint32_t end);

};

enum class ExamMode : int8_t {
    Unknown = -1,
    Off = 0,
    Standard = 1,
    NoSym = 2,
    NoSymNoText = 3,
    Dutch = 4,
  };

}
}

#endif
