void setup() {
  // Serial
  Serial.begin(600);
  while (!Serial)
    delay(10);
  
  Serial.write("Mulai\n\n");


  // byte; 1 byte = 8 bit
  Serial.write("\nOperasi Byte\n");

  byte ba = 0b00001111;
  byte bb = 0b11110000;
  byte bc = 0b00000000;

  // operasi byte
  Serial.write("(((");
  Serial.print(bb, BIN);
  Serial.write(" >> 4) & ");
  Serial.print(ba, BIN);
  Serial.write(") << 4) | ");
  Serial.print(bc, BIN);
  Serial.write(" = ");

  bc = (((bb >> 4) & ba) << 4) | bc;

  Serial.println(bc, BIN);


  // word; 1 word = 16 bit
  Serial.write("\nOperasi Word\n");

  word wa = 0b11110000111100001111; // 16 bit pertama saja yang akan disimpan (dari LSB)
  word wb = 0b1111111100000000;
  word wc = 0b0000000000000000;

  // operasi word
  Serial.write("((");
  Serial.print(wa, BIN);
  Serial.write(" | ");
  Serial.print(wb, BIN);
  Serial.write(") << 4) >> 4 = ");

  wc = wa | wb;
  wc <<= 4;
  wc >>= 4;

  Serial.println(wc, BIN);


  // array byte
  Serial.write("\nOperasi Array Byte dengan Pointer\n");
  byte arrb[3] = {ba, bb, bc};
  byte* arrx = nullptr;

  // operasi array dgn pointer
  Serial.write("{");
  Serial.print(arrb[0], BIN);
  Serial.write(", ");
  Serial.print(arrb[1], BIN);
  Serial.write(", ");
  Serial.print(arrb[2], BIN);
  Serial.write("} menjadi ");

  arrx = arrb;
  arrx[0] = bc;
  arrx[1] = bb;
  arrx[2] = ba;
  
  Serial.write("{");
  Serial.print(arrb[0], BIN);
  Serial.write(", ");
  Serial.print(arrb[1], BIN);
  Serial.write(", ");
  Serial.print(arrb[2], BIN);
  Serial.write("}\n");


  // array word
  Serial.write("\nOperasi Array Word dengan Pointer\n");
  word arrw[3] = {wa, wb, wc};
  word* arry = nullptr;

  // operasi
  Serial.write("{");
  Serial.print(arrw[0], BIN);
  Serial.write(", ");
  Serial.print(arrw[1], BIN);
  Serial.write(", ");
  Serial.print(arrw[2], BIN);
  Serial.write("} menjadi ");

  arry = arrw + 1;
  arry[0] = 0b1010101001010101;
  arry[1] = 0b1111111111111110;

  Serial.write("{");
  Serial.print(arrw[0], BIN);
  Serial.write(", ");
  Serial.print(arrw[1], BIN);
  Serial.write(", ");
  Serial.print(arrw[2], BIN);
  Serial.write("}\n");


  Serial.write("\n\nSelesai\n");
}

void loop() {}
