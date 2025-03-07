void setup() {
  // Aktifkan Serial0
  UCSR0B = (1 << TXEN0);

  // Set baud rate
  // Baud rate 2400 bps -> UBRR0 di-set ke 416 desimal atau 0001 1010 0000 biner
  UBRR0L = 0b10100000;
  UBRR0H = 0b1;

  // Untuk keperluan Serial Monitoring
  byte i = 0;
  const char* initTransmit = "\n\nI/O & USART dengan register\n\n";
  while(initTransmit[i] != '\0') {
    while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
    UDR0 = *(initTransmit + i++);
  }

  // Set input pull up pada pin digital 2 sampai 7
  PORTD |= 0b11111100;

  // Set input pull up pada pin digital 8 dan 9
  PORTB |= 0b11;
}

void loop() {
  // Membaca pin 2 sampai 7
  // Register PIND merupakan state pin digital 0 - 7 saat mode input, di shift ke kanan 2 kali karena pin digital 0 dan 1 tidak digunakan
  uint8_t inputs = PIND >> 2;

  // Membaca pin 8 dan 9 dan dimasukkan juga ke 'inputs'
  // Register PINB merupakan state pin digital 8 - 13 saat mode input, di shift ke kiri 6 kali karena pin digital 8 dan 9 digunakan sebagai bit ke 6 dan 7 pada 'inputs'
  inputs += PINB << 6;
  
  // Menunggu hingga Serial buffer kosong untuk mengirim data
  // Men-set register UDR akan mengirimkan data ke Serial
  // Mengirimkan byte 'inputs' sebagai 8 buah karakter biner
  // UDR0 = 49 adalah karakter 1 -- UDR0 = 48 adalah karakter 0
  for(uint8_t i = 0; i < sizeof(uint8_t) * 8; i++) {
    while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
    inputs & 0b1 ? UDR0 = 49 : UDR0 = 48;
    inputs >>= 1;
  }

  // new line (ASCII 10) untuk keperluan serial monitoring
  while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
  UDR0 = 10;
}
