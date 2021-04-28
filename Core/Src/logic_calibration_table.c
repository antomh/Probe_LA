/*******************************************************************************
 * @File: logic_calibration_table.c
 * @Author: Kozlov-dev, A.
 * @Project: Probe_LA.c * @Microcontroller: STM32F103C8T
 * @Device: Probe_LA
 * @Date: 07.04.2021
 * @Purpose: Calibration table volt2dac
 *******************************************************************************/
#include <logic_calibration_table.h>
#include <math.h>

//void crete_calibration_table(Table_t *calibTable){//de
//
//     calibTable->dacValA_m12[0] = 0x0;
//     calibTable->dacValA_m12[1] = 0x189;
//     calibTable->dacValA_m12[2] = 0x31d;
//     calibTable->dacValA_m12[3] = 0x223;
//     calibTable->dacValA_m12[4] = 0x21f;
//     calibTable->dacValA_m12[5] = 0x19d;
//     calibTable->dacValA_m12[6] = 0x27e;
//     calibTable->dacValA_m12[7] = 0x297;
//     calibTable->dacValA_m12[8] = 0x27e;
//     calibTable->dacValA_m12[9] = 0x297;
//     calibTable->dacValA_m12[10] = 0x1a1;
//     calibTable->dacValA_m12[11] = 0x223;
//     calibTable->dacValA_m12[12] = 0x21e;
//     calibTable->dacValA_m12[13] = 0x1b6;
//     calibTable->dacValA_m12[14] = 0x297;
//     calibTable->dacValA_m12[15] = 0x188;
//     calibTable->dacValA_m12[16] = 0x223;
//     calibTable->dacValA_m12[17] = 0x1a6;
//     calibTable->dacValA_m12[18] = 0x233;
//     calibTable->dacValA_m12[19] = 0x29b;
//     calibTable->dacValA_m12[20] = 0x21e;
//     calibTable->dacValA_m12[21] = 0x1b6;
//     calibTable->dacValA_m12[22] = 0x2e6;
//     calibTable->dacValA_m12[23] = 0x233;
//     calibTable->dacValA_m12[24] = 0x184;
//     calibTable->dacValA_m12[25] = 0x27e;
//     calibTable->dacValA_m12[26] = 0x855;
//     calibTable->dacValA_m12[27] = 0x877;
//     calibTable->dacValA_m12[28] = 0x8b1;
//     calibTable->dacValA_m12[29] = 0x8cb;
//     calibTable->dacValA_m12[30] = 0x8fc;
//     calibTable->dacValA_m12[31] = 0x960;
//     calibTable->dacValA_m12[32] = 0x953;
//     calibTable->dacValA_m12[33] = 0x992;
//     calibTable->dacValA_m12[34] = 0x9c4;
//     calibTable->dacValA_m12[35] = 0x9d6;
//     calibTable->dacValA_m12[36] = 0xa02;
//     calibTable->dacValA_m12[37] = 0xa2f;
//     calibTable->dacValA_m12[38] = 0x9dd;
//     calibTable->dacValA_m12[39] = 0xa89;
//     calibTable->dacValA_m12[40] = 0xab4;
//     calibTable->dacValA_m12[41] = 0xae1;
//     calibTable->dacValA_m12[42] = 0xb0b;
//     calibTable->dacValA_m12[43] = 0xb36;
//     calibTable->dacValA_m12[44] = 0xb8b;
//     calibTable->dacValA_m12[45] = 0xb8f;
//     calibTable->dacValA_m12[46] = 0xbd1;
//     calibTable->dacValA_m12[47] = 0xbe6;
//     calibTable->dacValA_m12[48] = 0xc12;
//     calibTable->dacValA_m12[49] = 0xc4e;
//     calibTable->dacValA_m12[50] = 0xc69;
//     calibTable->dacValA_m12[51] = 0xc96;
//     calibTable->dacValA_m12[52] = 0xcd5;
//     calibTable->dacValA_m12[53] = 0xcee;
//     calibTable->dacValA_m12[54] = 0xd19;
//     calibTable->dacValA_m12[55] = 0xc98;
//     calibTable->dacValA_m12[56] = 0xd70;
//     calibTable->dacValA_m12[57] = 0xd99;
//     calibTable->dacValA_m12[58] = 0xdb7;
//     calibTable->dacValA_m12[59] = 0xdca;
//     calibTable->dacValA_m12[60] = 0xdd8;
//     calibTable->dacValA_m12[61] = 0xddc;
//     calibTable->dacValA_m12[62] = 0xde9;
//     calibTable->dacValA_m12[63] = 0xded;
//     calibTable->dacValA_m12[64] = 0xdf4;
//     calibTable->dacValA_m12[65] = 0xdf9;
//     calibTable->dacValA_m12[66] = 0xdfc;
//     calibTable->dacValA_m12[67] = 0xdf7;
//     calibTable->dacValA_m12[68] = 0xdf8;
//     calibTable->dacValA_m12[69] = 0xdfa;
//     calibTable->dacValA_m12[70] = 0xdfc;
//     calibTable->dacValA_m12[71] = 0xdfe;
//     calibTable->dacValA_m12[72] = 0xe01;
//     calibTable->dacValA_m12[73] = 0xe01;
//     calibTable->dacValA_m12[74] = 0xe06;
//     calibTable->dacValA_m12[75] = 0xe06;
//     calibTable->dacValA_m12[76] = 0xe0a;
//     calibTable->dacValA_m12[77] = 0xe0e;
//     calibTable->dacValA_m12[78] = 0xe05;
//     calibTable->dacValA_m12[79] = 0xe01;
//     calibTable->dacValA_m12[80] = 0xe09;
//     calibTable->dacValA_m12[81] = 0x7d0;
//     calibTable->dacValA_m12[82] = 0xe06;
//     calibTable->dacValA_m12[83] = 0x7d0;
//     calibTable->dacValA_m12[84] = 0xe06;
//     calibTable->dacValA_m12[85] = 0xe00;
//     calibTable->dacValA_m12[86] = 0xdfe;
//     calibTable->dacValA_m12[87] = 0x1000;
//
//     calibTable->dacValB_m12[0] = 0x0;
//     calibTable->dacValB_m12[1] = 0x1bb;
//     calibTable->dacValB_m12[2] = 0x1ed;
//     calibTable->dacValB_m12[3] = 0x251;
//     calibTable->dacValB_m12[4] = 0x1bb;
//     calibTable->dacValB_m12[5] = 0x1ed;
//     calibTable->dacValB_m12[6] = 0x2ce;
//     calibTable->dacValB_m12[7] = 0x1d4;
//     calibTable->dacValB_m12[8] = 0x1f2;
//     calibTable->dacValB_m12[9] = 0x1d9;
//     calibTable->dacValB_m12[10] = 0x1bc;
//     calibTable->dacValB_m12[11] = 0x1bb;
//     calibTable->dacValB_m12[12] = 0x1f3;
//     calibTable->dacValB_m12[13] = 0x1d9;
//     calibTable->dacValB_m12[14] = 0x1ed;
//     calibTable->dacValB_m12[15] = 0x1f3;
//     calibTable->dacValB_m12[16] = 0x1c0;
//     calibTable->dacValB_m12[17] = 0x1c1;
//     calibTable->dacValB_m12[18] = 0x1c0;
//     calibTable->dacValB_m12[19] = 0x2ec;
//     calibTable->dacValB_m12[20] = 0x1d4;
//     calibTable->dacValB_m12[21] = 0x251;
//     calibTable->dacValB_m12[22] = 0x1d4;
//     calibTable->dacValB_m12[23] = 0x1d4;
//     calibTable->dacValB_m12[24] = 0x2ce;
//     calibTable->dacValB_m12[25] = 0x1cb;
//     calibTable->dacValB_m12[26] = 0x857;
//     calibTable->dacValB_m12[27] = 0x877;
//     calibTable->dacValB_m12[28] = 0x8a4;
//     calibTable->dacValB_m12[29] = 0x8cf;
//     calibTable->dacValB_m12[30] = 0x8fb;
//     calibTable->dacValB_m12[31] = 0x926;
//     calibTable->dacValB_m12[32] = 0x954;
//     calibTable->dacValB_m12[33] = 0x980;
//     calibTable->dacValB_m12[34] = 0x9ac;
//     calibTable->dacValB_m12[35] = 0x9d8;
//     calibTable->dacValB_m12[36] = 0xa04;
//     calibTable->dacValB_m12[37] = 0xa30;
//     calibTable->dacValB_m12[38] = 0xa5b;
//     calibTable->dacValB_m12[39] = 0xa86;
//     calibTable->dacValB_m12[40] = 0xab2;
//     calibTable->dacValB_m12[41] = 0xadf;
//     calibTable->dacValB_m12[42] = 0xb0b;
//     calibTable->dacValB_m12[43] = 0xb36;
//     calibTable->dacValB_m12[44] = 0xb63;
//     calibTable->dacValB_m12[45] = 0xb8e;
//     calibTable->dacValB_m12[46] = 0xbea;
//     calibTable->dacValB_m12[47] = 0xafd;
//     calibTable->dacValB_m12[48] = 0xb91;
//     calibTable->dacValB_m12[49] = 0xc3d;
//     calibTable->dacValB_m12[50] = 0xc69;
//     calibTable->dacValB_m12[51] = 0xbbe;
//     calibTable->dacValB_m12[52] = 0xcc2;
//     calibTable->dacValB_m12[53] = 0xd20;
//     calibTable->dacValB_m12[54] = 0xd19;
//     calibTable->dacValB_m12[55] = 0xd44;
//     calibTable->dacValB_m12[56] = 0xd6e;
//     calibTable->dacValB_m12[57] = 0xd92;
//     calibTable->dacValB_m12[58] = 0xd17;
//     calibTable->dacValB_m12[59] = 0xdc5;
//     calibTable->dacValB_m12[60] = 0xdc2;
//     calibTable->dacValB_m12[61] = 0xdcb;
//     calibTable->dacValB_m12[62] = 0xdd4;
//     calibTable->dacValB_m12[63] = 0xdd9;
//     calibTable->dacValB_m12[64] = 0xe09;
//     calibTable->dacValB_m12[65] = 0xc6a;
//     calibTable->dacValB_m12[66] = 0xbbc;
//     calibTable->dacValB_m12[67] = 0xc5d;
//     calibTable->dacValB_m12[68] = 0xc4f;
//     calibTable->dacValB_m12[69] = 0xcde;
//     calibTable->dacValB_m12[70] = 0xc52;
//     calibTable->dacValB_m12[71] = 0xdde;
//     calibTable->dacValB_m12[72] = 0xdff;
//     calibTable->dacValB_m12[73] = 0xe05;
//     calibTable->dacValB_m12[74] = 0xe0b;
//     calibTable->dacValB_m12[75] = 0xc80;
//     calibTable->dacValB_m12[76] = 0xc1f;
//     calibTable->dacValB_m12[77] = 0xe0d;
//     calibTable->dacValB_m12[78] = 0xc77;
//     calibTable->dacValB_m12[79] = 0xd49;
//     calibTable->dacValB_m12[80] = 0xd55;
//     calibTable->dacValB_m12[81] = 0xcf5;
//     calibTable->dacValB_m12[82] = 0xe14;
//     calibTable->dacValB_m12[83] = 0xd7f;
//     calibTable->dacValB_m12[84] = 0xd2a;
//     calibTable->dacValB_m12[85] = 0xd51;
//     calibTable->dacValB_m12[86] = 0xde0;
//     calibTable->dacValB_m12[87] = 0x1000;
//
//     calibTable->dacValA_m27[0] = 0x0;
//     calibTable->dacValA_m27[1] = 0x1f1;
//     calibTable->dacValA_m27[2] = 0x1a6;
//     calibTable->dacValA_m27[3] = 0x21e;
//     calibTable->dacValA_m27[4] = 0x233;
//     calibTable->dacValA_m27[5] = 0x27e;
//     calibTable->dacValA_m27[6] = 0x27e;
//     calibTable->dacValA_m27[7] = 0x1bb;
//     calibTable->dacValA_m27[8] = 0x1bb;
//     calibTable->dacValA_m27[9] = 0x1bb;
//     calibTable->dacValA_m27[10] = 0x477;
//     calibTable->dacValA_m27[11] = 0x5a3;
//     calibTable->dacValA_m27[12] = 0x1c4;
//     calibTable->dacValA_m27[13] = 0x1bb;
//     calibTable->dacValA_m27[14] = 0x1bb;
//     calibTable->dacValA_m27[15] = 0x29c;
//     calibTable->dacValA_m27[16] = 0x1bf;
//     calibTable->dacValA_m27[17] = 0x1bb;
//     calibTable->dacValA_m27[18] = 0x386;
//     calibTable->dacValA_m27[19] = 0x1bf;
//     calibTable->dacValA_m27[20] = 0x1bb;
//     calibTable->dacValA_m27[21] = 0x283;
//     calibTable->dacValA_m27[22] = 0x37d;
//     calibTable->dacValA_m27[23] = 0x283;
//     calibTable->dacValA_m27[24] = 0x37d;
//     calibTable->dacValA_m27[25] = 0x37d;
//     calibTable->dacValA_m27[26] = 0x843;
//     calibTable->dacValA_m27[27] = 0x843;
//     calibTable->dacValA_m27[28] = 0x83e;
//     calibTable->dacValA_m27[29] = 0x869;
//     calibTable->dacValA_m27[30] = 0x870;
//     calibTable->dacValA_m27[31] = 0x877;
//     calibTable->dacValA_m27[32] = 0x7d9;
//     calibTable->dacValA_m27[33] = 0x7e3;
//     calibTable->dacValA_m27[34] = 0x864;
//     calibTable->dacValA_m27[35] = 0x800;
//     calibTable->dacValA_m27[36] = 0x864;
//     calibTable->dacValA_m27[37] = 0x828;
//     calibTable->dacValA_m27[38] = 0x8cc;
//     calibTable->dacValA_m27[39] = 0x8d2;
//     calibTable->dacValA_m27[40] = 0x7fc;
//     calibTable->dacValA_m27[41] = 0x864;
//     calibTable->dacValA_m27[42] = 0x7fc;
//     calibTable->dacValA_m27[43] = 0x8ff;
//     calibTable->dacValA_m27[44] = 0x87e;
//     calibTable->dacValA_m27[45] = 0x834;
//     calibTable->dacValA_m27[46] = 0x828;
//     calibTable->dacValA_m27[47] = 0x847;
//     calibTable->dacValA_m27[48] = 0x800;
//     calibTable->dacValA_m27[49] = 0x87d;
//     calibTable->dacValA_m27[50] = 0x94a;
//     calibTable->dacValA_m27[51] = 0x977;
//     calibTable->dacValA_m27[52] = 0x7de;
//     calibTable->dacValA_m27[53] = 0x864;
//     calibTable->dacValA_m27[54] = 0x974;
//     calibTable->dacValA_m27[55] = 0x90f;
//     calibTable->dacValA_m27[56] = 0x8dd;
//     calibTable->dacValA_m27[57] = 0x874;
//     calibTable->dacValA_m27[58] = 0x7d4;
//     calibTable->dacValA_m27[59] = 0x7e3;
//     calibTable->dacValA_m27[60] = 0x7e8;
//     calibTable->dacValA_m27[61] = 0x914;
//     calibTable->dacValA_m27[62] = 0x9d3;
//     calibTable->dacValA_m27[63] = 0x919;
//     calibTable->dacValA_m27[64] = 0x8fb;
//     calibTable->dacValA_m27[65] = 0x7e4;
//     calibTable->dacValA_m27[66] = 0x86b;
//     calibTable->dacValA_m27[67] = 0x814;
//     calibTable->dacValA_m27[68] = 0x823;
//     calibTable->dacValA_m27[69] = 0x826;
//     calibTable->dacValA_m27[70] = 0x8af;
//     calibTable->dacValA_m27[71] = 0x804;
//     calibTable->dacValA_m27[72] = 0xa44;
//     calibTable->dacValA_m27[73] = 0x7ef;
//     calibTable->dacValA_m27[74] = 0x8f0;
//     calibTable->dacValA_m27[75] = 0x853;
//     calibTable->dacValA_m27[76] = 0x7d4;
//     calibTable->dacValA_m27[77] = 0x900;
//     calibTable->dacValA_m27[78] = 0x949;
//     calibTable->dacValA_m27[79] = 0x951;
//     calibTable->dacValA_m27[80] = 0xa80;
//     calibTable->dacValA_m27[81] = 0x832;
//     calibTable->dacValA_m27[82] = 0x899;
//     calibTable->dacValA_m27[83] = 0x879;
//     calibTable->dacValA_m27[84] = 0xac1;
//     calibTable->dacValA_m27[85] = 0x8b7;
//     calibTable->dacValA_m27[86] = 0x8dd;
//     calibTable->dacValA_m27[87] = 0x7d0;
//     calibTable->dacValA_m27[88] = 0x897;
//     calibTable->dacValA_m27[89] = 0x7d3;
//     calibTable->dacValA_m27[90] = 0x94b;
//     calibTable->dacValA_m27[91] = 0x8e9;
//     calibTable->dacValA_m27[92] = 0x8e9;
//     calibTable->dacValA_m27[93] = 0x7da;
//     calibTable->dacValA_m27[94] = 0x836;
//     calibTable->dacValA_m27[95] = 0x802;
//     calibTable->dacValA_m27[96] = 0x836;
//     calibTable->dacValA_m27[97] = 0x802;
//     calibTable->dacValA_m27[98] = 0x8cc;
//     calibTable->dacValA_m27[99] = 0x8e3;
//     calibTable->dacValA_m27[100] = 0x8cc;
//     calibTable->dacValA_m27[101] = 0x917;
//     calibTable->dacValA_m27[102] = 0x917;
//     calibTable->dacValA_m27[103] = 0x931;
//     calibTable->dacValA_m27[104] = 0x930;
//     calibTable->dacValA_m27[105] = 0xb95;
//     calibTable->dacValA_m27[106] = 0xb90;
//     calibTable->dacValA_m27[107] = 0xbc2;
//     calibTable->dacValA_m27[108] = 0x962;
//     calibTable->dacValA_m27[109] = 0x992;
//     calibTable->dacValA_m27[110] = 0x992;
//     calibTable->dacValA_m27[111] = 0x9ab;
//     calibTable->dacValA_m27[112] = 0x994;
//     calibTable->dacValA_m27[113] = 0xa9f;
//     calibTable->dacValA_m27[114] = 0xbd0;
//     calibTable->dacValA_m27[115] = 0xbea;
//     calibTable->dacValA_m27[116] = 0x9c6;
//     calibTable->dacValA_m27[117] = 0xb31;
//     calibTable->dacValA_m27[118] = 0xc1c;
//     calibTable->dacValA_m27[119] = 0x9ec;
//     calibTable->dacValA_m27[120] = 0x9f8;
//     calibTable->dacValA_m27[121] = 0xa0f;
//     calibTable->dacValA_m27[122] = 0x9fa;
//     calibTable->dacValA_m27[123] = 0xc46;
//     calibTable->dacValA_m27[124] = 0xc43;
//     calibTable->dacValA_m27[125] = 0xa1e;
//     calibTable->dacValA_m27[126] = 0xa32;
//     calibTable->dacValA_m27[127] = 0xa32;
//     calibTable->dacValA_m27[128] = 0xa39;
//     calibTable->dacValA_m27[129] = 0xa50;
//     calibTable->dacValA_m27[130] = 0xcb0;
//     calibTable->dacValA_m27[131] = 0xa5a;
//     calibTable->dacValA_m27[132] = 0xa64;
//     calibTable->dacValA_m27[133] = 0xcb0;
//     calibTable->dacValA_m27[134] = 0xa76;
//     calibTable->dacValA_m27[135] = 0xcbf;
//     calibTable->dacValA_m27[136] = 0xa8c;
//     calibTable->dacValA_m27[137] = 0xa95;
//     calibTable->dacValA_m27[138] = 0xcd9;
//     calibTable->dacValA_m27[139] = 0xaaa;
//     calibTable->dacValA_m27[140] = 0xbcb;
//     calibTable->dacValA_m27[141] = 0xbcf;
//     calibTable->dacValA_m27[142] = 0xacb;
//     calibTable->dacValA_m27[143] = 0xae1;
//     calibTable->dacValA_m27[144] = 0xaeb;
//     calibTable->dacValA_m27[145] = 0xaeb;
//     calibTable->dacValA_m27[146] = 0xaec;
//     calibTable->dacValA_m27[147] = 0xaf4;
//     calibTable->dacValA_m27[148] = 0xafc;
//     calibTable->dacValA_m27[149] = 0xc38;
//     calibTable->dacValA_m27[150] = 0xb18;
//     calibTable->dacValA_m27[151] = 0xb11;
//     calibTable->dacValA_m27[152] = 0xb27;
//     calibTable->dacValA_m27[153] = 0xb25;
//     calibTable->dacValA_m27[154] = 0xb2c;
//     calibTable->dacValA_m27[155] = 0xb31;
//     calibTable->dacValA_m27[156] = 0xb45;
//     calibTable->dacValA_m27[157] = 0xb56;
//     calibTable->dacValA_m27[158] = 0xb54;
//     calibTable->dacValA_m27[159] = 0xb56;
//     calibTable->dacValA_m27[160] = 0xb63;
//     calibTable->dacValA_m27[161] = 0xb62;
//     calibTable->dacValA_m27[162] = 0x1000;
//
//     calibTable->dacValB_m27[0] = 0x0;
//     calibTable->dacValB_m27[1] = 0x1c1;
//     calibTable->dacValB_m27[2] = 0x1d5;
//     calibTable->dacValB_m27[3] = 0x1d5;
//     calibTable->dacValB_m27[4] = 0x1d5;
//     calibTable->dacValB_m27[5] = 0x1d5;
//     calibTable->dacValB_m27[6] = 0x1d5;
//     calibTable->dacValB_m27[7] = 0x1d5;
//     calibTable->dacValB_m27[8] = 0x1d9;
//     calibTable->dacValB_m27[9] = 0x1f8;
//     calibTable->dacValB_m27[10] = 0x1bb;
//     calibTable->dacValB_m27[11] = 0x1bb;
//     calibTable->dacValB_m27[12] = 0x1bb;
//     calibTable->dacValB_m27[13] = 0x571;
//     calibTable->dacValB_m27[14] = 0x1bb;
//     calibTable->dacValB_m27[15] = 0x283;
//     calibTable->dacValB_m27[16] = 0x1cf;
//     calibTable->dacValB_m27[17] = 0x1c9;
//     calibTable->dacValB_m27[18] = 0x1bf;
//     calibTable->dacValB_m27[19] = 0x1bb;
//     calibTable->dacValB_m27[20] = 0x21f;
//     calibTable->dacValB_m27[21] = 0x1cf;
//     calibTable->dacValB_m27[22] = 0x1e8;
//     calibTable->dacValB_m27[23] = 0x1e8;
//     calibTable->dacValB_m27[24] = 0x1cf;
//     calibTable->dacValB_m27[25] = 0x1e8;
//     calibTable->dacValB_m27[26] = 0x7d3;
//     calibTable->dacValB_m27[27] = 0x80b;
//     calibTable->dacValB_m27[28] = 0x857;
//     calibTable->dacValB_m27[29] = 0x875;
//     calibTable->dacValB_m27[30] = 0x866;
//     calibTable->dacValB_m27[31] = 0x7d0;
//     calibTable->dacValB_m27[32] = 0x877;
//     calibTable->dacValB_m27[33] = 0x8a7;
//     calibTable->dacValB_m27[34] = 0x8a2;
//     calibTable->dacValB_m27[35] = 0x7f7;
//     calibTable->dacValB_m27[36] = 0x857;
//     calibTable->dacValB_m27[37] = 0x829;
//     calibTable->dacValB_m27[38] = 0x8f2;
//     calibTable->dacValB_m27[39] = 0x897;
//     calibTable->dacValB_m27[40] = 0x8cc;
//     calibTable->dacValB_m27[41] = 0x8ca;
//     calibTable->dacValB_m27[42] = 0x81f;
//     calibTable->dacValB_m27[43] = 0x7de;
//     calibTable->dacValB_m27[44] = 0x864;
//     calibTable->dacValB_m27[45] = 0x8ce;
//     calibTable->dacValB_m27[46] = 0x8d9;
//     calibTable->dacValB_m27[47] = 0x870;
//     calibTable->dacValB_m27[48] = 0x7de;
//     calibTable->dacValB_m27[49] = 0x80b;
//     calibTable->dacValB_m27[50] = 0x95b;
//     calibTable->dacValB_m27[51] = 0x89c;
//     calibTable->dacValB_m27[52] = 0x95b;
//     calibTable->dacValB_m27[53] = 0x7e2;
//     calibTable->dacValB_m27[54] = 0x8ce;
//     calibTable->dacValB_m27[55] = 0x974;
//     calibTable->dacValB_m27[56] = 0x7e7;
//     calibTable->dacValB_m27[57] = 0x801;
//     calibTable->dacValB_m27[58] = 0x864;
//     calibTable->dacValB_m27[59] = 0x8a1;
//     calibTable->dacValB_m27[60] = 0x988;
//     calibTable->dacValB_m27[61] = 0x7e3;
//     calibTable->dacValB_m27[62] = 0x864;
//     calibTable->dacValB_m27[63] = 0x92a;
//     calibTable->dacValB_m27[64] = 0x7fc;
//     calibTable->dacValB_m27[65] = 0x897;
//     calibTable->dacValB_m27[66] = 0x892;
//     calibTable->dacValB_m27[67] = 0x8af;
//     calibTable->dacValB_m27[68] = 0x83a;
//     calibTable->dacValB_m27[69] = 0x810;
//     calibTable->dacValB_m27[70] = 0x83a;
//     calibTable->dacValB_m27[71] = 0x7d4;
//     calibTable->dacValB_m27[72] = 0x914;
//     calibTable->dacValB_m27[73] = 0x7d6;
//     calibTable->dacValB_m27[74] = 0x8e8;
//     calibTable->dacValB_m27[75] = 0x7e8;
//     calibTable->dacValB_m27[76] = 0x8e7;
//     calibTable->dacValB_m27[77] = 0x8fa;
//     calibTable->dacValB_m27[78] = 0xa82;
//     calibTable->dacValB_m27[79] = 0x86c;
//     calibTable->dacValB_m27[80] = 0x906;
//     calibTable->dacValB_m27[81] = 0x8f8;
//     calibTable->dacValB_m27[82] = 0x885;
//     calibTable->dacValB_m27[83] = 0x884;
//     calibTable->dacValB_m27[84] = 0x930;
//     calibTable->dacValB_m27[85] = 0x865;
//     calibTable->dacValB_m27[86] = 0x8d0;
//     calibTable->dacValB_m27[87] = 0x7e7;
//     calibTable->dacValB_m27[88] = 0x8b9;
//     calibTable->dacValB_m27[89] = 0xab4;
//     calibTable->dacValB_m27[90] = 0x8c8;
//     calibTable->dacValB_m27[91] = 0x8e9;
//     calibTable->dacValB_m27[92] = 0xaff;
//     calibTable->dacValB_m27[93] = 0x7da;
//     calibTable->dacValB_m27[94] = 0x804;
//     calibTable->dacValB_m27[95] = 0x7da;
//     calibTable->dacValB_m27[96] = 0x804;
//     calibTable->dacValB_m27[97] = 0x7da;
//     calibTable->dacValB_m27[98] = 0x8ca;
//     calibTable->dacValB_m27[99] = 0x947;
//     calibTable->dacValB_m27[100] = 0x8fe;
//     calibTable->dacValB_m27[101] = 0x8fc;
//     calibTable->dacValB_m27[102] = 0x8ed;
//     calibTable->dacValB_m27[103] = 0x989;
//     calibTable->dacValB_m27[104] = 0x92e;
//     calibTable->dacValB_m27[105] = 0x930;
//     calibTable->dacValB_m27[106] = 0x9cf;
//     calibTable->dacValB_m27[107] = 0x979;
//     calibTable->dacValB_m27[108] = 0x9cf;
//     calibTable->dacValB_m27[109] = 0x979;
//     calibTable->dacValB_m27[110] = 0x9e6;
//     calibTable->dacValB_m27[111] = 0x9fc;
//     calibTable->dacValB_m27[112] = 0x992;
//     calibTable->dacValB_m27[113] = 0xaa9;
//     calibTable->dacValB_m27[114] = 0xbd0;
//     calibTable->dacValB_m27[115] = 0xc1c;
//     calibTable->dacValB_m27[116] = 0x9c6;
//     calibTable->dacValB_m27[117] = 0xb2b;
//     calibTable->dacValB_m27[118] = 0x9d8;
//     calibTable->dacValB_m27[119] = 0xc1f;
//     calibTable->dacValB_m27[120] = 0xb5d;
//     calibTable->dacValB_m27[121] = 0xc50;
//     calibTable->dacValB_m27[122] = 0xc4e;
//     calibTable->dacValB_m27[123] = 0xc4c;
//     calibTable->dacValB_m27[124] = 0xa0e;
//     calibTable->dacValB_m27[125] = 0xc76;
//     calibTable->dacValB_m27[126] = 0xbed;
//     calibTable->dacValB_m27[127] = 0xa2f;
//     calibTable->dacValB_m27[128] = 0xa36;
//     calibTable->dacValB_m27[129] = 0xc80;
//     calibTable->dacValB_m27[130] = 0xc71;
//     calibTable->dacValB_m27[131] = 0xa55;
//     calibTable->dacValB_m27[132] = 0xcac;
//     calibTable->dacValB_m27[133] = 0xa6b;
//     calibTable->dacValB_m27[134] = 0xcbb;
//     calibTable->dacValB_m27[135] = 0xa7d;
//     calibTable->dacValB_m27[136] = 0xb9a;
//     calibTable->dacValB_m27[137] = 0xba7;
//     calibTable->dacValB_m27[138] = 0xab4;
//     calibTable->dacValB_m27[139] = 0xbe4;
//     calibTable->dacValB_m27[140] = 0xab4;
//     calibTable->dacValB_m27[141] = 0xbbc;
//     calibTable->dacValB_m27[142] = 0xbba;
//     calibTable->dacValB_m27[143] = 0xd02;
//     calibTable->dacValB_m27[144] = 0xbf3;
//     calibTable->dacValB_m27[145] = 0xaf0;
//     calibTable->dacValB_m27[146] = 0xaed;
//     calibTable->dacValB_m27[147] = 0xaf8;
//     calibTable->dacValB_m27[148] = 0xcfc;
//     calibTable->dacValB_m27[149] = 0xc18;
//     calibTable->dacValB_m27[150] = 0xb0b;
//     calibTable->dacValB_m27[151] = 0xb18;
//     calibTable->dacValB_m27[152] = 0xb1b;
//     calibTable->dacValB_m27[153] = 0xc08;
//     calibTable->dacValB_m27[154] = 0xb2a;
//     calibTable->dacValB_m27[155] = 0xb2f;
//     calibTable->dacValB_m27[156] = 0xd09;
//     calibTable->dacValB_m27[157] = 0xc0a;
//     calibTable->dacValB_m27[158] = 0xb4f;
//     calibTable->dacValB_m27[159] = 0xb56;
//     calibTable->dacValB_m27[160] = 0xb6d;
//     calibTable->dacValB_m27[161] = 0xb44;
//     calibTable->dacValB_m27[162] = 0x1000;
//
// }

//--------------------------------------------------------------------------
// Описание: 
// Функция floor() возвращает наибольшее целое число (представленное как double), которое не больше, чем num. Например, если дано 1.02, то функция floor() возвращает 1.0. Если задано —1.02, то функция floor() возвращает —2.0.

// Функция floorl() представляет собой версию этой функции для переменных типа long double.
// floor()
// Пример: 
// Следующий фрагмент кода выводит на экран «10»:
// printf("%f", floor(10.9));

uint16_t volt2dgt(Table_t *calibTable, int16_t volt){

// TODO: Нужно ли учитывать Ктр? volt = volt*Ktr 
float count = (abs(MIN_VOLT_MODE_12)+abs(MAX_VOLT_MODE_12))/STEP_CALIBRATE;
uint16_t y = (floor((count*abs(MIN_VOLT_MODE_12))/(abs(MIN_VOLT_MODE_12)+abs(MAX_VOLT_MODE_12))/abs(MIN_VOLT_MODE_12)*volt+(count*abs(MIN_VOLT_MODE_12))/(abs(MIN_VOLT_MODE_12)+abs(MAX_VOLT_MODE_12)))); // искомый индекс в массиве!!! найти минимальное значение от него 26.5-->26 через floor
uint16_t CodeX = (((calibTable->dacValA_m12[y+1+1]-calibTable->dacValA_m12[y])/(((y+1+1) * STEP_CALIBRATE) -abs( MIN_VOLT_MODE_12)-((y+1) * STEP_CALIBRATE) - abs( MIN_VOLT_MODE_12))))*(volt-((y+1) * STEP_CALIBRATE) - abs( MIN_VOLT_MODE_12))+calibTable->dacValA_m12[y+1];
	return CodeX;
// printf((CodeX));


// uint16_t volt2dgt(union NVRAM *DevNVRAM, int16_t volt){


// // int16_t minVolt = MIN_VOLT_MODE_12;
// // int16_t maxVolt = MAX_VOLT_MODE_12;


// uint16_t x0 = abs(MIN_VOLT_MODE_12);
// uint16_t x1 = abs(MAX_VOLT_MODE_12);

// float count = (x0+x1)/STEP_CALIBRATE;

// uint16_t y0 = 0;            // начало индекса массива
// uint16_t y1 = count;        // конец индекса массива

// float b = (count*x0)/(x0+x1);
// float a = b/x0;

// int16_t x = volt ;// /Ktr!!!!!!!!!!!!!!
// int y = floor(a*x+b); // искомый индекс в массиве!!! найти минимальное значение от него 26.5-->26 через floor

// // TODO:Найти по найденому индексу значение в массиве!  и найти значение n+1

// uint16_t Ca0 =(uint16_t *) DevNVRAM->calibration_table.dacValA_m12[y];
// uint16_t Ca1 = DevNVRAM->calibration_table.dacValA_m12[y+1];

// uint16_t a0 = (y * STEP_CALIBRATE) - abs( MIN_VOLT_MODE_12);// TODO: не правльно переводит значения!27*200 = 5400
// uint16_t a1 = ((y+1) * STEP_CALIBRATE) -abs( MIN_VOLT_MODE_12);// TODO: не правльно переводит значения!28*200 = 5600



// float CodeX = (((Ca1-Ca0)/(a1-a0)))*(x-a0)+Ca0;
// 	return CodeX;
// // printf((CodeX));





}






































// //
// ////  Интерполяция
// uint16_t interpolation_dacVAL(uint16_t valDAC_0,uint16_t valDAC_1,uint16_t ya,uint16_t yb,uint16_t yc){
// 	uint16_t determined_value = 0;
// 	return determined_value = (yc - yb) * ((valDAC_0 - valDAC_1) / (ya - yb)) + valDAC_1;
// }


// //uint16_t interpolation_dacVAL(uint16_t xa,uint16_t xb,uint16_t ya,uint16_t yb,uint16_t yc){
// //	uint16_t determined_value = 0;
// // 	m = (xa - xb) / (ya - yb);
// //    xc = (yc - yb) * m + xb;
// //
// //    xc = (yc - yb) * (xa - xb) / (ya - yb) + xb;
// //
// //	return determined_value
// //}
// //--------------------------------------------------------------------------
// // Для перевода напряжения (в вольтах) в код ЦАП
// uint16_t vlt2dgt(uint16_t V) {
// 	uint16_t valDAC;
// 	return valDAC = (V/DAC_REF)*DAC_MAX;
// }
// //--------------------------------------------------------------------------
// uint16_t findValDAC(union NVRAM *DevNVRAM, uint16_t Volt) {
// 	// Проверим что таблица записана и контрольная сумма совпадает
// 	if ((DevNVRAM->calibration_table.MagicNum == MAGIC_KEY_DEFINE)
// 			&& ((DevNVRAM->sector.CheckSum == DevNVRAM->sector.CheckSum))) {
// 		//TODO: c начала найти значений которые есть в таблице

// 		for (int i = 0; i < MAX_VAL_M12; ++i) {

// 		if (DevNVRAM->calibration_table.dacValA_m12[i] == vlt2dgt(Volt)) {
// 					return DevNVRAM->calibration_table.dacValA_m12[i];
// 				}
// 				//TODO: Если нет в таблице, то интерпалировать из ближайшего меньшего и сдедующего
// 			else
// 			{

// 				//TODO Калибровочная не верная!!!

// 			}
// 		}
// 	}
// }
