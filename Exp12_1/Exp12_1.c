/* ========================================================================== */
/*                       Exp12_1.c : Music Melody Play                        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

#define VLA 10991                              // define note, octave 2
#define VLAX 14052
#define VLB 16942
#define LOC 19669                              // define note, octave 3
#define LOCX 22243
#define LOD 24673
#define LODX 26966
#define LOE 29131
#define LOF 31174
#define LOFX 33103
#define LOG 34923
#define LOGX 36642
#define LOA 38263
#define LOAX 39794
#define LOB 41238
#define MIC 42602                              // define note, octave 4
#define MICX 43890
#define MID 45105
#define MIDX 46251
#define MIE 47334
#define MIF 48355
#define MIFX 49320
#define MIG 50230
#define MIGX 51089
#define MIA 51900
#define MIAX 52665
#define MIB 53387
#define HIC 54069                              // define note, octave 5
#define HICX 54713
#define HID 55320
#define HIDX 55894
#define HIE 56435
#define HIF 56946
#define HIFX 57428
#define HIG 57883
#define HIGX 58312
#define HIA 58718
#define HIAX 59100
#define HIB 59462
#define VHC 59803                              // define note, octave 6
#define VHCX 60124
#define VHD 60428
#define VHDX 60715
#define VHE 60985

#define NOTE32 1*3                             // define note length
#define NOTE16 2*3
#define NOTE16D 3*3
#define NOTE16T 2*2
#define NOTE8 4*3
#define NOTE8D 6*3
#define NOTE8T 4*2
#define NOTE4 8*3
#define NOTE4D 12*3
#define NOTE4T 8*2
#define NOTE2 16*3
#define NOTE2D 24*3
#define NOTE1 32*3

#define REST32 1*3                             // define rest length
#define REST16 2*3
#define REST16D 3*3
#define REST8 4*3
#define REST8D 6*3
#define REST4 8*3
#define REST4D 12*3
#define REST2 16*3
#define REST2D 24*3
#define REST1 32*3

unsigned char tempo;

Play_note(unsigned int sound, unsigned int note)
{                                              /* play note */
  if (sound == RCAP2H * 256 + RCAP2L)          // if same note, cut shortly
    Delay_ms(1);

  T2CON = 0x04;                                // TR2=1, C/-T2=0
  T2MOD = 0x02;                                // T2OE=1(speaker on)
  RCAP2H = (sound >> 8);
  RCAP2L = sound & 0x00FF;

  Delay_ms(note * tempo * 7);                  // note play time

  T2MOD = 0x00;                                // speaker off(T2OE=0)
}

Play_rest(unsigned int rest)
{                                              /* play rest */
  Delay_ms(rest * tempo * 7);                  // rest play time
}

main()
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    LCD_string(0x80, " * MUSIC PLAY * ");      // display title
    LCD_string(0xC0, "PongdangPongdang");      // display music
    tempo = 4;                                 // set tempo
    Play_note(MIC, NOTE8);                     // line 1
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE4);                     // line 2
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIA, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MIA, NOTE8D);                    // line 3
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_rest(REST8);
    Play_note(MIG, NOTE8D);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE4D);
    Play_rest(REST8);
    Play_note(MID, NOTE8D);                    // line 4
    Play_note(MIE, NOTE16);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE16);
    Play_note(MIF, NOTE16);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE4D);
    Play_rest(REST8);
    Delay_ms(1000);

    LCD_string(0xC0, "18-Year Old Girl");      // display music
    tempo = 3;                                 // set tempo
    Play_note(MIG, NOTE4D);                    // line 1
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 2
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 3
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE8);                     // line 4
    Play_note(HIE, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8D);
    Play_note(HIC, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 5
    Play_note(HIE, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);
    Play_note(MIG, NOTE4D);                    // line 6
    Play_note(HIG, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE2D);
    Play_note(MIG, NOTE4D);                    // line 7
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE8);                     // line 8
    Play_note(HIE, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8D);
    Play_note(HIC, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE2);
    Delay_ms(1000);

    LCD_string(0xC0, "Triangle Rotary ");      // display music
    tempo = 5;                                 // set tempo
    Play_note(MIC, NOTE4);                     // prelude
    Play_note(MIC, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(HIE, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE2);
    Play_note(HIC, NOTE8);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE4);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);                          // line 1
    Play_note(MIC, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE1);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE2D);
    Play_rest(REST8);
    Play_note(HIE, NOTE4D);                    // line 2
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE16);
    Play_rest(REST8);
    Play_note(MIE, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE2);
    Play_rest(REST8);
    Play_note(LOA, NOTE8);
    Play_note(LOA, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE4);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIC, NOTE16);
    Play_note(LOA, NOTE16);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);
    Play_note(MID, NOTE4D);                    // line 3
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE4);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_rest(REST8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE2);
    Play_rest(REST8);
    Play_note(MIG, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE16T);
    Play_note(HIE, NOTE16T);
    Play_note(HID, NOTE16T);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIE, NOTE2D);
    Play_rest(REST8);
    Play_note(HIF, NOTE4D);                    // line 4
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(HIC, NOTE4);
    Play_rest(REST8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_rest(REST8);
    Play_note(MIE, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MIE, NOTE16T);
    Play_note(MIF, NOTE16T);
    Play_note(MIE, NOTE16T);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE2D);
    Delay_ms(1000);

    LCD_string(0xC0, "  Chil-Gab San  ");      // display music
    tempo = 4;                                 // set tempo
    Play_note(HIG, NOTE16);                    // prelude line 1
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2D);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE2);
    Play_note(HID, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE2D);
    Play_rest(REST32);
    Play_note(MID, NOTE4D);                    // prelude line 2
    Play_note(MID, NOTE8);
    Play_note(MIF, NOTE8);
    Play_note(MID, NOTE16);
    Play_note(MIF, NOTE16);
    Play_note(MIG, NOTE2);
    Play_note(MIAX, NOTE4);
    Play_note(MIG, NOTE2);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2);
    Play_rest(REST8);
    Play_note(HID, NOTE4);                     // line 1
    Play_note(HID, NOTE2);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE2);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_rest(REST8);
    Play_note(MID, NOTE8);                     // line 2
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(HIC, NOTE8T);
    Play_note(MIAX, NOTE8T);
    Play_note(HIC, NOTE8T);
    Play_note(HID, NOTE1);
    Play_rest(REST4);
    Play_note(HID, NOTE4);                     // line 3
    Play_note(HID, NOTE4);
    Play_note(HIF, NOTE4);
    Play_note(HIG, NOTE2);
    Play_note(HIF, NOTE4);
    Play_note(HID, NOTE4);
    Play_note(HIF, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE2);
    Play_rest(REST8);
    Play_note(HIC, NOTE8);                     // line 4
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_note(MIAX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE1);
    Play_rest(REST4);
    Play_note(MIA, NOTE4D);                    // line 5
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(MIA, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(MIG, NOTE4);
    Play_note(MIG, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE2);
    Play_rest(REST4);
    Play_note(MIG, NOTE4);                     // line 6
    Play_note(MIAX, NOTE4);
    Play_note(HIC, NOTE4);
    Play_note(HID, NOTE4D);
    Play_note(HIF, NOTE8);
    Play_note(HIG, NOTE8);
    Play_note(HIF, NOTE8);
    Play_note(HID, NOTE1);
    Play_rest(REST4);
    Play_note(HIG, NOTE4D);                    // line 7
    Play_note(HIF, NOTE8);
    Play_note(HIG, NOTE8);
    Play_note(HIF, NOTE8);
    Play_note(HID, NOTE2D);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_rest(REST8);
    Play_note(MID, NOTE8);                     // line 8
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(MIAX, NOTE8T);
    Play_note(HIC, NOTE8T);
    Play_note(MIAX, NOTE8T);
    Play_note(MIG, NOTE1);
    Play_rest(REST1);
    Delay_ms(1000);

    LCD_string(0xC0, "   Empty Sky    ");      // display music
    tempo = 4;                                 // set tempo
    Play_note(MIA, NOTE8);                     // line 1
    Play_note(MIB, NOTE8);
    Play_note(MIFX, NOTE4D);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIFX, NOTE2D);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(LOB, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(LOA, NOTE2D);
    Play_note(MID, NOTE8);                     // line 2
    Play_note(LOA, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIB, NOTE2);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE1);
    Play_rest(REST4);
    Play_note(MID, NOTE8);                     // line 3
    Play_note(MID, NOTE8);
    Play_note(HID, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HID, NOTE2D);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE4D);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE2D);
    Play_note(MIE, NOTE8);                     // line 4
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE4D);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIFX, NOTE4D);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE1);
    Play_rest(REST4);
    Play_note(HID, NOTE8);                     // line 5
    Play_note(HIE, NOTE8);
    Play_note(HIE, NOTE4D);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HIFX, NOTE2);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HIFX, NOTE8);
    Play_note(HIE, NOTE2D);
    Play_note(HIFX, NOTE8);                    // line 6
    Play_note(HIFX, NOTE8);
    Play_note(HIFX, NOTE4D);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE4);
    Play_note(MIB, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIA, NOTE2D);
    Play_note(LOA, NOTE8);                     // line 7
    Play_note(LOB, NOTE8);
    Play_note(MID, NOTE4D);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(HID, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE2);
    Play_note(MIA, NOTE8);                     // line 8
    Play_note(HIFX, NOTE8);
    Play_note(HIFX, NOTE4);
    Play_note(HIFX, NOTE4);
    Play_note(HIE, NOTE4D);
    Play_note(HIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE1);
    Play_rest(REST1);
    Delay_ms(1000);
  }
}
