#ifndef __TFA9894_Seltech_DEMO_H__
#define __TFA9894_Seltech_DEMO_H__
#include "fsl_tfa9894.h"
const uint8_t Firmware_N2A1_patch[] = {
  0x94, 0xff, 0xff, 0x00, 0x00, 0x3a, 0x03, 0x00, 0x90, 0x00, 0x01, 0xfb,
  0x00, 0x91, 0x40, 0x00, 0x7e, 0x83, 0xf9, 0xf1, 0xb5, 0x00, 0x42, 0x38,
  0x82, 0x10, 0x44, 0x00, 0x6c, 0x3e, 0x56, 0x7d, 0x3b, 0x42, 0x40, 0x31,
  0x6b, 0xbf, 0xd6, 0xfe, 0x6b, 0x7d, 0xf9, 0x73, 0xb5, 0x00, 0x42, 0x2b,
  0x82, 0x10, 0x7e, 0x9c, 0x3b, 0x43, 0x40, 0x13, 0x3a, 0xb6, 0x01, 0x0f,
  0xb5, 0x00, 0x57, 0x7a, 0x9b, 0xa0, 0xc2, 0x18, 0x62, 0x88, 0x44, 0x88,
  0x3a, 0x9e, 0xfe, 0xf4, 0x6b, 0x7c, 0xc2, 0xf0, 0x3b, 0x80, 0x1d, 0x85,
  0x3a, 0xa3, 0x00, 0x39, 0xb5, 0x00, 0x56, 0xb9, 0x61, 0x14, 0x7e, 0x9c,
  0x92, 0x10, 0xd4, 0x3f, 0x3b, 0x62, 0x40, 0x23, 0x7f, 0x4e, 0x54, 0x3b,
  0xb5, 0x00, 0x42, 0x01, 0x82, 0x10, 0x54, 0xbe, 0x61, 0x40, 0x42, 0x49,
  0x3b, 0x42, 0x40, 0x21, 0x61, 0x64, 0x54, 0x3d, 0x82, 0x14, 0x7e, 0x9c,
  0x3b, 0x62, 0x40, 0x21, 0xb3, 0x92, 0xfe, 0x9c, 0x3b, 0x00, 0x40, 0x28,
  0xb5, 0x00, 0x42, 0x40, 0x3b, 0x00, 0x40, 0x28, 0xb5, 0x00, 0x7e, 0x40,
  0x3a, 0x80, 0x00, 0x04, 0x72, 0x02, 0x42, 0x02, 0x61, 0x00, 0x76, 0x00,
  0x61, 0x20, 0x54, 0x3d, 0x61, 0x24, 0x54, 0xbe, 0xb5, 0x00, 0x42, 0x00,
  0x82, 0x10, 0x7e, 0x9c, 0x3b, 0x62, 0x40, 0x2f, 0x9b, 0x81, 0xd4, 0x3a,
  0xb5, 0x00, 0x58, 0x3c, 0x3b, 0x00, 0x40, 0x38, 0xb5, 0x00, 0x42, 0x40,
  0x3b, 0x00, 0x40, 0x38, 0xb5, 0x00, 0x58, 0x3c, 0x3a, 0x8e, 0x00, 0x36,
  0xb5, 0x00, 0x44, 0x88, 0x3b, 0x80, 0x0e, 0x2f, 0xb5, 0x00, 0x42, 0x88,
  0x9b, 0x80, 0xd4, 0x3e, 0x6a, 0x1e, 0xc2, 0x40, 0x6c, 0x1e, 0x42, 0x40,
  0x3c, 0xd8, 0x03, 0x00, 0x7f, 0x4e, 0x7d, 0x79, 0x3a, 0x80, 0x00, 0x07,
  0x30, 0x61, 0x00, 0x00, 0x7c, 0x02, 0xc3, 0x40, 0x61, 0xa0, 0xc3, 0x41,
  0xfb, 0x00, 0x91, 0x40, 0x3e, 0x7c, 0x02, 0x43, 0x40, 0x61, 0xa0, 0x43,
  0x41, 0x3a, 0x80, 0x00, 0x05, 0x7f, 0x20, 0xfd, 0x02, 0x7f, 0x22, 0xfb,
  0x04, 0xb5, 0x00, 0x58, 0x7e, 0x3b, 0x80, 0x2b, 0x06, 0xb5, 0x00, 0x54,
  0x7f, 0xb5, 0x00, 0x54, 0x3f, 0x3a, 0x80, 0x00, 0x17, 0x3b, 0x80, 0x2b,
  0x06, 0xb5, 0x00, 0x54, 0x7f, 0xb5, 0x00, 0x54, 0x3f, 0x3a, 0x80, 0x00,
  0x17, 0x3b, 0x80, 0x2b, 0xfa, 0xb5, 0x00, 0x54, 0x7f, 0xb5, 0x00, 0x54,
  0x3f, 0x3a, 0x80, 0x00, 0x0c, 0x3b, 0x80, 0x2b, 0xfa, 0xb5, 0x00, 0x54,
  0x7f, 0xb5, 0x00, 0x54, 0x3f, 0x3a, 0x80, 0x00, 0x0c, 0x3b, 0x80, 0x2b,
  0xfa, 0xb5, 0x00, 0x54, 0x7f, 0xb5, 0x00, 0x54, 0x3f, 0x3a, 0x88, 0x00,
  0x20, 0xb5, 0x00, 0x44, 0x0b, 0x3b, 0x80, 0x1f, 0x73, 0xb5, 0x00, 0x54,
  0xff, 0x8b, 0xc0, 0x54, 0xbf, 0xb5, 0x00, 0x7e, 0x9c, 0x80, 0xb8, 0x44,
  0x0a, 0xb5, 0x00, 0x44, 0x88, 0x3a, 0x80, 0x00, 0x12, 0x30, 0xa0, 0x0f,
  0xd4, 0x3b, 0x80, 0x1f, 0x25, 0x3a, 0x89, 0x00, 0x41, 0x30, 0x80, 0x0f,
  0xd4, 0x9b, 0xc6, 0xfe, 0x41, 0x30, 0x40, 0x0f, 0xde, 0x9b, 0xa0, 0xc2,
  0x41, 0x61, 0x22, 0xfb, 0x04, 0x61, 0x60, 0x43, 0x41, 0x3a, 0x80, 0xff,
  0xf9, 0x3b, 0x80, 0x17, 0xd2, 0xb5, 0x00, 0x54, 0x7f, 0x6a, 0x1f, 0xd8,
  0x3e, 0x3b, 0x00, 0x1f, 0x73, 0x3c, 0xd0, 0xff, 0xfe, 0x6a, 0x7d, 0xfd,
  0x09, 0x3a, 0x9a, 0x00, 0x73, 0x6a, 0x3f, 0xc5, 0x19, 0x3a, 0x80, 0x00,
  0x11, 0x6a, 0xbe, 0xd5, 0xfe, 0x71, 0x25, 0x58, 0x7a, 0x3b, 0x80, 0x3c,
  0x9a, 0x9b, 0x80, 0xd4, 0x7c, 0xb5, 0x00, 0x54, 0xbd, 0x3b, 0x80, 0x3c,
  0xba, 0x3c, 0xc8, 0xff, 0xf9, 0x7c, 0x01, 0x54, 0x3c, 0xb5, 0x00, 0x42,
  0x00, 0xfb, 0x00, 0x91, 0x40, 0x7c, 0x82, 0x10, 0x54, 0xbe, 0x3b, 0x47,
  0x40, 0x86, 0x3a, 0x99, 0xff, 0x96, 0xb5, 0x00, 0x44, 0x08, 0x3a, 0x88,
  0x00, 0x1a, 0x61, 0x44, 0x52, 0x39, 0xd0, 0x0c, 0xfe, 0x9c, 0xb5, 0x00,
  0x7e, 0x9c, 0x94, 0x25, 0x7e, 0x9c, 0x3a, 0x03, 0xff, 0xf9, 0x3a, 0x88,
  0x00, 0x19, 0xb5, 0x00, 0x42, 0x08, 0x82, 0x10, 0x7e, 0x9c, 0x3b, 0x63,
  0x40, 0x8d, 0xb5, 0x00, 0x74, 0x39, 0x3b, 0x00, 0x40, 0x9a, 0xb5, 0x00,
  0x7e, 0x40, 0x7c, 0x00, 0xd4, 0xbf, 0x3a, 0x89, 0x00, 0x17, 0x61, 0x40,
  0x44, 0x88, 0x3a, 0x89, 0x00, 0x09, 0xb5, 0x00, 0x43, 0x08, 0xd0, 0x4c,
  0xfe, 0x9c, 0x3b, 0x80, 0x2c, 0x36, 0x9b, 0x86, 0xfe, 0x85, 0xb5, 0x00,
  0x52, 0x39, 0xd1, 0x84, 0xfe, 0x9c, 0xb5, 0x00, 0x7e, 0x9c, 0x94, 0x27,
  0xfe, 0x9c, 0x3a, 0x03, 0xff, 0xf9, 0x8b, 0xa0, 0x44, 0x19, 0x3a, 0x93,
  0x00, 0x6a, 0x3a, 0x8a, 0xff, 0x8d, 0xb5, 0x00, 0x42, 0x09, 0x80, 0x50,
  0x43, 0x08, 0xb0, 0x33, 0x45, 0x10, 0x69, 0x9c, 0xf9, 0x11, 0xb5, 0x00,
  0x43, 0xa0, 0xa6, 0x27, 0xc3, 0x58, 0x71, 0x84, 0x55, 0xbb, 0x90, 0xb4,
  0xc3, 0x98, 0xd1, 0xf4, 0x7e, 0x9c, 0xb5, 0x00, 0x7e, 0x9c, 0x94, 0x03,
  0xfe, 0x9c, 0xb5, 0x00, 0x60, 0xc0, 0xb2, 0x0f, 0x41, 0xe1, 0xb5, 0x00,
  0x41, 0x90, 0xa2, 0x15, 0xfe, 0x9c, 0x3b, 0x44, 0x40, 0xa4, 0xa0, 0x48,
  0xc0, 0x59, 0xb5, 0x00, 0x7e, 0x9c, 0x6a, 0xbf, 0xc2, 0x48, 0x3b, 0x80,
  0x39, 0xd5, 0xb5, 0x00, 0x42, 0x90, 0xb5, 0x00, 0x74, 0x38, 0x30, 0x90,
  0x0f, 0xd4, 0x3b, 0x80, 0x3c, 0x9a, 0x9b, 0x80, 0xd2, 0x78, 0x30, 0x90,
  0x0f, 0xd4, 0x3b, 0x80, 0x3c, 0xba, 0x3c, 0xc8, 0xff, 0xf7, 0x7f, 0x4e,
  0x54, 0x3f, 0xa7, 0x00, 0x91, 0x40, 0xba, 0x69, 0x1b, 0xc3, 0x00, 0x6a,
  0x1d, 0xd2, 0xb9, 0x3b, 0x80, 0x40, 0xc1, 0xb2, 0xb2, 0xfe, 0x9c, 0xb5,
  0x00, 0x58, 0x3a, 0x3c, 0xd8, 0x03, 0x00, 0x7f, 0x4e, 0x7d, 0x77, 0x82,
  0x18, 0x7e, 0x9c, 0x3b, 0x66, 0x40, 0xc6, 0x3c, 0xc6, 0x40, 0xc5, 0x7f,
  0x4e, 0x7e, 0x9c, 0xb5, 0x00, 0x42, 0xc1, 0x3c, 0xd8, 0x03, 0x00, 0x7f,
  0x4e, 0x7a, 0x80, 0x3a, 0x91, 0x00, 0x74, 0xb5, 0x00, 0x45, 0x10, 0x3a,
  0x80, 0x00, 0x05, 0x3a, 0x9a, 0x00, 0x17, 0x60, 0x8c, 0x40, 0x00, 0xa2,
  0x01, 0x7e, 0x9c, 0x3b, 0x64, 0x40, 0xd6, 0x3a, 0x82, 0x00, 0x18, 0xb5,
  0x00, 0x41, 0x00, 0xa2, 0x01, 0x7e, 0x9c, 0x3b, 0x67, 0x40, 0xd6, 0x3a,
  0x82, 0x00, 0x13, 0x3b, 0x00, 0x40, 0xd8, 0xb5, 0x00, 0x42, 0x00, 0x3a,
  0x82, 0x00, 0x14, 0xb5, 0x00, 0x42, 0x00, 0x60, 0x86, 0xfb, 0x25, 0xb5,
  0x00, 0x43, 0x08, 0xd0, 0x14, 0x7e, 0x9c, 0x38, 0x08, 0x11, 0x36, 0xb5,
  0x00, 0x7e, 0x80, 0x94, 0x01, 0x7e, 0x9c, 0xb5, 0x00, 0x60, 0x00, 0xb2,
  0x08, 0x7e, 0x9c, 0x3c, 0xd8, 0x03, 0x00, 0xb3, 0x10, 0x7e, 0x9c, 0xb5,
  0x00, 0x40, 0x48, 0x03, 0x00, 0x90, 0x00, 0x05, 0x03, 0x00, 0x90, 0x00,
  0x07, 0x66, 0x00, 0x91, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x4c,
  0x00, 0x40, 0x00, 0x00, 0x3b, 0x80, 0x00, 0x00, 0x01, 0x00, 0x10, 0x35,
  0x00, 0x40, 0x3a, 0x00, 0x3b, 0x80, 0x00, 0x00, 0x01, 0x00, 0x24, 0x1b,
  0x00, 0xc2, 0x44, 0x00, 0x9b, 0x81, 0x00, 0x00, 0x01, 0x00, 0x24, 0x1c,
  0x00, 0xc2, 0x42, 0x00, 0x9b, 0xa0, 0x00, 0x00, 0x01, 0x00, 0x24, 0x1d,
  0x00, 0xfe, 0x40, 0x00, 0x6c, 0x1c, 0x00, 0x00, 0x01, 0x00, 0x24, 0x1f,
  0x00, 0x7d, 0x69, 0x00, 0x61, 0x62, 0x00, 0x00, 0x01, 0x00, 0x28, 0x22,
  0x00, 0x40, 0xc8, 0x00, 0x3b, 0x80, 0x00, 0x00, 0x01, 0x00, 0x28, 0x3d,
  0x00, 0x40, 0x6f, 0x00, 0x3b, 0x80, 0x00, 0x00, 0x00, 0x06, 0x00, 0x91,
  0x03, 0x24, 0x00, 0x00, 0x00, 0x03, 0x00, 0x90, 0x00, 0x03, 0x06, 0x00,
  0x91, 0x02, 0x0b, 0x00, 0x00, 0x01, 0x06, 0x00, 0x91, 0x11, 0x36, 0x03,
  0x29, 0x8b, 0x06, 0x00, 0x91, 0x11, 0xff, 0x04, 0x01, 0x01
};
const uint32_t Firmware_N2A1_patch_len = 1090;
/* New characterization with RT/Voice case */
unsigned char Seltech_speaker[] = {
  0x04, 0x81, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xc4, 0xfa, 0xff, 0x98, 0xb9, 0xff, 0x38, 0x64,
  0x00, 0x75, 0xae, 0x00, 0x48, 0x19, 0x00, 0xbc, 0x5a, 0x00, 0x3a, 0x84,
  0x00, 0x47, 0x8d, 0xff, 0xda, 0xdd, 0xff, 0xf7, 0x75, 0xff, 0xcb, 0xb9,
  0xff, 0xf6, 0xcc, 0xff, 0xf6, 0xa4, 0x00, 0x10, 0xc6, 0x00, 0x16, 0x0a,
  0x00, 0x1c, 0xa8, 0x00, 0x1b, 0xdb, 0x00, 0x08, 0x98, 0x00, 0x06, 0xff,
  0x00, 0x00, 0xba, 0xff, 0xf8, 0x67, 0xff, 0xfa, 0x63, 0xff, 0xfe, 0xf2,
  0x00, 0x00, 0x68, 0xff, 0xfe, 0x26, 0x00, 0x03, 0x6b, 0xff, 0xfd, 0x78,
  0xff, 0xfe, 0x0e, 0xff, 0xfb, 0x6f, 0xff, 0xfe, 0xd5, 0xff, 0xfc, 0x40,
  0xff, 0xfe, 0x99, 0xff, 0xfa, 0xd7, 0xff, 0xff, 0xf2, 0x00, 0x01, 0xf5,
  0x00, 0x00, 0xd3, 0x00, 0x00, 0xc8, 0x00, 0x01, 0xc0, 0xff, 0xff, 0xaf,
  0x00, 0x00, 0xed, 0x00, 0x00, 0x64, 0x00, 0x00, 0xbe, 0x00, 0x00, 0xc8,
  0xff, 0xff, 0xd4, 0xff, 0xff, 0xca, 0xff, 0xff, 0x6a, 0x00, 0x00, 0xe8,
  0xff, 0xff, 0xaa, 0xff, 0xff, 0x5c, 0xff, 0xfe, 0x92, 0xff, 0xfe, 0xea,
  0xff, 0xfe, 0xd1, 0xff, 0xfe, 0x69, 0xff, 0xfe, 0x9f, 0xff, 0xff, 0x66,
  0xff, 0xff, 0x26, 0xff, 0xff, 0x63, 0xff, 0xff, 0x20, 0xff, 0xff, 0xe4,
  0x00, 0x00, 0x05, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x20, 0x00, 0x00, 0x0e,
  0x00, 0x00, 0x1c, 0x00, 0x00, 0x65, 0x00, 0x00, 0x73, 0x00, 0x00, 0x50,
  0xff, 0xff, 0xfa, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x61, 0x00, 0x00, 0x27,
  0xff, 0xff, 0xde, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x37, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xb1, 0xff, 0xff, 0xd9, 0x00, 0x00, 0x39, 0x00, 0x00, 0x48,
  0x00, 0x00, 0x20, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x27, 0x00, 0x00, 0x13,
  0xff, 0xff, 0xf7, 0xff, 0xff, 0xf7, 0x00, 0x00, 0x09, 0xff, 0xff, 0xf8,
  0xff, 0xff, 0xfa, 0x00, 0x00, 0x05, 0x00, 0x00, 0x16, 0xff, 0xff, 0xf4,
  0xff, 0xff, 0xd8, 0xff, 0xff, 0xf4, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xd5,
  0xff, 0xff, 0xc2, 0xff, 0xff, 0xd0, 0xff, 0xff, 0xea, 0xff, 0xff, 0xee,
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x11,
  0x00, 0x00, 0x0d, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0d,
  0x00, 0x00, 0x07, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xf6,
  0x00, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x05, 0x40, 0x00, 0x00, 0x4a, 0x3d, 0x71, 0x16, 0x66, 0x66,
  0x00, 0x02, 0xed, 0x00, 0x03, 0x02, 0x15, 0xcc, 0x00, 0x26, 0xc0, 0x00,
  0x04, 0x00, 0x00, 0x09, 0xeb, 0x85, 0x1c, 0xc0, 0x00, 0x00, 0x6f, 0x69,
  0x06, 0x40, 0x00, 0x06, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x07, 0x5c, 0x29,
  0x07, 0x6b, 0x85, 0x0c, 0x3a, 0xe1, 0x04, 0x9c, 0x29, 0x07, 0x68, 0xf6
};
unsigned int Seltech_speaker_len = 456;
#ifdef FACTORY_CALIBRATION_ONLY  
const uint8_t Calibration_vstep[] = {
  0x56, 0x50, 0x33, 0x5f, 0x30, 0x30, 0x33, 0x04, 0x50, 0x4e, 0x73, 0x1c,
  0x43, 0x75, 0x73, 0x74, 0x6f, 0x6d, 0x65, 0x72, 0x50, 0x72, 0x6f, 0x6a,
  0x65, 0x63, 0x74, 0x00, 0x49, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x06, 0x14, 0x00, 0x01, 0x01, 0x51, 0x87, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0xb5, 0x04, 0x81, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x28, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
  0x00, 0x01, 0x27, 0x99, 0x9a, 0x00, 0x00, 0x32, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x87, 0x00, 0x00, 0x01, 0x00, 0x4e, 0x20, 0x00, 0x03, 0xe8, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xe8, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0xe3,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x88, 0xce, 0x00, 0x00, 0xba,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0xd0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x0a,
  0x3d, 0x71, 0x00, 0x01, 0x2c, 0x00, 0x0b, 0xb8, 0x00, 0x00, 0x7d, 0x00,
  0x05, 0xdc, 0x00, 0x27, 0x10, 0x03, 0x33, 0x33, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x05, 0x00, 0x01, 0xf4, 0x00, 0x27, 0x10, 0x06, 0x40, 0x00, 0x00,
  0x01, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x28, 0xf5, 0xc3, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x47, 0x00, 0x00, 0x01, 0x00,
  0x01, 0x2c, 0x00, 0x4e, 0x20, 0xe2, 0x00, 0x00, 0x9c, 0x00, 0x00, 0xd8,
  0x00, 0x00, 0x00, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0x00, 0x00, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0x00, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x4e, 0x20, 0x00,
  0x27, 0x10, 0x00, 0x13, 0x88, 0x00, 0x00, 0x01, 0x00, 0x00, 0x23, 0x00,
  0x75, 0x30, 0x00, 0x03, 0xe8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1e,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0xc3, 0x50, 0x00,
  0x75, 0x30, 0x00, 0xc3, 0x50, 0x00, 0x27, 0x10, 0x10, 0xa3, 0xd7, 0x19,
  0x99, 0x9a, 0x01, 0x40, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0xcc, 0xcd, 0x00, 0x00, 0x01, 0x26, 0x66, 0x66, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x66, 0x66, 0x00, 0x40, 0x00, 0x00, 0x75, 0x30, 0x00,
  0xc3, 0x50, 0x00, 0x1b, 0x58, 0x00, 0x4e, 0x20, 0x13, 0x33, 0x33, 0x06,
  0x66, 0x66, 0x00, 0x03, 0xe8, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x33, 0x33, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xe8, 0x00, 0xea, 0x60, 0x00,
  0x03, 0xe8, 0x00, 0xea, 0x60, 0x20, 0x00, 0x00, 0x06, 0x66, 0x66, 0x00,
  0x03, 0xe8, 0x01, 0x40, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00,
  0x27, 0x10, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x13, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x88, 0x00, 0x00, 0x00, 0x00, 0x03, 0xa2, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x87, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x64, 0x00, 0x01, 0x90, 0x00,
  0x07, 0xd0, 0x00, 0xaf, 0xc8, 0x00, 0x13, 0x88, 0x00, 0x03, 0xe8, 0x00,
  0x4e, 0x20, 0x00, 0x13, 0x88, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0a,
  0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0xfd,
  0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0xc8, 0x00,
  0x0b, 0xb8, 0xec, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x05, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x64, 0x00, 0x01, 0xf4, 0xe2, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0xc8, 0x3f,
  0x45, 0x39, 0xb0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x3e, 0x04, 0x82, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xb8, 0xb8, 0x7e, 0x35, 0xf9,
  0x0f, 0xdb, 0x09, 0xe0, 0x49, 0xee, 0x0f, 0xdb, 0x09, 0x00, 0x00, 0x01,
  0xc2, 0x53, 0x66, 0x7d, 0x80, 0x82, 0x3d, 0x31, 0xca, 0x82, 0x7f, 0x7e,
  0x40, 0x7a, 0xcf, 0x00, 0x00, 0x00, 0xea, 0xaa, 0xab, 0x00, 0x00, 0x00,
  0x25, 0x55, 0x55, 0x4a, 0xaa, 0xaa, 0x25, 0x55, 0x55, 0x00, 0x00, 0x00,
  0xb1, 0xa1, 0x8a, 0x69, 0x83, 0xd9, 0x5c, 0x19, 0x8d, 0x96, 0x7c, 0x27,
  0x72, 0x44, 0xe8, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x71, 0xcf, 0x54, 0x02, 0x00, 0x00, 0x60, 0x04, 0x81, 0x07, 0x80, 0x00,
  0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x14, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x13, 0x88, 0x00, 0x13, 0x88,
  0x00, 0x13, 0x88, 0x00, 0x13, 0x88, 0x00, 0x13, 0x88, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x90, 0x00, 0x33, 0x33, 0x00, 0x33,
  0x33, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x14, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10, 0x00, 0x27, 0x10, 0xd7, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x02, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27,
  0x10, 0x00, 0x27, 0x10, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x20, 0x00, 0x33,
  0x33, 0x00, 0x33, 0x33, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x14, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10, 0x00, 0x27,
  0x10, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x02, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x27, 0x10, 0x00, 0x27, 0x10, 0xd7, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06,
  0x40, 0x00, 0x33, 0x33, 0x00, 0x33, 0x33, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x02, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27,
  0x10, 0x00, 0x27, 0x10, 0xd7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x14, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x10, 0x00, 0x27, 0x10, 0xd7, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint32_t Calibration_vstep_len = 1075;
#endif /* FACTORY_CALIBRATION_ONLY */
const uint8_t music_P_48000_vstep[] = {
  0x56, 0x50, 0x33, 0x5f, 0x30, 0x30, 0x33, 0x04, 0x38, 0xd0, 0xd7, 0xe2,
  0x4e, 0x58, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x65, 0x6d, 0x6f,
  0x00, 0x00, 0x00, 0x00, 0x44, 0x65, 0x76, 0x4b, 0x69, 0x74, 0x00, 0x00,
  0x06, 0x14, 0x00, 0x01, 0x01, 0x51, 0x87, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x00, 0xb5, 0x04, 0x81, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x28, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
  0x00, 0x01, 0x27, 0x99, 0x9a, 0x00, 0x00, 0x32, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x64, 0x00, 0x00, 0x02, 0x00, 0x4e, 0x20, 0x00, 0x03, 0xe8, 0x00,
  0x00, 0x00, 0x00, 0x03, 0xe8, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0xe3,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x88, 0xce, 0x00, 0x00, 0xba,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0xd0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x0a,
  0x3d, 0x71, 0x00, 0x01, 0x2c, 0x00, 0x0b, 0xb8, 0x00, 0x00, 0x7d, 0x00,
  0x05, 0xdc, 0x00, 0x27, 0x10, 0x00, 0x66, 0x66, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x05, 0x00, 0x01, 0xf4, 0x00, 0x61, 0xa8, 0x06, 0x40, 0x00, 0x00,
  0x01, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x28, 0xf5, 0xc3, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x47, 0x00, 0x00, 0x01, 0x00,
  0x01, 0x2c, 0x00, 0x4e, 0x20, 0xe2, 0x00, 0x00, 0x9c, 0x00, 0x00, 0xd8,
  0x00, 0x00, 0x00, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0x00, 0x00, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x00, 0x00, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x14, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x4e, 0x20, 0x00,
  0x13, 0x88, 0x00, 0x13, 0x88, 0x00, 0x00, 0x01, 0x00, 0x00, 0x23, 0x00,
  0x75, 0x30, 0x00, 0x75, 0x30, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1e,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x27, 0x10, 0x00,
  0x01, 0xf4, 0x00, 0xc3, 0x50, 0x00, 0x01, 0xf4, 0x26, 0x66, 0x66, 0x00,
  0xc4, 0x9c, 0x01, 0x40, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
  0xcc, 0xcd, 0x00, 0x00, 0x01, 0x26, 0x66, 0x66, 0x00, 0x00, 0x01, 0x03,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2a, 0xf8, 0x00,
  0x9c, 0x40, 0x00, 0x0f, 0xa0, 0x00, 0x27, 0x10, 0x1e, 0xb8, 0x52, 0x07,
  0xae, 0x14, 0x00, 0x03, 0xe8, 0x03, 0xc0, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x33, 0x33, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xe8, 0x00, 0xea, 0x60, 0x00,
  0x03, 0xe8, 0x00, 0xea, 0x60, 0x20, 0x00, 0x00, 0x06, 0x66, 0x66, 0x00,
  0x03, 0xe8, 0x01, 0x40, 0x00, 0x00, 0x03, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x04, 0xb0, 0x00, 0xa3, 0xd7, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x13, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x13, 0x88, 0x00, 0x00, 0x00, 0x00, 0x03, 0xa2, 0x03, 0x33, 0x33, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x91, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x64, 0x00, 0xea, 0x60, 0x00, 0x1f, 0x40, 0x00, 0x00, 0x00, 0x00,
  0xc3, 0x50, 0x00, 0x3a, 0x98, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x08,
  0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0xfd,
  0x66, 0x66, 0x04, 0x33, 0x33, 0x00, 0x02, 0x8a, 0x00, 0x00, 0x96, 0x00,
  0x2a, 0xf8, 0xec, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x0f, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xa0, 0xd7, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x64, 0x3f,
  0x45, 0x39, 0xb0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x3e, 0x04, 0x82, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc1, 0xa7, 0x5b, 0x7e, 0x50, 0xa2,
  0x0f, 0xdd, 0xcd, 0xe0, 0x44, 0x66, 0x0f, 0xdd, 0xcd, 0x00, 0x00, 0x01,
  0xc1, 0xa6, 0xf9, 0x7e, 0x23, 0x65, 0x3e, 0x31, 0x2a, 0x81, 0xdc, 0x9b,
  0x40, 0x27, 0xdd, 0x00, 0x00, 0x01, 0xc1, 0xb7, 0x5e, 0x7e, 0x34, 0x72,
  0x3d, 0x54, 0x05, 0x81, 0xcb, 0x8e, 0x40, 0xf4, 0x9d, 0x00, 0x00, 0x01,
  0xc3, 0x92, 0xb6, 0x7b, 0xa3, 0xab, 0x3d, 0x16, 0x13, 0x84, 0x5c, 0x55,
  0x3f, 0x57, 0x37, 0x00, 0x00, 0x01, 0xc4, 0x6e, 0x19, 0x79, 0xeb, 0x61,
  0x3b, 0xfc, 0x09, 0x86, 0x14, 0x9f, 0x3f, 0x95, 0xdd, 0x00, 0x00, 0x01,
  0xcd, 0x39, 0xae, 0x29, 0x21, 0xae, 0x31, 0x6f, 0xeb, 0xd6, 0xde, 0x52,
  0x41, 0x56, 0x66, 0x00, 0x00, 0x01, 0xc7, 0x08, 0xaa, 0x6d, 0xda, 0xc6,
  0x38, 0x89, 0x7a, 0x92, 0x25, 0x3a, 0x40, 0x6d, 0xdb, 0x00, 0x00, 0x00,
  0xa1, 0x62, 0x1b, 0x7e, 0x1b, 0x1f, 0x66, 0x22, 0xbb, 0x81, 0xe4, 0xe1,
  0x78, 0x7b, 0x2a, 0x00, 0x00, 0x01, 0xd9, 0xf7, 0xa3, 0x5f, 0x31, 0xe3,
  0x1c, 0x2c, 0x0d, 0xb7, 0xbf, 0x1a, 0x32, 0xeb, 0x53, 0x00, 0x00, 0x01,
  0xf7, 0x0c, 0xd6, 0xed, 0x1e, 0x83, 0x26, 0x8a, 0x9b, 0x4d, 0x15, 0x36,
  0x26, 0x8a, 0x9b, 0x02, 0x00, 0x00, 0x60, 0x04, 0x81, 0x07, 0x80, 0x00,
  0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x3c, 0x00, 0x01, 0x90, 0x00, 0x55, 0xf0, 0x00, 0x1b,
  0x58, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x80, 0x00, 0x23, 0x28, 0xf3, 0x80,
  0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x81, 0x01, 0x33, 0x33, 0x01, 0x33,
  0x33, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0xee, 0x00, 0x00, 0x02, 0xe6,
  0x66, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xc8, 0x00, 0x0b, 0xb8, 0xd7, 0x00,
  0x00, 0x01, 0x99, 0x9a, 0x00, 0x00, 0x14, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x01, 0xe9, 0x00, 0x00, 0x04, 0x99, 0x9a, 0x00, 0x00, 0x0a, 0x00, 0x00,
  0x82, 0x00, 0x04, 0xb0, 0xd7, 0x00, 0x00, 0x02, 0xb3, 0x33, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x7f, 0x00, 0xcc,
  0xcd, 0x00, 0xcc, 0xcd, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0xe9, 0x80,
  0x00, 0x04, 0x33, 0x33, 0x00, 0x00, 0x19, 0x00, 0x00, 0xfa, 0x00, 0x11,
  0x94, 0xf6, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x01, 0xe5, 0x66, 0x66, 0x06, 0x99, 0x9a, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0xb4, 0x00, 0x05, 0x78, 0xd7, 0x00, 0x00, 0x04, 0x33,
  0x33, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0b,
  0xb8, 0x00, 0x66, 0x66, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x03, 0xe6, 0x80, 0x00, 0x00, 0xeb, 0x85, 0x00, 0x00, 0x8c, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x14, 0xfe, 0x4c, 0xcd, 0x01, 0xb3, 0x33, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xd5, 0x00, 0x00, 0x01, 0x66,
  0x66, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xfb, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f
};
const uint32_t music_P_48000_vstep_len = 1075;
unsigned char seltech_music_P_48000_excursion_filter_msg[] = {
  0x04, 0x81, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0xcc, 0xcd, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x3f, 0x09, 0x18,
  0x80, 0xec, 0x4c, 0x40, 0x0e, 0x67, 0xc0, 0xe8, 0xe4, 0x7f, 0x14, 0x18,
  0x00, 0x5c, 0xf4, 0x00, 0xb9, 0xe9, 0x00, 0x5c, 0xf4, 0xca, 0x07, 0x9a,
  0x74, 0x84, 0x95, 0x21, 0x01, 0x90, 0xb3, 0xff, 0xa7, 0x2b, 0xd4, 0xb9,
  0xcd, 0x3d, 0xb4, 0x71, 0xec, 0x5d
};
unsigned int seltech_music_P_48000_excursion_filter_msg_len = 78;
/* Mono down mix */
const uint8_t Mix_SetInputSelector_msg[] = {
  0x00, 0x80, 0x06, 0xff, 0xff, 0x01, 0xff, 0xff, 0x32, 0x00, 0x0f, 0xff
};
const uint8_t Right_SetInputSelector_msg[] = {
  0x00, 0x80, 0x06, 0xff, 0xff, 0xf1, 0xff, 0xff, 0x32, 0x00, 0x0f, 0xff
};
const uint8_t Left_SetInputSelector_msg[] = {
  0x00, 0x80, 0x06, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x32, 0x00, 0x0f, 0xff
};
const uint32_t SetInputSelector_msg_len = 12;
const uint8_t SetGains_msg[] = {
  0x00, 0x80, 0x0a, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff
};
const uint32_t SetGains_msg_len = 9;
const uint8_t SetLagW_msg[] = {
  0x04, 0x81, 0x01, 0x00, 0x00, 0x00
};
const uint32_t SetLagW_msg_len = 6;
const uint8_t SetOutputSelector_msg[] = {
  0x00, 0x80, 0x08, 0xff, 0xff, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
const uint32_t SetOutputSelector_msg_len = 12;
const uint8_t SetProgramConfig_msg[] = {
  0x00, 0x80, 0x09, 0x00, 0x00, 0x10
};
const uint32_t SetProgramConfig_msg_len = 6;
const uint8_t SetSensesCal_msg[] = {
  0x00, 0x80, 0x05, 0x5b, 0x66, 0x67, 0x0d, 0x85, 0x1f, 0x00, 0x00, 0x01
};
const uint32_t SetSensesCal_msg_len = 12;
const uint8_t SetSensesDelay_msg[] = {
  0x00, 0x80, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
};
const uint32_t SetSensesDelay_msg_len = 9;
const uint8_t SetvBatFactors_msg[] = {
  0x00, 0x80, 0x02, 0x6e, 0x63, 0x20
};
const uint32_t SetvBatFactors_msg_len = 6;
#endif /* __TFA9894_Seltech_DEMO_H__ */
