void setup() {
  char buff[5] = {0, 0, 0, 0, 0};

  // MEMULAI SERIAL0 DGN BAUDRATE 600, PELAN SAJA
  Serial.begin(600);

  Serial.write("Mulai\n\n");

  while (true) {
    // JIKA TERDAPAT SESUATU PADA BUFFER SERIAL
    if (Serial.available()) {
      // HANYA MENERIMA 3 (TIGA) KARAKTER --> {CHAR, CHAR, CHAR, [LINE FEED]}
      if (Serial.readBytes(buff, 5) != 4)
        continue;
      
      // MENCETAK TIGA KARAKTER YANG DITERIMA KE MONITOR
      Serial.print("buff 1 = ");
      Serial.println(buff[0]);
      Serial.print("buff 2 = ");
      Serial.println(buff[1]);
      Serial.print("buff 3 = ");
      Serial.println(buff[2]);
      Serial.println();

      // BERHENTI, KELUAR DARI LOOP, JIKA DAN HANYA JIKA KARAKTER YG DITERIMA ADL X,X,X,[LINE FEED]
      if (buff[0] == 'X' && buff[1] == 'X' && buff[2] == 'X' && buff[3] == 10)
        break;
    }
  }

  Serial.write("Selesai");

  Serial.end();
}

void loop() {}
