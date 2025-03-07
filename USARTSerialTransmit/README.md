<h2>
  I/O Read & USART Transmit dengan Register - Mencoba Low-Level Embedded Like Programming
</h2>
<h3>
  <br>
  Hardware yang digunakan:
  <h5>
    <br>
    - Arduino Uno R3
    <br>
    - Kabel USB A to USB B
    <br>
    - DIP switch 8 pin
  </h5>
  
  <p>
    <br>
    IOReadUSARTTransmit.ino berisi eksperimen I/O serta transmisi Serial pada Arduino Uno. Program akan membaca delapan pin digital yang dikontrol melalui DIP switch lalu mengirimkan state tersebut melalui modul Serial USART. Program dibuat tanpa menggunakan class Serial maupun fungsi digitalRead, hanya memanipulasi register USART dan I/O, sehingga sangat efektif dari segi memori program dan kecepatan eksekusi.
  </p>

  <p>
    <br>
    UCSR0B = (1 << TXEN0);
    <br>
    TXENn yang diset ke 1 akan mengaktifkan USART Transmitter.
    <br><br>
    UBRR0L = 0b10100000;
    <br>
    UBRR0H = 0b1;
    <br>
    UBRRnL dan UBBRnH digunakan untuk menentukan baudrate USART, nilai 000110100000 -> 2400 bps.
    <br><br>
    PORTD |= 0b11111100;
    <br>
    PORTB |= 0b11;
    <br>
    PORTD dan PORTB digunakan untuk mengatur input dengan internal resistor pull up, 1 -> pull up on.
    <br><br>
    uint8_t inputs = PIND >> 2;
    <br>
    inputs += PINB << 6;
    <br>
    PIND merupakan state digital pin 0 - 9, PINB merupakan state digital pin 8 - 13, shifting diperlukan untuk mengatur pin yang akan dibaca dan diassign ke inputs.
    <br><br>
    for(uint8_t i = 0; i < sizeof(uint8_t) * 8; i++) {
      <br>
      while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
      <br>
      inputs & 0b1 ? UDR0 = 49 : UDR0 = 48;
      <br>
      inputs >>= 1;
      <br>
    }
    <br>
    Blok ini akan mengirim byte inputs dalam karakter biner ('1' atau '0') sehingga byte inputs tidak direpresentasikan menjadi karakter ASCII oleh Serial Monitor. Ada while loop yang digunakan untuk menunggu hingga buffer kosong, yang ditandakan dengan nilai 1 pada bit UDREn pada register UCSRnA. Register UDRn diassign dan akan langsung mengirimkan data ke buffer.
    <br><br>
    while( ! ( UCSR0A & ( 1 << UDRE0 ) ) );
    <br>
    UDR0 = 10;
    <br>
    Blok ini akan mengirimkan karakter ASCII 10 (line feed) sebagai enter, merapihkan Serial Monitor.
    <br>
  </p>

  <br>
  Serial Monitor yang dihasilkan oleh kode ini adalah:
</h3>

<h6>
  <br>
  I/O & USART dengan register
  <br>
  00010111
  <br>
  00010111
  <br>
  00010111
  <br>
  00010111
  <br>
</h6>
